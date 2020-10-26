#include <stdio.h>
#include <stdlib.h>
#define MAX 15
#define MAX2 100

typedef struct vet_of_vets{

    int vet[MAX];
    int n_elementos;

}vet_of_vets;


void dobra (int vet [MAX], int p_corte, int tam, vet_of_vets vet_candidatos[MAX]){


    int aux_1[MAX] = {0};
    int aux_2[MAX] = {0};
    int aux_2_invertido[MAX] = {0};

    int resp[MAX] = {0};


    int i, j, count, count_2, tam_dobra, minus;

    count = 0;
    count_2 = 0;
    j = 0;
    tam_dobra = 0;
    

    //primeiro dividir o vet principal em duas partes

    //primeira parte
    for (i = 0; i <= p_corte; i++){
        aux_1[i] = vet[i];
    }

    //segunda parte
    for (i = p_corte + 1; i < tam; i++){
        aux_2[j] = vet[i];
        j++;
        count = j;
    }
    
    //agora, pegar o segundo vetor e inverter ele

    for (i = 0; i < count; i++){
        aux_2_invertido[i] = aux_2[j - 1];
        j--;
    }

    j = count;
    count_2 = p_corte;
    
    

    //preciso achar o tam do vetor de dobra

    if (p_corte >= count){
        tam_dobra = p_corte + 1;
    }

    else if (count > p_corte){
        tam_dobra = count;
    }

    else if (p_corte + 1 == count){
        tam_dobra = count;
    }

    

    //percorrer o normal e o invert de tras pra frente preenchendo a resp

    for (i = 0; i < tam; i++){

        if(j >= 0 && count_2 >= 0){
            resp[i] = aux_2_invertido[j - 1] + aux_1[count_2];
            j--;
            count_2--;
        }
        else if (j < 0 && count_2 >= 0){
            resp[i] = aux_1[count_2];
            count_2--;
        }
        else if (j >= 0 && count_2 < 0){
            resp[i] = aux_2_invertido[j - 1];
            j--;
        }

    }

    //agora precisamos inverter o vetor resp
    //p_corte tbm eh o numero do conjunto candidato

    minus = tam_dobra;

    if (tam - 1 == p_corte){
        for (i = 0; i < tam_dobra; i++){
            vet_candidatos[p_corte].vet[i] = resp[i];
        }
    }

    else{
        for (i = 0; i < tam_dobra; i++){
            vet_candidatos[p_corte].vet[i] = resp[minus - 1];
            minus--;
        }
    }

    //salvando o tamanho daquele respectivo candidato

    vet_candidatos[p_corte].n_elementos = tam_dobra;
    


    /*
    //printando
    for (i = 0; i <= p_corte; i++){
        printf ("aux_1[%d]: %d\n", i, aux_1[i]);
    }

    printf ("\n");

    for (i = 0; i < count; i++){
        printf ("aux_2[%d]: %d\n", i, aux_2[i]);
    }
    
    for (i = 0; i < count; i++){
        printf ("aux_2_invertido[%d]: %d\n", i, aux_2_invertido[i]);
    }
    

    for (i = 0; i < tam_dobra; i++){
        printf ("resp[%d]: %d\n", i, resp[i]);
    }

    for (i = 0; i < tam_dobra; i++){
        printf ("FINAL [%d]: %d\n", i, vet_candidatos[p_corte].vet[i]);
    }

    printf ("DE DENTRO DA STRUCT %d", vet_candidatos[p_corte].n_elementos);
    */


}




void build_candidatos (int k, int vet_N[MAX], int n, vet_of_vets vet_candidatos[MAX], int * n_candidatos, vet_of_vets resp_vet[MAX]){

    int i;

    if (k == 1){ // primeira iteracao, nao tem como eu saber de muita coisa, entao usar o vet_N pra gerar os primeiros

        *n_candidatos = n;

        for (i = 0; i < n; i++){
            dobra (vet_N, i, n, vet_candidatos); // 1 vetor q vai dobrar, 2 onde vai dobrar, 3 tam do vetor de dobra, 4 preencha aqui
        }

    }

    else {

        *n_candidatos = resp_vet[k - 1].n_elementos;

        for (i = 0; i < *n_candidatos; i++){
            dobra (resp_vet[k-1].vet, i, resp_vet[k-1].n_elementos, vet_candidatos);
        }

    }

}





int eh_igual (vet_of_vets resp_vet[MAX], int k, int vet_M[MAX], int m){ //mandei o m pra nao ter que verificar o vetor inteiro

    int i, aux, teste, teste_inv;

    teste = 0;
    teste_inv = 0;
    
    aux = m - 1;

    for (i = 0; i < m; i++){
        if (resp_vet[k].vet[i] != vet_M[i]){
            teste = 1; //quer dizer que eles nao são iguais
        }
    }

    //preciso comparar o inverso tbm se eh IGUAL
    
    for (i = 0; i < m; i++){ // talvez seja uma boa testar isso a parte dps 
        if (resp_vet[k].vet[aux] != vet_M[i]){
            teste_inv = 1;
        }
        aux--;
    }
    

    if (teste == 1 && teste_inv == 1){
        return 0; //nao fez nenhma atribuicao, entao eh igual
    }
    else {
        return 1;
    }


    //se forem iguais ele vai iterar ate aqui
    //EH IGUAL
    //return 1; 

}



void make_move (vet_of_vets resp_vet[MAX], int i, int k, vet_of_vets vet_candidatos[MAX]){

    int j;

    for (j = 0; j < vet_candidatos[i].n_elementos; j++){
        resp_vet[k].vet[j] = vet_candidatos[i].vet[j];
    }

    resp_vet[k].n_elementos = vet_candidatos[i].n_elementos;

}



//resp_vet eh o vetor de soluçcoes
void backtrack (vet_of_vets resp_vet[MAX], int k, int vet_N[MAX], int n, int vet_M[MAX], int m){

    vet_of_vets vet_candidatos[MAX];    //desconfio que nao precisa ser ate MAX mas dps diminuo se precisar

    int n_candidatos;
    int i, j;
    int testando;

    testando = 0;



    
    if (eh_igual(resp_vet, k, vet_M, m) == 1 || resp_vet[k].n_elementos == 1){ //se resp == vet_M quer dizer que achamos a solucao

        if (eh_igual(resp_vet, k, vet_M, m) == 1){
            printf ("S");
            //faz alguma merda pra matar o programa pra nao perder tempo calculando coisa inutil
            exit(0);
        }

    }

    else {
        k = k + 1;
        build_candidatos (k, vet_N, n, vet_candidatos, &n_candidatos, resp_vet); // ate onde sei nao vai precisar de imput, mas ta ai neh

        /*if (k == 4){
            for (i = 0; i < n_candidatos; i++){
                for(j = 0; j < vet_candidatos[i].n_elementos; j++){
                    printf ("vet_candidatos[%d].vet[%d] = %d\n", i, j, vet_candidatos[i].vet[j]);
                }
                printf ("\n");
                
            }
        }
        */

        for (i = 0; i < n_candidatos - 1; i++){ //ir ate o ultimo eh inutil vai ver tudo denovo e assim eu elimino um seg fault

            make_move (resp_vet, i, k, vet_candidatos); //resp_vet[k] = vet_candidatos[i]; //transformar em funcao dps dar certo

            /*
            if (i == 0 && testando == 0){
                for (j = 0; j < vet_candidatos[i].n_elementos; j++){
                    printf("resp_vet[%d].vet[%d] = %d\n", k, j, resp_vet[k].vet[j]);
                }
                testando = 6;
            }
            */

            backtrack (resp_vet, k, vet_N, n, vet_M, m);

        }

    }
    
}







int main(void) {
  
    int i, n, m;
    int vet_N[MAX] = {0};
    int vet_M[MAX] = {0};

    vet_of_vets resp_vet[MAX]; //vetor de solucao



    ////////////        FAZENDO A ENTRADA DOS DADOS           ///////////////

    scanf ("%d", &n);
    
    for (i = 0; i < n; i++){
        scanf ("%d", &vet_N[i]);
    }

    scanf ("%d", &m);

    for (i = 0; i < m; i++){
        scanf ("%d", &vet_M[i]);
    }

    ////////////        FIM DA ENTRADA DOS DADOS           ///////////////


    for (i = 0; i < n; i++){
        resp_vet[0].vet[i] = vet_N[i];
    }




    // precisamos usar backtracking para resolver o problema


    backtrack (resp_vet, 0, vet_N, n, vet_M, m);


    //ele soh vai printar esse N se o backtrack nao achar nada, pq dentro do backtrack
    //eu coloquei um exit caso ele ache algum match
    printf ("N");





    //resp = analise(n, vet_N, m, vet_M);




    ////////////        PRINTANDO O RESULTADO           ///////////////
    /*
    if (resp == 1){
        printf ("S"); //caso tenha achado uma subsequencia
    }

    else if (resp == 0){
        printf ("N"); //caso NAO tenha achado
    }

    */
    
    
    /*   PRINTS DA ENTRADA PARA TESTE
    for (i = 0; i < n; i++){
        printf ("%d ", vet_N[i]);
    }

    printf ("\n");

    for (i = 0; i < m; i++){
        printf ("%d ", vet_M[i]);
    }*/


    return 0;
}