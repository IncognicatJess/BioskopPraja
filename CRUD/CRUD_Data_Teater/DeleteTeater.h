#define TEMP_TEATERDAT "./Database/Teater/TempDataTeater.dat"

void HapusTeater();
int BandingkanIDTeater(const void *a, const void *b);
int DeleteKursi(char idHapus[10]);

int DeleteTeater() {
    ReadTeater();
    printf("\n==== Hapus Teater ====\n");
    HapusTeater();
    return 0;
}

void HapusTeater() {
    FILE *file = fopen(TEATERDAT, "rb");
    FILE *tempFile = fopen(TEMP_TEATERDAT, "wb");

    if (!file || !tempFile) {
        printf("Gagal membuka file database teater.\n");
        if (file) fclose(file);
        if (tempFile) fclose(tempFile);
        return;
    }

    char idHapus[10] = {0};
    printf("Masukkan ID teater yang ingin dihapus: ");
    
    // Input ID F&B  dan deteksi "Esc"
    int i = 0;
    while (1) {
        char ch = getch(); // Ambil input karakter per karakter

        if (ch == 27) { // Jika tombol "Esc" ditekan (kode ASCII 27)
            TampilkanPesan("\nProses penghapusan teater dibatalkan.\n", 2);
            fclose(file);
            fclose(tempFile);
            remove(TEMP_TEATERDAT);
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

    // Validasi: Cek apakah teater terdaftar di jadwal tayang
    FILE *fileJadwal = fopen(SCHEDULEDAT, "rb");
    if (fileJadwal) {
        ScheduleData jadwal;
        while (fread(&jadwal, sizeof(ScheduleData), 1, fileJadwal)) {
            if (strcmp(jadwal.IDTeater, idHapus) == 0) {
                fclose(fileJadwal);
                fclose(file);
                fclose(tempFile);
                remove(TEMP_TEATERDAT);
                TampilkanPesan("\nTeater tidak dapat dihapus karena masih terdaftar di jadwal tayang.\n", 2);
                return;
            }
        }
        fclose(fileJadwal);
    }

    TeaterData teater;
    TeaterData teaterDihapus;
    bool ditemukan = false;

    while (fread(&teater, sizeof(TeaterData), 1, file)) {
        if (strcmp(teater.ID, idHapus) == 0) {
            ditemukan = true;
            teaterDihapus = teater;
        } else {
            fwrite(&teater, sizeof(TeaterData), 1, tempFile);
        }
    }

    fclose(file);
    fclose(tempFile);

    if (ditemukan) {
        // Konfirmasi sebelum penghapusan
        int konfirmasi = TombolKonfirmasi("Teater", "Hapus", &teaterDihapus, "TeaterData");
        if (konfirmasi == 1) { // KONFIRMASI
            DeleteKursi(idHapus);
            remove(TEATERDAT);
            rename(TEMP_TEATERDAT, TEATERDAT);
            printf("Teater dengan ID %s berhasil dihapus.\n", idHapus);
            sleep(2);
        } else { // BATAL
            TampilkanPesan("Penghapusan dibatalkan.\n", 2);
            remove(TEMP_TEATERDAT);
        }
    } else {
        remove(TEMP_TEATERDAT);
        printf("Teater dengan ID %s tidak ditemukan.\n", idHapus);
        sleep(2);
    }
}
