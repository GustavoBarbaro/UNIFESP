#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 1025

int soma_sub_area (int x1, int y1, int x2, int y2, int sat[MAX][MAX], int d) {

    
    if (x1 - 1 >= 0 && y1 - 1 >=0){
        return sat[x2][y2] - sat[x1-1][y2] - sat[x2][y1-1] + sat[x1-1][y1-1];
    }

    else if (x1 - 1 <= 0 && y1 - 1 >= 0){
        return sat[x2][y2] - sat[x2][y1 - 1];
    }

    else if (x1 - 1 <= 0 && y1 - 1 <= 0){
        return sat[x2][y2];
    }

    else if (y1 - 1 <= 0 && x1 - 1 >= 0){
        return sat[x2][y2] - sat[x1 - 1][y2];
    }
/*
    x1 = i - d;
    y1 = j - d;

    x2 = i + d;
    y2 = j + d;
*/

    //return sat[x2][y2] - sat[x1-1][y2] - sat[x2][y1-1] + sat[x1-1][y1-1];
//                       superior            esquerda     diagonal de cima
}


void build_mat_sat (int mat[MAX][MAX], int d){

    int i ,j, resp, aux, resp_x, resp_y;
    int sat[MAX][MAX] = {0};

    aux = 0;
    resp = 0;
    resp_x = 0;
    resp_y = 0;


    ////////    CONSTRUINDO A MAT SAT /////////

    for (i = 0; i < MAX; i++){
        for (j = 0; j < MAX; j++){
            if(i > 0 && j > 0){
                sat[i][j] = mat[i][j] + sat[i-1][j] + sat[i][j-1] - sat[i-1][j-1];
            }
            else if(i > 0 && j == 0){
                sat[i][j] = mat[i][j] + sat[i-1][j]; //somando linha (andando na linha)
            }
            else if(j > 0 && i == 0){
                sat[i][j] = mat[i][j] + sat[i][j-1]; //somando na coluna (descendo coluna)
            }
            else{
                sat[i][j] = mat[i][j]; //caso primeiro lugar
            }                    
        }
    }

    ////// matrix sat processada  yeeee  ////////
    

    // vamos procurar no mapa agora

    for (i = 0; i < MAX; i++){
        for (j = 0; j < MAX; j++){

            //BASE PRIMEIRO POSICAO
            if (i == 0 && j == 0){ 
                aux = sat[i + d][j + d];
            }

            // CASO SUPERIOR PLANO - REVISADO
            else if (i == 0 && j >= d && j <= MAX - 1 - d){  
                aux = soma_sub_area (i, j - d, i + d, j + d, sat, d);
            }

            //QUINA SUPERIOR DIREITA - REVISADO (eu podeira usar a funcao mas n quero)
            else if (i == 0 && j == MAX - 1 ){
                aux = sat[i + d][j] - sat[i + d][j - d - 1];
            }

            // LATERAL ESQUERDO - REVISADO
            else if (j == 0 && i >= d && i <= MAX - 1 - d){
                aux = soma_sub_area (i - d, j, i + d, j + d, sat, d);
            }

            // QUINA INFERIOR ESQUERDA - REVISADO (poderia usar a funcao mas n quero)
            else if (j == 0 && i == MAX - 1 ){ 
                aux = sat[i][j + d] - sat[i - d - 1][j + d];
            }

            // CASO LATERAL DIREITA - REVISADO
            else if (i >= d && i <= MAX - 1 - d && j == MAX - 1){ // OK FUNCIONANDO
                aux = soma_sub_area (i - d, j - d, i + d, j, sat, d);
            }

            // QUINA INFERIOR DIREITA - REVISADO
            else if (i == MAX - 1 && j == MAX - 1){ //quina final da matriz
                aux = soma_sub_area (i - d, j - d, i , j, sat, d);
            }

            // CASO INFERIOR PLANO - REVISADO
            else if (i == MAX - 1 && j >= d && j <= MAX - 1 - d){
                aux = soma_sub_area (i - d, j - d, i, j + d, sat, d);
            }

            else {

                if (i - d >= 0 && j - d >= 0 && i + d >= 0 && j + d >= 0){
                    if (i - d <= MAX - 1 && j - d <= MAX - 1 && i + d <= MAX - 1 && j + d <= MAX - 1){
                        aux = soma_sub_area (i - d, j - d, i + d, j + d, sat, d);        
                    }   
                }
            }

            //COMPARATIVO DO MAIOR
            if (aux > resp){ //ele vai comparando e quando achar o maior substitui no resp
                resp = aux;
                resp_x = i;
                resp_y = j;
            }
        }
    }

    printf("%d %d %d\n", resp_x, resp_y, resp);

}






int main(void) {
  
    int d, n, x, y, user;
    int i, j;
    int resp, aux;
    int resp_x, resp_y;

    resp = 0;
    aux = 0;
    resp_x = 0;
    resp_y = 0;

    int mat[MAX][MAX] = {0};


    // FAZENDO OS INPUTS
    
    scanf ("%d", &d);
    scanf ("%d", &n);

    for (i = 0; i < n; i++){
        scanf ("%d %d %d", &x, &y, &user);
        mat[x][y] = user;
    }

    // FIM DOS INPUTS 


    // FAZENDO A BUSCA E PRINTANDO OS RESULTADOS

    build_mat_sat (mat, d);

    // TERNINANDO A BUSCA
    

  return 0;
}