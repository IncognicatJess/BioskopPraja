#include <time.h> // Untuk waktu lokal

// Fungsi untuk menghasilkan ID transaksi dan nomor urut
void GenerateTransactionID(Tiket *pesanan) {
    static long nomorUrut = 0; // Simpan nomor urut secara global
    static char lastID[10] = "TRT000"; // Simpan ID terakhir

    FILE *file = fopen(TRANSCFILE, "rb");
    if (file) {
        // Cari ID terakhir di file transaksi
        Tiket temp;
        while (fread(&temp, sizeof(Tiket), 1, file)) {
            if (strncmp(temp.ID, "TRT", 3) == 0) {
                strncpy(lastID, temp.ID, sizeof(lastID) - 1);
                lastID[sizeof(lastID) - 1] = '\0';
                nomorUrut = temp.no; // Ambil nomor urut terakhir
            }
        }
        fclose(file);
    }

    // Increment nomor urut
    nomorUrut++;

    // Generate ID baru
    int nomorID = (nomorUrut - 1) % 999 + 1; // Reset ke 1 setelah 999
    snprintf(pesanan->ID, sizeof(pesanan->ID), "TRT%03d", nomorID);
    pesanan->no = nomorUrut; // Simpan nomor urut
}

// Fungsi untuk menambahkan tanggal transaksi
void TambahkanTanggalTransaksi(Tiket *pesanan) {
    time_t now = time(NULL);
    struct tm *local = localtime(&now);

    pesanan->tanggalTransc.tanggal = local->tm_mday;
    pesanan->tanggalTransc.bulan = local->tm_mon + 1; // tm_mon dimulai dari 0
    pesanan->tanggalTransc.tahun = local->tm_year + 1900; // tm_year adalah tahun sejak 1900
}
void InvoiceTiket(Tiket *pesanan) {
    char key;
    double nominalPembayaran = 0;
    double kembalian = 0;
    int metodePembayaran = 0; // 0: Tunai, 1: E-Wallet, 2: Bank, 3: Lainnya
    const char *metode[] = {"Tunai", "E-Wallet", "Bank", "Lainnya"};
    char catatan[1000] = "";
    int step = 0; // Step untuk navigasi form

    // Generate ID transaksi dan nomor urut
    GenerateTransactionID(pesanan);

    // Tambahkan tanggal transaksi
    TambahkanTanggalTransaksi(pesanan);

    while (1) {
        system("cls");
        printf("==== Transaksi Tiket ====\n\n");

        // Tampilkan invoice
        printf("ID Transaksi: %s\n", pesanan->ID);
        printf("No. Transaksi: %ld\n", pesanan->no);
        printf("Tanggal Transaksi: %02d/%02d/%04d\n", pesanan->tanggalTransc.tanggal, pesanan->tanggalTransc.bulan, pesanan->tanggalTransc.tahun);
        printf("Film: %s\n", pesanan->judulFilm);
        printf("Tanggal: %02d/%02d/%04d\n", pesanan->Tanggal.tanggal, pesanan->Tanggal.bulan, pesanan->Tanggal.tahun);
        printf("Jam: %02d:%02d\n", pesanan->jamTayang.jam, pesanan->jamTayang.menit);
        printf("ID Teater: %s\n", pesanan->IDTeater);
        printf("No Teater: %d\n", pesanan->Teater);
        printf("Jumlah Tiket: %d\n", pesanan->tiket);
        printf("Harga Tiket: Rp. %.2lf\n", pesanan->harga);
        printf("Total Harga: Rp. %.2lf\n", pesanan->total);
        printf("\n");

        // Step 0: Input nominal pembayaran
        if (step == 0) {
            printf("Nominal Pembayaran: Rp. %.2lf\n", nominalPembayaran);
            printf("Kembalian: Rp. %.2lf\n", kembalian);
            if (nominalPembayaran < pesanan->total) {
                printf("Uang tidak cukup! Silakan tambah nominal.\n");
            }
            printf("\nTekan Enter untuk lanjut, Esc untuk keluar.\n");
        }

        // Step 1: Pilih metode pembayaran
        else if (step == 1) {
            printf("Metode Pembayaran: ");
            for (int i = 0; i < 4; i++) {
                if (i == metodePembayaran) {
                    printf(" >[%s] ", metode[i]);
                } else {
                    printf("  [%s] ", metode[i]);
                }
            }
            printf("\n\nTekan Enter untuk lanjut, Esc untuk keluar.\n");
        }

        // Step 2: Input catatan
        else if (step == 2) {
            printf("Catatan: %s\n", catatan);
            printf("\nTekan Enter untuk lanjut, Esc untuk keluar.\n");
        }

        // Step 3: Konfirmasi transaksi
        else if (step == 3) {
            printf("Apakah Anda yakin ingin menyelesaikan transaksi?\n");
            printf("Tekan Enter untuk konfirmasi, Esc untuk keluar.\n");
        }

        // Handle input pengguna
        key = getch();

        // Tombol "Esc" untuk membatalkan transaksi
        if (key == 27) {
            printf("Transaksi dibatalkan.\n");
            return;
        }

        // Step 0: Input nominal pembayaran
        if (step == 0) {
            if (key == '\r') { // Enter untuk lanjut
                if (nominalPembayaran >= pesanan->total) {
                    step++;
                } else {
                    printf("Masukkan nominal pembayaran: ");
                    scanf("%lf", &nominalPembayaran);
                    getchar(); // Menangkap newline setelah input
                    if (nominalPembayaran < pesanan->total) {
                        TampilkanPesan("Uang tidak cukup! Silakan tambah nominal.", 2);
                    } else {
                        kembalian = nominalPembayaran - pesanan->total;
                        step++;
                    }
                }
            }
        }

        // Step 1: Pilih metode pembayaran
        else if (step == 1) {
            if (key == 75) { // Panah kiri
                metodePembayaran = (metodePembayaran - 1 + 4) % 4;
            } else if (key == 77) { // Panah kanan
                metodePembayaran = (metodePembayaran + 1) % 4;
            } else if (key == '\r') { // Enter untuk lanjut
                step++;
            }
        }

        // Step 2: Input catatan
        else if (step == 2) {
            if (key == '\r') { // Enter untuk lanjut
                step++;
            } else if (key == 8 && strlen(catatan) > 0) { // Backspace
                catatan[strlen(catatan) - 1] = '\0';
            } else if (strlen(catatan) < 999 && isprint(key)) { // Input karakter
                catatan[strlen(catatan)] = key;
                catatan[strlen(catatan) + 1] = '\0';
            }
        }

        // Step 3: Konfirmasi transaksi
        else if (step == 3) {
            // Konfirmasi transaksi
                int konfirmasi = TombolKonfirmasi("Transaksi", "Konfirmasi", pesanan, "Tiket");
                if (konfirmasi == 1) { // KONFIRMASI
                    // Simpan transaksi ke file
                    FILE *file = fopen(TRANSCFILE, "ab");
                    if (!file) {
                        TampilkanPesan("Gagal membuka file transaksi.", 2);
                        return;
                    }
                    fwrite(pesanan, sizeof(Tiket), 1, file);
                    fclose(file);

                    TampilkanPesan("Transaksi berhasil disimpan!", 1);
                    return;
                } else { // BATAL
                    printf("Transaksi dibatalkan.\n");
                    return;
                }
        }
    }
}