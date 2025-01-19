typedef struct
{
    char ID[10];
    char namaMakanan[50];
    char kategori[20];
    int stok;
    double harga;
} FnbDataUpdate;

void EditMenu();

// Fungsi untuk membaca dan menampilkan daftar film (debugging)
int UpdateFnb()
{
    printf("\n==== Data Menu F&B ====\n");
    EditMenu();
    return 0;
}

// Fungsi untuk mengedit data film
void EditMenu()
{
    FILE *file = fopen(FILEMENU, "rb");
    if (!file)
    {
        printf("Gagal membuka file database.\n");
        return;
    }

    // Baca semua record ke memori
    FnbDataUpdate menuArray[MAX_ID];
    int totalRecords = 0;

    while (fread(&menuArray[totalRecords], sizeof(FnbDataUpdate), 1, file) == 1)
    {
        totalRecords++;
    }
    fclose(file);

    // Cari film berdasarkan ID
    char idCari[10];
    printf("Masukkan ID menu yang ingin diedit: ");
    scanf("%9s", idCari);

    int targetIndex = -1;
    for (int i = 0; i < totalRecords; i++)
    {
        if (strcmp(menuArray[i].ID, idCari) == 0)
        {
            targetIndex = i;
            break;
        }
    }

    if (targetIndex == -1)
    {
        printf("Menu dengan ID %s tidak ditemukan.\n", idCari);
        return;
    }

    FnbDataUpdate *menu = &menuArray[targetIndex];
    printf("\nMenu ditemukan:\n");
    printf("ID: %s | Nama: %s | Kategori: %s | Stok: %d | Harga: %.2f jam\n",
           menu->ID, menu->namaMakanan, menu->kategori, menu->stok, menu->harga);

    // Edit data menu
    printf("Masukkan menu baru: ");
    getchar(); // Bersihkan newline buffer
    fgets(menu->namaMakanan, sizeof(menu->namaMakanan), stdin);
    strtok(menu->namaMakanan, "\n"); // Hapus newline di akhir input

    printf("Stok baru: ");
    scanf("%d", &menu->stok);

    printf("Harga baru: Rp. ");
    scanf("%lf", &menu->harga);

    // Pilih kategori
    const char *pilihanKategori[] = {"Makanan", "Minuman"};
    int pilihanKategoriIndex = 0;
    while (1)
    {

        system("cls");
        printf("\nPilih kategori menu:\n");
        for (int i = 0; i < 2; i++)
        {
            if (i == pilihanKategoriIndex)
            {
                printf(" > [%s]", pilihanKategori[i]); // Sorot pilihan
            }
            else
            {
                printf("   [%s]", pilihanKategori[i]);
            }
        }
        printf("\nGunakan panah kiri/kanan untuk navigasi, Enter untuk konfirmasi.\n");

        char key = getch();
        if (key == 75)
        { // Panah kiri
            pilihanKategoriIndex = (pilihanKategoriIndex - 1 + 2) % 2;
        }
        else if (key == 77)
        { // Panah kanan
            pilihanKategoriIndex = (pilihanKategoriIndex + 1) % 2;
        }
        else if (key == '\r')
        { // Enter
            strncpy(menu->kategori, pilihanKategori[pilihanKategoriIndex], sizeof(menu->kategori) - 1);
            menu->kategori[sizeof(menu->kategori) - 1] = '\0';
            break;
        }
    }

    // Simpan data yang diperbarui
    file = fopen(FILEMENU, "wb");
    if (!file)
    {
        printf("Gagal membuka file untuk menulis.\n");
        return;
    }
    fwrite(menuArray, sizeof(FnbDataUpdate), totalRecords, file);
    fclose(file);

    printf("Data menu berhasil diperbarui.\n");
}
