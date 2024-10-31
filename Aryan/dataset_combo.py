import pandas as pd
import numpy as np

#Read CSV
df1 = pd.read_csv('UnmergedData/AA_data.csv')
df2 = pd.read_csv('UnmergedData/Composition.csv')
df3 = pd.read_csv('UnmergedData/Grouped_AA_Comp.csv')

#Change to numpy for easier access
np1 = df1.to_numpy()
np2 = df2.to_numpy()
np3 = df3.to_numpy()

#Merge features
merged = np.concatenate((np1, np2[:, 2:], np3[:, 2:]), axis=1)

#Reconvert class types to strings and print csv
type_mapping = {
    0 : "DNA",
    1 : "RNA",
    2 : "DRNA",
    3 : "nonDRNA"
}

mdf = pd.DataFrame(merged)
mdf[0] = mdf[0].astype(int).map(type_mapping)
mdf.to_csv('Aryan_Dataset.csv',header=False)