#define FILENAME "./Database/Akun/DataAkun.dat"
#define MAX_ACCOUNTS 1000

typedef struct {
    char ID[10];
    char akun[20];
    char username[50];
    char sandi[50];
    char jabatan[20];
    char status[50];
} AkunDataRead;

void TampilkanAkun();
int BandingkanID(const void *a, const void *b);

int ReadAkun() {
    printf("\n==== Data Akun ====\n");
    TampilkanAkun();
    return 0;
}

void TampilkanAkun() {
    FILE *file = fopen(FILENAME, "rb");
    if (!file) {
        printf("Gagal membuka file %s. Pastikan file tersebut ada.\n", FILENAME);
        return;
    }

    AkunDataRead akun[MAX_ACCOUNTS];
    int jumlahAkun = 0;

    // Membaca semua data dari file
    while (fread(&akun[jumlahAkun], sizeof(AkunDataRead), 1, file)) {
        strncpy(akun[jumlahAkun].status, "Aktif", sizeof(akun[jumlahAkun].status));
        jumlahAkun++;
    }
    fclose(file);

    // Mengurutkan data berdasarkan ID
    qsort(akun, jumlahAkun, sizeof(AkunDataRead), BandingkanID);

    // Menampilkan tabel
    printf("| %-8s | %-10s | %-15s | %-15s | %-15s | %-10s |\n", "ID", "Akun", "Username", "Sandi", "Jabatan", "Status");
    printf("----------------------------------------------------------------------------------------------------\n");

    for (int i = 0; i < jumlahAkun; i++) {
        printf("| %-8s | %-10s | %-15s | %-15s | %-15s | %-10s |\n",
               akun[i].ID, akun[i].akun, akun[i].username, akun[i].sandi, akun[i].jabatan, akun[i].status);
    }
    printf("\n\n\n");
}

// Fungsi pembanding untuk qsort berdasarkan ID
int BandingkanID(const void *a, const void *b) {
    AkunDataRead *akunA = (AkunDataRead *)a;
    AkunDataRead *akunB = (AkunDataRead *)b;

    // Memisahkan jenis ID (ADM atau USR)
    char prefixA[4], prefixB[4];
    int numberA, numberB;

    sscanf(akunA->ID, "%3s%d", prefixA, &numberA);
    sscanf(akunB->ID, "%3s%d", prefixB, &numberB);

    // Urutkan berdasarkan prefix dulu (ADM < USR)
    int cmp = strcmp(prefixA, prefixB);
    if (cmp != 0) {
        return cmp;
    }

    // Jika prefix sama, urutkan berdasarkan nomor ID
    return numberA - numberB;
}
