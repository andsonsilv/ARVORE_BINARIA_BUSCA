/* Operações em árvores binária de busca
** Informações associada a um nó é um número inteiro;
** Não vamos considerar a possibilidade de repetição de valores associados aos nós da árvore
*/

#include<stdio.h>
#include<stdlib.h>

typedef struct arv{
    int info;
    struct Arv* esq;
    struct Arv* dir;
}Arv;

Arv* abb_cria(void){

    return NULL;

}

/* IMPRIMINDO ORDEM CRESCENTE */
void abb_imprime(Arv* a){

    if(a != NULL){
        abb_imprime(a->esq);
        printf("%d",a->info);
        abb_imprime(a->dir);
    }

}

Arv* abb_busca(Arv* a, int valor){

    if(a == NULL) return NULL;
    else if(a->info > valor) abb_busca(a->esq,valor);
    else if(a->info < valor) abb_busca(a->dir,valor);
    else return a;

}

Arv* abb_insere(Arv* a, int valor){

    if(a == NULL){
        a = (Arv*) malloc(sizeof(Arv));
        a->info = valor;
        a->esq = a->dir = NULL;
    }
    else if(a->info > valor){
        a->esq = abb_insere(a->esq,valor);
    }
    else{
        a->dir = abb_insere(a->dir,valor);
    }
    return a;

} 

Arv* abb_retira(Arv* a, int valor){

    if(a == NULL)
        return NULL;
    else if(a->info > valor)
        a->esq = abb_retira(a->esq,valor);
    else if(a->info < valor)
        a->dir = abb_retira(a->dir,valor);
    else{
        /* ACHOU O ELEMENTO */
        /* 1º CASO: ELEMENTO SEM FILHOS */
        if((a->esq == NULL) && (a->dir == NULL)){
            free(a);
            a = NULL;
        }
        /* 2º CASO: SÓ TEM FILHOS À DIREITA */
        else if(a->esq == NULL){
            Arv* aux = a;
            a = a->dir;
            free(aux);
        }
        /* 3º CASO: SÓ TEM FILHOS À ESQUERDA */
        else if(a->dir == NULL){
            Arv* aux = a;
            a = a->esq;
            free(aux);
        }
        /* 4º CASO: TEM OS DOIS FILHOS */
        else{
            Arv* aux = a->esq;
            while(aux->dir != NULL){
                aux = aux->dir;
            }
            a->info = aux->info; //Troca de valores
            aux->info = valor;
            a->esq = abb_retira(a->esq,valor);
        }
    }

    return a;

}

int abb_altura(Arv* a){

    int qtd_esq, qtd_dir;

    if(a == NULL)
        return 0;

    qtd_esq = abb_altura(a->esq);
    qtd_dir = abb_altura(a->dir);
    
    if(qtd_esq > qtd_dir)
        return 1 + qtd_esq;
    else
        return 1 + qtd_dir;

}

int abb_num_folhas(Arv* a){

    if(a == NULL)
        return 0;
    if((a->esq == NULL) && (a->dir == NULL))
        return 1;
    return abb_num_folhas(a->esq) + abb_num_folhas(a->dir);

}

void abb_pre_ordem(Arv* a){

    if(a != NULL){
        printf("%d ",a->info);
        abb_pre_ordem(a->esq);
        abb_pre_ordem(a->dir);
    }

}

void abb_inordem(Arv* a){

    if(a != NULL){
        abb_inordem(a->esq);
        printf("%d ",a->info);
        abb_inordem(a->dir);
    }

}

void abb_pos_ordem(Arv* a){

    if(a != NULL){
        abb_pos_ordem(a->esq);
        abb_pos_ordem(a->dir);
        printf("%d ",a->info);
    }

}

Arv* abb_minimo(Arv* a){

    if(a == NULL || a->esq == NULL)
        return a;
    return abb_minimo(a->esq);

}

Arv* abb_maximo(Arv* a){

    if(a == NULL || a->dir == NULL)
        return a;
    return abb_maximo(a->dir);

}

int abb_iguais(Arv* a, Arv* b){

    if(a == NULL && b == NULL)
        return 1;
    if(a == NULL && b == NULL)
        return 0;
    return ((a->info == b->info) && abb_iguais(a->esq,b->esq) && abb_iguais(a->dir,b->dir));

}

int main(void){

    Arv* arvore = abb_cria();
    
    arvore = abb_insere(arvore,2);
    arvore = abb_insere(arvore,5);
    arvore = abb_insere(arvore,7);
    arvore = abb_insere(arvore,1);
    

    printf("Essas árvores tem %d folhas\n",abb_num_folhas(arvore));

    printf("A árvore tem %d de altura\n",abb_altura(arvore));

    abb_pre_ordem(arvore);
    printf("\n");
    abb_inordem(arvore);
    printf("\n");
    abb_pos_ordem(arvore);
    printf("\n");
    
    printf("Mínimo é: %d\n",abb_minimo(arvore)->info);
    printf("Máximo é: %d\n",abb_maximo(arvore)->info);
    return 0;

}