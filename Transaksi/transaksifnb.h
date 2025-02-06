void pilihMenu();
void pilihMakanan();
void BacaTransaksiMakanan(const char *filename);
void updateTransaksiMakanan();
void deleteTransaksiMakanan();
void riwayatTransaksi();
float hitungtotal(float harga, int jumlah);
void pilihMetodeMakanan(ListMakanan *makanan);
void konfirmasiPembayaran(ListMakanan *makanan);
int lastid(const char *filename);
void simpanTransaksi(ListMakanan *makanan);
void tampilkanTransaksi(ListMakanan *makanan);
int DashboardUserFnb(AkunData *akun);

ListMakanan makanan;
FnbData menu;

int TransaksiMakanan()
{
    pilihMenu();
    return 0;
}

float transaksimakanan(ListMakanan makanan)
{
    return makanan.total;
}

float hitungtotal(float harga, int jumlah)
{
    return harga * jumlah;
}

void pilihMetodeMakanan(ListMakanan *makanan)
{
    const char *metodePembayaran[] = {"CASH", "QRIS"};
    int metodePembayaranIndex = 0;
    char key;

    while (1)
    {
        system("cls");
        printf("\nMetode Pembayaran\n");
        for (int i = 0; i < 2; i++)
        {
            if (i == metodePembayaranIndex)
            {
                printf(" > \033[48;2;62;254;255m %s \033[0m \n", metodePembayaran[i]);
            }
            else
            {
                printf("   %s\n", metodePembayaran[i]);
            }
        }
        printf("\nGunakan panah kiri/kanan untuk navigasi, Enter untuk konfirmasi.\n");

        key = getch();
        if (key == 72) // Panah atas
            metodePembayaranIndex = (metodePembayaranIndex - 1 + 2) % 2;
        else if (key == 80) // Panah bawah
            metodePembayaranIndex = (metodePembayaranIndex + 1) % 2;
        else if (key == '\r')
        { // Enter
            strncpy(makanan->metode, metodePembayaran[metodePembayaranIndex], sizeof(makanan->metode) - 1);
            break;
        }
    }
}

void konfirmasiPembayaran(ListMakanan *makanan)
{
    const char *konfirmasiPembayaran[] = {"KONFIRMASI", "BATALKAN"};
    int konfirmasiPembayaranIndex = 0;
    char key;

    while (1)
    {
        system("cls");
        printf("\n=== Konfirmasi Data yang Diinput ===\n");
        printf("ID Transaksi      : TRSM 00%d\n", makanan->id);
        printf("Nama Makanan      : %s\n", menu.namaMakanan);
        printf("Harga             : Rp. %.2f\n", menu.harga);
        printf("Jumlah Dibeli     : %d\n", makanan->jumlah);
        printf("Total Harga       : Rp. %.2f\n", makanan->total);
        printf("Metode Pembayaran : %s\n", makanan->metode);
        printf("Tanggal           : %s\n", makanan->tanggal);

        printf("\nKonfirmasi Pembayaran\n");
        for (int i = 0; i < 2; i++)
        {
            if (i == konfirmasiPembayaranIndex)
            {
                printf(" > \033[48;2;62;254;255m %s \033[0m \n", konfirmasiPembayaran[i]);
            }
            else
            {
                printf("   %s\n", konfirmasiPembayaran[i]);
            }
        }
        printf("\nGunakan panah kiri/kanan untuk navigasi, Enter untuk konfirmasi.\n");

        key = getch();
        if (key == 72) // Panah atas
            konfirmasiPembayaranIndex = (konfirmasiPembayaranIndex - 1 + 2) % 2;
        else if (key == 80) // Panah bawah
            konfirmasiPembayaranIndex = (konfirmasiPembayaranIndex + 1) % 2;
        else if (key == '\r')
        { // Enter
            strcpy(makanan->konfir, konfirmasiPembayaran[konfirmasiPembayaranIndex]);
            if (konfirmasiPembayaranIndex = 1)
            {
                return;
            }

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

    ListMakanan temp;
    int idTerakhir = 0;

    while (fread(&temp, sizeof(ListMakanan), 1, file))
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
        system("cls");
        printf("\n=============================\n");
        printf("   TRANSAKSI BIOSKOP PRAJA\n");
        printf("=============================\n");

        for (int i = 0; i < jumlahPilihan; i++)
        {
            if (i == pilihan)
            {
                printf(" > \033[48;2;62;254;255m %s \033[0m \n", menu[i]);
            }
            else
            {
                printf("   %s\n", menu[i]);
            }
        }

        printf("=============================\n");
        printf("Gunakan panah atas/bawah untuk memilih, dan tekan Enter untuk memilih.\n");

        key = getch();
        if (key == 72) // Panah atas
            pilihan = (pilihan - 1 + 6) % 6;
        else if (key == 80) // Panah bawah
            pilihan = (pilihan + 1) % 6;
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
                return;
            }
            printf("Tekan sembarang tombol untuk kembali ke menu...\n");
            getch();
        }
    } while (1);
}

void pilihMakanan()
{
    FILE *fileMakanan = fopen(FILEMENU, "rb+"); // Buka file dalam mode baca dan tulis
    if (fileMakanan == NULL)
    {
        printf("Gagal membuka file Makanan.dat\n");
        return;
    }

    FnbData daftarMakanan[100]; // Maksimal 100 makanan
    int jumlahMakanan = 0;

    while (fread(&daftarMakanan[jumlahMakanan], sizeof(FnbData), 1, fileMakanan) == 1)
    {
        jumlahMakanan++;
    }

    if (jumlahMakanan == 0)
    {
        printf("Tidak ada data makanan tersedia.\n");
        fclose(fileMakanan);
        return;
    }

    int makananIndex = 0;
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
        printf("-----------------------------------------------------------------------------------------------\n");
        printf("| %-8s | %-20s | %-15s | %-10s | %-13s | %-10s |\n",
               "ID", "Nama", "Kategori", "Stok", "Harga (Rp)", "Status");
        printf("-----------------------------------------------------------------------------------------------\n");

        for (int i = 0; i < jumlahMakanan; i++)
        {
            char status[20];
            if (daftarMakanan[i].stok > 0)
            {
                strncpy(status, "Tersedia", sizeof(status) - 1);
            }
            else
            {
                strncpy(status, "Habis", sizeof(status) - 1);
            }

            printf("| %-8s | %-20s | %-15s | %-10d | %-13.0f | %-10s |\n",
                   daftarMakanan[i].ID, daftarMakanan[i].namaMakanan, daftarMakanan[i].kategori, daftarMakanan[i].stok, daftarMakanan[i].harga, status);
        }
        printf("-----------------------------------------------------------------------------------------------\n");
        printf("\n");

        for (int i = 0; i < jumlahMakanan; i++)
        {
            if (i == makananIndex)
            {
                printf(" > \033[48;2;62;254;255m %s\033[0m <\n",
                       daftarMakanan[i].namaMakanan);
            }
            else
            {
                printf("   %s\n", daftarMakanan[i].namaMakanan);
            }
        }

        key = getch();
        if (key == 72) // Panah atas
            makananIndex = (makananIndex - 1 + jumlahMakanan) % jumlahMakanan;
        else if (key == 80) // Panah bawah
            makananIndex = (makananIndex + 1) % jumlahMakanan;
        else if (key == 13) // Enter
            break;
    }

    // Menyimpan pilihan makanan
    strncpy(menu.namaMakanan, daftarMakanan[makananIndex].namaMakanan, sizeof(menu.namaMakanan) - 1);
    menu.harga = daftarMakanan[makananIndex].harga;

    printf("\nID                 : TRSM00%d\n", makanan.id);
    printf("Nama Makanan       : %s\n", menu.namaMakanan);
    printf("Harga              : Rp. %.2f\n", menu.harga);
    printf("Jumlah yang Dibeli : ");
    scanf("%d", &makanan.jumlah);

    // Cek apakah stok mencukupi
    if (makanan.jumlah > daftarMakanan[makananIndex].stok)
    {
        printf("Stok tidak mencukupi! Hanya ada %d item tersedia.\n", daftarMakanan[makananIndex].stok);
        fclose(fileMakanan);
        return;
    }

    makanan.total = hitungtotal(menu.harga, makanan.jumlah);
    printf("Total Harga        : Rp. %.2f\n", makanan.total);

    pilihMetodeMakanan(&makanan);
    konfirmasiPembayaran(&makanan);
    printf("Tanggal           : %s\n", makanan.tanggal);

    // Hanya kurangi stok jika transaksi dikonfirmasi
    if (strcmp(makanan.konfir, "KONFIRMASI") == 0)
    {
        // Kurangi stok makanan
        daftarMakanan[makananIndex].stok -= makanan.jumlah;

        // Simpan perubahan stok kembali ke file
        fseek(fileMakanan, 0, SEEK_SET); // Kembali ke awal file
        for (int i = 0; i < jumlahMakanan; i++)
        {
            fwrite(&daftarMakanan[i], sizeof(FnbData), 1, fileMakanan);
        }
    }

    // Simpan transaksi ke file
    simpanTransaksi(&makanan);
    fclose(fileMakanan);
}

void simpanTransaksi(ListMakanan *makanan)
{
    FILE *Transaksimakanan = fopen("Makanan.dat", "ab");
    if (Transaksimakanan == NULL)
    {
        printf("Gagal membuka file untuk menyimpan transaksi.\n");
        return;
    }
    fwrite(makanan, sizeof(ListMakanan), 1, Transaksimakanan);
    fclose(Transaksimakanan);
}

void BacaTransaksiMakanan(const char *filename)
{
    FILE *Transaksimakanan = fopen(filename, "rb");
    if (Transaksimakanan == NULL)
    {
        printf("Error: Tidak dapat membuka file %s\n", filename);
        return;
    }

    // Baca data makanan dari FILEMENU
    FILE *fileMakanan = fopen(FILEMENU, "rb");
    if (fileMakanan == NULL)
    {
        printf("Error: Tidak dapat membuka file makanan.\n");
        fclose(Transaksimakanan);
        return;
    }

    FnbData daftarMakanan[100]; // Array untuk menyimpan data makanan
    int jumlahMakanan = 0;

    // Baca semua data makanan dari file
    while (fread(&daftarMakanan[jumlahMakanan], sizeof(FnbData), 1, fileMakanan) == 1)
    {
        jumlahMakanan++;
    }
    fclose(fileMakanan);

    ListMakanan makanan;
    int found = 0;

    printf("\n=== Daftar Transaksi Makanan ===\n");
    printf("===============================================================================================================================\n");
    printf("| %-8s | %-15s  | %-20s | %-12s | %-7s | %-14s | %-10s | %-15s |\n",
           "ID", "Tanggal", "Nama Menu", "Harga", "Jumlah", "Total Harga", "Metode", "Status");
    printf("-------------------------------------------------------------------------------------------------------------------------------\n");

    // Baca semua transaksi dari file
    while (fread(&makanan, sizeof(ListMakanan), 1, Transaksimakanan) == 1)
    {
        found = 1;

        // Cari data makanan yang sesuai dengan transaksi
        FnbData *menu = NULL;
        for (int i = 0; i < jumlahMakanan; i++)
        {
            if (strcmp(makanan.nama, daftarMakanan[i].namaMakanan) == 0)
            {
                menu = &daftarMakanan[i];
                break;
            }
        }

        // Jika data makanan ditemukan, tampilkan informasi
        if (menu != NULL)
        {
            printf("| TRSM00%-8d | %-15s | %-20s | Rp %-9.2f | %-7d | Rp %-11.2f | %-10s | %-15s |\n",
                   makanan.id, makanan.tanggal, menu->namaMakanan, menu->harga, makanan.jumlah, makanan.total, makanan.metode, makanan.konfir);
        }
        else
        {
            printf("| TRSM00%-2d | %-15s | %-20s | Rp %-9.2f | %-7d | Rp %-11.2f | %-10s | %-15s |\n",
                   makanan.id, makanan.tanggal, "Tidak Ditemukan", 0.0, makanan.jumlah, makanan.total, makanan.metode, makanan.konfir);
        }
    }

    if (!found)
    {
        printf("Tidak ada transaksi makanan ditemukan.\n");
    }

    printf("===============================================================================================================================\n");

    if (!found)
    {
        printf("Tidak ada transaksi makanan ditemukan.\n");
    }

    printf("===============================================================================================================================\n");

    fclose(Transaksimakanan);
}

void updateTransaksiMakanan()
{
    FILE *Transaksimakanan = fopen("Makanan.dat", "rb+");
    FILE *fileMakanan = fopen(FILEMENU, "rb+"); // Buka file makanan untuk memperbarui stok
    int id, found = 0;

    if (Transaksimakanan == NULL || fileMakanan == NULL)
    {
        printf("Gagal membuka file.\n");
        return;
    }

    printf("\n=== Update Transaksi Makanan ===\n");
    printf("Masukkan ID transaksi yang ingin diupdate: ");
    printf("TRSM");
    scanf("%d", &id);

    while (fread(&makanan, sizeof(ListMakanan), 1, Transaksimakanan))
    {
        if (id == makanan.id)
        {
            found = 1;
            printf("\nData Ditemukan!\n");
            tampilkanTransaksi(&makanan);

            // Simpan jumlah sebelumnya
            int jumlahSebelumnya = makanan.jumlah;

            // Input data baru
            printf("Masukkan Jumlah yang Dibeli: ");
            scanf("%d", &makanan.jumlah);
            makanan.total = hitungtotal(menu.harga, makanan.jumlah);
            printf("Total Harga Baru : Rp. %.2f\n", makanan.total);
            konfirmasiPembayaran(&makanan);

            // Hitung perubahan stok
            int perubahanStok = makanan.jumlah - jumlahSebelumnya;

            // Update stok di file makanan
            FnbData daftarMakanan[100];
            int jumlahMakanan = 0;

            // Baca semua data makanan dari file
            while (fread(&daftarMakanan[jumlahMakanan], sizeof(FnbData), 1, fileMakanan) == 1)
            {
                jumlahMakanan++;
            }

            // Temukan makanan yang sesuai dan perbarui stok
            for (int i = 0; i < jumlahMakanan; i++)
            {
                if (strcmp(makanan.nama, daftarMakanan[i].namaMakanan) == 0)
                {
                    daftarMakanan[i].stok -= perubahanStok; // Update stok
                    break;
                }
            }

            // Simpan kembali data makanan ke file
            fseek(fileMakanan, 0, SEEK_SET);
            for (int i = 0; i < jumlahMakanan; i++)
            {
                fwrite(&daftarMakanan[i], sizeof(FnbData), 1, fileMakanan);
            }

            // Update transaksi
            fseek(Transaksimakanan, -sizeof(ListMakanan), SEEK_CUR);
            fwrite(&makanan, sizeof(ListMakanan), 1, Transaksimakanan);
            printf("\nTransaksi berhasil diupdate.\n");
            break;
        }
    }

    if (!found)
    {
        printf("Transaksi dengan ID %d tidak ditemukan.\n", id);
    }

    fclose(Transaksimakanan);
    fclose(fileMakanan);
}

void deleteTransaksiMakanan()
{
    FILE *Transaksimakanan, *TempFile;
    ListMakanan makanan;
    int cariID;
    int found = 0;
    char ulangi;

    do
    {
        // Buka file transaksi
        Transaksimakanan = fopen("Makanan.dat", "rb");
        if (Transaksimakanan == NULL)
        {
            printf("Gagal membuka file.\n");
            return;
        }

        // Buka file sementara
        TempFile = fopen("Temp.dat", "wb");
        if (TempFile == NULL)
        {
            printf("Gagal membuat file sementara.\n");
            fclose(Transaksimakanan);
            return;
        }

        // Tampilkan riwayat transaksi
        riwayatTransaksi();

        // Minta input ID transaksi yang ingin dihapus
        printf("\n=== Hapus Transaksi Makanan ===\n");
        printf("Masukkan ID Transaksi Makanan yang Ingin Dihapus : ");
        printf("TRSM");
        scanf("%d", &cariID);

        // Baca semua transaksi dan salin ke file sementara kecuali yang sesuai dengan ID
        found = 0;
        while (fread(&makanan, sizeof(ListMakanan), 1, Transaksimakanan) == 1)
        {
            if (makanan.id != cariID)
            {
                fwrite(&makanan, sizeof(ListMakanan), 1, TempFile);
            }
            else
            {
                found = 1; // ID ditemukan
            }
        }

        fclose(Transaksimakanan);
        fclose(TempFile);

        if (found)
        {
            // Hapus file asli dan ganti dengan file sementara
            remove("Makanan.dat");
            rename("Temp.dat", "Makanan.dat");
            printf("\nData dengan ID %d berhasil dihapus!\n", cariID);
            break; // Keluar dari loop jika ID ditemukan dan dihapus
        }
        else
        {
            // Hapus file sementara karena ID tidak ditemukan
            remove("Temp.dat");
            printf("\nData dengan ID %d tidak ditemukan.\n", cariID);

            // Tanya apakah pengguna ingin mencoba lagi
            printf("Apakah Anda ingin mencoba lagi? (y/n): ");
            scanf(" %c", &ulangi); // Spasi sebelum %c untuk menghindari masalah buffer

            if (ulangi != 'y' && ulangi != 'Y')
            {
                break; // Keluar dari loop jika pengguna tidak ingin mencoba lagi
            }
        }
    } while (1); // Ulangi sampai ID ditemukan atau pengguna memilih untuk berhenti
}

void riwayatTransaksi()
{
    FILE *Transaksimakanan = fopen("Makanan.dat", "rb");
    if (Transaksimakanan == NULL)
    {
        printf("Gagal membuka file.\n");
        return;
    }

    ListMakanan makanan;
    printf("======================================================================================================================================\n");
    printf("%*s\n", 65, "DAFTAR TRANSAKSI F&B");
    printf("======================================================================================================================================\n");
    printf("| %-5s     | %-10s       | %-10s | %-10s    | %-10s | %-10s    | %-10s | %-15s |\n", "ID", "Tanggal", "Nama Menu", "Harga", "Jumlah Makanan", "Total Harga", "Metode Pembayaran", "Status Pembayaran");
    printf("--------------------------------------------------------------------------------------------------------------------------------------\n");

    while (fread(&makanan, sizeof(ListMakanan), 1, Transaksimakanan) == 1)
    {
        printf("| TRS00%-2d | %-10s | %-10s | Rp %-10.2f | %-10d     | Rp %-10.2f  | %-10s       | %-15s    |\n",
               makanan.id, makanan.tanggal, menu.namaMakanan, menu.harga, makanan.jumlah, makanan.total, makanan.metode, makanan.konfir);
    }
    printf("======================================================================================================================================\n");

    fclose(Transaksimakanan);
}

void tampilkanTransaksi(ListMakanan *makanan)
{
    printf("ID                 : TRSM00%d\n", makanan->id);
    printf("Nama Makanan       : %s\n", menu.namaMakanan);
    printf("Harga              : Rp. %.2f\n", menu.harga);
    printf("Jumlah yang Dibeli : %d\n", makanan->jumlah);
    printf("Total Harga        : Rp. %.2f\n", makanan->total);
    printf("Metode Pembayaran  : %s\n", makanan->metode);
}
