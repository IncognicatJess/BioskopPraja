#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>

typedef struct
{
    int id;
    char nama[50];
    char metode[10];
    char konfir[15];
    char tanggal[15];
    float harga;
    int jumlah;
    float total;
} Listmakanan;

Listmakanan makanan;

void pilihMenu();
void pilihMakanan();
void BacaTransaksiMakanan();
void updateTransaksiMakanan();
void deleteTransaksiMakanan();
void riwayatTransaksi();

float transaksimakanan(Listmakanan makanan)
{
    return makanan.total;
}

float hitungtotal(float harga, int jumlah)
{
    return harga * jumlah;
}

void pilihMetodeMakanan(Listmakanan *makanan)
{
    const char *metodePembayaran[] = {"CASH", "QRIS"};
    int metodePembayaranIndex = 0;
    int step = 0;
    char key;

    while (1)
    {
        system("cls");

        printf("\nMetode Pembayaran\n");
        for (int i = 0; i < 2; i++)
        {
            if (i == metodePembayaranIndex)
            {
                printf(" > \033[48;2;62;254;255m %s \033[0m \n", metodePembayaran[i]); // Sorot pilihan
            }
            else
            {
                printf("   %s\n", metodePembayaran[i]);
            }
        }
        printf("\nGunakan panah kiri/kanan untuk navigasi, Enter untuk konfirmasi.\n");

        key = getch();
        if (key == 72)
            metodePembayaranIndex = (metodePembayaranIndex - 1 + 2) % 2;
        else if (key == 80)
            metodePembayaranIndex = (metodePembayaranIndex + 1) % 2;
        else if (key == '\r') // Enter
        {
            strncpy(makanan->metode, metodePembayaran[metodePembayaranIndex], sizeof(makanan->metode) - 1);
            break;
        }
    }
}

void konfirmasiPembayaran(Listmakanan *makanan)
{
    const char *konfirmasiPembayaran[] = {"KONFIRMASI", "BATALKAN"};
    int konfirmasiPembayaranIndex = 0;
    char konfir;
    int step = 0;
    char key;

    while (1)
    {
        system("cls");

        printf("\nKonfirmasi Pembayaran\n");
        for (int i = 0; i < 2; i++)
        {
            if (i == konfirmasiPembayaranIndex)
            {
                printf(" > \033[48;2;62;254;255m %s \033[0m \n", konfirmasiPembayaran[i]); // Sorot pilihan
            }
            else
            {
                printf("   %s\n", konfirmasiPembayaran[i]);
            }
        }
        printf("\nGunakan panah kiri/kanan untuk navigasi, Enter untuk konfirmasi.\n");

        key = getch();
        if (key == 72)
            konfirmasiPembayaranIndex = (konfirmasiPembayaranIndex - 1 + 2) % 2;
        else if (key == 80)
            konfirmasiPembayaranIndex = (konfirmasiPembayaranIndex + 1) % 2;
        else if (key == '\r') // Enter
        {
            strcpy(makanan->konfir, konfirmasiPembayaran[konfirmasiPembayaranIndex]);
            break;
        }
    }
}

int lastid(const char *filename)
{
    FILE *file = fopen(filename, "rb");
    if (file == NULL)
    {
        return 0; // Jika file tidak ada, ID mulai dari 0
    }

    Listmakanan temp;
    int idTerakhir = 0;

    // Baca setiap data dalam file untuk menemukan ID terbesar
    while (fread(&temp, sizeof(Listmakanan), 1, file))
    {
        if (temp.id > idTerakhir)
        {
            idTerakhir = temp.id;
        }
    }

    fclose(file);
    return idTerakhir;
}

void pilihMenu()
{
    int pilihan = 0;
    int jumlahPilihan = 6;
    char key;
    const char *menu[] = {
        "BUAT TRANSAKSI",
        "LIHAT TRANSAKSI",
        "UPDATE TRANSAKSI",
        "HAPUS TRANSAKSI",
        "RIWAYAT TRANSAKSI",
        "KELUAR DARI MENU"};

    do
    {
        // Clear screen
        system("cls");

        printf("\n=============================\n");
        printf("   TRANSAKSI BIOSKOP PRAJA\n");
        printf("=============================\n");

        // Cetak menu dengan highlighting
        for (int i = 0; i < jumlahPilihan; i++)
        {
            if (i == pilihan)
            {
                // Highlight opsi yang dipilih
                printf(" > \033[48;2;62;254;255m %s \033[0m \n", menu[i]);
            }
            else
            {
                printf("   %s\n", menu[i]);
            }
        }

        printf("=============================\n");
        printf("Gunakan panah atas/bawah untuk memilih, dan tekan Enter untuk memilih.\n");

        // Ambil input tombol
        key = getch();
        if (key == 72)
        { // Panah atas
            pilihan = (pilihan - 1 + 6) % 6;
        }
        else if (key == 80)
        { // Panah bawah
            pilihan = (pilihan + 1) % 6;
        }
        else if (key == '\r')
        { // Enter
            system("cls");
            switch (pilihan)
            {
            case 0:
                pilihMakanan();
                break;
            case 1:
                BacaTransaksiMakanan("Makanan.dat");
                break;
            case 2:
                updateTransaksiMakanan();
                break;
            case 3:
                deleteTransaksiMakanan();
                break;
            case 4:
                riwayatTransaksi();
                break;
            case 5:
                printf("Terima kasih! Anda telah keluar dari program.\n");
                exit(0);
            }
            printf("Tekan sembarang tombol untuk kembali ke menu...\n");
            getch();
        }
    } while (1);
}

void pilihMakanan()
{
    FILE *Transaksimakanan = fopen("Makanan.dat", "ab");
    if (Transaksimakanan == NULL)
    {
        printf("Gagal membuka file.\n");
        return;
    }

    int makananIndex = 0;
    const char *namaMakanan[] = {"Popcorn", "Kentang", "Sosis"};
    float hargaMakanan[] = {40000, 40000, 40000};
    char key;

    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    strftime(makanan.tanggal, 20, "%d-%m-%Y %H:%M", tm);

    int idTerakhir = lastid("Makanan.dat");
    makanan.id = idTerakhir + 1;

    while (1)
    {
        system("cls");
        printf("\n=== Memilih Makanan ===\n");
        for (int i = 0; i < 3; i++)
        {
            if (i == makananIndex)
            {
                // Highlight opsi yang dipilih
                printf(" > \033[48;2;62;254;255m %s - Rp. %.2f \033[0m \n", namaMakanan[i], hargaMakanan[i]);
            }
            else
            {
                printf("   %s\n", namaMakanan[i], hargaMakanan[i]);
            }
        }

        key = getch();
        if (key == 72)
        { // Panah atas
            makananIndex = (makananIndex - 1 + 3) % 3;
        }
        else if (key == 80)
        { // Panah bawah
            makananIndex = (makananIndex + 1) % 3;
        }
        else if (key == 13)
        { // Enter
            break;
        }
    }

    strcpy(makanan.nama, namaMakanan[makananIndex]);
    makanan.harga = hargaMakanan[makananIndex];

    printf("\nID                 : TRSM 00%d\n", makanan.id);
    printf("Nama Makanan       : %s\n", makanan.nama);
    printf("Harga              : Rp. %.2f\n", makanan.harga);
    printf("Jumlah yang Dibeli : ");
    scanf("%d", &makanan.jumlah);

    makanan.total = hitungtotal(makanan.harga, makanan.jumlah);
    printf("Total Harga        : Rp. %.2f\n", makanan.total);

    pilihMetodeMakanan(&makanan);
    konfirmasiPembayaran(&makanan);
    printf("Tanggal           : %s\n", makanan.tanggal);

    fwrite(&makanan, sizeof(Listmakanan), 1, Transaksimakanan);
    fclose(Transaksimakanan);
}

void BacaTransaksiMakanan(const char *filename)
{
    FILE *Transaksimakanan = fopen("Makanan.dat", "rb");
    if (Transaksimakanan == NULL)
    {
        printf("Error: Tidak dapat membuka file %s\n", filename);
        return;
    }

    int found = 0;

    printf("\n=== Transaksi Makanan ===\n");
    while (fread(&makanan, sizeof(makanan), 1, Transaksimakanan) == 1)
        found = 1;
    printf("ID Makanan         : TRSM 00%d\n", makanan.id);
    printf("Nama Makanan       : %s\n", makanan.nama);
    printf("Harga              : Rp. %.2f\n", makanan.harga);
    printf("Jumlah yang Dibeli : %d\n", makanan.jumlah);
    printf("Total Harga        : Rp. %.2f\n", makanan.total);
    printf("Metode Pembayaran  : %s\n", makanan.metode);
    printf("Status Pembayaran  : %s\n", makanan.konfir);
    printf("Tanggal Transaksi  : %s\n", makanan.tanggal);
    printf("----------------------------\n");

    if (!found)
    {
        printf("Tidak ada transaksi makanan ditemukan.\n");
    }

    fclose(Transaksimakanan);
}

void updateTransaksiMakanan()
{
    FILE *Transaksimakanan = fopen("Makanan.dat", "rb+");
    int id, found = 0;

    if (Transaksimakanan == NULL)
    {
        printf("Gagal membuka file.\n");
        return;
    }

    printf("\n=== Update Transaksi Makanan ===\n");
    printf("Masukkan ID transaksi yang ingin diupdate: ");
    scanf("%d", &id);

    while (fread(&makanan, sizeof(Listmakanan), 1, Transaksimakanan))
    {
        if (id == makanan.id)
        {
            found = 1;
            printf("\nData Ditemukan!\n");
            printf("ID                 : TRSM 00%d\n", makanan.id);
            printf("Nama Makanan       : %s\n", makanan.nama);
            printf("Harga              : Rp. %.2f\n", makanan.harga);
            printf("Jumlah yang Dibeli : %d\n", makanan.jumlah);
            printf("Total Harga        : Rp. %.2f\n", makanan.total);
            printf("Metode Pembayaran  : %s\n", makanan.metode);

            // Input data baru
            printf("Masukkan Jumlah yang Dibeli: ");
            scanf("%d", &makanan.jumlah);
            makanan.total = hitungtotal(makanan.harga, makanan.jumlah);
            printf("Total Harga Baru : Rp. %.2f\n", makanan.total);
            konfirmasiPembayaran(&makanan);

            fseek(Transaksimakanan, -sizeof(Listmakanan), SEEK_CUR);
            fwrite(&makanan, sizeof(Listmakanan), 1, Transaksimakanan);
            printf("\nTransaksi berhasil diupdate.\n");
            break;
        }
    }

    if (!found)
    {
        printf("Transaksi dengan ID %d tidak ditemukan.\n", id);
    }

    fclose(Transaksimakanan);
}

void deleteTransaksiMakanan()
{
    FILE *Transaksimakanan, *TempFile;
    Listmakanan makanan;
    int cariID;
    int found = 0;

    Transaksimakanan = fopen("Makanan.dat", "rb");
    if (Transaksimakanan == NULL)
    {
        printf("Gagal membuka file.\n");
        return;
    }

    TempFile = fopen("Temp.dat", "wb");
    if (TempFile == NULL)
    {
        printf("Gagal membuat file sementara.\n");
        fclose(Transaksimakanan);
        return;
    }

    printf("\n=== Hapus Transaksi Makanan ===\n");
    printf("Masukkan ID Transaksi Makanan yang Ingin Dihapus : ");
    scanf("%d", &cariID);

    while (fread(&makanan, sizeof(Listmakanan), 1, Transaksimakanan) == 1)
    {
        if (makanan.id != cariID)
        {
            fwrite(&makanan, sizeof(Listmakanan), 1, TempFile);
        }
        else
        {
            found = 1;
        }
    }

    fclose(Transaksimakanan);
    fclose(TempFile);

    if (found)
    {
        remove("Makanan.dat");             // Hapus file asli
        rename("Temp.dat", "Makanan.dat"); // Gantikan dengan file sementara
        printf("\nData berhasil dihapus!\n");
    }
    else
    {
        remove("Temp.dat"); // Hapus file sementara jika tidak ada data yang dihapus
        printf("\nData dengan ID %d tidak ditemukan.\n", cariID);
    }
}

void riwayatTransaksi()
{
    FILE *Transaksimakanan = fopen("Makanan.dat", "rb");
    if (Transaksimakanan == NULL)
    {
        printf("Gagal membuka file.\n");
        return;
    }

    Listmakanan makanan;
    printf("======================================================================================================================================\n");
    printf("%*s\n", 65, "DAFTAR TRANSAKSI F&B");
    printf("======================================================================================================================================\n");
    printf("| %-5s     | %-10s       | %-10s | %-10s    | %-10s | %-10s    | %-10s | %-15s |\n", "ID", "Tanggal", "Nama Menu", "Harga", "Jumlah Makanan", "Total Harga", "Metode Pembayaran", "Status Pembayaran");
    printf("--------------------------------------------------------------------------------------------------------------------------------------\n");

    while (fread(&makanan, sizeof(Listmakanan), 1, Transaksimakanan) == 1)
    {
        printf("| TRSM 00%-2d | %-10s | %-10s | Rp %-10.2f | %-10d     | Rp %-10.2f  | %-10s       | %-15s    |\n",
               makanan.id, makanan.tanggal, makanan.nama, makanan.harga, makanan.jumlah, makanan.total, makanan.metode, makanan.konfir);
    }
    printf("======================================================================================================================================\n");

    fclose(Transaksimakanan);
}

int main()
{
    pilihMenu();
    printf("\nTransaksi selesai. Terima kasih!\n");
    return 0;
}