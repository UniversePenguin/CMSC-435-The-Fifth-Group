import pandas as pd
import glob

#Grab filepath
folder = 'UnmergedData/*.tsv1'

#First Dataset in our merge
mdf = pd.read_csv((glob.glob(folder))[0], sep='\t')

#Go through filepath and add to merged Dataset
for i, file in enumerate(glob.glob(folder)):
    if i == 0:
        continue
    df = pd.read_csv(file, sep='\t')
    mdf = pd.merge(mdf,df, on=['SampleName', 'label'], how='left')

#Reconvert class types to strings
type_mapping = {
    0 : "DNA",
    1 : "RNA",
    2 : "DRNA",
    3 : "nonDRNA"
}
mdf['label'] = mdf['label'].astype(int).map(type_mapping)

#Print to CSV
mdf.to_csv('Aryan_Dataset.csv',index=False)
