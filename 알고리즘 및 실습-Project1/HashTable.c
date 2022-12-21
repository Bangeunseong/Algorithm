//Hash Table ADT
//--------------------------------------분할 통치법(1)
#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)
//Data type --- Structure
/*typedef struct node {
	int key; struct node *next;
}node;
typedef struct List {
	node *start;
}List;
//----------------------------------
//--------General Method---------
node *getnode() {
	node *tmp = (node *)malloc(sizeof(node));
	tmp->next = NULL; tmp->key = -1;
	return tmp;
}
void initBucketArray(List *L, int M) {
	for (int i = 0; i < M; i++)L[i].start = getnode();
}
//-------------Search Function--------------
int findElementList(node *start, int key) {
	node *p = start->next; int i = 1;
	if (p == NULL) return 0;
	while (p != NULL) { if (p->key == key) return i; p = p->next; i++; }
	return 0;
}
int findElement(List *L, int key, int M) {
	int v = key % M;
	return findElementList(L[v].start, key);
}
//---------------Insert Item to BucketList-----------------
void InsertItemList(node *start, int key) {
	node *newnode = getnode(); newnode->key = key;
	newnode->next = start->next; start->next = newnode;
}
void InsertItem(List *L, int key, int M) {
	int v = key % M;
	InsertItemList(L[v].start, key);
}
//--------------Remove Item to BucketList-----------------
int removeElementList(node *start, int key) {
	node *p = start; int i = 1;
	while (p->next != NULL) {
		if (p->next->key == key) {
			node *del = p->next;
			p->next = p->next->next;
			free(del);
			return i;
		}
		p = p->next; i++;
	}
	return 0;
}
int removeElement(List *L, int key, int M) {
	int v = key % M;
	return removeElementList(L[v].start, key);
}
//-------------------Print List----------------------
void printList(List *L, int M) {
	for (int i = 0; i < M; i++) {
		node *p = L[i].start->next;
		while (p != NULL) { printf(" %d", p->key); p = p->next; }
	}
	printf("\n");
}
//-------------------Free List----------------------
void freeList(List *L, int M) {
	for (int i = 0; i < M; i++) {
		node *p = L[i].start;
		while (p != NULL) { node *del = p; p = p->next; free(del); }
	}
}
//Main
int main() {
	int M; scanf("%d", &M); getchar();
	List *L = (List *)malloc(sizeof(List)*M);
	initBucketArray(L, M);
	while (1) {
		char ch; int key; int v; scanf("%c", &ch);
		switch (ch) {
		case 'i': scanf("%d", &key); InsertItem(L, key, M); break;
		case 's': scanf("%d", &key); printf("%d\n", findElement(L, key, M)); break;
		case 'd': scanf("%d", &key); printf("%d\n", removeElement(L, key, M)); break;
		case 'p': printList(L, M); break;
		case 'e': freeList(L, M); free(L); return 0;
		}
		getchar();
	}
	return 0;
}*/
//------------------------------------------선형 조사법(2)
/*#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)
void initBucketArray(int **L, int M) {
	*L = (int *)malloc(sizeof(int)*M);
	for (int i = 0; i < M; i++) (*L)[i] = 0;
}
//---------------General Method----------------
//Hash Function
int getNextBucket(int v, int M, int i) { return (v + i) % M; }
//Overflow Exception
int overflowException(int *L, int M, int N) {
	int cnt = 0;
	for (int i = 0; i < M; i++) if (L[i] != 0) cnt++;
	if (cnt > N) return 1;
	return 0;
}
//--------------Search Function-------------------
int findElement(int *L, int M, int key) {
	int v = key % M;
	int i = 0;
	while (i < M) {
		int nextBucket = getNextBucket(v, M, i);
		if (L[nextBucket] == 0) return -1;
		else if (L[nextBucket] == key) { printf("%d ", nextBucket); return L[nextBucket]; }
		else i++;
	}
}
//---------------Insert Function------------------
void insertItem(int *L, int M, int N, int key) {
	if (overflowException(L, M, N)) return;
	int v = key % M;
	int i = 0;
	while (i < M) {
		int nextBucket = getNextBucket(v, M, i);
		if (L[nextBucket] == 0) { L[nextBucket] = key; printf("%d\n", nextBucket); return; }
		else { printf("C"); i++; }
	}
}
//Main
int main() {
	int *L = NULL; int M, N; scanf("%d %d", &M, &N); getchar();
	initBucketArray(&L, M);
	while (1) {
		char ch; int key; scanf("%c", &ch);
		switch (ch) {
		case 'i': scanf("%d", &key); insertItem(L, M, N, key); break;
		case 's': scanf("%d", &key); printf("%d\n", findElement(L, M, key)); break;
		case 'e': free(L); return 0;
		}
		getchar();
	}
}*/
//-----------------------------------------이중 해싱(3)
/*//Initialize BucketArray
void initBucketArray(int **L, int M) {
	*L = (int *)malloc(sizeof(int)*M);
	for (int i = 0; i < M; i++) (*L)[i] = 0;
}
//Hash Functions
int SecondHashFunction(int key, int Q) { return Q - (key % Q); }
int FirstHashFunction(int key, int M, int Q, int i) { return ((key % M + i * SecondHashFunction(key, Q))) % M; }
//Get The next Bucket
int getNextBucket(int key, int M, int Q, int i) { return FirstHashFunction(key, M, Q, i); }
//Overflow Exception
int overflowException(int *L, int M, int N) {
	int cnt = 0;
	for (int i = 0; i < M; i++) if (L[i] != 0) cnt++;
	if (cnt > N) return 1;
	return 0;
}
//----------------Search Func------------------
int findElement(int *L, int M, int Q, int key) {
	int i = 0;
	while (i < M) {
		int nextBucket = getNextBucket(key, M, Q, i);
		if (L[nextBucket] == 0) return -1;
		else if (L[nextBucket] == key) { printf("%d ", nextBucket); return L[nextBucket]; }
		else i++;
	}
}
//----------------Insert Func------------------
void insertItem(int *L, int M, int N, int Q, int key) {
	if (overflowException(L, M, N)) return;
	int i = 0;
	while (i < M) {
		int nextBucket = getNextBucket(key, M, Q, i);
		if (L[nextBucket] == 0) { L[nextBucket] = key; printf("%d\n", nextBucket); return; }
		else { printf("C"); i++; }
	}
}
//----------Print List-----------
void printList(int *L, int M) {
	for (int i = 0; i < M; i++) printf(" %d", L[i]);
	printf("\n");
}
//Main
int main() {
	int *L = NULL; int M, N, Q; scanf("%d %d %d", &M, &N, &Q); getchar();
	initBucketArray(&L, M);
	while (1) {
		char ch; int key; scanf("%c", &ch);
		switch (ch) {
		case 'i': scanf("%d", &key); insertItem(L, M, N, Q, key); break;
		case 's': scanf("%d", &key); printf("%d\n", findElement(L, M, Q, key)); break;
		case 'p': printList(L, M); break;
		case 'e': printList(L, M); free(L); return 0;
		}
		getchar();
	}
}*/
//-----------------------------------비활성화 방식(선형 조사법)
/*#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)
void InitHashTable(int **HashTable, int M) {
	*HashTable = (int *)malloc(sizeof(int)*M);
	for (int i = 0; i < M; i++) (*HashTable)[i] = 0;
}
int getNextBucket(int v, int M, int i) { return (v + i) % M; }
void InsertItem(int *HashTable, int M, int key) {
	int v = key % M;
	int i = 0;
	while (i < M) {
		int nextBucket = getNextBucket(v, M, i);
		if (HashTable[nextBucket] <= 0) { printf("%d\n", nextBucket); HashTable[nextBucket] = key; return; }
		else { printf("C"); i++; }
	}
}
int SearchKey(int *HashTable, int M, int key) {
	int v = key % M;
	int i = 0;
	while (i < M) {
		int nextBucket = getNextBucket(v, M, i);
		if (HashTable[nextBucket] == 0) return -1;
		else if (HashTable[nextBucket] == key) { printf("%d ", nextBucket); return HashTable[nextBucket]; }
		else i++;
	}
}
int DeactivateKey(int *HashTable, int M, int key) {
	int v = key % M;
	int i = 0;
	while (i < M) {
		int nextBucket = getNextBucket(v, M, i);
		if (HashTable[nextBucket] == 0) return -1;
		else if (HashTable[nextBucket] == key) { printf("%d ", nextBucket); int elem = HashTable[nextBucket]; HashTable[nextBucket] = -1; return elem; }
		else i++;
	}
}
int main() {
	int *HashTable = NULL; int M; scanf("%d", &M); getchar();
	InitHashTable(&HashTable, M);
	while (1) {
		char ch; int key; scanf("%c", &ch);
		switch (ch) {
		case 'i': scanf("%d", &key); InsertItem(HashTable, M, key); break;
		case 's': scanf("%d", &key); printf("%d\n", SearchKey(HashTable, M, key)); break;
		case 'd': scanf("%d", &key); printf("%d\n", DeactivateKey(HashTable, M, key)); break;
		case 'e': free(HashTable); return 0;
		}
		getchar();
	}
}*/