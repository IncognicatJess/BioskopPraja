#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    char TempatLahir[50];
    int Tanggal;
    int Bulan;
    int Tahun;
} TempatTanggalLahir;

typedef struct {
    int ID;
    char username[50];
    char password[50];
    char nama[50];
    TempatTanggalLahir TTL;
    char jabatan[50];
    int noHP;
} DefaultAdmin;

// Fungsi untuk membersihkan layar (cross-platform)
void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// Fungsi untuk menampilkan profil admin
void tampilkanProfil(DefaultAdmin admin) {
    clearScreen();
    printf("=== PROFIL ===\n");
    printf("ID       : ADM000\n");
    printf("Username : %s\n", admin.username);
    printf("Nama     : John Agus\n");
    printf("TTL      : Bandung, 1 Januari 1990\n");
    printf("Jabatan  : Admin Utama\n");
    printf("No HP    : 081234567890\n");
    printf("\nTekan Enter untuk kembali ke menu utama...");
    getchar();
    getchar();
}

// Fungsi untuk menampilkan daftar akun (dummy)
void tampilkanDaftarAkun() {
    clearScreen();
    printf("=== DAFTAR AKUN ===\n");
    printf("| ID  | Username   | Password   | Jabatan       | Status   |\n");
    printf("|-----|------------|------------|---------------|----------|\n");
    printf("| 001 | user1      | pass1      | Staff         | Aktif    |\n");
    printf("| 002 | user2      | pass2      | Supervisor    | Nonaktif |\n");
    printf("\nTekan Enter untuk kembali ke menu utama...");
    getchar();
    getchar();
}

// Fungsi untuk menampilkan daftar film (dummy)
void tampilkanDaftarFilm() {
    clearScreen();
    printf("=== DAFTAR FILM ===\n");
    printf("| ID Film | Judul Film      | Durasi | Genre       |\n");
    printf("|---------|-----------------|--------|-------------|\n");
    printf("| 001     | Avengers        | 180m   | Action      |\n");
    printf("| 002     | Frozen          | 120m   | Animation   |\n");
    printf("\nTekan Enter untuk kembali ke menu utama...");
    getchar();
    getchar();
}

// Fungsi untuk menampilkan daftar ruangan (dummy)
void tampilkanDaftarRuangan() {
    clearScreen();
    printf("=== DAFTAR RUANGAN ===\n");
    printf("| ID Ruangan | Nama Ruangan  | Kapasitas |\n");
    printf("|------------|---------------|-----------|\n");
    printf("| 001        | Studio 1      | 100       |\n");
    printf("| 002        | Studio 2      | 150       |\n");
    printf("\nTekan Enter untuk kembali ke menu utama...");
    getchar();
    getchar();
}

// Fungsi untuk menampilkan menu utama
void tampilkanMenu(DefaultAdmin admin) {
    int pilihan;

    do {
        clearScreen();
        printf("=== SIDE NAVBAR ===\n");
        printf("1. Profil\n");
        printf("2. Daftar Akun\n");
        printf("3. Daftar Film\n");
        printf("4. Daftar Ruangan\n");
        printf("5. Log Out\n");
        printf("\nPilih menu: ");
        scanf("%d", &pilihan);

        switch (pilihan) {
            case 1:
                tampilkanProfil(admin);
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
            case 5:
                printf("Logging out...\n");
                break;
            default:
                printf("Pilihan tidak valid!\n");
                getchar();
                getchar();
                break;
        }
    } while (pilihan != 5);
}

int main() {
    const char correctUsername[] = "Admin";
    const char correctPassword[] = "Admin#123";

    DefaultAdmin AdminUtama;

    int loginSuccess = 0;

    while (!loginSuccess) {
        clearScreen();
        printf("=== BIOSKOP PRAJA ===\n");
        printf("Sistem Pemesanan Tiket & FnB\n\n");
        printf("#LOGIN\n");
        printf("Username: ");
        scanf("%49s", AdminUtama.username);
        printf("Password: ");
        scanf("%49s", AdminUtama.password);

        if (strcmp(AdminUtama.username, correctUsername) == 0 && strcmp(AdminUtama.password, correctPassword) == 0) {
            loginSuccess = 1;
        } else {
            printf("Username atau password salah!\n");
            printf("Tekan Enter untuk mencoba lagi...");
            getchar();
            getchar();
        }
    }

    tampilkanMenu(AdminUtama);

    return 0;
}
