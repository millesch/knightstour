#include <iostream>
#include <iomanip>
#include <chrono>
#define N 8

//retirado da internet tutorialspoint.com/The-Knight-s-tour-problem
using namespace std;
int sol[N][N];

bool isValid(int x, int y, int sol[N][N]) {     //check place is in range and not assigned yet
    return (x >= 0 && x < N && y >= 0 && y < N && sol[x][y] == -1);
}

void displaySolution() {
    for (int x = 0; x < N; x++) {
        for (int y = 0; y < N; y++)
            cout << setw(3) << sol[x][y] << " ";
        cout << endl;
    }
}

int knightTour(int x, int y, int move, int sol[N][N], int xMove[N], int yMove[N], int &contador) {
    int xNext, yNext;
    if (move == N * N)     //when the total board is covered
        return true;

    for (int k = 0; k < 8; k++) {
        xNext = x + xMove[k];
        yNext = y + yMove[k];
        if (isValid(xNext, yNext, sol)) {     //check room is preoccupied or not
            sol[xNext][yNext] = move;
            contador++;
            if (knightTour(xNext, yNext, move + 1, sol, xMove, yMove,contador) == true) {
                return true;
            }
            else
                sol[xNext][yNext] = -1;// backtracking
        }
    }
    return false;
}

bool findKnightTourSol(int posicao_x, int posicao_y) {
    int contador = 0;

    for (int x = 0; x < N; x++)     //initially set all values to -1 of solution matrix
        for (int y = 0; y < N; y++)
            sol[x][y] = -1;
    //all possible moves for knight
    int xMove[8] = { 2, 1, -1, -2, -2, -1,  1,  2 };
    int yMove[8] = { 1, 2,  2,  1, -1, -2, -2, -1 };
    //ajustado para input
    sol[posicao_x][posicao_y] = 0;     //starting from room (0, 0)

    if (knightTour(0, 0, 1, sol, xMove, yMove, contador) == false) {
        cout << "Solution does not exist";
        return false;
    }
    else
        displaySolution();
        cout << "\nPassos do Algoritmo (recursividade): " << contador;
    return true;
}

int main() {
    //desenvolvido
    int posicao_x;
    int posicao_y;

    do {
        cout << "\nChoose your position (x): ";
        cin >> posicao_x;

        if (posicao_x > N) {
            cout << "\nPlease enter a valid value!\n";
        }

    } while (posicao_x > N);

    do {
        cout << "\nChoose your position (y): ";
        cin >> posicao_y;

        if (posicao_y > N) {
            cout << "\nPlease enter a valid value!\n";
        }

    } while (posicao_y > N);

    auto start = std::chrono::high_resolution_clock::now();

    findKnightTourSol(posicao_x, posicao_y);

    auto end = std::chrono::high_resolution_clock::now();
    auto duration_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    auto duration_s = std::chrono::duration_cast<std::chrono::seconds>(end - start).count();

    cout << "\nDurou " << duration_ms << " milisegundos\n";
    
    cout << "\nDurou " << duration_s << " segundos\n";
   
}