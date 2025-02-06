void HapusMenu();

int DeleteFnb()
{
    printf("\n==== Hapus Menu ====\n");
    HapusMenu();
    return 0;
}
void HapusMenu() {
    FILE *file = fopen(FILEMENU, "rb");
    FILE *tempFile = fopen(TEMP_FILEMENU, "wb");

    if (!file || !tempFile) {
        printf("Gagal membuka file database.\n");
        if (file) fclose(file);
        if (tempFile) fclose(tempFile);
        return;
    }

    char idHapus[10] = {0};
    printf("Masukkan ID menu yang ingin dihapus: ");
    

    // Input ID F&B  dan deteksi "Esc"
    int i = 0;
    while (1) {
        char ch = getch(); // Ambil input karakter per karakter

        if (ch == 27) { // Jika tombol "Esc" ditekan (kode ASCII 27)
            TampilkanPesan("\nProses penghapusan F&B dibatalkan.\n", 2);
            fclose(file);
            fclose(tempFile);
            remove(TEMP_FILEMENU);
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

    FnbData menu;
    FnbData menuDihapus;
    bool ditemukan = false;

    // Baca semua data dari file
    while (fread(&menu, sizeof(FnbData), 1, file)) {
        if (strcmp(menu.ID, idHapus) == 0) {
            ditemukan = true;
            menuDihapus = menu;
        } else {
            fwrite(&menu, sizeof(FnbData), 1, tempFile);
        }
    }

    fclose(file);
    fclose(tempFile);

    if (ditemukan) {
        // Tampilkan data menu yang akan dihapus
        printf("\nMenu yang akan dihapus:\n");
        printf("ID      : %s\n", menuDihapus.ID);
        printf("Nama    : %s\n", menuDihapus.namaMakanan);
        printf("Kategori: %s\n", menuDihapus.kategori);
        printf("Stok    : %d\n", menuDihapus.stok);
        printf("Harga   : Rp. %.2f\n", menuDihapus.harga);

        // Konfirmasi penghapusan menggunakan TombolKonfirmasi
        int konfirmasi = TombolKonfirmasi("Fnb", "Hapus", &menuDihapus, "FnbData");
        if (konfirmasi == 1) { // KONFIRMASI
            remove(FILEMENU);
            rename(TEMP_FILEMENU, FILEMENU);
            printf("Menu dengan ID %s berhasil dihapus.\n", idHapus);
        } else { // BATAL
            remove(TEMP_FILEMENU);
            printf("Penghapusan dibatalkan.\n");
        }
    } else {
        remove(TEMP_FILEMENU);
        printf("Menu dengan ID %s tidak ditemukan.\n", idHapus);
    }
}