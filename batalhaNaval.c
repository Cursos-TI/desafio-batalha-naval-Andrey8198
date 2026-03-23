#include <stdio.h>

// Desafio Batalha Naval - MateCheck
// Este código inicial serve como base para o desenvolvimento do sistema de Batalha Naval.
// Siga os comentários para implementar cada parte do desafio.
int board[10][10];


int main() {
    // Inicializando o tamanho dos navios e os arrays dos navios
    int maxShipSize = 3;
    int ship1[] = {3, 3, 3};
    int ship2[] = {3, 3, 3};
    int ship3[] = {3, 3, 3};
    int ship4[] = {3, 3, 3};

    // Inicializar habilidades
    int upsidedownTriangle[5][5];
    int cross[5][5];
    int diamond[5][5];

    // Inicializar tabuleiro com 0
    for(int i = 0; i < 10; i++) { for(int o = 0; o < 10; o++) { board[i][o] = 0; } }

    // Inicializar poderes
    initializeHability(5, upsidedownTriangle, 't'); // Triângulo
    initializeHability(5, cross, 'c'); // Cruz
    initializeHability(5, diamond, 'd'); // Diamante

    // Checar se as posições são válidas e posicionar navios
    checkPositionShip(4, 5, ship1, maxShipSize, 'H');
    checkPositionShip(2, 9, ship2, maxShipSize, 'V');
    checkPositionShip(6, 3, ship2, maxShipSize, 'd');
    checkPositionShip(3, 3, ship2, maxShipSize, 'D');

    // Checar se as posições são válidas e posicionar habilidades
    checkPositionHability(7, 3, 5, upsidedownTriangle);
    checkPositionHability(4, 7, 5, cross);
    checkPositionHability(3, 5, 5, diamond);

    // Renderizar tabuleiro
    renderBoard();

    return 0;
}

// Retorna 1 se as posições estão vazias, 0 se alguma está em uso
//
// Direções são:
// H/h - horizontal, preencher row
// V/v - vertical, preencher collum
// D - diagonal subindo
// d - diagonal descendo
int checkValidPositionsShip(int row, int collum, int shipSize, int direction) {
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
        printf("checkValidPositionsShip() -> Erro nas direções\n");
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
    if(checkValidPositionsShip(row, collum, shipSize, direction)) { positionShip(row, collum, ship, shipSize, direction); } 
    else {
        printf("Navio: { ");
        for(int i = 0; i < shipSize; i++) { printf("%i ", ship[i]); }
        printf("} - Posição não é válida!\n"); 
    }
}

// Renderiza a array board (tabuleiro) em cor ao stdout
void renderBoard() {
    // ANSI_COLOR_YELLOW  "\x1b[33m"
    // ANSI_COLOR_BLUE    "\x1b[34m"
    // ANSI_COLOR_RED     "\x1b[31m"
    // ANSI_COLOR_RESET   "\x1b[0m"
    for(int i = 0; i < 10; i++) {
        
        for(int o = 0; o < 10; o++) { 
            if(board[i][o] == 3) {
                printf("\x1b[33m" "%i " "\x1b[0m", board[i][o]);
            } else if(board[i][o] == 5) {
                printf("\x1b[31m" "%i " "\x1b[0m", board[i][o]);
            } else {
                printf("\x1b[34m" "%i " "\x1b[0m", board[i][o]);
            }
        }
        
        printf("\n");
    }
}

// Inicializa um array com uma forma de habilidade
//
// Formas válidas são:
// T/t - triângulo de ponta-cabeça
// C/c - cruz
// L/l - losango
void initializeHability(int arraySize, int habilityArray[][arraySize], char habilityType) {
    int right, left;

    // Encher de zero
    for(int i = 0; i < arraySize; i++) { for(int o = 0; o < arraySize; o++) { habilityArray[i][o] = 0; } }

    switch(habilityType) {
    // 1 1 1 1 1
    // 0 1 1 1 0
    // 0 0 1 0 0
    // 0 0 0 0 0
    // 0 0 0 0 0
    case 'T':
    case 't':
        right = 0, left = arraySize;

        // Criar forma
        for(int i = 0; i < arraySize; i++) {
            for(int o = right; o < left; o++) {
                habilityArray[i][o] = 1;
            }

            right++;
            left--;
        }

        break;

    // 0 0 1 0 0
    // 1 1 1 1 1
    // 0 0 1 0 0
    // 0 0 1 0 0
    // 0 0 1 0 0
    case 'C':
    case 'c':
        right = (arraySize / 2) - 1, left = (arraySize - right) - 1;
        int crossArms = arraySize / 3;

        // Criar forma
        for(int i = 0; i < arraySize; i++) {
            for(int o = 0; o < arraySize; o++) {
                if(i == crossArms || o > right && o < left) { habilityArray[i][o] = 1; }
                // if() { habilityArray[i][o] = 1; }
            }
        }

        break;

    // 0 0 1 0 0
    // 0 1 1 1 0
    // 1 1 1 1 1
    // 0 1 1 1 0
    // 0 0 1 0 0
    case 'D':
    case 'd':
        right = (arraySize / 2) - 1, left = (arraySize - right) - 1;
        int isDecreasing = 0;

        // Criar forma
        for(int i = 0; i < arraySize; i++) {
            for(int o = 0; o < arraySize; o++) {
                if(o > right && o < left) { habilityArray[i][o] = 1; }
            }

            if(left == arraySize || isDecreasing) { isDecreasing = 1; right++; left--; } else { right--; left++; }
        }

        break;

    default:
        printf("initializeHability() -> Erro no tipo de habilidade");
        break;
    }
}

// Retorna 1 se a forma da habilidade está dentro dos limites do array de board (tabuleiro), 0 se não
int checkValidPositionsHability(int row, int collum, int arraySize) {
    return !(row + (arraySize / 2) >= 10 || collum + (arraySize / 2) >= 10) ||
            (row - (arraySize / 2) < 0 || collum - (arraySize / 2) < 0);
}

// Posiciona uma forma de habilidade no board (tabuleiro) usando o centro da forma como ponto de montagem
void positionHability(int row, int collum, int arraySize, int habilityArray[][arraySize]) {
    int startRow = row - (arraySize / 2) - 1, startCollum = collum - (arraySize / 2) - 1, \
    finishRow = row + (arraySize / 2) - 1, finishCollum = collum + (arraySize / 2) - 1;

    for(int i = startRow, hi = 0; i <= finishRow; i++, hi++)
        { for(int o = startCollum, ho = 0; o <= finishCollum; o++, ho++) {
            if(habilityArray[hi][ho] == 1) { board[i][o] = 5; }
        }
    }

}

// Determina se a posição é válida e posiciona forma de habilidade em board (tabuleiro) se for válida, faz nada se for inválida
void checkPositionHability(int row, int collum, int arraySize, int habilityArray[][arraySize]) {
    if(checkValidPositionsHability(row, collum, arraySize)) { positionHability(row, collum, arraySize, habilityArray); }
    else {
        printf("Forma de habilidade: {\n");
        for(int i = 0; i < arraySize; i++) { for(int o = 0; o < arraySize; o++) { printf("%i ", habilityArray[i][o]); } printf("\n"); }
        printf("} - Posição não é válida!\n\n");
    }
}
