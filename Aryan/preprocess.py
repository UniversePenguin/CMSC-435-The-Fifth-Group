import pandas as pd
import numpy as np

#Grab values from csv and put them into a numpy array
df = pd.read_csv('sequences_training.csv')
change = df.to_numpy()

"""Understanding the data
#Create set of classes
class_set = set(change[1] for change in change)

#Create set of amino acids
protien_set = set(''.join({change[0] for change in change}))

#Create set of amino acids after removal
aa_remove = {'B','J','O','U','X','Z'}
protien_set = protien_set.difference(aa_remove)

#Print Results
print(sorted(list(protien_set)))
print(class_set)
"""
#Grab Total num of amino acids
print(len(change))

#Deletion Set
aa_remove = {'B','J','O','U','X','Z'}

new_change = np.array([change for change in change if not any(char in aa_remove for char in change[0])])

#New length
print(len(new_change))

df_c = pd.DataFrame(new_change).reset_index(drop=True)
df_c.to_csv('sequences_training_clean.csv', header = False)