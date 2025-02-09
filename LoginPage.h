#define FILENAME "./Database/Akun/DataAkun.dat"
#define FILEFILM "./Database/Film/DataFilm.dat"
#define PROFILDAT "./Database/Akun/DataProfil.dat"
#define FILEMENU "./Database/FNB/DataFnb.dat"
#define TEATERDAT "./Database/Teater/DataTeater.dat"
#define TEMP_FILEMENU "./Database/FNB/TempDataFnb.dat"
#define TEMP_FILEFILM "./Database/Film/TempDataFilm.dat"
#define SCHEDULEDAT "./Database/JadwalTayang/DataJadwalTayang.dat"
#define TEMP_SCHEDULEDAT "./Database/JadwalTayang/TempJadwalTayang.dat"
#define SEATDAT "./Database/Teater/DataKursi.dat"
#define TRANSCFILE "./Transaksi/Tiket.dat"


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
#include <math.h>

// LIBRARY EXTENDED


/*
// Fungsi untuk mengatur ukuran CMD ke 1366x720 dan mencegah resize
void setConsoleReso() {
    HWND hwnd = GetConsoleWindow(); // Dapatkan handle jendela CMD
    if (hwnd != NULL) {
        // Atur ukuran CMD ke 1366x720 di posisi (50,50) dari pojok kiri atas
        MoveWindow(hwnd, 50, 50, 1366, 720, TRUE);

        // Hilangkan fitur resize (drag), tombol maximize, dan border resize
        LONG style = GetWindowLong(hwnd, GWL_STYLE);
        style &= ~WS_SIZEBOX;   // Hilangkan fitur resize (drag)
        style &= ~WS_MAXIMIZEBOX; // Hilangkan tombol maximize
        SetWindowLong(hwnd, GWL_STYLE, style);

        // Terapkan perubahan
        SetWindowPos(hwnd, NULL, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_FRAMECHANGED);
    }
}

*/


// #include "CRUD/CRUD_Data_Akun/ReadAkun.h" // Untuk membaca akun dari file

void loginPage();
 //setConsoleReso(); // Atur ukuran CMD sebelum menampilkan login
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
    char IDFilm[10];
    char IDTeater[10];
    char judulFilm[50];
    int Teater;
    int durasi;
    TanggalTayang Tanggal;
    JamTayang jamTayang;
    JamTayangAkhir Berakhir;
    char status[20];
    double harga;
} ScheduleData;

typedef struct
{
    char IDTeater[10];
    int jumlahKursi;
    int baris;
    int kolom;
    char ID[10];
    char status[10]; // Status kursi, default "Tersedia"
} KursiData;

typedef struct
{
    int id;
    char nama[50];
    char metode[10];
    char konfir[15];
    char tanggal[15];
    double harga;
    int jumlah;
    float total;
} ListMakanan;


typedef struct
{
    int tanggal;
    int bulan;
    int tahun;
} TanggalTayangTransc;

typedef struct
{
    int jam;
    int menit;
} JamTayangTransc;

typedef struct
{
    int tanggal;
    int bulan;
    int tahun;
} TanggalTransc;

typedef struct
{
    char ID[10];
    char IDFilm[10];
    char IDTeater[10];
    char judulFilm[50];
    int Teater;
    char IDkursi[20][10];
    char kategori[10];
    char bentuk[10];
    TanggalTayangTransc Tanggal;
    JamTayangTransc jamTayang;
    int tiket;
    long no;
    // char status[20];
    double harga;
    double total;
    char metodePembayaran[10];
    double nominal;
    char catatan[1000];
    TanggalTransc tanggalTransc;
} Tiket;


// FUNGSI EXTENDED
#include "TampilkanJudul.h"
// #include "TampungID.h"
#include "TampilkanPesan.h"
#include "HidePassword.h"
#include "ReadNowShowing.h"
#include "TombolOpsi.h"
#include "TombolKonfirmasi.h"
#include "DashboardAdmin.h" // Dashboard admin
#include "DashboardKasirFnb.h"
#include "DashboardKasirTiket.h"
#include "Utility.h"
#include "Transaksi/RefreshKursi.h"


// Prototipe fungsi
bool validasiLogin(const char *username, const char *password, AkunData *akun);
void dashboardUser(AkunData *akun);
void loginPage();
void ResetKursiPerID();

// Fungsi utama
void loginPage()
{
    enable_ansi_support();
    setConsoleSize();
    system("cls"); // Membersihkan layar sebelum menampilkan tampilan login
    takeDrawBox();
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
    judul();
    
    char username[50], password[50];
    AkunData akun;
    int attempt = 3; // Jumlah percobaan login

    while (attempt > 0)
    {
        
        // Judul LOGIN
        gotoxy(30, 16);
        printf("\033[37;48;2;197;148;1m LOGIN\033[0m");

        gotoxy(30, 20);
        printf("\033[37;48;2;197;148;1m USERNAME : \033[0m");
        textBoxBordir(30, 21, 30, 2); // Kotak input username

        gotoxy(30, 24);
        printf("\033[37;48;2;197;148;1m PASSWORD : \033[0m");
        textBoxBordir(30, 25, 30, 2); // Kotak input password

        gotoxy(54, 29);
        printf("\033[37;48;2;197;148;1m login : \033[0m");
        textBoxBordir(53, 28, 7, 2); // Kotak login

        gotoxy(32, 22);
        printf("\033[30;48;2;197;148;1m"); // Set latar belakang coklat keemasan
        fgets(username, sizeof(username), stdin);
        username[strcspn(username, "\n")] = '\0'; // Hapus newline
        printf("\033[0m");                        // Reset warna setelah input

        gotoxy(32, 26);
        printf("\033[30;48;2;197;148;1m");  // Set latar belakang coklat keemasan
        HidePW(password, sizeof(password)); // Sembunyikan password
        printf("\033[0m");                  // Reset warna setelah input

        // Fokus ke kotak login
        gotoxy(55, 29);
        printf("\033[30;48;2;197;148;1m"); // Set latar belakang coklat keemasan
        char loginConfirm;
        loginConfirm = getch(); // Tunggu input dari pengguna (misalnya, Enter)
        printf("\033[0m");      // Reset warna setelah input

        // Jika pengguna menekan Enter di kotak login
        if (loginConfirm == 13) // 13 adalah kode ASCII untuk Enter
        {
            // Validasi login
            if (validasiLogin(username, password, &akun))
            {
                if (strlen(akun.ID) > 0)
                { // Cek apakah ID tidak kosong
                    if (strcmp(akun.akun, "Admin") == 0)
                    {
                        DashboardAdmin(&akun); // Buka dashboard admin
                    }
                    else
                    {
                        dashboardUser(&akun); // Buka dashboard user
                    }
                    return; // Keluar setelah login berhasil
                }
                else
                {
                    gotoxy(20, 25);
                    printf("\033[31mID tidak ditemukan.\033[0m"); // Pesan error merah
                    Sleep(2000);                                  // Tunggu 2 detik
                }
            }
            else
            {
                attempt--;
                char pesan[100];
                snprintf(pesan, sizeof(pesan), "\033[30;48;2;197;148;1mUsername atau password salah! %d percobaan tersisa.\033[0m", attempt);
                gotoxy(30, 55);
                printf("%s", pesan); // Tampilkan pesan error
                Sleep(2000);         // Tunggu 2 detik

                // Membersihkan area input username dan password
                gotoxy(32, 22);
                printf("\033[30;48;2;197;148;1m"); // Set latar belakang coklat keemasan
                for (int i = 0; i < sizeof(username); i++)
                {
                    printf(" "); // Mengisi dengan spasi untuk menghapus input sebelumnya
                }
                printf("\033[0m"); // Reset warna setelah input

                gotoxy(32, 26);
                printf("\033[30;48;2;197;148;1m"); // Set latar belakang coklat keemasan
                for (int i = 0; i < sizeof(password); i++)
                {
                    printf(" "); // Mengisi dengan spasi untuk menghapus input sebelumnya
                }
                printf("\033[0m"); // Reset warna setelah input
            }
        }
    }

    // Jika lebih dari 3 kali gagal
    gotoxy(20, 25);
    printf("\033[31mLogin gagal. Silakan coba lagi nanti.\033[0m");
    Sleep(2000); // Tunggu 2 detik sebelum keluar
    exit(0);     // Keluar dari program
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

void dashboardUser(AkunData *akun)
{
    system("cls");
    tampilkanJudul();

    if (strcmp(akun->jabatan, "Kasir Tiket") == 0)
    {
        printf("Selamat datang, %s (Kasir Tiket).\n", akun->username);
        DashboardUserTiket(akun);
    }
    else if (strcmp(akun->jabatan, "Kasir FNB") == 0)
    {
        printf("Selamat datang, %s (Kasir F&B).\n", akun->username);
        DashboardUserFnb(akun);
    }
    else
    {
        printf("Jabatan tidak dikenali.\n");
    }

    printf("Tekan Enter untuk keluar...");
    getchar();
    getchar();
}
