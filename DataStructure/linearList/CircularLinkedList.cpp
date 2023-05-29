/*
    作者: btx
    日期: 23-5-28
    功能：循环链表的基本实现
*/
#include <stdio.h>
#include <stdlib.h>
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
Node* createNode(ElemType data) {
    Node* newNode = (Node *) malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}
// 表尾插入
bool listAppend(Node** head, int data) {
    Node* newNode = createNode(data);
    //判断头指针是否为空（是否为空链表）
    if (*head == NULL) {
        *head = newNode;
        newNode->next = *head;
        return true;
    } 
    Node* current = *head;
        while (current->next != *head)
            current = current->next;
    current->next = newNode;
    newNode->next = *head;
    return true;
}
// 在循环链表指定位置插入节点
bool listInsert(Node** head, int position, int e) {
    Node* newNode = createNode(e);
    Node* temp = *head;
    if (position == 1) {
        newNode->next = *head;
        //找到最后一个节点
        while (temp->next != *head)
            temp = temp->next;
        temp->next = newNode;
        *head = newNode;
        return true;
    } 
    else{
        for (int i = 1; i < position - 1; i++){
            //说明position大于链表长度
            if(temp->next == *head)
                return false;
            temp = temp->next;
        }
        newNode->next = temp->next;
        temp->next = newNode;
        return true;
    }
    return false;
}
//删除节点
bool listDelete(Node** head, int key) {
    if (*head == NULL)
        return false;
    //两个指针，一个指向当前节点，一个指向上一个节点
    Node* current = *head, *prev;
    while (current->data != key) {
        //目标节点不存在
        if (current->next == *head)
            return false;
        prev = current;
        current = current->next;
    }
    // 删除唯一节点
    if (current->next == *head && current == *head) {
        *head = NULL;
        free(current);
        return true;
    }
    // 删除头节点
    if (current == *head) {
        prev = *head;
        //遍历找到最后一个节点
        while (prev->next != *head)
            prev = prev->next;
         // 头指针指向下一个节点
        *head = (*head)->next;
        prev->next = *head;
        free(current);
        return true;
    } 
    // 删除尾节点
    else if (current->next == *head) {
        prev->next = *head;
        free(current);
        return true;
    } 
    // 删除中间节点
    else 
    {
        prev->next = current->next;
        free(current);
        return true;
    }
}
// 遍历链表
void printList(struct Node* node) {
    printf("链表: ");
    struct Node* temp = node;
    if (node != NULL) {
        do {
            printf("%d ", temp->data);
            temp = temp->next;
        } while (temp != node);
    }
}
int main() {
    Node* L = listInit();
    printf("插入数据\n");
    listAppend(&L, 1);
    listAppend(&L, 2);
    listAppend(&L, 3);
    listAppend(&L, 4);
    printList(L);
    printf("\n在指定位置插入\n");
    listInsert(&L,4,8);
    printList(L);
    printf("\n删除值为3的结点:\n");
    listDelete(&L,3);
    printList(L);
    return 0;
}

