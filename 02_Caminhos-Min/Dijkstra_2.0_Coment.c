#include <stdio.h>
#include <stdlib.h>

#define maximo 20
#define infinito 99999999

float vertices[maximo][maximo];
char nomes[maximo][10];
int quant=0, caminhoMinimo[maximo];

typedef struct etiqueta {
    int vert;
    float acumulado;
    int precedente;
    int visitado;
} etiq;

etiq caminho[maximo];

void zeraMatriz(void);
void pedeVertices(void);
void pedeArestas(void);
void imprimeMatriz(void);
void buscaCaminho(void);
void dijkstra(int vertIni, int vertFim);


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
        case 3: buscaCaminho();
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


void buscaCaminho(void){

    int vert1, vert2, i, j;

    if (quant == 0 || quant == 1){
        printf("\n\nNão há vértices suficientes a serem buscados");
        return;
    }

    printf("\n\n\tInforme o vértice inicial da busca do caminho: \n");
    do { 
        for(int i=0; i<=maximo; i++)
            if (nomes[i][0] != '\0')
                printf("%dº:  %s",i + 1, nomes[i]);
        scanf("%d", &vert1);
        vert1--;
        if (vert1 > quant-1 || vert1 < 0)
            printf("\nÉ necessário informar um valor de vértice existente.\n\n");
    } while (vert1 > quant-1 || vert1 < 0);

    printf("\n\n\tInforme o vértice final da busca do caminho: ");
    do { 
        scanf("%d", &vert2);
        vert2--;
        if (vert2 > quant-1 || vert2 < 0 || vert2 == vert1)
            printf("\nÉ necessário informar um valor de vértice existente e diferente do primeiro informado.\nTente outro valor:\n\n");
    } while (vert2 > quant-1 || vert2 < 0 || vert2 == vert1);

    dijkstra(vert1, vert2);

}


void dijkstra(int vert1, int vert2){

    int i, vertAtual, fim, menor, menorVert;

    for (i=0; i<quant; i++){                            //Todos os vértices com acumulado infinito, ou valor(caso adjacente de A), sem antecedentes e não visitados
        caminho[i].vert = i;
        caminho[i].precedente = -1;
        caminho[i].visitado = 0;
    }

    caminho[vert1].acumulado = 0;                        //vértice de origem marcado como visitado e com acumulado 0
    caminho[vert1].visitado = 1;

    for (i=0; i<quant; i++){                            //Inicialização
        if (vertices[vert1][i] != -1){
            caminho[i].acumulado = vertices[vert1][i];
            caminho[i].precedente = vert1;
        }
        else if (vert1 != i) {
            caminho[i].acumulado = infinito;
        }
    }

    vertAtual = vert1;
    fim = 1;                            //Variavél que fará o controle dos vértices visitados

    while (fim != 0){
        menor = infinito;
        for (i=0; i<quant; i++){        //Acha o menor valor
            if (caminho[i].visitado == 0){
                if (menor > caminho[i].acumulado){
                    menor = caminho[i].acumulado;
                    menorVert = i;
                }
            }
        }
        if (menor == infinito){
            fim = 0;
        }
        else {
            caminho[menorVert].visitado = 1;
            vertAtual = menorVert;
            for (i=0; i<quant; i++){
                if (vertices[vertAtual][i] != -1 && caminho[i].visitado == 0){
                    if (caminho[i].acumulado > (caminho[vertAtual].acumulado + vertices[vertAtual][i])){
                    caminho[i].acumulado = caminho[vertAtual].acumulado + vertices[vertAtual][i];
                    caminho[i].precedente = vertAtual;
                    }
                }
            }
            fim = 0;
            for (i=0; i<quant; i++)
                if (caminho[i].visitado == 0)
                    fim++;
        }
        
    }
    
    int cont=0;
    caminhoMinimo[cont] = vert2;
    for (i=vert2; i!=vert1;){                   //Imprime os valores
        if (caminho[i].precedente == -1){
            printf("\n\nNão há caminhos entre esses dois vértices.");
            return;
        }
        cont++;
        caminhoMinimo[cont] = caminho[i].precedente;
        i = caminho[i].precedente;
    }

    printf("\n\nMenor caminho encontado com a distância de %.2f pelo seguinte caminho:\n\n", caminho[vert2].acumulado);
    for (cont; cont >= 0; cont--){    
        for(int j=0; nomes[caminhoMinimo[cont]][j] != '\n' && nomes [caminhoMinimo[cont]][j] != '\0'; j++){
            putchar(nomes[caminhoMinimo[cont]][j]);
        }
        if (cont > 0)
            printf("  -->  ");
    }
}