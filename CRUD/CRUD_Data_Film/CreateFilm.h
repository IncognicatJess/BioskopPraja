#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_ID 1000

typedef struct
{
    char ID[10];
    char judul[50];
    char genre[20];
    int tahunRelease;
    double durasi;
    char studioFilm[20];
    char bentuk[10];
    double harga;
    char status[50];
} MovieData;

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
        printf("Gagal membuka file database.\n");
        return;
    }

    MovieData film;
    memset(&film, 0, sizeof(MovieData));

    const char *pilihanGenre[] = {"Action", "Horror", "Comedy", "Drama", "Romance", "Thriller", "Sci-Fi", "Fantasy", "Animation", "Documentary"};
    const char *pilihanBentuk[] = {"2D", "3D"};

    int pilihanGenreIndex = 0;
    int pilihanBentukIndex = 0;
    int step = 0;

    printf("==== Tambah Film ====\n");
    getchar(); // Consume newline left by scanf

    printf("Judul (maks. 50 karakter): ");
    scanf("%[^\n]", film.judul);

    printf("Tahun Rilis: ");
    scanf("%d", &film.tahunRelease);

    printf("Durasi (dalam jam): ");
    scanf("%lf", &film.durasi);

    getchar(); // Consume newline left by scanf

    printf("Studio Film (maks. 20 karakter): ");
    scanf("%[^\n]", film.studioFilm);

    printf("Harga (Rp): ");
    scanf("%lf", &film.harga);

    // Select Genre
    printf("Genre Film    :");
    for (int i = 0; i < 2; i++)
    {
        if (i == pilihanGenreIndex && step == 0)
        {
            printf(" >[%s]", pilihanGenre[i]);
        }
        else
        {
            printf("  [%s]", pilihanGenre[i]);
        }
    }
    printf("\n");

    if (pilihanGenreIndex < 1 || pilihanGenreIndex > 10)
    {
        printf("Pilihan genre tidak valid.\n");
        fclose(file);
        return;
    }
    strcpy(film.genre, pilihanGenre[pilihanGenreIndex - 1]);

    // Select Format
    printf("Bentuk :");
    const char **bentukOptions = strcmp(pilihanBentuk[pilihanBentukIndex], "2D") == 0 ? pilihanGenre : pilihanBentuk;
    int studioOptionsCount = 2;
    for (int i = 0; i < studioOptionsCount; i++)
    {
        if (i == pilihanBentukIndex && step == 1)
        {
            printf(" >[%s]", bentukOptions[i]);
        }
        else
        {
            printf("  [%s]", bentukOptions[i]);
        }
    }
    printf("\n\n");

    printf("Film: %s%s\n", step == 2 ? ">" : "", film.judul);

    if (pilihanBentukIndex < 1 || pilihanBentukIndex > 2)
    {
        printf("Pilihan bentuk tidak valid.\n");
        fclose(file);
        return;
    }
    strcpy(film.bentuk, pilihanBentuk[pilihanBentukIndex - 1]);

    // Generate ID
    rewind(file);
    int idTerpakai[MAX_ID] = {0};
    MovieData temp;
    while (fread(&temp, sizeof(MovieData), 1, file))
    {
        if (strncmp(temp.ID, "MOV", 3) == 0)
        {
            int idNum = atoi(&temp.ID[3]);
            if (idNum > 0 && idNum < MAX_ID)
            {
                idTerpakai[idNum] = 1;
            }
        }
    }

    int idBaru = 1;
    while (idBaru < MAX_ID && idTerpakai[idBaru])
    {
        idBaru++;
    }

    if (idBaru >= MAX_ID)
    {
        printf("Gagal menghasilkan ID baru.\n");
        fclose(file);
        return;
    }

    snprintf(film.ID, sizeof(film.ID), "MOV%03d", idBaru);

    // Save to file
    fwrite(&film, sizeof(MovieData), 1, file);
    printf("Film berhasil ditambahkan dengan ID: %s\n", film.ID);

    fclose(file);
}
