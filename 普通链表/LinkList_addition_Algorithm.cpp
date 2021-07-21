#include<stdio.h>
#include<stdlib.h>
//                                                      *****��ͨ�������㷨*****
//                                              ��һ������Ŀ����ͷ�ڵ㣬�ڶ�������Ŀ����ͷ�ڵ�
//��ͨ����ṹ
typedef int DataType;
typedef struct node {
	DataType data;
	struct node* link;
}LinkNode, * LinkList;

//������ͷ����ʼ��
void initListNoHead(LinkList& first) {
	first == nullptr;
}
//������ͷ����ʼ��
void initListHead(LinkList& first) {
	first = (LinkNode*)malloc(sizeof(LinkNode));
	first->link = nullptr;
}

//                                                               ��һ����


//ȷ��Ԫ��ֵ���Ľڵ�                                                             O(n),O(1)
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

//ͳ���ж��ٸ�Ԫ��ֵΪx�Ľڵ�                                                         O(n),O(1)
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

//ɾ��һ��ֵ��С�Ľڵ�                                                          O(n),O(1)
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

//��ֵ��С�Ľڵ��ƶ���������ǰ��                                                O(n),O(1)
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

//�ҵ�������k���ڵ㣬���ֵ����1                                                           O(n),O(1)
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

//�ж�����������������ż��                                                 O(n),O(1)
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

//�����м�ڵ��ָ��      ͬ��������ɾ���м�ڵ�                                O(n),O(1)
LinkList midPoint(LinkList& L) {
	LinkList fast = L->link, slow = L->link;
	while (fast!= NULL && fast->link!=NULL)
	{
		slow = slow->link;
		fast = fast->link->link;
	}
	return slow;
}

//�ж������Ƿ����ĶԳƣ���ת��벿�֣�һһ�Աȼ��ɣ�                                 O(n),O(1)
bool isPalindrome(LinkList& L) {
	if (L == NULL || L->link == NULL) {
		return true;
	}
	LinkNode* p = L->link, * q = L->link,*s;
	while (q->link != NULL && q->link->link != NULL) {       //�ҵ��м�ڵ�
		p = p->link;
		q = q->link->link;
	}
	q = p->link;
	p->link = NULL;
	s = nullptr;                                             //��벿����ת

	while (q != NULL) {
		s = q->link;
		q->link = p;
		p = q;
		q = s;
	}
	s = p;
	q = L->link;
	bool res = true;                                        //��ʼ�Ƚ�
	while (q != NULL && p != NULL) {
		if (q->data != p->data) {
			res = false;
			break;
		}
		q = q->link;
		p = p->link;
	}

	p = s->link;
	s->link = NULL;                                         //�Ƚ���ϣ��ָ�����
	while (p != nullptr) {
		q = p->link;
		p->link = s;
		s = p;
		p = q;
	}
	return res;
}

//���潫A��B�Ľڵ����C��                                   O��n��,O(1)
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

//�ж������Ƿ��л����еĻ�����ڣ��������»��ж��㷨��                         O(n),O(1)
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

//�ɶ���ת����˳��  1-2-3-4    ->     2-1-4-3                       O(n),O(1)
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

//                                                              �ڶ�����

//����Ԫ��ѭ������k��λ��                                                     //O(n),O(1)
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
	}                                                //fast�����slow�ڵ���k+1����k������ᵽ������ǰ�漴��
	fast->link = L;
	L = slow->link;
	slow->link = NULL;
}

//�ɶ���ת����˳����ǿ�棬����k��ת������k=3    1-2-3-4-5-6             ->               3-2-1-6-5-4
LinkList k_reverse(LinkList& L, int k) {
	int n = k;
	LinkList p = L,s,h,t,q,r;                    //pָ�����������������s��ʱ�����ڵ㣬htָ����ʱ�����ͷβ��qrָ���������ͷβ
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