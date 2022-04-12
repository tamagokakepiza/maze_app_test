#include <stdio.h>

#define MAZE_ROW    5                         //迷路の行数
#define MAZE_COLUMN 5                         //迷路の列数

//迷路のーブロック
enum MazeKind {PATH, WALL, START, GOAL};      //ブロックの種類(道、壁、スタート、ゴール)
enum MazeFlag {FALSE, TRUE};                  //ブロックの判定
typedef struct {
  enum MazeKind kind;                         //種類(道、壁、スタート、ゴール)
  enum MazeFlag flag;                         //ブロックの判定
} MazeBlock;

//プレイヤー
typedef struct {
  int row;                                    //プレイヤー位置(行)
  int column;                                 //プレイヤー位置(列)
} MazePlayer;

//プレイヤーの初期化
int MazePlayerInit(int *playerRow, int *playerColumn, MazeBlock maze[MAZE_ROW][MAZE_COLUMN]) {
  int i, j;

  for(i = 0; i < MAZE_ROW; i++) {             //行
    for(j = 0; j < MAZE_COLUMN; j++) {        //列
      if(maze[i][j].kind == START) {          //スタート地点の場合
        *playerRow = i;
        *playerColumn = j;
        return 0;
      }
    }
  }

  printf("スタートがありません\n");               //スタート地点がない場合
  return -1;
}

//迷路表示
void MazeDraw(int playerRow, int playerColumn, MazeBlock maze[MAZE_ROW][MAZE_COLUMN]) {
  int i, j;
  for(i = 0; i < MAZE_ROW; i++) {             //行
    for(j = 0; j < MAZE_COLUMN; j++) {        //列
      if(playerRow == i && playerColumn == j) {
        printf("P");                          //プレイヤー位置
      } else if(maze[i][j].flag == FALSE) {   //ブロックが判明していない場合
        printf("?");
      } else {
        switch (maze[i][j].kind) {
        case WALL:
          printf("□");                        //壁
          break;
        case GOAL:
          printf("G");                        //ゴール
          break;
        default:
          printf(" ");                        //その他(スタート、道)
          break;
        }
      }
    }
    printf("\n");
  }
}

int main(void) {
  //迷路
  MazeBlock maze[MAZE_ROW][MAZE_COLUMN] = {
    { {START, TRUE } , {PATH , FALSE}, {PATH , FALSE}, {PATH , FALSE}, {PATH , FALSE} },
    { {WALL , FALSE} , {WALL , FALSE}, {PATH , FALSE}, {WALL , FALSE}, {WALL , FALSE} },
    { {WALL , FALSE} , {PATH , FALSE}, {PATH , FALSE}, {PATH , FALSE}, {PATH , FALSE} },
    { {PATH , FALSE} , {PATH , FALSE}, {WALL , FALSE}, {WALL , FALSE}, {WALL , FALSE} },
    { {WALL , FALSE} , {PATH , FALSE}, {PATH , FALSE}, {PATH , FALSE}, {GOAL , TRUE } },
  };

  //迷路表示
  MazeDraw(maze);

  return 0;
}