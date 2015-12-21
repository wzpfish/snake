#include "snake.h"
#include "frame.h"
#include <unistd.h>
#include <term.h>
#include <iostream>
#include <stdio.h>
#include <fcntl.h>

int kbhit(void)
{
    struct termios oldt, newt;
    int ch;
    int oldf;
  
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
  
    ch = getchar();
  
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);
  
    if(ch != EOF) {
        ungetc(ch, stdin);
        return 1;
    }
  
    return 0;
}

void ClearScreen() {
    if (!cur_term) {
        int result;
        setupterm(NULL, STDOUT_FILENO, &result);
        if (result <= 0) return;
    }

    putp( tigetstr( "clear" ) );
}

void Run() {
    Frame frame(30, 30);
    frame.init();
    while (true) {
        while (!kbhit()) {
            ClearScreen();
            frame.move();
            frame.display();
            usleep(500 * 1000);
        }

        char key = std::cin.get();
        frame.changeDir(key);
    }
}
int main() {
    Run();
    return 0;
}
