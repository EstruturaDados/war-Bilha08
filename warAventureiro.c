#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

//Definição da struct território
typedef struct {
    char nome[30];
    char corExercito[10];
    int quantidadeTropas;
}Territorio;


//funções limpador buffer de entrada
void limparBufferEntrada() {
    int c;
    while((c=getchar()) != '\n'  && c != EOF);
}

//função liberar memória
void liberarMemoria(Territorio *territorios) {
    free(territorios);

    printf("Memoria liberada, saindo...!\n");
}

//  Função registrar territorios
void registrarTerritorios(Territorio *territorios, int totalTerritorios) {
    for (int i = 0; i < totalTerritorios; i++) {
        printf("*** Cadastro do Territorio %d ***\n", i + 1);

        printf("Digite o nome do territorio: ");
        scanf("%s", territorios[i].nome);
        limparBufferEntrada(); // Limpar o '\n' deixado pelo scanf
    
        printf("Digite a cor do exercito: ");
        scanf("%s", territorios[i].corExercito);
        limparBufferEntrada(); 

        printf("Digite a quantidade de tropas: ");
        scanf("%d", &territorios[i].quantidadeTropas);
        limparBufferEntrada(); 

        printf("\n");
    }
}

//Função exibir territorios
void exibirTerritorios(Territorio *territorios, int totalTerritorios) {
    printf("===============================================\n");
    printf("*** Lista de Territorios Cadastrados ***\n");
    printf("===============================================\n\n");
    for (int i = 0; i < totalTerritorios; i++) {
        printf("Territorio %d:\n", i + 1);
        printf("Nome: %s\n", territorios[i].nome);
        printf("Cor do Exército: %s\n", territorios[i].corExercito);
        printf("Quantidade de Tropas: %d\n\n", territorios[i].quantidadeTropas);
    }
    printf("--------------------------------------\n");

}

//função atacar territorio
void atacarTerritorio(Territorio *atacante, Territorio *defensor) {
    if (atacante->quantidadeTropas < 1) {
        printf("O territorio %s nao possui tropas suficientes para atacar.\n", atacante->nome);
        return;
    } else if (strcmp(atacante->corExercito, defensor->corExercito) == 0) { // strcmp compara strings, se for igual retorna 0
        printf("O territorio %s nao pode atacar o territorio %s, pois ambos pertencem ao mesmo jogador.\n", atacante->nome, defensor->nome); 
        return;
    }

    int dadoAtaq, dadoDef, tropasTransferida = 0;
    dadoAtaq = rand() % 6 + 1; // Dado de 6 faces para o atacante
    dadoDef = rand() % 6 + 1;  // Dado de 6 faces para o defensor

    // Exibir resultados dos dados
    printf("\n-- RESULTADO DA BATALHA --\n");
    printf("%s esta atacando %s!\n", atacante->nome, defensor->nome);
    printf("O atacante %s rolou um dado e tirou: %d \n", atacante->nome, dadoAtaq);
    printf("O defensor %s rolou um dado e tirou: %d \n", defensor->nome, dadoDef);

    // Determinar o vencedor
    if (dadoAtaq == dadoDef) {
        printf("Empate! Nenhum território foi conquistado.\n");
    } else if (dadoAtaq > dadoDef) {
        printf("O atacante %s venceu e conquistou o território %s!\n", atacante->nome, defensor->nome);
        strcpy(defensor->corExercito, atacante->corExercito) ; // Utilizando strcpy para copiar a cor do exército do atacante para o defensor.
        tropasTransferida = atacante->quantidadeTropas / 2 ; // Quantidade de tropas do atacante que será movida. 
        defensor->quantidadeTropas = tropasTransferida ; // Transferindo as tropas para o território conquistado.
        atacante->quantidadeTropas -= tropasTransferida  ; // Atualiza a quantidade de tropas do atacante.
    } else {
        printf("O defensor %s venceu e manteve o território!\n", defensor->nome);
        atacante->quantidadeTropas -= 1; // O atacante perde uma tropa em caso de derrota.
    }

    printf("\nPressione Enter para continuar para o próximo turno... ");
    getchar();
    printf("\n");

}



int main () {
    int TotalTerritorios = 0; // iniciando territorio em 0 pois sera pedido ao usuario
    Territorio *Territorios;
    srand(time(NULL));


    printf("===============================================\n");
    printf("*** Desafio War estruturado ***\n");
    printf("===============================================\n");
    printf("\nInforme a quantidade de territorios a serem cadastrados: ");
    scanf("%d", &TotalTerritorios);
    limparBufferEntrada(); 
    printf("\n");

    // Alocação dinâmica de memória para o array de territórios (numero de elementos * tamanho).
    Territorios = (Territorio *) malloc(TotalTerritorios * sizeof(Territorio));

    // Verificar se a alocação foi bem-sucedida.
    if (Territorios == NULL) {
        printf("Erro na alocacao de memoria!\n");
        return 1; // Retorna 1 para indicar um erro
    }

    //Registrando os territorios
    registrarTerritorios(Territorios, TotalTerritorios);
    
    //Exibindo os territorios cadastrados
    exibirTerritorios(Territorios, TotalTerritorios);

    //Fase de ataque, pedindo o territorio atacante e defensor
    int atacante, defensor;
    do {
        printf("-- FASE DE ATAQUE --\n");
        printf("Digite o numero do territorio atacante (1 a %d ou 0 para sair): ", TotalTerritorios);
        scanf("%d", &atacante);
        limparBufferEntrada(); 

        if (atacante == 0) {
            break; // Sair do loop se o atacante for 0
        }

        printf("Digite o numero do territorio defensor (1 a %d): ", TotalTerritorios);
        scanf("%d", &defensor);
        limparBufferEntrada(); 

        // Validar entradas
        if ( atacante < 0 || atacante > TotalTerritorios || defensor < 1 || defensor > TotalTerritorios) {
            printf("Numero de territorio invalido. Tente novamente.\n");
            continue;
        }

        // Atacando
        atacarTerritorio(&Territorios[atacante - 1], &Territorios[defensor - 1]);

        // Exibir os territórios atualizados após o ataque
        exibirTerritorios(Territorios, TotalTerritorios);

    } while (atacante != 0);


    // Liberar a memória alocada para os territórios
    liberarMemoria(Territorios); 


    return 0;
}