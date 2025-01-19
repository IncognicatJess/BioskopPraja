#define TEMP_FILEFILM "./Database/Film/TempDataFilm.dat"

void HapusFilm();
int BandingkanID(const void *a, const void *b);

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
    printf("Masukkan ID yang ingin dihapus: ");
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
        ReadFilm();
        // Konfirmasi sebelum penghapusan
        int konfirmasi = TombolKonfirmasi("Film","Hapus", &filmDihapus, "MovieData");
        if (konfirmasi == 1) { // KONFIRMASI
            remove(FILEFILM);
            rename(TEMP_FILEFILM, FILEFILM);
            printf("Film dengan ID %s berhasil dihapus.\n", idHapus);
        } else { // BATAL
            printf("Penghapusan dibatalkan.\n");
            remove(TEMP_FILEFILM);
        }
    } else {
        remove(TEMP_FILEFILM);
        printf("Film dengan ID %s tidak ditemukan.\n", idHapus);
    }
}
