import tkinter as tk

val = "0" #状态机状态
time = 5.9  #定时炸弹时间
tk_tmp = "" #输入框

def init(): # 0
    global val,tk_tmp,time
    LCD1602_1.set("请输入你的绑匪编号：")
    LCD1602_2.set("*")
    val += "1" #切换到下一个状态
    tk_tmp = ""
    time = 5.9
    
def time_bomb(): # 1    定时炸弹
    global time
    if int(time)>0:
        LCD1602_1.set("倒计时")
        LCD1602_2.set(str(int(time)))
        time -= 0.1
    if int(time) == 0:
        LCD1602_1.set("炸弹爆炸了！！！")
        LCD1602_2.set("T win the game!")

def login():    # 01
    pass

def check_login():  # 010
    global tk_tmp,val
    if tk_tmp == "9527":
        tk_tmp = ""
        val+="1"
    else:
        tk_tmp = ""
        val = val[:-1]+"1"  #011
        
def bomb(): #011
    LCD1602_1.set("炸弹爆炸了！！！")
    LCD1602_2.set("你不是我们的人！")
    
def passwd_init():   #0101
    global val
    LCD1602_1.set("请输入密码")
    LCD1602_2.set("*")
    val = "0111"
    
def passwd():   #0111
    pass

def passwd_check(): #01110
    global val,tk_tmp
    if tk_tmp == "7355608":
        val = "1"
    else:
        val = "0101"
    tk_tmp = ""
    
def main():
    global val
    if val == "0":
        init()  #初始化
        
    if val == "1":
        time_bomb() #定时炸弹启动
    
    elif val == "01":
        login() #登录
        
    elif val == "010":
        check_login()   #检查登录
    
    elif val == "011":
        bomb()  #炸弹爆炸
        
    elif val == "0101":
        passwd_init()   #密码框初始化
        
    elif val == "0111":
        passwd()    #输入密码
        
    elif val == "01110":
        passwd_check()  #检查密码
    
    State.set(val)
    root.after(100, main)  #定时器中断，每100ms调用一次

if __name__ == '__main__':
    def click(num):
        global val,LCD1602_2
        if num == "confirm":
            val += "0"
        elif num == "reset":
            val = "0"
        else:
            global tk_tmp
            tk_tmp += str(num)
            LCD1602_2.set(tk_tmp)
        
    root = tk.Tk()
    root.geometry('750x500+100+100')
    root.title('csgo炸弹')
    f_20 = ("宋体",20)
    LCD1602_1 = tk.StringVar()
    LCD1602_2 = tk.StringVar()
    State = tk.StringVar();State.set(val)
    tk.Label(root,
             textvariable = LCD1602_1,
             font = f_20,
             height = 4,
             ).grid(row= 1 ,column = 1,columnspan=4)
    
    tk.Label(root,
             textvariable = LCD1602_2,
             font = f_20,
             height = 4,
             ).grid(row= 2 ,column = 1,columnspan=4)
    
    tk.Label(root,
             textvariable = State,
             font = f_20,
             height = 1,
            ).grid(row = 6,column = 1,columnspan = 2)
    
    one = tk.Button(root , text = "1", width = 10 , font = f_20 , relief=tk.FLAT,bg = "#b1b2b2")
    one.grid(row = 5,column=1,padx=8,pady=4)
    
    two = tk.Button(root , text = "2", width = 10 , font = f_20 , relief=tk.FLAT,bg = "#b1b2b2")
    two.grid(row = 5,column=2,padx=8,pady=4)
    
    three = tk.Button(root , text = "3", width = 10 , font = f_20 , relief=tk.FLAT,bg = "#b1b2b2")
    three.grid(row = 5,column=3,padx=8,pady=4)
    
    four = tk.Button(root , text = "4", width = 10 , font = f_20 , relief=tk.FLAT,bg = "#b1b2b2")
    four.grid(row = 4,column=1,padx=8,pady=4)
    
    five = tk.Button(root , text = "5", width = 10 , font = f_20 , relief=tk.FLAT,bg = "#b1b2b2")
    five.grid(row = 4,column=2,padx=8,pady=4)
    
    six = tk.Button(root , text = "6", width = 10 , font = f_20 , relief=tk.FLAT,bg = "#b1b2b2")
    six.grid(row = 4,column=3,padx=8,pady=4)
    
    seven = tk.Button(root , text = "7", width = 10 , font = f_20 , relief=tk.FLAT,bg = "#b1b2b2")
    seven.grid(row = 3,column=1,padx=8,pady=4)
    
    eight = tk.Button(root , text = "8", width = 10 , font = f_20 , relief=tk.FLAT,bg = "#b1b2b2")
    eight.grid(row = 3,column=2,padx=8,pady=4)
    
    nine = tk.Button(root , text = "9", width = 10 , font = f_20 , relief=tk.FLAT,bg = "#b1b2b2")
    nine.grid(row = 3,column=3,padx=8,pady=4)
    
    zero = tk.Button(root , text = "0", width = 10 , font = f_20 , relief=tk.FLAT,bg = "#b1b2b2")
    zero.grid(row = 3,column=4,padx=8,pady=4)
    
    reset = tk.Button(root , text = "重置", width = 10 , font = f_20 , relief=tk.FLAT,bg = "#b1b2b2")
    reset.grid(row = 4,column=4,padx=8,pady=4)
    
    confirm = tk.Button(root , text = "确定", width = 10 , font = f_20 , relief=tk.FLAT,bg = "#b1b2b2")
    confirm.grid(row = 5,column=4,padx=8,pady=4)
    
    one.config(command = lambda: click("1"))
    two.config(command = lambda: click("2"))
    three.config(command = lambda: click("3"))
    four.config(command = lambda: click("4"))
    five.config(command = lambda: click("5"))
    six.config(command = lambda: click("6"))
    seven.config(command = lambda: click("7"))
    eight.config(command = lambda: click("8"))
    nine.config(command = lambda: click("9"))
    zero.config(command = lambda: click("0"))
    reset.config(command = lambda: click("reset"))
    confirm.config(command = lambda: click("confirm"))
    
    root.after(100, main)
    root.mainloop()
    