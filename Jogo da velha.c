#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>

#define MAX_NOME 50
#define MAX_USUARIOS 100
#define MAX_PARTIDAS 100
#define ARQUIVO_USUARIOS "usuarios.txt"
#define ARQUIVO_PARTIDAS "partidas.txt"

typedef struct {
    char nome[MAX_NOME];
    char senha[MAX_NOME];
    int vitorias;
    int derrotas;
} Usuario;

typedef struct {
    char jogador1[MAX_NOME];
    char jogador2[MAX_NOME];
    char tabuleiro[3][3];
    int vez;
    int emAndamento;
    int contraBot;
    time_t dataHora;
} Partida;

Usuario usuarios[MAX_USUARIOS];
int totalUsuarios = 0;

void colorirTexto(const char *texto, int cor) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), cor);
    printf("%s", texto);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
}

void salvarUsuarios() {
    FILE *f = fopen(ARQUIVO_USUARIOS, "w");
    if (!f) return;
    for (int i = 0; i < totalUsuarios; i++) {
        fprintf(f, "%s %s %d %d\n", usuarios[i].nome, usuarios[i].senha, usuarios[i].vitorias, usuarios[i].derrotas);
    }
    fclose(f);
}

void carregarUsuarios() {
    FILE *f = fopen(ARQUIVO_USUARIOS, "r");
    if (!f) return;
    while (fscanf(f, "%s %s %d %d", usuarios[totalUsuarios].nome, usuarios[totalUsuarios].senha,
                  &usuarios[totalUsuarios].vitorias, &usuarios[totalUsuarios].derrotas) != EOF) {
        totalUsuarios++;
    }
    fclose(f);
}

int autenticar(char nome[]) {
    char senha[MAX_NOME];
    printf("Senha: ");
    int i = 0;
    char ch;
    while ((ch = getch()) != '\r') {
        if (ch == '\b') {
            if (i > 0) {
                i--;
                printf("\b \b");
            }
        } else {
            senha[i++] = ch;
            printf("*");
        }
    }
    senha[i] = '\0';
    printf("\n");

    for (int i = 0; i < totalUsuarios; i++) {
        if (strcmp(usuarios[i].nome, nome) == 0 && strcmp(usuarios[i].senha, senha) == 0) {
            return i;
        }
    }
    return -1;
}

int registrarUsuario() {
    char nome[MAX_NOME], senha[MAX_NOME];
    printf("Novo nome: ");
    scanf(" %s", nome);
    for (int i = 0; i < totalUsuarios; i++) {
        if (strcmp(usuarios[i].nome, nome) == 0) {
            printf("Usuário já existe.\n");
            return -1;
        }
    }
    printf("Nova senha: ");
    scanf(" %s", senha);
    strcpy(usuarios[totalUsuarios].nome, nome);
    strcpy(usuarios[totalUsuarios].senha, senha);
    usuarios[totalUsuarios].vitorias = 0;
    usuarios[totalUsuarios].derrotas = 0;
    totalUsuarios++;
    salvarUsuarios();
    return totalUsuarios - 1;
}

void exibirTabuleiro(char tabuleiro[3][3]) {
    colorirTexto("\n    0   1   2\n", 11);  // Título da coluna
    for (int i = 0; i < 3; i++) {
        printf("  +---+---+---+\n");
        printf("%d ", i);
        for (int j = 0; j < 3; j++) {
            printf("| ");
            if (tabuleiro[i][j] == 'X') {
                colorirTexto("X", 12);  // Vermelho para X
            } else if (tabuleiro[i][j] == 'O') {
                colorirTexto("O", 9);   // Azul para O
            } else {
                printf(" ");
            }
            printf(" ");
        }
        printf("|\n");
    }
    printf("  +---+---+---+\n");
}

int verificarVitoria(char tabuleiro[3][3], char simbolo) {
    for (int i = 0; i < 3; i++) {
        if (tabuleiro[i][0] == simbolo && tabuleiro[i][1] == simbolo && tabuleiro[i][2] == simbolo) return 1;
        if (tabuleiro[0][i] == simbolo && tabuleiro[1][i] == simbolo && tabuleiro[2][i] == simbolo) return 1;
    }
    if (tabuleiro[0][0] == simbolo && tabuleiro[1][1] == simbolo && tabuleiro[2][2] == simbolo) return 1;
    if (tabuleiro[0][2] == simbolo && tabuleiro[1][1] == simbolo && tabuleiro[2][0] == simbolo) return 1;
    return 0;
}

int verificarEmpate(char tabuleiro[3][3]) {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (tabuleiro[i][j] == ' ') return 0;
    return 1;
}

void salvarPartida(Partida *p) {
    FILE *f = fopen(ARQUIVO_PARTIDAS, "w");
    if (!f) return;
    fwrite(p, sizeof(Partida), 1, f);
    fclose(f);
}

int carregarPartida(Partida *p) {
    FILE *f = fopen(ARQUIVO_PARTIDAS, "r");
    if (!f) return 0;
    fread(p, sizeof(Partida), 1, f);
    fclose(f);
    return 1;
}

void limparPartidaSalva() {
    remove(ARQUIVO_PARTIDAS);
}

int capturarEntrada() {
    int valor;
    do {
        scanf("%d", &valor);
        if (valor < 0 || valor > 2)
            printf("Valor inválido! Digite 0, 1 ou 2: ");
    } while (valor < 0 || valor > 2);
    return valor;
}

void jogarPartida(Usuario *j1, Usuario *j2, int contraBot) {
    Partida p;
    if (!carregarPartida(&p) || !p.emAndamento) {
        memset(&p, 0, sizeof(p));
        strcpy(p.jogador1, j1 ? j1->nome : "Anonimo1");
        strcpy(p.jogador2, j2 ? j2->nome : contraBot ? "Bot" : "Anonimo2");
        p.vez = 0;
        p.contraBot = contraBot;
        p.dataHora = time(NULL);
        p.emAndamento = 1;
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                p.tabuleiro[i][j] = ' ';
    }

    int linha, coluna;
    while (1) {
        exibirTabuleiro(p.tabuleiro);
        printf("\nData e hora da partida: %s", ctime(&p.dataHora));
        char simbolo = p.vez % 2 == 0 ? 'X' : 'O';
        char *nome = p.vez % 2 == 0 ? p.jogador1 : p.jogador2;

        if (contraBot && strcmp(nome, "Bot") == 0) {
            do {
                linha = rand() % 3;
                coluna = rand() % 3;
            } while (p.tabuleiro[linha][coluna] != ' ');  // Lógica de jogada do bot
            printf("Bot jogou na posição %d %d\n", linha, coluna);
        } else {
            printf("%s (%c), digite linha e coluna: ", nome, simbolo);
            do {
                linha = capturarEntrada();
                coluna = capturarEntrada();
                if (p.tabuleiro[linha][coluna] != ' ')
                    printf("Posição já ocupada! Escolha outra: ");
            } while (p.tabuleiro[linha][coluna] != ' ');
        }

        p.tabuleiro[linha][coluna] = simbolo;

        if (verificarVitoria(p.tabuleiro, simbolo)) {
            exibirTabuleiro(p.tabuleiro);
            printf("%s venceu!\n", nome);
            if (j1 && strcmp(nome, j1->nome) == 0) {
                j1->vitorias++;
                if (j2) j2->derrotas++;
            } else if (j2 && strcmp(nome, j2->nome) == 0) {
                j2->vitorias++;
                if (j1) j1->derrotas++;
            }
            salvarUsuarios();
            limparPartidaSalva();
            break;
        } else if (verificarEmpate(p.tabuleiro)) {
            exibirTabuleiro(p.tabuleiro);
            printf("Empate!\n");
            limparPartidaSalva();
            break;
        }
        p.vez++;
        salvarPartida(&p);
    }
}

void exibirRanking() {
    printf("\n--- Ranking ---\n");
    for (int i = 0; i < totalUsuarios; i++) {
        int total = usuarios[i].vitorias + usuarios[i].derrotas;
        float taxa = total > 0 ? ((float)usuarios[i].vitorias / total) * 100 : 0;
        printf("%s - Vitórias: %d | Derrotas: %d | Winrate: %.2f%%\n", usuarios[i].nome,
               usuarios[i].vitorias, usuarios[i].derrotas, taxa);
    }

    // Jogadores sem login (Anônimo)
    printf("\n--- Jogadores Sem Login ---\n");
    for (int i = 0; i < 10; i++) {  // Limite para evitar muitos jogadores anônimos
        char nomeAnonimo[MAX_NOME];
        snprintf(nomeAnonimo, sizeof(nomeAnonimo), "Anonimo%d", i+1);
        printf("%s - Vitórias: %d | Derrotas: %d | Winrate: %.2f%%\n",
               nomeAnonimo, 0, 0, 0.0);
    }
}

void menu() {
    int opcao, indice1 = -1, indice2 = -1;
    srand(time(NULL));
    carregarUsuarios();
    do {
        colorirTexto("\n--- MENU ---\n", 14);
        printf("1. Login\n2. Registrar\n3. Jogar contra Bot\n4. Jogar sem login\n5. Ranking\n6. Continuar partida\n7. Sair\nEscolha: ");
        scanf("%d", &opcao);
        switch (opcao) {
            case 1:
                {
                    char nome[MAX_NOME];
                    printf("Nome: ");
                    scanf("%s", nome);
                    indice1 = autenticar(nome);
                    if (indice1 != -1) {
                        printf("Login bem-sucedido.\n");
                        char nome2[MAX_NOME];
                        printf("Digite o nome do outro jogador: ");
                        scanf("%s", nome2);
                        indice2 = autenticar(nome2);  // Autentica o segundo jogador
                        jogarPartida(&usuarios[indice1], &usuarios[indice2], 0);  // Inicia a partida entre dois jogadores
                    } else {
                        printf("Usuário ou senha inválidos.\n");
                    }
                }
                break;
            case 2:
                {
                    indice1 = registrarUsuario();
                    if (indice1 != -1) {
                        printf("Usuário registrado com sucesso.\n");
                    }
                }
                break;
            case 3:
                {
                    char nome[MAX_NOME];
                    printf("Digite seu nome: ");
                    scanf("%s", nome);
                    indice1 = autenticar(nome);
                    if (indice1 != -1) {
                        printf("Login bem-sucedido.\n");
                        jogarPartida(&usuarios[indice1], NULL, 1);  // Jogar contra o bot
                    } else {
                        printf("Usuário não encontrado.\n");
                    }
                }
                break;
            case 4:
                {
                    jogarPartida(NULL, NULL, 0);  // Jogar sem login
                }
                break;
            case 5:
                exibirRanking();
                break;
            case 6:
                {
                    Partida p;
                    if (carregarPartida(&p) && p.emAndamento) {
                        printf("Continuando partida...\n");
                        jogarPartida(NULL, NULL, p.contraBot);
                    } else {
                        printf("Não há partidas não finalizadas.\n");
                    }
                }
                break;
            case 7:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (opcao != 7);
}

int main() {
    menu();
    return 0;
}
