#define MAX_BARIS 50
#define MAX_KOLOM 50


void PerbaruiKursi(TeaterData *kursiTeater, int kelas);
void cariBarisKolom(int jumlahKursi, int *baris, int *kolom, int kelas);
void indeksKeHuruf(int indeks, char *huruf);
int UpdateKursi(TeaterData *kursiTeater, int kelas);


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

