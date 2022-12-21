//자료구조 복습
//이중 연결리스트
//1
/*#include <stdio.h>
#pragma warning(disable : 4996)
typedef struct node {
	char val; struct node *next, *prev;
}node;
typedef struct list {
	node *H, *T; int size;
}list;
node *getnode() {
	node *tmp = (node *)malloc(sizeof(node));
	tmp->next = tmp->prev = NULL;
	return tmp;
}
void initList(list *L) {
	L->H = getnode(); L->T = getnode();
	L->H->next = L->T; L->T->prev = L->H;
	L->size = 0;
}
void add(list *L, int rank, char val) {
	if (rank < 1 || rank > L->size + 1) { printf("invalid position\n"); return; }
	node *newnode = getnode(); newnode->val = val;
	int index = 0; node *p = L->H;
	while (index < rank) { p = p->next; index++; }
	newnode->next = p; newnode->prev = p->prev;
	p->prev->next = newnode; p->prev = newnode; L->size++;
}
void delete(list *L, int rank) {
	if (rank < 1 || rank > L->size) { printf("invalid position\n"); return; }
	node *p = L->H; int index = 0;
	while (index < rank) { p = p->next; index++; }
	p->next->prev = p->prev; p->prev->next = p->next; L->size--;
	free(p);
}
char get(list L, int rank) {
	if (rank < 1 || rank > L.size) { printf("invalid position\n"); return '\0'; }
	node *p = L.H; int index = 0;
	while (index < rank) { p = p->next; index++; }
	return p->val;
}
void print(list L) {
	for (node *p = L.H->next; p != L.T; p = p->next) printf("%c", p->val);
	printf("\n");
}
void freeList(list *L) {
	node *p = L->H->next;
	while (p != L->T) { node *del = p; p->next->prev = p->prev; p->prev->next = p->next; p = p->next; free(del); }
}
int main() {
	list L; initList(&L);
	int n; scanf("%d", &n); getchar();
	for (int i = 0; i < n; i++) {
		char job, val, ch; int rank; scanf("%c", &job);
		switch (job) {
		case 'A': scanf("%d %c", &rank, &val); add(&L, rank, val); break;
		case 'D': scanf("%d", &rank); delete(&L, rank); break;
		case 'G': scanf("%d", &rank); ch = get(L, rank); if (ch != '\0') printf("%c\n", ch); break;
		case 'P': print(L); break;
		}
		getchar();
	}
	freeList(&L);
	return 0;
}*/
//트리 ADT
//2
/*#include <stdio.h>
#pragma warning (disable : 4996)
typedef struct node {
	int val; struct node *left, *right;
}node;
typedef struct tree {
	node *root;
}tree;
node *getnode() {
	node *tmp = (node *)malloc(sizeof(node));
	tmp->left = tmp->right = NULL;
	return tmp;
}
void initTree(tree *T) { T->root = NULL; }
node *findnode(node *root, int val) {
	if (root == NULL) return root;
	if (root->val == val) return root;
	node *left = findnode(root->left, val);
	if (left != NULL) return left;
	node *right = findnode(root->right, val);
	if (right != NULL) return right;
}
void inputnode(tree *T, int val) {
	int left, right; scanf("%d %d", &left, &right);
	if (T->root == NULL) { node *newnode = getnode(); newnode->val = val; T->root = newnode; }
	node *f = findnode(T->root, val);
	if (left != 0) { node *newnode = getnode(); newnode->val = left; f->left = newnode; }
	if (right != 0) { node *newnode = getnode(); newnode->val = right; f->right = newnode; }
}
void preorder(node *root) {
	if (root != NULL) {
		printf("%d ", root->val);
		preorder(root->left);
		preorder(root->right);
	}
}
int main() {
	tree t; initTree(&t);
	int n; scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		int val; scanf("%d", &val); inputnode(&t, val);
	}
	int m; scanf("%d", &m);
	for (int i = 0; i < m; i++) {
		char str[101]; scanf("%s", str);
		node *ptr = t.root;
		for (int j = 0; j < strlen(str) + 1; j++) {
			if (j == 0) printf(" %d", ptr->val);
			else {
				if (str[j - 1] == 'R') ptr = ptr->right;
				else ptr = ptr->left;
				if (ptr == NULL) break;
				else printf(" %d", ptr->val);
			}
		}
		printf("\n");
	}
	return 0;
}*/
//------------------------------------------------------------------------
//-------------------------우선순위 큐 logic----------------------------
//------------------------------------------------------------------------
//순서리스트로 구현 ( 삽입정렬 이용 )
/*#include <stdio.h>
#pragma warning(disable:4996)
typedef struct node {
	char key, val; struct node *next, *prev;
}node;
typedef struct Queue {
	node *f, *r;
}Queue;
node *getnode() {
	node *tmp = (node *)malloc(sizeof(node));
	tmp->next = tmp->prev = NULL;
	return tmp;
}
int isEmpty(Queue q) { 
	if (q.f == NULL && q.r == NULL) return 1;
	return 0;
}
void initQueue(Queue *q) { q->f = q->r = NULL; }
void insertItem(Queue *q, char key, char val) {
	node *newnode = getnode(); newnode->key = key; newnode->val = val;
	if (isEmpty(*q)) { q->f = q->r = newnode; }
	else {
		node *ptr = q->f;
		while (ptr->key < key && ptr != q->r) { ptr = ptr->next; }
		if (ptr == q->f && ptr == q->r) {
			if (ptr->key < key) { newnode->prev = ptr; newnode->next = ptr->next; ptr->next = newnode; q->r = newnode; }
			else { newnode->next = ptr; newnode->prev = ptr->prev; ptr->prev = newnode; q->f = newnode; }
		}
		else if (ptr == q->f) { newnode->next = ptr; ptr->prev = newnode; q->f = newnode; }
		else if(ptr == q->r){
			if (ptr->key < key) { newnode->prev = ptr; newnode->next = ptr->next; ptr->next = newnode; q->r = newnode; }
			else { newnode->next = ptr; newnode->prev = ptr->prev; ptr->prev->next = newnode; ptr->prev = newnode; }
		}
		else { newnode->next = ptr; newnode->prev = ptr->prev; ptr->prev->next = newnode; ptr->prev = newnode; }
	}
}
char removeMin(Queue *q) {
	node *del = q->f;
	char val = del->val;
	q->f = q->f->next;
	if (q->f != NULL) q->f->prev = NULL;
	else q->r = NULL;
	free(del);
	return val;
}
void print(Queue q) {
	for (node *p = q.f; p != NULL; p = p->next) printf("%c ", p->val);
	printf("\n");
}
void freenode(Queue *q) {
	node *p = q->f;
	while (p != NULL) { node *del = p; p = p->next; free(del); }
	q->f = q->r = NULL;
}
int main() {
	Queue q; initQueue(&q);
	insertItem(&q, 'f', 'F');
	insertItem(&q, 'b', 'B');
	insertItem(&q, 'e', 'E');
	insertItem(&q, 'd', 'D');
	insertItem(&q, 'a', 'A');
	print(q);
	char val = removeMin(&q);
	printf("%c\n", val);
	print(q);
	freenode(&q);
}*/
//우선 순위 큐(선택 정렬, 큐 ADT 이용)
/*#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <Windows.h>
#include <time.h>
#pragma warning(disable:4996)
typedef struct node {
	int val; struct node *next, *prev;
}node;
typedef struct Queue {
	node *f, *r;
}Queue;
node *getnode() {
	node *tmp = (node *)malloc(sizeof(node));
	tmp->next = tmp->prev = NULL;
	return tmp;
}
int isEmpty(Queue q) { if (q.f == NULL && q.r == NULL) return 1; return 0; }
void initQueue(Queue *q) { q->f = q->r = NULL; }
void enqueue(Queue *q, int val) {
	node *newnode = getnode(); newnode->val = val;
	if (isEmpty(*q)) { q->f = q->r = newnode; }
	else { newnode->prev = q->r; q->r->next = newnode; q->r = newnode; }
}
int dequeue(Queue *q) {
	node *del = q->r; node *p = q->r->prev;
	while (p != NULL) { 
		if (p->val > del->val) { del = p; }
		p = p->prev;
	}
	int val = del->val;
	if (del == q->f) { 
		q->f = q->f->next; 
		if(q->f != NULL) q->f->prev = NULL;
		else q->r = NULL;
	}
	else if (del == q->r) { 
		q->r = q->r->prev; 
		if(q->r != NULL) q->r->next = NULL;
		else q->f = NULL;
	}
	else { del->prev->next = del->next; del->next->prev = del->prev; }
	free(del);
	return val;
}
void print(Queue q) { for (node *p = q.f; p != NULL; p = p->next) printf("%d ", p->val); printf("\n"); }
int main() {
	Queue q; initQueue(&q);
	int size; scanf("%d", &size);
	int *x = (int *)malloc(sizeof(int)*size);

	srand((unsigned)time(NULL));
	for (int i = 0; i < size; i++) enqueue(&q, ((((long)rand() << 15) | rand()) % 1000000) + 1);

	LARGE_INTEGER ticksPerSec;
	LARGE_INTEGER start, end, diff;

	QueryPerformanceFrequency(&ticksPerSec);

	QueryPerformanceCounter(&start);
	for (int i = 0; i < size; i++) x[size - 1 - i] = dequeue(&q);
	QueryPerformanceCounter(&end);

	for (int i = 0; i < size; i++) printf("%d ", x[i]);
	printf("\n");
	diff.QuadPart = end.QuadPart - start.QuadPart;
	printf("%.10fms\n", ((double)diff.QuadPart / (double)ticksPerSec.QuadPart));
}*/
//우선 순위 큐 과제
//1 선택정렬(제자리 정렬 사용)
/*#include <stdio.h>
#pragma warning(disable:4996)
void input(int *x, int size) { for (int i = 0; i < size; i++) scanf("%d", x + i); }
void Selectionsort(int *x, int size) {
	for (int i = size - 1; i > 0; i--) {
		int maxLoc = i;
		for (int j = i; j >= 0; j--) { if (x[maxLoc] < x[j]) maxLoc = j; }
		int tmp = x[i]; x[i] = x[maxLoc]; x[maxLoc] = tmp;
	}
}
void print(int *x, int size) { for (int i = 0; i < size; i++) printf(" %d", x[i]); }
int main() {
	int size; scanf("%d", &size); int *x = (int *)malloc(sizeof(int)*size);
	input(x, size);
	Selectionsort(x, size);
	print(x, size);
	free(x);
}*/
//우선 순위 큐를 이용
/*#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <Windows.h>
#include <time.h>
#pragma warning(disable:4996)
typedef struct node {
	int val; struct node *next, *prev;
}node;
typedef struct Queue {
	node *f, *r;
}Queue;
node *getnode() {
	node *tmp = (node *)malloc(sizeof(node));
	tmp->next = tmp->prev = NULL;
	return tmp;
}
int isEmpty(Queue q) { if (q.f == NULL && q.r == NULL) return 1; return 0; }
void initQueue(Queue *q) { q->f = q->r = NULL; }
void enqueue(Queue *q, int val) {
	node *newnode = getnode(); newnode->val = val;
	if (isEmpty(*q)) { q->f = q->r = newnode; }
	else { newnode->prev = q->r; q->r->next = newnode; q->r = newnode; }
}
int dequeue(Queue *q) {
	node *del = q->r; node *p = q->r->prev;
	while (p != NULL) {
		if (p->val > del->val) { del = p; }
		p = p->prev;
	}
	int val = del->val;
	if (del == q->f) {
		q->f = q->f->next;
		if (q->f != NULL) q->f->prev = NULL;
		else q->r = NULL;
	}
	else if (del == q->r) {
		q->r = q->r->prev;
		if (q->r != NULL) q->r->next = NULL;
		else q->f = NULL;
	}
	else { del->prev->next = del->next; del->next->prev = del->prev; }
	free(del);
	return val;
}
void print(Queue q) { for (node *p = q.f; p != NULL; p = p->next) printf("%d ", p->val); printf("\n"); }
int main() {
	Queue q; initQueue(&q);
	int size; scanf("%d", &size);
	int *x = (int *)malloc(sizeof(int)*size);

	for (int i = 0; i < size; i++) { scanf("%d", x + i); enqueue(&q, x[i]); }
	for (int i = 0; i < size; i++) x[size - 1 - i] = dequeue(&q);
	for (int i = 0; i < size; i++) printf(" %d", x[i]);
}*/
//2 삽입정렬(제자리 정렬 사용)
/*#include <stdio.h>
#pragma warning(disable:4996)
void input(int *x, int size) { for (int i = 0; i < size; i++) scanf("%d", x + i); }
void Insertionsort(int *x, int size) {
	for (int i = 1; i < size; i++) {
		int val = x[i];
		int j = i - 1;
		while (j >= 0 && x[j] > val) { x[j + 1] = x[j]; j--; }
		x[j + 1] = val;
	}
}
void print(int *x, int size) { for (int i = 0; i < size; i++) printf(" %d", x[i]); }
int main() {
	int size; scanf("%d", &size); int *x = (int *)malloc(sizeof(int)*size);
	input(x, size);
	Insertionsort(x, size);
	print(x, size);
	free(x);
}*/
//3 선택정렬, 삽입정렬 시간 비교
//가상의 우선순위 큐를 이용한 것처럼 정렬 구현
/*#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#pragma warning(disable:4996)
void input(int *x, int size) { for (int i = 0; i < size; i++) { x[i] = ((((long) rand( ) << 15) | rand()) % 1000000) + 1; } }
void Selectionsort(int *x, int size) {
	for (int i = size - 1; i > 0; i--) {
		int maxLoc = i;
		for (int j = i - 1; j >= 0; j--) { if (x[j] > x[maxLoc]) maxLoc = j; }
		int tmp = x[i]; x[i] = x[maxLoc]; x[maxLoc] = tmp;
	}
}
void Insertionsort(int *x, int size) {
	for (int i = 1; i < size; i++) {
		int val = x[i];
		int j = i - 1;
		while (j >= 0 && x[j] > val) { x[j + 1] = x[j]; j--; }
		x[j + 1] = val;
	}
}
void print(int *x, int size) { for (int i = 0; i < size; i++) printf(" %d", x[i]); printf("\n"); }
int main() {
	int size; scanf("%d", &size);
	int *x = (int *)malloc(sizeof(int)*size);
	int *y = (int *)malloc(sizeof(int)*size);

	srand((unsigned)time(NULL));
	input(x, size); input(y, size);

	LARGE_INTEGER ticksPerSec;
	LARGE_INTEGER start, end, diff;

	QueryPerformanceFrequency(&ticksPerSec);
	
	QueryPerformanceCounter(&start);
	Selectionsort(x, size);
	QueryPerformanceCounter(&end);

	//print(x, size);
	diff.QuadPart = end.QuadPart - start.QuadPart;
	printf("%.10fms\n", ((double)diff.QuadPart / (double)ticksPerSec.QuadPart));

	QueryPerformanceCounter(&start);
	Insertionsort(y, size);
	QueryPerformanceCounter(&end);

	//print(y, size);
	diff.QuadPart = end.QuadPart - start.QuadPart;
	printf("%.10fms", ((double)diff.QuadPart / (double)ticksPerSec.QuadPart));
}*/
//---------------------------------------------------------------
//----------------------힙과 힙 정렬---------------------------
//---------------------------------------------------------------
//힙 정렬 성공!!!! (Final confirmation completed)
//정말 빠르다... 100만개 정렬 1.2초 걸림
/*#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#pragma warning(disable:4996)
typedef struct node {
	int key;
	struct node *left, *right, *parent;
}node;
typedef struct Tree {
	node *root, *last;
}Tree;
typedef struct Data {
	node *data; struct Data *next;
}Data;
typedef struct Queue {
	Data *f, *r;
}Queue;
//Tree에 집어넣을 노드 생성 함수
node *getnode() {
	node *tmp = (node *)malloc(sizeof(node));
	tmp->left = tmp->right = tmp->parent =  NULL; tmp->key = -1;
	return tmp;
}
//Queue에 집어넣을 노드를 포함하는 데이터 생성 함수
Data *getData() {
	Data *tmp = (Data *)malloc(sizeof(Data));
	tmp->next = NULL;
	return tmp;
}
//Tree 및 Queue initiation 함수
void initTree(Tree *T) { T->root = getnode(); T->last = NULL; }
void initQueue(Queue *q) { q->f = q->r = NULL; }
//Queue 삽입 삭제 함수
void enqueue(Queue *q, node *val) {
	Data *newdata = getData(); newdata->data = val;
	if (q->f == NULL && q->r == NULL) { q->f = q->r = newdata; }
	else { q->r->next = newdata; q->r = newdata; }
}
node *dequeue(Queue *q) {
	Data *del = q->f;
	q->f = q->f->next;
	node *data = del->data;
	if (q->f == NULL) q->r = NULL;
	free(del);
	return data;
}
//트리 높이 구하는 알고리즘, 노드 높이 구하는 알고리즘
int TreeHeight(node *root) {
	if (root->key == -1) return 0;
	int left = 1 + TreeHeight(root->left);
	int right = 1 + TreeHeight(root->right);
	if (left > right) return left;
	else return right;
}
int countNodeHeight(node *root) {
	if (root->parent == NULL) return 0;
	return 1 + countNodeHeight(root->parent);
}
//같은 레벨 노드 개수 구하는 알고리즘
int countCertainHeightNodes(node *root, int height) {
	if (root->key == -1) return 0;
	if (countNodeHeight(root) == height) return 1;
	int left = countCertainHeightNodes(root->left, height);
	int right = countCertainHeightNodes(root->right, height);
	return left + right;
}
//Tree의 Last를 갱신하는 함수(노드 입력 시 사용)
void advanceLast(Tree *T) {
	if (T->last == NULL) { T->last = T->root; return; }
	if (T->last != T->root) {
		while (T->last->parent != NULL) { if (T->last->parent->right != T->last) break; T->last = T->last->parent; }
		if(T->last->parent != NULL) T->last = T->last->parent->right;
	}
	while (T->last->key != -1) { T->last = T->last->left; }
}
void expandExternal(node *root) {
	node *left = getnode(), *right = getnode();
	left->parent = right->parent = root;
	root->left = left; root->right = right;
}
void upHeap(Tree *T, node *root) {
	if (T->root == root) return;
	if (root->key >= root->parent->key) return;
	int tmp = root->key; root->key = root->parent->key; root->parent->key = tmp;
	upHeap(T, root->parent);
}
void insertItem(Tree *T, int key) {
	advanceLast(T);
	T->last->key = key;
	expandExternal(T->last);
	upHeap(T, T->last);
}
void retreatLast(Tree *T) {
	if (T->last == T->root) { T->last = NULL; return; }
	while (T->last->parent != NULL) { if (T->last->parent->left != T->last) break; T->last = T->last->parent; }
	if (T->last->parent != NULL) { T->last = T->last->parent->left; }
	while (T->last->right->key != -1) { T->last = T->last->right; }
}
void reduceExternal(Tree *T, node *del) {
	node *parent = del->parent;

	node *sibling = del->parent->left;
	if (parent->parent == NULL) { T->root = sibling; sibling->parent = NULL; }
	else {
		node *g = parent->parent;
		sibling->parent = g;
		if (g->left == parent) g->left = sibling;
		else g->right = sibling;
	}
	free(parent);
	free(del);
}
void downHeap(node *root) {
	if (root->key == -1) return;
	if (root->left->key == -1 && root->right->key == -1) return;
	node *smaller = root->left;
	if (root->right->key != -1) {
		if (smaller->key > root->right->key) smaller = root->right;
	}
	if (root->key <= smaller->key) return;
	int tmp = root->key; root->key = smaller->key; smaller->key = tmp;
	downHeap(smaller);
}
int removeKey(Tree *T) {
	int r_key = T->root->key;
	node *del = T->last;
	T->root->key = del->key; del->key = -1;
	retreatLast(T);
	reduceExternal(T, del->right);
	downHeap(T->root);
	return r_key;
}
void preorder(node *root) {
	if (root->key == -1) return;
	printf("%d ", root->key);
	preorder(root->left);
	preorder(root->right);
}
int main() {
	Tree T; initTree(&T);
	int size; scanf("%d", &size); int *x = (int *)malloc(sizeof(int)*size);
	
	srand((unsigned)time(NULL));
	for (int i = 0; i < size; i++) { x[i] = ((((long)rand() << 15) | rand()) % 1000000) + 1; insertItem(&T, x[i]); }

	LARGE_INTEGER ticksPerSec;
	LARGE_INTEGER start, end, diff;

	QueryPerformanceFrequency(&ticksPerSec);
	QueryPerformanceCounter(&start);
	int i = 0;
	while (T.root->key != -1) { x[i++] = removeKey(&T); }
	QueryPerformanceCounter(&end);
	
	diff.QuadPart = end.QuadPart - start.QuadPart;
	printf("%.10fms\n", ((double)diff.QuadPart / (double)ticksPerSec.QuadPart));
}*/
//제자리 힙 정렬 (배열 사용)
/*#include <stdio.h>
#pragma warning(disable:4996)
int H[100], n = 0;
void upHeap(int last) {
	if (last == 1) return;
	if (H[last] <= H[last / 2]) return;
	int tmp = H[last]; H[last] = H[last / 2]; H[last / 2] = tmp;
	upHeap(last / 2);
}
void insertItem(int key) {
	if (n >= 99) return;
	H[++n] = key;
	upHeap(n);
}
void downHeap(int root) {
	if (n == 1) return;
	if(root >= n) return;
	int bigger = 2 * root;
	if(2 * root + 1 <= n) {
		if (H[bigger] < H[2 * root + 1]) bigger = 2 * root + 1;
	}
	if (H[bigger] >= H[2 * root + 1]) return;
	int tmp = H[bigger]; H[bigger] = H[root]; H[root] = tmp;
	downHeap(bigger);
}
int removeMax() {
	int key = H[1];
	H[1] = H[n--];
	downHeap(1);
	return key;
}
void printHeap() {
	for (int i = 1; i <= n; i++) printf(" %d", H[i]);
	printf("\n");
}
int main() {
	while (1) {
		char job; int key; scanf("%c", &job);
		switch (job) {
		case 'i': scanf("%d", &key); insertItem(key); break;
		case 'd': printf("%d\n", removeMax()); break;
		case 'p': printHeap(); break;
		case 'q': return;
		default: printf("Wrong Input!\n"); break;
		}
		getchar();
	}
	return 0;
}*/
//상향식 힙생성
/*#include <stdio.h>
#pragma warning(disable:4996)
int H[100] = { 0, }, n = 0;
void downHeap(int root) {
	if (n == 1) return;
	if(root >= n) return;
	int bigger = root * 2;
	if (2 * root + 1 <= n) {
		if (H[bigger] < H[2 * root + 1]) bigger = 2 * root + 1;
	}
	if (H[root] >= H[bigger]) return;
	int tmp = H[root]; H[root] = H[bigger]; H[bigger] = tmp;
	downHeap(bigger);
}
void rbuildHeap(int index) {
	if (index > n) return;
	rbuildHeap(2 * index);
	rbuildHeap(2 * index + 1);
	downHeap(index);
}
void printHeap() {
	for (int i = 1; i <= n; i++) printf(" %d", H[i]);
}
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", H + i);
	rbuildHeap(1);
	printHeap();
}*/

//연결리스트를 이용한 상향식 힙생성

#include <stdio.h>
#pragma warning(disable:4996)
/*typedef struct node {
	int key; struct node *left, *right, *parent;
}node;
typedef struct Tree {
	node *root, *last;
}Tree;
node *getnode() {
	node *tmp = (node *)malloc(sizeof(node));
	tmp->key = -1;
	tmp->left = tmp->right = tmp->parent = NULL;
	return tmp;
}
void initTree(Tree *T) { T->root = getnode(); T->last = NULL; }
void expandExternal(node *last) {
	node *left = getnode(); node *right = getnode();
	left->parent = right->parent = last;
	last->left = left; last->right = right;
}
void advanceLast(Tree *T) {
	if (T->last == NULL) { T->last = T->root; return; }
	while (T->last->parent != NULL) { if (T->last->parent->right != T->last) break; T->last = T->last->parent; }
	if (T->last != T->root) {
		if (T->last->parent != NULL) T->last = T->last->parent->right;
	}
	while (T->last->key != -1) T->last = T->last->left;
}
void LevelExpand(node *root) {
	if (root->key == -1) { expandExternal(root); return; }
	LevelExpand(root->left);
	LevelExpand(root->right);
}
void insertItem(Tree *T, int key) {
	advanceLast(T);
	if (T->last->left == NULL && T->last->right == NULL) LevelExpand(T->root);
	T->last->key = key;
}
void downHeap(node *root) {
	if (root->key == -1) return;
	if (root->left->key == -1 && root->right->key == -1) return;
	node *smaller = root->left;
	if (root->right->key != -1) {
		if (smaller->key > root->right->key) smaller = root->right;
	}
	if (root->key <= smaller->key) return;
	int tmp = root->key; root->key = smaller->key; smaller->key = tmp;
	downHeap(smaller);
}
void rBuildHeap(node *root) {
	if (root->left != NULL && root->right != NULL) {
		rBuildHeap(root->left);
		rBuildHeap(root->right);
		downHeap(root);
	}
}
void convertToCompleteBinaryTree(Tree *T) {
	int size; scanf("%d", &size);
	for (int i = 0; i < size; i++) { insertItem(T, ((((long)rand() << 15) | rand()) % 1000000) + 1); }
}
void BuildHeap(Tree *T) {
	convertToCompleteBinaryTree(T);
	rBuildHeap(T->root);
}
void preorder(node *root) {
	if (root->key == -1) return;
	printf("%d ", root->key);
	preorder(root->left);
	preorder(root->right);
}
int main() {
	srand((unsigned)time(NULL));
	Tree T; initTree(&T);
	BuildHeap(&T);
}


//과제 1
//배열을 이용하여 힙 정렬 구현
//1
//#include <stdio.h>
//#pragma warning(disable:4996)
//int H[100] = { 0, }, n = 0;
//void upHeap(int last) {
//	if (last == 1) return;
//	if (H[last] <= H[last / 2]) return;
//	int tmp = H[last]; H[last] = H[last / 2]; H[last / 2] = tmp;
//	upHeap(last / 2);
//}
//void insertItem(int key) {
//	if (n >= 99) return;
//	H[++n] = key;
//	upHeap(n);
//	printf("0\n");
//}
//void downHeap(int root) {
//	if (n == 1) return;
//	if(root >= n) return;
//	int bigger = root * 2;
//	if (2 * root + 1 <= n) {
//		if (H[bigger] < H[2 * root + 1]) bigger = 2 * root + 1;
//	}
//	if (H[root] >= H[bigger]) return;
//	int tmp = H[root]; H[root] = H[bigger]; H[bigger] = tmp;
//	downHeap(bigger);
//}
//int removeMax() {
//	int key = H[1];
//	H[1] = H[n--];
//	downHeap(1);
//	return key;
//}
//void printHeap() {
//	for (int i = 1; i <= n; i++) printf(" %d", H[i]);
//	printf("\n");
//}
//int main() {
//	while (1) {
//		char job; int key; scanf("%c", &job);
//		switch (job) {
//		case 'i': scanf("%d", &key); insertItem(key); break;
//		case 'd': printf("%d\n", removeMax()); break;
//		case 'p': printHeap(); break;
//		case 'q': return;
//		default: printf("Wrong Input!\n"); break;
//		}
//		getchar();
//	}
//	return 0;
//}
//상향식 힙생성
//2
*/
/*#include <stdio.h>
#pragma warning(disable:4996)
int H[100] = { 0, }, n = 0;
void downHeap(int root) {
	if (n == 1) return;
	if(root >= n) return;
	int bigger = root * 2;
	if (2 * root + 1 <= n) {
		if (H[bigger] < H[2 * root + 1]) bigger = 2 * root + 1;
	}
	if (H[root] >= H[bigger]) return;
	int tmp = H[root]; H[root] = H[bigger]; H[bigger] = tmp;
	downHeap(bigger);
}
void rbuildHeap(int index) {
	if (index > n) return;
	rbuildHeap(2 * index);
	rbuildHeap(2 * index + 1);
	downHeap(index);
}
void printHeap() {
	for (int i = 1; i <= n; i++) printf(" %d", H[i]);
}
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", H + i);
	rbuildHeap(1);
	printHeap();
}*/
//과제 2
//1, 2 힙정렬 유일 키 and 중복 키
/*
#include <stdio.h>
#pragma warning(disable:4996)
int H[100] = { '\0' }; int n = 0;
void upHeap(int last) {
	if (last == 1) return;
	if (H[last] < H[last / 2]) return;
	int tmp = H[last]; H[last] = H[last / 2]; H[last / 2] = tmp;
	upHeap(last / 2);
}
void InsertItem(int key) {
	if (n >= 99) return;
	H[++n] = key;
	upHeap(n);
}
void downHeap(int root, int last) {
	if (root >= last) return;
	int bigger = 2 * root;
	if (bigger > last) return;
	if (2 * root + 1 <= last) {
		if (H[bigger] < H[2 * root + 1]) bigger = 2 * root + 1;
	}
	if (H[bigger] < H[root]) return;
	int tmp = H[bigger]; H[bigger] = H[root]; H[root] = tmp;
	downHeap(bigger, last);
}
void inplaceHeapSort() {
	for (int i = n; i > 1; i--) {
		int tmp = H[1]; H[1] = H[i]; H[i] = tmp;
		downHeap(1, i - 1);
	}
}
void printArray() {
	for (int i = 1; i <= n; i++) printf(" %d", H[i]);
}
int main() {
	int size; scanf("%d", &size);
	for (int i = 1; i <= size; i++) { int key; scanf("%d", &key); InsertItem(key); }
	inplaceHeapSort();
	printArray();
}
*/
//힙정렬 과제 - 1
/*#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#pragma warning(disable:4996)
//부모노드로 올라가면서 키의 value를 비교하는 upHeap함수
void upHeap(int *list, int last) {
	if (last == 1) return;
	if (list[last] > list[last / 2]) return;
	int tmp = list[last]; list[last] = list[last / 2]; list[last / 2] = tmp;
	upHeap(list, last / 2);
}
//키를 리스트에 입력하는 함수
void Insertkey(int *list, int index, int key) { 
	list[index] = key;
	upHeap(list, index);
}
//부모노드에서 자식노드로 내려가면서 value를 비교 및 swap하는 downHeap함수
void downHeap(int *list, int root, int last) {
	if (last == 1) return;					//리스트의 크기를 1로 해석하면 된다
	int smaller = 2 * root;
	if (smaller > last) return;			//부모의 왼쪽노드가 없는 경우(external node)
	if (2 * root + 1 <= last) {
		if (list[smaller] > list[2 * root + 1]) smaller = 2 * root + 1;
	}
	if (list[root] < list[smaller]) return;
	int tmp = list[root]; list[root] = list[smaller]; list[smaller] = tmp;	//swapping 작업
	downHeap(list, smaller, last);
}
//리스트에 저장된 첫 노드를 미리 저장하고 마지막노드와 바꾸면서 downHeap 실행(이를 통해 두번째로 작은 노드 앞으로 보냄)
int removeMin(int *list, int *last) {
	int key = list[1];
	list[1] = list[*last];
	(*last)--;
	downHeap(list, 1, *last);
	return key;
}
int *buildList(int size, int min, int max) {
	int *list = (int *)malloc(sizeof(int)*size);
	for (int i = 0; i < size; i++) { list[i] = ((((long)rand() << 15) | rand()) % 1000000) % (max - min + 1) + min; }
	return list;
}
void printList(int *list, int size) {
	for (int i = 0; i < size; i++) { printf(" %d", list[i]); }
	printf("\n");
}
//buffer라는 리스트를 만들어 리스트에 있는 자료를 upHeap을 이용하면서 저장
//또한 removemin을 통해 첫 노드를 제거하면서 k번째 작은 수를 구할 수 있다.
int findKthSmallest(int *list, int size, int k) {
	int *buffer = (int *)malloc(sizeof(int)*(size + 1)); int last = 0;
	for (int i = 1; i <= size; i++, last++) Insertkey(buffer, i, list[i - 1]);
	int key = 0;
	for (int i = 0; i < k; i++) { key = removeMin(buffer, &last); }
	free(buffer);
	return key;
}
int main() {
	srand((unsigned)time(NULL));
	int *list1 = NULL; int size1 = 10;
	list1 = buildList(size1, 1, 1000000);
	printList(list1, size1);
	int output[4];
	for (int i = 1; i < 4; i++)
		output[i] = findKthSmallest(list1, size1, i);
	printf("Key1 = %d, Key2 = %d, Key3 = %d\n", output[1], output[2], output[3]);

	int *list2 = NULL; int size2 = 100000;
	list2 = buildList(size2, 1, 1000000);

	int karray[4] = { 1,100,99900,99999 };
	LARGE_INTEGER ticksPerSec;
	QueryPerformanceFrequency(&ticksPerSec);

	for (int i = 0; i < 4; i++) {
		LARGE_INTEGER start, end, diff;
		QueryPerformanceCounter(&start);
		int key = findKthSmallest(list2, size2, karray[i]);
		QueryPerformanceCounter(&end);

		diff.QuadPart = end.QuadPart - start.QuadPart;
		printf("Key of karray[%d] = %d, Time = %.10fms\n", i, key, ((double)diff.QuadPart / (double)ticksPerSec.QuadPart));
	}
	free(list1); free(list2);
}*/
//-----------------------------------------------------------
//-----------------------합병 정렬--------------------------
//-----------------------------------------------------------
//합병정렬 구현 완료!!!(O(n*logn) 실행 시간)
/*#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#pragma warning(disable:4996)
typedef struct node {
	int key; struct node *next;
}node;
node *getnode() {
	node *tmp = (node *)malloc(sizeof(node));
	tmp->next = NULL;
	return tmp;
}
void addLast(node **list, int key) {
	node *newnode = getnode(); newnode->key = key;
	if (*list == NULL) *list = newnode;
	else {
		node *p = *list; while (p->next != NULL) p = p->next;
		p->next = newnode;
	}
}
int removeFirst(node **list) {
	node *del = *list;
	int key = del->key;
	*list = (*list)->next;
	free(del);
	return key;
}
void print(node *list) {
	if (list == NULL) return;
	printf(" %d", list->key);
	print(list->next);
}
void partition(node **list, int size, node **L1, node **L2) {
	node *p = *list; *L1 = *list; int i = 0;
	while (i < size - 1) { p = p->next; i++; }
	*L2 = p->next; p->next = NULL;
}
node *merge(node **L1, node **L2) {
	node *list = NULL;
	while (*L1 != NULL && *L2 != NULL) {
		if ((*L1)->key <= (*L2)->key) addLast(&list, removeFirst(L1));
		else addLast(&list, removeFirst(L2));
	}
	while (*L1 != NULL) addLast(&list, removeFirst(L1));
	while (*L2 != NULL) addLast(&list, removeFirst(L2));
	return list;
}
void mergeSort(node **list, int size) {
	if (size > 1) {
		node *L1 = NULL, *L2 = NULL;
		partition(list, size / 2, &L1, &L2);
		mergeSort(&L1, size / 2);
		mergeSort(&L2, size / 2 + size % 2);
		*list = merge(&L1, &L2);
	}
}
int main() {
	node *list = NULL;
	srand((unsigned)time(NULL));
	int size; scanf("%d", &size);
	for (int i = 0; i < size; i++) { addLast(&list, ((((long)rand() << 15) | rand()) % 1000000) + 1); }
	
	LARGE_INTEGER ticksPerSec;
	LARGE_INTEGER start, end, diff;

	QueryPerformanceFrequency(&ticksPerSec);
	QueryPerformanceCounter(&start);
	mergeSort(&list, size);
	QueryPerformanceCounter(&end);

	diff.QuadPart = end.QuadPart - start.QuadPart;
	printf("%.10fms\n", ((double)diff.QuadPart / (double)ticksPerSec.QuadPart));

	return 0;
}*/
//합병정렬 실습 - 1
/*#include <stdio.h>
#pragma warning(disable:4996)
typedef struct node {
	int key; struct node *next;
}node;
node *getnode() {
	node *tmp = (node *)malloc(sizeof(node));
	tmp->next = NULL;
	return tmp;
}
void addLast(node **L, int key) {
	node *newnode = getnode(); newnode->key = key;
	if (*L == NULL) *L = newnode;
	else {
		node *p = *L;
		while (p->next != NULL) p = p->next;
		p->next = newnode;
	}
}
int removeFirst(node **L) {
	node *del = *L;
	int key = del->key;
	*L = (*L)->next;
	free(del);
	return key;
}
void partition(node **L, int size, node **L1, node **L2) {
	*L1 = *L; node *p = *L; int i = 0;
	while (i < size - 1) { p = p->next; i++; }
	*L2 = p->next; p->next = NULL;
}
node *merge(node **L1, node **L2) {
	node *list = NULL;
	while (*L1 != NULL && *L2 != NULL) {
		if ((*L1)->key < (*L2)->key) addLast(&list, removeFirst(L1));
		else addLast(&list, removeFirst(L2));
	}
	while (*L1 != NULL) addLast(&list, removeFirst(L1));
	while (*L2 != NULL) addLast(&list, removeFirst(L2));
	return list;
}
void mergeSort(node **L, int size) {
	if (size > 1) {
		node *L1 = NULL, *L2 = NULL;
		partition(L, size / 2, &L1, &L2);
		mergeSort(&L1, size / 2);
		mergeSort(&L2, size / 2 + size % 2);
		*L = merge(&L1, &L2);
	}
}
void printList(node *L) {
	for (node *p = L; p != NULL; p = p->next) printf(" %d", p->key);
	printf("\n");
}
void freenode(node **L) {
	while (*L != NULL) { node *del = *L; *L = (*L)->next; free(del); }
}
int main() {
	node *L = NULL;
	srand((unsigned)time(NULL));
	int size; scanf("%d", &size);
	for (int i = 0; i < size; i++) { int key; scanf("%d", &key); addLast(&L, key); }
	mergeSort(&L, size);
	printList(L);
	freenode(&L);
	return 0;
}*/
//----------------------------------------------------
//---------------------퀵 정렬-----------------------
//----------------------------------------------------
/*#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#pragma warning(disable:4996)
typedef struct node{
	int key; struct node *next;
}node;
node *getnode() {
	node *tmp = (node *)malloc(sizeof(node));
	tmp->next = NULL; return tmp;
}
void addLast(node **list, int key) {
	node *newnode = getnode(); newnode->key = key;
	if (*list == NULL) { *list = newnode; }
	else {
		node *p = *list;
		while (p->next != NULL) p = p->next;
		p->next = newnode;
	}
}
int removeFirst(node **list) {
	node *del = *list;
	int key = del->key;
	*list = (*list)->next;
	free(del);
	return key;
}
int GetSize(node *list) {
	int cnt = 0; node *p = list;
	while (p != NULL) { p = p->next; cnt++; }
	return cnt;
}
int GetPivot(node *list) {
	int size = GetSize(list);
	return size / 2 - 1;
}
int GetPivotkey(node *list, int pivot) {
	int i = 0; node *p = list;
	while (i < pivot) { p = p->next; i++; }
	return p->key;
}
void partition(node **list, int pivot, node **LT, node **EQ, node **GT) {
	int key = GetPivotkey(*list, pivot);
	while (*list != NULL) {
		int elem = removeFirst(list);
		if (elem < key) addLast(LT, elem);
		else if (elem == key) addLast(EQ, elem);
		else addLast(GT, elem);
	}
}
void merge(node **list, node **LT, node **EQ, node **GT) {
	while (*LT != NULL) { addLast(list, removeFirst(LT)); }
	while (*EQ != NULL) { addLast(list, removeFirst(EQ)); }
	while (*GT != NULL) { addLast(list, removeFirst(GT)); }
}
void QuickSort(node **list) {
	if (*list != NULL) {
		node *LT = NULL, *EQ = NULL, *GT = NULL;
		int pivot = GetPivot(*list);
		partition(list, pivot, &LT, &EQ, &GT);
		QuickSort(&LT);
		QuickSort(&GT);
		merge(list, &LT, &EQ, &GT);
	}
}
void print(node *list) {
	if (list == NULL) return;
	printf(" %d", list->key);
	print(list->next);
}
int main() {
	node *list = NULL;
	srand((unsigned)time(NULL));
	int size; scanf("%d", &size);
	for (int i = 0; i < size; i++) { addLast(&list, ((((long)rand() << 15) | rand()) % 1000000) + 1); }

	LARGE_INTEGER ticksPerSec;
	LARGE_INTEGER start, end, diff;

	QueryPerformanceFrequency(&ticksPerSec);
	QueryPerformanceCounter(&start);
	QuickSort(&list);
	QueryPerformanceCounter(&end);

	diff.QuadPart = end.QuadPart - start.QuadPart;
	printf("%.10fms\n", ((double)diff.QuadPart / (double)ticksPerSec.QuadPart));
	
}*/
//퀵 정렬 실습 - 1
/*#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#pragma warning(disable:4996)
int findpivot(int root, int last) {
	int pivot = rand() % (last - root + 1) + root;
	return pivot;
}
int inplacePartition(int *x, int root, int last, int pivot) {
	int key = x[pivot - 1];
	int storage = x[pivot - 1]; x[pivot - 1] = x[last - 1]; x[last - 1] = storage;
	int i = root - 1; int j = last - 2;
	while (i <= j) {
		while (i <= j && x[i] <= key)
			i++;
		while (j >= i && x[j] >= key)
			j--;
		if (i < j) { int tmp = x[i]; x[i] = x[j]; x[j] = tmp; }
	}
	int tmp = x[i]; x[i] = x[last - 1]; x[last - 1] = tmp;
	return i + 1;
}
void inplaceQuickSort(int *x, int root, int last) {
	if (root >= last) return;
	int pivot = findpivot(root, last);
	int center = inplacePartition(x, root, last, pivot);
	inplaceQuickSort(x, root, center - 1);
	inplaceQuickSort(x, center + 1, last);
}
void printList(int *x, int size) {
	for (int i = 0; i < size; i++) printf(" %d", x[i]);
}
int main() {
	srand((unsigned)time(NULL));
	int *x = NULL; int size; scanf("%d", &size);
	x = (int *)malloc(sizeof(int)*size);
	for (int i = 0; i < size; i++) scanf("%d", x + i);
	inplaceQuickSort(x, 1, size);
	printList(x, size);
}*/ 
//퀵 정렬 과제-2
/*#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#pragma warning(disable:4996)
int n = 100000; int Limits[] = { 1,100,500,1000 };
int Limit = 1; int mode = 0;
enum { DETERMINISTIC_1, DETERMINISTIC_3, RANDOMIZED_1, RANDOMIZED_3 };

int *createArray() {
	int *arr = (int *)malloc(sizeof(int)*n);
	for (int i = 0; i < n; i++) arr[i] = ((((long)rand() << 15) | rand()) % 1000000) + 1;
	return arr;
}
int *copyArray(int *arr, int size) {
	int *carr = (int *)malloc(sizeof(int)*size);
	for (int i = 0; i < size; i++) carr[i] = arr[i];
	return carr;
}
void InsertionSort(int *arr, int size) {
	for (int i = 1; i < size; i++) {
		int key = arr[i];
		int j = i - 1;
		while (j >= 0 && arr[j] > key) { arr[j + 1] = arr[j]; j--; }
		arr[j + 1] = key;
	}
}
void printArray(int *arr, int size) {
	for (int i = 0; i < size; i++) printf("%d ", arr[i]);
	printf("\n");
}
int findMedianPivot(int l, int r) {
	int random[3];
	for (int i = 0; i < 3; i++) random[i] = rand() % (r - l + 1) + l;

	int min = random[0], secondmin;
	for (int i = 1; i < 3; i++) {
		if (random[i] < min) { secondmin = min; min = random[i]; }
		else { if (i == 1) secondmin = random[i]; else { if (secondmin > random[i]) secondmin = random[i]; } }
	}
	return secondmin;
}
int findPivot(int l, int r) {
	if (mode == DETERMINISTIC_1) return r;
	if (mode == RANDOMIZED_1) return rand() % (r - l + 1) + l;
	if (r - l == 1) return l;
	switch (mode) {
	case DETERMINISTIC_3: return (l + r) / 2;
	case RANDOMIZED_3: return findMedianPivot(l, r);
	}
}
int inPlacePartition(int *arr, int l, int r, int pivot) {
	int pivotkey = arr[pivot];
	int tmp = arr[pivot]; arr[pivot] = arr[r]; arr[r] = tmp;
	int i = l, j = r - 1;
	while (i <= j) {
		while (i <= j && arr[i] <= pivotkey) i++;
		while (i <= j && arr[j] >= pivotkey) j--;
		if (i < j) { int tmp = arr[i]; arr[i] = arr[j]; arr[j] = tmp; }
	}
	tmp = arr[i]; arr[i] = arr[r]; arr[r] = tmp;
	return i;
}
void rQuickSort(int *arr, int l, int r) {
	if (r - l >= Limit) {
		int pivot = findPivot(l, r);
		int med = inPlacePartition(arr, l, r, pivot);
		rQuickSort(arr, l, med - 1);
		rQuickSort(arr, med + 1, r);
	}
}
void QuickSort(int *arr, int size) {
	rQuickSort(arr, 0, size - 1);
	if (Limit > 1) InsertionSort(arr, size);
}
int main() {
	srand((unsigned)time(NULL));
	int *arr = createArray();

	LARGE_INTEGER ticksPerSec;
	LARGE_INTEGER start, end, diff;
	QueryPerformanceFrequency(&ticksPerSec);
	
	printf("Limit\tDETERMINISTIC_1\tDETERMINISTIC_3\tRANDOMIZED_1\tRANDOMIZED_3\n");
	for (int i = 0; i < 4; i++) {
		Limit = Limits[i]; printf("%d\t", Limit);
		for (int j = 0; j < 4; j++) {
			int *carr = copyArray(arr, n); mode = j;
			QueryPerformanceCounter(&start);
			QuickSort(carr, n);	
			QueryPerformanceCounter(&end);
			diff.QuadPart = end.QuadPart - start.QuadPart;
			printf("%.10fms\t", ((double)diff.QuadPart / (double)ticksPerSec.QuadPart));
			free(carr);
		}
		printf("\n");
	}
	free(arr);
}*/
//사전
//1, 2
/*#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)
int rfindlessthankeyMax(int *x, int n, int l, int r, int key) {
	if (l > r) { 
		if (l == 0 || r == n - 1) return r;
		if (x[l] > key) return l - 1; else return l;
	}
	int median = (l + r) / 2;
	if (x[median] == key) return median;
	else if (x[median] > key) return rfindlessthankeyMax(x, n, l, median - 1, key);
	else return rfindlessthankeyMax(x, n, median + 1, r, key);
}
int findlessthankeyMax(int *x, int n, int key) {
	int l = 0, r = n - 1;
	while (l < r) {
		int median = (l + r) / 2;
		if (x[median] == key) return median;
		else if (x[median] > key) r = median - 1;
		else l = median + 1;
	}
	if (x[l] < key) return l + 1; else return l;
}
int main() {
	int n, key; scanf("%d%d", &n, &key);
	int *x = (int *)malloc(sizeof(int)*n);
	for (int i = 0; i < n; i++) scanf("%d", x + i);
	int index1 = rfindlessthankeyMax(x, n, 0, n - 1, key);
	int index2 = findlessthankeyMax(x, n, key);
	printf(" %d %d", index1, index2);
	free(x);
}*/
//3
/*#include <stdio.h>
#pragma warning(disable:4996)
int rNumberGame(int l, int r) {
	if (l == r) return l;
	char note; scanf("%c", &note);
	int median = (l + r) / 2;
	if (note == 'N') return rNumberGame(l, median);
	else return rNumberGame(median + 1, r);
}
int main() {
	int l, r, n; scanf("%d%d%d", &l, &r, &n); getchar();
	int key = rNumberGame(l, r);
	printf("%d", key);
}*/
//탐색트리
//과제 1
/*#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)
typedef struct node {
	int key; struct node *left, *right, *parent;
}node;
typedef struct Tree {
	node *root;
}Tree;
node *getnode() {
	node *tmp = (node *)malloc(sizeof(node));
	tmp->key = -1;
	tmp->left = tmp->right = tmp->parent = NULL;
	return tmp;
}
int isExternal(node *root) {
	if (root->left == NULL && root->right == NULL) return 1;
	return 0;
}
int isInternal(node *root) {
	if (root->left != NULL && root->right != NULL) return 1;
	return 0;
}
node *sibling(node *leaf) {
	if (leaf->parent == NULL) return NULL;
	if (leaf->parent->left == leaf) return leaf->parent->right;
	else return leaf->parent->left;
}
void initTree(Tree *T) { T->root = getnode(); }
node *treeSearch(node *root, int key) {
	if (isExternal(root)) return root;
	if (root->key == key) return root;
	else if (root->key > key) return treeSearch(root->left, key);
	else return treeSearch(root->right, key);
}
int findElement(Tree *T, int key) {
	node *n = treeSearch(T->root, key);
	if (isExternal(n)) return -1;
	else return n->key;
}
void expandExternal(node *root) {
	node *left = getnode(); node *right = getnode();
	left->parent = right->parent = root;
	root->left = left; root->right = right;
}
void InsertItem(Tree *T, int key) {
	node *input = treeSearch(T->root, key);
	if (isInternal(input)) return;
	input->key = key;
	expandExternal(input);
}
void reduceExternal(Tree *T, node *z) {
	node *parent = z->parent;

	node *zs = sibling(z);
	if (parent->parent == NULL) { T->root = zs; zs->parent = NULL; }
	else {
		node *g = parent->parent;
		zs->parent = g;
		if (g->left == parent) g->left = zs;
		else g->right = zs;
	}
	free(parent);
	free(z);
}
node *inOrderSucc(node *root) {
	node *w = root->right;
	if (isExternal(w)) return NULL;
	while (isInternal(w->left)) { w = w->left; }
	return w;
}
int removeItem(Tree *T, int key) {
	node *output = treeSearch(T->root, key);
	if (isExternal(output)) return -1;

	int elem = output->key;
	node *z = output->left;
	if (!isExternal(z)) z = output->right;
	if (isExternal(z)) reduceExternal(T, z);
	else {
		node *y = inOrderSucc(output);
		z = y->left;
		output->key = y->key;
		reduceExternal(T, z);
	}
	return elem;
}
void Preordertraverse(node *root) {
	if (root->key == -1) return;
	printf(" %d", root->key);
	Preordertraverse(root->left);
	Preordertraverse(root->right);
}
int main() {
	Tree T; initTree(&T);
	int key, del;
	node *search = NULL;
	while (1) {
		char ch; scanf("%c", &ch);
		switch (ch) {
		case 'i': scanf("%d", &key); InsertItem(&T, key); break;
		case 'p': Preordertraverse(T.root); printf("\n"); break;
		case 's': 
			scanf("%d", &key); search = treeSearch(T.root, key); 
			if (search->key == -1) printf("X\n");
			else printf("%d\n", search->key);
			break;
		case 'd': 
			scanf("%d", &key); del = removeItem(&T, key); 
			if (del != -1) printf("%d\n", del); 
			else printf("X\n");
			break;
		case 'q': return;
		}
		getchar();
	}
}*/
//과제 2 AVL트리
/*#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)
typedef struct node {
	int key, height; struct node *left, *right, *parent;
}node;
typedef struct Tree {
	node *root;
}Tree;
node *getnode() {
	node *tmp = (node *)malloc(sizeof(node));
	tmp->key = -1; tmp->height = 0;
	tmp->left = tmp->right = tmp->parent = NULL;
	return tmp;
}
void initTree(Tree *T) { T->root = getnode(); }
int isExternal(node *root) {
	if (root->left == NULL && root->right == NULL) return 1;
	return 0;
}
int isInternal(node *root) {
	if (root->left != NULL && root->right != NULL) return 1;
	return 0;
}
int isBalanced(node *leaf) {
	if (abs(leaf->left->height - leaf->right->height) > 1) return 0;
	return 1;
}
int updateHeight(node *leaf) {
	int height;
	if (leaf->left->height > leaf->right->height) height = 1 + leaf->left->height;
	else height = 1 + leaf->right->height;
	if (leaf->height != height) { leaf->height = height; return 1; }
	else return 0;
}
node *sibling(node *leaf) {
	if (leaf->parent == NULL) return NULL;
	if (leaf->parent->left == leaf) return leaf->parent->right;
	else return leaf->parent->left;
}
node *treeSearch(node *root, int key) {
	if (isExternal(root)) return root;
	if (root->key == key) return root;
	else if (root->key > key) return treeSearch(root->left, key);
	else return treeSearch(root->right, key);
}
node *restructure(Tree *T, node *x, node *y, node *z) {
	node *a = NULL, *b = NULL, *c = NULL;
	node *T0 = NULL, *T1 = NULL, *T2 = NULL, *T3 = NULL;
	if (z->left->left == x) {
		a = x; b = y; c = z;
		T0 = a->left; T1 = a->right; T2 = b->right; T3 = c->right;
	}
	else if (z->right->right == x) {
		a = z; b = y; c = x;
		T0 = a->left; T1 = b->left; T2 = c->left; T3 = c->right;
	}
	else if (z->left->right == x) {
		a = y; b = x; c = z;
		T0 = a->left; T1 = b->left; T2 = b->right; T3 = c->right;
	}
	else {
		a = z; b = x; c = y;
		T0 = a->left; T1 = b->left; T2 = b->right; T3 = c->right;
	}
	
	if (z->parent == NULL) T->root = b;
	else if (z->parent->left == z) z->parent->left = b;
	else z->parent->right = b;
	b->parent = z->parent;

	a->left = T0; a->right = T1;
	T0->parent = T1->parent = a;
	updateHeight(a);

	c->left = T2; c->right = T3;
	T2->parent = T3->parent = c;
	updateHeight(c);

	b->left = a; b->right = c;
	a->parent = c->parent = b;
	updateHeight(b);
	return b;
}
void searchAndFixAfterInsertion(Tree *T, node *leaf) {
	if (leaf->parent == NULL) return;
	node *z = leaf->parent; node *y = NULL, *x = NULL;
	while (updateHeight(z) && isBalanced(z)) {
		if (z->parent == NULL) return;
		z = z->parent;
	}
	if (isBalanced(z)) return;
	if (z->left->height > z->right->height) y = z->left;
	else y = z->right;
	if (y->left->height > y->right->height) x = y->left;
	else x = y->right;
	restructure(T, x, y, z);
}
void expandExternal(node *root) {
	node *left = getnode(); node *right = getnode();
	left->parent = right->parent = root;
	root->left = left; root->right = right; root->height = 1;
}
void InsertItem(Tree *T, int key) {
	node *input = treeSearch(T->root, key);
	if (isInternal(input)) return;
	input->key = key;
	expandExternal(input);
	searchAndFixAfterInsertion(T, input);
}
node *reduceExternal(Tree *T, node *z) {
	node *parent = z->parent;
	node *zs = sibling(z);
	node *g = NULL;
	if (parent->parent == NULL) { T->root = zs; zs->parent = NULL; }
	else {
		g = parent->parent;
		zs->parent = g;
		if (g->left == parent) g->left = zs;
		else g->right = zs;
	}
	free(parent);
	free(z);
	return zs;
}
node *inOrderSucc(node *root) {
	node *w = root->right;
	if (isExternal(w)) return NULL;
	while (isInternal(w->left)) { w = w->left; }
	return w;
}
void searchAndFixAfterRemoval(Tree *T, node *leaf) {
	if (leaf == NULL) return;
	node *z = leaf; node *y = NULL, *x = NULL, *b = NULL;
	while (updateHeight(z) && isBalanced(z)) {
		if (z->parent == NULL) return;
		z = z->parent;
	}
	if (isBalanced(z)) return;
	if (z->left->height > z->right->height) y = z->left;
	else y = z->right;
	if (y->left->height > y->right->height) x = y->left;
	else if (y->left->height < y->right->height) x = y->right;
	else {
		if (z->left == y) x = y->left;
		else x = y->right;
	}
	b = restructure(T, x, y, z);
	searchAndFixAfterRemoval(T, b->parent);
}
int removeItem(Tree *T, int key) {
	node *output = treeSearch(T->root, key);
	if (isExternal(output)) return -1;

	int elem = output->key;
	node *z = output->left;
	node *zs = NULL;
	if (!isExternal(z)) z = output->right;
	if (isExternal(z)) zs = reduceExternal(T, z);
	else {
		node *y = inOrderSucc(output);
		z = y->left;
		output->key = y->key;
		zs = reduceExternal(T, z);
	}
	searchAndFixAfterRemoval(T, zs->parent);
	return elem;
}
int findElement(Tree *T, int key) {
	node *n = treeSearch(T->root, key);
	if (isExternal(n)) return -1;
	else return n->key;
}
void Preordertraverse(node *root) {
	if (root->key == -1) return;
	printf(" %d", root->key);
	Preordertraverse(root->left);
	Preordertraverse(root->right);
}
int main() {
	Tree T; initTree(&T);
	int key, del;
	node *search = NULL;
	while (1) {
		char ch; scanf("%c", &ch);
		switch (ch) {
		case 'i': scanf("%d", &key); InsertItem(&T, key); break;
		case 'p': Preordertraverse(T.root); printf("\n"); break;
		case 's':
			scanf("%d", &key); search = treeSearch(T.root, key);
			if (search->key == -1) printf("X\n");
			else printf("%d\n", search->key);
			break;
		case 'd':
			scanf("%d", &key); del = removeItem(&T, key);
			if (del != -1) printf("%d\n", del);
			else printf("X\n");
			break;
		case 'q': return;
		}
		getchar();
	}
}*/
//해쉬 테이블
//과제 1 --- 분할통치
/*#include <stdio.h>
#pragma warning(disable:4996);
typedef struct node {
	int key; struct node *next;
}node;
typedef struct List {
	node *start;
}List;
node *getnode() {
	node *tmp = (node *)malloc(sizeof(node));
	tmp->key = -1; tmp->next = NULL;
	return tmp;
}
void initBucketArray(List *L, int M) {
	for (int i = 0; i < M; i++) L[i].start = getnode();
}
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
void InsertItemList(node *start, int key) {
	node *newnode = getnode(); newnode->key = key;
	newnode->next = start->next; start->next = newnode;
}
void InsertItem(List *L, int key, int M) {
	int v = key % M;
	InsertItemList(L[v].start, key);
}
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
void printList(List *L, int M) {
	for (int i = 0; i < M; i++) {
		node *p = L[i].start->next;
		while (p != NULL) { printf(" %d", p->key); p = p->next; }
	}
	printf("\n");
}
void freeList(List *L, int M) {
	for (int i = 0; i < M; i++) {
		node *p = L[i].start;
		while (p != NULL) { node *del = p; p = p->next; free(del); }
	}
}
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
//과제 2 --- 선형조사법
/*#include <stdio.h>
#pragma warning(disable:4996)
void initBucketArray(int **L, int M) {
	*L = (int *)malloc(sizeof(int)*M);
	for (int i = 0; i < M; i++) (*L)[i] = 0;
}
int getNextBucket(int v, int M, int i) { return (v + i) % M; }
int overflowException(int *L, int M, int N) {
	int cnt = 0;
	for (int i = 0; i < M; i++) if (L[i] != 0) cnt++;
	if (cnt > N) return 1;
	return 0;
}
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
//과제 3 --- 이중해싱
/*#include <stdio.h>
#pragma warning(disable:4996)
void initBucketArray(int **L, int M) {
	*L = (int *)malloc(sizeof(int)*M);
	for (int i = 0; i < M; i++) (*L)[i] = 0;
}
int SecondHashFunction(int key, int Q) { return Q - (key % Q); }
int FirstHashFunction(int key, int M, int Q, int i) { return ((key % M + i * SecondHashFunction(key, Q))) % M; }
int getNextBucket(int key, int M, int Q, int i) { return FirstHashFunction(key, M, Q, i); }
int overflowException(int *L, int M, int N) {
	int cnt = 0;
	for (int i = 0; i < M; i++) if (L[i] != 0) cnt++;
	if (cnt > N) return 1;
	return 0;
}
int findElement(int *L, int M, int Q, int key) {
	int i = 0;
	while (i < M) {
		int nextBucket = getNextBucket(key, M, Q, i);
		if (L[nextBucket] == 0) return -1;
		else if (L[nextBucket] == key) { printf("%d ", nextBucket); return L[nextBucket]; }
		else i++;
	}
}
void insertItem(int *L, int M, int N, int Q, int key) {
	if (overflowException(L, M, N)) return;
	int i = 0;
	while (i < M) {
		int nextBucket = getNextBucket(key, M, Q, i);
		if (L[nextBucket] == 0) { L[nextBucket] = key; printf("%d\n", nextBucket); return; }
		else { printf("C"); i++; }
	}
}
void printList(int *L, int M) {
	for (int i = 0; i < M; i++) printf(" %d", L[i]);
	printf("\n");
}
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
//해쉬 테이블 과제 - 비활성화 방식 삭제 구현
/*#include <stdio.h>
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
		else { printf("C"); i++;}
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

//그래프
//과제 1
/*#include <stdio.h>
#pragma warning(disable:4996)
typedef struct edge {
	int weight;
	struct edge *next;
	struct vertex *start;
	struct vertex *end;
}edge;
typedef struct vertex {
	int val;
	struct vertex *next;
	struct edge *incidenceList;
}vertex;
typedef struct Graph {
	int vertexCount;
	struct vertex *GraphRoot;
}Graph;
void InitGraph(Graph **G) {
	*G = (Graph *)malloc(sizeof(Graph));
	(*G)->GraphRoot = NULL;
	(*G)->vertexCount = 0;
}
vertex *getVertex() {
	vertex *v = (vertex *)malloc(sizeof(vertex));
	v->next = v->incidenceList = NULL;
}
edge *getEdge() {
	edge *e = (edge *)malloc(sizeof(edge));
	e->start = e->end = e->next = NULL;
}
vertex *InsertVertex(Graph *G, int val) {
	vertex *newVertex = getVertex(); newVertex->val = val;
	newVertex->incidenceList = getEdge();
	G->vertexCount++;
	if (G->GraphRoot == NULL) G->GraphRoot = newVertex;
	else {
		vertex *p = G->GraphRoot;
		while (p->next != NULL) { p = p->next; }
		p->next = newVertex;
	}
	return newVertex;
}
void InsertEdge(vertex *start, vertex *end, int weight) {
	edge *newEdge = getEdge();
	newEdge->start = start; newEdge->end = end; newEdge->weight = weight;

	edge *H = start->incidenceList;
	if (H->next == NULL) H->next = newEdge;
	else {
		while (H->next != NULL) {
			if (H->next->end->val > newEdge->end->val) {
				newEdge->next = H->next;
				H->next = newEdge; return;
			}
			H = H->next;
		}
		H->next = newEdge;
	}
}
vertex *SearchVertex(Graph *G, int val) {
	vertex *p = G->GraphRoot;
	while (p != NULL) { if (p->val == val) break; p = p->next; }
	return p;
}
edge *SearchEdge(vertex *start, vertex *end) {
	edge *H = start->incidenceList->next;
	while (H != NULL) { if (H->end == end) break; H = H->next; }
	return H;
}
void DeleteEdge(Graph *G, vertex *Start, vertex *End) {
	edge *H = Start->incidenceList; edge *T = End->incidenceList;

	while (H->next != NULL) { if (H->next->end->val == End->val) break; H = H->next; }
	if(H->next == NULL) return;
	edge *delH = H->next; H->next = delH->next; free(delH);

	while (T->next != NULL) { if (T->next->end->val == Start->val) break; T = T->next; }
	if (T->next == NULL) return;
	edge *delT = T->next; T->next = delT->next; free(delT);
}
void InsertExtraEdge(vertex *Start, vertex *End, int weight) {
	if(Start == End) InsertEdge(Start, End, weight);
	else { InsertEdge(Start, End, weight); InsertEdge(End, Start, weight); }
}
void InvalidateEdgeFunction(Graph *G, int start, int end, int weight) {
	vertex *Start = SearchVertex(G, start); vertex *End = SearchVertex(G, end);
	if (Start == NULL || End == NULL) { printf("-1\n"); return; }

	if (!weight) DeleteEdge(G, Start, End);
	else {
		edge *S = SearchEdge(Start, End); edge *E = SearchEdge(End, Start);
		if (S == NULL) InsertExtraEdge(Start, End, weight);
		else { S->weight = weight; E->weight = weight; }
	}
}
void PrintIncidenceList(Graph *G, int val) {
	vertex *p = G->GraphRoot;
	while (p != NULL) { if (p->val == val) break; p = p->next; }
	if (p == NULL) { printf("-1"); return; }
	else { edge *H = p->incidenceList->next; while (H != NULL) { printf(" %d %d", H->end->val, H->weight); H = H->next; } }
	printf("\n");
}
void freeGraph(Graph *G) {
	vertex *p = G->GraphRoot;
	while (p != NULL) {
		edge *H = p->incidenceList->next;
		while (H != NULL) { edge *del = H; H = H->next; free(del); }
		free(p->incidenceList);
		p = p->next;
	}
}
int main() {
	Graph *G = NULL;
	InitGraph(&G);

	vertex *v1 = InsertVertex(G, 1); vertex *v2 = InsertVertex(G, 2);
	vertex *v3 = InsertVertex(G, 3); vertex *v4 = InsertVertex(G, 4);
	vertex *v5 = InsertVertex(G, 5); vertex *v6 = InsertVertex(G, 6);

	InsertEdge(v1, v2, 1); InsertEdge(v1, v3, 1); InsertEdge(v1, v4, 1); InsertEdge(v1, v6, 2);
	InsertEdge(v2, v1, 1); InsertEdge(v2, v3, 1);
	InsertEdge(v3, v1, 1); InsertEdge(v3, v2, 1); InsertEdge(v3, v5, 4);
	InsertEdge(v4, v1, 1);
	InsertEdge(v5, v3, 4); InsertEdge(v5, v5, 4); InsertEdge(v5, v6, 3);
	InsertEdge(v6, v1, 2); InsertEdge(v6, v5, 3);

	while (1) {
		char ch; int val; int start, end, weight;
		scanf("%c", &ch);
		switch (ch) {
		case 'a': scanf("%d", &val); PrintIncidenceList(G, val); break;
		case 'm': scanf("%d %d %d", &start, &end, &weight); InvalidateEdgeFunction(G, start, end, weight); break;
		case 'q': freeGraph(G); free(G); return;
		default: break;
		}
		getchar();
	}
}*/
//과제 2
/*#include <stdio.h>
#pragma warning(disable:4996)
typedef struct edge {
	int weight;
	struct vertex *start;
	struct vertex *end;
}edge;
typedef struct vertex {
	int val;
	struct vertex *next;
}vertex;
typedef struct Graph {
	int vertexCount;
	struct vertex *GraphRoot;
	struct edge *Matrix[6][6];
}Graph;
void InitGraph(Graph **G) {
	*G = (Graph *)malloc(sizeof(Graph));
	(*G)->GraphRoot = NULL;
	(*G)->vertexCount = 0;
	for (int i = 0; i < 6; i++) { for (int j = 0; j < 6; j++) (*G)->Matrix[i][j] = NULL; }
}
vertex *getVertex() {
	vertex *v = (vertex *)malloc(sizeof(vertex));
	v->next = NULL;
}
edge *getEdge() {
	edge *e = (edge *)malloc(sizeof(edge));
	e->start = e->end = NULL;
}
vertex *InsertVertex(Graph *G, int val) {
	vertex *newVertex = getVertex(); newVertex->val = val;
	G->vertexCount++;
	if (G->GraphRoot == NULL) G->GraphRoot = newVertex;
	else {
		vertex *p = G->GraphRoot;
		while (p->next != NULL) { p = p->next; }
		p->next = newVertex;
	}
	return newVertex;
}
void InsertEdge(Graph *G, vertex *start, vertex *end, int weight) {
	edge *newEdge = getEdge();
	newEdge->start = start; newEdge->end = end; newEdge->weight = weight;
	G->Matrix[start->val - 1][end->val - 1] = newEdge;
}
vertex *SearchVertex(Graph *G, int val) {
	vertex *p = G->GraphRoot;
	while (p != NULL) { if (p->val == val) break; p = p->next; }
	return p;
}
edge *SearchEdge(Graph *G, vertex *start, vertex *end) { return G->Matrix[start->val - 1][end->val - 1]; }
void DeleteEdge(Graph *G, vertex *Start, vertex *End) {
	edge *H = G->Matrix[Start->val - 1][End->val - 1]; 
	if (H != NULL) { free(H); G->Matrix[Start->val - 1][End->val - 1] = NULL; }
	
	edge *T = G->Matrix[End->val - 1][Start->val - 1];
	if (T != NULL) { free(T); G->Matrix[End->val - 1][Start->val - 1] = NULL; }
}
void InsertExtraEdge(Graph *G, vertex *Start, vertex *End, int weight) {
	if (Start == End) InsertEdge(G, Start, End, weight);
	else { InsertEdge(G, Start, End, weight); InsertEdge(G, End, Start, weight); }
}
void InvalidateEdgeFunction(Graph *G, int start, int end, int weight) {
	vertex *Start = SearchVertex(G, start); vertex *End = SearchVertex(G, end);
	if (Start == NULL || End == NULL) { printf("-1\n"); return; }

	if (!weight) DeleteEdge(G, Start, End);
	else {
		edge *S = SearchEdge(G, Start, End); edge *E = SearchEdge(G, End, Start);
		if (S == NULL) InsertExtraEdge(G, Start, End, weight);
		else { S->weight = weight; E->weight = weight; }
	}
}
void PrintIncidenceList(Graph *G, int val) {
	vertex *p = G->GraphRoot;
	while (p != NULL) { if (p->val == val) break; p = p->next; }
	if (p == NULL) printf("-1");
	else { for (int i = 0; i < 6; i++) if (G->Matrix[p->val - 1][i] != NULL) printf(" %d %d", G->Matrix[p->val - 1][i]->end->val, G->Matrix[p->val - 1][i]->weight); }
	printf("\n");
}
void freeGraph(Graph *G) {
	vertex *p = G->GraphRoot;
	while (p != NULL) {
		vertex *del = p; p = p->next; free(del);
	}
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 6; j++) if (G->Matrix[i][j] != NULL) free(G->Matrix[i][j]);
	}
}
int main() {
	Graph *G = NULL;
	InitGraph(&G);

	vertex *v1 = InsertVertex(G, 1); vertex *v2 = InsertVertex(G, 2);
	vertex *v3 = InsertVertex(G, 3); vertex *v4 = InsertVertex(G, 4);
	vertex *v5 = InsertVertex(G, 5); vertex *v6 = InsertVertex(G, 6);

	InsertEdge(G, v1, v2, 1); InsertEdge(G, v1, v3, 1); InsertEdge(G, v1, v4, 1); InsertEdge(G, v1, v6, 2);
	InsertEdge(G, v2, v1, 1); InsertEdge(G, v2, v3, 1);
	InsertEdge(G, v3, v1, 1); InsertEdge(G, v3, v2, 1); InsertEdge(G, v3, v5, 4);
	InsertEdge(G, v4, v1, 1);
	InsertEdge(G, v5, v3, 4); InsertEdge(G, v5, v5, 4); InsertEdge(G, v5, v6, 3);
	InsertEdge(G, v6, v1, 2); InsertEdge(G, v6, v5, 3);

	while (1) {
		char ch; int val; int start, end, weight;
		scanf("%c", &ch);
		switch (ch) {
		case 'a': scanf("%d", &val); PrintIncidenceList(G, val); break;
		case 'm': scanf("%d %d %d", &start, &end, &weight); InvalidateEdgeFunction(G, start, end, weight); break;
		case 'q': freeGraph(G); free(G); return;
		default: break;
		}
		getchar();
	}
}*/
//그래프 순회
//1
/*#include <stdio.h>
#pragma warning(disable:4996)
typedef struct vertex {
	int key; int visited;
	struct vertex *next;
	struct Incidencelist *list;
}vertex;
typedef struct edge {
	struct vertex *start, *end;
	struct edge *next;
}edge;
typedef struct Incidencelist {
	struct edge *val; 
	struct Incidencelist *next;
}Incidencelist;
typedef struct Graph {
	int vertexCount;
	struct vertex *VertexRoot;
	struct edge *EdgeRoot;
}Graph;
void InitGraph(Graph **G) {
	*G = (Graph *)malloc(sizeof(Graph));
	(*G)->VertexRoot = (*G)->EdgeRoot = NULL; (*G)->vertexCount = 0;
}
vertex *getVertex() {
	vertex *newVertex = (vertex *)malloc(sizeof(vertex));
	newVertex->visited = newVertex->key = 0;
	newVertex->list = newVertex->next = NULL;
}
Incidencelist *getList() {
	Incidencelist *newList = (Incidencelist *)malloc(sizeof(Incidencelist));
	newList->next = newList->val = NULL;
}
edge *getEdge() {
	edge *newEdge = (edge *)malloc(sizeof(edge));
	newEdge->next = newEdge->start = newEdge->end = NULL;
}
vertex *SearchVertex(Graph *G, int key) {
	vertex *p = G->VertexRoot;
	while (p != NULL) { if (p->key == key) break; p = p->next; }
	return p;
}
void InsertVertex(Graph *G, int key) {
	vertex *newVertex = getVertex(); newVertex->key = key; newVertex->list = getList();
	if (G->VertexRoot == NULL) G->VertexRoot = newVertex;
	else {
		vertex *p = G->VertexRoot;
		while (p->next != NULL) { p = p->next; }
		p->next = newVertex;
	}
	G->vertexCount++;
}

void Insert_OneEdge(Graph *G, int start, int end) {
	vertex *S = SearchVertex(G, start); vertex *E = SearchVertex(G, end);
	if (S == NULL || E == NULL) return;

	edge *newEdge = getEdge(); newEdge->start = S; newEdge->end = E;
	if (G->EdgeRoot == NULL) G->EdgeRoot = newEdge;
	else {
		edge *p = G->EdgeRoot;
		while (p->next != NULL) p = p->next;
		p->next = newEdge; 
	}

	Incidencelist *newList = getList(); newList->val = newEdge;
	Incidencelist *H = S->list;
	while (H->next != NULL) { if (H->next->val->end->key > newEdge->end->key) break; H = H->next; }
	if (H->next == NULL) H->next = newList;
	else { newList->next = H->next; H->next = newList; }
}
void InsertEdges(Graph *G, int start, int end) { 
	if (start != end) { Insert_OneEdge(G, start, end); Insert_OneEdge(G, end, start); }
	else Insert_OneEdge(G, start, end);
}
void DFS(vertex *u) {
	printf("%d\n", u->key); u->visited = 1;
	for (Incidencelist *p = u->list->next; p != NULL; p = p->next)
		if (!p->val->end->visited) DFS(p->val->end);
}
void PrintIncidenceList(Graph *G, int key) {
	vertex *p = SearchVertex(G, key);
	Incidencelist *H = p->list->next;
	while (H != NULL) { printf(" %d %d", H->val->start->key, H->val->end->key); H = H->next; }
	printf("\n");
}
void freenode(Graph *G) {
	edge *p = G->EdgeRoot;
	while (p != NULL) { edge *del = p; p = p->next; free(del); }
	vertex *q = G->VertexRoot;
	while (q != NULL) { vertex *del = q; Incidencelist *k = del->list; while (k != NULL) { Incidencelist *d = k; k = k->next; free(d); } q = q->next; free(del); }
}
int main() {
	Graph *G = NULL; InitGraph(&G);
	int vertexC, EdgeC, SPoint, start, end;

	scanf("%d %d %d", &vertexC, &EdgeC, &SPoint);
	for (int i = 0; i < vertexC; i++) InsertVertex(G, i + 1);
	for (int i = 0; i < EdgeC; i++) { scanf("%d %d", &start, &end); InsertEdges(G, start, end); }
	DFS(SearchVertex(G, SPoint));
	freenode(G); free(G);
}*/
//2
/*#include <stdio.h>
#pragma warning(disable:4996)
typedef struct vertex {
	int key; int visited;
	struct vertex *next;
}vertex;
typedef struct edge {
	struct vertex *start, *end;
	struct edge *next;
}edge;
typedef struct Graph {
	int vertexCount;
	struct vertex *VertexRoot;
	struct edge *EdgeRoot;
	struct edge ***Matrice;
}Graph;
void InitGraph(Graph **G, int vertexC) {
	*G = (Graph *)malloc(sizeof(Graph));
	(*G)->VertexRoot = (*G)->EdgeRoot = NULL; (*G)->vertexCount = 0;
	(*G)->Matrice = (edge**)malloc(sizeof(edge*)*vertexC);
	for (int i = 0; i < vertexC; i++) { (*G)->Matrice[i] = (edge *)malloc(sizeof(edge)*vertexC); }
	for (int i = 0; i < vertexC; i++) { for (int j = 0; j < vertexC; j++) (*G)->Matrice[i][j] = NULL; }
}
vertex *getVertex() {
	vertex *newVertex = (vertex *)malloc(sizeof(vertex));
	newVertex->key = newVertex->visited = 0; newVertex->next = NULL;
}
edge *getEdge() {
	edge *newEdge = (edge *)malloc(sizeof(edge));
	newEdge->next = newEdge->start = newEdge->end = NULL;
}
vertex *SearchVertex(Graph *G, int key) {
	vertex *p = G->VertexRoot;
	while (p != NULL) { if (p->key == key) break; p = p->next; }
	return p;
}
void InsertVertex(Graph *G, int key) {
	vertex *newVertex = getVertex(); newVertex->key = key;
	if (G->VertexRoot == NULL) G->VertexRoot = newVertex;
	else {
		vertex *p = G->VertexRoot;
		while (p->next != NULL) p = p->next;
		p->next = newVertex;
	}
	G->vertexCount++;
}
void Insert_OneEdge(Graph *G, int start, int end) {
	vertex *S = SearchVertex(G, start); vertex *E = SearchVertex(G, end);
	edge *newEdge = getEdge(); newEdge->start = S; newEdge->end = E;

	if (G->EdgeRoot == NULL) G->EdgeRoot = newEdge;
	else {
		edge *p = G->EdgeRoot;
		while (p->next != NULL) p = p->next;
		p->next = newEdge;
	}
	G->Matrice[start - 1][end - 1] = newEdge;
}
void InsertEdges(Graph *G, int start, int end) {
	if (start != end) { Insert_OneEdge(G, start, end); Insert_OneEdge(G, end, start); }
	else Insert_OneEdge(G, start, end);
}
void BFS(Graph *G, vertex *v, int vertexC) {
	vertex *Queue[100]; int f = 0, r = -1;
	Queue[(++r) % 101] = v; v->visited = 1;
	while ((r + 1) % 100 != f % 100) {
		vertex *e = Queue[(f++) % 101];
		printf("%d\n", e->key);
		for (int i = 0; i < vertexC; i++) { 
			if (G->Matrice[e->key - 1][i] != NULL) { 
				if (!G->Matrice[e->key - 1][i]->end->visited) { G->Matrice[e->key - 1][i]->end->visited = 1; Queue[(++r) % 101] = G->Matrice[e->key - 1][i]->end; }
			} 
		}
	}
}
void PrintIncidenceList(Graph *G, int vertexC, int key) {
	for (int i = 0; i < vertexC; i++) 
		if (G->Matrice[key][i] != NULL) { printf(" %d %d", G->Matrice[key][i]->start->key, G->Matrice[key][i]->end->key); }
	printf("\n");
}
void freeGraph(Graph *G, int vertexC) {
	vertex *p = G->VertexRoot;
	while (p != NULL) { vertex *del = p; p = p->next; free(del); }
	edge *q = G->EdgeRoot;
	while (q != NULL) { edge *del = q; q = q->next; free(del); }
	for (int i = 0; i < vertexC; i++) { free(G->Matrice[i]); }
	free(G->Matrice);
}
int main() {
	Graph *G = NULL; 
	int vertexC, EdgeC, SPoint, start, end;
	scanf("%d %d %d", &vertexC, &EdgeC, &SPoint);

	InitGraph(&G, vertexC);
	for (int i = 0; i < vertexC; i++) InsertVertex(G, i + 1);
	for (int i = 0; i < EdgeC; i++) { scanf("%d %d", &start, &end); InsertEdges(G, start, end); }
	BFS(G, SearchVertex(G, SPoint), vertexC);
	freeGraph(G, vertexC); free(G);
}*/
//방향 그래프
//1
/*#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)
typedef struct vertex {
	char key; int inlabel; int visited;
	struct vertex *next;
	struct inedge *inH;
	struct outedge *outH;
}vertex;
typedef struct inedge {
	struct vertex *val;
	struct vertex *in;
	struct inedge *nextEdge;
}inedge;
typedef struct outedge {
	struct vertex *val;
	struct vertex *out;
	struct outedge *nextEdge;
}outedge;
typedef struct Graph {
	int vertexCount;
	struct vertex *VertexRoot;
	struct edge *EdgeRoot;
}Graph;
vertex *getVertex() {
	vertex *newVertex = (vertex *)malloc(sizeof(vertex));
	newVertex->inlabel = newVertex->visited = 0;
	newVertex->inH = newVertex->outH = NULL; newVertex->next = NULL;
	return newVertex;
}
inedge *getInEdge() {
	inedge *newInEdge = (inedge *)malloc(sizeof(inedge));
	newInEdge->val = newInEdge->in = newInEdge->nextEdge = NULL;
	return newInEdge;
}
outedge *getOutEdge() {
	outedge *newOutEdge = (outedge *)malloc(sizeof(outedge));
	newOutEdge->val = newOutEdge->out = newOutEdge->nextEdge = NULL;
	return newOutEdge;
}
void InitGraph(Graph **G) {
	*G = (Graph *)malloc(sizeof(Graph));
	(*G)->VertexRoot = (*G)->EdgeRoot = NULL; (*G)->vertexCount = 0;
}
void InsertVertex(Graph *G, char key) {
	vertex *newVertex = getVertex(); newVertex->key = key;
	if (G->VertexRoot == NULL) G->VertexRoot = newVertex;
	else {
		vertex *p = G->VertexRoot;
		while (p->next != NULL) { p = p->next; }
		p->next = newVertex;
	}
	G->vertexCount++;
}
vertex *SearchVertex(Graph *G, char key) {
	vertex *p = G->VertexRoot;
	while (p != NULL) { if (p->key == key) break; p = p->next; }
	return p;
}
void InsertEdge(Graph *G, char in, char out) {
	vertex *inVertex = SearchVertex(G, in); vertex *outVertex = SearchVertex(G, out);
	inedge *I = getInEdge(); I->val = outVertex; I->in = inVertex;
	outedge *O = getOutEdge(); O->val = inVertex; O->out = outVertex;
	outVertex->inlabel++;
	if (inVertex->outH == NULL) inVertex->outH = O;
	else {
		O->nextEdge = inVertex->outH;
		inVertex->outH = O;
	}
	if (outVertex->inH == NULL) outVertex->inH = I;
	else {
		I->nextEdge = outVertex->inH;
		outVertex->inH = I;
	}
}
void topologicalSort(Graph *G) {
	int f = 0, r = -1; int insertptr = 0;
	vertex **queue = (vertex **)malloc(sizeof(vertex *)*G->vertexCount);
	char *Orderedlist = (char *)malloc(sizeof(char)*G->vertexCount);

	vertex *p = G->VertexRoot;
	while (p != NULL) { if (p->inlabel == 0) queue[++r] = p; p = p->next; }

	int i = 1;
	while (f <= r) {
		vertex *elem = queue[f++];
		Orderedlist[insertptr++] = elem->key; i++;
		outedge *O = elem->outH;
		while (O != NULL) {
			O->out->inlabel--;
			if (O->out->inlabel == 0) queue[++r] = O->out;
			O = O->nextEdge;
		}
	}
	if (i <= G->vertexCount) printf("0\n");
	else { for (int j = 0; j < G->vertexCount; j++) printf("%c ", Orderedlist[j]); printf("\n"); }
	free(queue);
	free(Orderedlist);
	return;
}
void freeVertexNEdges(Graph *G) {
	vertex *p = G->VertexRoot;
	while (p != NULL) {
		vertex *delv = p;
		inedge *IH = p->inH;
		outedge *OH = p->outH;
		while (IH != NULL) { inedge *del = IH; IH = IH->nextEdge; free(del); }
		while (OH != NULL) { outedge *del = OH; OH = OH->nextEdge; free(del); }
		p = p->next; free(delv);
	}
}
int main() {
	Graph *G = NULL; InitGraph(&G);
	int Cvertex; scanf("%d", &Cvertex); getchar();
	for (int i = 0; i < Cvertex; i++) { char key; scanf("%c", &key); InsertVertex(G, key); getchar(); }
	int Cedge; scanf("%d", &Cedge); getchar();
	for (int i = 0; i < Cedge; i++) { char start, end; scanf("%c %c", &start, &end); InsertEdge(G, start, end); getchar(); }
	topologicalSort(G);
	freeVertexNEdges(G);
	free(G);
}*/
//과제 1
/*#include <stdio.h>
#include <time.h>
#include <Windows.h>
int MAX = 30;
void InitArray(int *array, int type) {
	if (type) {
		array[0] = 0; array[1] = 1;
		for (int i = 2; i < MAX; i++) array[i] = array[i - 1] + array[i - 1] % 5 + 3;
	}
	else {
		array[0] = 0; array[1] = 5;
		for (int i = 2; i < MAX; i++) array[i] = (array[i - 1] + i) % 9 + 1;
	}
}
int r_airtelDC(int *A, int *H, int src, int dest) {
	if (src == dest) return 0;
	int mincost;
	for (int i = src; i < dest; i++) {
		int cost = r_airtelDC(A, H, src, i) + A[dest - i];
		if (i != src) cost += H[i];
		if (i == src) mincost = cost;
		else { if (mincost > cost) mincost = cost; }
	}
	return mincost;
}
int airtelDC(int *A, int *H, int n, int src, int dest){
	return r_airtelDC(A, H, src, dest);
}
int airtelDP(int *A, int *H, int n, int src, int dest) {
	int *min = (int *)malloc(sizeof(int)*n);
	min[src] = 0;
	for (int i = src + 1; i <= dest; i++) {
		for (int j = src; j < i; j++) {
			int cost = min[j] + A[i - j];
			if (j != src) cost += H[j];
			if (j == src) min[i] = cost;
			else { if (min[i] > cost) min[i] = cost; }
		}
	}
	int mincost = min[dest];
	free(min);
	return mincost;
}
int main() {
	int *A = (int *)malloc(sizeof(int)*MAX); int *H = (int *)malloc(sizeof(int)*MAX);
	InitArray(A, 1); InitArray(H, 0);
	
	LARGE_INTEGER ticksPerSec;
	LARGE_INTEGER start, end, diff;
	QueryPerformanceFrequency(&ticksPerSec);
	int n = 6;
	
	printf("n\ts\td\tmincost\tversion\tcputime\n");
	for (int i = 0; i < 3; i++) {
		int src, dest;
		if (i == 0) { src = 0; dest = 4; }
		else if (i == 1) { src = 2; dest = 5; }
		else { src = 2; dest = 4; }
		QueryPerformanceCounter(&start);
		printf("%d\t%d\t%d\t%d\tDC\t", n, src, dest, airtelDC(A, H, n, src, dest));
		QueryPerformanceCounter(&end);
		diff.QuadPart = end.QuadPart - start.QuadPart;
		printf("%.10fms\n", ((double)diff.QuadPart / (double)ticksPerSec.QuadPart));
		
		QueryPerformanceCounter(&start);
		printf("%d\t%d\t%d\t%d\tDP\t", n, src, dest, airtelDP(A, H, n, src, dest));
		QueryPerformanceCounter(&end);
		diff.QuadPart = end.QuadPart - start.QuadPart;
		printf("%.10fms\n", ((double)diff.QuadPart / (double)ticksPerSec.QuadPart));
	}

	n = MAX;
	int src = 1, dest = n - 2;

	QueryPerformanceCounter(&start);
	printf("%d\t%d\t%d\t%d\tDC\t", n, src, dest, airtelDC(A, H, n, src, dest));
	QueryPerformanceCounter(&end);
	diff.QuadPart = end.QuadPart - start.QuadPart;
	printf("%.10fms\n", ((double)diff.QuadPart / (double)ticksPerSec.QuadPart));
	
	QueryPerformanceCounter(&start);
	printf("%d\t%d\t%d\t%d\tDP\t", n, src, dest, airtelDP(A, H, n, src, dest));
	QueryPerformanceCounter(&end);
	diff.QuadPart = end.QuadPart - start.QuadPart;
	printf("%.10fms\n", ((double)diff.QuadPart / (double)ticksPerSec.QuadPart));
	free(A); free(H);
}*/
//최소신장트리
//prim_jarnik algorithm
/*#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)
typedef struct vertex {
	int key; int visited;
	int distance;
	struct edge *parent;
	struct vertex *next;
	struct Incidencelist *list;
}vertex;
typedef struct edge {
	int weight;
	struct vertex *start, *end;
	struct edge *next;
}edge;
typedef struct Incidencelist {
	struct edge *val;
	struct Incidencelist *next;
}Incidencelist;
typedef struct Graph {
	int vertexCount;
	struct vertex *VertexRoot;
	struct edge *EdgeRoot;
}Graph;
void InitGraph(Graph **G) {
	*G = (Graph *)malloc(sizeof(Graph));
	(*G)->VertexRoot = NULL;  (*G)->EdgeRoot = NULL; (*G)->vertexCount = 0;
}
vertex *getVertex() {
	vertex *newVertex = (vertex *)malloc(sizeof(vertex));
	newVertex->visited = newVertex->key = 0;
	newVertex->distance = 1000000000;
	newVertex->list = NULL;  newVertex->next = NULL; newVertex->parent = NULL;
	return newVertex;
}
Incidencelist *getList() {
	Incidencelist *newList = (Incidencelist *)malloc(sizeof(Incidencelist));
	newList->next = NULL; newList->val = NULL;
	return newList;
}
edge *getEdge() {
	edge *newEdge = (edge *)malloc(sizeof(edge));
	newEdge->next = NULL; newEdge->start = newEdge->end = NULL;
	return newEdge;
}
vertex *SearchVertex(Graph *G, int key) {
	vertex *p = G->VertexRoot;
	while (p != NULL) { if (p->key == key) break; p = p->next; }
	return p;
}
void InsertVertex(Graph *G, int key) {
	vertex *newVertex = getVertex(); newVertex->key = key; newVertex->list = getList();
	if (G->VertexRoot == NULL) G->VertexRoot = newVertex;
	else {
		vertex *p = G->VertexRoot;
		while (p->next != NULL) { p = p->next; }
		p->next = newVertex;
	}
	G->vertexCount++;
}
void Insert_OneEdge(Graph *G, int start, int end, int weight) {
	vertex *S = SearchVertex(G, start); vertex *E = SearchVertex(G, end);
	if (S == NULL || E == NULL) return;

	edge *newEdge = getEdge(); newEdge->start = S; newEdge->end = E; newEdge->weight = weight;
	if (G->EdgeRoot == NULL) G->EdgeRoot = newEdge;
	else {
		edge *p = G->EdgeRoot;
		while (p->next != NULL) p = p->next;
		p->next = newEdge;
	}

	Incidencelist *newList = getList(); newList->val = newEdge;
	Incidencelist *H = S->list;
	while (H->next != NULL) { if (H->next->val->end->key > newEdge->end->key) break; H = H->next; }
	if (H->next == NULL) H->next = newList;
	else { newList->next = H->next; H->next = newList; }
}
void InsertEdges(Graph *G, int start, int end, int weight) {
	if (start != end) { Insert_OneEdge(G, start, end, weight); Insert_OneEdge(G, end, start, weight); }
	else Insert_OneEdge(G, start, end, weight);
}
vertex *minVertex(vertex **Queue, int f, int r) {
	vertex *minimum = NULL; int min = 1000000000;
	for (int i = f; i <= r; i++) {
		if (min > Queue[i]->distance) {
			min = Queue[i]->distance;
			minimum = Queue[i];
			vertex *tmp = Queue[i]; Queue[i] = Queue[f]; Queue[f] = tmp;
		}
	}
	return minimum;
}
int Prim_JarnikMST(Graph *G) {
	vertex *s = G->VertexRoot; int result = 0;
	s->distance = 0;
	
	vertex **Queue = (vertex **)malloc(sizeof(vertex*)*G->vertexCount);
	int f = 0, r = -1;
	vertex *p = G->VertexRoot;
	while (p != NULL) { Queue[++r] = p; p = p->next; }
	while (f <= r) {
		vertex *v = minVertex(Queue, f, r); f++;
		printf(" %d", v->key);
		if (v->parent != NULL) result += v->parent->weight;
		Incidencelist *p = v->list->next;
		while (p != NULL) {
			vertex *edgev = p->val->end;
			int flag = 0, index;
			for (int i = f; i <= r; i++) { if (edgev == Queue[i]) { flag = 1; index = i; break; } }
			if (flag && p->val->weight < edgev->distance) {
				edgev->distance = p->val->weight;
				edgev->parent = p->val;
				Queue[index]->distance = p->val->weight;
			}
			p = p->next;
		}
	}
	return result;
}
int main() {
	Graph *G = NULL; InitGraph(&G);
	int n, m;
	scanf("%d %d", &n, &m);
	for (int i = 0; i < n; i++) InsertVertex(G, i + 1);
	for (int i = 0; i < m; i++) {
		int src, dest, weight;
		scanf("%d %d %d", &src, &dest, &weight);
		InsertEdges(G, src, dest, weight);
	}
	printf("\n%d", Prim_JarnikMST(G));
}*/
//kruskal algorithm
/*#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)
typedef struct vertex {
	int key; int visited; int SackN;
	struct edge *parent;
	struct vertex *next;
	struct Incidencelist *list;
}vertex;
typedef struct edge {
	int weight;
	struct vertex *start, *end;
	struct edge *next;
}edge;
typedef struct Incidencelist {
	struct edge *val;
	struct Incidencelist *next;
}Incidencelist;
typedef struct Graph {
	int vertexCount;
	struct vertex *VertexRoot;
	struct edge *EdgeRoot;
}Graph;
void InitGraph(Graph **G) {
	*G = (Graph *)malloc(sizeof(Graph));
	(*G)->VertexRoot = NULL;  (*G)->EdgeRoot = NULL; (*G)->vertexCount = 0;
}
vertex *getVertex() {
	vertex *newVertex = (vertex *)malloc(sizeof(vertex));
	newVertex->visited = newVertex->key = 0;
	newVertex->list = NULL;  newVertex->next = NULL; newVertex->parent = NULL;
	return newVertex;
}
Incidencelist *getList() {
	Incidencelist *newList = (Incidencelist *)malloc(sizeof(Incidencelist));
	newList->next = NULL; newList->val = NULL;
	return newList;
}
edge *getEdge() {
	edge *newEdge = (edge *)malloc(sizeof(edge));
	newEdge->next = NULL; newEdge->start = newEdge->end = NULL;
	return newEdge;
}
vertex *SearchVertex(Graph *G, int key) {
	vertex *p = G->VertexRoot;
	while (p != NULL) { if (p->key == key) break; p = p->next; }
	return p;
}
void InsertVertex(Graph *G, int key) {
	vertex *newVertex = getVertex(); newVertex->key = newVertex->SackN = key; newVertex->list = getList();
	if (G->VertexRoot == NULL) G->VertexRoot = newVertex;
	else {
		vertex *p = G->VertexRoot;
		while (p->next != NULL) { p = p->next; }
		p->next = newVertex;
	}
	G->vertexCount++;
}
void Insert_OneEdge(Graph *G, int start, int end, int weight) {
	vertex *S = SearchVertex(G, start); vertex *E = SearchVertex(G, end);
	if (S == NULL || E == NULL) return;

	edge *newEdge = getEdge(); newEdge->start = S; newEdge->end = E; newEdge->weight = weight;
	if (G->EdgeRoot == NULL) G->EdgeRoot = newEdge;
	else {
		edge *p = G->EdgeRoot;
		while (p->next != NULL) p = p->next;
		p->next = newEdge;
	}

	Incidencelist *newList = getList(); newList->val = newEdge;
	Incidencelist *H = S->list;
	while (H->next != NULL) { if (H->next->val->end->key > newEdge->end->key) break; H = H->next; }
	if (H->next == NULL) H->next = newList;
	else { newList->next = H->next; H->next = newList; }
}
void InsertEdges(Graph *G, int start, int end, int weight) {
	if (start != end) { Insert_OneEdge(G, start, end, weight); Insert_OneEdge(G, end, start, weight); }
	else Insert_OneEdge(G, start, end, weight);
}
edge *minEdge(edge **Q, int f, int r) {
	edge *minE = Q[f];
	int minWeight = Q[f]->weight;
	for (int i = f + 1; i <= r; i++) {
		if (minWeight > Q[i]->weight) { 
			minWeight = Q[i]->weight; minE = Q[i];
			edge *tmp = Q[f]; Q[f] = Q[i]; Q[i] = tmp;
		}
	}
	return minE;
}
void KruskalMST(Graph *G) {
	edge **Queue = (edge **)malloc(sizeof(edge *) * 1000);
	int f = 0, r = -1;
	edge *p = G->EdgeRoot;
	while (p != NULL) { if (p->start->key <= p->end->key) Queue[++r] = p; p = p->next; }

	vertex **tmp = (vertex **)malloc(sizeof(vertex*)*G->vertexCount);
	vertex *q = G->VertexRoot;
	int i = 0;
	while (q != NULL) { tmp[i++] = q; q = q->next; }
	
	int result = 0;
	while (f <= r) {
		edge *e = minEdge(Queue, f, r); f++;
		if (e->start->SackN != e->end->SackN) {
			int endSackN = e->end->SackN;
			for (int j = 0; j < G->vertexCount; j++) if (endSackN == tmp[j]->SackN) tmp[j]->SackN = e->start->SackN;
			printf(" %d", e->weight); result += e->weight;
		}
	}
	printf("\n%d", result);
}
int main() {
	Graph *G = NULL; InitGraph(&G);
	int n, m; scanf("%d %d", &n, &m);
	for (int i = 0; i < n; i++) InsertVertex(G, i + 1);
	for (int i = 0; i < m; i++) {
		int src, dest, weight; scanf("%d %d %d", &src, &dest, &weight);
		InsertEdges(G, src, dest, weight);
	}
	KruskalMST(G);
}*/
//최단경로
//1 ---- DijkstraShortestPaths(무방향 그래프 최단경로 찾기)
/*#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)
typedef struct vertex {
	int key; int visited;
	int distance;
	struct edge *parent;
	struct vertex *next;
	struct Incidencelist *list;
}vertex;
typedef struct edge {
	int weight;
	struct vertex *start, *end;
	struct edge *next;
}edge;
typedef struct Incidencelist {
	struct edge *val;
	struct Incidencelist *next;
}Incidencelist;
typedef struct Graph {
	int vertexCount;
	struct vertex *VertexRoot;
	struct edge *EdgeRoot;
}Graph;
void InitGraph(Graph **G) {
	*G = (Graph *)malloc(sizeof(Graph));
	(*G)->VertexRoot = NULL;  (*G)->EdgeRoot = NULL; (*G)->vertexCount = 0;
}
vertex *getVertex() {
	vertex *newVertex = (vertex *)malloc(sizeof(vertex));
	newVertex->visited = newVertex->key = 0;
	newVertex->distance = 1000000000;
	newVertex->list = NULL;  newVertex->next = NULL; newVertex->parent = NULL;
	return newVertex;
}
Incidencelist *getList() {
	Incidencelist *newList = (Incidencelist *)malloc(sizeof(Incidencelist));
	newList->next = NULL; newList->val = NULL;
	return newList;
}
edge *getEdge() {
	edge *newEdge = (edge *)malloc(sizeof(edge));
	newEdge->next = NULL; newEdge->start = newEdge->end = NULL;
	return newEdge;
}
vertex *SearchVertex(Graph *G, int key) {
	vertex *p = G->VertexRoot;
	while (p != NULL) { if (p->key == key) break; p = p->next; }
	return p;
}
void InsertVertex(Graph *G, int key) {
	vertex *newVertex = getVertex(); newVertex->key = key; newVertex->list = getList();
	if (G->VertexRoot == NULL) G->VertexRoot = newVertex;
	else {
		vertex *p = G->VertexRoot;
		while (p->next != NULL) { p = p->next; }
		p->next = newVertex;
	}
	G->vertexCount++;
}
void Insert_OneEdge(Graph *G, int start, int end, int weight) {
	vertex *S = SearchVertex(G, start); vertex *E = SearchVertex(G, end);
	if (S == NULL || E == NULL) return;

	edge *newEdge = getEdge(); newEdge->start = S; newEdge->end = E; newEdge->weight = weight;
	if (G->EdgeRoot == NULL) G->EdgeRoot = newEdge;
	else {
		edge *p = G->EdgeRoot;
		while (p->next != NULL) p = p->next;
		p->next = newEdge;
	}

	Incidencelist *newList = getList(); newList->val = newEdge;
	Incidencelist *H = S->list;
	while (H->next != NULL) { if (H->next->val->end->key > newEdge->end->key) break; H = H->next; }
	if (H->next == NULL) H->next = newList;
	else { newList->next = H->next; H->next = newList; }
}
void InsertEdges(Graph *G, int start, int end, int weight) {
	if (start != end) { Insert_OneEdge(G, start, end, weight); Insert_OneEdge(G, end, start, weight); }
	else Insert_OneEdge(G, start, end, weight);
}
vertex *findMin(vertex **Queue, int f, int r) {
	vertex *min = Queue[f];
	for (int i = f + 1; i <= r; i++) {
		if (min->distance > Queue[i]->distance) {
			min = Queue[i];
			vertex *tmp = Queue[f]; Queue[f] = Queue[i]; Queue[i] = tmp;
		}
	}
	return min;
}

int QueueElement(vertex **Queue, int key, int f, int r) {
	for (int i = f; i <= r; i++)
		if (Queue[i]->key == key) return 1;
	return 0;
}
#define MIN 1000000000
void DijkstraShortestPaths(Graph *G, int src) {
	vertex **Queue = (vertex **)malloc(sizeof(vertex *)*G->vertexCount);
	int f = 0, r = -1;

	vertex *p = G->VertexRoot;
	while (p != NULL) { Queue[++r] = p; p->distance = MIN; p = p->next; }
	vertex *v = SearchVertex(G, src);
	v->distance = 0;

	while (f <= r) {
		vertex *u = findMin(Queue, f, r); f++;
		Incidencelist *p = u->list->next;
		while (p != NULL) {
			vertex *op = p->val->end;
			if (QueueElement(Queue, op->key, f, r)) {
				if (op->distance > u->distance + p->val->weight)
					op->distance = u->distance + p->val->weight;
			}
			p = p->next;
		}
	}
	
	vertex *k = G->VertexRoot;
	while (k != NULL) {
		if (k->distance != MIN && k->key != src) printf("%d %d\n", k->key, k->distance); k = k->next;
	}
}
int main() {
	Graph *G = NULL; InitGraph(&G);
	int n, m, key; scanf("%d %d %d", &n, &m, &key);
	for (int i = 0; i < n; i++) InsertVertex(G, i + 1);
	for (int i = 0; i < m; i++) {
		int start, end, weight; scanf("%d %d %d", &start, &end, &weight);
		InsertEdges(G, start, end, weight);
	}
	DijkstraShortestPaths(G, key);
}*/
//2 ---- Bellman-Ford(방향 그래프 최단경로 찾기)
/*#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)
typedef struct vertex {
	int key; int inlabel; int visited; int distance;
	struct vertex *next;
	struct inedge *inH;
	struct outedge *outH;
}vertex;
typedef struct inedge {
	int weight;
	struct vertex *val;
	struct vertex *in;
	struct inedge *nextEdge;
}inedge;
typedef struct outedge {
	int weight;
	struct vertex *val;
	struct vertex *out;
	struct outedge *nextEdge;
}outedge;
typedef struct Graph {
	int vertexCount;
	struct vertex *VertexRoot;
}Graph;
vertex *getVertex() {
	vertex *newVertex = (vertex *)malloc(sizeof(vertex));
	newVertex->inlabel = newVertex->visited = 0;
	newVertex->inH = newVertex->outH = NULL; newVertex->next = NULL;
	return newVertex;
}
inedge *getInEdge() {
	inedge *newInEdge = (inedge *)malloc(sizeof(inedge));
	newInEdge->val = newInEdge->in = newInEdge->nextEdge = NULL;
	return newInEdge;
}
outedge *getOutEdge() {
	outedge *newOutEdge = (outedge *)malloc(sizeof(outedge));
	newOutEdge->val = newOutEdge->out = NULL; newOutEdge->nextEdge = NULL;
	return newOutEdge;
}
void InitGraph(Graph **G) {
	*G = (Graph *)malloc(sizeof(Graph));
	(*G)->VertexRoot = NULL; (*G)->vertexCount = 0;
}
void InsertVertex(Graph *G, int key) {
	vertex *newVertex = getVertex(); newVertex->key = key;
	if (G->VertexRoot == NULL) G->VertexRoot = newVertex;
	else {
		vertex *p = G->VertexRoot;
		while (p->next != NULL) { p = p->next; }
		p->next = newVertex;
	}
	G->vertexCount++;
}
vertex *SearchVertex(Graph *G, int key) {
	vertex *p = G->VertexRoot;
	while (p != NULL) { if (p->key == key) break; p = p->next; }
	return p;
}
void InsertEdge(Graph *G, int in, int out, int weight) {
	vertex *inVertex = SearchVertex(G, in); vertex *outVertex = SearchVertex(G, out);
	inedge *I = getInEdge(); I->val = outVertex; I->in = inVertex;
	outedge *O = getOutEdge(); O->val = inVertex; O->out = outVertex;
	I->weight = O->weight = weight;
	outVertex->inlabel++;
	if (inVertex->outH == NULL) inVertex->outH = O;
	else {
		O->nextEdge = inVertex->outH;
		inVertex->outH = O;
	}
	if (outVertex->inH == NULL) outVertex->inH = I;
	else {
		I->nextEdge = outVertex->inH;
		outVertex->inH = I;
	}
}

void AvailableToAccess(int *list, vertex *src) {
	if (src == NULL || src->visited) return;
	src->visited = 1;
	outedge *O = src->outH;
	while (O != NULL) {
		list[O->out->key - 1] = 1;
		AvailableToAccess(list, O->out);
		O = O->nextEdge;
	}
}
#define MIN 1000000
void BellmanFordShortestPaths(Graph *G, int src) {
	vertex *p = G->VertexRoot;
	while (p != NULL) { p->distance = MIN; p = p->next; }
	vertex *v = SearchVertex(G, src);
	v->distance = 0;

	for (int i = 1; i < G->vertexCount; i++) {
		vertex *q = G->VertexRoot;
		while (q != NULL) {
			outedge *O = q->outH;
			while (O != NULL) {
				vertex *k = O->val;
				vertex *u = O->out;
				if (u->distance > k->distance + O->weight) {
					u->distance = k->distance + O->weight;
				}
				O = O->nextEdge;
			}
			q = q->next;
		}
	}
	int *list = (int *)malloc(sizeof(int)*G->vertexCount);
	AvailableToAccess(list, v);
	vertex *w = G->VertexRoot;
	for (int i = 0; i < G->vertexCount; i++, w = w->next) {
		if (list[i] == 1 && i != v->key - 1) printf("%d %d\n", w->key, w->distance);
	}
}
int main() {
	Graph *G = NULL; InitGraph(&G);
	int n, m, key; scanf("%d %d %d", &n, &m, &key);
	for (int i = 0; i < n; i++) InsertVertex(G, i + 1);
	for (int i = 0; i < m; i++) {
		int start, end, weight; scanf("%d %d %d", &start, &end, &weight);
		InsertEdge(G, start, end, weight);
	}
	BellmanFordShortestPaths(G, key);
}*/
//과제
/*#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)
typedef struct vertex {
	char key; int visited;
	int distance;
	struct edge *parent;
	struct vertex *next;
	struct Incidencelist *list;
}vertex;
typedef struct edge {
	int weight;
	struct vertex *start, *end;
	struct edge *next;
}edge;
typedef struct Incidencelist {
	struct edge *val;
	struct Incidencelist *next;
}Incidencelist;
typedef struct Graph {
	int vertexCount;
	struct vertex *VertexRoot;
	struct edge *EdgeRoot;
}Graph;
void InitGraph(Graph **G) {
	*G = (Graph *)malloc(sizeof(Graph));
	(*G)->VertexRoot = NULL;  (*G)->EdgeRoot = NULL; (*G)->vertexCount = 0;
}
vertex *getVertex() {
	vertex *newVertex = (vertex *)malloc(sizeof(vertex));
	newVertex->visited = 0;
	newVertex->distance = 1000000000;
	newVertex->list = NULL;  newVertex->next = NULL; newVertex->parent = NULL;
	return newVertex;
}
Incidencelist *getList() {
	Incidencelist *newList = (Incidencelist *)malloc(sizeof(Incidencelist));
	newList->next = NULL; newList->val = NULL;
	return newList;
}
edge *getEdge() {
	edge *newEdge = (edge *)malloc(sizeof(edge));
	newEdge->next = NULL; newEdge->start = newEdge->end = NULL;
	return newEdge;
}
vertex *SearchVertex(Graph *G, char key) {
	vertex *p = G->VertexRoot;
	while (p != NULL) { if (p->key == key) break; p = p->next; }
	return p;
}
void InsertVertex(Graph *G, char key) {
	vertex *newVertex = getVertex(); newVertex->key = key; newVertex->list = getList();
	if (G->VertexRoot == NULL) G->VertexRoot = newVertex;
	else {
		vertex *p = G->VertexRoot;
		while (p->next != NULL) { p = p->next; }
		p->next = newVertex;
	}
	G->vertexCount++;
}
void Insert_OneEdge(Graph *G, char start, char end, int weight) {
	vertex *S = SearchVertex(G, start); vertex *E = SearchVertex(G, end);
	if (S == NULL || E == NULL) return;

	edge *newEdge = getEdge(); newEdge->start = S; newEdge->end = E; newEdge->weight = weight;
	if (G->EdgeRoot == NULL) G->EdgeRoot = newEdge;
	else {
		edge *p = G->EdgeRoot;
		while (p->next != NULL) p = p->next;
		p->next = newEdge;
	}

	Incidencelist *newList = getList(); newList->val = newEdge;
	Incidencelist *H = S->list;
	while (H->next != NULL) { if (H->next->val->end->key > newEdge->end->key) break; H = H->next; }
	if (H->next == NULL) H->next = newList;
	else { newList->next = H->next; H->next = newList; }
}
void InsertEdges(Graph *G, char start, char end, int weight) {
	if (start != end) { Insert_OneEdge(G, start, end, weight); Insert_OneEdge(G, end, start, weight); }
	else Insert_OneEdge(G, start, end, weight);
}
vertex *findMin(vertex **Queue, int f, int r) {
	vertex *min = Queue[f];
	for (int i = f + 1; i <= r; i++) {
		if (min->distance > Queue[i]->distance) {
			min = Queue[i];
			vertex *tmp = Queue[f]; Queue[f] = Queue[i]; Queue[i] = tmp;
		}
	}
	return min;
}
int QueueElement(vertex **Queue, char key, int f, int r) {
	for (int i = f; i <= r; i++)
		if (Queue[i]->key == key) return 1;
	return 0;
}
#define MIN 1000000000
void DijkstraShortestPaths(Graph *G, char src, char dest, int distance, int *min, int *cnt) {
	if(src == dest){
		if (*min > distance) { *min = distance; *cnt = 1; }
		else if (*min == distance) (*cnt)++;
		return;
	}
	vertex *v = SearchVertex(G, src);
	Incidencelist *p = v->list->next;
	while (p != NULL) {
		vertex *z = p->val->end;
		if (!z->visited) {
			z->visited = 1;
			DijkstraShortestPaths(G, z->key, dest, distance + p->val->weight, min, cnt);
			z->visited = 0;
		}
		p = p->next;
	}
}
int main() {
	Graph *G = NULL; InitGraph(&G);
	for (int i = 0; i < 6; i++) InsertVertex(G, (char)('A' + i));
	InsertEdges(G, 'A', 'B', 8); InsertEdges(G, 'A', 'C', 1); InsertEdges(G, 'A', 'D', 4);
	InsertEdges(G, 'B', 'C', 7); InsertEdges(G, 'B', 'E', 4);
	InsertEdges(G, 'C', 'E', 3); InsertEdges(G, 'C', 'F', 9); InsertEdges(G, 'C', 'D', 5);
	InsertEdges(G, 'D', 'F', 4);
	for (int i = 0; i < 4; i++) {
		char src, dest; int min = MIN, cnt = 0;
		if (i == 0) { src = 'C'; dest = 'A'; }
		else if (i == 1) { src = 'C'; dest = 'F'; }
		else if (i == 2) { src = 'F'; dest = 'C'; }
		else { src = 'B'; dest = 'D'; }
		DijkstraShortestPaths(G, src, dest, 0, &min, &cnt);
		printf("%c, %c : 최단거리 =  %d, 최단경로 수 = %d\n", src, dest, min, cnt);
	}
}*/