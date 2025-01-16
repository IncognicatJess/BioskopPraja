#define TEMP_FILENAME "./Database/Akun/TempDataAkun.dat"


void HapusAkun();
int BandingkanID(const void *a, const void *b);

int DeleteAkun() {
    printf("\n==== Hapus Akun ====\n");
    HapusAkun();
    return 0;
}

void HapusAkun() {
    FILE *file = fopen(FILENAME, "rb");
    FILE *tempFile = fopen(TEMP_FILENAME, "wb");

    if (!file || !tempFile) {
        printf("Gagal membuka file database.\n");
        if (file) fclose(file);
        if (tempFile) fclose(tempFile);
        return;
    }

    char idHapus[10];
    printf("Masukkan ID yang ingin dihapus: ");
    scanf("%9s", idHapus);

    // Validasi untuk ID yang tidak bisa dihapus
    if (strcmp(idHapus, "ACT001") == 0) {
        TampilkanPesan("ID ACT001 tidak dapat dihapus karena merupakan akun utama.\n", 2);
        fclose(file);
        fclose(tempFile);
        remove(TEMP_FILENAME);
        return;
    }

    AkunData akun;
    AkunData akunDihapus;
    bool ditemukan = false;

    while (fread(&akun, sizeof(AkunData), 1, file)) {
        if (strcmp(akun.ID, idHapus) == 0) {
            ditemukan = true;
            akunDihapus = akun;
        } else {
            fwrite(&akun, sizeof(AkunData), 1, tempFile);
        }
    }

    fclose(file);
    fclose(tempFile);

    if (ditemukan) {
        ReadAkun();
        // Konfirmasi sebelum penghapusan
        int konfirmasi = TombolKonfirmasi("Akun","Hapus", &akunDihapus, "AkunData");
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
