//LIBRARY STANDAR
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <conio.h>
#include <time.h>
#include <ctype.h>
#include <windows.h>
#include <unistd.h>

//CRUD DATA AKUN
#include "CRUD/CRUD_Data_Akun/ReadAkun.h"
#include "CRUD/CRUD_Data_Akun/CreateAkun.h"
#include "CRUD/CRUD_Data_Akun/UpdateAkun.h"
#include "CRUD/CRUD_Data_Akun/DeleteAkun.h"

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
void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// Fungsi untuk menampilkan menu dengan navigasi arrow key
int tampilkanMenuNavigasi() {
    int pilihan = 1; // Indeks menu yang sedang dipilih
    int jumlahPilihan = 7; // Total menu
    char key;

    while (1) {
        clearScreen();
        printf("=== SIDE NAVBAR ===\n");
        printf("%s PROFIL\n", pilihan == 1 ? ">" : " ");
        printf("%s DAFTAR AKUN\n", pilihan == 2 ? ">" : " ");
        printf("%s DAFTAR RUANGAN\n", pilihan == 3 ? ">" : " ");
        printf("%s JADWAL TAYANG\n", pilihan == 4 ? ">" : " ");
        printf("%s DAFTAR FNB\n", pilihan == 5 ? ">" : " ");
        printf("%s LAPORAN\n", pilihan == 6 ? ">" : " ");
        printf("%s LOGOUT\n", pilihan == 7 ? ">" : " ");

        key = getch();

        if (key == 72) { // Arrow Up
            pilihan--;
            if (pilihan < 1) pilihan = jumlahPilihan;
        } else if (key == 80) { // Arrow Down
            pilihan++;
            if (pilihan > jumlahPilihan) pilihan = 1;
        } else if (key == '\r') { // Enter
            return pilihan;
        }
    }
}

// Fungsi untuk menampilkan profil admin
void tampilkanProfil() {
    clearScreen();
    printf("=== PROFIL ===\n");
    printf("ID       : ADM000\n");
    printf("Username : AdminUtama\n");
    printf("Nama     : John Agus\n");
    printf("TTL      : Bandung, 1 Januari 1990\n");
    printf("Jabatan  : Admin Utama\n");
    printf("No HP    : 081234567890\n");
    printf("\nTekan Enter untuk kembali ke menu utama...");
    getchar();
}

// Fungsi untuk menampilkan daftar akun
void tampilkanDaftarAkun() {
    while (1) {
        clearScreen();
 
        const char *menuAkun[] = {"EDIT", "-HAPUS", "+TAMBAH","KEMBALI"};
        ReadAkun();
        
        int pilihan = PilihOpsi("Pilih aksi untuk akun:", menuAkun, 4);

        switch (pilihan) {
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
        if (pilihan == 3) {
            break;
        }
    }
}

// Fungsi untuk menampilkan daftar ruangan
void tampilkanDaftarRuangan() {
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
void tampilkanMenu() {
    int pilihan;

    do {
        pilihan = tampilkanMenuNavigasi();

        switch (pilihan) {
            case 1:
                tampilkanProfil();
                break;
            case 2:
                tampilkanDaftarAkun();
                break;
            case 3:
                tampilkanDaftarRuangan();
                break;
            case 7:
                printf("Logging out...\n");
                return; // Kembali ke halaman login
            default:
                
                TampilkanPesan("Fitur belum tersedia!\n",1);
                break;
        }
    } while (1);
}

int main() {
    tampilkanMenu();
    return 0;
}
