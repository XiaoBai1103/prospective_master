'''
    作者: btx
    日期: 23-7-4
    功能：查找与排序
'''
# 顺序查找
def linearSearch(li,val):
    for index,v in enumerate(li):
        if v == val:
            return index 
    return None

# 二分查找
def binarySearch(li,val):
    left = 0
    right = len(li) - 1
    # 候选区有值
    while left <= right:
        mid = (left +right) // 2
        if li[mid] == val:
            return mid
        # 待查找的值在mid左侧
        elif li[mid] > val:
            right = mid - 1
        # 待查找的值在mid右侧
        else:
            left = mid +1
    return None

# 冒泡排序
def bubbleSort(li):
    for i in range(len(li)-1):
        exchange = False
        for j in range(len(li)-i-1):
            if li[j] > li[j+1]:
                li[j], li[j+1] = li[j+1], li[j]
                exchange = True
            print(li)
        # 是否完成排序判断
        if not exchange:
            return True
# 简单选择排序
def selectSortSimple(li):
    liNew = []
    for i in range(len(li)):
        minVal = min(li)
        liNew.append(minVal)
        li.remove(minVal)
        print("原列表:",end='')
        print(li,end='')
        print("新列表:",end='')
        print(liNew)
    return liNew

# 选择排序
def selectSort(li):
    for i in range(len(li)-1):
        minLoc = i
        for j in range(i+1,len(li)):
            if li[j] < li[minLoc]:
                minLoc = j
        li[i],li[minLoc] = li[minLoc],li[i]
        print(li)

# 插入排序
def insertSort(li):
    for i in range(1,len(li)):
        # 当前数
        temp = li[i]
        # 有序区最后一个数
        j = i - 1
        # 遍历有序区找到插入位置
        while li[j] > temp and j >= 0:
            # 数据右移
            li[j+1] = li[j]
            j -= 1
        # 插入当前数
        li[j+1] = temp
        print(li)



if __name__ == '__main__':
    li0 = [1,2,3,4,5,6,7,8,9]
    print("待查找列表：",end='')
    print(li0)    
    print("顺序查找3的位置(Python内置函数):",end='')
    print(li0.index(3))
    print("顺序查找3的位置:",end='')
    print(linearSearch(li0,3))
    print("二分查找3的位置:",end='')
    print(binarySearch(li0,3))

    # 排序
    li1 = [4,9,7,1,3,2,5,8,6]
    print("待排序列表：",end='')
    print(li1)    
    # bubbleSort(li1)
    # selectSort(li1)
    insertSort(li1)
    print("排序结果：",end='')
    print(li1)
    # print(selectSortSimple(li1))

        