// Fungsi deklarasi
#define MAX_ID 1000

void createTransaksi();

int transaksiFnb()
{
    printf("Transaksi FNB\n");
    createTransaksi();
    return 0;
}

// Fungsi untuk memproses transaksi
void createTransaksi()
{
    FILE *file = fopen(FILEMENU, "rb");
    if (!file)
    {
        printf("Gagal membuka file database.\n");
        return;
    }

    // Baca semua record ke dalam array
    FnbData menuArray[MAX_ID];
    int totalRecords = 0;

    while (fread(&menuArray[totalRecords], sizeof(FnbData), 1, file) == 1)
    {
        totalRecords++;
    }
    fclose(file);

    // Tampilkan menu yang tersedia
    printf("\nMenu yang tersedia:\n");
    printf("| %-8s | %-20s | %-15s | %-10s | %-15s |\n",
           "ID", "Nama", "Kategori", "Stok", "Harga");
    printf("-----------------------------------------------------------------------------------\n");

    for (int i = 0; i < totalRecords; i++)
    {
        printf("| %-8s | %-20s | %-15s | %-10d | Rp.%-13.0f |\n",
               menuArray[i].ID, menuArray[i].namaMakanan, menuArray[i].kategori, menuArray[i].stok, menuArray[i].harga);
    }

    int totalPrice = 0;
    while (1)
    {
        char idCari[10];
        int quantity;

        printf("\nMasukkan ID menu yang ingin dipesan (atau 'selesai' untuk selesai): ");
        scanf("%9s", idCari);

        // Jika pengguna mengetik "selesai", keluar dari loop
        if (strcmp(idCari, "selesai") == 0)
        {
            break;
        }

        // Cari menu berdasarkan ID
        int targetIndex = -1;
        for (int i = 0; i < totalRecords; i++)
        {
            if (strcmp(menuArray[i].ID, idCari) == 0)
            {
                targetIndex = i;
                break;
            }
        }

        // Jika menu tidak ditemukan
        if (targetIndex == -1)
        {
            printf("Menu dengan ID %s tidak ditemukan.\n", idCari);
            continue;
        }

        // Tampilkan informasi menu dan minta jumlah pesanan
        FnbData *menu = &menuArray[targetIndex];
        printf("\nMenu dipesan:\n");
        printf("ID: %s | Nama: %s | Harga: Rp.%.0f\n",
               menu->ID, menu->namaMakanan, menu->harga);

        printf("Masukkan jumlah %s yang ingin dipesan: ", menu->namaMakanan);
        scanf("%d", &quantity);

        if (quantity > 0)
        {
            int subtotal = menu->harga * quantity;
            totalPrice += subtotal;
            printf("Subtotal untuk %d %s: Rp%d\n", quantity, menu->namaMakanan, subtotal);
        }
        else
        {
            printf("Jumlah tidak valid! Pesanan dibatalkan.\n");
        }
    }

    // Tampilkan total tagihan
    printf("\nTotal tagihan: Rp.%.0f\n", totalPrice);

    // Pilihan metode pembayaran
    printf("\nPilih metode pembayaran:\n");
    printf("Gunakan panah atas/bawah untuk navigasi, lalu tekan Enter:\n");

    const char *metode[] = {"Tunai", "Kartu Kredit", "E-Wallet"};
    int metodeIndex = 0;
    int metodeCount = 3;

    while (1)
    {
        // Tampilkan metode pembayaran dengan penanda
        for (int i = 0; i < metodeCount; i++)
        {
            if (i == metodeIndex)
            {
                printf(" > %s\n", metode[i]); // Penanda metode terpilih
            }
            else
            {
                printf("   %s\n", metode[i]);
            }
        }

        // Tangkap input arrow key
        char key = getch();
        if (key == 27)
        {            // ESC sequence untuk arrow keys dimulai dengan 27
            getch(); // Abaikan karakter kedua
            switch (getch())
            {
            case 75: // Panah atas
                metodeIndex = (metodeIndex - 1 + metodeCount) % metodeCount;
                break;
            case 77: // Panah bawah
                metodeIndex = (metodeIndex + 1) % metodeCount;
                break;
            }
        }
        else if (key == '\r')
        { // Enter
            break;
        }

        // Bersihkan output untuk memperbarui pilihan
        system("cls");
        printf("\nPilih metode pembayaran:\n");
    }

    // Input key untuk konfirmasi pembayaran

    // Verifikasi key

    // Konfirmasi pembayaran
    printf("\nKonfirmasi pembayaran: \n");
    printf("Anda memilih metode pembayaran %s.\n", metode[metodeIndex]);
    printf("\nPembayaran sebesar Rp.%.0f berhasil diproses. Terima kasih atas pesanan Anda!\n", totalPrice);
}
