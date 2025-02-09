#include <time.h> // Untuk waktu lokal

void GenerateTransactionID(Tiket *pesanan)
{
    static long nomorUrut = 0;         // Simpan nomor urut secara global
    static char lastID[10] = "TRT000"; // Simpan ID terakhir

    FILE *file = fopen(TRANSCFILE, "rb");
    if (file)
    {
        // Cari ID terakhir di file transaksi
        Tiket temp;
        while (fread(&temp, sizeof(Tiket), 1, file))
        {
            if (strncmp(temp.ID, "TRT", 3) == 0)
            {
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

void TambahkanTanggalTransaksi(Tiket *pesanan)
{
    time_t now = time(NULL);
    struct tm *local = localtime(&now);

    pesanan->tanggalTransc.tanggal = local->tm_mday;
    pesanan->tanggalTransc.bulan = local->tm_mon + 1;     // tm_mon dimulai dari 0
    pesanan->tanggalTransc.tahun = local->tm_year + 1900; // tm_year adalah tahun sejak 1900
}

void InvoiceTiket(Tiket *pesanan)
{
    FILE *file = fopen(TRANSCFILE, "ab");
    if (!file)
    {
        TampilkanPesan("Gagal membuka file database.", 2);
        return;
    }

    char key;
    double nominalPembayaran = 0;
    double kembalian = 0;
    int metodePembayaran = 0; // 0: Tunai, 1: E-Wallet, 2: Bank, 3: Lainnya
    const char *metode[] = {"Tunai", "E-Wallet", "Bank", "Lainnya"};
    char catatan[1000] = "";
    int step = 0; // Step untuk navigasi form
    char nominalStr[20] = "";
   
    GenerateTransactionID(pesanan);     // Generate ID dan nomor transaksi
    TambahkanTanggalTransaksi(pesanan); // Tambahkan tanggal transaksi

    while (1)
    {
        system("cls");
        printf("==== Transaksi Tiket ====\n\n");

        // Tampilkan invoice
        printf("ID Transaksi        : %s\n", pesanan->ID);
        printf("No. Transaksi       : %ld\n", pesanan->no);
        printf("Tanggal Transaksi   : %02d/%02d/%04d\n", pesanan->tanggalTransc.tanggal, pesanan->tanggalTransc.bulan, pesanan->tanggalTransc.tahun);
        printf("Film                : %s\n", pesanan->judulFilm);
        printf("Tanggal             : %02d/%02d/%04d\n", pesanan->Tanggal.tanggal, pesanan->Tanggal.bulan, pesanan->Tanggal.tahun);
        printf("Jam                 : %02d:%02d\n", pesanan->jamTayang.jam, pesanan->jamTayang.menit);
        printf("ID Teater           : %s\n", pesanan->IDTeater);
        printf("No Teater           : %d\n", pesanan->Teater);
        printf("Jumlah Tiket        : %d\n", pesanan->tiket);
        printf("Harga Tiket         : Rp. %.2lf\n", pesanan->harga);
        printf("Total Harga         : Rp. %.2lf\n", pesanan->total);
        printf("\n");

        // Step 0: Pilih metode pembayaran
        printf("Metode Pembayaran: ");
        for (int i = 0; i < 4; i++)
        {
            if (i == metodePembayaran && step > 0)
            {
                printf(" #[%s]", metode[i]);
            }
            else if (i == metodePembayaran)
            {
                printf(" >[%s] ", metode[i]);
            }
            else
            {
                printf("  [%s]  ", metode[i]);
            }
        }
        printf("\n");

        printf("Nominal Pembayaran  : Rp.%s %s\n", step == 1 ? ">" : (step > 0 ? "#" : " "), nominalStr);
        printf("Kembalian           : Rp. %.2lf\n", kembalian);
        printf("Catatan             : %s%s\n", step == 2 ? ">" : (step > 2 ? "#" : " "), catatan);
        printf("\nTekan Enter untuk lanjut, Esc untuk keluar.\n");

        // Handle input pengguna
        key = getch();

        if (key == 27) // Esc untuk membatalkan transaksi
        {
            printf("Transaksi dibatalkan.\n");
            fclose(file);
            return;
        }

        if (step == 0)
        {
            if (key == 75) // Panah kiri
            {
                metodePembayaran = (metodePembayaran - 1 + 4) % 4;
            }
            else if (key == 77) // Panah kanan
            {
                metodePembayaran = (metodePembayaran + 1) % 4;
            }
            else if (key == '\r') // Enter untuk lanjut
            {
                step++;
            }
        }
        else if (step == 1)
        {
            if (isdigit(key) || key == '.')
            {
                size_t len = strlen(nominalStr);
                if (len < 9)
                {
                    nominalStr[len] = key;
                    nominalStr [len + 1] = '\0';
                }
            }
            else if (key == 8 && strlen(nominalStr) > 0)
            {
                nominalStr[strlen(nominalStr) - 1] = '\0';
            }
            else if (key == '\r' && ValidasiHarga(nominalStr))
            {
                nominalPembayaran = atof(nominalStr);
                if (nominalPembayaran >= pesanan->total)
                {
                    kembalian = nominalPembayaran - pesanan->total;
                    step++;
                }
                else
                {
                    TampilkanPesan("Uang tidak cukup! Silakan tambah nominal.", 2);
                }
            }
        }
        else if (step == 2)
        {
            if (key == '\r')
            {
                step++;
            }
            else if (key == 8 && strlen(catatan) > 0)
            {
                catatan[strlen(catatan) - 1] = '\0';
            }
            else if (strlen(catatan) < 999 && isprint(key))
            {
                catatan[strlen(catatan)] = key;
                catatan[strlen(catatan) + 1] = '\0';
            }
        }
        else if (step == 3)
        {
            strncpy(pesanan->metodePembayaran, metode[metodePembayaran], sizeof(pesanan->metodePembayaran) - 1);
            pesanan->metodePembayaran[sizeof(pesanan->metodePembayaran) - 1] = '\0';
            strncpy(pesanan->catatan, catatan, sizeof(pesanan->catatan) - 1);
            pesanan->catatan[sizeof(pesanan->catatan) - 1] = '\0';

            int konfirmasi = TombolKonfirmasi("Transaksi", "Konfirmasi", pesanan, "Tiket");
            if (konfirmasi == 1)
            {
                FILE *kursiFile = fopen(SEATDAT, "rb+");
                if (!kursiFile)
                {
                    TampilkanPesan("Gagal membuka file kursi.", 2);
                    fclose(file);
                    return;
                }

                KursiData kursi;
                while (fread(&kursi, sizeof(KursiData), 1, kursiFile))
                {
                    for (int i = 0; i < pesanan->tiket; i++)
                    {
                        if (strcmp(kursi.IDTeater, pesanan->IDTeater) == 0 && strcmp(kursi.ID, pesanan->IDkursi[i]) == 0)
                        {
                            strncpy(kursi.status, "Dipesan", sizeof(kursi.status) - 1);
                            fseek(kursiFile, -sizeof(KursiData), SEEK_CUR);
                            fwrite(&kursi, sizeof(KursiData), 1, kursiFile);
                            break; // Keluar dari loop setelah menemukan kursi yang sesuai
                        }
                    }
                }
                fclose(kursiFile);

                fwrite(pesanan, sizeof(Tiket), 1, file);
                fclose(file);

                TampilkanPesan("Transaksi berhasil disimpan!", 1);
                return;
            }
            else
            {
                TampilkanPesan("Transaksi dibatalkan.\n", 2);
                return;
            }
        }
    }
}