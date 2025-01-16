#define TEMP_TEATERDAT "./Database/Teater/TempDataTeater.dat"

void HapusTeater();
int BandingkanIDTeater(const void *a, const void *b);

int DeleteTeater() {
    ReadTeater();
    printf("\n==== Hapus Teater ====\n");
    HapusTeater();
    return 0;
}

void HapusTeater() {
    FILE *file = fopen(TEATERDAT, "rb");
    FILE *tempFile = fopen(TEMP_TEATERDAT, "wb");

    if (!file || !tempFile) {
        printf("Gagal membuka file database teater.\n");
        if (file) fclose(file);
        if (tempFile) fclose(tempFile);
        return;
    }

    char idHapus[10];

    
    printf("\n\n");
    printf("Masukkan ID teater yang ingin dihapus: ");
    scanf("%9s", idHapus);

    // Validasi untuk ID teater yang tidak bisa dihapus
    /*
    if (strcmp(idHapus, "TTR001") == 0) {
        TampilkanPesan("ID TTR001 tidak dapat dihapus karena merupakan data teater utama.\n", 2);
        fclose(file);
        fclose(tempFile);
        remove(TEMP_TEATERDAT);
        return;
    }*/

    TeaterData teater;
    TeaterData teaterDihapus;
    bool ditemukan = false;

    while (fread(&teater, sizeof(TeaterData), 1, file)) {
        if (strcmp(teater.ID, idHapus) == 0) {
            ditemukan = true;
            teaterDihapus = teater;
        } else {
            fwrite(&teater, sizeof(TeaterData), 1, tempFile);
        }
    }

    fclose(file);
    fclose(tempFile);

    if (ditemukan) {
      //  ReadTeater(); // Tampilkan data teater untuk memastikan keberadaan ID
        // Konfirmasi sebelum penghapusan
        int konfirmasi = TombolKonfirmasi("Teater", "Hapus", &teaterDihapus, "TeaterData");
        if (konfirmasi == 1) { // KONFIRMASI
            remove(TEATERDAT);
            rename(TEMP_TEATERDAT, TEATERDAT);
            printf("Teater dengan ID %s berhasil dihapus.\n", idHapus);
            sleep(2);
        } else { // BATAL
            TampilkanPesan("Penghapusan dibatalkan.\n",2);
            remove(TEMP_TEATERDAT);
        }
    } else {
        remove(TEMP_TEATERDAT);
        printf("Teater dengan ID %s tidak ditemukan.\n", idHapus);
        sleep(2);
    }
}
