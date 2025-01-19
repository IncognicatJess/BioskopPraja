typedef struct {
    char ID[10];
    char namaMakanan[50];
    char kategori[20];
    int stok;
    double harga;
} FnbDataRead;

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

    FnbDataRead menu[MAX_ID];
    int jumlahMenu = 0;

    // Membaca data dari file
    while (fread(&menu[jumlahMenu], sizeof(FnbDataRead), 1, file) == 1) {
        jumlahMenu++;
        if (jumlahMenu >= MAX_ID) {
            printf("Peringatan: Jumlah data melebihi kapasitas maksimum (%d).\n", MAX_ID);
            break;
        }
    }

    fclose(file);

    // Mengurutkan data berdasarkan ID
    qsort(menu, jumlahMenu, sizeof(FnbDataRead), BandingkanIDMenu);

    // Menampilkan tabel
    printf("| %-8s | %-15s | %-15s | %-10s | %-10s |\n", "ID", "Nama", "Kategori", "Stok", "Harga");
    printf("-------------------------------------------------------------------------------\n");

    for (int i = 0; i < jumlahMenu; i++) {
        printf("| %-8s | %-15s | %-15s | %-10d | Rp%-8.0f |\n",
               menu[i].ID, menu[i].namaMakanan, menu[i].kategori, menu[i].stok, menu[i].harga);
    }
    printf("\n");
}

// Fungsi pembanding untuk qsort berdasarkan ID
int BandingkanIDMenu(const void *a, const void *b) {
    FnbDataRead *menuA = (FnbDataRead *)a;
    FnbDataRead *menuB = (FnbDataRead *)b;

    char prefixA[4] = {0}, prefixB[4] = {0};
    int numberA = 0, numberB = 0;

    sscanf(menuA->ID, "%3s%d", prefixA, &numberA);
    sscanf(menuB->ID, "%3s%d", prefixB, &numberB);

    int cmp = strcmp(prefixA, prefixB);
    if (cmp != 0) {
        return cmp;
    }

    return numberA - numberB;
}
