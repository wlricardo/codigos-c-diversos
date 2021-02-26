
// Gerar uma tabela de valores inteiros entre 50 e 150 e, a partir dela, criar uma tabela de 
// dados agrupados em classes, e algumas estatisticas básicas, como Média, 
// Moda, Mediana, Variância e Desvio-padrão.

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>

int main(int argc, char const *argv[])
{
    setlocale(LC_ALL, "Portuguese");
    srand(time(NULL));

    int n;          // Valor informado pelo usuário da quantidade de valores da tabela de dados
    int *tabela;    // Tabela de valores inteiros gerada aleatoriamente, em função de 'n'
    //int i;

    printf("\n Quantos dados tem sua tabela ? \n > ");
    scanf("%d", &n);

    // Gerando os dados da tabela
    tabela = (int*)calloc(n,sizeof(int));
    if (tabela==NULL) {
        printf("\n Erro de alocação de memória !\n");
    }
    
    for (int i = 0; i < n; i++) {
        tabela[i] = 50 + (rand()%100);
    }

    // Imprimindo os dados gerados
    for (int i = 0; i < n; i++) {
        printf(" %d", tabela[i]);
        if (i%10 == 0) {
            printf("\n");
        }        
    }    
    
    return 0;
}

