#include <stdio.h>

// Desafio Batalha Naval - MateCheck
// Este código inicial serve como base para o desenvolvimento do sistema de Batalha Naval.
// Siga os comentários para implementar cada parte do desafio.
int board[10][10];


int main() {
    // Nível Novato - Posicionamento dos Navios
    // Sugestão: Declare uma matriz bidimensional para representar o tabuleiro (Ex: int tabuleiro[5][5];).
    // Sugestão: Posicione dois navios no tabuleiro, um verticalmente e outro horizontalmente.
    // Sugestão: Utilize `printf` para exibir as coordenadas de cada parte dos navios.
    int maxShipSize = 3;
    int ship1[] = {3, 3, 3};
    int ship2[] = {3, 3, 3};
    int ship3[] = {3, 3, 3};
    int ship4[] = {3, 3, 3};

    // Inicializar tabuleiro com 0
    for(int i = 0; i < 10; i++) { for(int o = 0; o < 10; o++) { board[i][o] = 0; } }

    // Checar se as posições são válidas e posicionar navios
    checkPositionShip(4, 5, ship1, maxShipSize, 'H');
    checkPositionShip(2, 9, ship2, maxShipSize, 'V');
    checkPositionShip(6, 3, ship2, maxShipSize, 'd');
    checkPositionShip(3, 3, ship2, maxShipSize, 'D');

    // Renderizar tabuleiro
    renderBoard();
    

    // Nível Aventureiro - Expansão do Tabuleiro e Posicionamento Diagonal
    // Sugestão: Expanda o tabuleiro para uma matriz 10x10.
    // Sugestão: Posicione quatro navios no tabuleiro, incluindo dois na diagonal.
    // Sugestão: Exiba o tabuleiro completo no console, mostrando 0 para posições vazias e 3 para posições ocupadas.

    // Nível Mestre - Habilidades Especiais com Matrizes
    // Sugestão: Crie matrizes para representar habilidades especiais como cone, cruz, e octaedro.
    // Sugestão: Utilize estruturas de repetição aninhadas para preencher as áreas afetadas por essas habilidades no tabuleiro.
    // Sugestão: Exiba o tabuleiro com as áreas afetadas, utilizando 0 para áreas não afetadas e 1 para áreas atingidas.

    // Exemplos de exibição das habilidades:
    // Exemplo para habilidade em cone:
    // 0 0 1 0 0
    // 0 1 1 1 0
    // 1 1 1 1 1
    
    // Exemplo para habilidade em octaedro:
    // 0 0 1 0 0
    // 0 1 1 1 0
    // 0 0 1 0 0

    // Exemplo para habilidade em cruz:
    // 0 0 1 0 0
    // 1 1 1 1 1
    // 0 0 1 0 0

    return 0;
}

// Retorna 1 se as posições estão vazias, 0 se alguma está em uso
//
// Direções são:
// H/h - horizontal, preencher row
// V/v - vertical, preencher collum
// D - diagonal subindo
// d - diagonal descendo
int checkValidPositions(int row, int collum, int shipSize, int direction) {
    int valid = 0;

    switch(direction) {
    case 'H':
    case 'h':
        // Testar se a posição do navio está dentro dos limites do array
        if((row >= 10) || (collum + shipSize >= 10)) { return 0; }

        // Testar se a posição do navio está disponível
        for(int i = 0; i < shipSize; i++) { valid = board[row][collum + i] == 0; }
        break;

    case 'V':
    case 'v':
        // Testar se a posição do navio está dentro dos limites do array
        if((row + shipSize >= 10) || (collum >= 10)) { return 0; }

        // Testar se a posição do navio está disponível
        for(int i = 0; i < shipSize; i++) { valid = board[row + i][collum] == 0; }
        break;

    case 'D':
        // Testar se a posição do navio está dentro dos limites do array
        if((row - shipSize < 0) || (collum - shipSize < 0)) { return 0; }

        // Testar se a posição do navio está disponível
        for(int i = 0; i < shipSize; i++) { valid = board[row - i][collum - i] == 0; }
        break;

    case 'd':
        // Testar se a posição do navio está dentro dos limites do array
        if((row + shipSize >= 10) || (collum + shipSize >= 10)) { return 0; }

        // Testar se a posição do navio está disponível
        for(int i = 0; i < shipSize; i++) { valid = board[row + i][collum + i] == 0; }
        break;

    default:
        printf("checkValidPositions() -> Erro nas direções\n");
        return 0;
    }

    return valid;
}

// Posiciona navio em board (tabuleiro). Deduz que as posições são válidas
//
// Direções são:
// H/h - horizontal, preencher row
// V/v - vertical, preencher collum
// D - diagonal subindo
// d - diagonal descendo
void positionShip(int row, int collum, int ship[], int shipSize, int direction) {

    switch(direction) {
    case 'H':
    case 'h':
        for(int i = 0; i < shipSize; i++) { board[row][collum + i] = ship[i]; }
        break;

    case 'V':
    case 'v':
        for(int i = 0; i < shipSize; i++) { board[row + i][collum] = ship[i]; }
        break;

    case 'D':
        for(int i = 0; i < shipSize; i++) { board[row - i][collum - i] = ship[i]; }
        break;

    case 'd':
        for(int i = 0; i < shipSize; i++) { board[row + i][collum + i] = ship[i]; }
        break;

    default:
        printf("positionShip() -> Erro nas direções\n");
        break;
    }
}

// Determina se a posição é válida e posiciona navio em board (tabuleiro) se for válida, faz nada se for inválida
//
// Direções são:
// H/h - horizontal, preencher row
// V/v - vertical, preencher collum
// D - diagonal subindo
// d - diagonal descendo
void checkPositionShip(int row, int collum, int ship[], int shipSize, int direction) {
    if(checkValidPositions(row, collum, shipSize, direction)) { positionShip(row, collum, ship, shipSize, direction); }
}

// Renderiza a array board (tabuleiro) em cor ao stdout
void renderBoard() {
    // ANSI_COLOR_YELLOW  "\x1b[33m"
    // ANSI_COLOR_BLUE    "\x1b[34m"
    // ANSI_COLOR_RESET   "\x1b[0m"
    for(int i = 0; i < 10; i++) {
        
        for(int o = 0; o < 10; o++) { 
            (board[i][o] == 3)? printf("\x1b[33m" "%i " "\x1b[0m", board[i][o]) : printf("\x1b[34m" "%i " "\x1b[0m", board[i][o]); 
        }
        
        printf("\n");
    }
}
