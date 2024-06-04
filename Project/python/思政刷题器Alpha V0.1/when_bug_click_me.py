import pandas as pd
df=pd.read_csv("data.csv",index_col=0)
print (df.head(5))
for i in range(len(df)):
    a=""
    if "A" in str(df.iloc[i,2]):
        a+='A'
    if "B" in str(df.iloc[i,2]):
        a+='B'
    if 'C' in str(df.iloc[i,2]):
        a+='C'
    if 'D' in str(df.iloc[i,2]):
        a+='D'
    df.iloc[i,2]=a
df.to_csv("data.csv")
