import copy
class HuffmanTree(object):
    def __init__(self,tree):
        self.tree = tree
        self.origin = tree
        self.dict = {}
        self.min1 = -1
        self.min2 = -1
        self.Node = []
        self.weight = -1

    def MakeNode(self):     #将权值最小的两个数据/节点生成子树(min1,min2)
        self.Compare()
        #print(self.tree)
        self.weight = self.tree[self.min1][1] + self.tree[self.min2][1]
        self.Node = [ self.tree[self.min1][0],self.tree[self.min2][0] ]

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
    
    def Encode(self,tree,encoding):
        #left
        if type(tree) != list:
            self.dict[tree] = encoding
        else:
            self.Encode(tree[0],encoding+'0')
            self.Encode(tree[1],encoding+'1')

    def Show(self):
        while len(self.tree) != 1:
            self.MakeNode()
        print("霍夫曼树:  ",self.tree)
        self.Encode(self.tree[0][0],"")
        #print(self.dict)
        print("霍夫曼编码: ")
        for key in self.origin:
            print(key[0],self.dict[key[0]])
        

def main():
    tree = [['a',3],['b',5],['c',7],['d',8],['e',6],['f',4]]
    MakeTree = HuffmanTree(tree)
    MakeTree.Show()

if __name__ == '__main__':
    main()