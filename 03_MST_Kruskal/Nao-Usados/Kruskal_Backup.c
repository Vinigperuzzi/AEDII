#include <stdio.h>
#include <stdlib.h>

#define maximo 20
#define infinito 99999999

float vertices[maximo][maximo];
char nomes[maximo][10];
int quant=0;

void zeraMatriz(void);
void pedeVertices(void);
void pedeArestas(void);
void imprimeMatriz(void);
void Kruskal(void);


int main(void){

    int op;

    system ("cls || clear");
    
    zeraMatriz();

    for(;;){
        do {
            imprimeMatriz();
            printf("\tInforme a operação que deseja fazer: \n\t[1] Inserir vértices\n\t[2] Inserir arestas\n\t[3] Buscar um caminho mínimo entre vértices\n\t[4] Sair do programa\n");
            scanf("%d", &op);
            if (op < 1 || op > 4)
                printf("\n\tVocê precisa informar um valor válido para seleção!\n\n");
        } while (op < 1 || op > 4);

        switch (op)
        {
        case 1: pedeVertices();
            break;
        case 2: pedeArestas();
            break;
        case 3: ;
            break;
        case 4: exit(0);
        default: printf("\n\nAconteceu algum erro!\n Tente novamente.\n\n");
            break;
        }
    }

    return 0;
}


void zeraMatriz(void){

    for(int i=0; i<maximo; i++)
        for(int j=0; j<maximo; j++)
            vertices[i][j] = -1;
}

void pedeVertices(void){

    if (quant < maximo){
        printf("\n\nMatriz atual:\n\n");
        imprimeMatriz();
        printf("\n\nPor favor, informe o nome do vértice com até 10 letras: ");
        getchar();
        fgets(nomes[quant], 10, stdin);
        quant++;
    } 
    else
        printf("\nMáximo de vértices atingidos!\n");
    return;
}


void pedeArestas(void){

    if (quant == 0 || quant == 1){
        printf("\n\nNão há vértices suficientes para receber arestas");
        return;
    }

    int vert1 = 0, vert2 = 0;
    printf("\n\nMatriz atual:\n\n");
    imprimeMatriz();
    
    printf("\nInforme os vértices aos quais deseja conectar uma aresta, um de cada vez: \n");
    do { 
        for(int i=0; i<=maximo; i++)
            if (nomes[i][0] != '\0')
                printf("%dº:  %s",i + 1, nomes[i]);
        scanf("%d", &vert1);
        vert1--;
        if (vert1 > quant-1 || vert1 < 0)
            printf("\nÉ necessário informar um valor de vértice existente.\n\n");
    } while (vert1 > quant-1 || vert1 < 0);

    do { 
        scanf("%d", &vert2);
        vert2--;
        if (vert2 > quant-1 || vert2 < 0)
            printf("\nÉ necessário informar um valor de vértice existente.\n\n");
        if (vert1 == vert2){
            printf("\n\nPara fins de busca de caminhos mínimos, não se considera loops");
            return;
        }
    } while (vert2 > quant-1 || vert2 < 0 || vert1 == vert2);

    
    if (vert1 == maximo || vert2 == maximo)
        return;

    printf("Por favor, informe o valor da aresta entre os vértices: ");
        
    for(int j=0; nomes[vert1][j] != '\n' && nomes [vert1][j] != '\0'; j++){
        putchar(nomes[vert1][j]);
    }
    printf(" e ");
    for(int j=0; nomes[vert2][j] != '\n' && nomes [vert2][j] != '\0'; j++){
        putchar(nomes[vert2][j]);
    }
    printf(": ");  //De 74 a 81 só formata a saída no terminal, sem enter onde não deve e com espaços que fazem sentido.


    setbuf(stdin, NULL);
    scanf("%f", &vertices[vert1][vert2]);
    vertices[vert2][vert1] = vertices[vert1][vert2];
}


void imprimeMatriz(void){

    int i, j, qtd=0;
    printf("\n\n");
    for(i=0; i<=maximo; i++){
        printf("\t");
        if (nomes[i][0] != '\0'){
            for(int j=0; nomes[i][j] != '\n' && nomes [i][j] != '\0'; j++){
                putchar(nomes[i][j]);
            }
            qtd++;
        }
    }
    for (i=0; i < qtd; i++){
        printf("\n");
        for(j=0; nomes[i][j] != '\n' && nomes [i][j] != '\0'; j++){
                putchar(nomes[i][j]);
        }
        for(j=0; j<qtd; j++){
            if(vertices[i][j] != -1)
                printf("\t%.2f", vertices[i][j]);
            else   
                printf("\t-");
        }
    }
    printf("\n\n");
}


/*Ideia geral
Cada vértice é uma árvore independente
A cada iteração, procurar a menor aresta que ligue duas árvores diferentes. (Talvez ordenar as arestas)
Os vértices das árvores selecionadas passam a fazer parte de uma mesma árvore.
Repete o processo
Quando todos os vértices fazem parte de uma mesma árvore, encerra.
*/

void Kruskal(void) {


    
}