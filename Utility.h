void cariFilmByIDOrJudul(const char *keyword);


// void drawBox(int x, int y, int width, int height, const char *label) {
//     int i, j;
//     // Gambar bagian atas kotak
//     gotoxy(x, y);
//     printf("+");
//     for (i = 0; i < width; i++) printf("-");
//     printf("+");

//     // Gambar sisi kiri dan kanan kotak
//     for (j = 0; j < height; j++) {
//         gotoxy(x, y + j + 1);
//         printf("|");
//         for (i = 0; i < width; i++) printf(" ");
//         printf("|");
//     }

//     // Gambar bagian bawah kotak
//     gotoxy(x, y + height + 1);
//     printf("+");
//     for (i = 0; i < width; i++) printf("-");
//     printf("+");

//     // Tulis label di tengah kotak
//     gotoxy(x + (width - strlen(label)) / 2 + 1, y + height / 2 + 1);
//     printf("%s", label);
// }

// Fungsi untuk memindahkan kursor ke posisi tertentu di konsol
// void gotoxy(int x, int y) {
//     COORD coord;
//     coord.X = x;
//     coord.Y = y;
//     SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
// }

void cariFilmByIDOrJudul(const char *keyword) {
    FILE *file = fopen(FILEFILM, "rb");
    if (!file) {
        printf("Gagal membuka file database film.\n");
        return;
    }

    MovieData film;
    bool found = false;

    printf("\nHasil Pencarian:\n");
    printf("==============================================\n");
    printf("| %-8s | %-20s | %-10s |\n", "ID", "Judul", "Genre");
    printf("==============================================\n");

    while (fread(&film, sizeof(MovieData), 1, file)) {
        if (strstr(film.ID, keyword) != NULL || strstr(film.judul, keyword) != NULL) {
            printf("| %-8s | %-20s | %-10s |\n", film.ID, film.judul, film.genre);
            found = true;
        }
    }

    if (!found) {
        printf("| %-8s | %-20s | %-10s |\n", "Tidak", "Ditemukan", " ");
    }

    printf("==============================================\n");
    fclose(file);
}
