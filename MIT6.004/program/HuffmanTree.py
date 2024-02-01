import copy
class HuffmanTree(object):
    def __init__(self,tree):
        self.tree = tree
        self.min1 = -1
        self.min2 = -1
        self.Node = []
        self.weight = -1

    def MakeNode(self):     #将权值最小的两个数据/节点生成子树(min1,min2)
        self.Compare()
        print(self.min2,self.tree)
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
        max = 0
        for i in range (len(self.tree)):        #防止min1,min2一开始取到最小值
            if max < self.tree[i][1]:
                self.min1 = self.min2 = i
                max = i
        for i in range(len(self.tree)):
            if self.tree[i][1] <= self.tree[self.min1][1]:
                self.min1 = i
            if ((self.tree[i][1] < self.tree[self.min2][1] and self.tree[i][1] > self.tree[self.min1][1]) #tree[i]的权重大于min1但小于min2
                    or (self.tree[i][1] == self.tree[self.min2][1] and i != self.min1)):    ##min1的权重==min2的权重,但min1 != min2
                self.min2 = i

    def pre(self):
        while len(self.tree) != 1:
            self.MakeNode()
        print(self.tree)
        

def main():
    tree = [['a',3],['b',5],['c',7],['d',8],['e',6],['f',4]]
    MakeTree = HuffmanTree(tree)
    MakeTree.pre()

if __name__ == '__main__':
    main()