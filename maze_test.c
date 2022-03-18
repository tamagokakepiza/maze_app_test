#include <stdio.h>

//迷路のーブロック
enum MazeKind {PATH, WALL, START, GOAL};    //ブロックの種類(道、壁、スタート、ゴール)
enum MazeFlag {FALSE, TRUE};                //ブロックが判明しているかどうか

typedef struct
{
  enum MazeKind kind;                       //種類(道、壁、スタート、ゴール)
  enum MazeFlag flag;                       //ブロックが判明しているかどうか
} MazeBlock;
