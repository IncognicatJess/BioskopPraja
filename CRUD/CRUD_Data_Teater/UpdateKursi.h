#define MAX_BARIS 50
#define MAX_KOLOM 50


void PerbaruiKursi(TeaterData *kursiTeater, int kelas);
void cariBarisKolom(int jumlahKursi, int *baris, int *kolom, int kelas);
void indeksKeHuruf(int indeks, char *huruf);
int UpdateKursi(TeaterData *kursiTeater, int kelas);

//const char *StatusKursi[] = {"Tersedia", "Dipesan"};

// Fungsi utama untuk membuat kursi berdasarkan data teater
int UpdateKursi(TeaterData *kursiTeater, int kelas)
{
    PerbaruiKursi(kursiTeater, kelas);
    return 0;
}
void PerbaruiKursi(TeaterData *kursiTeater, int kelas) {
    FILE *file = fopen(SEATDAT, "rb");
    FILE *tempFile = fopen(TEMP_SEATDAT, "wb");

    if (!file || !tempFile) {
        TampilkanPesan("Gagal membuka file database kursi.", 2);
        if (file) fclose(file);
        if (tempFile) fclose(tempFile);
        return;
    }

    KursiData kursi;
    int baris = 0, kolom = 0;
    cariBarisKolom(kursiTeater->jumlahKursi, &baris, &kolom, kelas);

    if (baris == 0 || kolom == 0) {
        TampilkanPesan("Gagal menentukan konfigurasi kursi.", 2);
        fclose(file);
        fclose(tempFile);
        remove(TEMP_SEATDAT);
        return;
    }

    // Salin data kursi kecuali milik teater yang sedang diperbarui
    while (fread(&kursi, sizeof(KursiData), 1, file)) {
        if (strcmp(kursi.IDTeater, kursiTeater->ID) != 0) {
            fwrite(&kursi, sizeof(KursiData), 1, tempFile);
        }
    }

    // Tambahkan data kursi baru untuk teater ini
    char huruf[3];
    strncpy(kursi.IDTeater, kursiTeater->ID, sizeof(kursi.IDTeater) - 1);

    for (int i = 0; i < baris; i++) {
        indeksKeHuruf(i, huruf); // Mendapatkan huruf baris (A, B, C...)
        for (int j = 1; j <= kolom; j++) {
            char sj[5];
            snprintf(sj, sizeof(sj), "%d", j); // Konversi kolom ke string

            snprintf(kursi.ID, sizeof(kursi.ID), "%s%s", huruf, sj);         // Gabungkan huruf dan nomor
            strncpy(kursi.status, StatusKursi[0], sizeof(kursi.status) - 1); // Default "Tersedia"

            fwrite(&kursi, sizeof(KursiData), 1, tempFile); // Simpan ke file
        }
    }

    fclose(file);
    fclose(tempFile);

    // Ganti file lama dengan file baru
    remove(SEATDAT);
    rename(TEMP_SEATDAT, SEATDAT);

    TampilkanPesan("Kursi berhasil diperbarui.", 2);
}

/*
// Fungsi untuk mengubah indeks ke karakter huruf (melewati I dan O)
void indeksKeHuruf(int indeks, char *huruf)
{
    int count = 0;
    for (int i = 0; i <= indeks; i++)
    {
        huruf[0] = 'A' + count;
        if (huruf[0] == 'I' || huruf[0] == 'O')
        {
            count++; // Lewati huruf I dan O
            huruf[0] = 'A' + count;
        }
        count++;
    }
    huruf[1] = '\0';
}

// Fungsi untuk mencari pasangan baris dan kolom terbaik berdasarkan kelas
void cariBarisKolom(int jumlahKursi, int *baris, int *kolom, int kelas)
{
    int minBaris, maxBaris, minKolom, maxKolom;

    // Tetapkan batasan berdasarkan kelas
    switch (kelas)
    {
    case 0: // Reguler
        minBaris = 10;
        maxBaris = 12;
        minKolom = 10;
        maxKolom = 20;
        break;
    case 1: // Premiere
        minBaris = 4;
        maxBaris = 6;
        minKolom = 5;
        maxKolom = 10;
        break;
    case 2: // Mini Studio
        minBaris = 8;
        maxBaris = 10;
        minKolom = 8;
        maxKolom = 12;
        break;
    default:
        TampilkanPesan("Kelas tidak valid.", 2);
        *baris = 0;
        *kolom = 0;
        return;
    }

    int minSelisih = 9999;
    *baris = 0; // Inisialisasi nilai default
    *kolom = 0;

    for (int i = minBaris; i <= maxBaris; i++)
    {
        if (jumlahKursi % i == 0)
        {
            int k = jumlahKursi / i;
            if (k >= minKolom && k <= maxKolom)
            {
                int selisih = abs(i - k);
                if (selisih < minSelisih)
                {
                    *baris = i;
                    *kolom = k;
                    minSelisih = selisih;
                }
            }
        }
    }

    if (*baris == 0 || *kolom == 0)
    {
        TampilkanPesan("Tidak ada kombinasi baris dan kolom yang valid.", 2);
    }
}

*/