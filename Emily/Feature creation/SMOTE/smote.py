import imblearn
import pandas as pd

FILENAME = "MinMax_normal_data_Emily.csv"

data = pd.read_csv(FILENAME)

smote = imblearn.over_sampling.SMOTE(sampling_strategy='all')

x,y= smote.fit_resample(data.iloc[:,1:], data.iloc[:,0])

newdata=y.to_frame().join(x)

print(newdata)

newdata.to_csv(f'SMOTE_{FILENAME}')

print("Old Counts:\n", data.iloc[:,0].value_counts())
print("New Counts:\n", newdata.iloc[:,0].value_counts())