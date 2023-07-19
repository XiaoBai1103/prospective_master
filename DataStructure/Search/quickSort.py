'''
    作者: btx
    日期: 23-7-14
    功能：快速排序
'''
def partition(li,left,right):
    # 取出左边第一个数
    tmp = li[left]
    # 当left和right相等，将第一个数补到空位中
    while left < right:
        # 从右边找比tmp小的数 left < right是为了避免left == right时代码被执行
        while left < right and li[right] >= tmp:
            right -= 1  # 指针向左移一步
        li[left] = li[right]  # 把右边的值写到左边的空位
        print(li)
        # 从左边找比tmp小的数 left < right是为了避免left == right时代码被执行
        while left < right and li[left] <= tmp:
            left += 1
        li[right] = li[left]  # 把左边的值写到左边的空位
        print(li)
    li[left] = tmp
    # 此时left==right，返回left和right均可
    return left

def quickSort(li,left,right):
    if left < right:
        # 归位函数算出中间下标的位置，mid将列表分为两部分
        mid = partition(li, left, right)
        quickSort(li, left, mid-1)
        quickSort(li, mid+1, right)

li = [4, 9, 7, 1, 3, 2, 5, 8, 6]
print("待排序列表：", end = '')
print(li)
quickSort(li,0,len(li)-1)
print(li)
