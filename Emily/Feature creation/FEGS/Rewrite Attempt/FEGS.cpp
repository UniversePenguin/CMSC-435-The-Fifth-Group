#include <iostream>
#include <fstream>
#include <string>
#include <cmdparser.hpp>
#include <eigen3/Eigen/Dense>
#include <vector>
#include <math.h>

using namespace std;
using namespace Eigen;

float* upper_phi_values;
float* lower_phi_values;

Vector3<float> upper_phi(int i) {
    Vector3<float> toReturn(
        cos((2.0f * M_PIf * i)/20.0f),
        sin((2.0f * M_PIf * i)/20.0f),
        1.0f
    );
    return toReturn;
}

void calculatePhiValues(float* upper_phi_values, float* lower_phi_values) {
    for (int i = 1; i <= 20; i++) {
        size_t offset = 2 * (i-1);

        upper_phi_values[offset] = cos((2 * M_PIf * i)/20);
        upper_phi_values[offset + 1] = sin((2 * M_PIf * i)/20);
    }

    for (int i = 1; i <= 20; i++) {
        for (int j = 1; j <= 20; j++) {
            size_t i_offset = 2 * (i-1);
            size_t j_offset = 2 * (j-1);
            size_t total_offset = i_offset * 20 + j_offset;

            float upper_i_value_x = upper_phi_values[i_offset];
            float upper_i_value_y = upper_phi_values[i_offset + 1];
            float upper_j_value_x = upper_phi_values[j_offset];
            float upper_j_value_y = upper_phi_values[j_offset + 1];

            lower_phi_values[total_offset] = upper_i_value_x + ((1.0f/4.0f) * (upper_j_value_x - upper_i_value_x));
            lower_phi_values[total_offset + 1] = upper_i_value_y + ((1.0f/4.0f) * (upper_j_value_y - upper_i_value_y));
        }
    }
}

float getValue(int index, float* arr, char component) {
    size_t offset = 2 * index;

    switch(component) {
        case 'x':
            return arr[offset];
        case 'y':
            return arr[offset + 1];
        default:
            return -numeric_limits<float>::infinity();
    }
}

float getValue(int index_1, int index_2, float* arr, char component) {
    size_t i_offset = 2 * index_1;
    size_t j_offset = 2 * index_2;
    size_t total_offset = i_offset * 20 + j_offset;

    switch(component) {
        case 'x':
            return arr[total_offset];
        case 'y':
            return arr[total_offset + 1];
        default:
            return -numeric_limits<float>::infinity();
    }
}

float findPairFrequency(char a, char b, string seq) {
    if (seq.size() < 2) return 0.0f;
    int occurences = 0;
    for (int i = 0; i < seq.size()-1; i++) {
        if (seq[i] == a && seq[i+1] == b) {
            occurences++;
        }
    }
    return (float)occurences / (float)(seq.size()-1);
}

MatrixX3f psi(string seq, string AAindex) {
    const string aminoAcids = "ACDEFGHIKLMNPQRSTVWY";

    MatrixX3f toReturn(seq.size(), 3);

    for (int i = 0; i < seq.size(); i++) {
        RowVector3f term1;
        if (i==0) {
            term1 = RowVector3f::Zero();
        } else {
            term1 = toReturn.row(i-1);
        }
        
        RowVector3f term2(
            getValue(AAindex.find_first_of(seq[i]), upper_phi_values, 'x'),
            getValue(AAindex.find_first_of(seq[i]), upper_phi_values, 'y'),
            1
        );

        RowVector3f term3 = RowVector3f::Zero();

        for (int o1 = 0; o1 < aminoAcids.size(); o1++) {
            for (int o2 = 0; o2 < aminoAcids.size(); o2++) {

                float freq = findPairFrequency(aminoAcids[o1], aminoAcids[o2], seq.substr(0, i+1));

                RowVector3f phi_result(
                    getValue(AAindex.find_first_of(aminoAcids[o1]),AAindex.find_first_of(aminoAcids[o2]), lower_phi_values, 'x'),
                    getValue(AAindex.find_first_of(aminoAcids[o1]),AAindex.find_first_of(aminoAcids[o2]), lower_phi_values, 'y'),
                    1
                );

                term3 += (phi_result * freq);

            }
        }

        toReturn.row(i) = (term1+term2+term3);
    }

    return toReturn;
}

float reduceToNumericalFeature(string seq, string AAindex) {
    MatrixX3f points = psi(seq, AAindex);

    int totalPoints = points.rows();

    MatrixXf direct_distances(totalPoints, totalPoints);
    
    for (int i = 0; i < totalPoints; i++) {
        for (int j = 0; j <= i; j++) {
            if (i == j) {
                direct_distances(i, j) = 0;
            } else {
                Vector3f p1 = points.row(i);
                Vector3f p2 = points.row(j);
                direct_distances(i, j) = direct_distances(j, i) = sqrt(
                    pow(p1(0) - p2(0),2) + pow(p1(1) - p2(1),2) + pow(p1(2) - p2(2),2)
                );
            }
        }
    }

    MatrixXf path_distances(totalPoints, totalPoints);

    for (int i = 0; i < totalPoints; i++) {
        for (int j = i; j < totalPoints; j++) {
            if (i == j) {
                path_distances(i, j) = direct_distances(i, j);
            } else {
                path_distances(i, j) = path_distances(j,i) = path_distances(i, j-1) + direct_distances(j-1, j);
            }
        }
    }

    for (int i = 0; i < totalPoints; i++) {
        path_distances(i, i) = 1;
    }

    MatrixXf quotient(totalPoints, totalPoints);

    for (int i = 0; i < totalPoints; i++) {
        for (int j = 0; j < i; j++) {
            quotient(i, j) = quotient(j, i) = direct_distances(i, j)/path_distances(i, j);
        }
    }

    return quotient.eigenvalues()(0).real()/totalPoints;
}

int main(int argc, char *argv[]) {
    upper_phi_values = (float*) malloc(20 * (2 * sizeof(float)));
    lower_phi_values = (float*) malloc(400 * (2 * sizeof(float)));
    calculatePhiValues(upper_phi_values, lower_phi_values);

    // cout << psi("AGYLLGKINLKALAALAKKILTYADFIASGRTGRRNAI", "DKERNHYGQPWTSVAICFML") << endl;

    reduceToNumericalFeature("AGYLLGKINLKALAALAKKILTYADFIASGRTGRRNAI", "DKERNHYGQPWTSVAICFML");

    free(upper_phi_values);
    free(lower_phi_values);
}