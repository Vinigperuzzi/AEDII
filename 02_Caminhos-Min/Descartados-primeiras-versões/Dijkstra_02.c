#include <stdio.h>
#include <stdlib.h>

float vertices[20][20];
char nomes[20][10];
int quant=0, caminhoMinimo[20];

typedef struct etiqueta {
    int vert;
    float acumulado;
    int precedente;
    int visitado;
} etiq;

etiq caminho[20];

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

    for(int i=0; i<20; i++)
        for(int j=0; j<20; j++)
            vertices[i][j] = -1;
}

void pedeVertices(void){

    if (quant < 20){
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
        for(int i=0; i<=20; i++)
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

    
    if (vert1 == 20 || vert2 == 20)
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
    for(i=0; i<=20; i++){
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

    int vert1, vert2, i, j, cand=0;
    float custo[20][20];
    etiq final;

    if (quant == 0 || quant == 1){
        printf("\n\nNão há vértices suficientes a serem buscados");
        return;
    }

    printf("\n\n\tInforme o vértice inicial da busca do caminho: \n");
    do { 
        for(int i=0; i<=20; i++)
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
            printf("\nÉ necessário informar um valor de vértice existente e diferente do primeiro informado.\n\n");
    } while (vert2 > quant-1 || vert2 < 0 || vert2 == vert1);

    dijkstra(vert1, vert2);

}


void dijkstra(int vert1, int vert2){

    int vertAtual=vert1, i, j, menorVert, fim, cont;
    float menor=99999;

    caminho[vert1].visitado = 1;            //1.
    caminho[vert1].acumulado = 0;
    caminho[vert1].precedente = -1;
    caminho[vert1].vert = vert1;

    for(i=0; i<quant; i++){                    //2.
        if (i != vert1){
            caminho[i].visitado = 0;
            caminho[i].acumulado = 99999;
            caminho[i].precedente = -1;
            caminho[i].vert = i;
        }
    }

    for (i=vert1; i!=vert2;){                  //3.
        cont = 0;         
        for (j=0; j<quant; j++){
            if (caminho[j].visitado == 0 &&  vertices[vertAtual][j] != -1){
                if (caminho[j].acumulado > (caminho[vertAtual].acumulado + vertices[vertAtual][j])){
                    caminho[j].acumulado = caminho[vertAtual].acumulado + vertices[vertAtual][j];
                    caminho[j].precedente = vertAtual;
                    cont++;
                }
            }
        }
        if (cont == 0){
            caminho[vertAtual].visitado = 1;
        }
        
        menor=99999;
        for (j=0; j<quant; j++){               //4.
            if (caminho[j].acumulado < menor && caminho[j].visitado == 0){
                menor = caminho[j].acumulado;
                menorVert = j;
            }
        }
        
        vertAtual = menorVert;
        caminho[menorVert].visitado = 1;
        
        fim = 0;
        for (j=0; j<quant; j++)
            if (caminho[j].visitado == 0)
                fim++;
        
        if (fim == 0){
            i = vert2;
        }
    }

    for (i=vert2; i!=vert1;){
        if (caminho[i].precedente == -1){
            printf("\n\nNão há caminhos entre esses dois vértices.");
            return;
        }
        i = caminho[i].precedente;
    }

    cont = 0;
    caminhoMinimo[cont] = vert2;
    for (i=vert2; i!=vert1;){
        cont++;
        caminhoMinimo[cont] = caminho[i].precedente;
        i = caminho[i].precedente;
    }

    printf("\n\nMenor caminho encontado com a distância de %.2f pelo seguinte caminho:\n\n", caminho[vert2].acumulado);
    for (cont; cont >= 0; cont--){    
        for(j=0; nomes[caminhoMinimo[cont]][j] != '\n' && nomes [caminhoMinimo[cont]][j] != '\0'; j++){
            putchar(nomes[caminhoMinimo[cont]][j]);
        }
        if (cont > 0)
            printf("  -->  ");
    }
}