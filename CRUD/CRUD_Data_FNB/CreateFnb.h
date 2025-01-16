#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_ENTER '\r'


#define MAX_ID 1000

typedef struct
{
    char ID[10];
    char namaMakanan[50];
    char kategori[20];
    int stok;
    double harga;
} FnbData;

void BuatMenu();

int CreateMenu()
{
    BuatMenu();
    return 0;
}

void BuatMenu()
{
    FILE *file = fopen(FILEMENU, "a+b");
    if (!file)
    {
        perror("Gagal membuka file database");
        return;
    }

    fseek(file, 0, SEEK_END);

    FnbData menu;
    memset(&film, 0, sizeof(FnbData));

    const char *pilihanKategori[] = {"Makanan", "Minuman"};
    const char *TombolKonfirmasi[] = {"KONFIRMASI", "BATALKAN"};

    int pilihanKategoriIndex = 0;
    int step = 0;
    int konfirmasiIndex = 0; // 0 untuk "BATAL", 1 untuk "KONFIRMASI"
    char key;

    while (1)
    {
        // Render menu berdasarkan step
        system("cls"); // Bersihkan layar untuk tampilan baru
        printf("==== Tambah Menu ====\n");

        if (step == 0) // Input menu, stok, dan Harga
        {
            printf("Nama: ");
            scanf(" %[^\n]", menu.namaMakanan); // Input string dengan spasi
            printf("Stok: ");
            scanf("%d", &menu.stok);
            printf("Durasi (dalam jam): ");
            printf("Harga (Rp): ");
            scanf("Rp.%lf", &film.harga);

            step++; // Lanjut ke genre
        }
        
        else if (step == 1) // Pilih Bentuk
        {
            printf("Kategori:\n");
            for (int i = 0; i < 2; i++)
            {
                if (i == pilihanKategori)
                {
                    printf(" > [%s] ", pilihanKategori[i]); // Sorot pilihan
                }
                else
                {
                    printf("   [%s] ", pilihanKategori[i]);
                }
            }
            printf("\nGunakan panah kiri/kanan untuk navigasi, Enter untuk konfirmasi.\n");

            key = getch();
            if (key == 75) // Panah kiri
                pilihanKategoriIndex = (pilihanKategoriIndex - 1 + 2) % 2;
            else if (key == 77) // Panah kanan
                pilihanKategoriIndex = (pilihanKategoriIndex + 1) % 2;
            else if (key == '\r') // Enter
            {
                strncpy(menu.kategori, pilihanKategori[pilihanKategoriIndex], sizeof(menu.kategori) - 1);
                step++; // Lanjut ke konfirmasi
            }
        }
        else if (step == 2) // Konfirmasi
        {
            printf("Konfirmasi Tambah Menu:\n");
            printf("Nama: %s\n", menu.namaMakanan);
            printf("Kategori: %s\n", menu.kategori);
            printf("Stok: %s\n", menu.stok);
            printf("Harga: Rp%.2lf\n", menu.harga);
            printf("\nKonfirmasi: %s\n", konfirmasiIndex == 0 ? "BATAL" : "KONFIRMASI");
            printf("\nGunakan panah kiri/kanan untuk navigasi, Enter untuk konfirmasi.\n");

            key = getch();
            if (key == 75 || key == 77) // Panah kiri/kanan
                konfirmasiIndex = 1 - konfirmasiIndex; // Toggle antara 0 dan 1
            else if (key == '\r') // Enter
            {
                if (konfirmasiIndex == 0)
                {
                    printf("Pembuatan film dibatalkan.\n");
                    break;
                }
                else
                {
                    rewind(file);

                    // Generate ID baru
                    bool idTerpakai[MAX_ID] = {false};
                    FnbData temp;
                    while (fread(&temp, sizeof(FnbData), 1, file))
                    {
                        if (strncmp(temp.ID, "MOV", 3) == 0)
                        {
                            int idNum = atoi(&temp.ID[3]);
                            if (idNum > 0 && idNum < MAX_ID)
                            {
                                idTerpakai[idNum] = true;
                            }
                        }
                    }

                    int idBaru = 1;
                    while (idBaru < MAX_ID && idTerpakai[idBaru])
                        idBaru++;
                    snprintf(menu.ID, sizeof(menu.ID), "FNB%03d", idBaru);

                    fwrite(&menu, sizeof(FnbData), 1, file);
                    printf("Menu berhasil ditambahkan!\n");
                    break;
                }
            }
        }
    }

    fclose(file);
}

