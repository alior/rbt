#include <stdio.h>
#include <stdlib.h>
#define RED 1        /* stala oznaczajaca kolor wezla */
#define BLACK 0      /* stala oznaczajaca kolor wezla */

typedef struct W {
	int key;
	struct W *left, *right, *p;
	int kolor;
} wezel;

//wezel* FINDFATHER(wezel y, wezel *x){
//	if(y->left==x || y->right==x)
//		return y;
//	y=FINDFATHER(y->left, x);
//}
wezel* TREESEARCH(wezel *x, int k){
	if(x==NULL || k==x->key)
		return x;
	if(k< x->key)
		return TREESEARCH(x->left,k);
	else
		return TREESEARCH(x->right,k);
}
wezel* TREEMIN(wezel *x){
	while(x->left!=NULL){
		x=x->left;
	}
	return x;
}

wezel* TREESUCC(wezel *x){
	wezel *y;
	if(x->right!=NULL)
		return TREEMIN(x->right);
	y=x->p;
	while(y!=NULL && x==y->right){
		x=y;
		y=y->p;
	}
	return y;
}

wezel* LEFTROTATE(wezel *root, wezel *x){
//	printf("robie leftrotate dla %d %d", root->key, x->key);
	wezel *y=x->right;
	x->right=y->left; //lewe poddrzewo na prawe
	if (y->left != NULL)
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
//  printf("robie rightroteate dla %d %d", root->key, x->key);
	wezel *y=x->left;
	x->left=y->right; //lewe poddrzewo na prawe
	if (y->right != NULL)
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

wezel *RBDELFIX(wezel*root, wezel *x){
	wezel *w;
	while(x!=root && x->kolor==BLACK){
		if(x==x->p->left){
			w=x->p->right;
			if(w->kolor==RED){
				w->kolor=BLACK;
				x->p->kolor=RED;
				root=LEFTROTATE(root,x->p);
				w=x->p->right;
				}
			if(w->left->kolor==BLACK && w->right->kolor==BLACK){
				w->kolor=RED;
				x=x->p;
			}
			else{
				if(w->right->kolor==BLACK){
					w->left->kolor=BLACK;
					w->kolor=RED;
					root=RIGHTROTATE(root,w);
					w=x->p->right;
				}
				w->kolor=x->p->kolor;
				x->p->kolor=BLACK;
				w->right->kolor=BLACK;
				root=LEFTROTATE(root,x->p);
				x=root;
			}
		}
		else{
			w=x->p->left;
			if(w->kolor==RED){
				w->kolor=BLACK;
				x->p->kolor=RED;
				root=RIGHTROTATE(root,x->p);
				w=x->p->left;
				}
			if(w->right->kolor==BLACK && w->left->kolor==BLACK){
				w->kolor=RED;
				x=x->p;
			}
			else{
				if(w->left->kolor==BLACK){
					w->right->kolor=BLACK;
					w->kolor=RED;
					root=LEFTROTATE(root,w);
					w=x->p->left;
				}
				w->kolor=x->p->kolor;
				x->p->kolor=BLACK;
				w->left->kolor=BLACK;
				root=RIGHTROTATE(root,x->p);
				x=root;
			}
		}
	x->kolor=BLACK;
	return root;
	}
}


wezel* RBDEL(wezel *root, wezel *z){
	wezel *x, *y;
	if(z->left==NULL || z->right==NULL)
		y=z;
	else
		y=TREESUCC(z);
	if(y->left!=NULL)
		x=y->left;
	else
		x=y->right;
	if(x!=NULL)
		x->p=y->p;
	if(y->p==NULL)
		root=x;
	else{
		if(y==y->p->left)
			y->p->left=x;
		else
			y->p->right=x;
	}
	if(y!=z){
		z->key=y->key;
		z->left= y->left;
		z->right= y->right;
		z->kolor= y->kolor;
		z->p= y->p;
	}
	if(y->kolor==BLACK)
		root=RBDELFIX(root,x);
	return y;
}

wezel* RBFIX(wezel *root, wezel *z){
	wezel *y;

//	printf("RBFIX dla (%d,%d)\n", root->key, z->key);
	while(root!=z && z->p->kolor==RED){
		if(z->p == z->p->p->left){
//	printf("ojciec %d  jest po lewej stronie dziadka \n", z->key);
			y = z->p->p->right;
			if(y!= NULL && y->kolor==RED){
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
		  //printf("ojciec %d  jest po prawej stronie dziadka \n", z->key);
			y = z->p->p->left;
			if(y!= NULL && y->kolor==RED){
				z->p->kolor=BLACK;
				y->kolor=BLACK;
				z->p->p->kolor=RED;
				z = z->p->p;
			}
			else {
//			  printf("Po lewej stronie dziadka jest czarny wezel\n");
			  if(z==z->p->left){
//			    printf("%d jest lewym synem %d\n", z->key, z->p->key);
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
//  printf("Dodaje %d do drzewa\n",wartosc);
//	if (root!=NULL)
//		printf("root ma wartosc %d\n",root->key);
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
	wezel *root=NULL, *zm=NULL;
	//printf("Co chcesz zrobic? ");
	while(znak!='x') {
		scanf("%c", &znak);
		if(znak=='+'){
			scanf("%d",&wartosc);
			if(TREESEARCH(root, wartosc)==NULL)  // spr czy klucz juz istnieje
				root = RBinsert(root,wartosc);
			else
				printf("BLAD! taki klucz juz istnieje \n");
		}
		if(znak=='-'){
			scanf("%d",&wartosc);
			zm=RBDEL(root, TREESEARCH(root, wartosc));
			//printf("usunalem %d \n", zm->key);
		}
		else if(znak=='p'){
			printf("digraph G {\n");
			wyswietl(root);
			printf("}\n");
		}
	}
	//printf("Narazie..");
	return 0;
}
