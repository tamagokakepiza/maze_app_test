#include <stdio.h>

#define MAZE_ROW    5                         //迷路の行数
#define MAZE_COLUMN 5                         //迷路の列数

//迷路のブロック
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

//メニュー
enum MazeMenu {STAGE0, EXIT};

//タイトル
int MazeTitle() {
  char buf[100];
  int menu = -1;

  printf("\n\n---迷路ゲーム---\n\n");
  printf("メニュー\n");
  printf("%d:ステージ0\n", STAGE0);
  printf("%d:終了\n", EXIT);
  printf("メニューを選んで数字を入力して下さい--");

  fgets(buf, sizeof(buf), stdin);
  sscanf(buf, "%d", &menu);

  while(menu < 0 || menu > EXIT) {
    printf("入力が不正です。再入力してください--");
    fgets(buf, sizeof(buf), stdin);
    sscanf(buf, "%d", &menu);
  }

  return menu;
}

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

//迷路の表示
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

//方向
enum MazeDirection{UP, DOWN, LEFT, RIGHT, Invalid};

//プレイヤーの移動
void MazePlayerMove(int *playerRow, int *playerColumn, MazeBlock maze[MAZE_ROW][MAZE_COLUMN]) {
  char buf[100];
  int direction = -1;

  printf("%d:上\n", UP);
  printf("%d:下\n", DOWN);
  printf("%d:左\n", LEFT);
  printf("%d:右\n", RIGHT);
  printf("数字を入力して下さい--");

  fgets(buf, sizeof(buf), stdin);
  sscanf(buf, "%d", &direction);

  while(direction < 0 || direction > (Invalid -1)) {
    printf("入力が不正です 再入力して下さい--");
    fgets(buf, sizeof(buf), stdin);
    scanf(buf, "%d", &direction);
  }

  switch(direction) {
    //上へ移動
    case UP:
      if(*playerRow - 1 >= 0) {
        maze[*playerRow - 1][*playerColumn].flag = TRUE;
        if(maze[*playerRow - 1][*playerColumn].kind != WALL) {
          *playerRow -= 1;
          printf("\n上に移動しました--\n");
        } else {
          printf("\n上には壁があります--\n");
        }
      } else {
        printf("\n範囲外です--\n");
      }
    break;

    //下へ移動
    case DOWN:
      if(*playerRow + 1 <= MAZE_ROW) {
        maze[*playerRow + 1][*playerColumn].flag = TRUE;
        if(maze[*playerRow + 1][*playerColumn].kind != WALL) {
          *playerRow += 1;
          printf("\n下に移動しました--\n");
        } else {
          printf("\n下には壁があります--\n");
        }
      } else {
        printf("\n範囲外です--\n");
      }
      break;

    //左へ移動
    case LEFT:
      if(*playerColumn - 1 >= 0) {
        maze[*playerRow][*playerColumn - 1].flag = TRUE;
        if(maze[*playerRow][*playerColumn - 1].kind != WALL) {
          *playerColumn -= 1;
          printf("\n左に移動しました--\n");
        } else {
          printf("\n左には壁があります--\n");
        }
      } else {
        printf("\n範囲外です--\n");
      }
      break;

    //右へ移動
    case RIGHT:
      if(*playerColumn + 1 <= MAZE_COLUMN) {
        maze[*playerRow][*playerColumn + 1].flag = TRUE;
        if(maze[*playerRow][*playerColumn + 1].kind != WALL) {
          *playerColumn += 1;
          printf("\n右に移動しました--\n");
        } else {
          printf("\n右には壁があります--\n");
        }
      } else {
        printf("\n範囲外です--\n");
      }
      break;
  }
}

//ゴールの判定
int MazeGoalCheck(int playerRow, int playerColumn, MazeBlock maze[MAZE_ROW][MAZE_COLUMN]) {
  if(maze [playerRow][playerColumn].kind == GOAL) {
    printf("ゴール！ステージクリアです--\n");
    return 1;
  }
  return 0;
}

//ゲーム
void MazeGame(void) {
  //迷路
  MazeBlock maze[MAZE_ROW][MAZE_COLUMN] = {
    { {START, TRUE } , {PATH , FALSE}, {PATH , FALSE}, {PATH , FALSE}, {PATH , FALSE} },
    { {WALL , FALSE} , {WALL , FALSE}, {PATH , FALSE}, {WALL , FALSE}, {WALL , FALSE} },
    { {WALL , FALSE} , {PATH , FALSE}, {PATH , FALSE}, {PATH , FALSE}, {PATH , FALSE} },
    { {PATH , FALSE} , {PATH , FALSE}, {WALL , FALSE}, {WALL , FALSE}, {WALL , FALSE} },
    { {WALL , FALSE} , {PATH , FALSE}, {PATH , FALSE}, {PATH , FALSE}, {GOAL , TRUE } },
  };

  //プレイヤー
  MazePlayer player;

  //プレイヤーの初期化
  if(MazePlayerInit(&player.row, &player.column, maze) == -1) {
    return;
  }


  //ゲームプレイ
  while(MazeGoalCheck(player.row, player.column, maze) != 1) {
    //迷路の表示
    MazeDraw(player.row, player.column, maze);
    //プレイヤーの移動
    MazePlayerMove(&player.row, &player.column, maze);
  }
  
  //ステージの結果表示
  MazeDraw(player.row, player.column, maze);
}

int main(void) {
  int menu;

  while(1) {
    //メニュー
    menu = MazeTitle();
    printf("\n");

    //ゲーム終了
    if(menu == EXIT) {
      break;
    }

    //ゲーム
    MazeGame();
  }

  return 0;
}