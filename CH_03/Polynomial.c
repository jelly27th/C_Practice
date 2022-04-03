#include <stdio.h>
#include <stdlib.h>

typedef struct Node* ptrToNode;
typedef ptrToNode Polynomial;
typedef struct Node** Position;
struct Node {
    int Coefficient;//系数
    int Exponent;//指数
    Polynomial next;
};

Polynomial CreateNode(Position head, Polynomial L);
void Delete(Polynomial head);
void PrintNode(Polynomial head);
int Length(Polynomial head);
Polynomial zeroPolynomial(Position head, int length);
int Union(Polynomial head1, Polynomial head2);
Polynomial Copy(Polynomial y);
Polynomial FindPrevious(Polynomial L, Polynomial head);
Polynomial Insert(Polynomial head, Polynomial Node);
Polynomial Addition(Polynomial head1, Polynomial head2);
Polynomial Multiply(Polynomial head1, Polynomial head2);
int IsLast(Polynomial pos);
Polynomial Pow(Polynomial FX, unsigned int N);
int IsEven(int N);

int main(int argc, char** argv)
{
    Polynomial y1 = malloc(sizeof(struct Node));
    Polynomial head1 = NULL;
    for (int i = 0; i < 3; i++) {
        y1 = CreateNode(&head1, y1);
    }

    // Polynomial y2 = malloc(sizeof(struct Node));
    // Polynomial head2 = NULL;
    // for (int i = 0; i < 4; i++) {
    //     y2 = CreateNode(&head2, y2);
    // }
    /***多项式相加***/
    // Polynomial y = Addition(head1,head2);
    // PrintNode(y);
    // Delete(y);
    /***多项式相加***/  

    /***多项式相乘***/  
    // Polynomial head = Multiply(head1,head2);
    // PrintNode(head);
    // Delete(head);
    /***多项式相乘***/ 

    /***多项式求幂***/ 
    Polynomial power = Pow(head1,2);
    PrintNode(power);
    Delete(power);
    /***多项式求幂***/  
    Delete(head1);
    // Delete(head2);
    return 0;
}

//创建节点
Polynomial CreateNode(Position head, Polynomial L)
{
    Polynomial temp = malloc(sizeof(struct Node));
    int Coefficient, Exponent;
    scanf("%d %d", &Coefficient, &Exponent);
    temp->Coefficient = Coefficient;
    temp->Exponent = Exponent;
    temp->next = NULL;
    if (*head == NULL)
    {
        *head = L = temp;
    }
    else
    {
        L->next = temp;
        L = temp;
    }
    return L;
}
//删除节点
void Delete(Polynomial head)
{
    Polynomial temp = head;
    while (temp != NULL)
    {
        head = head->next;
        free(temp);
        temp = head;
    }
}
//打印链表
void PrintNode(Polynomial head)
{
    Polynomial pos = head;
    while (pos != NULL)
    {
        printf("%d %d\n", pos->Coefficient, pos->Exponent);
        pos = pos->next;
    }
}
//统计链表长度
int Length(Polynomial head)
{
    Polynomial pos = head;
    int length = 0;
    while (pos != NULL)
    {
        pos = pos->next;
        length++;
    }
    return length;
}
/**创建空链表***/
Polynomial zeroPolynomial(Position head, int length)
{
    int Coefficient = 0;
    int Exponent = 0;
    Polynomial pos = NULL;
    for (int i = 0; i < length; i++)
    {
        Polynomial temp = malloc(sizeof(struct Node));
        temp->Coefficient = Coefficient;
        temp->Exponent = Exponent;
        temp->next = NULL;

        if (*head == NULL) {
            *head = pos = temp;
        }
        else {
            pos->next = temp;
            pos = temp;
        }
    }
    return *head;
}
/***计算多项式相加的长度***/
int Union(Polynomial head1, Polynomial head2)
{
    Polynomial y1, y2;
    y1 = head1;
    int Length = 0;
    while (y1 != NULL)
    {
        y2 = head2;
        while (y2 != NULL && y2->Exponent != y1->Exponent)//遍历head2链表匹配
            y2 = y2->next;
        if (y2 == NULL)//当两个元素不相同时 长度加1
        {
            Length++;
        }
        y1 = y1->next;
    }
    y2 = head2;
    while (y2 != NULL)//把head2链表接到Length后面
    {
        Length++;
        y2 = y2->next;
    }
    return Length;
}
/***复制链表***/
Polynomial Copy(Polynomial y)
{
    int Len = Length(y);
    Polynomial y1 = y;
    Polynomial L = NULL;
    Polynomial head = NULL;
    for (int i = 0; i < Len; i++)
    {
        Polynomial temp = malloc(sizeof(struct Node));
        temp->Coefficient = y1->Coefficient;
        temp->Exponent = y1->Exponent;
        temp->next = NULL;
        if (head == NULL)
        {
            head = L = temp;
        }
        else
        {
            L->next = temp;
            L = temp;
        }
        y1 = y1->next;
    }
    return head;
}
//找上一个节点
Polynomial FindPrevious(Polynomial L, Polynomial head)
{
    Polynomial temp = head;
    while (temp != NULL)
    {
        if (temp->next == L)
            return temp;
        temp = temp->next;
    }
    return NULL;
}
/***插入节点***/
Polynomial Insert(Polynomial head, Polynomial Node)
{
    
    if (head->Exponent < Node->Exponent)//交换的是头节点时
    {
        Polynomial temp = malloc(sizeof(struct Node));
        temp->Coefficient = Node->Coefficient;
        temp->Exponent = Node->Exponent;
        temp->next = head;
        head = temp;
    }
    else {//交换的不是是头节点时
        Polynomial pos = head;
        while (pos != NULL)
        {
            if (Node->Exponent > pos->Exponent)
            {
                Polynomial prev = FindPrevious(pos, head);
                Polynomial temp = malloc(sizeof(struct Node));
                temp->Coefficient = Node->Coefficient;
                temp->Exponent = Node->Exponent;
                temp->next = pos;
                prev->next = temp;
                return head;
            }
            if(IsLast(pos)){//指数最小时添置末尾
                Polynomial temp = malloc(sizeof(struct Node));
                temp->Coefficient = Node->Coefficient;
                temp->Exponent = Node->Exponent;
                temp->next = NULL;
                pos->next = temp;
                return head;
            }
            pos = pos->next;
        }
    }
}
/***检查是否是链表末尾***/
int IsLast(Polynomial pos)
{
    return pos->next==NULL;
}
/***多项式相加***/
Polynomial Addition(Polynomial head1, Polynomial head2)
{
    Polynomial y1, y2;
    y1 = head1; y2 = head2;
    Polynomial y = Copy(y1);//复制一个链表
    while (y2 != NULL)
    {
        y1 = y;
        while (y1 != NULL && y1->Exponent != y2->Exponent)//y2链表每个元素遍历一遍y1链表匹配元素
            y1 = y1->next;
        if (y1 == NULL){//没有相同元素插入
            y = Insert(y, y2);
        }
        else {//有则系数相加
            y1->Coefficient = y1->Coefficient + y2->Coefficient;
        }
        y2 = y2->next;
    }
    return y;
}
/***多项式相乘***/
Polynomial Multiply(Polynomial head1, Polynomial head2)
{
    Polynomial y1, y2, y,head;
    head = y = NULL;
    y1 = head1;
    y2 = head2;
    while(y1!= NULL)//先得到一个链表
    {
        Polynomial temp = malloc(sizeof(struct Node));
        temp->Coefficient = y1->Coefficient*y2->Coefficient;
        temp->Exponent  = y1->Exponent+y2->Exponent;
        temp->next = NULL;
        if(y==NULL){
            y = head = temp;
        }
        else{
            y->next = temp;
            y = temp;
        }
        y1 = y1->next;
    }
    y2 = y2->next;//从第二个节点开始

    while(y2 != NULL)
    {
        y1 = head1;
        while(y1 != NULL)
        {
            Polynomial temp = malloc(sizeof(struct Node));
            temp->Coefficient = y1->Coefficient*y2->Coefficient;
            temp->Exponent  = y1->Exponent+y2->Exponent;
            temp->next = NULL;
            //比较
            y = head;
            while(y!= NULL&& y->Exponent!=temp->Exponent)
                y = y->next;
            if(y==NULL){
                head = Insert(head,temp);
                free(temp);
            }
            else{
                y->Coefficient = y->Coefficient+temp->Coefficient;
                free(temp);
            }
            y1 = y1->next;
        }
        y2 = y2->next;
    }
    return head;
}
/***时间复杂度为O(M2N)***/

/***判断是否是偶数***/
int IsEven(int N)
{
    return N%2==0;
}
/***多项式取幂***/
Polynomial Pow(Polynomial FX, unsigned int N)
{
    if(N==0)
      return 1;
    if(N==1)
      return FX;
    if(IsEven(N)){
        return Pow(Multiply(FX, FX),N/2);
    }
    else{
        return Multiply(Pow(Multiply(FX,FX),N/2),FX);
    }
}