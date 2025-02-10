#include <stdio.h>
#include <string.h>
#include <stdlib.h>
void ResetKursiPerID();
void ResetKursiPerTeater();

void ResetKursiPerID()
{
    FILE *file = fopen(SEATDAT, "rb+");
    if (!file)
    {
        TampilkanPesan("Gagal membuka file kursi.", 2);
        return;
    }

    char idTeater[10];
    char idKursi[10];
    bool teaterDitemukan = false;
    bool kursiDitemukan = false;

    // Input ID Teater
    printf("\n==== RESET KURSI ====\n");
    printf("1. Masukkan ID Teater: ");
    scanf("%s", idTeater);

    // Input ID Kursi
    printf("2. Masukkan ID Kursi dari ID teater tersebut: ");
    scanf("%s", idKursi);

    KursiData kursi;
    while (fread(&kursi, sizeof(KursiData), 1, file))
    {
        // Cek apakah ID Teater cocok
        if (strcmp(kursi.IDTeater, idTeater) == 0)
        {
            teaterDitemukan = true;

            // Cek apakah ID Kursi cocok
            if (strcmp(kursi.ID, idKursi) == 0)
            {
                kursiDitemukan = true;
                // Reset status kursi menjadi "Tersedia"

                if (kursiDitemukan)
                {

                    int konfirmasi = TombolKonfirmasi("StatusKursi", "PerbaruiPerID", &kursi, "KursiData");

                    if (konfirmasi == 1)
                    {
                        strncpy(kursi.status, "Tersedia", sizeof(kursi.status) - 1);
                        fseek(file, -sizeof(KursiData), SEEK_CUR);  // Kembali ke posisi awal kursi
                        fwrite(&kursi, sizeof(KursiData), 1, file); // Simpan perubahan
                    }
                    else
                    {
                        TampilkanPesan("Reset Status kursi dibatalkan.\n", 2);
                    }
                }
                fclose(file);

                break; // Keluar dari loop setelah update
            }
        }
    }

    // Tampilkan pesan berdasarkan hasil pencarian
    if (!teaterDitemukan)
    {
        TampilkanPesan("ID teater tidak ditemukan!", 2);
    }
    else if (!kursiDitemukan)
    {
        TampilkanPesan("ID kursi tidak ditemukan!", 2);
    }
    else
    {
        TampilkanPesan("Kursi berhasil disegarkan menjadi berstatus 'Tersedia'.", 2);
    }

}void ResetKursiPerTeater()
{
    FILE *file = fopen(SEATDAT, "rb+");
    if (!file)
    {
        TampilkanPesan("Gagal membuka file kursi.", 2);
        return;
    }

    char idTeater[10];
    bool teaterDitemukan = false;
    bool kursiDitemukan = false;

    // Input ID Teater
    printf("\n==== RESET KURSI ====\n");
    printf("1. Masukkan ID Teater: ");
    scanf("%s", idTeater);

    KursiData kursi;
    KursiData kursiUpdate[MAX_BARIS * MAX_KOLOM]; // Asumsi jumlah maksimum kursi
    long posisiFile[MAX_BARIS * MAX_KOLOM]; // Simpan posisi file untuk setiap kursi
    int jumlahKursiUpdate = 0;

    // Pertama, kita akan mencari kursi yang sesuai dengan ID teater
    while (fread(&kursi, sizeof(KursiData), 1, file))
    {
        // Cek apakah ID Teater cocok
        if (strcmp(kursi.IDTeater, idTeater) == 0)
        {
            teaterDitemukan = true;

            // Cek apakah kursi dalam status "Dipesan"
            if (strcmp(kursi.status, "Dipesan") == 0)
            {
                kursiDitemukan = true; // Menandakan bahwa kita menemukan kursi untuk teater ini

                // Reset status kursi menjadi "Tersedia"
                strncpy(kursi.status, "Tersedia", sizeof(kursi.status) - 1);

                // Simpan kursi yang perlu diupdate beserta posisi filenya
                kursiUpdate[jumlahKursiUpdate] = kursi;
                posisiFile[jumlahKursiUpdate] = ftell(file) - sizeof(KursiData); // Simpan posisi file
                jumlahKursiUpdate++;
            }
        }
    }

    // Tampilkan pesan berdasarkan hasil pencarian
    if (!teaterDitemukan)
    {
        TampilkanPesan("ID teater tidak ditemukan!", 2);
    }
    else if (kursiDitemukan)
    {
        // Konfirmasi sebelum menyimpan perubahan
        int konfirmasi = TombolKonfirmasi("StatusKursi", "PerbaruiPerTeater", idTeater, "KursiData");
        if (konfirmasi == 1)
        {
            // Jika konfirmasi diterima, simpan perubahan
            for (int i = 0; i < jumlahKursiUpdate; i++)
            {
                // Pindahkan pointer ke posisi yang sesuai
                fseek(file, posisiFile[i], SEEK_SET);
                // Tulis ulang data kursi yang diupdate
                fwrite(&kursiUpdate[i], sizeof(KursiData), 1, file);
            }
            TampilkanPesan("Kursi berhasil disegarkan menjadi berstatus 'Tersedia'.", 2);
        }
        else
        {
            TampilkanPesan("Reset Status kursi dibatalkan.\n", 2);
        }
    }
    else
    {
        TampilkanPesan("Tidak ada kursi yang berstatus 'Dipesan' untuk ID teater ini.", 2);
    }

    fclose(file); // Tutup file setelah selesai
}