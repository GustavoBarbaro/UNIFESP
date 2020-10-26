#include <stdio.h>
#include <stdlib.h>
#define MAX 100000

//using kaneda algorithm
int maxSubArraySum(int a[MAX], int size){

    int max_so_far = 0, max_ending_here = 0; 
    int i;
  
    for (i = 0; i < size; i++) 
    { 
        max_ending_here = max_ending_here + a[i]; 
        if (max_so_far < max_ending_here) 
            max_so_far = max_ending_here; 
  
        if (max_ending_here < 0) 
            max_ending_here = 0; 
    } 
    return max_so_far; 
} 





int main(void) {

    int n, i, custo, resp,aux;
    int vet[MAX] = {0};

    ////////    FAZENDO OS INPUTS     //////////

    scanf ("%d", &n);
    scanf ("%d", &custo);

    for (i = 0; i < n; i++){
        scanf("%d", &aux);
        vet[i] = aux - custo;
    }

    /////////      FIM DOS INPUTS     ///////////


    resp = maxSubArraySum(vet, n);

    if (resp <= 0){
        printf ("%d",0);
    }
    else{
        printf ("%d", resp);    
    }

    



  return 0;
}