
// Gerar uma tabela de valores inteiros entre 50 e 150 e, a partir dela, criar uma tabela de 
// dados agrupados em classes, e algumas estatisticas básicas, como Média, 
// Moda, Mediana, Variância e Desvio-padrão.

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>

/* ESTRUTURAS AUXILIARES */
// Cria uma estrutura que armazena os dados de uma classe de dados agrupados
typedef struct {
    int F;
    int Fac;
    float xi;
} Classe;


/* FUNÇÕES AUXILIARES */
// Retorna o menor valor de uma lista de números inteiros
int menor_valor(int *lista, int tamanho) {
    int menor = lista[0];
    for (int i = 1; i < tamanho; i++) {
        if (lista[i] < menor) {
            menor = lista[i];
        }
    }
    return menor;
}

// Retorna o maior valor de uma lista de números inteiros
int maior_valor(int *lista, int tamanho) {
    int maior = lista[0];
    for (int i = 1; i < tamanho; i++) {
        if (lista[i] > maior) {
            maior = lista[i];
        }
    }
    return maior;
}

// Determina a frequência absoluta de uma classe
int freq_absoluta(int *lista, int tamanho, int inf, int sup) {
    int total = 0;
    for (int i = 0; i < tamanho; i++) {
        if (lista[i] >= inf && lista[i] < sup) {
            total++;
        }
    }   
    return total; 
}

// ***** INÍCIO DO PROGRAMA *****

int main(int argc, char const *argv[])
{    
    /* BIBLIOTECA PARA GERAR NÚMEROS PSEUDO-ALEATÓRIOS */
    srand(time(NULL));

    /* DECLARAÇÃO DE VARIÁVEIS */        
    int n;              // Valor informado pelo usuário da quantidade de valores da tabela de dados
    int *tabela;        // Tabela de valores inteiros gerada aleatoriamente, em função de 'n'
    int k;              // Informa o número de classes após dados serem agrupados
    int maior, menor;   // O maior e o menor, respectivamente, valores da tabela
    int at, ac;         // A amplitude total e a amplitude de classe, respectivamente
    Classe *c;          // Cria uma estrutura do tipo Classe
    int Linf, Lsup;     // Limites inferior e superior da classe   
    float num;          // Um valor real para auxiliar no cálculo da amplitude de classe (ac)         

    printf("\n Quantos dados tem sua tabela ? \n > ");
    scanf("%d", &n);

    // Gerando os dados da tabela
    tabela = (int*)calloc(n,sizeof(int));
    if (tabela==NULL) {
        printf("\n Erro de alocação de memória !\n");
    }
    
    for (int i = 0; i < n; i++) {
        tabela[i] = 30 + (rand()%110);
    }

    // Imprimindo os dados gerados
    printf("\n Dados obtidos:\n\n");
    for (int i = 0; i < n; i++) {
        printf(" %3d", tabela[i]);
        if ((i+1)%30 == 0) {
            printf("\n");
        }        
    }    
    
    // Cálculo das variáveis auxiliares para construir o agrupamento de dados    
    k = roundf(sqrt(n));
    maior = maior_valor(tabela, n);
    menor = menor_valor(tabela, n);
    at = maior-menor;
    ac = ceil(at/(1.0*k));

    printf("\n\n");    
    printf("\n >> Preparacao para agrupamento de dados:");
    printf("\n");    
    printf("\n  > Total de dados (n)...............: %d", n);
    printf("\n  > Numero de classes (k)............: %d", k);
    printf("\n  > Menor valor da tabela de dados...: %d", menor);    
    printf("\n  > Maior valor da tabela de dados...: %d", maior);   
    printf("\n  > Amplitude total (at).............: %d", at);
    printf("\n  > Amplitude de classe (ac).........: %d", ac);
    printf("\n\n");  

    // Construção das classes    
    c = (Classe*)calloc(k, sizeof(Classe));
    if (c == NULL) {
        printf("\n\n Erro de alocação de memória !\n\n");                
    }

    Linf = menor;
    for (int i = 0; i < k; i++) {   
        Lsup = Linf+ac;     
        c[i].F = freq_absoluta(tabela, ac, Linf, Lsup);
        printf("\n Total de elemento na %da Classe: %d", i+1, c[i].F);
        Linf = Lsup;
    }
    

    Linf = menor;
    for (int i = 0; i < k; i++) {
        Lsup = Linf+ac;
        printf("\n %3d [-- %3d ", Linf, Lsup);
        Linf = Lsup;        
    }
        
    

        

    
    return 0;
}

