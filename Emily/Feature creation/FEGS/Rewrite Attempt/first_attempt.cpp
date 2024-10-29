#include <iostream>
#include <math.h>
#include <vector>
#include <string>
#include <eigen3/Eigen/Eigen>
using namespace std;
using namespace Eigen;

class myDouble3 {
    public:
        double x, y , z;

    myDouble3() {
        x=y=z=0.0;
    }
    myDouble3(double x, double y, double z) {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    string toString() {
        return to_string(x) + ", " + to_string(y) + ", " + to_string(z);
    }

    myDouble3 operator+(myDouble3 const& obj) {
        myDouble3 result;
        result.x = x + obj.x;
        result.y = y + obj.y;
        result.z = z + obj.z;
        return result;
    }

    myDouble3 operator-(myDouble3 const& obj) {
        myDouble3 result;
        result.x = x - obj.x;
        result.y = y - obj.y;
        result.z = z - obj.z;
        return result;
    }

    myDouble3 operator*(double const& d) {
        myDouble3 result;
        result.x = x * d;
        result.y = y * d;
        result.z = z * d;
        return result;
    }
};

myDouble3 upper_phi(int i) {
    myDouble3 toReturn = myDouble3(
        cos((2 * M_PIf64x * i)/20),
        sin((2 * M_PIf64x * i)/20),
        1
    );
    return toReturn;
}

myDouble3 lower_phi(int i, int j) {
    myDouble3 phi_i = upper_phi(i);
    myDouble3 phi_j = upper_phi(j);

    return phi_i + ((phi_j - phi_i) * (1.0/4.0));
}

double findPairFrequency(char a, char b, string seq) {
    if (seq.size() < 2) return 0.0;
    int occurences = 0;
    for (int i = 0; i < seq.size()-1; i++) {
        if (seq[i] == a && seq[i+1] == b) {
            occurences++;
        }
    }
    return (double)occurences / (seq.size()-1);
}

myDouble3 psi(vector<myDouble3> *aggregator, string seq, string AAindex, int i) {
    const string aminoAcids = "ACDEFGHIKLMNPQRSTVWY";
    if (i==0) return myDouble3();
    

    myDouble3 term1 = psi(aggregator, seq, AAindex, i-1);
    myDouble3 term2 = upper_phi(AAindex.find_first_of(seq[i-1])+1);
    myDouble3 term3 = myDouble3();

    double sum = 0.0;

    for (int omega_1 = 0; omega_1 < aminoAcids.size(); omega_1++) {
        for (int omega_2 = 0; omega_2 < aminoAcids.size(); omega_2++) { 
            myDouble3 phi_result = lower_phi(AAindex.find_first_of(aminoAcids[omega_1])+1, AAindex.find_first_of(aminoAcids[omega_2])+1);
            double freq = findPairFrequency(aminoAcids[omega_1], aminoAcids[omega_2], seq.substr(0, i));
            term3 = term3 + phi_result * freq;
            sum += freq;
        }
    }

    cout << sum << endl;

    myDouble3 toReturn = term1 + term2 + term3;

    aggregator->push_back(toReturn);

    return toReturn;
}

vector<myDouble3> psi(string seq, string AAindex) {
    vector<myDouble3> toReturn;
    psi(&toReturn, seq, AAindex, seq.size());
    return toReturn;
}

int main(void) {

    vector<myDouble3> points = psi("AGYLLGKINLKALAALAKKILTYADFIASGRTGRRNAI", "DKERNHYGQPWTSVAICFML");

    for (myDouble3 x: points) {
        cout << x.toString() << "\n";
    }

    MatrixXd myMatrix(points.size(), points.size());

    for (int i = 0; i < myMatrix.rows(); i++) {
        for (int j = 0; j <= i; j++) {
            if (i == j) {
                myMatrix(i, j) = 0;
            } else {
                int val = i+j;
                myMatrix(i, j) = myMatrix(j, i) = val;
            }
        }
    }

    // cout << myMatrix << endl;

    cout << points.size() << endl;

}