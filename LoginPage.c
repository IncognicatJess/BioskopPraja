#define FILENAME "./Database/Akun/DataAkun.dat"


// LIBRARY STANDARD
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <conio.h>
#include <unistd.h>
//#include "CRUD/CRUD_Data_Akun/ReadAkun.h" // Untuk membaca akun dari file
#include "TampilkanPesan.h"
#include "DashboardAdmin.h" // Dashboard admin

//FUNGSI EXTENDED

// Struct AkunData untuk validasi login
typedef struct {
    char ID[10];
    char akun[20];
    char username[50];
    char sandi[50];
    char jabatan[20];
    char status[50];
} AkunData;

// Prototipe fungsi
void tampilkanJudul();
bool validasiLogin(const char *username, const char *password, AkunData *akun);
void dashboardUser(const AkunData *akun);

// Fungsi utama
int main() {
    char username[50], password[50];
    AkunData akun;
    int attempt = 3; // Jumlah percobaan login

    while (attempt > 0) {
        system("cls");
        tampilkanJudul();

        // Input username
        printf("Username: ");
        scanf("%s", username);

        // Input password
        printf("Password: ");
        int i = 0;
        char ch;
        while ((ch = getch()) != '\r') { // Mask password input
            if (ch == '\b' && i > 0) {
                printf("\b \b");
                i--;
            } else if (ch != '\b' && i < sizeof(password) - 1) {
                password[i++] = ch;
                printf("*");
            }
        }
        password[i] = '\0';
        printf("\n");

        // Validasi login
        if (validasiLogin(username, password, &akun)) {
            if (strcmp(akun.akun, "Admin") == 0) {
                DashboardAdmin();
            } else {
                dashboardUser(&akun);
            }
            return 0; // Keluar setelah login berhasil
        } else {
            attempt--;
            char pesan[100];
            snprintf(pesan, sizeof(pesan), "Username atau password salah! %d percobaan tersisa.", attempt);
            TampilkanPesan(pesan, 2);
        }
    }

    printf("Login gagal. Silakan coba lagi nanti.\n");
    return 0;
}

// Fungsi menampilkan judul aplikasi
void tampilkanJudul() {
    printf("\n========================\n");
    printf("  BIOSKOP PRAJA\n");
    printf("  Sistem Pemesanan Tiket dan F&B\n");
    printf("========================\n\n");
}

// Fungsi validasi login
bool validasiLogin(const char *username, const char *password, AkunData *akun) {
    FILE *file = fopen(FILENAME, "rb");
    if (!file) {
        printf("Gagal membuka file database.\n");
        return false;
    }

    while (fread(akun, sizeof(AkunData), 1, file)) {
        if (strcmp(akun->username, username) == 0 && strcmp(akun->sandi, password) == 0) {
            fclose(file);
            return true;
        }
    }

    fclose(file);
    return false;
}

// Fungsi menampilkan dashboard user (dummy)
void dashboardUser(const AkunData *akun) {
    system("cls");
    tampilkanJudul();
    if (strcmp(akun->jabatan, "Kasir Tiket") == 0) {
        printf("Selamat datang, %s (Kasir Tiket).\n", akun->username);
        printf("Fitur ini belum tersedia.\n");
    } else if (strcmp(akun->jabatan, "Kasir FNB") == 0) {
        printf("Selamat datang, %s (Kasir F&B).\n", akun->username);
        printf("Fitur ini belum tersedia.\n");
    } else {
        printf("Jabatan tidak dikenali.\n");
    }
    printf("Tekan Enter untuk keluar...");
    getchar();
    getchar();
}

