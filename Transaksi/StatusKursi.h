void UpdateStatusKursi(Tiket *pesanan) {
    FILE *file = fopen(SEATDAT, "r+b");
    if (!file) {
        TampilkanPesan("Gagal membuka file database kursi.", 2);
        return;
    }

    KursiData kursi;
    bool ditemukan = false;

    // Baca file SEATDAT dan cari kursi yang sesuai
    while (fread(&kursi, sizeof(KursiData), 1, file)) {
        if (strcmp(kursi.IDTeater, pesanan->IDTeater) == 0) {
            for (int i = 0; i < pesanan->tiket; i++) {
                if (strcmp(kursi.ID, pesanan->IDkursi[i]) == 0) {
                    // Update status kursi menjadi "Dipesan"
                    strncpy(kursi.status, "Dipesan", sizeof(kursi.status) - 1);
                    kursi.status[sizeof(kursi.status) - 1] = '\0';

                    // Pindahkan pointer file ke posisi kursi yang akan diupdate
                    fseek(file, -sizeof(KursiData), SEEK_CUR);
                    fwrite(&kursi, sizeof(KursiData), 1, file);
                    fseek(file, 0, SEEK_CUR); // Pindahkan pointer ke akhir file
                    ditemukan = true;
                }
            }
        }
    }

    fclose(file);

    if (!ditemukan) {
        TampilkanPesan("Kursi tidak ditemukan di database.", 2);
    }
}