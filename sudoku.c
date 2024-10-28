/*
Primeira parte de um algoritmo que cria jogos de Sudoku, usando backtracking para resolve-lo e lógica básica para preencher os valores.
proximos passos visualização gráfica e acessibilidade.
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NMAX 9

void inicia_grid(int M[][NMAX], int n);
void imprime_sudoku(int M[][NMAX], int n);
int verifica_numero(int M[][NMAX], int lin, int col, int num);
void insere_numero(int M[][NMAX], int n);
int resolve_sudoku(int M[][NMAX]);
void remover_numeros(int M[][NMAX], int dificuldade);
void joga_sudoku(int M[][NMAX]);
int sudoku_completo(int M[][NMAX]);

int main()
{   
    // descobri q precisa disso para colocar numeros aleatorios
    srand(time(NULL));
    
    int grid[NMAX][NMAX];
    char letra;
    int dificuldade;

    inicia_grid(grid, NMAX);
    resolve_sudoku(grid);
    
    printf("Ola para iniciar selecione a dificuldade: 'F' para facil, 'M' para medio, 'D' para difcil\n");
    scanf("%c", &letra); // Use & para passar o endereço da variável
    getchar();

    if(letra == 'F') dificuldade = 3;//(rand() % 6) + 30;
    if(letra == 'M') dificuldade = (rand() % 11) + 35;
    if(letra == 'D') dificuldade = (rand() % 6) + 45;

    remover_numeros(grid, dificuldade);
    imprime_sudoku(grid, NMAX);

    while (1) {
        joga_sudoku(grid);
        if (sudoku_completo(grid)) {
            printf("Parabens! Voce resolveu o Sudoku!\n");
            break;
        }
    }

    return 0;
}

//essa função recebe uma matriz vazia e preenche com valores de 0 
void inicia_grid(int M[NMAX][NMAX], int n) {
    
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            M[i][j] = 0;
        }    
    }
    printf("\n");

}

//essa função recebe uma matriz e imprime seus valores
void imprime_sudoku(int M[][NMAX], int n) {
    
    printf("Sudoku: \n");
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            printf("%d ", M[i][j]);
        }
        printf("\n");
    }

}

//essa funcao verifica se o numero inserido não quebra a solução do sudoku
int verifica_numero(int M[][NMAX], int lin, int col, int num){

    for (int i = 0; i < NMAX; i++){
        if ((i != col && M[lin][i] == num) || (i != lin && M[i][col] == num)) {
            return 0;
        }
    }
    
    //Aqui eu pego a linha atual e verifico em qual grade 3x3 do sudoku 9x9 está de acordo com as coordenadas iniciais da grade
    //ou seja, para o exemplo (linha = 4; coluna = 5), essas cordenadas da na grade do meio com pontos iniciais (3,3)
    //ou seja 4 - 4 % 3 = 4 - 1 = 3
    //5 - 5 % 3 = 5 - 2 = 3
    int gradeLinha = lin - lin % 3, gradecoluna = col - col % 3;

    for(int j = 0; j < 3; j++){
        for(int k = 0; k < 3; k++){
            if ((gradeLinha + j != lin || gradecoluna + k != col) && M[gradeLinha + j][gradecoluna + k] == num) {
                return 0;
            }
        }
    }
    
    return 1;
}

//insere numeros manualmente, função para testes recomendo mudar o NMAX para testar;
void insere_numero(int M[][NMAX], int n){
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            scanf("%d", &M[i][j]);
            if(verifica_numero(M, i, j, M[i][j])){
                printf("numero safe\n");
            }else{
                printf("numero errado\n");
            }
        }    
    }
    printf("\n");
}

//aqui é um algoritmo backtracking, ou seja ele encontra o primeiro valor vazio que no nosso caso é local da matriz com valor 0
//depois ela preenche com um valor e testa se esse valor é válido para solução da matriz se for ela preenche com o num
//se não ele preenche com 0 e tenta com outro número. ou seja volta atras em um passo.
int resolve_sudoku(int M[][NMAX]) {
    int isVazio = 1;
    int linha = -1, coluna = -1; //apenas uso padrão para as varíaveis ainda não usadas
    for (int i = 0; i < NMAX; i++) {
        for (int j = 0; j < NMAX; j++) {
            if (M[i][j] == 0) {
                linha = i;
                coluna = j;
                isVazio = 0;
                break; 
            }
        }
        if (!isVazio) break; 
    }
    
    if (isVazio) return 1;
    for (int k = 0; k <= NMAX; k++) {
        int num = rand() % NMAX + 1;
        if(verifica_numero(M, linha, coluna, num)){
            M[linha][coluna] = num;
            if (resolve_sudoku(M)) return 1;
            M[linha][coluna] = 0; //backtracking
        }  
    }
    return 0;  
}

//Essa função remove aleatoriamente alguns numeros do sudoku de acordo com a dificuldade escolhida
void remover_numeros(int M[][NMAX], int dificuldade){
    int contador = dificuldade;
    while (contador != 0)
    {
        int aleatorio = rand() % 81;
        int linha = aleatorio / 9;
        int coluna = aleatorio % 9;
        if(M[linha][coluna] != 0){
            M[linha][coluna] = 0;
            contador--;
        }
    }
}

//adicionar as jogadas 
void joga_sudoku(int M[][NMAX]) {
    int linha, coluna, num;
    printf("Insira linha, coluna e numero: ");
    scanf("%d %d %d", &linha, &coluna, &num);
    if (verifica_numero(M, linha, coluna, num) && M[linha][coluna] == 0 && (num > 0 && num <= 9)){
        M[linha][coluna] = num; 
        printf("Jogada Correta!\n");
        imprime_sudoku(M, NMAX);
    } else {
        printf("Jogada incorreta!\n");
    }
}

//verifica se o sudoku está completo
int sudoku_completo(int M[][NMAX]) {
    for (int i = 0; i < NMAX; i++) {
        for (int j = 0; j < NMAX; j++) {
            if (M[i][j] == 0 || !verifica_numero(M, i, j, M[i][j])) {
                return 0; 
            }
        }
    }
    return 1; 
}
