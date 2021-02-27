
// Gerar uma tabela de valores inteiros entre 50 e 150 e, a partir dela, criar uma tabela de 
// dados agrupados em classes, e algumas estatisticas básicas, como Média, 
// Moda, Mediana, Variância e Desvio-padrão.

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>
#include <math.h>

// Funções auxiliares

int menor(int *lista, int tamanho) {
    int menor = lista[0];
    for (int i = 1; i < tamanho; i++) {
        if (lista[i] < menor) {
            menor = lista[i];
        }
    }
    return menor;
}


int main(int argc, char const *argv[])
{
    setlocale(LC_ALL, "Portuguese");
    srand(time(NULL));

    int n;          // Valor informado pelo usuário da quantidade de valores da tabela de dados
    int *tabela;    // Tabela de valores inteiros gerada aleatoriamente, em função de 'n'
    int k;          // Informa o número de classes após dados serem agrupados

    printf("\n Quantos dados tem sua tabela ? \n > ");
    scanf("%d", &n);

    // Gerando os dados da tabela
    tabela = (int*)calloc(n,sizeof(int));
    if (tabela==NULL) {
        printf("\n Erro de alocação de memória !\n");
    }
    
    for (int i = 0; i < n; i++) {
        tabela[i] = 30 + (rand()%100);
    }

    // Imprimindo os dados gerados
    printf("\n Dados obtidos:\n\n");
    for (int i = 0; i < n; i++) {
        printf(" %3d", tabela[i]);
        if ((i+1)%30 == 0) {
            printf("\n");
        }        
    }    
    
    k = round(sqrt(n));

    printf("\n\n Preparacao para agrupamento de dados:");
    printf("\n Número de classes: %d", k);
    printf("\n Menor valor da tabela de dados: %d", menor(tabela, n));

    return 0;
}

