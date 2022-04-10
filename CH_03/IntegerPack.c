#include <stdio.h>
#include <stdlib.h>
typedef enum{
	MORE = 1,
	LESS,
	EQUAL
}Judge;

typedef struct Node* ptrToNode;
typedef ptrToNode List;
typedef struct Node** Position;
struct Node {
    int num;
    List next;
	List prev;
};
 
int SIGN = 1;//1为正号 0为负号

List CreateNode(int element, Position head, Position L);
void Delete(List head);
void PrintNode(List head);
int Length(List head);
void BigIntegerStorage(Position head, Position L);
Judge BigIntegerCompare(List head1,List head2);
List BigIntegerAdd(List rear1,List rear2);
List BigIntegerSubtract(List rear1,List rear2);
List BigIntegerMultiply(List rear1,List rear2);

int main(int argc, char** argv)
{
	List L = NULL;
	List P  = NULL;
    List L_head = NULL;
	List P_head = NULL;
	BigIntegerStorage(&L_head,&L);
	BigIntegerStorage(&P_head,&P);
    // printf("%d\n",BigIntegerCompare(L_head,P_head));
	// List head = BigIntegerAdd(L, P);
	// List head = BigIntegerSubtract(L, P);
	List head = BigIntegerMultiply(L, P);
	PrintNode(head);
	PrintNode(L_head);
	PrintNode(P_head);
	Delete(L_head);
	Delete(P_head);
	Delete(head);
	return 0;
}


// char ch;
// while((ch = getchar()) != '\n') 
// 	putchar(ch);
//创建节点
List CreateNode(int element, Position head, Position L)
{
    List temp = malloc(sizeof(struct Node));
    temp->num = element;
    temp->next = NULL;
	temp->prev = NULL;
    if (*head == NULL)
    {
        *head = *L = temp;
    }
    else
    {
        (*L)->next = temp;
		temp->prev = *L;
        *L = temp;
    }
    return *L;
}
//删除节点
void Delete(List head)
{
    List temp  = head;
    while (temp != NULL)
    {
        head = head->next;
        free(temp);
        temp = head;
    }
}
//打印链表&大整数表示
void PrintNode(List head)
{
    List pos = head;
	if(SIGN==0)
	{
		printf("-");
		SIGN = 1;
	}
    while(pos != NULL)
    {
        printf("%d",pos->num);
        pos = pos->next;
    }
	if(pos == NULL)
	{
		printf("\n");
	}
}
//统计链表长度
int Length(List head)
{
    List pos = head;
    int length = 0;
	if(pos->next==NULL)
	{
		while(pos != NULL)
		{
			pos = pos->prev;
			length++;
		}
	}
	else if(pos->prev == NULL){
		while(pos != NULL)
		{
			pos = pos->next;
			length++;
		}
	}
    return length;
}
// 大整数存储
void BigIntegerStorage(Position head, Position L)
{
	int ch;
	while((ch = getchar()) != '\n') 
	    *L = CreateNode(ch-48,head,L);
}
// 大整数比较
Judge BigIntegerCompare(List head1,List head2)
{
	if(Length(head1)>Length(head2))
	   return MORE;
	else if(Length(head1)<Length(head2))
	   return LESS;
	else if(Length(head1)==Length(head2)){
		List L1 = head1;
		List L2 = head2;
		if(L1->next==NULL&&L2->next==NULL)//若是低位从高位开始
		{
			for(int i=0;i< Length(head1)-1;i++)
			{
				L1 = L1->prev;
				L2 = L2->prev;
			}
		}
		while(L1!= NULL)
		{
			if(L1->num>L2->num)
			   return MORE;
			else if(L1->num<L2->num)
			   return LESS;
			else if(L1->num==L2->num){
				L1 = L1->next;
				L2 = L2->next;
			}
		}
	}
	return EQUAL;
}
// 大整数加法
List BigIntegerAdd(List rear1,List rear2)
{
	List L1 = NULL, L2 = NULL;
	List head = NULL;
	int carry = 0;
	if(BigIntegerCompare(rear1,rear2)==MORE||BigIntegerCompare(rear1,rear2)==EQUAL){
		L1 = rear1;
		L2 = rear2;
	}
	else if(BigIntegerCompare(rear1,rear2)==LESS){
		L1 = rear2;
		L2 = rear1;
	}

	while(L1 != NULL)
	{
		List temp = malloc(sizeof(struct Node));
		if(L2 == NULL){
			temp->num =  L1->num + carry;
		}
		else
			temp->num = L1->num + L2->num + carry;
		carry = 0;
		temp->next = NULL;
		temp->prev = NULL;
		if(temp->num>=10)
		{
			carry = 1;
			temp->num = temp->num%10;//取个位数
		}
		if(head == NULL)
		{
			head = temp;
		}
		else{//头插法
			head->prev  = temp;
			temp->next = head;
			head = temp;
		}
		L1 = L1->prev;
		if(L2 != NULL){
			L2 = L2->prev;
		}
	}
	if(carry==1)
	{
		List temp = malloc(sizeof(struct Node));
		temp->num = carry;
		temp->next = NULL;
		temp->prev = NULL;

		head->prev  = temp;
		temp->next = head;
		head = temp;
	}
	return head;
}
// 大整数减法
List BigIntegerSubtract(List rear1,List rear2)
{
	List L1 = NULL, L2 = NULL;
	List head = NULL;
	if(BigIntegerCompare(rear1,rear2)==MORE||BigIntegerCompare(rear1,rear2)==EQUAL){
		L1 = rear1;
		L2 = rear2;
	}
	else if(BigIntegerCompare(rear1,rear2)==LESS){
		L1 = rear2;
		L2 = rear1;
		SIGN = 0;
	}
	int carry  = 0;
	int flag = 0;
	while(L1 != NULL)
	{
		List temp = malloc(sizeof(struct Node));
		if(L2!= NULL){
			if(L1->num<L2->num&&flag==0){
				carry = 10;
				flag = 1;
			}
			else if(L1->num<L2->num&&flag==1){
				carry = 9;
			}
			else if(L1->num>L2->num&&flag==1){
				carry = -1;
				flag = 0;
			}
		}
		else if(L2== NULL&&flag==1){
			carry = -1;
			flag = 0;
		}
		     
		if(L2!= NULL){
			temp->num = L1->num - L2->num + carry;
		}
		else if(L2== NULL){
			temp->num = L1->num  + carry;
		}
		carry = 0;
		temp->next = NULL;
		temp->prev = NULL;
		if(head == NULL)
		{
			head = temp;
		}
		else{//头插法
			head->prev  = temp;
			temp->next = head;
			head = temp;
		}
		L1 = L1->prev;
		if(L2 != NULL){
			L2 = L2->prev;
		}
	}
	return head;
}
// 大整数乘法
List BigIntegerMultiply(List rear1,List rear2)
{
	List L1 = NULL, L2 = NULL;
	List head = NULL,rear = NULL;
	if(BigIntegerCompare(rear1,rear2)==MORE||BigIntegerCompare(rear1,rear2)==EQUAL){
		L1 = rear2;
		L2 = rear1;
	}
	else if(BigIntegerCompare(rear1,rear2)==LESS){
		L1 = rear1;
		L2 = rear2;
	}
	List ret = L2;
/**先得到一个链表 START**/
	int carry = 0;
	while(ret != NULL)
	{
		List temp = malloc(sizeof(struct Node));
		temp->num = L1->num*ret->num+carry;
		temp->next = NULL;
		temp->prev = NULL;
		carry = 0;
		if(temp->num>=10)
		{
			carry = temp->num/10;
			temp->num = temp->num%10;
		}
		if(head == NULL)
		{
			rear = head = temp;
		}
		else{//头插法
			head->prev  = temp;
			temp->next = head;
			head = temp;
		}
		ret = ret->prev;
	}
	if(carry!=0)
	{
		List temp = malloc(sizeof(struct Node));
		temp->num = carry;
		temp->next = NULL;
		temp->prev = NULL;

		head->prev  = temp;
		temp->next = head;
		head = temp;
	}
/**先得到一个链表 END**/
	L1 = L1->prev;
	while(L1 != NULL)
	{
		/**再得到另外一个链表 START****/
		carry = 0;
		List head1 = NULL,rear3 = NULL;
		ret = L2;
		while(ret != NULL)
		{
			List temp = malloc(sizeof(struct Node));
			temp->num = L1->num*ret->num+carry;
			temp->prev = NULL;
			temp->next = NULL;
			carry = 0;
			if(temp->num>=10)
			{
				carry = temp->num/10;
				temp->num = temp->num%10;
			}
			if(head1 == NULL)
			{
				rear3 = head1 = temp;
			}
			else{//头插法
				head1->prev  = temp;
				temp->next = head1;
				head1 = temp;
			}
			ret = ret->prev;
		}
		if(carry!=0)
		{
			List temp = malloc(sizeof(struct Node));
			temp->num = carry;
			temp->next = NULL;
			temp->prev = NULL;

			head1->prev  = temp;
			temp->next = head1;
			head1 = temp;
		}
		/**再得到另外一个链表 END****/
		/**两链表相加 START **/
		List pos = rear->prev;
		carry = 0;
		while(rear3 != NULL)
		{
			if(pos!= NULL)
			{
				pos->num = pos->num + rear3->num + carry;
				carry = 0;
				if(pos->num>=10)
				{
					carry = 1;
					pos->num = pos->num%10;
				}
			}
			else{
				List temp = malloc(sizeof(struct Node));
				temp->num = head1->num + carry;
				carry = 0;
				temp->next = NULL;
				temp->prev = NULL;

				head->prev = temp;
				temp->next = head;
				head = temp;
			}
			rear3 = rear3->prev;
			if(pos!= NULL)
				pos = pos->prev;
		}
		Delete(head1);//销毁临时链表
		/**两链表相加 END **/
		rear = rear->prev;//目标指针向前移一位
		L1 = L1->prev;
	}
	return head;
}
// 大整数除法