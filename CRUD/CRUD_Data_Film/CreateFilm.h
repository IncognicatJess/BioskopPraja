#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_ENTER '\r'


#define MAX_ID 1000

void BuatFilm();

int CreateFilm()
{
    BuatFilm();
    return 0;
}

void BuatFilm()
{
    FILE *file = fopen(FILEFILM, "a+b");
    if (!file)
    {
        perror("Gagal membuka file database");
        return;
    }

    fseek(file, 0, SEEK_END);

    MovieData film;
    memset(&film, 0, sizeof(MovieData));

    const char *pilihanGenre[] = {"Action", "Horror", "Comedy", "Drama", "Romance"};
    const char *pilihanBentuk[] = {"2D", "3D", "IMAX"};
    const char *TombolKonfirmasi[] = {"KONFIRMASI", "BATALKAN"};
   
    int pilihanGenreIndex = 0;
    int pilihanBentukIndex = 0;
    int step = 0;
    int konfirmasiIndex = 0; // 0 untuk "BATAL", 1 untuk "KONFIRMASI"
    char key;

    while (1)
    {
        // Render menu berdasarkan step
        system("cls"); // Bersihkan layar untuk tampilan baru
        printf("==== Tambah Film ====\n");

        if (step == 0) // Input Judul, Tahun, Durasi, Studio, dan Harga
        {
            printf("Judul (maks. 50 karakter): ");
            scanf(" %[^\n]", film.judul); // Input string dengan spasi
            printf("Tahun Rilis: ");
            scanf("%d", &film.tahunRelease);
            printf("Durasi (dalam menit): ");
            scanf("%lf", &film.durasi);
            getchar(); // Bersihkan newline buffer
            printf("Studio Film (maks. 20 karakter): ");
            scanf(" %[^\n]", film.studioFilm);
            printf("Harga (Rp): ");
            scanf("%lf", &film.harga);

            step++; // Lanjut ke genre
        }
        
        else if (step == 1) // Pilih Genre
        {
            printf("Pilih Genre Film:\n");
            for (int i = 0; i < 5; i++)
            {
                if (i == pilihanGenreIndex)
                {
                    printf(" > [%s] ", pilihanGenre[i]); // Sorot pilihan
                }
                else
                {
                    printf("   [%s] ", pilihanGenre[i]);
                }
            }
            printf("\nGunakan panah kiri/kanan untuk navigasi, Enter untuk konfirmasi.\n");

            key = getch();
            if (key == 75) // Panah kiri
                pilihanGenreIndex = (pilihanGenreIndex - 1 + 5) % 5;
            else if (key == 77) // Panah kanan
                pilihanGenreIndex = (pilihanGenreIndex + 1) % 5;
            else if (key == '\r') // Enter
            {
                strncpy(film.genre, pilihanGenre[pilihanGenreIndex], sizeof(film.genre) - 1);
                step++; // Lanjut ke format
            }
        }
        else if (step == 2) // Pilih Bentuk
        {
            printf("Pilih Bentuk Film:\n");
            for (int i = 0; i < 2; i++)
            {
                if (i == pilihanBentukIndex)
                {
                    printf(" > [%s] ", pilihanBentuk[i]); // Sorot pilihan
                }
                else
                {
                    printf("   [%s] ", pilihanBentuk[i]);
                }
            }
            printf("\nGunakan panah kiri/kanan untuk navigasi, Enter untuk konfirmasi.\n");

            key = getch();
            if (key == 75) // Panah kiri
                pilihanBentukIndex = (pilihanBentukIndex - 1 + 2) % 2;
            else if (key == 77) // Panah kanan
                pilihanBentukIndex = (pilihanBentukIndex + 1) % 2;
            else if (key == '\r') // Enter
            {
                strncpy(film.bentuk, pilihanBentuk[pilihanBentukIndex], sizeof(film.bentuk) - 1);
                step++; // Lanjut ke konfirmasi
            }
        }
        else if (step == 3) // Konfirmasi
        {
            printf("Konfirmasi Tambah Film:\n");
            printf("Judul: %s\n", film.judul);
            printf("Genre: %s\n", film.genre);
            printf("Bentuk: %s\n", film.bentuk);
            printf("Harga: Rp%.2lf\n", film.harga);
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
                    MovieData temp;
                    while (fread(&temp, sizeof(MovieData), 1, file))
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
                    snprintf(film.ID, sizeof(film.ID), "MOV%03d", idBaru);

                    fwrite(&film, sizeof(MovieData), 1, file);
                    printf("Film berhasil ditambahkan!\n");
                    break;
                }
            }
        }
    }

    fclose(file);
}

