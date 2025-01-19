#define FILENAME "./Database/Akun/DataAkun.dat"
#define FILEFILM "./Database/Film/DataFilm.dat"
#define PROFILDAT "./Database/Akun/DataProfil.dat"
#define FILEMENU "./Database/FNB/DataFnb.dat"
#define TEATERDAT "./Database/Teater/DataTeater.dat"
#define TEMP_FILEMENU "./Database/FNB/TempDataFnb.dat"
#define TEMP_FILEFILM "./Database/Film/TempDataFilm.dat"



// LIBRARY STANDARD
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <conio.h>
#include <unistd.h>
#include <string.h>
#include <windows.h>
#include <ctype.h>
#include <time.h>

// #include "CRUD/CRUD_Data_Akun/ReadAkun.h" // Untuk membaca akun dari file

// Struct AkunData untuk validasi login
typedef struct
{
    char ID[10];
    char akun[20];
    char username[50];
    char sandi[50];
    char jabatan[20];
    char status[50];
} AkunData;

typedef struct
{
    char tempat[50];
    int tanggal;
    int bulan;
    int tahun;
} TempatTanggalLahir;

// Struct Untuk menampung data ke dashboard sesuai akun
typedef struct
{
    char ID[10];
    char nama[50];
    TempatTanggalLahir TTL;
    char noHP[13];
} ProfilData;

typedef struct
{
    char ID[10];
    int noTeater;
    char kategoriTheater[20];
    int jumlahKursi;
    char status[20];
    double harga;
} TeaterData;

typedef struct
{
    char ID[10];
    char namaMakanan[50];
    char kategori[10];
    int stok;
    double harga;
} FnbData;

// FUNGSI EXTENDED
#include "TampilkanJudul.h"
// #include "TampungID.h"
#include "TampilkanPesan.h"
#include "HidePassword.h"
#include "TombolOpsi.h"
#include "TombolKonfirmasi.h"
#include "DashboardAdmin.h" // Dashboard admin
#include "cobadesain.h"

// Prototipe fungsi
bool validasiLogin(const char *username, const char *password, AkunData *akun);
void dashboardUser(const AkunData *akun);
void loginPage();

// Fungsi utama
int main()
{
    char username[50], password[50];
    AkunData akun;
    ProfilData profil;
    int attempt = 3; // Jumlah percobaan login

    while (attempt > 0)
    {
        system("cls");
        tampilkanJudul();

        // Input username
        printf("Username: ");
        scanf("%s", username);

        // Input password
        printf("Password: ");

        // Fungsi menyembunyikan Password
        HidePW(password, sizeof(password));

        // Validasi login
        if (validasiLogin(username, password, &akun))
        {
            // profil = validasiID(username, password); // Simpan profil yang dikembalikan
            if (strlen(akun.ID) > 0)
            { // Cek apakah ID tidak kosong
                if (strcmp(akun.akun, "Admin") == 0)
                {
                    DashboardAdmin(&akun); // Kirim profil ke DashboardAdmin
                }
                else
                {
                    // DashboardUser(&akun); // Kirim profil ke DashboardKasirTiket
                }
                return 0; // Keluar setelah login berhasil
            }
            else
            {
                printf("ID tidak ditemukan.\n");
            }
        }
        else
        {
            attempt--;
            char pesan[100];
            snprintf(pesan, sizeof(pesan), "Username atau password salah! %d percobaan tersisa.", attempt);
            TampilkanPesan(pesan, 2);
        }
    }

    // Jika lebih dari 3 kali
    printf("Login gagal. Silakan coba lagi nanti.\n");
    return 0;
}

// Fungsi validasi login
bool validasiLogin(const char *username, const char *password, AkunData *akun)
{
    FILE *file = fopen(FILENAME, "rb");
    if (!file)
    {
        printf("Gagal membuka file database.\n");
        return false;
    }

    while (fread(akun, sizeof(AkunData), 1, file))
    {
        if (strcmp(akun->username, username) == 0 && strcmp(akun->sandi, password) == 0)
        {

            fclose(file);
            return true;
        }
    }

    fclose(file);
    return false;
}
