#define FILENAME "./Database/Akun/DataAkun.dat"
#define FILEFILM "./Database/Film/DataFilm.dat"
#define PROFILDAT "./Database/Akun/DataProfil.dat"
#define FILEMENU "./Database/FNB/DataFnb.dat"
#define TEATERDAT "./Database/Teater/DataTeater.dat"
#define TEMP_FILEMENU "./Database/FNB/TempDataFnb.dat"
#define TEMP_FILEFILM "./Database/Film/TempDataFilm.dat"
#define SCHEDULEDAT "./Database/JadwalTayang/DataJadwalTayang.dat"
#define TEMP_SCHEDULEDAT "./Database/JadwalTayang/TempJadwalTayang.dat"

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

void loginPage();

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
    char judul[50];
    char genre[20];
    int tahunRelease;
    double durasi;
    char studioFilm[20];
    char bentuk[10];
    double harga;
    char status[50];
} MovieData;

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

typedef struct
{
    int tanggal;
    int bulan;
    int tahun;
} TanggalTayang;

typedef struct
{
    int jam;
    int menit;
} JamTayang;

typedef struct
{
    int jam;
    int menit;
} JamTayangAkhir;


typedef struct {
    char ID[10];
    char judulFilm[50];
    int Teater;
    int durasi;
    TanggalTayang Tanggal;
    JamTayang jamTayang;
    JamTayangAkhir Berakhir;
    char status[20];
    double harga;
} ScheduleData;



// FUNGSI EXTENDED
#include "TampilkanJudul.h"
// #include "TampungID.h"
#include "TampilkanPesan.h"
#include "HidePassword.h"
#include "TombolOpsi.h"
#include "TombolKonfirmasi.h"
#include "DashboardKasirTiket.h"
#include "DashboardAdmin.h" // Dashboard admin
#include "cobadesain.h"
#include "Utility.h"

// Prototipe fungsi
bool validasiLogin(const char *username, const char *password, AkunData *akun);
void dashboardUser(const AkunData *akun);
void loginPage();

// Fungsi utama
void loginPage()
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
                    DashboardUser(&akun);
                }
                break; // Keluar setelah login berhasil
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

// void dashboardUser(const AkunData *akun)
// {
//     system("cls");
//     tampilkanJudul();
//     if (strcmp(akun->jabatan, "Kasir Tiket") == 0)
//     {
//         printf("Selamat datang, %s (Kasir Tiket).\n", akun->username);
//         printf("Fitur ini belum tersedia.\n");
//     }
//     else if (strcmp(akun->jabatan, "Kasir FNB") == 0)
//     {
//         printf("Selamat datang, %s (Kasir F&B).\n", akun->username);
//         printf("Fitur ini belum tersedia.\n");
//     }
//     else
//     {
//         printf("Jabatan tidak dikenali.\n");
//     }
//     printf("Tekan Enter untuk keluar...");
//     getchar();
//     getchar();
// }

// void tombolKeluar()
// {
//     system("cls");
//     drawBox(10, 5, 30, 5, " KELUAR PROGRAM ");
//     gotoxy(12, 11); // Tempatkan pesan di bawah tombol
//     printf("Tekan Enter untuk keluar...");
//     gotoxy(12, 12);
//     printf("Tekan ESC untuk kembali.");

//     char key = getch(); // Menunggu input tombol
//     if (key == '\r')
//     { // Enter
//         system("cls");
//         printf("Terima kasih telah menggunakan program ini.\n");
//         sleep(2);
//         exit(0);
//     }
//     else if (key == 27)
//     {           // ESC
//         return; // Kembali ke menu sebelumnya
//     }
// }
