#include <stdlib.h>  /* exit() y EXIT_FAILURE */
#include <stdio.h>   /* printf(), scanf()     */
#include <stdbool.h> /* Tipo bool             */

#include <assert.h>  /* assert() */

#define BOARD_SIZE 3
#define CELL_MAX (BOARD_SIZE * BOARD_SIZE - 1)

void print_board(char board[BOARD_SIZE][BOARD_SIZE])
{
    int cell = 0;
    printf("\t .................................................\n");
    for (int row = 0; row < BOARD_SIZE; ++row) {
        for (int column = 0; column < BOARD_SIZE; ++column) {
            printf("\t | %d: %c ", cell, board[row][column]);
            ++cell;
        }
        printf("\t | \n");
        printf("\t .................................................\n");
    }
}

char get_winner(char board[BOARD_SIZE][BOARD_SIZE])
{
    board = board;
    char winner = '-';
    int equal1;
    int equal2;
    int equal3=0;
    int equal4=0;

    for (size_t i = 0; i < BOARD_SIZE; i++)             //verifica filas iguales
    {
        equal1 = 0;
        for (size_t j = 0; j < BOARD_SIZE-1; j++)
        {
            if (board[i][j] == board[i][j+1])
                equal1++;
        }if (equal1 == BOARD_SIZE-1)
            winner = board[i][0];
    }

    for (size_t j = 0; j < BOARD_SIZE; j++)             //verifica columnas iguales
    {
        equal2 = 0;
        for (size_t i = 0; i < BOARD_SIZE-1; i++)
        {
            if (board[i][j] == board[i+1][j])
                equal2++;
        }if (equal2 == BOARD_SIZE-1)
            winner = board[0][j];
    }
    
    for (size_t j = 0; j < BOARD_SIZE-1; j++)           //verifica diagonales de izq a der
    {
        if (board[j][j] == board[j+1][j+1])
            equal3++;
        if (equal3 == BOARD_SIZE-1)
            winner = board[j][j];
    }

    for (size_t j = 0; j < BOARD_SIZE-1; j++)             //verifica diagonales de der a izq
    {
        if (board[j][BOARD_SIZE-j-1] == board[j+1][BOARD_SIZE-j-2])
            equal4++;
        if (equal4 == BOARD_SIZE-1)
            winner = board[0][BOARD_SIZE-1];
    }

    return winner;
}

bool has_free_cell(char board[BOARD_SIZE][BOARD_SIZE])
{
    board = board;
    bool full = false;

    for (size_t i = 0; i < BOARD_SIZE; i++)
    {
        for (size_t j = 0; j < BOARD_SIZE; j++)
            full = full || board[i][j] == '-';   
    }

    return full;
}

int main(void)
{
    printf("TicTacToe [InCoMpLeTo :'(]\n");

    char board[BOARD_SIZE][BOARD_SIZE] = {
        { '-', '-', '-' },
        { '-', '-', '-' },
        { '-', '-', '-' }
    };

    char turn = 'X';
    char winner = '-';
    int cell = 0;
    while (winner == '-' && has_free_cell(board)) {
        print_board(board);
        printf("\nTurno %c - Elija posición (número del 0 al 8): ",
               turn);
        int scanf_result = scanf("%d", &cell);
        if (scanf_result <= 0) {
            printf("Error al leer un número desde teclado\n");
            exit(EXIT_FAILURE);
        }
        if (cell >= 0 && cell <= CELL_MAX) {
            int row = cell / BOARD_SIZE;
            int colum = cell % BOARD_SIZE;
            if (board[row][colum] == '-') {
                board[row][colum] = turn;
                turn = turn == 'X' ? 'O' : 'X';
                winner = get_winner(board);
            } else {
                printf("\nCelda ocupada!\n");
            }
        } else {
            printf("\nCelda inválida!\n");
        }
    }
    print_board(board);
    if (winner == '-') {
        printf("Empate!\n");
    } else {
        printf("Ganó %c\n", winner);
    }
    return 0;
}
