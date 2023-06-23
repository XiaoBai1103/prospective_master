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
    #root必须传入节点，而不是数值
    def __init__(self,root=None):
        self.root = root
    #添加节点
    def add(self, elem):
        node = Node(elem)
        #如果树是空的，则对根节点赋值
        if self.root == None:
            self.root = node
            return
        queue = [self.root]
        #对已有的节点进行层次遍历
        while queue:
                #弹出队列的第一个元素
                cur = queue.pop(0)
                if cur.lchild == None:
                    cur.lchild = node
                    return
                else:
                    queue.append(cur.lchild)
                if cur.rchild == None:
                    cur.rchild = node
                    return
                else:
                    queue.append(cur.rchild)
                    

    #广度优先遍历
    def breadth(self):
        if self.root == None:
            return
        queue = [self.root]
        while queue:
            cur = queue.pop(0)
            print(cur.elem,end=' ')
            if cur.lchild != None:
                queue.append(cur.lchild)
            if cur.rchild != None:
                queue.append(cur.rchild)
    #深度优先遍历-先序遍历（根左右）
    def preorder(self,node):
        if node == None:
            return
        print(node.elem,end=' ')
        self.preorder(node.lchild)
        self.preorder(node.rchild)
    #深度优先遍历-中序遍历（左根右)
    def inorder(self, node):
        if node == None:
            return
        self.inorder(node.lchild)
        print(node.elem,end=' ')
        self.inorder(node.rchild)
    #深度优先遍历-后 序遍历（左右根）
    def postorder(self, node):
        if node == None:
            return
        self.postorder(node.lchild)
        self.postorder(node.rchild)
        print(node.elem,end=' ')
if __name__ == '__main__':  
    tree = Tree()
    tree.add(1)
    tree.add(2)
    tree.add(3)
    tree.add(4)
    tree.add(5)
    tree.add(6)
 

    '''
                1
            2       3
         4     5 6      
    '''
    print("广度优先遍历:")
    tree.breadth()
    print()
    print("先序遍历:")
    tree.preorder(tree.root)
    print()
    print("中序遍历:")
    tree.inorder(tree.root)
    print()
    print("后序遍历:")
    tree.postorder(tree.root)