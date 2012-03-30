#include <stdio.h>
#include <stdlib.h>
#define RED 1        /* stala oznaczajaca kolor wezla */
#define BLACK 0      /* stala oznaczajaca kolor wezla */

typedef struct W {
	int key;
	struct W *left, *right, *p;
	int kolor;
} wezel;

wezel NIL;

wezel* TREESEARCH(wezel *x, int k){
	if(x==&NIL || k==x->key)
		return x;
	if(k< x->key)
		return TREESEARCH(x->left,k);
	else
		return TREESEARCH(x->right,k);
}
wezel* TREEMIN(wezel *x){
	while(x->left!=&NIL){
		x=x->left;
	}
	return x;
}

wezel* TREESUCC(wezel *x){
	wezel *y;
	if(x->right!=&NIL)
		return TREEMIN(x->right);
	y=x->p;
	while(y!=&NIL && x==y->right){
		x=y;
		y=y->p;
	}
	return y;
}

wezel* LEFTROTATE(wezel *root, wezel *x){
//	printf("robie leftrotate dla %d %d", root->key, x->key);
	wezel *y=x->right;
	x->right=y->left; //lewe poddrzewo na prawe
	if (y->left != &NIL)
	  y->left->p=x;
	y->p=x->p;  //ojcem y uczyn ojca x
	if(x->p==&NIL)
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
	if (y->right != &NIL)
	  y->right->p=x;
	y->p=x->p;  //ojcem y uczyn ojca x
	if(x->p==&NIL)
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
			if(w->kolor==RED){				//PRZYPADEK 1
				w->kolor=BLACK;				//PRZYPADEK 1
				x->p->kolor=RED;			//PRZYPADEK 1
				root=LEFTROTATE(root,x->p); //PRZYPADEK 1
				w=x->p->right;
				}
			if(w->left->kolor==BLACK && w->right->kolor==BLACK){
				w->kolor=RED;				//PRZYPADEK 2
				x=x->p;						//PRZYPADEK 2
			}
			else{
				if(w->right->kolor==BLACK){
					w->left->kolor=BLACK;	//PRZYPADEK 3
					w->kolor=RED;			//PRZYPADEK 3
					root=RIGHTROTATE(root,w);//PRZYPADEK 3
					w=x->p->right;			//PRZYPADEK 3
				}
				w->kolor=x->p->kolor;		//PRZYPADEK 4
				x->p->kolor=BLACK;			//PRZYPADEK 4
				w->right->kolor=BLACK;		//PRZYPADEK 4
				root=LEFTROTATE(root,x->p);	//PRZYPADEK 4
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
	}
	x->kolor=BLACK;
	return root;
}

wezel* RBDEL(wezel *root, wezel *z){
	wezel *x, *y;
	if(z->left==&NIL || z->right==&NIL)
		y=z;
	else
		y=TREESUCC(z);
	if(y->left!=&NIL)
		x=y->left;
	else
		x=y->right;
	x->p=y->p;
	if(y->p==&NIL)
		root=x;
	else{
		if(y==y->p->left)
			y->p->left=x;
		else
			y->p->right=x;
	}
	if(y!=z){
		z->key=y->key;
		//z->left= y->left;
		//z->right= y->right;
		z->kolor= y->kolor;
		//z->p= y->p;
	}
	if(y->kolor==BLACK)
		root=RBDELFIX(root,x);
	return root;
}

wezel* RBFIX(wezel *root, wezel *z){
	wezel *y;

//	printf("RBFIX dla (%d,%d)\n", root->key, z->key);
	while(root!=z && z->p->kolor==RED){
		if(z->p == z->p->p->left){
//	printf("ojciec %d  jest po lewej stronie dziadka \n", z->key);
			y = z->p->p->right;
			if(y!= &NIL && y->kolor==RED){
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
			if(y!= &NIL && y->kolor==RED){
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
//	if (root!=&NIL)
//		printf("root ma wartosc %d\n",root->key);
	wezel *y, *x, *z;
	y=&NIL;
	x=root;
	while(x!=&NIL) {
		y=x;
		if(wartosc < x->key)
			x= x->left;
		else x= x->right;
	}
	z = malloc(sizeof(wezel));
	z->p = y;
	z->key = wartosc;
	z->left = &NIL;
	z->right = &NIL;
	z->kolor=RED;
	if(y==&NIL){
		root=z;
	}
	else {
		if(z->key < y->key)
			y->left=z;
		else
			y->right = z;
	}
	root=RBFIX(root,z);
	root->p=&NIL;
	return root;
}

void wyswietl(wezel* root) {
	if (root!=&NIL) {
		printf("%d ",root->key);
		if(root->kolor==RED)   // jaki kolor
			printf("[style=filled, fillcolor=red]\n");
		else
			printf("[style=filled, fillcolor=gray]\n");
		if (root->left!=&NIL || root->right!=&NIL) {
			if (root->left!=&NIL ) {
				printf("%d->%d;",root->key, root->left->key);
			}
			if (root->right!=&NIL ) {
				printf("%d->%d;",root->key,root->right->key);
			}
			printf("\n");
			if (root->left!=&NIL ) {
				wyswietl(root->left);
			}
			if (root->right!=&NIL ) {
				wyswietl(root->right);
			}
		}
	}
}

int main() {
	int wartosc;
	char znak;
	wezel *root=&NIL;
	NIL.key=-1;
	NIL.left=&NIL;
	NIL.right=&NIL;
	NIL.kolor=BLACK;
	//printf("Co chcesz zrobic? ");
	while(znak!='x') {
		scanf("%c", &znak);
		if(znak=='+'){
			scanf("%d",&wartosc);
			if(TREESEARCH(root, wartosc)==&NIL)  // spr czy klucz juz istnieje
				root = RBinsert(root,wartosc);
			else
				printf("BLAD! taki klucz juz istnieje \n");
		}
		if(znak=='-'){
			scanf("%d",&wartosc);
			root=RBDEL(root, TREESEARCH(root, wartosc));

		}
		if(znak=='p'){
			printf("digraph G {\n");
			wyswietl(root);
			printf("}\n");
		}
	}
	//printf("Narazie..");
	return 0;
}
