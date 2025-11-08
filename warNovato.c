/* Cadastrar 5 territorios com nome, cor do exército
 e quantidade de tropas. Depois listar os territorios cadastrados.  
 Usando struct para representar o territorio.
*/

#include <stdio.h>
#include <string.h>

//Constante global
#define QUANTIDADE_TERRITORIOS 5

//Definição da struct território
typedef struct {
    char nome[30];
    char corExercito[10];
    int quantidadeTropas;
}Territorio;

//Função para limpar o buffer de entrada
void limparBufferEntrada() {
    int c;
    while((c=getchar()) != '\n'  && c != EOF);
}

//Função principal
int main() {
    Territorio Territorios[QUANTIDADE_TERRITORIOS]; //Array da struct território 

    printf("===============================================\n");
    printf("Desafio cadastro/exibição de territórios\n");
    printf("===============================================\n");
    printf("\n");

    //Uso do for para cadastro dos territórios dentro do array "territorios"
    for(int i = 0; i < QUANTIDADE_TERRITORIOS; i++) {
        printf("*** Cadastro do Territorio %d ***\n", i + 1);

        printf("Digite o nome do territorio: ");
        scanf("%s", Territorios[i].nome);
        limparBufferEntrada(); // Limpar o '\n' deixado pelo scanf
    
        printf("Digite a cor do exercito: ");
        scanf("%s", Territorios[i].corExercito);
        limparBufferEntrada(); 

        printf("Digite a quantidade de tropas: ");
        scanf("%d", &Territorios[i].quantidadeTropas);
        limparBufferEntrada(); 
        printf("\n");
    }
    

    printf("===============================================\n");
    printf("*** Exibindo territorios cadastrados ***\n");
    printf("===============================================\n");
    printf("\n");

    //Uso do for para exibição dos territórios cadastrados no array "territorios"
    for(int i = 0; i < QUANTIDADE_TERRITORIOS; i++) {
        printf("*** Territorio %d ***\n", i + 1);
        printf("Nome: %s\n", Territorios[i].nome);
        printf("Cor do exercito: %s\n", Territorios[i].corExercito);
        printf("Quantidade de tropas: %d\n", Territorios[i].quantidadeTropas);
        printf("\n");
    }

    return 0;
}