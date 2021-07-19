#include<stdio.h>
#include<stdlib.h>

/*顺序表静态存储分配
* #define maxSize 100
* typedef int DataType;
* typedef struct {
	DataType data[maxSize];
	int n;
} SeqList;
*/

//顺序表动态存储分配                        
#define initSize 100
typedef int DataType;
typedef struct {
	DataType* data;
	int n, maxSize;
} SeqList;

//删除最小元素并返回，最后一个元素补空位                                        O(n),O(1)
bool deleteMin(SeqList& L, int& x) {
	if (L.n == 0){
		printf("表空，删除失败！\n");
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

//删除所有等于给定值的元素                                                      O(n),O(1)
void deleteValue(SeqList& L, DataType x) {
	if (L.n == 0) {
		printf("表空，删除失败！\n");
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

//删除所有在给定值区间内的元素                                                 O(n),O(1)
bool deleteS_to_T(SeqList& L, DataType s, DataType t) {
	if (L.n == 0) {
		printf("表空，删除失败！\n");
		return false;
	}
	if (s > t) {
		printf("参数不合理，删除失败！\n");
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

//使表中相同数据只存在一份                                                   O(n^2),O(1)
bool deleteSame(SeqList& L) {
	if (L.n == 0) {
		printf("表空，删除失败!\n");
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

//不多于3n/2的比较次数，找出最大数和最小数（分治）
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

//向有序表中插入元素仍然有序                                                  //O(n),O(1)
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

//删除有序表中所有等于x的                                              //O(n),O(1)      
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

//合并两个有序表成一个                                                      //O(n),O(1)
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

//两个有序表，操作后A里存放A和B共有的元素
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

//原地逆置顺序表                                                                            O(n),O(1)
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

//把某一类值放在某个位置时，可以寻找第一个不满足条件的，通过交换或移动的方法完成
