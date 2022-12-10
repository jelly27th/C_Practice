#include "Backtrack.h"
#include <stdlib.h>
#include <stdio.h>

// Suppose the distance set is sorted from small to large.
// In the distance set D, find a maximum value, if found, return -1.
static int FindMax(int D[], int N) {
    for (int i = N * (N - 1) / 2; i >= 1; i--) {
        if (D[i] != -1) return D[i];
    }
    return -1;
}

// Suppose the distance set is sorted from small to large.
// In the D array of size N, find a number Num, and delete the number (set to -1).
// Returns false if not found.
static bool FindNum(int D[], int N, int Num) {
    for (int i = 1; i <= N * (N - 1) / 2; i++) {
        if (D[i] == Num) {
            D[i] = -1;
            return true;
        }
    }
    return  false;
}

// Copy the elements in the Dset collection to Dtmp.
static void Copy(int Dtmp[], int Dset[], int N) {
    for (int i = 1; i <= N * (N - 1) / 2; i++) {
        Dtmp[i] = Dset[i];
    }
}

// x[] is a collection of points.
// Dset[] is a collection of distance of point to point.
// N is the number of point.
int turnPike(int X[], int Dset[], int N) {
    // Include the largest and smallest points into the vertices.
    X[1] = 0;
    X[N] = Dset[N * (N - 1) / 2];
    // Set the maximum distance to -1, which means empty.
    Dset[N * (N - 1) / 2] = -1;
    return Place(X, Dset, N, 2, N-1);
}

// x[] is a collection of points.
// Dset[] is a collection of distance of point to point.
// N is the number of point.
// left and right are the leftmost and rightmost of X[].
static bool Place(int X[], int Dset[], int N, int Left,int Right) {
    bool found = false, flag = false;
    
    if (Left > Right) return true;
    
    // the maximum value of the current distance set Dset[].
    int Dmax = FindMax(Dset, N);

    // Dtmp[] is a copy of Dset[] for backtracking.
    int* Dtmp = malloc(sizeof(int) * (N * (N - 1) / 2));
    Copy(Dtmp, Dset, N);

    /*First step: try to place DMax at X[right].*/
    //Judge whether the distance of X[i]-DMax is in the set Dtmp[], i ∈ [1, left) 
    for (int i = 1; i < Left; i++) {
        if (!FindNum(Dtmp, N, abs(X[i] - Dmax))) {
            flag = true;
            break;
        }
    }

    //Judge whether the distance of X[i]-DMax is in the set Dtmp[], i ∈ (right, N]
    for (int i = N; i > Right; i--) {
        if (!FindNum(Dtmp, N, abs(X[i] - Dmax))) {
            flag = true;
            break;
        }
    }

    // if Dmax can place in the set X[], recursive next level.
    if (!flag) {
        X[Right] = Dmax;
        found = Place(X, Dtmp, N, Left, Right - 1);
    }

    /*If first attempt failed, try to place X[N] - Dmax at X[left]*/
    if (flag || !found) {
        flag = false;
        //Update Dtmp[] to Dset[] again so that backtrack.
        Copy(Dtmp, Dset, N);

        //Judge whether the distance of X[i] - (X[N] - Dmax) is in the set Dtmp[], i ∈ [1, left) 
        for (int i = 1; i < Left; i++) {
            if (!FindNum(Dtmp, N, abs(X[i] - (X[N] - Dmax)))) {
                flag = true;
                break;
            }
        }

        //Judge whether the distance of X[i] - (X[N] - Dmax) is in the set Dtmp[], i ∈ (right, N]
        for (int i = N; i > Right; i--) {
            if (!FindNum(Dtmp, N, abs(X[i] - (X[N] - Dmax)))) {
                flag = true;
                break;
            }
        }

        // if X[N] - Dmax can place in the set X[], recursive next level.
        if (!flag) {
            X[Left] = X[N] - Dmax;
            found = Place(X, Dtmp, N, Left + 1, Right);
        }
    }
    free(Dtmp);
    return found;
}

// Recursive procedure to find best move for computer.
// Best points to a number from 1 to 9 indicating square.
// Possible evaluations satisfy CompLoss < Draw < CompWin.
// Board is an array and thus can be changed by place.
// Default Board[] has 10 elements and Board[0] not use.
void FindCompMove(int Board[], int* BestMove, int* Value,  int Alpha, int Beta) {
    int Dc = -1, Response = -1;

    if (FullBoard(Board))
        *Value = Draw;
    else if (ImmediateWin(Board, BestMove, Comp))
        *Value = CompWin;
    else {
        *Value = Alpha;
        for (int pos = 1; pos <= 9 && *Value < Beta; pos++) {
            if (IsEmpty(Board, pos)) {
                Place1(Board, pos, Comp);
                FindHumanMove(Board, &Dc, &Response, *Value, Beta);
                UnPlace1(Board, pos); // Restore board

                if (Response > *Value) {
                    // Update best move
                    *Value = Response;
                    *BestMove = pos;
                }
            }
        }
    }
}


// Recursive procedure to find best move for computer.
// BestMove points to a number from 1 to 9 indicating square.
// Possible evaluations satisfy CompLoss < Draw < CompWin.
// Board is an array and thus can be changed by place.
// Default Board[] has 10 elements and Board[0] not use.
void FindHumanMove(int Board[], int* BestMove, int* Value, int Alpha, int Beta) {
    int Dc = -1, Response = -1;

    if (FullBoard(Board))
        *Value = Draw;
    else if (ImmediateWin(Board, BestMove, Human))
        *Value = CompWin;
    else {
        *Value = Beta;
        for (int pos = 1; pos <= 9 && *Value > Alpha; pos++) {
            if (IsEmpty(Board, pos)) {
                Place1(Board, pos, Human);
                FindHumanMove(Board, &Dc, &Response, Alpha, *Value);
                UnPlace1(Board, pos); // Restore board

                if (Response < *Value) {
                    // Update best move
                    *Value = Response;
                    *BestMove = pos;
                }
            }
        }
    }
}

static bool FullBoard(int Board[]) {
    for (int pos = 1; pos <= 9; pos++) {
        if (Board[pos] == Empty)
            return false;
    }
    return true;
}

static bool IsEmpty(int Board[], int pos) {
    if (Board[pos] == Empty) return true;
    return false;
}

static bool CanWin(int Board[], int state) {
    // check every row 
    for (int pos = 1; pos <= 7; pos += 3) {
        if (Board[pos] == state && Board[pos] == Board[pos + 1] &&
            Board[pos] == Board[pos + 2])
            return true;
    }
    // check every column
    for (int pos = 1; pos <= 3; pos++) {
        if (Board[pos] == state && Board[pos] == Board[pos + 3] &&
            Board[pos] == Board[pos + 6])
        return true;
    }
    // check every diagonals
    if (Board[1] == state && Board[5] == state && Board[9] == state)
        return true;
    if (Board[3] == state && Board[5] == state && Board[7] == state)
        return true;
    return false;
}

static bool ImmediateWin(int Board[], int* BestMove, int State) {
    bool win;
    for (int pos = 1; pos <= 9; pos++) {
        if (IsEmpty(Board, pos)) {
            Board[pos] = State;
            win = CanWin(Board, State);
            Board[pos] = Empty; // Backtraceing
            if (win) {
                *BestMove = pos;
                return true;
            }
        }
    }
    return false;
}

static void Place1(int Board[], int pos, int State) {
    Board[pos] = State;
}

static void UnPlace1(int Board[], int pos) {
    Board[pos] = Empty; 
}

static void Print(int Board[]) {
    int i;
    printf("----------------\n");
    for (i = 1; i <= 3; i++) printf("|%d", Board[i]);
    printf("|\n"); 

    printf("----------------\n");
    for (i = 4; i <= 6; i++) printf("|%d", Board[i]);
    printf("|\n"); 

    printf("----------------\n");
    for (i = 7; i <= 9; i++) printf("|%d", Board[i]);
    printf("|\n"); 
    printf("----------------\n");
}

void GameStart() {
    int Board[10] = {Empty};
    int first = ChooseFirstPlace();
    if (first == 10) CompPlace(Board);
    while (1) {
        Print(Board);
        if (HandleGameOver(Board)) break;
        HumanPlace(Board);
        Print(Board);
        if (HandleGameOver(Board)) break;
        CompPlace(Board);
    }

}

int ChooseFirstPlace() {
    int state;
    printf("Who will place first\n");
    printf("-2 : human first \n");
    printf("10 : computer first\n");
    scanf("%d",&state);
    return state;
}

void HumanPlace(int Board[]) {
    int pos = GetPlacePosition();
    Place1(Board, pos, Human);
    printf("Your choice:\n");
}

static int GetPlacePosition() {
    printf("It is your turn, please input where you want :\n");
    printf("Such as 1 ~ 9\n");
    int pos;
    scanf("%d",&pos);
    return pos;
}

void CompPlace(int Board[]) {
    int BestMove = GetBestMove(Board);
    Place1(Board, BestMove, Comp);
    printf("The Compute choice:\n");
}

static int GetBestMove(int Board[]) {
    int BestMove = 0, Value = 0;
    FindCompMove(Board,&BestMove, &Value, Human, Comp);
    return BestMove;
}

bool HandleGameOver(int Board[]) {
    bool draw = false;
    int WhoWin;
    if (GameOver(Board, &draw, &WhoWin)) {
        if (draw)
            printf("Draw!\n");
        else if (WhoWin == Comp)
            printf("You lose!\n");
        else if (WhoWin == Human)
            printf("Congratulate! You defeat the computer.\n");
        return true;
    }
    return false;
}

static bool GameOver(int Board[], bool* draw, int* Win) {
    if (CanWin(Board, Comp)) {
        *Win = Comp;
        *draw = false;
        return true;
    } else if (CanWin(Board, Human)) {
        *Win = Human;
        *draw = false;
        return true;
    } else if (FullBoard(Board)) {
        *draw = true;
        return true;
    }
    return false;
}