//Graph ADT
//---------무방향 그래프--------
/*#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)
//Data types
typedef struct vertex {
	int key; int visited;
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
//---------------------------------------------
//----Initialize vertex, edge, Incidencelist----
vertex *getVertex() {
	vertex *newVertex = (vertex *)malloc(sizeof(vertex));
	newVertex->visited = newVertex->key = 0;
	newVertex->list = newVertex->next = NULL;
}
edge *getEdge() {
	edge *newEdge = (edge *)malloc(sizeof(edge));
	newEdge->next = newEdge->start = newEdge->end = NULL;
}
Incidencelist *getList() {
	Incidencelist *newList = (Incidencelist *)malloc(sizeof(Incidencelist));
	newList->next = newList->val = NULL;
}
//Initialize Graph
void InitGraph(Graph **G) {
	*G = (Graph *)malloc(sizeof(Graph));
	(*G)->VertexRoot = getVertex(); (*G)->EdgeRoot = getEdge(); (*G)->vertexCount = 0;
}
//----------------------------------------------------------
//--------------------Search Function---------------------
//Search for vertex
vertex *SearchVertex(Graph *G, int key) {
	vertex *p = G->VertexRoot->next;
	while (p != NULL) { if (p->key == key) break; p = p->next; }
	return p;
}
//Search for Edge
edge *SearchEdge(Graph *G, int start, int end) {
	edge *p = G->EdgeRoot->next;
	while (p != NULL) { if (p->start->key == start && p->end->key == end) break; p = p->next; }
	return p;
}
//-----------------------------------------------------
//------------------Insert Fucntion-------------------
//Insert Vertex
void InsertVertex(Graph *G, int key) {
	vertex *newVertex = getVertex(); newVertex->key = key; newVertex->list = getList();
	vertex *p = G->VertexRoot;
	while (p->next != NULL) { p = p->next; }
	p->next = newVertex;
	G->vertexCount++;
}
//Insert Single Edge
void Insert_OneEdge(Graph *G, int start, int end) {
	vertex *S = SearchVertex(G, start); vertex *E = SearchVertex(G, end);
	if (S == NULL || E == NULL) return;

	edge *newEdge = getEdge(); newEdge->start = S; newEdge->end = E;
	edge *p = G->EdgeRoot;
	while (p->next != NULL) p = p->next;
	p->next = newEdge;

	Incidencelist *newList = getList(); newList->val = newEdge;
	Incidencelist *H = S->list;
	while (H->next != NULL) { if (H->next->val->end->key > newEdge->end->key) break; H = H->next; }
	if (H->next == NULL) H->next = newList;
	else { newList->next = H->next; H->next = newList; }
}
//Insert Edges
void InsertEdges(Graph *G, int start, int end) {
	if (start != end) { Insert_OneEdge(G, start, end); Insert_OneEdge(G, end, start); }
	else Insert_OneEdge(G, start, end);
}
//-------------------------------------------------------------
//---------------------Delete Functions----------------------
void Delete_OneEdge(Graph *G, int start, int end) {
	vertex *S = SearchVertex(G, start); vertex *E = SearchVertex(G, end);
	if (S == NULL || E == NULL) return;

	edge *q = G->EdgeRoot;
	while (q->next != NULL) { if (q->next->start->key == start && q->next->end->key == end) break; q = q->next; }
	edge *del = q->next;
	q->next = del->next;

	Incidencelist *p = S->list;
	while (p->next != NULL) { if (p->next->val->end->key == end) break; p = p->next; }
	Incidencelist *delI = p->next;
	p->next = delI->next;

	free(del); free(delI);
}
void DeleteEdges(Graph *G, int start, int end) {
	if (start != end) { Delete_OneEdge(G, start, end); Delete_OneEdge(G, end, start); }
	else Delete_OneEdge(G, start, end);
}
void PrintGraph(Graph *G) {
	vertex *p = G->VertexRoot->next;
	while (p != NULL) { 
		printf("%d\n", p->key);
		Incidencelist *q = p->list->next;
		while (q != NULL) { printf("%d %d ", q->val->start->key, q->val->end->key); q = q->next; }
		printf("\n");
		p = p->next;
	}
}
int main() {
	Graph *G = NULL; InitGraph(&G);
	int vertexC, edgeC; int start, end;
	scanf("%d %d", &vertexC, &edgeC);
	for (int i = 0; i < vertexC; i++) InsertVertex(G, i + 1);
	for (int i = 0; i < edgeC; i++) { scanf("%d %d", &start, &end); InsertEdges(G, start, end); }
	PrintGraph(G);
}*/
//그래프 순회-------------------DFS(깊이 우선 순회)
/*void DFS(vertex *u) {
	printf("%d\n", u->key); u->visited = 1;
	for (Incidencelist *p = u->list->next; p != NULL; p = p->next)
		if (!p->val->end->visited) DFS(p->val->end);
}*/
//그래프 순회-------------------BFS(너비 우선 순회)
/*void BFS(Graph *G, int key) {
	vertex *v = SearchVertex(G, key);
	vertex **Queue = (vertex **)malloc(sizeof(vertex*)*G->vertexCount);
	int f = 0, r = -1;
	Queue[(++r) % G->vertexCount] = v; v->visited = 1;
	while (f <= r) {
		vertex *e = Queue[(f++) % G->vertexCount];
		printf("%d\n", e->key);
		Incidencelist *p = e->list->next;
		while (p != NULL) {
			if (!p->val->end->visited) { p->val->end->visited = 1; Queue[(++r) % G->vertexCount] = p->val->end; }
		}
	}
}*/
//---------------------------------방향 그래프
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
//-----------------General Method------------------------
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
vertex *SearchVertex(Graph *G, char key) {
	vertex *p = G->VertexRoot;
	while (p != NULL) { if (p->key == key) break; p = p->next; }
	return p;
}
//-------------------------------------------------------------
//---------------------Insert Function------------------------
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
//------------------------------------------------------------------
//----------------------------------------위상정렬 알고리즘(DAG)
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
//---------------------------------최소신장트리
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
//-------------------------------최단 경로 및 경로의 갯수 구하는 함수
/*void DijkstraShortestPaths(Graph *G, char src, char dest, int distance, int *min, int *cnt) {
	if (src == dest) {
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
}*/