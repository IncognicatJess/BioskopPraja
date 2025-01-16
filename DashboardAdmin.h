
// LIBRARY STANDAR
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <conio.h>
#include <time.h>
#include <ctype.h>
#include <windows.h>
#include <unistd.h>

// CRUD DATA AKUN
#include "CRUD/CRUD_Data_Akun/ReadAkun.h"
#include "CRUD/CRUD_Data_Akun/CreateAkun.h"
#include "CRUD/CRUD_Data_Akun/UpdateAkun.h"
#include "CRUD/CRUD_Data_Akun/DeleteAkun.h"

// CRU DATA PROFILE
#include "CRUD/CRU_Data_Profile/CreateProfile.h"
#include "CRUD/CRU_Data_Profile/ReadProfile.h"

// CRUD DATA FILM
#include "CRUD/CRUD_Data_Film/ReadFilm.h"
#include "CRUD/CRUD_Data_Film/CreateFilm.h"
#include "CRUD/CRUD_Data_Film/UpdateFilm.h"
#include "CRUD/CRUD_Data_Film/DeleteFilm.h"

// Struct AkunDataSementara (sudah ada di file eksternal CRUD)
typedef struct
{
    char ID[10];
    char akun[20];
    char username[50];
    char sandi[50];
    char jabatan[20];
    char status[50];
} AkunDataSementara;

// Prototipe fungsi tambahan
void clearScreen();
void tampilkanProfil();
void tampilkanDaftarAkun();
void tampilkanDaftarRuangan();
void tampilkanMenu();
int tampilkanMenuNavigasi();

// Fungsi membersihkan layar
void clearScreen()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// Fungsi untuk menampilkan menu dengan navigasi arrow key
int tampilkanMenuNavigasi()
{
    int pilihan = 1;       // Indeks menu yang sedang dipilih
    int jumlahPilihan = 8; // Total menu
    char key;

    while (1)
    {
        clearScreen();
        printf("=== SIDE NAVBAR ===\n");
        printf("%s PROFIL\n", pilihan == 1 ? ">" : " ");
        printf("%s DAFTAR AKUN\n", pilihan == 2 ? ">" : " ");
        printf("%s DAFTAR FILM\n", pilihan == 3 ? ">" : " ");
        printf("%s DAFTAR RUANGAN\n", pilihan == 4 ? ">" : " ");
        printf("%s JADWAL TAYANG\n", pilihan == 5 ? ">" : " ");
        printf("%s DAFTAR FNB\n", pilihan == 6 ? ">" : " ");
        printf("%s LAPORAN\n", pilihan == 7 ? ">" : " ");
        printf("%s LOGOUT\n", pilihan == 8 ? ">" : " ");

        key = getch();

        if (key == 72)
        { // Arrow Up
            pilihan--;
            if (pilihan < 1)
                pilihan = jumlahPilihan;
        }
        else if (key == 80)
        { // Arrow Down
            pilihan++;
            if (pilihan > jumlahPilihan)
                pilihan = 1;
        }
        else if (key == '\r')
        { // Enter
            return pilihan;
        }
    }
}

// Fungsi untuk menampilkan profil admin
void tampilkanProfil(AkunData *akun, ProfilData *profil)
{

    while (1)
    {
        clearScreen();

        const char *menuProfil[] = {"GANTI SANDI", "EDIT", "KEMBALI"};

        int pilihan = PilihOpsi("Profil", menuProfil, akun, profil, 3);

        ReadProfile(akun, profil);

        switch (pilihan)
        {
        case 0:
            system("cls");
            ReadProfile(akun, profil);
            TampilkanPesan("Maaf fitur belum tersedia!", 2);
            break;
        case 1:
            system("cls");
            ReadProfile(akun, profil);
            EditProfil(akun, profil);
            break;
        case 2:
            break;
        }
        if (pilihan == 2)
        {
            break;
        }
    }
}

// Fungsi untuk menampilkan daftar akun
void tampilkanDaftarAkun()
{
    while (1)
    {
        clearScreen();

        const char *menuAkun[] = {"EDIT", "-HAPUS", "+TAMBAH", "KEMBALI"};

        const char *Master = "Akun";
        int pilihan = PilihOpsi(Master, menuAkun, NULL, NULL, 4);
        ReadAkun();
        switch (pilihan)
        {
        case 0:
            system("cls");
            ReadAkun();
            UpdateAkun();
            break;
        case 1:
            system("cls");
            ReadAkun();
            DeleteAkun();
            break;
        case 2:
            ReadAkun();
            CreateAkun();
            break;
        case 3:
            break;
        }
        if (pilihan == 3)
        {
            break;
        }
    }
}
void tampilkanDaftarFilm()
{
    while (1)
    {
        system("cls");

        const char *menuFilm[] = {"EDIT", "-HAPUS", "+TAMBAH", "KEMBALI"};

        const char *Master = "Film";
        int pilihan = PilihOpsi(Master, menuFilm, NULL, NULL, 4);
        ReadFilm();
        switch (pilihan)
        {
        case 0:
            system("cls");
            ReadFilm();
            UpdateFilm();
            break;
        case 1:
            system("cls");
            ReadFilm();
            DeleteFilm();
            break;
        case 2:
            system("cls");
            CreateFilm();
            break;
        case 3:
            break;
        }
        if (pilihan == 3)
        {
            break;
        }
    }
}
void tampilkanDaftarMenu()
{
    while (1)
    {
        system("cls");

        const char *menuFnb[] = {"EDIT", "-HAPUS", "+TAMBAH", "KEMBALI"};

        const char *Master = "Fnb";
        int pilihan = PilihOpsi(Master, menuFnb, NULL, NULL, 4);
        ReadFnb();
        switch (pilihan)
        {
        case 0:
            system("cls");
            
            break;
        case 1:
            system("cls");
            break;
        case 2:
            system("cls");
            createFnb();
            break;
        case 3:
            break;
        }
        if (pilihan == 3)
        {
            break;
        }
    }
}

// Fungsi untuk menampilkan daftar ruangan
void tampilkanDaftarRuangan()
{
    clearScreen();
    printf("=== DAFTAR RUANGAN ===\n");
    printf("| ID Ruangan | Nama Ruangan  | Kapasitas |\n");
    printf("|------------|---------------|-----------|\n");
    printf("| 001        | Studio 1      | 100       |\n");
    printf("| 002        | Studio 2      | 150       |\n");
    printf("\nTekan Enter untuk kembali ke menu utama...");
    getchar();
}

// Fungsi untuk menampilkan menu utama
void tampilkanMenu(AkunData *akun, ProfilData *profil)
{
    int pilihan;

    do
    {
        pilihan = tampilkanMenuNavigasi();

        switch (pilihan)
        {
        case 1:
            tampilkanProfil(akun, profil);
            break;
        case 2:
            tampilkanDaftarAkun();
            break;
        case 3:
            tampilkanDaftarFilm();
            break;
        case 4:
            tampilkanDaftarRuangan();
            break;
        case 8:
            TampilkanPesan("Logging out...\n", 1);
            // return loginPage(); // Kembali ke halaman login
            return;
        default:

            TampilkanPesan("Fitur belum tersedia!\n", 1);
            break;
        }
    } while (1);
    //  if(pilihan == 8){return main();}
}

// MAIN
int DashboardAdmin(AkunData *akun)
{

    ProfilData profil = {0};
    tampilkanMenu(akun, &profil);
    return 0;
}
