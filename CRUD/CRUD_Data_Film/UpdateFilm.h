    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <ctype.h>
    #include <conio.h>
    #include <time.h>
    #define KEY_LEFT 75
    #define KEY_RIGHT 77
    #define KEY_UP 72
    #define KEY_DOWN 80
    #define KEY_ENTER '\r'

    #define MAX_ID 1000

    void EditFilm();

    int UpdateFilm() {
        printf("\n==== Edit Film ====\n");
        EditFilm();
        return 0;
    }

    void EditFilm() {
        FILE *file = fopen(FILEFILM, "rb+");
        if (!file) {
            printf("Gagal membuka file database.\n");
            return;
        }

        // Baca semua record ke memori
        MovieData filmArray[MAX_ID];
        int totalRecords = 0;

        while (fread(&filmArray[totalRecords], sizeof(MovieData), 1, file) == 1) {
            totalRecords++;
        }

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
            fclose(file);
            return;
        }

        MovieData *film = &filmArray[targetIndex];
        const char *pilihanGenre[] = {"Action", "Comedy", "Drama", "Horror", "Romance"};
        const char *pilihanBentuk[] = {"2D", "3D", "IMAX"};

        int pilihanGenreIndex = 0, pilihanBentukIndex = 0;
        char judul[50] = "", tahunReleaseStr[5] = "", durasiStr[10] = "", studioFilm[20] = "", hargaStr[10] = "";
        int step = 0;

        // Ambil tahun saat ini
    
        // Inisialisasi data film yang akan diedit
        strncpy(judul, film->judul, sizeof(judul) - 1);
        snprintf(tahunReleaseStr, sizeof(tahunReleaseStr), "%d", film->tahunRelease);
        snprintf(durasiStr, sizeof(durasiStr), "%.0f", film->durasi);
        strncpy(studioFilm, film->studioFilm, sizeof(studioFilm) - 1);
        snprintf(hargaStr, sizeof(hargaStr), "%.2f", film->harga);

        for (int i = 0; i < 5; i++) {
            if (strcmp(film->genre, pilihanGenre[i]) == 0) {
                pilihanGenreIndex = i;
                break;
            }
        }

        for (int i = 0; i < 3; i++) {
            if (strcmp(film->bentuk, pilihanBentuk[i]) == 0) {
                pilihanBentukIndex = i;
                break;
            }
        }

        while (1) {
            system("cls");
            printf("==== Edit Film ====\n");

            printf("Judul        : %s%s\n", step == 0 ? ">" : "", judul);
            printf("Tahun Rilis  : %s%s\n", step == 1 ? ">" : "", tahunReleaseStr);
            printf("Durasi (menit): %s%s\n", step == 2 ? ">" : "", durasiStr);
            printf("Studio Film  : %s%s\n", step == 3 ? ">" : "", studioFilm);
            printf("Harga (Rp)   : %s%s\n", step == 4 ? ">" : "", hargaStr);
            printf("Genre        : ");
            for (int i = 0; i < 5; i++) {
                if (i == pilihanGenreIndex && step == 5) {
                    printf(">[%s] ", pilihanGenre[i]); // Sudah dipilih
                } else if (i == pilihanGenreIndex) {
                    printf("#[%s] ", pilihanGenre[i]); // Sedang dipilih
                } else {
                    printf(" [%s] ", pilihanGenre[i]); // Belum dipilih
                }
            }
            printf("\nBentuk       : ");
            for (int i = 0; i < 3; i++) {
                if (i == pilihanBentukIndex && step == 6) {
                    printf(">[%s] ", pilihanBentuk[i]); // Sudah dipilih
                } else if (i == pilihanBentukIndex) {
                    printf("#[%s] ", pilihanBentuk[i]); // Sedang dipilih
                } else {
                    printf(" [%s] ", pilihanBentuk[i]); // Belum dipilih
                }
            }
            printf("\n");

            char key = getch();
            if (step == 0) { // Input judul
                if (isalnum(key) || key == ' ' || key == '.') {
                    size_t len = strlen(judul);
                    if (len < sizeof(judul) - 1) {
                        judul[len] = key;
                        judul[len + 1] = '\0';
                    }
                } else if (key == 8 && strlen(judul) > 0) {
                    judul[strlen(judul) - 1] = '\0';
                } else if (key == '\r' && strlen(judul) > 0) {
                    step++;
                }
            } else if (step == 1) { // Input tahun rilis
                if (isdigit(key)) {
                    size_t len = strlen(tahunReleaseStr);
                    if (len < 4) {
                        tahunReleaseStr[len] = key;
                        tahunReleaseStr[len + 1] = '\0';
                    }
                } else if (key == 8 && strlen(tahunReleaseStr) > 0) {
                    tahunReleaseStr[strlen(tahunReleaseStr) - 1] = '\0';
                } else if (key == '\r' && strlen(tahunReleaseStr) == 4) {
                    int tahun = atoi(tahunReleaseStr);
                    if (tahun >= 1900) {
                        step++;
                    } else {
                        TampilkanPesan("Tahun rilis harus antara 1900 dan tahun saat ini.\n", 2);
                    }
                }
            } else if (step == 2) { // Input durasi
                if (isdigit(key)) {
                    size_t len = strlen(durasiStr);
                    if (len < sizeof(durasiStr) - 1) {
                        durasiStr[len] = key;
                        durasiStr[len + 1] = '\0';
                    }
                } else if (key == 8 && strlen(durasiStr) > 0) {
                    durasiStr[strlen(durasiStr) - 1] = '\0';
                } else if (key == '\r' && strlen(durasiStr) > 0) {
                    int durasi = atoi(durasiStr);
                    if (durasi > 0 && durasi <= 6000) { // Durasi maksimal 100 jam (6000 menit)
                        step++;
                    } else {
                        TampilkanPesan("Durasi harus antara 1 dan 6000 menit.\n", 2);
                    }
                }
            } else if (step == 3) { // Input studio film
                if (isalnum(key) || key == ' ' || key == '.') {
                    size_t len = strlen(studioFilm);
                    if (len < sizeof(studioFilm) - 1) {
                        studioFilm[len] = key;
                        studioFilm[len + 1] = '\0';
                    }
                } else if (key == 8 && strlen(studioFilm) > 0) {
                    studioFilm[strlen(studioFilm) - 1] = '\0';
                } else if (key == '\r' && strlen(studioFilm) > 0) {
                    step++;
                }
            } else if (step == 4) { // Input harga
                if (isdigit(key) || key == '.') {
                    size_t len = strlen(hargaStr);
                    if (len < sizeof(hargaStr) - 1) {
                        hargaStr[len] = key;
                        hargaStr[len + 1] = '\0';
                    }
                } else if (key == 8 && strlen(hargaStr) > 0) {
                    hargaStr[strlen(hargaStr) - 1] = '\0';
                } else if (key == '\r' && strlen(hargaStr) > 0) {
                    double harga = atof(hargaStr);
                    if (harga >= 1000) {
                        step++;
                    } else {
                        TampilkanPesan("Harga minimal Rp 1.000.\n", 2);
                    }
                }
            } else if (step == 5) { // Pilih genre
                if (key == KEY_LEFT || key == KEY_UP) {
                    pilihanGenreIndex = (pilihanGenreIndex - 1 + 5) % 5;
                } else if (key == KEY_RIGHT || key == KEY_DOWN) {
                    pilihanGenreIndex = (pilihanGenreIndex + 1) % 5;
                } else if (key == KEY_ENTER) {
                    step++;
                }
            } else if (step == 6) { // Pilih bentuk
                if (key == KEY_LEFT || key == KEY_UP) {
                    pilihanBentukIndex = (pilihanBentukIndex - 1 + 3) % 3;
                } else if (key == KEY_RIGHT || key == KEY_DOWN) {
                    pilihanBentukIndex = (pilihanBentukIndex + 1) % 3;
                } else if (key == KEY_ENTER) {
                    step++;
                }
            } else if (step >= 7) { // Konfirmasi
                strncpy(film->judul, judul, sizeof(film->judul) - 1);
                film->tahunRelease = atoi(tahunReleaseStr);
                film->durasi = atof(durasiStr);
                strncpy(film->studioFilm, studioFilm, sizeof(film->studioFilm) - 1);
                film->harga = atof(hargaStr);
                strncpy(film->genre, pilihanGenre[pilihanGenreIndex], sizeof(film->genre) - 1);
                strncpy(film->bentuk, pilihanBentuk[pilihanBentukIndex], sizeof(film->bentuk) - 1);

                int konfirmasi = TombolKonfirmasi("Film", "Perbarui", film, "MovieData");
                if (konfirmasi == 1) {
                    rewind(file);
                    fwrite(filmArray, sizeof(MovieData), totalRecords, file);
                    TampilkanPesan("\nData film berhasil diperbarui.\n", 2);
                } else {
                    TampilkanPesan("\nPembaruan film dibatalkan.\n", 2);
                }
                break;
            }
        }

        fclose(file);
    }