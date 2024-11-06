import pandas as pd

#Grab csv
df = pd.read_csv('sequences_training_clean.csv')

#Convert String types to ints for fasta creation
type_mapping = {
    "DNA": 0,
    "RNA": 1,
    "DRNA": 2,
    "nonDRNA": 3
}

#Create fasta
with open('sequences_training_clean.fasta', 'w') as f:
    for index, row in df.iterrows():
        f.write(f">{row[0]}|{type_mapping.get(row[2])}\n")
        for i in range(0, len(row[1]), 80):
            f.write(f"{row[1][i:i+80]}\n")

print("Fasta created")