/*
    作者: btx
    日期: 23-5-18
    功能：单链表的基本实现
*/
#include <stdio.h>
#include<malloc.h>
#define ElemType int
//每个结点的存储结构
typedef struct Node {
    ElemType data;
    struct Node* next;
} Node;
// 初始化
Node* listInit() {
    Node* head = NULL;
    return head;
}
// 创建节点
Node* createNode(ElemType e) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = e;
    newNode->next = NULL;
    return newNode;
}
// 在表尾插入
// 使用二级指针实现，通过改变头指针的值来实现在链表头部插入新节点的操作
bool listAppend(Node** head, ElemType value) {
    Node* newNode = createNode(value);
    //判断头指针是否为空（是否为空链表）
    if (*head == NULL) {  
        *head = newNode;
        return true;
    }
    Node* current = *head;
    //遍历链表，找到尾结点
    while (current->next != NULL) {
        //将当前节点指针current指向下一个节点
        current = current->next;
    }
    //将新节点添加在尾节点后
    current->next = newNode;
    return true;
}
// 在表头插入
bool listInsertAtBegin(Node** head, ElemType value) {
    Node* newNode = createNode(value);
    if (*head == NULL) {
        *head = newNode;
        return true;
    }
    newNode->next = *head;
    *head = newNode;
    return true;
}
// 在指定位置插入 前一个结点prevNode 元素:e
bool listInsert(Node* prevNode, ElemType e) {
    //给定结点合法性检查
    if (prevNode == NULL) {
        return false;
    }
    Node* newNode = createNode(e);
    newNode->next = prevNode->next;
    prevNode->next = newNode;
    return true;
}
// 删除节点 元素:e
bool listDelete(Node** head, ElemType e) {
    //非空判断
    if (*head == NULL) {
        return false;
    }
    //需要删除的是否是头结点
    if ((*head)->data == e) {
        *head = (*head)->next;
        return true;
    }
    //遍历结点找到要删除的
    Node* current = *head;
    while (current->next != NULL && current->next->data != e) {
        current = current->next;
    }
    if (current->next != NULL) {
        Node* temp = current->next;
        current->next = temp->next;
        free(temp);
        return true;
    }
    return false;
}
// 遍历链表
void printList(Node* head) {
    Node* current = head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

int main() {
    Node* L = listInit();

    if (listAppend(&L, 1)) {
        printf("表尾插入成功 ");printf("链表: ");printList(L);
    }
    if (listAppend(&L, 2)) {
        printf("表尾插入成功 ");printf("链表: ");printList(L);
    }
    if (listInsert(L, 3)) {
        printf("指定位置插入成功 ");printf("链表: ");printList(L);
    }
    if (listInsertAtBegin(&L, 4)) {
        printf("表头插入成功 ");printf("链表: ");printList(L);
    }

    printf("链表: ");
    printList(L);

    if (listDelete(&L, 3)) {
        printf("删除值为3的结点\n");
    } 

    printf("删除节点后的链表: ");
    printList(L);

    return 0;
}


