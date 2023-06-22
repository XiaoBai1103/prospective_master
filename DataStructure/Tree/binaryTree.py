'''
    作者: btx
    日期: 23-6-21
    功能：二叉树
'''
class Node:
    def __init__(self,item):
        self.elem = item
        self.lchild = None
        self.rchild = None
class Tree:
    def __init__(self,root=None):
        self.root = root
#添加节点(优先添加到左结点)
    def add(self, elem):
        node = Node(elem)
        #如果树是空的，则对根节点赋值
        if self.root == None:
            self.root = node
        else:
            queue = []
            queue.append(self.root)
        #对已有的节点进行层次遍历
        while queue:
                #弹出队列的第一个元素
                cur = queue.pop(0)
                if cur.lchild == None:
                    cur.lchild = node
                    return
                elif cur.rchild == None:
                    cur.rchild = node
                    return
                else:
                #如果左右子树都不为空，加入队列继续判断
                    queue.append(cur.lchild)



if __name__ == '__main__':  
    tree = Tree(4)
    tree.add(3)

    
        