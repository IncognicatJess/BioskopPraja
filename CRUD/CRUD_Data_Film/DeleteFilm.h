#define TEMP_FILEFILM "./Database/Film/TempDataFilm.dat"

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
} MovieDataDelete;

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

    MovieDataDelete film;
    MovieDataDelete filmDihapus;
    bool ditemukan = false;

    while (fread(&film, sizeof(MovieDataDelete), 1, file)) {
        if (strcmp(film.ID, idHapus) == 0) {
            ditemukan = true;
            filmDihapus = film;
        } else {
            fwrite(&film, sizeof(MovieDataDelete), 1, tempFile);
        }
    }

    fclose(file);
    fclose(tempFile);

    if (ditemukan) {
        ReadFilm();
        // Konfirmasi sebelum penghapusan
        int konfirmasi = TombolKonfirmasi("Film","Hapus", &filmDihapus, "MovieDataDelete");
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
