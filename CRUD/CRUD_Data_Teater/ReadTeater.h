void TampilkanTeater();
int BandingkanIDTeater(const void *a, const void *b);

int ReadTeater() {
    printf("\n==== Data Teater ====\n");
    TampilkanTeater();
    return 0;
}

void TampilkanTeater() {
    FILE *file = fopen(TEATERDAT, "rb");
    if (!file) {
        printf("Gagal membuka file %s. Pastikan file tersebut ada.\n", TEATERDAT);
        return;
    }

    TeaterData teater[MAX_TEATER];
    int jumlahTeater = 0;

    // Membaca semua data dari file
    while (fread(&teater[jumlahTeater], sizeof(TeaterData), 1, file)) {
        jumlahTeater++;
    }
    fclose(file);

    // Mengurutkan data berdasarkan ID
    qsort(teater, jumlahTeater, sizeof(TeaterData), BandingkanIDTeater);

    // Menampilkan tabel
    printf("| %-8s | %-10s | %-15s | %-15s | %-10s | %-15s |\n", 
           "ID", "No Teater", "Kategori", "Jumlah Kursi", "Status", "Harga(Rp)");
    printf("--------------------------------------------------------------------------------------------\n");

    for (int i = 0; i < jumlahTeater; i++) {
        printf("| %-8s | %-10d | %-15s | %-15d | %-10s | %-15.2f |\n",
               teater[i].ID, teater[i].noTeater, teater[i].kategoriTheater, 
               teater[i].jumlahKursi, teater[i].status, teater[i].harga);
    }
    printf("\n\n\n");
}

// Fungsi pembanding untuk qsort berdasarkan ID
int BandingkanIDTeater(const void *a, const void *b) {
    TeaterData *teaterA = (TeaterData *)a;
    TeaterData *teaterB = (TeaterData *)b;

    // Memisahkan jenis ID (TTR)
    char prefixA[4], prefixB[4];
    int numberA, numberB;

    sscanf(teaterA->ID, "%3s%d", prefixA, &numberA);
    sscanf(teaterB->ID, "%3s%d", prefixB, &numberB);

    // Urutkan berdasarkan prefix (TTR)
    int cmp = strcmp(prefixA, prefixB);
    if (cmp != 0) {
        return cmp;
    }

    // Jika prefix sama, urutkan berdasarkan nomor ID
    return numberA - numberB;
}
