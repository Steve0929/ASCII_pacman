#include <conio.h>
#include <stdbool.h>
#include <windows.h>
#include <stdio.h>
#define DELAY 100

char *pacman_right[] = {
    " .--.",
    "/ _.-'",
    "|  '-.",
    " '--'"
};


char *pacman_right_closed[] = {
     " .--.",
     "/ ___'",
     "|    .",
     " '--'"
};

char *pacman_left[]={
     " .--.",
     "'-._ \\",
     ".-'  |",
     " '--'"
};

char *pacman_left_closed[]={
     " .--.",
     "'___ \\",
     ".    |",
     " '--'"
};

char *pacman_up[]={
      " .   .",
      "/ \\ / \\",
      "|  _  |",
      " '---'",
};

char *pacman_up_closed[]={
     " .   .",
     "/  |  \\",
     "|  '  |",
     " '---'"
};

char *pacman_down[]={
      " .---.",
      "|  -  |",
      "\\ / \\ /",
      " '   '",
};

char *pacman_down_closed[]={
      " .---.",
      "|  '  |",
      "\\  |  /",
      " '   '",
};

void gotoxy(int x, int y) {
    COORD coord = {x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void printSprite(int x, int y, char *sprite[]){
  for (int i = 0; i < sizeof(sprite); i++)
    {
        printf(sprite[i]);
        gotoxy(x, y + i +1);
    }
  gotoxy(x, y);
}


void clrscr() {
    COORD coordScreen = { 0, 0 };
    DWORD cCharsWritten;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD dwConSize;

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    GetConsoleScreenBufferInfo(hConsole, &csbi);
    dwConSize = csbi.dwSize.X * csbi.dwSize.Y;

    FillConsoleOutputCharacter(hConsole, (TCHAR) ' ', dwConSize, coordScreen, &cCharsWritten);

    SetConsoleCursorPosition(hConsole, coordScreen);
}


typedef struct {
    int x;
    int y;
    int direction;
    bool mouth_open;
} Pacman;

void draw_pacman(Pacman *pacman) {
    gotoxy(pacman->x, pacman->y);
    if(pacman->mouth_open){
        //Up direction
        if(pacman->direction == 0){
            printSprite(pacman->x, pacman->y, pacman_up);  
         }
        //Right direction
        else if(pacman->direction == 1){
            printSprite(pacman->x, pacman->y, pacman_right);  
        }
        //lef direction
        else if(pacman->direction == 3){
            printSprite(pacman->x, pacman->y, pacman_left);
        }
        //Down direction
        else if(pacman->direction == 2){
            printSprite(pacman->x, pacman->y, pacman_down);
        }
    }
    else{
        //Up direction
        if(pacman->direction == 0){
            printSprite(pacman->x, pacman->y, pacman_up_closed);  
         }
        //Right direction
        else if(pacman->direction == 1){
            printSprite(pacman->x, pacman->y, pacman_right_closed);  
        }
        //lef direction
        else if(pacman->direction == 3){
            printSprite(pacman->x, pacman->y, pacman_left_closed);
        }
        //Down direction
        else if(pacman->direction == 2){
            printSprite(pacman->x, pacman->y, pacman_down_closed);
        }
    }
}

int main() {
    HANDLE console_handle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursor_info;
    cursor_info.dwSize = 1;
    cursor_info.bVisible = false;
    SetConsoleCursorInfo(console_handle, &cursor_info);

    Pacman pacman = {0, 0, 0, false};

    while (true) {
       
        if (kbhit()) {  
            switch (getch()) { 
                case 72:
                    pacman.direction = 0;
                    pacman.y--;
                    break;
                case 77: 
                    pacman.direction = 1;
                    pacman.x++;
                    break;
                case 80:
                    pacman.direction = 2;
                    pacman.y++;
                    break;
                case 75:
                    pacman.direction = 3;
                    pacman.x--;
                    break;
                case 27:
                    return 0;
            }
        }

        pacman.mouth_open = !pacman.mouth_open;
        
        clrscr();
        draw_pacman(&pacman);

        Sleep(DELAY);
    }

    return 0;
}
