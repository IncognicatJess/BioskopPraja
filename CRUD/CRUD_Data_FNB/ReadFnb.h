#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ID 1000

void TampilkanMenuFnb();
int BandingkanIDMenu(const void *a, const void *b);

int ReadFnb() {
    printf("\n==== Data Menu F&B ====\n");
    TampilkanMenuFnb();
    return 0;
}

void TampilkanMenuFnb() {
    FILE *file = fopen(FILEMENU, "rb");
    if (!file) {
        printf("Gagal membuka file %s. Pastikan file tersebut ada.\n", FILEMENU);
        return;
    }

    FnbData menu[MAX_ID];
    int jumlahMenu = 0;

    // Membaca data dari file
    while (fread(&menu[jumlahMenu], sizeof(FnbData), 1, file)) {
        jumlahMenu++;
        if (jumlahMenu >= MAX_ID) {
            printf("Peringatan: Jumlah data melebihi kapasitas maksimum (%d).\n", MAX_ID);
            break;
        }
    }

    fclose(file);

    // Mengurutkan data berdasarkan ID
    qsort(menu, jumlahMenu, sizeof(FnbData), BandingkanIDMenu);

    // Menampilkan tabel
    printf("| %-8s | %-20s | %-15s | %-10s | %-15s | %-10s |\n", 
           "ID", "Nama", "Kategori", "Stok", "Harga (Rp)", "Status");
    printf("-------------------------------------------------------------------------------------------\n");

    for (int i = 0; i < jumlahMenu; i++) {
        char status[20];
        if (menu[i].stok > 0) {
            strncpy(status, "Tersedia", sizeof(status));
        } else {
            strncpy(status, "Habis", sizeof(status));
        }

        printf("| %-8s | %-20s | %-15s | %-10d | %-13.0f | %-10s |\n",
               menu[i].ID, menu[i].namaMakanan, menu[i].kategori, menu[i].stok, menu[i].harga, status);
    }
    printf("\n");
}

// Fungsi pembanding untuk qsort berdasarkan ID
int BandingkanIDMenu(const void *a, const void *b) {
    const FnbData *menuA = (const FnbData *)a;
    const FnbData *menuB = (const FnbData *)b;

    char prefixA[4] = {0}, prefixB[4] = {0};
    int numberA = 0, numberB = 0;

    // Ekstrak prefix dan angka dari ID
    sscanf(menuA->ID, "%3s%d", prefixA, &numberA);
    sscanf(menuB->ID, "%3s%d", prefixB, &numberB);

    // Bandingkan prefix terlebih dahulu
    int cmp = strcmp(prefixA, prefixB);
    if (cmp != 0) {
        return cmp;
    }

    // Jika prefix sama, bandingkan angka
    return numberA - numberB;
}