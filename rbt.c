#include <stdio.h>
#include <stdlib.h>
#define RED 1        /* stala oznaczajaca kolor wezla */
#define BLACK 0      /* stala oznaczajaca kolor wezla */

typedef struct W {
	int key;
	struct W *left, *right, *p;
	int kolor;
} wezel;

wezel* LEFTROTATE(wezel *root, wezel *x){
	wezel *y=x->right;
	x->right=x->left; //lewe poddrzewo na prawe
	y->left->p=x;
	y->p=x->p;  //ojcem y uczyn ojca x
	if(x->p==NULL)
		root=y;

	else {
		if (x==x->p->left)
			x->p->left=y;
		else x->p->right=y;
	}
	y->left=x;
	x->p=y;
	return root;
}

wezel* RIGHTROTATE(wezel *root, wezel *x){
	wezel *y=x->left;
	x->left=x->right; //lewe poddrzewo na prawe
	y->right->p=x;
	y->p=x->p;  //ojcem y uczyn ojca x
	if(x->p==NULL)
		root=y;
	else {
		if (x==x->p->right)
			x->p->right=y;
		else x->p->left=y;
	}
	y->right=x;
	x->p=y;
	return root;
}

wezel* RBFIX(wezel *root, wezel *z){
	wezel *y;

	while(root!=z && z->p->kolor==RED){
		if(z->p == z->p->p->left){
			y = z->p->p->right;
			if(y->kolor==RED){
				z->p->kolor=BLACK;
				y->kolor=BLACK;
				z->p->p->kolor=RED;
				z = z->p->p;
			}
			else{
				if(z==z->p->right){
				z=z->p;
				root=LEFTROTATE(root,z);
				}
				z->p->kolor=BLACK;
				z->p->p->kolor=RED;
				root=RIGHTROTATE(root,z->p->p);
			}
		}
		else{
			y = z->p->p->left;
			if(y->kolor==RED){
				z->p->kolor=BLACK;
				y->kolor=BLACK;
				z->p->p->kolor=RED;
				z = z->p->p;
			}
			else{
				if(z==z->p->left){
				z=z->p;
				root=RIGHTROTATE(root, z);
				}
				z->p->kolor=BLACK;
				z->p->p->kolor=RED;
				root=LEFTROTATE(root, z->p->p);
			}
		}
	}
	root->kolor = BLACK;
	return root;
}

wezel* RBinsert(wezel *root,int wartosc) {
	if (root!=NULL)
		printf("root ma wartosc %d\n",root->key);
	wezel *y, *x, *z;
	y=NULL;
	x=root;
	while(x!=NULL) {
		y=x;
		if(wartosc < x->key)
			x= x->left;
		else x= x->right;
	}
	z = malloc(sizeof(wezel));
	z->p = y;
	z->key = wartosc;
	z->left = NULL;
	z->right = NULL;
	z->kolor=RED;
	if(y==NULL){
		root=z;
	}
	else {
		if(z->key < y->key)
			y->left=z;
		else
			y->right = z;
	}
	root=RBFIX(root,z);
	return root;
}

void wyswietl(wezel* root) {
	if (root!=NULL) {
		printf("%d ",root->key);
		if(root->kolor==RED)   // jaki kolor
			printf("[style=filled, fillcolor=red]\n");
		else
			printf("[style=filled, fillcolor=gray]\n");
		if (root->left!=NULL || root->right!=NULL) {
			if (root->left!=NULL ) {
				printf("%d->%d;",root->key, root->left->key);
			}
			if (root->right!=NULL ) {
				printf("%d->%d;",root->key,root->right->key);
			}
			printf("\n");
			if (root->left!=NULL ) {
				wyswietl(root->left);
			}
			if (root->right!=NULL ) {
				wyswietl(root->right);
			}
		}
	}
}

int main() {
	int wartosc;
	char znak;
	wezel *root=NULL;
	printf("Co chcesz zrobic? ");
	while(znak!='x') {
		scanf("%c", &znak);
		if(znak=='+'){
			scanf("%d",&wartosc);
			root = RBinsert(root,wartosc);
		}
		else if(znak=='p'){
			printf("digraph G {\n");
			wyswietl(root);
			printf("}");
		}
//		printf("\n")
	}
	printf("Narazie..");
	return 0;
}
