#ifndef _Backtrack_H
#define _Backtrack_H
#include <stdbool.h>

/*trunpike reconstruction problem*/
static int FindMax(int D[], int N);
static bool FindNum(int D[], int N, int Num);
static void Copy(int Dtmp[], int Dset[], int N);
int turnPike(int X[], int Dset[], int N);
static bool Place(int X[], int Dset[], int N, int Left,int Right);

/* tic tac toe by alpha beta pruning */
#define  CompLoss (-1)
#define Draw (0) 
#define CompWin (1)

#define Human (-2)
#define Comp (10)
#define Empty (0)
void FindCompMove(int Board[], int* BestMove, int* Value, int Alpha, int Beta);
void FindHumanMove(int Board[], int* BestMove, int* Value, int Alpha, int Beta);
static bool FullBoard(int Board[]);
static bool IsEmpty(int Board[], int pos);
static bool ImmediateWin(int Board[], int* BestMove, int State);
static bool CanWin(int Board[], int state);
static void Place1(int Board[], int pos, int State);
static void UnPlace1(int Board[], int pos);
static void Print(int Board[]);
void GameStart();
int ChooseFirstPlace();
void CompPlace(int Board[]);
static int GetBestMove(int Board[]);
void HumanPlace(int Board[]);
static int GetPlacePosition();
bool HandleGameOver(int Board[]);
static bool GameOver(int Board[], bool* draw, int* Win);
#endif