
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

// CRUD DATA TEATER
#include "CRUD/CRUD_Data_Teater/CreateTeater.h"
#include "CRUD/CRUD_Data_Teater/ReadTeater.h"
#include "CRUD/CRUD_Data_Teater/DeleteTeater.h"
#include "CRUD/CRUD_Data_Teater/UpdateTeater.h"

// CRUD DATA FNB
#include "CRUD/CRUD_Data_FNB/CreateFnb.h"
#include "CRUD/CRUD_Data_FNB/ReadFnb.h"
#include "CRUD/CRUD_Data_FNB/DeleteFnb.h"
#include "CRUD/CRUD_Data_FNB/UpdateFnb.h"

// CRUD JADWAL TAYANG
#include "CRUD/CRUD_JadwalTayang/CreateSchedule.h"
#include "CRUD/CRUD_JadwalTayang/ReadSchedule.h"
#include "CRUD/CRUD_JadwalTayang/UpdateSchedule.h"
#include "CRUD/CRUD_JadwalTayang/DeleteSchedule.h"

// CRUD KURSI
#include "CRUD/CRUD_Data_Teater/CreateKursi.h"
#include "CRUD/CRUD_Data_Teater/ReadKursi.h"
#include "CRUD/CRUD_Data_Teater/DeleteKursi.h"
#include "CRUD/CRUD_Data_Teater/UpdateKursi.h"

// U SANDI
#include "CRUD/CRU_Data_Profile/UpdateSandi.h"

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
void tampilkanDaftarTeater();
void tampilkanMenuAdmin();
void tampilkanJadwalTayang();
int tampilkanMenuAdminNavigasi();

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
int tampilkanMenuAdminNavigasi()
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
        printf("%s DAFTAR TEATER\n", pilihan == 4 ? ">" : " ");
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
            GantiSandi(akun, "Profil");
            // TampilkanPesan("Hubungi Admin untuk mengganti username dan password!", 2);

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

        const char *menuAkun[] = {"EDIT", "-HAPUS", "+TAMBAH", "GANTI SANDI", "KEMBALI"};

        const char *Master = "Akun";
        int pilihan = PilihOpsi(Master, menuAkun, NULL, NULL, 5);
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
            system("cls");
            GantiSandi(NULL, "Akun");
            break;
        case 4:
            break;
        }
        if (pilihan == 4)
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

      
        int pilihan = PilihOpsi("Fnb", menuFnb, NULL, NULL, 4);
        switch (pilihan)
        {
        case 0:
            system("cls");
            ReadFnb();
            UpdateFnb();
            break;
        case 1:
            system("cls");
            ReadFnb();
            DeleteFnb();
            break;
        case 2:
            system("cls");
            CreateFnb();
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
void tampilkanDaftarTeater()
{
    while (1)
    {
        system("cls");

        const char *menuTeater[] = {"EDIT", "-HAPUS", "+TAMBAH", "KURSI", "KEMBALI"};

        const char *Master = "Teater";
        int pilihan = PilihOpsi(Master, menuTeater, NULL, NULL, 5);

        switch (pilihan)
        {
        case 0:
            system("cls");
            UpdateTeater();
            break;
        case 1:
            system("cls");
            DeleteTeater();
            break;
        case 2:
            system("cls");
            CreateTeater();
            break;
        case 3:
            system("cls");
            ReadKursi();
            break;
        case 4:
            break;
        }
        if (pilihan == 4)
        {
            break;
        }
    }
}

// Fungsi untuk menampilkan jadwal tayang
void tampilkanJadwalTayang()
{
    while (1)
    {
        system("cls");

        const char *menuJadwalTayang[] = {"EDIT", "-HAPUS", "+TAMBAH", "KEMBALI"};

        const char *Master = "Schedule";
        int pilihan = PilihOpsi(Master, menuJadwalTayang, NULL, NULL, 4);

        switch (pilihan)
        {
        case 0:
            system("cls");
            UpdateSchedule();
            break;
        case 1:
            system("cls");
            DeleteSchedule();
            break;
        case 2:
            system("cls");
            BuatJadwalTayang();
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

// Fungsi untuk menampilkan menu utama
void tampilkanMenuAdmin(AkunData *akun, ProfilData *profil)
{
    int pilihan;

    do
    {
        pilihan = tampilkanMenuAdminNavigasi();

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
            tampilkanDaftarTeater();
            break;
        case 5:
            tampilkanJadwalTayang();
            break;
        case 6:
            tampilkanDaftarMenu();
            break;
        case 8:
            TampilkanPesan("Logging out...\n", 1);
            return loginPage(); // Kembali ke halaman login
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
    tampilkanMenuAdmin(akun, &profil);
    return 0;
}
