import pandas as pd
import tkinter as tk
import sys
import os

os.chdir(sys.path[0])
df = pd.read_csv("./data.csv",index_col=0,encoding='utf-8')
cor = pd.read_csv("./correct.csv",index_col = 0)

df0 = df[df["flag"]==0]
df1 = df[df["flag"] == 1]
df2 = df[df["flag"]==2]
df = df2._append(df1)
df = df._append(df0)
swp = df.copy()
flag = False
flag_1 = False
ans = ''
i=0

root = tk.Tk()
root.geometry('750x500+100+100')
#root.attributes("-alpha",0.9)
root.title('思政刷题器')
f_20 = ("宋体",20)
result = tk.StringVar();result.set("Welcome")
result1 = tk.StringVar();result1.set("")
result2 = tk.StringVar();result2.set("")
ra = tk.StringVar();ra.set("A.")
rb = tk.StringVar();rb.set("B.")
rc = tk.StringVar();rc.set("C.")
rd = tk.StringVar();rd.set("D.")
re = tk.StringVar();re.set("")

def lower(x):
    if x == 'A':
        return 'a'
    if x == 'B':
        return 'b'
    if x == 'C':
        return 'c'
    if x == 'D':
        return 'd'
    return x
def flag_1_Ture():
    global flag_1
    if flag_1 == False:
        if df.iloc[i,11] == 1 or df.iloc[i,11] == 0:
            flag_1 = True
def show():
    if len(df.iloc[i,1])<=24:
        result.set(str(df.iloc[i,1]))
        result1.set("")
        result2.set("")
    elif len(df.iloc[i,1])>24 and len(df.iloc[i,1])<=48:
        result.set(str(df.iloc[i,1])[:24])
        result1.set(str(df.iloc[i,1])[24:])
        result2.set("")
    else:
        result.set(str(df.iloc[i,1])[:24])
        result1.set(str(df.iloc[i,1])[24:48])
        result2.set(str(df.iloc[i,1])[48:])
    if df.iloc[i,0] == "判断题":
        ra.set("A.正确")
        rb.set("B.错误")
        rc.set("")
        rd.set("")
    else:
        ra.set("A."+df.iloc[i,7])
        rb.set("B."+df.iloc[i,8])
        rc.set("C."+df.iloc[i,9])
        rd.set("D."+df.iloc[i,10])

def bubble(x):
    a=[]
    st = ''
    for t in x:
        a.append(lower(t))
    for t in range(len(a)):
        for p in range(len(a)-t-1):
            if(a[p]>a[p+1]):
                tmp = a[p]
                a[p]=a[p+1]
                a[p+1]=tmp
    for t in range(len(a)):
        st+=str(a[t])
    return st
        
def showcorrect():#输出正确答案
    correct = bubble(df.iloc[i,2])
    if ('a' in correct)==False:
        ra.set("A."+df.iloc[i,7]+"  X")
    if ('b' in correct)==False:
        rb.set("B."+df.iloc[i,8]+"  X")
    if ('c' in correct)==False:
        rc.set("C."+df.iloc[i,9]+"  X")
    if ('d' in correct)==False:
        rd.set("D."+df.iloc[i,10]+" X")
    
def click(x):
    global flag,ans,cor
    if x == 'q':
        if(flag_1):
            cor=cor._append(df[df["flag"] == 2])
            print(cor)
            cor.to_csv("correct.csv")
        sys.exit()
    elif x == "confirm":
        flag = True
        print("flag_is_True")
    else:
        ans+=x
        print(ans)
    if x == "clr":
        ans = ''
    if x == 'n':
        ans = x
        re.set(df.iloc[i,0]+"我的答案:")
        check()
    else:
        re.set(df.iloc[i,0]+"我的答案:"+ans)
    if flag:
        check()

def check():
    global ans,flag,i
    correct = df.iloc[i,2]
    print("correct:"+correct)
    if (df.iloc[i,0] == "单选题" or df.iloc[i,0] == "判断题") and flag:
        if ans == chr(ord(correct)+32):
            ans = 'n'
        else:
            ans = ''
            flag = False
            df.iloc[i,11]=2
            showcorrect()
    if df.iloc[i,0] == "多选题" and flag:
        if bubble(ans)==bubble(correct):
            ans = 'n'
        else:
            ans = ''
            flag = False
            df.iloc[i,11]=2
            showcorrect()
    if ans == 'n':  #下一题
        ans = ''
        flag = False
        print("flag_is_False")
        i+=1
        re.set(df.iloc[i,0]+"我的答案:")
        df.to_csv("data.csv")
        df.iloc[i,11]=0
        flag_1_Ture()
        show()
        
def main():
    tk.Label(root,
             textvariable = result,
             font = f_20,
             height = 2,
             ).grid(row= 1 ,column = 1,columnspan=4)
    
    tk.Label(root,
             textvariable = result1,
             font = f_20,
             height = 2,
             ).grid(row= 2 ,column = 1,columnspan=4)
    
    tk.Label(root,
             textvariable = result2,
             font = f_20,
             height = 2,
             ).grid(row= 3 ,column = 1,columnspan=4)
    
    tk.Label(root,
             textvariable = ra,
             font = f_20,
             height = 1,
             justify = tk.LEFT,
             anchor=tk.NW
             ).grid(row= 8 ,column = 1,columnspan=4)
    
    tk.Label(root,
             textvariable = rb,
             font = f_20,
             height = 1
             ).grid(row= 9 ,column = 1,columnspan=4)
    
    tk.Label(root,
             textvariable = rc,
             font = f_20,
             height = 1
             ).grid(row= 10 ,column = 1,columnspan=4)
    
    tk.Label(root,
             textvariable = rd,
             font = f_20,
             height = 1
             ).grid(row= 11 ,column = 1,columnspan=4)
    tk.Label(root,
             textvariable = re,
             font = f_20,
             height = 1
             ).grid(row= 14 ,column = 1,columnspan=4)
    
    bta = tk.Button(root , text = "A", width = 10 , font = f_20 , relief=tk.FLAT,bg = "#b1b2b2")
    bta.grid(row = 12,column=1,padx=8,pady=4)
    btb = tk.Button(root , text = "B", width = 10 , font = f_20 , relief=tk.FLAT, bg = "#b1b2b2")
    btb.grid(row = 12,column=2,padx=8,pady=4)
    btc = tk.Button(root , text = "C", width = 10 , font = f_20 , relief=tk.FLAT,bg = "#b1b2b2")
    btc.grid(row = 12,column=3,padx=8,pady=4)
    btd = tk.Button(root , text = "D", width = 10 , font = f_20 , relief=tk.FLAT,bg = "#b1b2b2")
    btd.grid(row = 12,column=4,padx=8,pady=4)
    nxt = tk.Button(root , text = "跳过", width = 10 , font = f_20 , relief=tk.FLAT,bg = "#b1b2b2")
    nxt.grid(row = 13,column=3,padx=8,pady=4)
    clr = tk.Button(root , text = "清除", width = 10 , font = f_20 , relief=tk.FLAT,bg = "#b1b2b2")
    clr.grid(row = 13,column=2,padx=8,pady=4)
    qut = tk.Button(root , text = "退出", width = 10 , font = f_20 , relief=tk.FLAT,bg = "#b1b2b2")
    qut.grid(row = 13,column=1,padx=8,pady=4)
    con = tk.Button(root , text = "确定", width = 10 , font = f_20 , relief=tk.FLAT,bg = "#b1b2b2")
    con.grid(row = 13,column=4,padx=8,pady=4)
    
    bta.config(command = lambda: click("a"))
    btb.config(command = lambda: click("b"))
    btc.config(command = lambda: click("c"))
    btd.config(command = lambda: click("d"))
    nxt.config(command = lambda: click("n"))
    qut.config(command = lambda: click("q"))
    con.config(command = lambda: click("confirm"))
    clr.config(command = lambda: click("clr"))

    flag_1_Ture()
    show()
    root.mainloop()
    
if __name__ == '__main__':
    main()
