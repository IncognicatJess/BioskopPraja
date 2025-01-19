
void EditFilm();

// Fungsi untuk membaca dan menampilkan daftar film (debugging)
int UpdateFilm() {
    printf("\n==== Data Film ====\n");
    EditFilm();
    return 0;
}

// Fungsi untuk mengedit data film
void EditFilm() {
    FILE *file = fopen(FILEFILM, "rb");
    if (!file) {
        printf("Gagal membuka file database.\n");
        return;
    }

    // Baca semua record ke memori
    MovieData filmArray[100];
    int totalRecords = 0;

    while (fread(&filmArray[totalRecords], sizeof(MovieData), 1, file) == 1) {
        totalRecords++;
    }
    fclose(file);

    // Cari film berdasarkan ID
    char idCari[10];
    printf("Masukkan ID film yang ingin diedit: ");
    scanf("%9s", idCari);

    int targetIndex = -1;
    for (int i = 0; i < totalRecords; i++) {
        if (strcmp(filmArray[i].ID, idCari) == 0) {
            targetIndex = i;
            break;
        }
    }

    if (targetIndex == -1) {
        printf("Film dengan ID %s tidak ditemukan.\n", idCari);
        return;
    }

    MovieData *film = &filmArray[targetIndex];
    printf("\nFilm ditemukan:\n");
    printf("ID: %s | Judul: %s | Genre: %s | Tahun: %d | Durasi: %.2f menit | Harga: %.2f\n",
           film->ID, film->judul, film->genre, film->tahunRelease, film->durasi, film->harga);

    // Edit data film
    printf("Masukkan judul baru: ");
    getchar(); // Bersihkan newline buffer
    fgets(film->judul, sizeof(film->judul), stdin);
    strtok(film->judul, "\n"); // Hapus newline di akhir input

    printf("Masukkan tahun rilis baru: ");
    scanf("%d", &film->tahunRelease);

    printf("Masukkan durasi baru (menit): ");
    scanf("%lf", &film->durasi);

    printf("Masukkan studio baru: ");
    getchar(); // Bersihkan newline buffer
    fgets(film->studioFilm, sizeof(film->studioFilm), stdin);
    strtok(film->studioFilm, "\n"); // Hapus newline di akhir input

    printf("Masukkan harga baru: ");
    scanf("%lf", &film->harga);

    // Pilih genre
    const char *pilihanGenre[] = {"Action", "Horror", "Comedy", "Drama", "Romance"};
    int pilihanGenreIndex = 0;
    while (1) {

        system("cls");
        printf("\nPilih Genre Film:\n");
        for (int i = 0; i < 5; i++) {
            if (i == pilihanGenreIndex) {
                printf(" > [%s] ", pilihanGenre[i]); // Sorot pilihan
            } else {
                printf("   [%s] ", pilihanGenre[i]);
            }
        }
        printf("\nGunakan panah kiri/kanan untuk navigasi, Enter untuk konfirmasi.\n");

        char key = getch();
        if (key == 75) // Panah kiri
            pilihanGenreIndex = (pilihanGenreIndex - 1 + 5) % 5;
        else if (key == 77) // Panah kanan
            pilihanGenreIndex = (pilihanGenreIndex + 1) % 5;
        else if (key == '\r') { // Enter
            strncpy(film->genre, pilihanGenre[pilihanGenreIndex], sizeof(film->genre) - 1);
            film->genre[sizeof(film->genre) - 1] = '\0';
            break;
        }
    }

    // Pilih format
    const char *pilihanBentuk[] = {"2D", "3D"};
    int pilihanBentukIndex = 0;
    while (1) {
        system("cls");
        printf("\nPilih Bentuk Film:\n");
        for (int i = 0; i < 2; i++) {
            if (i == pilihanBentukIndex) {
                printf(" > [%s] ", pilihanBentuk[i]); // Sorot pilihan
            } else {
                printf("   [%s] ", pilihanBentuk[i]);
            }
        }
        printf("\nGunakan panah kiri/kanan untuk navigasi, Enter untuk konfirmasi.\n");

        char key = getch();
        if (key == 75) // Panah kiri
            pilihanBentukIndex = (pilihanBentukIndex - 1 + 2) % 2;
        else if (key == 77) // Panah kanan
            pilihanBentukIndex = (pilihanBentukIndex + 1) % 2;
        else if (key == '\r') { // Enter
            strncpy(film->bentuk, pilihanBentuk[pilihanBentukIndex], sizeof(film->bentuk) - 1);
            film->bentuk[sizeof(film->bentuk) - 1] = '\0';
            break;
        }
    }

    // Simpan data yang diperbarui
    file = fopen(FILEFILM, "wb");
    if (!file) {
        printf("Gagal membuka file untuk menulis.\n");
        return;
    }
    fwrite(filmArray, sizeof(MovieData), totalRecords, file);
    fclose(file);

    printf("Data film berhasil diperbarui.\n");
}

