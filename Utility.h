void cariFilmByIDOrJudul(const char *keyword)
{
    FILE *file = fopen(FILEFILM, "rb");
    if (!file)
    {
        printf("Gagal membuka file database film.\n");
        return;
    }

    MovieData film;
    bool found = false;

    printf("\nHasil Pencarian:\n");
    printf("==============================================\n");
    printf("| %-8s | %-20s | %-10s |\n", "ID", "Judul", "Genre");
    printf("==============================================\n");

    while (fread(&film, sizeof(MovieData), 1, file))
    {
        if (strstr(film.ID, keyword) != NULL || strstr(film.judul, keyword) != NULL)
        {
            printf("| %-8s | %-20s | %-10s |\n", film.ID, film.judul, film.genre);
            found = true;
        }
    }

    if (!found)
    {
        printf("| %-8s | %-20s | %-10s |\n", "Tidak", "Ditemukan", " ");
    }

    printf("==============================================\n");
    fclose(file);
}

void cariMenuByID(const char *keyword)
{
    FILE *file = fopen(FILEMENU, "rb");
    if (!file)
    {
        printf("Gagal membuka file database film.\n");
        return;
    }

    FnbData menu;
    bool found = false;

    printf("\nHasil Pencarian:\n");
    printf("===========================================================\n");
    printf("| %-8s | %-20s | %-8s | %-10s |\n", "ID", "Nama Menu", "Stok", "Harga");
    printf("===========================================================\n");

    while (fread(&menu, sizeof(FnbData), 1, file))
    {
        if (strstr(menu.ID, keyword) != NULL || strstr(menu.namaMakanan, keyword) != NULL)
        {
            printf("| %-8s | %-20s | %-8d | %-10.0f |\n", menu.ID, menu.namaMakanan, menu.stok, menu.harga);
            found = true;
        }
    }

    if (!found)
    {
        printf("| %-8s | %-20s | %-10s |\n", "Tidak", "Ditemukan", " ");
    }

    printf("===========================================================\n");
    fclose(file);
}

#ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING
#define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004
#endif

void enable_ansi_support()
{
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;

    // Check if the handle is valid
    if (hOut == INVALID_HANDLE_VALUE)
    {
        fprintf(stderr, "Invalid handle\n");
        return;
    }

    // Get the current console mode
    if (!GetConsoleMode(hOut, &dwMode))
    {
        fprintf(stderr, "Failed to get console mode\n");
        return;
    }

    // Enable ANSI escape sequence processing
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    if (!SetConsoleMode(hOut, dwMode))
    {
        fprintf(stderr, "Failed to set console mode\n");
    }
}

#ifdef _WIN32
#include <windows.h>
#endif

void setConsoleSize()
{
#ifdef _WIN32
    // Dapatkan handle ke konsol
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut == INVALID_HANDLE_VALUE)
    {
        return;
    }

    // Dapatkan ukuran layar
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hOut, &csbi);

    // Atur ukuran konsol berdasarkan ukuran layar
    int width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    int height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

    SMALL_RECT windowSize = {0, 0, width - 1, height - 1};
    SetConsoleWindowInfo(hOut, TRUE, &windowSize);

    COORD bufferSize = {width, height};
    SetConsoleScreenBufferSize(hOut, bufferSize);
#else
    // Di Linux, Anda bisa menggunakan escape sequence untuk mengatur ukuran terminal
    printf("\033[8;%d;%dt", 30, 120); // Sesuaikan dengan ukuran yang diinginkan
#endif
}

void setFullscreen()
{
    HWND hwnd = GetConsoleWindow();
    ShowWindow(hwnd, SW_MAXIMIZE);
}

void setConsoleColor(int textColor)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), textColor);
}

int getTerminalWidth()
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if (GetConsoleScreenBufferInfo(hConsole, &csbi))
    {
        return csbi.srWindow.Right - csbi.srWindow.Left + 1;
    }
    return 80; // Default width
}

// Function to get the height of the terminal
int getTerminalHeight()
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if (GetConsoleScreenBufferInfo(hConsole, &csbi))
    {
        return csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    }
    return 25; // Default height
}

void drawBox(int x, int y, int width, int height)
{
    char line[width + 1]; // Buffer untuk satu baris kotak (termasuk null terminator)

    // Baris atas dan bawah
    memset(line, ' ', width);
    line[0] = ' ';         // Simbol pojok atau tepi (dapat disesuaikan)
    line[width - 1] = ' '; // Simbol pojok atau tepi (dapat disesuaikan)
    line[width] = '\0';    // Null terminator

    for (int i = 0; i < height; i++)
    {
        gotoxy(x, y + i);
        if (i == 0 || i == height - 1)
        {
            printf("\033[48;2;197;148;1m%s\033[0m", line); // Cetak baris tepi dengan warna
        }
        else
        {
            memset(line + 1, ' ', width - 2); // Isi tengah baris dengan spasi
            printf("\033[48;2;197;148;1m%c%s%c\033[0m", ' ', line + 1, ' ');
        }
    }
}

void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void takeDrawBox()
{
    enable_ansi_support();
    system("cls");
    setFullscreen();

    int width = getTerminalWidth();
    int height = getTerminalHeight();

    // Background kiri
    for (int i = 0; i < height; i++)
    {
        gotoxy(0, i);
        printf("\033[48;2;197;148;1m%*s\033[0m", width / 2, " "); // warna coklat keemasan
    }

    // Background kanan
    for (int i = 0; i < height; i++)
    {
        gotoxy(width / 2, i);
        printf("\033[48;2;217;217;217m%*s\033[0m", width / 2, " "); // warna abu abu
    }
}
void takeDrawBoxDashboard()
{
    enable_ansi_support();
    system("cls");
    setFullscreen();

    int width = getTerminalWidth();
    int height = getTerminalHeight();

    // Background kiri
    for (int i = 0; i < height; i++)
    {
        gotoxy(0, i);
        printf("\033[48;2;197;148;1m%*s\033[0m", width / 5, " "); // warna coklat keemasan
    }

    // Background kanan
    for (int i = 0; i < height; i++)
    {
        gotoxy(width / 4 - 11, i);
        printf("\033[48;2;217;217;217m%*s\033[0m", width * 3 / 4 + 12, " "); // warna abu abu
    }
}

void textBoxBordir(int x, int y, int width, int height)
{
    int i;
    int lineWidth = 20;

    gotoxy(x, y);
    printf("\033[37;48;2;197;148;1m%c\033[0m", 201); // Warna teks hitam, latar belakang coklat keemasan
    for (i = 1; i <= width; i++)
    {
        printf("\033[37;48;2;197;148;1m%c\033[0m", 205);
    }
    printf("\033[37;48;2;197;148;1m%c\033[0m", 187);

    for (i = 1; i <= height; i++)
    {
        gotoxy(x, y + i);
        printf("\033[37;48;2;197;148;1m%c\033[0m", 186);
        gotoxy(x + width + 1, y + i);
        printf("\033[37;48;2;197;148;1m%c\033[0m", 186);
    }

    printf("\n");
    gotoxy(x, y + height);
    printf("\033[37;48;2;197;148;1m%c\033[0m", 200);
    for (i = 1; i <= width; i++)
    {
        printf("\033[37;48;2;197;148;1m%c\033[0m", 205);
    }
    printf("\033[37;48;2;197;148;1m%c\033[0m", 188);
}

void judul()
{
    setConsoleColor(0);
    FILE *file = fopen("nama.txt", "r"); // Membuka file dalam mode baca (read)
    FILE *file1 = fopen("nama1.txt", "r");

    if (file == NULL || file1 == NULL)
    {
        printf("Error: File tidak ditemukan!\n");
        return;
    }

    char buffer[256]; // Buffer untuk menyimpan isi setiap baris
    int baris = 20;   // Mulai dari baris ke-5
    int baris1 = 25;  // Mulai dari baris ke-5
    int terminalWidth = getTerminalWidth();

    while (fgets(buffer, sizeof(buffer), file))
    {                         // Membaca file baris per baris
        gotoxy(122, baris++); // Geser kursor ke posisi tengah dan ke baris berikutnya
        printf("\033[48;2;217;217;217m%s", buffer);
    }

    while (fgets(buffer, sizeof(buffer), file1))
    {                          // Membaca file baris per baris
        gotoxy(122, baris1++); // Geser kursor ke posisi tengah dan ke baris berikutnya
        printf("\033[48;2;217;217;217m%s", buffer);
    }

    fclose(file);
}

// Fungsi untuk membersihkan area tertentu di layar
void clearArea(int x, int y, int width, int height)
{
    for (int i = 0; i < height; i++)
    {
        gotoxy(x, y + i);
        for (int j = 0; j < width; j++)
        {
            printf(" ");
        }
    }
}