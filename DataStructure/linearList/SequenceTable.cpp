/*
    作者: btx
    日期: 23-5-17
    功能：顺序表的基本实现
*/
#include<stdio.h>
#include<malloc.h>
#define initSize 10
typedef struct 
{
    int *data;//指向申请的存储空间
    int maxSize;//最大容量
    int length;//当前容量
}seqList;
/*
    初始化过程申请一片连续存储空间,申请的容量为 初始大小*int类型的大小
    将malloc函数的返回所申请存储空间的起始地址
    需要把返回值转化为int类型指针
*/
void listInit(seqList &L){
    L.data = (int *)malloc(initSize*sizeof(int));
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
bool listInsert(seqList &L,int i,int e){
    //判断数值合法、存储空间是否已满
    if(i<1||i>L.length+1||L.length>=L.maxSize-1)
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
bool listDelete(seqList &L,int i,int &e){
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

int main(){
    seqList L;
    listInit(L);
    int i,e;
    //插入
    i=1;e=5;
    if(listInsert(L,i,e))
        printf("已在%d的位置差入%d\n",i,L.data[i-1]);
    else
        printf("失败\n");
    //删除
    i=1;
    if(listDelete(L,i,e))
        printf("已删除第%d的元素%d",i,e);
    else
        printf("失败\n");
    return 0;

}