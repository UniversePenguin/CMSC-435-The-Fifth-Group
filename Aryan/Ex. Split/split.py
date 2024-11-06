import pandas as pd

#Grab main csv
main_df = pd.read_csv('Aryan_Dataset.csv')

#Create df for each class
DNA_df = main_df.copy()
RNA_df = main_df.copy()
DRNA_df = main_df.copy()
nonDRNA_df = main_df.copy()

#Create df where each class is positive and the rest is negative
DNA_df['label'] = main_df['label'].apply(lambda x: 'DNA' if x == 'DNA' else 'negative')
RNA_df['label'] = main_df['label'].apply(lambda x: 'RNA' if x == 'RNA' else 'negative')
DRNA_df['label'] = main_df['label'].apply(lambda x: 'DRNA' if x == 'DRNA' else 'negative')
nonDRNA_df['label'] = main_df['label'].apply(lambda x: 'nonDRNA' if x == 'nonDRNA' else 'negative')

#Create csvs     
DNA_df.to_csv('split/Aryan_Dataset_DNA.csv', index=False)
RNA_df.to_csv('split/Aryan_Dataset_RNA.csv', index=False)
DRNA_df.to_csv('split/Aryan_Dataset_DRNA.csv', index=False)
nonDRNA_df.to_csv('split/Aryan_Dataset_nonDRNA.csv', index=False)