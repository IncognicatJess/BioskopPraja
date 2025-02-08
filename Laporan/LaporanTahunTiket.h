
void BacaTransTiketBerdasarkanTahun();

void BacaTransTiketBerdasarkanTahun()
{
    int tahun = 0;
    char inputTahun[5] = {0}; // Buffer untuk tahun

    // Input tahun
    printf("Masukkan tahun: ");
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
    tahun = atoi(inputTahun);

    FILE *file = fopen(TRANSCFILE, "rb");
    if (!file)
    {
        printf("Gagal membuka file %s. Pastikan file tersebut ada.\n", TRANSCFILE);
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

    double totalTahunIni = 0.0;
    double totalTahunSebelumnya = 0.0;
    int foundTahunIni = 0;
    int foundTahunSebelumnya = 0;

    printf("\n\n");
    system("cls");
    // Menampilkan tabel
    printf("| %-8s | %-5s | %-10s | %-15s | %-15s | %-10s | %-10s | %-10s | %-10s | %-10s | %-10s | %-10s | \n",
           "ID", "No", "Tanggal", "Film", "Jadwal Tayang", "ID Teater", "No Teater", "Jumlah Tiket", "Harga Tiket", "Total Bayar", "Metode Pembayaran", "Catatan");
    printf("----------------------------------------------------------------------------------------------------\n");

    for (int i = 0; i < jumlahTransaksi; i++)
    {
        if (Trans[i].tanggalTransc.tahun == tahun)
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
            totalTahunIni += Trans[i].total;
            foundTahunIni = 1; // Menandakan bahwa transaksi tahun ini ditemukan
        }
    }

    if (!foundTahunIni)
    {
        printf("Tidak ada transaksi ditemukan untuk tahun %d.\n", tahun);
        sleep(2);
    }
    else
    {
        printf("Total transaksi tahun %d: Rp. %.2lf\n", tahun, totalTahunIni);
        sleep(2);
    }

    // Menghitung total tahun sebelumnya
    tahun--;

    for (int i = 0; i < jumlahTransaksi; i++)
    {
        if (Trans[i].tanggalTransc.tahun == tahun)
        {
            totalTahunSebelumnya += Trans[i].total;
            foundTahunSebelumnya = 1; // Menandakan bahwa transaksi tahun sebelumnya ditemukan
        }
    }

    if (foundTahunSebelumnya)
    {
        double yoyChange = ((totalTahunIni - totalTahunSebelumnya) / totalTahunSebelumnya) * 100;

        printf("Total transaksi tahun sebelumnya: Rp. %.2lf\n", totalTahunSebelumnya);
        printf("YoY Change: %.2lf%%\n", yoyChange);

        if (totalTahunIni < totalTahunSebelumnya)
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
        printf("YoY Change & Laba-Rugi: Belum ada data dari bulan sebelumnya.\n");
    }
    getchar();
    getchar();

    printf("\n\n\n");
}