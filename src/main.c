#include <stdio.h>
#include <stdlib.h>

struct TreeNode {
    int val;
    struct TreeNode* left;
    struct TreeNode* right;
};

struct TreeNode* Inserir(struct TreeNode* root, int val) {
    if(root==NULL) {
        struct TreeNode* aux = (struct TreeNode*)malloc(sizeof(struct TreeNode));
        aux->val = val;
        aux->left = NULL;
        aux->right = NULL;
        return aux;
    } else {
        if(val < root->val) {
            root->left = Inserir(root->left, val);
        } else {
            root->right = Inserir(root->right, val);
        }
        return root;
    }
}

int Altura(struct TreeNode* root) {
    if(root == NULL) {
        return -1;
    }

    int esq = Altura(root->left);
    int dir = Altura(root->right);

    if(esq > dir) {
        return esq + 1;
    } else {
        return dir + 1;
    }
}

void ContarNos(struct TreeNode* root, int* contagem, int nivel) {
    if(root != NULL) {
        contagem[nivel]++;
        ContarNos(root->left, contagem, nivel + 1);
        ContarNos(root->right, contagem, nivel + 1);
    }
}

void Preencher(struct TreeNode* root, int** vet, int* pos, int nivel) {
    if(root != NULL) {
        vet[nivel][pos[nivel]] = root->val;
        pos[nivel]++;

        Preencher(root->left, vet, pos, nivel + 1);
        Preencher(root->right, vet, pos, nivel + 1);
    }
}

void Inverter(int vet[], int tam) {
    int i = 0;
    int j = tam - 1;

    while(i < j) {
        int aux = vet[i];
        vet[i] = vet[j];
        vet[j] = aux;
        i++;
        j--;
    }
}

int** zigzagLevelOrder(struct TreeNode* root, int* returnSize, int** returnColumnSizes) {
    if(root == NULL) {
        *returnSize = 0;
        *returnColumnSizes = NULL;
        return NULL;
    }

    int tam = Altura(root) + 1;
    *returnSize = tam;

    int* contagem = (int*)calloc(tam, sizeof(int));

    ContarNos(root, contagem, 0);

    int** resposta = (int**)malloc(sizeof(int*) * tam);

    *returnColumnSizes = (int*)malloc(sizeof(int) * tam);

    for(int i = 0; i < tam; i++) {
        resposta[i] = (int*)malloc(sizeof(int) * contagem[i]);
        (*returnColumnSizes)[i] = contagem[i];
    }

    int* pos = (int*)calloc(tam, sizeof(int));

    Preencher(root, resposta, pos, 0);

    for(int i = 0; i < *returnSize; i++) {
        if(i % 2 == 1) {
            Inverter(resposta[i], (*returnColumnSizes)[i]);
        }
    }

    return resposta;
}

void Imprimir(struct TreeNode* root) {
    if(root!=NULL) {
        Imprimir(root->left);
        printf("%d ", root->val);
        Imprimir(root->right);
    }
}

int main() {
    
    struct TreeNode* arv = NULL;
    int returnSize;
    int* returnColumnSizes;

    arv = Inserir(arv, 3);
    arv = Inserir(arv, 1);
    arv = Inserir(arv, 20);
    arv = Inserir(arv, 15);
    arv = Inserir(arv, 27);

    printf("Arvore: ");
    Imprimir(arv);

    int** vet = zigzagLevelOrder(arv, &returnSize, &returnColumnSizes);

    printf("\n");

    for(int i = 0; i < returnSize; i++) {
        for(int j = 0; j < returnColumnSizes[i]; j++) {
            printf("%d ", vet[i][j]);
        }
        printf(" ");
    }

    return 0;
}