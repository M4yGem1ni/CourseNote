import copy
import turtle
import math     #计算绘制角度

LENGTH = 150     #设置二叉树最小边长度
CIRCLE = 20      #设置圆框的半径

class HuffmanTree(object):
    def __init__(self,string):
        self.string = string    #传入要处理的字符串
        self.tree = {}    #创建霍夫曼树
        self.origin = []  #保存原始数据
        self.dict = {}      #创建编码词典
        self.min1 = -1      #设置最小权重
        self.min2 = -1      #设置次小权重
        self.Node = []      #创建子树节点
        self.weight = -1    #创建权重数据

    def Translate(self):
        tmp = list(self.string)
        for part in tmp:
            if part in self.tree:
                self.tree[part] += 1
            else:
                self.tree[part] = 1
        tmp = []
        for part in self.tree:
            tmp.append([part , self.tree[part]])
        for i in range(len(tmp) - 1):
            for j in range(len(tmp)-1-i):
                if tmp[j][1] < tmp[j+1][1]:
                    temp = tmp[j]
                    tmp[j] = tmp[j+1]
                    tmp[j+1] =temp
        self.tree = self.origin = []
        self.tree = copy.deepcopy(tmp)
        self.origin = copy.deepcopy(tmp)


    def MakeNode(self):     #将权值最小的两个数据/节点生成子树(min1,min2)
        self.Compare()      #获取两个最小权值的位置
        #print(self.tree)
        self.weight = self.tree[self.min1][1] + self.tree[self.min2][1]     #计算子节点的权重
        self.Node = [ self.tree[self.min1][0],self.tree[self.min2][0] ]     #生成子节点

        tmp = []        #暂时存储
        for i in range(len(self.tree)):  #删除最小的两个数据/节点
            if i==self.min1 or i==self.min2:
                continue
            else:
                tmp.append(self.tree[i])
        tmp.append([self.Node,self.weight])   #将节点接到树上
        self.tree = copy.deepcopy(tmp)   #保存更改


    def Compare(self):
        tmp = 65535
        for i in range (len(self.tree)):        #min1取到最小值
            if  self.tree[i][1] < tmp:
                self.min1 = i
                tmp = self.tree[i][1]
        tmp = 65535
        for i in range (len(self.tree)):        #min2取到次小值
            if self.tree[i][1] < tmp and i != self.min1:
                self.min2 = i
                tmp = self.tree[i][1]
    
    def Encode(self,tree,encoding):     #递归方法对霍夫曼树进行编码
        if type(tree) != list:          #找到数据后对其进行编码
            self.dict[tree] = encoding
        else:                           #没找到继续向下递归
            self.Encode(tree[0],encoding+'0')
            self.Encode(tree[1],encoding+'1')

    def Show(self):
        self.Translate()
        while len(self.tree) != 1:
            self.MakeNode()
        print("霍夫曼树:  ",self.tree[0][0])
        self.Encode(self.tree[0][0],"") #去掉权重以后对其进行编码
        #print(self.dict)
        print("霍夫曼编码: ")
        for key in self.origin:
            print(key[0],self.dict[key[0]])     #将编码按顺序打印下来
        return self.dict

class Decode(object):
    def __init__(self,encoding,string):
        self.encoding = encoding
        self.string = string
        self.output = ""

    def dict_TurnDown(self):    #将字典颠倒{"a":'1000',"b":'500'} --> {'1000':"a",'500':"b"}
        tmp = {}
        for part in self.encoding:
            tmp[self.encoding[part]] = part
        self.encoding = copy.deepcopy(tmp)

    def decoding(self):
        self.dict_TurnDown()
        tmp = ""
        for i in range(len(self.string)):
            tmp += self.string[i]
            if tmp in self.encoding:
                self.output += self.encoding[tmp]
                tmp = ""
        if tmp != "":
            print("Decode Error!")
            exit(0)
        return self.output
    

class Turtle(object):   #适用于所有二叉树
    def __init__(self,encoding):
        self.depth = -1     #深度从0开始计算
        self.dict = encoding    #字典
        self.tree = []
        self.angle = []
        self.lenth = []
    
    def Depth(self):
        for part in self.dict:
            if len(self.dict[part]) > self.depth:
                self.depth = len(self.dict[part])
        for i in range(self.depth):     #创建空的二叉树
            self.tree.append(['nul' for j in range(int(math.pow(2,i+1)))])

    def AngleLength(self):
        for i in range(self.depth-1 , -1 , -1):
            alpha = math.atan2(LENGTH*math.pow(2,i)/2 , LENGTH)     #alpha为弧度制
            self.lenth.append(int(LENGTH / math.cos(alpha)))
            alpha = int(alpha / math.pi * 180 )       #转化为整型角度制
            self.angle.append(alpha)        #存储角度

    def FindNode(self,part,encoding):
        last = 0
        for i in range(len(encoding)):
            if len(encoding) == 1:
                self.tree[i][int(encoding[0])+last*2] = part
                encoding = ''
            if len(encoding) > 1:
                self.tree[i][int(encoding[0])+last*2] = 'val'
                last = int(encoding[0])+last*2
                encoding = encoding[1:]

    def MakeTree(self):
        for part in self.dict:
            self.FindNode(part,self.dict[part])

    def TurtleGo(self):
        def AdvanceSetting():
            turtle.setup(800,800,0,0)
            turtle.speed(10)
            turtle.hideturtle()
            turtle.penup()         #抬起画笔
            turtle.goto(0,350)
            turtle.pendown()       #画笔落下
            #画出第一个圆形
            x = turtle.xcor()
            y = turtle.ycor()
            turtle.penup()         #抬起画笔
            turtle.seth(270)
            turtle.fd(CIRCLE)
            turtle.seth(0)
            turtle.pendown()       #画笔落下
            turtle.circle(CIRCLE)
            turtle.penup()         #抬起画笔
            turtle.setx(x)
            turtle.sety(y)
            turtle.pendown()       #画笔落下
        def TurtleStep(length,angle,direc,val):     #画出去
            if val == 'nul':
                return 'nul'
            if direc == "l":
                direc = -1
            elif direc == "r":
                direc = 1
            turtle.seth(270+angle*direc)
            turtle.penup()         #抬起画笔
            turtle.fd(CIRCLE)
            turtle.pendown()       #画笔落下
            turtle.fd(length)
            turtle.penup()         #抬起画笔
            turtle.fd(CIRCLE)
            x = turtle.xcor()
            y = turtle.ycor()
            turtle.seth(270)
            turtle.fd(CIRCLE)
            turtle.seth(0)
            turtle.pendown()       #画笔落下
            turtle.circle(CIRCLE)
            turtle.penup()         #抬起画笔
            if val != 'val' :
                val = '\"'+ val + '\"'
                turtle.seth(270)
                turtle.fd(CIRCLE)
                turtle.seth(0)
                for val0 in val:
                    turtle.write(val0,font=("宋体",int(CIRCLE),'normal'))
                    turtle.fd(CIRCLE/2)
            turtle.setx(x)
            turtle.sety(y)



        def Recursion(depth,last):        #递归返回
            if depth == self.depth:
                return "depth"
            x = turtle.xcor()
            y = turtle.ycor()
            TurtleStep(self.lenth[depth],self.angle[depth],'l',self.tree[depth][2*last+0])
            Recursion(depth+1,2*last+0)
            turtle.setx(x)
            turtle.sety(y)
            TurtleStep(self.lenth[depth],self.angle[depth],'r',self.tree[depth][2*last+1])
            Recursion(depth+1,2*last+1)
            turtle.setx(x)
            turtle.sety(y)

        AdvanceSetting()
        Recursion(0,0)
        turtle.done()
        

        

    def DrawTree(self):
        self.Depth()
        self.AngleLength()
        self.MakeTree()
        #print("重新编码得到的二叉树: ",self.tree)
        #print("画线长度: ",self.lenth)
        #print("线的角度: ",self.angle)
        self.TurtleGo()

def main():
    #tree = [['a',3],['b',5],['c',7],['d',8],['e',6],['f',4]]    #(字符,权重)
    string = input("请输入需要哈夫曼编码的字符串: ")
    MakeTree = HuffmanTree(string)
    encodings = MakeTree.Show()
    string = input("请输入需要解码的二进制码: ")
    DecodeTree = Decode(encodings,string)
    print("解码结果:",DecodeTree.decoding())
    Draw = Turtle(encodings)
    Draw.DrawTree()

if __name__ == '__main__':
    main()