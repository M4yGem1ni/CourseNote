import copy
Binary_Tree1 = ""   #前序遍历
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
            global Binary_Tree1
            self.dict[tree] = encoding
            Binary_Tree1 += str(tree)    #对霍夫曼二叉树进行前序遍历
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


def main():
    #tree = [['a',3],['b',5],['c',7],['d',8],['e',6],['f',4]]    #(字符,权重)
    string = input("请输入需要哈夫曼编码的字符串: ")
    MakeTree = HuffmanTree(string)
    encodings = MakeTree.Show()
    string = input("请输入需要解码的二进制码: ")
    DecodeTree = Decode(encodings,string)
    print("解码结果:",DecodeTree.decoding())

if __name__ == '__main__':
    main()