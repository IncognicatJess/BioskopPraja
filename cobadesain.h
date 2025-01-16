#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <conio.h>
#include <time.h>
#include <ctype.h>
#include <windows.h>
#include <unistd.h>

void gotoxy(int x, int y) {
    COORD c;
    c.X = x;
    c.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void drawBox(int x, int y, int width, int height) {
    // Buffer for each row of the box
    char buffer[width + 1];
    buffer[width] = '\0'; // Null-terminate the buffer

    for (int i = 0; i < height; i++) {
        // Reset the buffer for each row
        memset(buffer, ' ', width);

        if (i == 0 || i == height - 1) {
            // Top and bottom borders
            for (int j = 0; j < width; j++) {
                if (j == 0 || j == width - 1) {
                    buffer[j] = '+'; // Corners of the box
                } else {
                    buffer[j] = '-'; // Horizontal borders
                }
            }

            // Apply color and print the row
            gotoxy(x, y + i);
            printf("\033[48;2;239;90;111m\033[38;2;239;90;111m%s\033[0m", buffer);

        } else {
            // Middle rows
            buffer[0] = '|'; // Left border
            buffer[width - 1] = '|'; // Right border

            gotoxy(x, y + i);

            // Print the left border
            printf("\033[48;2;239;90;111m\033[38;2;239;90;111m%c", buffer[0]);

            // Print the interior (spaces)
            printf("\033[48;2;255;241;219m%-*s", width - 2, "");

            // Print the right border
            printf("\033[48;2;239;90;111m\033[38;2;239;90;111m%c\033[0m", buffer[width - 1]);
        }
    }

    // Reset color after drawing the box
}

void setFullscreen() {
    HWND hwnd = GetConsoleWindow();
    ShowWindow(hwnd, SW_MAXIMIZE);
}