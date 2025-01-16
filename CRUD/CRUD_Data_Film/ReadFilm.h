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
} MovieDataBaca;

void TampilkanFilm();
int BandingkanIDFilm(const void *a, const void *b);

int ReadFilm()
{
    printf("\n==== Data Film ====\n");
    TampilkanFilm();
    return 0;
}

void TampilkanFilm()
{
    FILE *file = fopen(FILEFILM, "rb");
    if (!file)
    {
        printf("Gagal membuka file %s. Pastikan file tersebut ada.\n", FILEFILM);
        return;
    }

    MovieDataBaca film[MAX_ID];
    int jumlahFilm = 0;

    // Membaca semua data dari file
    while (fread(&film[jumlahFilm], sizeof(MovieDataBaca), 1, file))
    {
        strncpy(film[jumlahFilm].status, "Sedang Tayang", sizeof(film[jumlahFilm].status));
        jumlahFilm++;
    }
    fclose(file);

    // Mengurutkan data berdasarkan ID
    qsort(film, jumlahFilm, sizeof(MovieDataBaca), BandingkanID);

    // Menampilkan tabel
    printf("| %-8s | %-15s | %-15s | %-10s | %-8s | %-10s | %-8s | %-10s | %-10s |\n", "ID", "Judul Film", "Genre", "Tahun Rilis", "Durasi", "Studio Film", "Bentuk", "Harga", "Status");
    printf("------------------------------------------------------------------------------------------------------------------------\n");

    for (int i = 0; i < jumlahFilm; i++)
    {
        printf("| %-8s | %-15s | %-15s | %-10d | %-8.0f | %-10s | %-8s | %-10f | %-10s |\n",
               film[i].ID, film[i].judul, film[i].genre, film[i].tahunRelease, film[i].durasi, film[i].studioFilm, film[i].bentuk, film[i].harga, film[i].status);
    }
    printf("\n\n\n");
}

// Fungsi pembanding untuk qsort berdasarkan ID
int BandingkanIDFilm(const void *a, const void *b)
{
    MovieDataBaca *filmA = (MovieDataBaca *)a;
    MovieDataBaca *filmB = (MovieDataBaca *)b;

    // Memisahkan jenis ID (ADM atau USR)
    char prefixA[4], prefixB[4];
    int numberA, numberB;

    sscanf(filmA->ID, "%3s%d", prefixA, &numberA);
    sscanf(filmB->ID, "%3s%d", prefixB, &numberB);

    // Urutkan berdasarkan prefix dulu (ADM < USR)
    int cmp = strcmp(prefixA, prefixB);
    if (cmp != 0)
    {
        return cmp;
    }

    // Jika prefix sama, urutkan berdasarkan nomor ID
    return numberA - numberB;
}
