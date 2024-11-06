# Aryan's Code

## Understanding the Problem:
We want to predict whether a protein sequence can affect DNA, RNA, DRNA, or nonDRNA.

## Understanding the Data:
The data consists of 8795 objects, with each object consisting of a protein sequence and a label indicating whether it affects DNA, RNA, DRNA, or nonDRNA.

## Preprocess the Raw Data:
The raw data was originally in `.txt` format and was converted to `.csv` for easier use. During this process, some values in the data were identified as invalid and were removed. These invalid values include:

- **Values to remove:** `{'B', 'J', 'O', 'U', 'X', 'Z'}`
- **Valid amino acids in the data:** `{'A', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'K', 'L', 'M', 'N', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'}`

After removing the invalid amino acids, the following were excluded:

- **Amino acids removed:** `{'A', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'K', 'L', 'M', 'N', 'P', 'Q', 'R', 'S', 'T', 'V', 'W', 'Y'}`

### Create a Fasta File:
A Fasta file was created for use with feature creation software, with labels for whether the protein affects DNA, RNA, DRNA, or nonDRNA as 0, 1, 2, and 3 respectively.

## Feature Creation:
Using **iLearnPlus**, features were created using the following methods:
- **AAC (Amino Acid Composition)**
- **GAAC (Group Amino Acid Composition)**
- **CTDC (Composition of Trigrams of Dipeptides)**

## Full Dataset Merging:
The final dataset was obtained by merging the relevant data from different sources.

## Run Model:
We ran **Naive Bayes** and **Decision Tree** models on the data.

## Evaluation:
The evaluation results were written into `.txt` files, with each file containing the performance metrics for each model.
