//#define TEATERDAT "./Database/Teater/DataTeater.dat"

void TampilkanKursiTeater(const char *IDTeater);
int ReadKursi();

int ReadKursi()
{
    FILE *file = fopen(TEATERDAT, "rb");
    if (!file) {
        printf("Gagal membuka file database teater.\n");
        sleep(2);
        return 1;
    }

    ReadTeater();

    char IDTeater[10];
    printf("Masukkan ID Teater: ");
    scanf("%s", IDTeater);

    bool ditemukan = false;
    TeaterData teater;

    // Periksa apakah ID teater ada di file TEATERDAT
    while (fread(&teater, sizeof(TeaterData), 1, file)) {
        if (strcmp(teater.ID, IDTeater) == 0) {
            ditemukan = true;
            break;
        }
    }

    fclose(file);

    if (ditemukan) {
        printf("Menampilkan kursi untuk ID Teater: %s\n", IDTeater);
        printf("Kelas : %s\n", teater.kategoriTheater);
        printf("=====================================\n");
        printf("ID TEATER | ID KURSI | STATUS\n");
        printf("-------------------------------------\n");
        TampilkanKursiTeater(IDTeater); // Tampilkan kursi dari SEATDAT
    } else {
        printf("Teater dengan ID %s tidak ditemukan.\n", IDTeater);
        sleep(2);
    }

    return 0;
}

// Fungsi untuk membaca dan menampilkan kursi dalam bentuk tabel
void TampilkanKursiTeater(const char *IDTeater)
{
    FILE *file = fopen(SEATDAT, "rb");
    if (!file) {
        printf("Gagal membuka file database kursi.\n");
        return;
    }

    KursiData kursi;
    int dataDitemukan = 0;

    while (fread(&kursi, sizeof(KursiData), 1, file)) {
        if (strcmp(kursi.IDTeater, IDTeater) == 0) {
            printf("%-10s | %-8s | %-10s\n", kursi.IDTeater, kursi.ID, kursi.status);
            dataDitemukan = 1;
        }
    }

    if (!dataDitemukan) {
        printf("Tidak ada data kursi untuk ID teater: %s\n", IDTeater);
        sleep(2);
    }


    printf("\n");
    printf("Tekan apapun untuk kembali.\n");
    getch();
    fclose(file);
}
