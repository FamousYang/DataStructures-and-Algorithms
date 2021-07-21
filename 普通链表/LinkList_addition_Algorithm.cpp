#include<stdio.h>
#include<stdlib.h>
//                                                      *****普通链表附加算法*****
//                                              第一部分题目均有头节点，第二部分题目不带头节点
//普通链表结构
typedef int DataType;
typedef struct node {
	DataType data;
	struct node* link;
}LinkNode, * LinkList;

//链表无头结点初始化
void initListNoHead(LinkList& first) {
	first == nullptr;
}
//链表有头结点初始化
void initListHead(LinkList& first) {
	first = (LinkNode*)malloc(sizeof(LinkNode));
	first->link = nullptr;
}

//                                                               第一部分


//确定元素值最大的节点                                                             O(n),O(1)
LinkNode* Max(LinkList& L) {
	if (L->link == nullptr) {
		return nullptr;
	}
	LinkNode* pmax = L->link,*p;
	for (p = pmax->link; p != nullptr; p = p->link) {
		if (p->data > pmax->data) {
			pmax = p;
		}
	}
	return pmax;
}

//统计有多少个元素值为x的节点                                                         O(n),O(1)
int CountData_is_x(LinkList& L, DataType x) {
	LinkNode* p = L->link;
	int count = 0;
	for (; p != nullptr; p = p->link) {
		if (p->data == x) {
			count++;
		}
	}
	return count;
}

//删除一个值最小的节点                                                          O(n),O(1)
bool Remove_min(LinkList& L, DataType& x) {
	if (L->link == nullptr) {
		return false;
	}
	LinkList p, pr = L, pmin = L->link;
	for (p = pmin; p->link != nullptr; p = p->link) {
		if (p->link->data < p->data) {
			pr = p;
			pmin = p->link;
		}
	}
	pr->link = pmin->link;
	x = pmin->data;
	free(pmin);
	return true;
}

//将值最小的节点移动到链表最前面                                                O(n),O(1)
void Move_min_front(LinkList& L) {
	if (L->link == nullptr) {
		return;
	}
	LinkList p, pr = L, pmin = L->link;
	for (p = pmin; p->link != nullptr; p = p->link) {
		if (p->link->data < p->data) {
			pr = p;
			pmin = p->link;
		}
	}
	pr->link = pmin->link;
	pmin->link = L->link;
	L->link = pmin;
}

//找到倒数第k个节点，输出值返回1                                                           O(n),O(1)
int Search_rear_k(LinkList& L, int k) {
	LinkList p, q;
	int count = 0;
	for (p = q = L->link; p != nullptr; p = p->link) {
		if (count < k) {
			count++;
		}
		else {
			q = q->link;
		}
	}
	if (count < k) {
		return 0;
	}
	else {
		printf("%d\n", q->data);
		return 1;
	}
}

//判断链表长度是奇数还是偶数                                                 O(n),O(1)
int Even_Odd_len(LinkList& L) {
	LinkList p = L->link;
	while (p!=nullptr && p->link != nullptr)
	{
		p = p->link->link;
	}
	if (p == nullptr) {
		return 0;
	}
	else
	{
		return 1;
	}
}

//返回中间节点的指针      同样适用于删除中间节点                                O(n),O(1)
LinkList midPoint(LinkList& L) {
	LinkList fast = L->link, slow = L->link;
	while (fast!= NULL && fast->link!=NULL)
	{
		slow = slow->link;
		fast = fast->link->link;
	}
	return slow;
}

//判断链表是否中心对称（逆转后半部分，一一对比即可）                                 O(n),O(1)
bool isPalindrome(LinkList& L) {
	if (L == NULL || L->link == NULL) {
		return true;
	}
	LinkNode* p = L->link, * q = L->link,*s;
	while (q->link != NULL && q->link->link != NULL) {       //找到中间节点
		p = p->link;
		q = q->link->link;
	}
	q = p->link;
	p->link = NULL;
	s = nullptr;                                             //后半部分逆转

	while (q != NULL) {
		s = q->link;
		q->link = p;
		p = q;
		q = s;
	}
	s = p;
	q = L->link;
	bool res = true;                                        //开始比较
	while (q != NULL && p != NULL) {
		if (q->data != p->data) {
			res = false;
			break;
		}
		q = q->link;
		p = p->link;
	}

	p = s->link;
	s->link = NULL;                                         //比较完毕，恢复链表
	while (p != nullptr) {
		q = p->link;
		p->link = s;
		s = p;
		p = q;
	}
	return res;
}

//交替将A，B的节点插入C中                                   O（n）,O(1)
void Merge(LinkList& A, LinkList& B, LinkList& C) {
	LinkList pa = A->link, pb = B->link, pc = C;
	free(A);
	free(B);
	while (pa != NULL && pb != NULL) {
		pc->link = pa;
		pc = pc->link;
		pa = pa->link;
		pc->link = pb;
		pc = pc->link;
		pb = pb->link;
	}
	if (pa != NULL) {
		pc->link = pa;
	}
	else {
		pc->link = pb;
	}
}

//判断链表是否有环，有的话求入口（弗洛伊德环判定算法）                         O(n),O(1)
LinkNode* findLoopEntry(LinkList& L) {
	LinkList fast = L->link, slow = L->link;
	while (fast!=nullptr && fast->link != nullptr)
	{
		slow = slow->link;
		fast = fast->link->link;
		if (fast == slow) {
			break;
		}
	}
	if (fast->link == nullptr) {
		return NULL;
	}
	slow = L->link;
	while (fast != slow) {
		slow = slow->link;
		fast = fast->link;
	}
	return fast;
}

//成对逆转链表顺序  1-2-3-4    ->     2-1-4-3                       O(n),O(1)
void pair_reverse(LinkList& L) {
	LinkList pr = L, p = L->link,q,r;
	while(p != nullptr && p->link != NULL) {
		q = p->link;
		r = q->link;
		q->link = p;
		p->link = r;
		pr->link = q;
		pr = p;
		p = r;
	}
}

//                                                              第二部分

//链表元素循环右移k个位置                                                     //O(n),O(1)
bool Rotate_List(LinkList& L, int k) {
	LinkList fast = L, slow;
	int i = 1;
	while (fast != NULL && i <= k) {
		fast = fast->link;
		i++;
	}
	if (fast == NULL) {
		return false;
	}
	slow = L;
	while (fast->link!=NULL)
	{
		fast = fast->link;
		slow = slow->link;
	}                                                //fast在最后，slow在倒数k+1，后k个整体搬到链表最前面即可
	fast->link = L;
	L = slow->link;
	slow->link = NULL;
}

//成对逆转链表顺序增强版，按照k翻转，例如k=3    1-2-3-4-5-6             ->               3-2-1-6-5-4
LinkList k_reverse(LinkList& L, int k) {
	int n = k;
	LinkList p = L,s,h,t,q,r;                    //p指向旧链表用来遍历，s临时创建节点，ht指向临时链表的头尾，qr指向新链表的头尾
	while (p != NULL) {
		s = (LinkList)malloc(sizeof(LinkNode));
		s->data = p->data;
		p = p->link;
		if (h == nullptr) {
			s->link = nullptr;
			h = t = s;
		}
		else {
			s->link = nullptr;
			h = s;
		}
		n--;
		if (n == 0) {
			if (q == NULL) {
				q = h;
				r = t;
			}
			else {
				r->link = h;
				r = t;
			}
			n = k;
			h = NULL;
		}
	}
	if (h != NULL) {
		r->link = h;
	}
	return q;
}