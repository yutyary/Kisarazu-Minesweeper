#define MINE 3
#define MAP 8

#include <time.h>
#include <stdio.h>
#include <stdlib.h>

void Print_Map(char a[MAP+1][MAP+1]); //For Print the Map
void Print_Real_Map(char a[MAP][MAP]); //For Print the Real(Opend) Map
void Initialize_Real_Map(char a[MAP][MAP]); //Initialize the Real_Map
void Initialize_Print_Map(char a[MAP+1][MAP+1]); //Initialize the Print_Map
void Map_Search(int x, int y, char a[MAP][MAP]); //Count the arount Bom num
int Map_Update(int x, int y, char Print_Map[MAP+1][MAP+1], char Real_Map[MAP][MAP]); // Update the Map and Print
void Set_Bom(char a[MAP][MAP]); //Set the Bom
void Map_Rand(char a[MAP][MAP]); //Change Map for Bom
void Game_Over(char a[MAP][MAP]);
void Game_Clear(char a[MAP][MAP]);


void main(void) {
  srand(time(NULL));
  
  int x,y,select;
  int Opend_Map = 0;
  int Empty_Map = MAP * MAP - MINE;
  char R_Map[MAP][MAP];
  char P_Map[MAP+1][MAP+1];
  Initialize_Real_Map(R_Map);
  Initialize_Print_Map(P_Map);

  while(1) {
    Print_Map(P_Map);
    do {
      printf("Opend_Map = %d\n",Opend_Map);
      printf("x y:");
      scanf("%d %d",&x,&y);
      while(getchar() != '\n');
    } while(x > MAP || x < 0 || y > MAP || y < 0);

    select = Map_Update(x,y,P_Map,R_Map);
    Opend_Map++;
    
    if(select == 1) {
      printf("Map is Opend. Please re-select the Map.\n");
      Opend_Map--;
    }
    
    if(select == 2) {
      Game_Over(R_Map);
      break;
    }
    
    if(Opend_Map == Empty_Map) {
      Game_Clear(R_Map);
      break;
    }
  }
    
}

void Print_Map(char a[MAP+1][MAP+1]) {
  for(int y = 0;y < MAP + 1;y++) {
    for(int x = 0;x < MAP + 1;x++) {
      printf("%c ",a[x][y]);
    }
    printf("\n");
  }
}

void Print_Real_Map(char a[MAP][MAP]) {
  for(int y = 0;y < MAP - 1 + 1;y++) {
    for(int x = 0;x < MAP - 1 + 1;x++) {
      printf("%c ",a[x][y]);
    }
    printf("\n");
  }
}

void Initialize_Real_Map(char a[MAP][MAP]){
  int x,y;
  int mine = 0;
  
  for(x = 0; x < MAP; x++) {
    for(y = 0; y < MAP; y++) {
      a[x][y] = ' ';
    }
  }

  Set_Bom(a);
  Map_Rand(a);

  for(x = 0; x < MAP; x++) {
    for(y = 0; y < MAP; y++) {
      Map_Search(x,y,a);
    }
  }
}

void Initialize_Print_Map(char a[MAP+1][MAP+1]) {
  int i = 0;
  for(int y = 0;y < MAP+1; y++) {
    for(int x = 0;x < MAP+1; x++) {
      if(x == 0 && y == 0) a[x][y] = ' ';
      else if(y == 0) a[x][y] = '/' + x;
      else if(x == 0) a[x][y] = '/' + y;
      else a[x][y] = '.';
    }
  }
}

void Map_Search(int x, int y, char a[MAP][MAP]) {
  int mine = 0;

  if(a[x][y] == 'M') return;
  
  if(x > 0) {
    if(y > 0) if(a[x-1][y-1] == 'M') mine++;
    if(a[x-1][y] =='M') mine++;
    if(y < MAP) if(a[x-1][y+1] == 'M') mine++;
  }
  
  if(y > 0) if(a[x][y-1] == 'M') mine++;
  if(y < MAP) if(a[x][y+1] =='M') mine++;

  if(x < MAP) {
    if(y > 0) if(a[x+1][y-1] == 'M') mine++;
    if(a[x+1][y] == 'M') mine++;
    if(y < MAP) if(a[x+1][y+1] == 'M') mine++;
  }
  a[x][y] = mine + '0';
}    

int Map_Update(int x, int y, char Print_Map[MAP+1][MAP+1], char Real_Map[MAP][MAP]) {
  if(Print_Map[x+1][y+1] != '.') return 1;
  Print_Map[x+1][y+1] = Real_Map[x][y];
  if(Real_Map[x][y] == 'M') return 2; //Game Over
  return 0;
}

void Set_Bom(char a[MAP][MAP]) {
  int x,y;
  int mine = 0;

  y = 0;
  while(y < MAP && mine < MINE) {
    x = 0;
    while(x < MAP && mine < MINE) {
      a[x][y] = 'M';
      mine++;
      x++;
    }
    y++;
  }
}

void Map_Rand(char a[MAP][MAP]) {
  int x,y,change_x,change_y;
  char W;

  for(y = 0; y < MAP; y++) {
    for(x = 0; x < MAP; x++) {
      change_x = rand() % MAP;
      change_y = rand() % MAP;
      W = a[x][y];
      a[x][y] = a[change_x][change_y];
      a[change_x][change_y] = W;
    }
  }

}

void Game_Over(char a[MAP][MAP]) {
  printf("\n\nGame Over!\nMAP\n");
  Print_Real_Map(a);
}

void Game_Clear(char a[MAP][MAP]) {
  printf("\n\nGame Clear!\nMAP\n");
  Print_Real_Map(a);
}
