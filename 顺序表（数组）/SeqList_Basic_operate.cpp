#include<stdio.h>
#include<stdlib.h>

/*˳���̬�洢����
* #define maxSize 100
* typedef int DataType;
* typedef struct {
	DataType data[maxSize];
	int n;
} SeqList;
*/

//˳���̬�洢����                        
#define initSize 100
typedef int DataType;
typedef struct {
	DataType *data;
	int n,maxSize;
} SeqList;

//˳���ĳ�ʼ��                                                                 time O(1),O(1)
void initList(SeqList& L) {
	L.data = (DataType*)malloc(initSize * sizeof(DataType));
	if (!L.data) {
		printf("�洢�������\n");
		exit(1);
	}
	L.maxSize = initSize;
	L.n = 0;
}

//˳�����                                                                     time O(1),O(1)
int Length(SeqList& L) {
	return L.n;
}

//����ָ��Ԫ��λ��                                                                time O(n),O(1)
int Search(SeqList& L, DataType x) {
	for (int i = 0; i < L.n; i++) {
		if (L.data[i] == x) return i + 1;
	}
	return -1;
}

//���ζ�������A��n��Ԫ��ֵ������˳���                                              time O(n),O(1)
void createList(SeqList& L, DataType A[], int n) {
	initList(L);
	for (int i = 0; i < n; i++) {
		L.data[i] = A[i];
	}
	L.n = n;
}

//���������������Ԫ��ֵ                                                            time O(n),O(1)
void printList(SeqList& L) {
	for (int i = 0; i < L.n; i++) {
		printf("%d ", L.data[i]);
	}
	printf("\n");
}

//����һ��˳���                                                                   time O(n),O(1)
void copyList(SeqList& L, SeqList& L1) {
	L1.maxSize = L.maxSize;
	L1.n = L.n;
	L1.data = (DataType*)malloc(L1.maxSize * sizeof(DataType));
	if (!L1.data) {
		printf("�洢�������\n");
		exit(1);
	}
	for (int i = 0; i < L.n; i++) {
		L1.data[i] = L.data[i];
	}
}

//����Ԫ�ص���i��λ��                                                                   time O(n),O(1)
bool Insert(SeqList& L, DataType x, int i) {
	if (L.n == L.maxSize) {
		return false;
	}
	if (i<1 || i>L.n+1) {
		return false;
	}
	for (int j = L.n; j >= i; j--) {
		L.data[j] = L.data[j - 1];
	}
	L.data[i] = x;
	L.n++;
	return true;
}

//ɾ����i��Ԫ��                                                                         time O(n),O(1)
bool Remove(SeqList& L, int i, DataType& x) {
	if (L.n == 0) {
		return false;
	}
	if (i<1 || i>L.n) {
		return false;
	}
	x = L.data[i - 1];
	for (int j = i; j < L.n; j++) {
		L.data[j - 1] = L.data[j];
	}
	L.n--; return true;
}

//ȡ��i��Ԫ�ص���ֵ                                                                       time O(1),O(1)
DataType getValue(SeqList& L, int i) {
	if (i > 0 && i <= L.n) {
		return L.data[i - 1];
	}
	else {
		return -1;
	}
}

//���ݺ����ݣ�����80%����һ����С��25%��Сһ��                                                 time O(n),O(n)
void reallocate(SeqList& L) {
	int newSize;
	DataType* newArray;
	if (L.n > 0.8 * L.maxSize) {
		newSize = 2 * L.maxSize;
	}else if (L.n < 0.25 * L.maxSize) {
		newSize = L.maxSize/2;
	}else
	{
		return;
	}
	newArray = (DataType*)malloc(newSize * sizeof(DataType));
	for (int i = 0; i < L.n; i++) {
		newArray[i] = L.data[i];
	}
	L.data = newArray; 
	L.maxSize = newSize;
}