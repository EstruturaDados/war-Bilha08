/* ============================================================================
         PROJETO WAR ESTRUTURADO - DESAFIO DE CÓDIGO

OBJETIVOS:
- Modularizar completamente o código em funções especializadas.
- Implementar um sistema de missões para um jogador.
- Criar uma função para verificar se a missão foi cumprida.
- Utilizar passagem por referência (ponteiros) para modificar dados e
  passagem por valor/referência constante (const) para apenas ler.
- Foco em: Design de software, modularização, const correctness, lógica de jogo.
============================================================================ */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Constantes globais
#define MAX_TERRITORIOS 5
#define NUM_MISSOES 5
#define TAM_STRING 100

// Definição das structs
typedef struct {
    char nome[TAM_STRING];
    char corExercito[TAM_STRING];
    int quantidadeTropas;
    int conquistado; // 1 para conquistado, 0 para não conquistado
} Territorio;

typedef struct {
    char* missao;
    char corExercito[TAM_STRING];
} Jogador;

// Protótipos
void limparBufferEntrada();
void alocarterritorios(Territorio **territorios);
void alocarMissaoJogador(Jogador **jogadorInfo, const char* missao);
void liberarMemoria(Territorio *territorios, Jogador *jogadorInfo);
void registrarTerritorios(Territorio *territorios);
void exibirTerritorios(const Territorio *territorios);
void atribuirMissao(Jogador **jogadorInfo, const char* missoes[], Territorio *territorios, int *idMissao);
void exibirMissao(const Jogador *jogadorInfo);
void exibirMenuPrincipal();
void atacar(Territorio *atacante, Territorio *defensor, Jogador *jogadorInfo, const Territorio *territorios, int idMissao, int *vitoriasConsecutivas);
void faseDeAtaque(Jogador *jogadorInfo, Territorio *territorios, int idMissao, int *vitoriasConsecutivas);
int verificarMissao(const Jogador *jogadorInfo, const Territorio *territorios, int idMissao, int vitoriasConsecutivas);



int main() {
    srand(time(NULL)); // Inicializa o gerador de números aleatórios

    // Alocação de memória para os territórios
    Territorio *territorios;
    alocarterritorios(&territorios);

    // Lista de missões disponíveis
    char* missoes[NUM_MISSOES] = {
        "Conquistar 3 territórios",
        "Eliminar um território qualquer",
        "Perder todas as tropas",
        "Conquistar o segundo território",
        "Vencer três batalhas seguidas"
    };
    // Variáveis para controle do jogo
    int idMissao;
    int vitoriasConsecutivas = 0;

    // Registro e exibição dos territórios
    registrarTerritorios(territorios);
    exibirTerritorios(territorios);

    // Alocação e atribuição da missão
    Jogador *jogadorInfo = NULL;
    atribuirMissao(&jogadorInfo, (const char**)missoes, territorios, &idMissao);
    exibirMissao(jogadorInfo);

    // Fase de ataque
    faseDeAtaque(jogadorInfo, territorios, idMissao, &vitoriasConsecutivas);

    // Liberação de memória
    liberarMemoria(territorios, jogadorInfo);

    return 0;
}

// -------------------------------------------------------------
// Implementações
// -------------------------------------------------------------

// Função para limpar o buffer de entrada
void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
// Função para alocar memória para os territórios
void alocarterritorios(Territorio **territorios) {
    *territorios = calloc(MAX_TERRITORIOS, sizeof(Territorio));// Inicializa com zeros
    if (*territorios == NULL) {
        printf("Erro ao alocar memoria para territorios!\n");
        exit(1);
    }
}
// Função para alocar memória para a missão do jogador
void alocarMissaoJogador(Jogador **jogadorInfo, const char* missao) {
    *jogadorInfo = malloc(sizeof(Jogador)); // Aloca memória para o jogador
    if (*jogadorInfo == NULL) {
        printf("Erro ao alocar memoria para jogador!\n");
        exit(1);
    }

    (*jogadorInfo)->missao = malloc(strlen(missao) + 1);// Aloca memória para a missão
    if ((*jogadorInfo)->missao == NULL) {
        printf("Erro ao alocar memoria para a missão!\n");
        exit(1);
    }

    strcpy((*jogadorInfo)->missao, missao);
}
// Função para liberar a memória alocada
void liberarMemoria(Territorio *territorios, Jogador *jogadorInfo) {
    free(territorios);
    free(jogadorInfo->missao);
    free(jogadorInfo);
    printf("\nMemória liberada com sucesso!\n");
}
// Função para registrar os territórios
void registrarTerritorios(Territorio *territorios) {
    printf("\n=== Cadastro dos Territórios ===\n");
    for (int i = 0; i < MAX_TERRITORIOS; i++) {
        printf("\nDigite o nome do território %d: ", i + 1);
        fgets(territorios[i].nome, TAM_STRING, stdin);
        territorios[i].nome[strcspn(territorios[i].nome, "\n")] = '\0';// Remove o '\n' do final

        printf("Digite a cor do exército deste território: ");
        fgets(territorios[i].corExercito, TAM_STRING, stdin);
        territorios[i].corExercito[strcspn(territorios[i].corExercito, "\n")] = '\0';

        printf("Digite a quantidade de tropas: ");
        scanf("%d", &territorios[i].quantidadeTropas);
        limparBufferEntrada();

        territorios[i].conquistado = 0;
    }
}
// Função para exibir os territórios
void exibirTerritorios(const Territorio *territorios) {
    printf("\n===============================================\n");
    printf("*** Lista de Territórios Cadastrados ***\n");
    printf("===============================================\n");
    for (int i = 0; i < MAX_TERRITORIOS; i++) {
        printf("\nTerritório %d:\n", i + 1);
        printf("Nome: %s\n", territorios[i].nome);
        printf("Cor do Exército: %s\n", territorios[i].corExercito);
        printf("Quantidade de Tropas: %d\n", territorios[i].quantidadeTropas);
    }
    printf("===============================================\n\n");
}
// Função para atribuir uma missão ao jogador
void atribuirMissao(Jogador **jogadorInfo, const char* missoes[], Territorio *territorios, int *idMissao) {
    int escolhaCor;
    printf("\n--- Escolha a cor do seu exército entre as opções abaixo ---\n");
    for (int i = 0; i < MAX_TERRITORIOS; i++) {
        printf("%d. Exército %s\n", i + 1, territorios[i].corExercito);
    }

    printf("Escolha o número da cor de suas tropas: ");
    scanf("%d", &escolhaCor);
    limparBufferEntrada();

    *idMissao = rand() % NUM_MISSOES;// Seleciona uma missão aleatória
    alocarMissaoJogador(jogadorInfo, missoes[*idMissao]);// Aloca e atribui a missão ao jogador

    strcpy((*jogadorInfo)->corExercito, territorios[escolhaCor - 1].corExercito);// Atribui a cor do exército escolhida
}
// Função para exibir a missão do jogador
void exibirMissao(const Jogador *jogadorInfo) {
    printf("\n--- Sua missão (%s): ---\n", jogadorInfo->corExercito);
    printf("%s\n\n", jogadorInfo->missao);
}
// Função para exibir o menu principal
void exibirMenuPrincipal() {
    printf("===============================================\n");
    printf("*** Menu de ações ***\n");
    printf("===============================================\n");
    printf("1. Atacar\n");
    printf("2. Verificar Missão\n");
    printf("0. Sair\n");
    printf("-----------------------------------------------\n");
    printf("Escolha uma opção: ");
}
// Função para realizar um ataque entre territórios
void atacar(Territorio *atacante, Territorio *defensor, Jogador *jogadorInfo,
            const Territorio *territorios, int idMissao, int *vitoriasConsecutivas) {

    if (atacante->quantidadeTropas < 1) {
        printf("O território %s não possui tropas suficientes para atacar.\n", atacante->nome);
        return;
    } else if (strcmp(atacante->corExercito, defensor->corExercito) == 0) { //verifica se as cores são iguais
        printf("O território %s não pode atacar o território %s, pois ambos pertencem ao mesmo jogador.\n",
               atacante->nome, defensor->nome);
        return;
    }
    // Simula o lançamento dos dados
    int dadoAtacante = rand() % 6 + 1;
    int dadoDefensor = rand() % 6 + 1;
    int tropasTransferidas = 0;

    printf("\nDado atacante: %d | Dado defensor: %d\n", dadoAtacante, dadoDefensor);

    if (dadoAtacante == dadoDefensor) {
        printf("Empate! Ambos perdem uma tropa.\n");
        atacante->quantidadeTropas -= 1;
        defensor->quantidadeTropas -= 1;
    } else if (dadoAtacante > dadoDefensor) {
        printf("O território %s venceu a batalha contra %s!\n", atacante->nome, defensor->nome);
        strcpy(defensor->corExercito, atacante->corExercito);
        tropasTransferidas = atacante->quantidadeTropas / 2;
        atacante->quantidadeTropas -= tropasTransferidas;
        defensor->quantidadeTropas = tropasTransferidas;
        defensor->conquistado = 1;
        (*vitoriasConsecutivas)++; // Incrementa vitórias consecutivas
    } else {
        printf("O território atacante %s foi derrotado!\n", atacante->nome);
        atacante->quantidadeTropas -= 1;
        *vitoriasConsecutivas = 0; // Reseta vitórias consecutivas
    }

    if (verificarMissao(jogadorInfo, territorios, idMissao, *vitoriasConsecutivas)) {
        printf("\n Parabéns! Você completou sua missão!\n");
    }
    printf("\nPressione Enter para continuar...\n");
    getchar();
}
// Função para gerenciar a fase de ataque
void faseDeAtaque(Jogador *jogadorInfo, Territorio *territorios, int idMissao, int *vitoriasConsecutivas) {
    int opcao;
    do {
        exibirMenuPrincipal();
        scanf("%d", &opcao);
        limparBufferEntrada();

        switch (opcao) {
            case 1: {
                int atacante, defensor;
                printf("Digite o número do território atacante (1 a %d): ", MAX_TERRITORIOS);
                scanf("%d", &atacante);
                limparBufferEntrada();

                printf("Digite o número do território defensor (1 a %d): ", MAX_TERRITORIOS);
                scanf("%d", &defensor);
                limparBufferEntrada();

                if (atacante < 1 || atacante > MAX_TERRITORIOS ||
                    defensor < 1 || defensor > MAX_TERRITORIOS) {
                    printf("Números inválidos.\n");
                } else {
                    atacar(&territorios[atacante - 1], &territorios[defensor - 1],
                           jogadorInfo, territorios, idMissao, vitoriasConsecutivas);
                }
                break;
            }
            case 2:
                exibirMissao(jogadorInfo);
                if (verificarMissao(jogadorInfo, territorios, idMissao, *vitoriasConsecutivas))
                    printf("Missão cumprida!\n");
                else
                    printf("Missão ainda não cumprida.\n");
                break;
            case 0:
                printf("\nSaindo do jogo...\n");
                break;
            default:
                printf("Opção inválida!\n");
                break;
        }
    } while (opcao != 0);
}
// Função para verificar se a missão foi cumprida
int verificarMissao(const Jogador *jogadorInfo, const Territorio *territorios, int idMissao, int vitoriasConsecutivas) {
    if (idMissao == 0) {
        // Verifica se o jogador conquistou 3 territórios
        int conquistados = 0;
        for (int i = 0; i < MAX_TERRITORIOS; i++)
            if (territorios[i].conquistado && strcmp(territorios[i].corExercito, jogadorInfo->corExercito) == 0) //utiliza o strcmp para comparar strings
                conquistados++;
        if (conquistados >= 3) return 1;
    } else if (idMissao == 1) {
        // Verifica se o jogador conquistou o território 1
        for (int i = 0; i < MAX_TERRITORIOS; i++)
            if (territorios[i].conquistado && strcmp(territorios[i].corExercito, jogadorInfo->corExercito) == 0)
                return 1;
    } else if (idMissao == 2) {
        // Verifica se o jogador perdeu todas as tropas
        int totalTropas = 0;
        for (int i = 0; i < MAX_TERRITORIOS; i++)
            if (strcmp(territorios[i].corExercito, jogadorInfo->corExercito) == 0)
                totalTropas += territorios[i].quantidadeTropas;
        if (totalTropas == 0) return 1;
    } else if (idMissao == 3) {
        // Verifica se o segundo território foi conquistado
        if (territorios[1].conquistado && strcmp(territorios[1].corExercito, jogadorInfo->corExercito) == 0)
            return 1;
    } else if (idMissao == 4) {
        // Verifica se o jogador tem vitórias consecutivas
        if (vitoriasConsecutivas >= 3) return 1;
    }
    return 0;
}