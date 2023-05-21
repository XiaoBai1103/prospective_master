/*
    作者: btx
    日期: 23-5-17
    功能：顺序表的基本实现
*/
#include<stdio.h>
#include<malloc.h>
#define ElemType int 
typedef struct 
{
    ElemType *data;//指向申请的存储空间
    int maxSize;//最大容量
    int length;//当前容量
}seqList;
/*
    初始化过程申请一片连续存储空间,申请的容量为 初始大小*int类型的大小
    将malloc函数的返回所申请存储空间的起始地址
    需要把返回值转化为int类型指针
*/
void listInit(seqList &L,int initSize){
    L.data = (int *)malloc(initSize*sizeof(ElemType));
    L.length = 0;
    L.maxSize = initSize;
}

//增加长度
void listIncrease(seqList &L,int len){
    int *p = L.data;
    L.data = (int *)malloc((L.maxSize+len)*sizeof(int));
    //复制数据到新申请的区域
    for(int i=0;i<L.length;i++){
        L.data[i] = p[i];
    }
    L.maxSize = L.maxSize+len;
    free(p);
}
//插入数据 位置:i 元素:e
bool listInsert(seqList &L,int i,ElemType e){
    //判断数值合法、存储空间是否已满
    if(i<1||i>L.length+1||L.length>=L.maxSize)
        return false;
    else{
        for(int j=L.length;j>=i;j--)
            L.data[j] = L.data[j-1];
        L.data[i-1] = e;
        L.length++;
        return true;
    }
}
//删除数据 位置:i 元素:e(e的作用是把删除的元素带回)
bool listDelete(seqList &L,int i,ElemType &e){
    //判断数值合法、存储空间是否已满
    if(i<1||i>L.length)
        return false;
    else{
        e = L.data[i-1];
        for(int j=i;j<L.length;j++)
            L.data[j-1] = L.data[j];
        L.length--;
        return true;
    }
}
//查找 返回位置
bool findElement(seqList &L, ElemType e,int &loc) {
    for (loc = 0; loc < L.length; loc++) {
        if (L.data[loc] == e) {
            loc++;
            return true;
        }
    }
    return false;
}
// 遍历顺序表
void printList(seqList &L) {
    printf("顺序表:");
    for(int i = 0;i < L.length; i++){
    printf(" %d",L.data[i]);    
    }
    printf("\n");
}
int main(){
    seqList L;
    listInit(L,2);
    //插入
    listInsert(L,1,1);
    listInsert(L,2,2);
    if(listInsert(L,3,3))
        printf("扩容前插入成功\n");
    else
        printf("扩容前插入失败\n");
    listIncrease(L,3);
    if(listInsert(L,3,3))
        printf("扩容后插入成功\n");
    else
        printf("扩容后插入失败\n");
    printList(L);
    //查找
    int loc;
    if(findElement(L,3,loc))
        printf("值为3的元素位于%d\n",loc);
    //删除
    int e;
    if(listDelete(L,2,e))  
        printf("已删除第2的元素%d\n",e);
    printList(L);
    return 0;
}