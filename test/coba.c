#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <windows.h>

// Fungsi untuk mengatur posisi teks di layar
void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// Fungsi untuk mengatur warna teks
void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

// Fungsi untuk membuat kotak
void drawBox(int x1, int y1, int x2, int y2) {
    setColor(11); // Warna biru muda untuk kotak
    for (int i = x1; i <= x2; i++) {
        gotoxy(i, y1);
        printf("%c", (i == x1 || i == x2) ? '+' : '-');
        gotoxy(i, y2);
        printf("%c", (i == x1 || i == x2) ? '+' : '-');
    }

    for (int i = y1 + 1; i < y2; i++) {
        gotoxy(x1, i);
        printf("|");
        gotoxy(x2, i);
        printf("|");
    }
    setColor(15); // Kembali ke warna default
}

// Fungsi untuk fullscreen
void setFullscreen() {
    keybd_event(VK_MENU, 0x38, 0, 0); // ALT Key Down
    keybd_event(VK_RETURN, 0x1C, 0, 0); // Enter Key Down
    keybd_event(VK_RETURN, 0x1C, KEYEVENTF_KEYUP, 0); // Enter Key Up
    keybd_event(VK_MENU, 0x38, KEYEVENTF_KEYUP, 0); // ALT Key Up
}

// Fungsi login page
void loginPage() {
    char username[30], password[30];
    char storedUsername[] = "admin";
    char storedPassword[] = "12345";

    int attempt = 0;
    int loggedIn = 0;

    while (attempt < 3 && !loggedIn) {
        system("cls"); // Membersihkan layar
        drawBox(5, 3, 115, 25); // Kotak besar keseluruhan

        // Garis pembagi sisi kiri dan kanan
        setColor(14); // Warna kuning untuk garis pembagi
        for (int i = 4; i < 25; i++) {
            gotoxy(45, i);
            printf("|");
        }

        // Judul Program di sisi kiri
        setColor(10); // Warna hijau untuk teks judul
        gotoxy(12, 6);
        printf("==== PROGRAM BIOSKOP PRAJA ====");
        gotoxy(12, 8);
        printf("Selamat datang di sistem kami!");
        gotoxy(12, 10);
        printf("Silakan login untuk melanjutkan.");

        // Input login di sisi kanan
        setColor(14); // Warna kuning untuk teks login
        gotoxy(55, 6);
        printf("==== LOGIN PAGE ====");
        setColor(15); // Kembali ke warna default
        gotoxy(50, 9);
        printf("Username: ");
        gotoxy(62, 9);
        scanf("%s", username);

        gotoxy(50, 11);
        printf("Password: ");
        gotoxy(62, 11);

        // Sembunyikan password dengan *
        int i = 0;
        while (1) {
            char ch = getch();
            if (ch == 13) { // Enter
                password[i] = '\0';
                break;
            } else if (ch == 8 && i > 0) { // Backspace
                printf("\b \b");
                i--;
            } else if (ch != 8) { // Karakter lain
                password[i++] = ch;
                printf("*");
            }
        }

        // Validasi login
        if (strcmp(username, storedUsername) == 0 && strcmp(password, storedPassword) == 0) {
            loggedIn = 1;
        } else {
            setColor(12); // Warna merah untuk pesan gagal
            gotoxy(50, 14);
            printf("Login gagal. Coba lagi.");
            setColor(15); // Kembali ke warna default
            attempt++;
            getch(); // Tunggu sebelum ulang
        }

        // Tombol keluar program
        setColor(14); // Warna kuning untuk tombol keluar
        gotoxy(50, 20);
        printf("Tekan 'Q' untuk keluar atau tunggu login.");
        if (getch() == 'Q' || getch() == 'q') {
            exit(0);
        }
    }

    // Layar setelah login
    system("cls");
    drawBox(20, 8, 100, 18);
    if (loggedIn) {
        setColor(10); // Warna hijau untuk pesan sukses
        gotoxy(40, 12);
        printf("Login berhasil! Selamat datang, %s.", username);
    } else {
        setColor(12); // Warna merah untuk pesan gagal
        gotoxy(40, 12);
        printf("Anda telah mencoba terlalu banyak. Akses ditolak.");
    }

    setColor(15); // Kembali ke warna default
    gotoxy(40, 14);
    printf("Tekan tombol apa saja untuk keluar...");
    getch();
}

int main() {
    setFullscreen(); // Auto fullscreen
    loginPage();
    return 0;
}
