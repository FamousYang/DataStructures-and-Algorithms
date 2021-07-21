#include<stdio.h>
#include<stdlib.h>
//                                                      *****普通链表基本操作*****
//                                   采用不带头节点的创建方式，有无头结点关键是看头指针链接，二者操作并无大异
//普通链表结构
typedef int DataType;
typedef struct node {
	DataType data;
	struct node* link;
}LinkNode,*LinkList;

//链表无头结点初始化
void initListNoHead(LinkList& first) {
	first == nullptr;
}

//清空链表                                                  O(n),O(1)
void clearList(LinkList& first) {
	LinkNode* pnode = nullptr;
	while (first!=nullptr)
	{
		pnode = first;
		first = first->link;
		free(pnode);
	}
}

//求链表长度                                                   O(n),O(1)
int Length(LinkList& first) {
	LinkNode* pnode = first;
	int cnt = 0;
	while (pnode)
	{
		pnode = pnode->link;
		cnt++;
	}
	return cnt;
}

//查找给定值的节点                                             O(n),O(1)
LinkNode* Search(LinkList& first, DataType x) {
	LinkNode* pnode = first;
	while (pnode && pnode->data != x)
	{
		pnode = pnode->link;
	}
	return pnode;
}

//查找第i个节点的地址                                         O(n),O(1)
LinkNode* Locate(LinkList& first, int i) {
	if (i <= 0) {
		return nullptr;
	}
	LinkNode* pnode = first;
	int k = 1;
	while (pnode && k < i) {
		pnode = pnode->link;
		k++;
	}
	return pnode;
}

//插入x到链表第i个位置                                                 O(n),O(1)
bool Insert(LinkList& first, int i, DataType x) {
	if (i <= 0 || i > Length(first) + 1) {
		return false;
	}
	LinkNode* s = (LinkNode*)malloc(sizeof(LinkNode));
	s->data = x;
	if (first == NULL || i == 1) {
		s->link = first;
		first = s;
	}
	else {
		LinkNode* p = first,*pr = nullptr;
		int k = 1;
		while (p && k<i)
		{
			pr = p;
			p = p->link;
			k++;
		}
		s->link = p;
		pr->link = s;
	}
	return true;
}

//删除第i个节点并返回值                                                 O(n),O(1)
bool Remove(LinkList& first, int i, DataType& x) {
	LinkNode* q, * p, * pr;
	int k;
	if (i <= 0 || first == nullptr) {
		return false;
	}
	if (i == 1) {
		q = first;
		first = first->link;
	}
	else {
		p = first; pr = nullptr; k = 1;
		while (p && k < i)             //寻找目标节点，找到了用q指向，然后free(q)
		{
			pr = p;
			p = p->link;
			k++;
		}
		if (!p) {
			return false;
		}
		q = p; pr->link = p->link;
	}
	x = q->data; 
	free(q);
	return true;
}

//后插法建立链表                                                        O(n),O(1)
void createListR(LinkList& first, DataType A[], int n) {
	initListNoHead(first);
	LinkNode *s,*r = (LinkNode*)malloc(sizeof(LinkNode));
	r->data = A[0];
	for (int i = 1; i < n; i++) {
		s = (LinkNode*)malloc(sizeof(LinkNode));
		s->data = A[i];
		r->link = s;
		r = s;
	}
	r->link = nullptr;
}

//前插法建立链表                                                    O(n),O(1)
void createListF(LinkList& first, DataType A[], int n) {
	initListNoHead(first);
	LinkNode* s;
	first = (LinkNode*)malloc(sizeof(LinkNode));
	first->data = A[0];
	first->link = nullptr;
	for (int i = 1; i < n; i++) {
		s = (LinkNode*)malloc(sizeof(LinkNode));
		s->data = A[i];
		s->link = first;
		first = s;
	}
}

//输出所有元素                                                     O(n),O(1)
void printList(LinkList& first) {
	for (LinkNode* p = first; p != nullptr; p = p->link) {
		printf("%d ", p->data);
	}
	printf("\n");
}