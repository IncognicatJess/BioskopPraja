#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h> // Untuk getch()

#define TEMP_FILEFILM "./Database/Film/TempDataFilm.dat"
#define SCHEDULEDAT "./Database/JadwalTayang/DataJadwalTayang.dat"

void HapusFilm();
int BandingkanIDFilm(const void *a, const void *b);

int DeleteFilm() {
    printf("\n==== Hapus Film ====\n");
    HapusFilm();
    return 0;
}

void HapusFilm() {
    FILE *file = fopen(FILEFILM, "rb");
    FILE *tempFile = fopen(TEMP_FILEFILM, "wb");

    if (!file || !tempFile) {
        printf("Gagal membuka file database.\n");
        if (file) fclose(file);
        if (tempFile) fclose(tempFile);
        return;
    }

    char idHapus[10] = {0}; // Inisialisasi array untuk menyimpan ID
    printf("Masukkan ID film yang ingin dihapus (tekan Esc untuk membatalkan): ");

    // Input ID film dengan fgets dan deteksi "Esc"
    int i = 0;
    while (1) {
        char ch = getch(); // Ambil input karakter per karakter

        if (ch == 27) { // Jika tombol "Esc" ditekan (kode ASCII 27)
            TampilkanPesan("\nProses penghapusan film dibatalkan.\n", 2);
            fclose(file);
            fclose(tempFile);
            remove(TEMP_FILEFILM);
            return; // Keluar dari fungsi
        } else if (ch == '\r') { // Jika tombol "Enter" ditekan
            idHapus[i] = '\0'; // Akhiri string
            break;
        } else if (ch == 8 && i > 0) { // Jika tombol "Backspace" ditekan
            i--;
            printf("\b \b"); // Hapus karakter terakhir dari layar
        } else if (i < 9 && (isalnum(ch) || ch == ' ')) { // Hanya terima alfanumerik atau spasi
            idHapus[i++] = ch;
            putchar(ch); // Tampilkan karakter ke layar
        }
    }

    // Validasi: Cek apakah film terdaftar di jadwal tayang
    FILE *fileJadwal = fopen(SCHEDULEDAT, "rb");
    if (fileJadwal) {
        ScheduleData jadwal;
        while (fread(&jadwal, sizeof(ScheduleData), 1, fileJadwal)) {
            if (strcmp(jadwal.IDFilm, idHapus) == 0) {
                fclose(fileJadwal);
                fclose(file);
                fclose(tempFile);
                remove(TEMP_FILEFILM);
                TampilkanPesan("\nFilm tidak dapat dihapus karena masih terdaftar di jadwal tayang.\n", 2);
                return;
            }
        }
        fclose(fileJadwal);
    }

    MovieData film;
    MovieData filmDihapus;
    bool ditemukan = false;

    while (fread(&film, sizeof(MovieData), 1, file)) {
        if (strcmp(film.ID, idHapus) == 0) {
            ditemukan = true;
            filmDihapus = film;
        } else {
            fwrite(&film, sizeof(MovieData), 1, tempFile);
        }
    }

    fclose(file);
    fclose(tempFile);

    if (ditemukan) {
        // Tampilkan data film yang akan dihapus
        printf("\nFilm yang akan dihapus:\n");
        printf("ID: %s | Judul: %s | Genre: %s | Tahun: %d | Durasi: %.0f menit | Harga: %.2f\n",
               filmDihapus.ID, filmDihapus.judul, filmDihapus.genre, filmDihapus.tahunRelease, filmDihapus.durasi, filmDihapus.harga);

        // Konfirmasi penghapusan
        int konfirmasi = TombolKonfirmasi("Film", "Hapus", &filmDihapus, "MovieData");
        if (konfirmasi == 1) { // KONFIRMASI
            remove(FILEFILM);
            rename(TEMP_FILEFILM, FILEFILM);
            TampilkanPesan("\nFilm berhasil dihapus.\n", 2);
        } else { // BATAL
            remove(TEMP_FILEFILM);
            TampilkanPesan("\nPenghapusan dibatalkan.\n", 2);
        }
    } else {
        remove(TEMP_FILEFILM);
        TampilkanPesan("\nFilm dengan ID tersebut tidak ditemukan.\n", 2);
    }
}