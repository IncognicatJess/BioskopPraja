#define FILENAME "./Database/Akun/DataAkun.dat"
#define FILEFILM "./Database/Film/DataFilm.dat"

// LIBRARY STANDARD
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <conio.h>
#include <unistd.h>
#include <string.h>
#include <windows.h>

//#include "CRUD/CRUD_Data_Akun/ReadAkun.h" // Untuk membaca akun dari file

// Struct AkunData untuk validasi login
typedef struct {
    char ID[10];
    char akun[20];
    char username[50];
    char sandi[50];
    char jabatan[20];
    char status[50];
} AkunData;

//Struct Untuk menampung data ke dashboard sesuai akun
typedef struct {
    char ID[10];
    char username[50];
    char jabatan[20];
} ProfilData;


//FUNGSI EXTENDED
#include "TampilkanJudul.h"
#include "TampungID.h"
#include "TampilkanPesan.h"
#include "HidePassword.h"
#include "TombolOpsi.h"
#include "DashboardAdmin.h" // Dashboard admin




// Prototipe fungsi
bool validasiLogin(const char *username, const char *password, AkunData *akun);
void dashboardUser(const AkunData *akun);

// Fungsi utama
int main() {
    char username[50], password[50];
    AkunData akun;
    ProfilData profil;
    int attempt = 3; // Jumlah percobaan login

    while (attempt > 0) {
        system("cls");
        tampilkanJudul();

        // Input username
        printf("Username: ");
        scanf("%s", username);

        // Input password
        printf("Password: ");

        //Fungsi menyembunyikan Password
       HidePW(password, sizeof(password));

        // Validasi login
        if (validasiLogin(username, password, &akun)) {
            profil = validasiID(username, password); // Simpan profil yang dikembalikan
            if (strlen(profil.ID) > 0) { // Cek apakah ID tidak kosong
                if (strcmp(akun.akun, "Admin") == 0) {
                    DashboardAdmin(profil); // Kirim profil ke DashboardAdmin
                } else {
                    dashboardUser (&akun);
                }
                return 0; // Keluar setelah login berhasil
            } else {
                printf("ID tidak ditemukan.\n");
            }
        } else {
            attempt--;
            char pesan[100];
            snprintf(pesan, sizeof(pesan), "Username atau password salah! %d percobaan tersisa.", attempt);
            TampilkanPesan(pesan, 2);
        }
    }

    //Jika lebih dari 3 kali
    printf("Login gagal. Silakan coba lagi nanti.\n");
    return 0;
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

