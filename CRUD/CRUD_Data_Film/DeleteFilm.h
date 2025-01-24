#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TEMP_FILEFILM "./Database/Film/TempDataFilm.dat"

void HapusFilm();
int BandingkanIDFilm(const void *a, const void *b);

int DeleteFilm() {
    printf("\n==== Hapus Film ====\n");
    HapusFilm();
    return 0;
}

void HapusFilm() {
    FILE *file = fopen(FILEFILM, "rb");
    FILE *tempFile = fopen(TEMP_FILEFILM, "wb");

    if (!file || !tempFile) {
        printf("Gagal membuka file database.\n");
        if (file) fclose(file);
        if (tempFile) fclose(tempFile);
        return;
    }

    char idHapus[10];
    printf("Masukkan ID film yang ingin dihapus: ");
    scanf("%9s", idHapus);

    MovieData film;
    MovieData filmDihapus;
    bool ditemukan = false;

    while (fread(&film, sizeof(MovieData), 1, file)) {
        if (strcmp(film.ID, idHapus) == 0) {
            ditemukan = true;
            filmDihapus = film;
        } else {
            fwrite(&film, sizeof(MovieData), 1, tempFile);
        }
    }

    fclose(file);
    fclose(tempFile);

    if (ditemukan) {
        // Tampilkan data film yang akan dihapus
        printf("\nFilm yang akan dihapus:\n");
        printf("ID: %s | Judul: %s | Genre: %s | Tahun: %d | Durasi: %.0f menit | Harga: %.2f\n",
               filmDihapus.ID, filmDihapus.judul, filmDihapus.genre, filmDihapus.tahunRelease, filmDihapus.durasi, filmDihapus.harga);

        // Konfirmasi penghapusan
        int konfirmasi = TombolKonfirmasi("Film", "Hapus", &filmDihapus, "MovieData");
        if (konfirmasi == 1) { // KONFIRMASI
            remove(FILEFILM);
            rename(TEMP_FILEFILM, FILEFILM);
            TampilkanPesan("\nFilm berhasil dihapus.\n", 2);
        } else { // BATAL
            remove(TEMP_FILEFILM);
            TampilkanPesan("\nPenghapusan dibatalkan.\n", 2);
        }
    } else {
        remove(TEMP_FILEFILM);
        TampilkanPesan("\nFilm dengan ID tersebut tidak ditemukan.\n", 2);
    }
}