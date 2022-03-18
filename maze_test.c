#include <stdio.h>

//迷路のーブロック
enum MazeKind {PATH, WALL, START, GOAL};    //ブロックの種類(道、壁、スタート、ゴール)
enum MazeFlag {FALSE, TRUE};                //ブロックが判明しているかどうか

typedef struct
{
  enum MazeKind kind;                       //種類(道、壁、スタート、ゴール)
  enum MazeFlag flag;                       //ブロックが判明しているかどうか
} MazeBlock;

//迷路
#define MAZE_ROW    5                       //迷路の行数
#define MAZE_COLUMN 5                       //迷路の列数

  MazeBlock maze[MAZE_ROW][MAZE_COLUMN] = 
    {
      { {START, TRUE } , {PATH , FALSE}, {PATH , FALSE}, {PATH , FALSE}, {PATH , FALSE} },
      { {WALL , FALSE} , {WALL , FALSE}, {PATH , FALSE}, {WALL , FALSE}, {WALL , FALSE} },
      { {WALL , FALSE} , {PATH , FALSE}, {PATH , FALSE}, {PATH , FALSE}, {PATH , FALSE} },
      { {PATH , FALSE} , {PATH , FALSE}, {WALL , FALSE}, {WALL , FALSE}, {WALL , FALSE} },
      { {WALL , FALSE} , {PATH , FALSE}, {PATH , FALSE}, {PATH , FALSE}, {GOAL , TRUE } },
    };
