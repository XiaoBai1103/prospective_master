'''
    btx
    23-6-28
    数据结构-图结构
'''
# Vertex包含了顶点信息，顶点连接边
class Vertex:
    def __init__(self,key):
        self.id = key
        self.connectedTo = {}
    # 添加相邻顶点及其权重
    def addNeighbor(self,nbr,weight=0):
        self.connectedTo[nbr] = weight
    # 返回顶点的字符串表示
    def __str__(self):
        return str(self.id) + 'connectedTo:' +str([x.id for x in self.connectedTo])
    # 返回相邻顶点的列表
    def getConnections(self):
        return self.connectedTo.keys()
    
    def getId(self):
        return self.id
    
    def getWeight(self,nbr):
        return self.connectedTo[nbr]
    
class Graph:
    def __init__(self):
        # 顶点列表
        self.vertList = {}
        # 顶点数量
        self.numVertices = 0
    # 向图中添加一个顶点
    def addVertex(self,key):
        self.numVertices = self.numVertices + 1
        newVertex = Vertex(key)
        self.vertList[key] = newVertex
        return newVertex
    # 添加边 f:起始顶点，t:终止顶点 weight：权重
    def addEdge(self,f,t,weight=0):
        if f not in self.vertList:
            return False
        if t not in self.vertList:
            return False
        self.vertList[f].addNeighbor(self.vertList[t],weight)
    # 根据给定的顶点ID返回对应的顶点对象
    def getVertex(self,n):
        if n in self.vertList:
            return self.vertList[n]
        else:
            return None
    # 迭代器
    def __iter__(self):
        return iter(self.vertList.values())
    # 检查图中是否包含指定的顶点标识符
    def __contains__(self,n):
        return n in self.vertList
    
if __name__ == "__main__":
    g = Graph()
    # 添加6个顶点
    for i in range(6):
        g.addVertex(i)
    # 添加边
    g.addEdge(0,1,5)
    g.addEdge(0,5,2)
    g.addEdge(1,2,4)
    g.addEdge(2,3,9)
    g.addEdge(3,4,7)
    g.addEdge(3,5,3)
    g.addEdge(4,0,1)
    g.addEdge(5,4,8)
    g.addEdge(5,2,1)
    for v in g:
        for w in v.getConnections():
            print('('+ str(v.getId()) +','+str(w.getId())+')')
        

        