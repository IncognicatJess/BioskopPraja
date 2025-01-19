

void BuatMenu();
void generateID(char *prefix, int count, char *output);

int CreateFnb()
{
    BuatMenu();
    return 0;
}

void BuatMenu()
{
    FILE *file = fopen(FILEMENU, "a+b");
    if (!file)
    {
        printf("Gagal membuka file database\n");
        return;
    }

    FnbData menu;
    const char *pilihanKategori[] = {"Makanan", "Minuman"};
    const char *TombolKonfirmasi[] = {"BATALKAN", "KONFIRMASI"};

    int pilihanKategoriIndex = 0;
    int step = 0;
    int konfirmasiIndex = 0; // 0 untuk "BATALKAN", 1 untuk "KONFIRMASI"
    char key;

    while (1)
    {
        system("cls"); // Bersihkan layar untuk tampilan baru
        printf("==== Tambah Menu ====\n");

        if (step == 0)
        {              // Input nama, stok, dan harga
            getchar(); // Buang karakter newline

            printf("Nama menu: ");
            scanf("%[^\n]", menu.namaMakanan);

            do
            {
                printf("Stok: ");
                scanf("%d", &menu.stok);
            } while (menu.stok < 0);

            do
            {
                printf("Harga: Rp.");
                scanf("%lf", &menu.harga);
            } while (menu.harga < 0);

            step++; // Lanjut ke kategori
            fflush(stdin);
        }
        else if (step == 1)
        { // Pilih kategori
            printf("Kategori:\n");
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

            key = getch();
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
                strncpy(menu.kategori, pilihanKategori[pilihanKategoriIndex], sizeof(menu.kategori) - 1);
                menu.kategori[sizeof(menu.kategori) - 1] = '\0'; // Pastikan null-terminated
                step++;                                          // Lanjut ke konfirmasi
            }
        }
        else if (step == 2)
        { // Konfirmasi
            printf("Konfirmasi Tambah Menu:\n");
            printf("Nama      : %s\n", menu.namaMakanan);
            printf("Kategori  : %s\n", menu.kategori);
            printf("Stok      : %d\n", menu.stok);
            printf("Harga     : Rp%.2lf\n", menu.harga);
            printf("\nKonfirmasi: [%s]\n", TombolKonfirmasi[konfirmasiIndex]);
            printf("\nGunakan panah kiri/kanan untuk navigasi, Enter untuk konfirmasi.\n");

            key = getch();
            if (key == 75 || key == 77)
            {                                          // Panah kiri/kanan
                konfirmasiIndex = 1 - konfirmasiIndex; // Toggle antara 0 dan 1
            }
            else if (key == '\r')
            { // Enter
                if (konfirmasiIndex == 1)
                { // KONFIRMASI
                    // Generate ID baru
                    fseek(file, 0, SEEK_END);
                    long count = ftell(file) / sizeof(FnbData);
                    generateID("FNB", count + 1, menu.ID);

                    // Simpan ke file
                    fwrite(&menu, sizeof(FnbData), 1, file);
                    printf("\nMenu berhasil ditambahkan dengan ID: %s\n", menu.ID);
                    break;
                }
                else
                { // BATALKAN
                    printf("Penambahan menu dibatalkan.\n");
                    break;
                }
            }
        }
    }

    fclose(file);
}

void generateID(char *prefix, int count, char *output)
{
    snprintf(output, 10, "%s%03d", prefix, count);
}
