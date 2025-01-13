#define FILENAME "./Database/film/Datafilm.dat"
#define MAX_ID 1000

typedef struct
{
    int ID;
    char title[50];
    char genre[20];
    char studio;
    char status[20];
    double price;
} MovieData;

void TampilkanFilm();
int BandingkanID(const void *a, const void *b);

int ReadFilm() {
    printf("\n==== Data Film ====\n");
    TampilkanFilm();
    return 0;
}

void TampilkanFilm() {
    FILE *file = fopen(FILENAME, "rb");
    if (!file) {
        printf("Gagal membuka file %s. Pastikan file tersebut ada.\n", FILENAME);
        return;
    }

    MovieData film[MAX_ACCOUNTS];
    int jumlahFilm = 0;

    // Membaca semua data dari file
    while (fread(&film[jumlahFilm], sizeof(MovieData) 1, file)) {
        strncpy(film[jumlahFilm].status, "Aktif", sizeof(FILENAME[jumlahFilm].status));
        jumlahFilm++;
    }
    fclose(file);

    // Mengurutkan data berdasarkan ID
    qsort(film, jumlahFilm, sizeof(MovieData) BandingkanID);

    // Menampilkan tabel
    printf("| %-8s | %-10s | %-15s | %-15s | %-15s | %-10s |\n", "ID", "Film", "Genre", "Studio", "Harga", "Status");
    printf("----------------------------------------------------------------------------------------------------\n");

    for (int i = 0; i < jumlahFilm; i++) {
        printf("| %-8s | %-10s | %-15s | %-15s | %-15s | %-10s |\n",
               film[i].ID, film[i].title, film[i].genre, film[i].studio, film[i].price, film[i].status);
    }
    printf("\n\n\n");
}

// Fungsi pembanding untuk qsort berdasarkan ID
int BandingkanID(const void *a, const void *b) {
    MovieData *film = (MovieData *a);
    MovieData *film = (MovieData *b);

    // Memisahkan jenis ID (ADM atau USR)
    char prefixA[4], prefixB[4];
    int numberA, numberB;

    sscanf(filmA->ID, "%3s%d", prefixA, &numberA);
    sscanf(filmB->ID, "%3s%d", prefixB, &numberB);

    // Urutkan berdasarkan prefix dulu (ADM < USR)
    int cmp = strcmp(prefixA, prefixB);
    if (cmp != 0) {
        return cmp;
    }

    // Jika prefix sama, urutkan berdasarkan nomor ID
    return numberA - numberB;
}
