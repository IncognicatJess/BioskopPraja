#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ID 1000

typedef struct {
    char ID[10];
    char judul[50];
    char genre[20];
    int tahunRelease;
    double durasi;
    char studioFilm[20];
    char bentuk[10];
    double harga;
    char status[50];
} MovieDataBaca;

void TampilkanFilm();
int BandingkanIDFilm(const void *a, const void *b);

int ReadFilm() {
    printf("\n==== Data Film ====\n");
    TampilkanFilm();
    return 0;
}

void TampilkanFilm() {
    FILE *file = fopen(FILEFILM, "rb");
    if (!file) {
        printf("Gagal membuka file %s. Pastikan file tersebut ada.\n", FILEFILM);
        return;
    }

    MovieDataBaca film[MAX_ID];
    int jumlahFilm = 0;

    // Membaca semua data dari file
    while (fread(&film[jumlahFilm], sizeof(MovieDataBaca), 1, file)) {
        strncpy(film[jumlahFilm].status, "Sedang Tayang", sizeof(film[jumlahFilm].status));
        jumlahFilm++;
    }
    fclose(file);

    // Mengurutkan data berdasarkan ID
    qsort(film, jumlahFilm, sizeof(MovieDataBaca), BandingkanIDFilm);

    // Menampilkan tabel
    printf("| %-8s | %-20s | %-10s | %-10s | %-10s | %-15s | %-8s | %-10s |\n", 
           "ID", "Judul Film", "Genre", "Tahun", "Durasi", "Studio", "Bentuk", "Harga (Rp)");
    printf("------------------------------------------------------------------------------------------------------------\n");

    for (int i = 0; i < jumlahFilm; i++) {
        printf("| %-8s | %-20s | %-10s | %-10d | %-10.0f | %-15s | %-8s | %-10.2f |\n",
               film[i].ID, film[i].judul, film[i].genre, film[i].tahunRelease, 
               film[i].durasi, film[i].studioFilm, film[i].bentuk, film[i].harga);
    }
    printf("\n");
}

// Fungsi pembanding untuk qsort berdasarkan ID
int BandingkanIDFilm(const void *a, const void *b) {
    MovieDataBaca *filmA = (MovieDataBaca *)a;
    MovieDataBaca *filmB = (MovieDataBaca *)b;

    // Memisahkan jenis ID (MOV)
    char prefixA[4], prefixB[4];
    int numberA, numberB;

    sscanf(filmA->ID, "%3s%d", prefixA, &numberA);
    sscanf(filmB->ID, "%3s%d", prefixB, &numberB);

    // Urutkan berdasarkan prefix (MOV)
    int cmp = strcmp(prefixA, prefixB);
    if (cmp != 0) {
        return cmp;
    }

    // Jika prefix sama, urutkan berdasarkan nomor ID
    return numberA - numberB;
}