/*
    作者: btx
    日期: 23-5-30
    功能：顺序栈的基本实现
*/
#include <stdio.h>
#include <stdlib.h>
#define ElemType int
#define MaxSize 10
typedef struct{
    ElemType data[MaxSize];
    int top; //栈顶指针
}SqStack;
//初始化
void srackInit(SqStack &S){
    S.top = -1;
}
//入栈
bool push(SqStack &S,ElemType x){
    //判断栈是否已满
    if(S.top == MaxSize-1)
        return false;
    S.top = S.top + 1;//指针+1
    S.data[S.top] = x;//入栈
    return true;
}
bool pop(SqStack &S,ElemType &x){
    if(S.top == -1)
        return false;
    x = S.data[S.top];//先出栈
    S.top = S.top - 1;//指针减1
    return true;
}
//获取栈顶元素
bool getTop(SqStack &S,ElemType &x){
    if(S.top == -1)
        return false;
    x = S.data[S.top];
    return true;
}
int main(){
    SqStack S;
    srackInit(S);
    push(S,1);
    push(S,2);
    push(S,3);
    int x;
    getTop(S,x);
    printf("当前栈顶元素为:%d\n",x);
    pop(S,x);
    printf("出栈:%d\n",x);
    pop(S,x);
    printf("出栈:%d\n",x);
    pop(S,x);
    printf("出栈:%d\n",x);
    return 0;
}