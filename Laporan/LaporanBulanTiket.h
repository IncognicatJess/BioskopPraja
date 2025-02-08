#define MAX_TRANS 1000

void BacaTransTiketBerdasarkanBulan();
//int BandingkanID(const void *a, const void *b);

void BacaTransTiketBerdasarkanBulan()
{
    int bulan = 0, tahun = 0;
    char inputBulan[5] = {0}; // Buffer untuk bulan
    char inputTahun[5] = {0}; // Buffer untuk tahun

    // Input bulan
    printf("Masukkan bulan (1-12): ");
    int i = 0;
    while (1)
    {
        char ch = getch(); // Ambil input karakter per karakter

        if (ch == 27)
        { // Jika tombol "Esc" ditekan
            printf("\nPencarian dibatalkan.\n");
            return; // Keluar dari fungsi
        }
        else if (ch == '\r')
        {                         // Jika tombol "Enter" ditekan
            inputBulan[i] = '\0'; // Akhiri string
            break;
        }
        else if (ch == 8 && i > 0)
        { // Jika tombol "Backspace" ditekan
            i--;
            printf("\b \b"); // Hapus karakter terakhir dari layar
        }
        else if (i < 4 && (isdigit(ch) || ch == ','))
        { // Hanya terima angka atau koma
            inputBulan[i++] = ch;
            putchar(ch); // Tampilkan karakter ke layar
        }
    }

    // Input tahun
    printf("\nMasukkan tahun: ");
    i = 0;
    while (1)
    {
        char ch = getch(); // Ambil input karakter per karakter

        if (ch == 27)
        { // Jika tombol "Esc" ditekan
            TampilkanPesan("\nPencarian dibatalkan.\n",2);

            return; // Keluar dari fungsi
        }
        else if (ch == '\r')
        {                         // Jika tombol "Enter" ditekan
            inputTahun[i] = '\0'; // Akhiri string
            break;
        }
        else if (ch == 8 && i > 0)
        { // Jika tombol "Backspace" ditekan
            i--;
            printf("\b \b"); // Hapus karakter terakhir dari layar
        }
        else if (i < 4 && isdigit(ch))
        { // Hanya terima angka
            inputTahun[i++] = ch;
            putchar(ch); // Tampilkan karakter ke layar
        }
    }

    // Konversi input ke integer
    bulan = atoi(inputBulan);
    tahun = atoi(inputTahun);

    // Validasi bulan dan tahun
    if (bulan < 1 || bulan > 12)
    {
        TampilkanPesan("\nBulan tidak valid. Harap masukkan bulan antara 1 dan 12.\n",2);
        return;
    }

    FILE *file = fopen(TRANSCFILE, "rb");
    if (!file)
    {
        printf("Gagal membuka file %s. Pastikan file tersebut ada.\n", TRANSCFILE);
        sleep(2);
        return;
    }

    Tiket Trans[MAX_TRANS];
    int jumlahTransaksi = 0;

    // Membaca semua data dari file
    while (fread(&Trans[jumlahTransaksi], sizeof(Tiket), 1, file))
    {
        jumlahTransaksi++;
    }
    fclose(file);

    double totalBulanIni = 0.0;
    double totalBulanSebelumnya = 0.0;
    int foundBulanIni = 0;
    int foundBulanSebelumnya = 0;

    printf("\n\n");
    system("cls");
    // Menampilkan tabel
    printf("| %-8s | %-5s | %-10s | %-15s | %-15s | %-10s | %-10s | %-10s | %-10s | %-10s | %-10s | %-10s | \n",
           "ID", "No", "Tanggal", "Film", "Jadwal Tayang", "ID Teater", "No Teater", "Jumlah Tiket", "Harga Tiket", "Total Bayar", "Metode Pembayaran", "Catatan");
    printf("----------------------------------------------------------------------------------------------------\n");

    for (int i = 0; i < jumlahTransaksi; i++)
    {
        if (Trans[i].tanggalTransc.bulan == bulan && Trans[i].tanggalTransc.tahun == tahun)
        {
            printf("| %-8s | %-5ld | %02d/%02d/%04d | %-15s | %02d/%02d/%04d, %02d:%02d | %-10s | %-10d | %-10d | Rp. %.2lf | Rp. %.2lf | %-10s | %-10s |\n",
                   Trans[i].ID, Trans[i].no,
                   Trans[i].tanggalTransc.tanggal, Trans[i].tanggalTransc.bulan, Trans[i].tanggalTransc.tahun,
                   Trans[i].judulFilm,
                   Trans[i].Tanggal.tanggal, Trans[i].Tanggal.bulan, Trans[i].Tanggal.tahun,
                   Trans[i].jamTayang.jam, Trans[i].jamTayang.menit,
                   Trans[i].IDTeater, Trans[i].Teater, Trans[i].tiket,
                   Trans[i].harga, Trans[i].total,
                   Trans[i].metodePembayaran, Trans[i].catatan);
            totalBulanIni += Trans[i].total;
            foundBulanIni = 1; // Menandakan bahwa transaksi bulan ini ditemukan
        }
    }

    if (!foundBulanIni)
    {
        printf("Tidak ada transaksi ditemukan untuk bulan %d dan tahun %d.\n", bulan, tahun);
        sleep(2);
    }
    else
    {
        printf("Total transaksi bulan %d tahun %d: Rp. %.2lf\n", bulan, tahun, totalBulanIni);
        sleep(2);
    }

    // Menghitung total bulan sebelumnya
    if (bulan == 1)
    {
        bulan = 12;
        tahun--;
    }
    else
    {
        bulan--;
    }

    for (int i = 0; i < jumlahTransaksi; i++)
    {
        if (Trans[i].tanggalTransc.bulan == bulan && Trans[i].tanggalTransc.tahun == tahun)
        {
            totalBulanSebelumnya += Trans[i].total;
            foundBulanSebelumnya = 1; // Menandakan bahwa transaksi bulan sebelumnya ditemukan
        }
    }

    if (foundBulanSebelumnya)
    {
        double labaRugi = totalBulanIni - totalBulanSebelumnya;
        double momChange = (labaRugi / totalBulanSebelumnya) * 100;

        printf("Total transaksi bulan sebelumnya: Rp. %.2lf\n", totalBulanSebelumnya);
        printf("Laba-Rugi: Rp. %.2lf\n", labaRugi);
        printf("MoM Change: %.2lf%%\n", momChange);

        if (labaRugi < 0)
        {
            printf("Penjualan mengalami penurunan.\n");
        }
        else
        {
            printf("Penjualan mengalami peningkatan.\n");
        }
    }
    else
    {
        printf("MoM Change & Laba-Rugi: Belum ada data dari bulan sebelumnya.\n");
    }

    getchar();
    getchar();
    printf("\n\n\n");
}