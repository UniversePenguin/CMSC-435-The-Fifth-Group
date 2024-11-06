import pandas as pd
import numpy as np
import sys

def results(csv):
    #import the data and convert to array for easy use
    df = pd.read_csv(f'{csv}.csv')
    per = df.to_numpy().tolist()

    #Make an array of important data
    imp_per = []
    for i in range(len(per)-1):
        imp_per.append(per[i][1:5])

    #Lists for Sensitivity, Specificity, Accuracy, and MCC
    Sensitivity = []
    Specificity = []
    Accuracy = []
    MCC = []

    #Get All FN,FP,TN,FN
    for i in range (len(imp_per)):
        #TP is value at diagonal
        TP = int(imp_per[i][i])
        
        #FP is sum of the row
        FP = sum(int(x) for y, x in enumerate(imp_per[i]) if i != y)

        #FN is sum of the column and TN is everything else
        FN = 0
        TN = 0
        for j in range(len(imp_per)):
            if i == j:
                continue
            FN += int(imp_per[j][i])

            #Add everything else
            for k in range(len(imp_per[j])):
                if j != i and k != i:
                    TN += int(imp_per[j][k])

        #Sensitivity is TP/(TP+FN)
        Sensitivity.append(round((TP/(TP+FN))*100,1))

        #Specificity is TN/(TN+FP)
        Specificity.append(round((TN/(TN+FP))*100,1))

        #Accuracy is (TP+TN)/(TP+TN+FP+FN)
        Accuracy.append(round(((TP+TN)/(TP+TN+FP+FN)*100),1))

        #MCC is ((TP*TN)-(FP*FN))/sqrt((TP+FP)*(TP+FN)*(TN+FP)*(TN+FN))
        MCC.append(round((((TP*TN)-(FP*FN))/(np.sqrt(((TP+FP)*(TP+FN)*(TN+FP)*(TN+FN))+1e-10))),3))

    #Print Results
    result = (f"""
    DNA: 
        Sensitivity: {Sensitivity[2]}
        Specificity: {Specificity[2]}
        Accuracy: {Accuracy[2]}
        MCC: {MCC[2]}
        
    RNA: 
        Sensitivity: {Sensitivity[1]}    
        Specificity: {Specificity[1]}
        Accuracy: {Accuracy[1]}
        MCC: {MCC[1]}
        
    DRNA: 
        Sensitivity: {Sensitivity[3]}
        Specificity: {Specificity[3]}
        Accuracy: {Accuracy[3]}
        MCC: {MCC[3]}
        
    nonDRNA: 
        Sensitivity: {Sensitivity[0]}
        Specificity: {Specificity[0]}
        Accuracy: {Accuracy[0]}
        MCC: {MCC[0]}
        
    averageMCC: {round(sum(MCC)/len(MCC),3)}
    accuracy4labels {round(sum(Accuracy)/len(Accuracy),1)}
    """)

    with open(f'{csv}.txt', 'w') as f:
        f.write(result)

def main():
    args = sys.argv[1]
    results(args)
if __name__ == "__main__":
    main()