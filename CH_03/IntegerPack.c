#include <stdio.h>
#include <stdlib.h>
typedef enum {
	MORE = 1,
	LESS,
	EQUAL
}Judge;

typedef enum {
	ZERO = 0,
	ONE ,
	TWO,
	THREE,
	FOUR,
	FIVE,
	SIX,
	SEVEN,
	EIGHT,
	NINE
}Num;

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
Judge BigIntegerCompare(List head1, List head2);
List BigIntegerAdd(List rear1, List rear2);
List BigIntegerSubtract(List rear1, List rear2);
List BigIntegerMultiply(List rear1, List rear2);
List BigIntegerDivision(List rear1, List rear2);
List Copy(List rear1);
void Distributed(List head);
List Empty();
List Filp(List pos);

int main(int argc, char** argv)
{
	List L = NULL;
	List P = NULL;
	List L_head = NULL;
	List P_head = NULL;
	BigIntegerStorage(&L_head, &L);
	BigIntegerStorage(&P_head, &P);
	// printf("%d\n",BigIntegerCompare(L_head,P_head));
	// List head = BigIntegerAdd(L, P);
	// List head = BigIntegerSubtract(L, P);
	// List head = BigIntegerMultiply(L, P);
	List head = BigIntegerDivision(L, P);
	Distributed(head);
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
	List temp = head;
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
	if (SIGN == 0)
	{
		printf("-");
		SIGN = 1;
	}
	while (pos != NULL)
	{
		printf("%d", pos->num);
		pos = pos->next;
	}
	if (pos == NULL)
	{
		printf("\n");
	}
}
//统计链表长度
int Length(List head)
{
	List pos = head;
	int length = 0;
	if (pos->next == NULL)
	{
		while (pos != NULL)
		{
			pos = pos->prev;
			length++;
		}
	}
	else if (pos->prev == NULL) {
		while (pos != NULL)
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
	while ((ch = getchar()) != '\n')
		*L = CreateNode(ch - 48, head, L);
}
// 大整数比较
Judge BigIntegerCompare(List head1, List head2)
{
	if (Length(head1) > Length(head2))
		return MORE;
	else if (Length(head1) < Length(head2))
		return LESS;
	else if (Length(head1) == Length(head2)) {
		List L1 = head1;
		List L2 = head2;
		if (L1->next == NULL)//若是低位从高位开始
		{
			for (int i = 0; i < Length(head1) - 1; i++)
				L1 = L1->prev;
		}
		if (L2->next == NULL)//若是低位从高位开始
		{
			for (int i = 0; i < Length(head1) - 1; i++)
				L2 = L2->prev;
		}
		while (L1 != NULL)
		{
			if (L1->num > L2->num)
				return MORE;
			else if (L1->num < L2->num)
				return LESS;
			else if (L1->num == L2->num) {
				L1 = L1->next;
				L2 = L2->next;
			}
		}
	}
	return EQUAL;
}
// 大整数加法
List BigIntegerAdd(List rear1, List rear2)
{
	List L1 = NULL, L2 = NULL;
	List head = NULL;
	int carry = 0;
	if (BigIntegerCompare(rear1, rear2) == MORE || BigIntegerCompare(rear1, rear2) == EQUAL) {
		L1 = rear1;
		L2 = rear2;
	}
	else if (BigIntegerCompare(rear1, rear2) == LESS) {
		L1 = rear2;
		L2 = rear1;
	}

	while (L1 != NULL)
	{
		List temp = malloc(sizeof(struct Node));
		if (L2 == NULL) {
			temp->num = L1->num + carry;
		}
		else
			temp->num = L1->num + L2->num + carry;
		carry = 0;
		temp->next = NULL;
		temp->prev = NULL;
		if (temp->num >= 10)
		{
			carry = 1;
			temp->num = temp->num % 10;//取个位数
		}
		if (head == NULL)
		{
			head = temp;
		}
		else {//头插法
			head->prev = temp;
			temp->next = head;
			head = temp;
		}
		L1 = L1->prev;
		if (L2 != NULL) {
			L2 = L2->prev;
		}
	}
	if (carry == 1)
	{
		List temp = malloc(sizeof(struct Node));
		temp->num = carry;
		temp->next = NULL;
		temp->prev = NULL;

		head->prev = temp;
		temp->next = head;
		head = temp;
	}
	return head;
}
// 大整数减法
List BigIntegerSubtract(List rear1, List rear2)
{
	List L1 = NULL, L2 = NULL;
	List head = NULL;
	if (BigIntegerCompare(rear1, rear2) == MORE || BigIntegerCompare(rear1, rear2) == EQUAL) {
		L1 = rear1;
		L2 = rear2;
	}
	else if (BigIntegerCompare(rear1, rear2) == LESS) {
		L1 = rear2;
		L2 = rear1;
		SIGN = 0;
	}
	int carry = 0;
	int flag = 0;
	while (L1 != NULL)
	{
		List temp = malloc(sizeof(struct Node));
		if (L2 != NULL) {
			if (L1->num < L2->num && flag == 0) {
				carry = 10;
				flag = 1;
			}
			else if (L1->num < L2->num && flag == 1) {
				carry = 9;
			}
			else if (L1->num > L2->num && flag == 1) {
				carry = -1;
				flag = 0;
			}
		}
		else if (L2 == NULL && flag == 1) {
			carry = -1;
			flag = 0;
		}

		if (L2 != NULL) {
			temp->num = L1->num - L2->num + carry;
		}
		else if (L2 == NULL) {
			temp->num = L1->num + carry;
		}
		carry = 0;
		temp->next = NULL;
		temp->prev = NULL;
		if (head == NULL)
		{
			head = temp;
		}
		else {//头插法
			head->prev = temp;
			temp->next = head;
			head = temp;
		}
		L1 = L1->prev;
		if (L2 != NULL) {
			L2 = L2->prev;
		}
	}
	if (Length(head) != 1)//长度不为1时
	{
		while (head->num == 0&&Length(head)!=1)//若最高位前面有零
		{
			List temp = head;
			head = head->next;
			head->prev = NULL;
			free(temp);
		}
	}
	return head;
}
// 大整数乘法
List BigIntegerMultiply(List rear1, List rear2)
{
	List L1 = NULL, L2 = NULL;
	List head = NULL, rear = NULL;
	if (BigIntegerCompare(rear1, rear2) == MORE || BigIntegerCompare(rear1, rear2) == EQUAL) {
		L1 = rear2;
		L2 = rear1;
	}
	else if (BigIntegerCompare(rear1, rear2) == LESS) {
		L1 = rear1;
		L2 = rear2;
	}
	List ret = L2;
	/**先得到一个链表 START**/
	int carry = 0;
	while (ret != NULL)
	{
		List temp = malloc(sizeof(struct Node));
		temp->num = L1->num * ret->num + carry;
		temp->next = NULL;
		temp->prev = NULL;
		carry = 0;
		if (temp->num >= 10)
		{
			carry = temp->num / 10;
			temp->num = temp->num % 10;
		}
		if (head == NULL)
		{
			rear = head = temp;
		}
		else {//头插法
			head->prev = temp;
			temp->next = head;
			head = temp;
		}
		ret = ret->prev;
	}
	if (carry != 0)
	{
		List temp = malloc(sizeof(struct Node));
		temp->num = carry;
		temp->next = NULL;
		temp->prev = NULL;

		head->prev = temp;
		temp->next = head;
		head = temp;
	}
	/**先得到一个链表 END**/
	L1 = L1->prev;
	while (L1 != NULL)
	{
		/**再得到另外一个链表 START****/
		carry = 0;
		List head1 = NULL, rear3 = NULL;
		ret = L2;
		while (ret != NULL)
		{
			List temp = malloc(sizeof(struct Node));
			temp->num = L1->num * ret->num + carry;
			temp->prev = NULL;
			temp->next = NULL;
			carry = 0;
			if (temp->num >= 10)
			{
				carry = temp->num / 10;
				temp->num = temp->num % 10;
			}
			if (head1 == NULL)
			{
				rear3 = head1 = temp;
			}
			else {//头插法
				head1->prev = temp;
				temp->next = head1;
				head1 = temp;
			}
			ret = ret->prev;
		}
		if (carry != 0)
		{
			List temp = malloc(sizeof(struct Node));
			temp->num = carry;
			temp->next = NULL;
			temp->prev = NULL;

			head1->prev = temp;
			temp->next = head1;
			head1 = temp;
		}
		/**再得到另外一个链表 END****/
		/**两链表相加 START **/
		List pos = rear->prev;
		carry = 0;
		while (rear3 != NULL)
		{
			if (pos != NULL)
			{
				pos->num = pos->num + rear3->num + carry;
				carry = 0;
				if (pos->num >= 10)
				{
					carry = 1;
					pos->num = pos->num % 10;
				}
			}
			else {
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
			if (pos != NULL)
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
List BigIntegerDivision(List rear1, List rear2)
{
	int len1 = Length(rear1);
	int len2 = Length(rear2);
	List head = NULL;
	if (len1 < len2)
	{
		head = malloc(sizeof(struct Node));
		head->num = 0;
		head->next = NULL;
		head->prev = NULL;
	}
	else if (len1 == len2) {
		head = malloc(sizeof(struct Node));
		head->num = 0;
		head->next = NULL;
		head->prev = NULL;
		List L1 = Copy(rear1);
		while (BigIntegerCompare(L1, rear2) == MORE || BigIntegerCompare(L1, rear2) == EQUAL)
		{
			head->num++;//次数加1
			while (L1->next != NULL)//头指针转向尾指针
			{
				L1 = L1->next;
			}
			L1 = BigIntegerSubtract(L1, rear2);
		}
		Delete(L1);
	}
	else if (len1 > len2) {
		int diff = len1 - len2 + 1;
		List rear = NULL;
		List L1 = Copy(rear1);
		while (diff)
		{
			/**目标链表 START**/
			List temp1 = malloc(sizeof(struct Node));
			temp1->next = NULL;
			temp1->prev = NULL;
			temp1->num = 0;
			if (head == NULL)
			{
				head = rear = temp1;
			}
			else {
				rear->next = temp1;//尾插法
				temp1->prev = rear;
				rear = temp1;
			}
			/**目标链表 END**/
			/**补零 START**/
			List L2 = Copy(rear2);
			for (int i = 0; i < diff - 1; i++)
			{
				List temp = malloc(sizeof(struct Node));
				temp->num = 0;
				temp->next = NULL;
				temp->prev = NULL;
				L2->next = temp;//尾插法
				temp->prev = L2;
				L2 = temp;
			}
			/**补零 END**/
			while (BigIntegerCompare(L1, L2) == MORE || BigIntegerCompare(L1,L2) == EQUAL)
			{
				rear->num++;//次数加1
				while (L1->next != NULL)//头指针转向尾指针
				{
					L1 = L1->next;
				}
				L1 = BigIntegerSubtract(L1, L2);
			}
			Delete(L2);
			diff--;
		}
		Delete(L1);
	}
	if (Length(head) != 1)//长度不为1时
	{
		while (head->num == 0 && Length(head) != 1)//若最高位前面有零
		{
			List temp = head;
			head = head->next;
			head->prev = NULL;
			free(temp);
		}
	}
	return head;
}
//复制双向链表并返回尾指针
List Copy(List rear1)
{
	List head = NULL, rear = NULL;
	List pos = rear1;
	while (pos != NULL)
	{
		List temp = malloc(sizeof(struct Node));
		temp->num = pos->num;
		temp->next = NULL;
		temp->prev = NULL;
		if (head == NULL)
			head = rear = temp;
		else {
			head->prev = temp;
			temp->next = head;
			head = temp;
		}
		pos = pos->prev;
	}
	return rear;
}
//计算数字分布 输入是首指针
void Distributed(List head)
{
	List pos = head;
	List add = malloc(sizeof(struct Node));
	add->num = 1;
	add->prev = NULL;
	add->next = NULL;
	List zero = Empty();
	List one = Empty();
	List two = Empty();
	List three = Empty();
	List four = Empty();
	List five = Empty();
	List six = Empty();
	List seven = Empty();
	List eight = Empty();
	List nine = Empty();
	while(pos != NULL)
	{
		switch(pos->num) {
			case ZERO:
			zero = BigIntegerAdd(zero,add);
			zero = Filp(zero);
			break;
			case ONE:
			one = BigIntegerAdd(one,add);
			one = Filp(one);
			break;
			case TWO:
			two = BigIntegerAdd(two,add);
			two = Filp(two);
			break;
			case THREE:
			three = BigIntegerAdd(three,add);
			three = Filp(three);
			break;
			case FOUR:
			four = BigIntegerAdd(four,add);
			four = Filp(four);
			break;
			case FIVE:
			five = BigIntegerAdd(five,add);
			five = Filp(five);
			break;
			case SIX:
			six = BigIntegerAdd(six,add);
			six = Filp(six);
			break;
			case SEVEN:
			seven = BigIntegerAdd(seven,add);
			seven = Filp(seven);
			break;
			case EIGHT:
			eight = BigIntegerAdd(eight,add);
			eight = Filp(eight);
			break;
			case NINE:
			nine = BigIntegerAdd(nine,add);
			nine = Filp(nine);
			break;
			default:
			printf("error");
			break;
		}
		pos = pos->next;
	}
	zero = Filp(zero);
	one = Filp(one);
	two = Filp(two);
	three = Filp(three);
	four = Filp(four);
	five = Filp(five);
	six = Filp(six);
	seven = Filp(seven);
	eight = Filp(eight);
	nine = Filp(nine);
	printf("0:");
	PrintNode(zero);
	printf("1:");
	PrintNode(one);
	printf("2:");
	PrintNode(two);
	printf("3:");
	PrintNode(three);
	printf("4:");
	PrintNode(four);
	printf("5:");
	PrintNode(five);
	printf("6:");
	PrintNode(six);
	printf("7:");
	PrintNode(seven);
	printf("8:");
	PrintNode(eight);
	printf("9:");
	PrintNode(nine);
}
//创建一个长度为1空链表
List Empty()
{
	List head = malloc(sizeof(struct Node));
	head->next = NULL;
	head->prev = NULL;
	head->num = 0;
	return head;
}
//指针首末倒换
List Filp(List pos)
{
	if(pos->next==NULL)
	{
		for(int i=0; i<Length(pos)-1; i++)
		   pos = pos->prev;
	}
	else{
		for(int i=0; i<Length(pos)-1;i++)
		   pos = pos->next;
	}
	return pos;
}