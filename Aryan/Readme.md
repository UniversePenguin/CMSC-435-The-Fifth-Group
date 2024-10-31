# Aryan's Code
## Understanding the problem: 
  We want to predict whether a protein sequence can affect DNA, RNA, DRNA, or nonDRNA.

## Understanding the data: 
  The data consists of 8795 objects with each object consisting of a protein sequence and whether it affects DNA, RNA, DRNA, or nonDRNA.

## Preprocess the raw data: 
  Data is in txt changed to csv for easier use
    There may be some values in the data that should not be there:
    Values that should not be in data:{‘B’, ’J’, ’O’, ’U’, ’X’, ’Z’}
    Values that are in the data {'A', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'K', 'L', 'M', 'N', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'}
    After Removal of amino acids {'A', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'K', 'L', 'M', 'N', 'P', 'Q', 'R', 'S', 'T', 'V', 'W', 'Y'}
  Create a Fasta file for use with feature creation software with whether or not it affects the DNA, RNA, DRNA, or nonDRNA as 0, 1, 2, and 3 respectively
## Create Features:
  Using iLearnPlus create features
  Used feature creation AAC, GAAC, CTDC

## Full Dataset Merging:
  Merged Dataset for final
