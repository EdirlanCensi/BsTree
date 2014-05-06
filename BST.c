#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode{
  int element;
  struct TreeNode *left, *right,*parent;
} TreeNode;

typedef struct BsTree{
	struct TreeNode *raiz;
}BsTree;

TreeNode *Consulta(TreeNode *p , int k){

	while( p != NULL && k != p->element){
        if(k < p->element )
            p = p->left;
        else
            p = p->right;
	}
	return p;

}

void ImprimaOrdenado(TreeNode *p){
	if( p!= NULL){
		ImprimaOrdenado(p->left);
		printf("%d ",p->element);
		ImprimaOrdenado(p->right);
	}
}

TreeNode *Minimo(TreeNode *p){
	while (p->left != NULL){
		p = p->left;
	}
	return p;
}

TreeNode *Maximo(TreeNode *p){
	while( p->right != NULL){
        p = p->right;
	}
    return p;
}

void Insira(BsTree *t,int k){

	TreeNode *x = (TreeNode*)malloc(sizeof(TreeNode));
	TreeNode *y, *yAnt;
	x->element = k;
	x->parent = x->left = x->right = NULL;
	y = t->raiz;
	yAnt = NULL;
	while( y != NULL){
		yAnt = y;
		if( k < y->element)
			y = y->left;
		else
			y = y->right;
	}

	if (yAnt == NULL)
		t->raiz = x;
	else if( k < yAnt->element)
		yAnt->left = x;
	else
		yAnt->right =x;
	x->parent = yAnt;
}

void Transplante(BsTree *t,TreeNode *p, TreeNode *q){
	if( p->parent == NULL)
		t->raiz = q;
	else if( p == p->parent->left)
		p->parent->left = q;
	else
		p->parent->right = q;
	if (q != NULL)
		q->parent = p->parent;

}

void Delete( BsTree *t, TreeNode *p){
	TreeNode *y;
	if( p->left == NULL){
		Transplante(t,p,p->right);
	}else if( p->right == NULL){
		Transplante(t, p, p->left);
	}else{
		y = Minimo(p->right);
		if( y != p->right){
			Transplante(t,y,y->right);
			y->right = p->right;
			p->right->parent = y;
		}
		Transplante(t,p,y);
		y->left = p->left;
		p->left->parent = y;
	}
	free(p);
}

TreeNode* SUCESSOR(TreeNode *x){
    TreeNode *y;
    if (x->right != NULL)
        return Minimo(x->right);
    y = x->parent;
    while (y != NULL && x == y->right){
		x = y;
         y = y->parent;
    }
	return y;
}

TreeNode* ANTECESSOR(TreeNode *x){
    TreeNode *y;

    if (x->left != NULL)
        return Maximo(x->left);
    y = x;
    while (y != NULL && x == y->left)
		x = y;
	y = y->parent;
	return y;
}

int main(){
	BsTree *t = (BsTree *)malloc(sizeof(BsTree));
	t->raiz = NULL;
	TreeNode *temp;
	int op,dado;
	do{

		printf("\n1) Inserir Dado\n2) Excluir Dado\n3) Buscar Dado\n4) Imprimir Ordenado\n5) Sucessor\n6) Antecessor\n7) Maximo\n8) Minimo\n9) sair\n");

		scanf("%d",&op);
		if(op == 1){
			printf("Digite o dado a ser inserido na arvore\n\n");
			scanf("%d",&dado);
			Insira(t, dado);
		}else if( op == 2){
			printf("Digite o dado a ser excluido da arvore\n\n");
			scanf("%d",&dado);
			temp = Consulta(t->raiz , dado);
			if(temp != NULL){
				Delete(t,temp);
			}else{
				printf("Dado Inexistente na arvore\n\n");
			}
		}else if(op == 3){
			printf("Digite o dado a ser buscado da arvore\n\n");
			scanf("%d",&dado);
			temp = Consulta(t->raiz , dado);
			if(temp != NULL){
				printf("Dado encontrado no endereço de memoria %p",temp);
			}else{
				printf("Dado Inexistente na arvore\n\n");
			}

		}else if(op == 4){
			ImprimaOrdenado(t->raiz);
		}else if(op == 5){
			scanf("%d",&dado);
			temp = Consulta(t->raiz , dado);
			if(temp != NULL ){
				temp = SUCESSOR(temp);
				if(temp != NULL)
                    printf("SUCESSOR DO %d eh %d\n",dado,temp->element);
			}else{
				printf("Sucessor Inexistente na arvore, retorno NULO\n\n");
			}
		}else if(op == 6){
			scanf("%d",&dado);
			temp = Consulta(t->raiz , dado);
			if(temp != NULL && temp != t->raiz){
				temp = ANTECESSOR(temp);
				if(temp != NULL)
				printf("ANTECESSOR DO %d eh %d\n",dado,temp->element);
			}else{
				printf("Antecessor Inexistente na arvore, retorno NULO\n\n");
			}
		}else if(op == 7){
		    if(t->raiz != NULL){
                temp = Maximo(t->raiz);
                printf("MAXIMO: %d\n",temp->element);
		    }else{
                printf("Arvore Vazia\n");
		    }
		}else if(op == 8){
		    if(t->raiz != NULL){
                temp = Minimo(t->raiz);
                printf("MINIMO: %d\n",temp->element);
		    }else{
                printf("Arvore Vazia\n");
		    }
		}

	}while(op != 9);
	return 0;
}
