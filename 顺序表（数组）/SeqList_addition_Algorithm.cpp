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
	DataType* data;
	int n, maxSize;
} SeqList;

//ɾ����СԪ�ز����أ����һ��Ԫ�ز���λ                                        O(n),O(1)
bool deleteMin(SeqList& L, int& x) {
	if (L.n == 0){
		printf("��գ�ɾ��ʧ�ܣ�\n");
		return false;
	}
	x = L.data[0];
	int pos = 0;
	for (int i = 1; i < L.n; i++) {
		if (L.data[i] < x) {
			x = L.data[i];
			pos = i;
		}
	}
	L.data[pos] = L.data[L.n - 1];
	return true;
}

//ɾ�����е��ڸ���ֵ��Ԫ��                                                      O(n),O(1)
void deleteValue(SeqList& L, DataType x) {
	if (L.n == 0) {
		printf("��գ�ɾ��ʧ�ܣ�\n");
		return;
	}
	int k = -1;
	for (int i = 0; i < L.n; i++) {
		if (L.data[i] != x && ++k != i) {
			L.data[k] = L.data[i];
		}
	}
	L.n = k + 1;
}

//ɾ�������ڸ���ֵ�����ڵ�Ԫ��                                                 O(n),O(1)
bool deleteS_to_T(SeqList& L, DataType s, DataType t) {
	if (L.n == 0) {
		printf("��գ�ɾ��ʧ�ܣ�\n");
		return false;
	}
	if (s > t) {
		printf("����������ɾ��ʧ�ܣ�\n");
		return false;
	}
	int k = -1;
	for (int i = 0; i < L.n; i++) {
		if ((L.data[i]<s || L.data[i] >t) && ++k != i) {
			L.data[k] = L.data[i];
		}
	}
	L.n = k + 1;
	return true;
}

//ʹ������ͬ����ֻ����һ��                                                   O(n^2),O(1)
bool deleteSame(SeqList& L) {
	if (L.n == 0) {
		printf("��գ�ɾ��ʧ��!\n");
		return false;
	}
	int j,k = 0;
	for (int i = 1; i < L.n; i++) {
		for (j = 0; j <= k; j++) {
			if (L.data[i] == L.data[j]) {
				break;
			}
		}
		if (j > k && ++k != i) {
			L.data[k] = L.data[i];
		}
	}
	L.n = k + 1;
	return true;
}

//������3n/2�ıȽϴ������ҳ����������С�������Σ�
void findMaxMin(SeqList& L, DataType& max, DataType& min) {
	DataType* large = (DataType*)malloc((L.n + 1) / 2 * sizeof(DataType));
	DataType* small = (DataType*)malloc((L.n + 1) / 2 * sizeof(DataType));
	int i = 0;
	for (i = 0; i < L.n - 1; i += 2) {
		if (L.data[i] < L.data[i + 1]) {
			large[i / 2] = L.data[i + 1];
			small[i / 2] = L.data[i];
		}
		else {
			large[i / 2] = L.data[i];
			small[i / 2] = L.data[i + 1];
		}
	}
	if (L.n % 2 != 0) {
		large[i / 2] = small[i / 2 ] = L.data[L.n - 1];
	}
	for (int k = (int)(L.n + 1) / 4; k >= 1; k /= 2) {
		for (i = 0; i < k; i++) {
			large[i] = large[2 * i] > large[2 * i + 1] ? large[2 * i] : large[2 * i + 1];
			small[i] = small[2 * i] < small[2 * i + 1] ? small[2 * i] : small[2 * i + 1];
		}
	}
	max = large[0];
	min = small[0];
	free(large);
	free(small);
}

//��������в���Ԫ����Ȼ����                                                  //O(n),O(1)
bool Insert_sort(SeqList& L, DataType x) {
	if (L.n == L.maxSize) {
		return false;
	}
	int i, j;
	for (i = 0; i < L.n; i++) {
		if (L.data[i] > x) {
			break;
		}
	}
	for (j = L.n - 1; j >= i; j--) {
		L.data[j + 1] = L.data[j];
	}
	L.data[i] = x;
	return true;
}

//ɾ������������е���x��                                              //O(n),O(1)      
bool deleteSameValue(SeqList& L, DataType x) {
	if (L.n == 0) {
		return false;
	}
	int i, j, k,s;
	for (i = 0; i < L.n; i++) {
		if (L.data[i] == x) {
			break;
		}
	}
	if (i == L.n) {
		return false;
	}
	for (j = i+1; j < L.n; j++) {
		if (L.data[j] != x) {
			break;
		}
	}
	for (k = j, s = i; k < L.n; k++, s++) {
		L.data[s] = L.data[k];
	}
	L.n = L.n - j + i;
	return true;
}

//�ϲ�����������һ��                                                      //O(n),O(1)
bool Merge(SeqList& L1, SeqList& L2,SeqList& L3) {
	if (L1.n + L2.n > L3.maxSize) {
		return false;
	}
	int i = 0, j = 0, k = 0;
	while (i < L1.n && j < L2.n) {
		if (L1.data[i] <= L2.data[i]) {
			L3.data[k++] = L1.data[i++];
		}
		else {
			L3.data[k++] = L2.data[j++];
		}
	}
	while (i < L1.n) L3.data[k++] = L1.data[i++];
	while (j < L2.n) L3.data[k++] = L2.data[j++];
	L3.n = k;
	return true;
}

//���������������A����A��B���е�Ԫ��
void interScet(SeqList& L1, SeqList& L2) {
	int i = 0, j = 0, k = -1;
	while (i<L1.n && j<L2.n)
	{
		if (L1.data[i] < L2.data[i]) {
			i++;
		}
		else if (L1.data[i] > L2.data[i]) {
			j++;
		}
		else {
			if (k == -1) {
				L1.data[++k] = L1.data[i];
			}
			else if (L1.data[k] != L1.data[i]) {
				L1.data[++k] = L1.data[i];
			}
			i++; j++;
		}
	}
	L1.n = k + 1;
}

//ԭ������˳���                                                                            O(n),O(1)
void Reverse(SeqList& L, int left, int right) {
	DataType temp;
	while (left < right) {
		temp = L.data[left];
		L.data[left] = L.data[right];
		L.data[right] = temp;

		left++;
		right--;
	}
}

//��ĳһ��ֵ����ĳ��λ��ʱ������Ѱ�ҵ�һ�������������ģ�ͨ���������ƶ��ķ������
