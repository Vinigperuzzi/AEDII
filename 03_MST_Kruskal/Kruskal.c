#include <stdio.h>
#include <stdlib.h>

#define maximo 20

typedef struct Aresta{
    int vertA, vertB;
    float peso;
} Aresta;

typedef struct ArestaLista{
    Aresta dados[((maximo*maximo)-maximo)/2];//Equação que retorna a quantidade máxima possível de arestas.
    int n;
} ArestaLista;

ArestaLista listaIni, listaFim;

float vertices[maximo][maximo];
char nomes[maximo][10];
int quant=0;

void zeraMatriz(void);
void pedeVertices(void);
void pedeArestas(void);
void imprimeMatriz(void);
void Kruskal(void);
void sort(void);
void imprimeMST(void);


int main(void){

    int op;

    system ("cls || clear");
    
    zeraMatriz();

    for(;;){
        do {
            imprimeMatriz();
            printf("\tInforme a operação que deseja fazer: \n\t[1] Inserir vértices\n\t[2] Inserir arestas\n\t[3] Buscar a árvore mínima geradora do grafo\n\t[4] Sair do programa\n");
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
        case 3: Kruskal();
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
    printf("\n\n\n\t\tMatriz atual:\n\n\n");
    if (quant == 0)
        printf("\t\t\tVazia\n\n\n");
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


void Kruskal(void) {
    int conjDisjunto[((maximo*maximo)-maximo)/2], i, j, vN1, vN2, testaConexo;
    listaIni.n = 0;

    if (quant <= 1){
        printf("\n\nSó é possível gerar uma árvore mínima com dois ou mais vértices!\n\n");
        return;
    }

    for(i=0; i<quant; i++){
        for(j=0; j<quant; j++){
            if (vertices[i][j] != -1){
                listaIni.dados[listaIni.n].vertA = i;
                listaIni.dados[listaIni.n].vertB = j;
                listaIni.dados[listaIni.n].peso = vertices[i][j];
                listaIni.n++;
            }
        }
    }
    
    sort();

    for (i=0; i<quant; i++)
        conjDisjunto[i] = i;
    
    listaFim.n = 0;

    for (i=0; i<listaIni.n; i++){
        vN1 = conjDisjunto[listaIni.dados[i].vertA];
        vN2 = conjDisjunto[listaIni.dados[i].vertB];

        if (vN1 != vN2) {
            listaFim.dados[listaFim.n] = listaIni.dados[i];
            listaFim.n++;
            for (j=0; j<quant; j++)
                if (conjDisjunto[j] == vN2)
                    conjDisjunto[j] = vN1;
        }
    }
    testaConexo = 0;
    for (i=0; i<quant-1; i++)
        if (conjDisjunto[i] != conjDisjunto[i+1])
            testaConexo++;
    if (testaConexo != 0){
        printf("\n\nO Grafo não é conexo! O grafo deve ser conexo para que se possa encontrar a árvore geradora mínima\n\n");
        return;
    }
    imprimeMST();
}

void sort() {
  int i, j;
  Aresta temp;

  for (i = 1; i < listaIni.n; i++)
    for (j = 0; j < listaIni.n - 1; j++)
      if (listaIni.dados[j].peso > listaIni.dados[j + 1].peso) {
        temp = listaIni.dados[j];
        listaIni.dados[j] = listaIni.dados[j + 1];
        listaIni.dados[j + 1] = temp;
      }
}


void imprimeMST(void){
    int i, j;
    float custo = 0;

    printf("\n\n\nA árvore geradora mínima desse grafo segue o seguinte caminho:\n\n");
    for (i=0; i<listaFim.n; i++){
        for(j=0; nomes[listaFim.dados[i].vertA][j] != '\n' && nomes [listaFim.dados[i].vertA][j] != '\0'; j++){
            putchar(nomes[listaFim.dados[i].vertA][j]);
        }
        printf(" <---> ");
        for(j=0; nomes[listaFim.dados[i].vertB][j] != '\n' && nomes [listaFim.dados[i].vertB][j] != '\0'; j++){
            putchar(nomes[listaFim.dados[i].vertB][j]);
        }
        printf(" : %.2f.\n", listaFim.dados[i].peso);
        custo = custo + listaFim.dados[i].peso;
    }

    printf("\nCusto total da árvore geradora mínima: %.2f", custo);
}