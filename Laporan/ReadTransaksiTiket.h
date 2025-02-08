#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// #define TRANSCFILE "transaksi.dat" // Pastikan ini sesuai dengan nama file yang Anda gunakan
#define MAX_TRANSAKSI 999

void BacaTransTiket();
int BandingkanIDTransaksi(const void *a, const void *b);

void BacaTransTiket()
{
    FILE *file = fopen(TRANSCFILE, "rb");
    if (!file)
    {
        printf("Gagal membuka file %s. Pastikan file tersebut ada.\n", TRANSCFILE);
        return;
    }

    Tiket Trans[MAX_TRANSAKSI];
    int jumlahTransaksi = 0;

    // Membaca semua data dari file
    while (fread(&Trans[jumlahTransaksi], sizeof(Tiket), 1, file))
    {
        jumlahTransaksi++;
    }
    fclose(file);

    // Mengurutkan data berdasarkan ID
    qsort(Trans, jumlahTransaksi, sizeof(Tiket), BandingkanIDTransaksi);

    // Menampilkan tabel
    printf("| %-8s | %-5s | %-10s | %-15s | %-18s| %-10s | %-10s | %-10s | %-9s | %-10s | %-15s | \n",
           "ID", "No", "Tanggal", "Film", "Jadwal Tayang", "No Teater", "QTY Tiket", "Harga Tiket", "Total", "Metode Bayar", "Ket");
    printf("----------------------------------------------------------------------------------------------------\n");

    for (int i = 0; i < jumlahTransaksi; i++)
    {
        printf("| %-8s | %-5ld | %02d/%02d/%04d | %-15s | %02d/%02d/%04d, %02d:%02d | %-10d | %-10d | Rp. %.2lf | Rp. %.2lf | %-10s | %-10s |\n",
               Trans[i].ID, Trans[i].no,
               Trans[i].tanggalTransc.tanggal, Trans[i].tanggalTransc.bulan, Trans[i].tanggalTransc.tahun,
               Trans[i].judulFilm,
               Trans[i].Tanggal.tanggal, Trans[i].Tanggal.bulan, Trans[i].Tanggal.tahun,
               Trans[i].jamTayang.jam, Trans[i].jamTayang.menit,
               Trans[i].Teater, Trans[i].tiket,
               Trans[i].harga, Trans[i].total,
               Trans[i].metodePembayaran, Trans[i].catatan);
    }
    printf("\n\n\n");
}

// Fungsi pembanding untuk qsort berdasarkan ID
int BandingkanIDTransaksi(const void *a, const void *b)
{
    Tiket *TransA = (Tiket *)a;
    Tiket *TransB = (Tiket *)b;

    char prefixA[4], prefixB[4];
    int numberA, numberB;

    sscanf(TransA->ID, "%3s%d", prefixA, &numberA);
    sscanf(TransB->ID, "%3s%d", prefixB, &numberB);

    // Urutkan berdasarkan prefix (TTR)
    int cmp = strcmp(prefixA, prefixB);
    if (cmp != 0)
    {
        return cmp;
    }

    // Jika prefix sama, urutkan berdasarkan nomor ID
    return numberA - numberB;
}
