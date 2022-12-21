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
#include <stdio.h>
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
}