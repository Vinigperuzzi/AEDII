#include <stdio.h>
#include <stdlib.h>

float vertices[20][20];
char nomes[20][10];

void zeraMatriz(void);
void pedeVertices(void);
void pedeArestas(void);
void imprimeMatriz(void);


int main(void){

    system ("cls || clear");

    zeraMatriz();
    pedeVertices();
    pedeArestas();
    imprimeMatriz();

    return 0;
}


void zeraMatriz(void){

    for(int i=0; i<20; i++)
        for(int j=0; j<20; j++)
            vertices[i][j] = 0;
}

void pedeVertices(void){

    int quant=0;
    char teste='S';

    printf("\n\nVamos criar uma matriz de um grafo de até 20 vértices.\n");
    while (quant < 20 && (teste == 'S' || teste == 's')){
        printf("\n\nMatriz atual:\n\n");
        imprimeMatriz();
        printf("\n\n\t\tDeseja informar um Vértice?(S/N): ");
        do{ 
            setbuf(stdin,NULL);
            teste = getchar();
        } while (teste != 'S' && teste != 's' && teste != 'N' && teste != 'n');
        if (teste == 'S' || teste == 's'){
            printf("\nPor favor, informe o nome do vértice com até 10 letras: ");
            getchar();
            fgets(nomes[quant], 10, stdin);
            quant++;
        }
    }
}


void pedeArestas(void){

    int i=0, vert;
    while (nomes[i][0] != '\0'){
        vert = 0;
        while (vert >= 0 && vert < 20){
            printf("\n\nMatriz atual:\n\n");
            imprimeMatriz();
            printf("\nPara o %dº Vértice: %s A quais vértices ele se conecta:(21 indica que não se conecta a mais nenhum.)\n\n", i+1, nomes[i]);
            for(int i=0; i<=20; i++)
                if (nomes[i][0] != '\0')
                    printf("%dº:  %s",i + 1, nomes[i]);
            scanf("%d", &vert);
            vert--;
            
            if (vert >= 0 && vert < 20){
                printf("Por favor, informe o valor da aresta entre os vértices: ");
                
                
                for(int j=0; nomes[i][j] != '\n' && nomes [i][j] != '\0'; j++){
                    putchar(nomes[i][j]);
                }
                printf(" e ");
                for(int j=0; nomes[vert][j] != '\n' && nomes [vert][j] != '\0'; j++){
                    putchar(nomes[vert][j]);
                }
                printf(": ");  //De 74 a 81 só formata a saída no terminal, sem enter onde não deve e com espaços que fazem sentido.


                setbuf(stdin, NULL);
                scanf("%f", &vertices[i][vert]);
                vertices[vert][i] = vertices[i][vert];
            }
        }
        i++;
    }
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
            if(vertices[i][j] != 0)
                printf("\t%.2f", vertices[i][j]);
            else   
                printf("\t-");
        }
    }
    printf("\n\n");
}