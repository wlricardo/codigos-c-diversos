
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

// Determina o limite inferior de uma classe
int lim_inferior(Classe *c, int menor, int classe, int ampl_classe) {
    int linf;

    linf = menor + ((classe-1)*ampl_classe);
    return linf;
}

// Determina o limite superior de uma classe
/*int lim_inferior(Classe *c, int menor, int classe, int ampl_classe) {
    int linf;

    linf = menor + ((classe-1)*ampl_classe);
    return linf;
}*/

// Calcula a media
float media(Classe *classe, int amp_classe, int tam_amostra) {
    float media=0.0;
    for (int i = 0; i < amp_classe; i++) {
        media += (classe[i].F * classe[i].xi);        
    }
    media /= (1.0*tam_amostra);
    return media;    
}

// Procura a Classe Modal
int classe_modal(Classe *classe, int num_classes) {
    int classe_modal = classe[0].F;
    for (int i = 1; i < num_classes; i++) {
        classe[i].F > classe_modal;
        classe_modal = classe[i].F;
    }
    return classe_modal;
}

// Calcula a moda
float moda(Classe *classe, int c_modal, int h, int k) {
    float moda=0.0;    
    int li;                 // Limite inferior da classe modal    
    int fx;                 // Freq. absoluta da classe anterior à classe modal
    int f;                  // Freq. absoluta da classe model
    int fy;                 // Freq. absoluta da classe posterior à classe modal

    if (c_modal == 1) {     // Significa que a classe modal é a 1a
        fx = 0;             // Como é a 1a classe, não haverá freq. absoluta anterior a ela
    } else {
        fx = classe[c_modal-1].F;
    }

    if (c_modal == k) {     // Significa que a classe modal é a última
        fy = 0;             // Como é a última classe, não haverá freq. absoluta posterior a ela
    } else {
        fy = classe[c_modal+1].F;
    }
    
    f = classe[c_modal].F;
    li = lim_inferior(classe, c_modal, h, k);
    
    moda = (1.0*(f - fx));     // Multiplico por 1.0 apenas para garantir que o valor seja real
    moda /= ((f-fx)+(f-fy));
    moda += li;

    return moda;

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
    int fac;            // Variável auxiliar para calcular a freq. acumulada das classes
    int c_modal;       // Classe normal
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

    // Exibição da tabela com os dados agrupados em classes
    Linf = menor;
    fac = 0;
    for (int i = 0; i < k; i++) {   
        Lsup = Linf+ac;             
        c[i].F = freq_absoluta(tabela, ac, Linf, Lsup);    // Calcula a freq. absoluta da classe
        c[i].Fac = fac + c[i].F;                           // Calcula a freq. acumulada da classe 
        c[i].xi = (Linf+Lsup)/2.0;                         // Calcula o ponto médio da classe
        if (Lsup == maior) {
            printf("\n %3d [--] %-3d ", Linf, Lsup);       // Exibe o intervalo de classe caso o maior seja igual ao Lsup da última classe
        } else {
            printf("\n %3d [--) %-3d ", Linf, Lsup);       // Exibe os intervalos de classes
        }
        printf("%6d", c[i].F);                             // Exibe a freq. absoluta da classe
        printf("%6d", c[i].Fac);                           // Exibe a freq. acumulada da classe
        printf("\t%6.2f", c[i].xi);                        // Exibe o ponto médio da classe        
        Linf = Lsup;        
        fac = c[i].Fac;
    }

    c_modal = classe_modal(c, k);
    printf("\n\n--------------------------------------------");
    printf("\n Media...: %-7.4f", media(c, k, n));              // Calcula e exibe a média dos dados amostrais
    printf("\n Moda....: %-7.2f", moda(c, c_modal, ac, k));

    
    printf("\n\n\n");
    return 0;
}