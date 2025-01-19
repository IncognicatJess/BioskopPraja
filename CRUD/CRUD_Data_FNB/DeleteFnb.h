typedef struct
{
    char ID[10];
    char namaMakanan[50];
    char kategori[20];
    int stok;
    double harga;
} FnbDataDelete;


void HapusMenu();

int DeleteFnb() {
    printf("\n==== Hapus Film ====\n");
    HapusMenu();
    return 0;
}

void HapusMenu() {
    FILE *file = fopen(FILEMENU, "rb");
    FILE *tempFile = fopen(TEMP_FILEMENU, "wb");

    if (!file || !tempFile) {
        printf("Gagal membuka file database.\n");
        if (file) fclose(file);
        if (tempFile) fclose(tempFile);
        return;
    }

    char idHapus[10];
    printf("Masukkan ID yang ingin dihapus: ");
    scanf("%9s", idHapus);

    FnbDataDelete menu;
    FnbDataDelete menuDihapus;
    bool ditemukan = false;

    while (fread(&menu, sizeof(FnbDataDelete), 1, file)) {
        if (strcmp(menu.ID, idHapus) == 0) {
            ditemukan = true;
            menuDihapus = menu;
        } else {
            fwrite(&menu, sizeof(FnbDataDelete), 1, tempFile);
        }
    }

    fclose(file);
    fclose(tempFile);

    if (ditemukan) {
        ReadFnb();
        // Konfirmasi sebelum penghapusan
        int konfirmasi = TombolKonfirmasi("FNB","Hapus", &menuDihapus, "FnbData"    );
        if (konfirmasi == 1) { // KONFIRMASI
            remove(FILEMENU);
            rename(TEMP_FILEMENU, FILEMENU);
            printf("Menu dengan ID %s berhasil dihapus.\n", idHapus);
        } else { // BATAL
            printf("Penghapusan dibatalkan.\n");
            remove(TEMP_FILEMENU);
        }
    } else {
        remove(TEMP_FILEMENU);
        printf("Menu dengan ID %s tidak ditemukan.\n", idHapus);
    }
}
