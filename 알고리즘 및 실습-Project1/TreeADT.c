//탐색트리 ADT
/*#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)
//Data type ---- structure
typedef struct node {
	int key;
	struct node *left, *right, *parent;
}node;
typedef struct Tree {
	node *root;
}Tree;
//--------------------------------------------------
//---------------General Method------------------
//Node initialize
node *getnode() {
	node *tmp = (node *)malloc(sizeof(node*));
	tmp->key = -1;
	tmp->left = tmp->right = tmp->parent = NULL;
	return tmp;
}
//Tree initialize
void initTree(Tree *T) { T->root = getnode(); }
//If it's external return 1
int isExternal(node *root) {
	if (root->left == NULL && root->right == NULL) return 1;
	else return 0;
}
//If it's internal return 1
int isInternal(node *root) {
	if (root->left != NULL || root->right != NULL) return 1;
	else return 0;
}
//GetSibling
node *sibling(node *root) {
	if (root->parent == NULL) return NULL;
	if (root->parent->left == root) return root->parent->right;
	else return root->parent->left;
}
//----------------------------------------------------
//----------------Search Function-------------------
//Search specific node
node *treeSearch(node *root, int key) {
	if (isExternal(root)) return root;
	if (root->key == key) return root;
	else if (root->key > key) return treeSearch(root->left, key);
	else return treeSearch(root->right, key);
}
//Search for node key
int findElement(Tree *T, int key) {
	node *tmp = treeSearch(T->root, key);
	if (isExternal(tmp)) return -1;
	else return tmp->key;
}
//-----------------------------------------------------
//-----------------Insert Function-------------------
void expandExternal(node *root) {
	node *left = getnode(); node *right = getnode();
	left->parent = right->parent = root;
	root->left = left; root->right = right;
}
void Insertitem(Tree *T, int key) {
	node *newnode = treeSearch(T->root, key);
	if (isInternal(newnode)) return;
	newnode->key = key;
	expandExternal(newnode);
}
//-----------------------------------------------------
//-----------------Delete Function-------------------
//Reconnecting Nodes(By searching DeleteNode's external node z)
void reduceExternal(Tree *T, node *z) {
	node *p = z->parent;

	node *zs = sibling(z);
	if (p->parent == NULL) { T->root = zs; zs->parent = NULL; }
	else {
		node *g = p->parent;
		zs->parent = g;
		if (g->left == p) g->left = zs;
		else g->right = zs;
	}
	free(p);
	free(z);
}
//Searching for inOrderSuccessor
node *inOrderSucc(node *root) {
	node *w = root->right;
	if (isExternal(w)) return NULL;
	while (isInternal(w->left)) w = w->left;
	return w;
}
//Remove specific node
int removeItem(Tree *T, int key) {
	node *delnode = treeSearch(T->root, key);
	if (isExternal(delnode)) return -1;

	int elem = delnode->key;
	node *z = delnode->left;
	if (!isExternal(z)) z = delnode->right;
	if (isExternal(z)) reduceExternal(T, z);
	else {
		node *y = inOrderSucc(delnode);
		z = y->left;
		delnode->key = y->key;
		reduceExternal(T, z);
	}
	return elem;
}
//Main
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
//AVL트리 ADT
/*#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)
//Data type --- structure
typedef struct node {
	int key, height;	//Organize depend on height
	struct node *left, *right, *parent;
}node;
typedef struct Tree {
	node *root;
}Tree;
//-------------------------------------------
//------------General Method-------------
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
//---------------------------------------------
//-------------Search Function---------------
node *inOrderSucc(node *root) {
	node *w = root->right;
	if (isExternal(w)) return NULL;
	while (isInternal(w->left)) { w = w->left; }
	return w;
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
int findElement(Tree *T, int key) {
	node *n = treeSearch(T->root, key);
	if (isExternal(n)) return -1;
	else return n->key;
}
//---------------------------------------------------------------
//--------------Restructure Func(Very Important)--------------
//Restructure Node by rotating
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
//-----------------Fix After Insertion-------------------
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
//------------------Fix After Removal---------------------
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
//---------------------------------------------------------
//-------------------Insert Func-------------------------
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
//--------------------------------------------------------
//-------------------Remove Func-----------------------
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
//--------------------------------------------------
//-------------------Print Tree---------------------
void Preordertraverse(node *root) {
	if (root->key == -1) return;
	printf(" %d", root->key);
	Preordertraverse(root->left);
	Preordertraverse(root->right);
}
//---------------------------------------------------
//Main
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