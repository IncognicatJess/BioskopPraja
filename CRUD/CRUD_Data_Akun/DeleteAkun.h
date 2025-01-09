#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <conio.h>

#define FILENAME "./Database/Akun/DataAkun.dat"
#define TEMP_FILENAME "./Database/Akun/TempDataAkun.dat"
#define MAX_ACCOUNTS 1000

typedef struct {
    char ID[10];
    char akun[20];
    char username[50];
    char sandi[50];
    char jabatan[20];
    char status[50];
} AkunDataDelete;


int TombolKonfirmasi(const char *judul);
void HapusAkun();
int BandingkanID(const void *a, const void *b);

int DeleteAkun() {
    printf("\n==== Hapus Akun ====\n");
    HapusAkun();
    return 0;
}

int TombolKonfirmasi(const char *judul) {
    const char *pilihan[] = {"BATAL", "KONFIRMASI"};
    int indeks = 0;
    char key;

    while (1) {
        system("cls");
        printf("%s\n\n", judul);

        for (int i = 0; i < 2; i++) {
            if (i == indeks) {
                printf(" >[%s]\n", pilihan[i]);
            } else {
                printf("  [%s]\n", pilihan[i]);
            }
        }

        key = getch();
        if (key == 75 || key == 72) // Panah kiri atau atas
            indeks = (indeks - 1 + 2) % 2;
        else if (key == 77 || key == 80) // Panah kanan atau bawah
            indeks = (indeks + 1) % 2;
        else if (key == '\r') // Enter
            return indeks;
    }
}

void HapusAkun() {
    FILE *file = fopen(FILENAME, "rb");
    FILE *tempFile = fopen(TEMP_FILENAME, "wb");

    if (!file || !tempFile) {
        printf("Gagal membuka file database.\n");
        return;
    }

    char idHapus[10];
    printf("Masukkan ID yang ingin dihapus: ");
    scanf("%s", idHapus);

    // Validasi untuk ID yang tidak bisa dihapus
    if (strcmp(idHapus, "ACT001") == 0) {
        TampilkanPesan("ID ACT001 tidak dapat dihapus karena merupakan akun utama.\n", 2);
        fclose(file);
        fclose(tempFile);
        remove(TEMP_FILENAME);
        return;
    }

    AkunDataDelete akun;
    bool ditemukan = false;

    while (fread(&akun, sizeof(AkunDataDelete), 1, file)) {
        if (strcmp(akun.ID, idHapus) == 0) {
            ditemukan = true;
        } else {
            fwrite(&akun, sizeof(AkunDataDelete), 1, tempFile);
        }
    }

    fclose(file);
    fclose(tempFile);

    if (ditemukan) {
        ReadAkun();
        // Konfirmasi sebelum penghapusan
        int konfirmasi = TombolKonfirmasi("Apakah Anda yakin ingin menghapus akun ini?");
        if (konfirmasi == 1) { // KONFIRMASI
            remove(FILENAME);
            rename(TEMP_FILENAME, FILENAME);
            printf("Akun dengan ID %s berhasil dihapus.\n", idHapus);
        } else { // BATAL
            printf("Penghapusan dibatalkan.\n");
            remove(TEMP_FILENAME);
        }
    } else {
        remove(TEMP_FILENAME);
        printf("Akun dengan ID %s tidak ditemukan.\n", idHapus);
    }
}
