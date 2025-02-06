void EditMenu();

// Fungsi untuk membaca dan menampilkan daftar film (debugging)
int UpdateFnb()
{
    printf("\n==== Data Menu F&B ====\n");
    EditMenu();
    return 0;
}
void EditMenu() {
    FILE *file = fopen(FILEMENU, "rb");
    if (!file) {
        printf("Gagal membuka file database.\n");
        return;
    }

    // Baca semua record ke memori
    FnbData menuArray[MAX_ID];
    int totalRecords = 0;

    while (fread(&menuArray[totalRecords], sizeof(FnbData), 1, file) == 1) {
        totalRecords++;
    }
    fclose(file);

    // Cari menu berdasarkan ID
    char idCari[10] = {0};
    printf("Masukkan ID menu yang ingin diedit: ");
    
    // Input ID F&B dan deteksi "Esc"
    int i = 0;
    while (1) {
        char ch = getch(); // Ambil input karakter per karakter

        if (ch == 27) { // Jika tombol "Esc" ditekan (kode ASCII 27)
            TampilkanPesan("\nProses pembaruan F&B dibatalkan.\n", 2);
            fclose(file);
            return; // Keluar dari fungsi
        } else if (ch == '\r') { // Jika tombol "Enter" ditekan
            idCari[i] = '\0'; // Akhiri string
            break;
        } else if (ch == 8 && i > 0) { // Jika tombol "Backspace" ditekan
            i--;
            printf("\b \b"); // Hapus karakter terakhir dari layar
        } else if (i < 9 && (isalnum(ch) || ch == ' ')) { // Hanya terima alfanumerik atau spasi
            idCari[i++] = ch;
            putchar(ch); // Tampilkan karakter ke layar
        }
    }

    int targetIndex = -1;
    for (int i = 0; i < totalRecords; i++) {
        if (strcmp(menuArray[i].ID, idCari) == 0) {
            targetIndex = i;
            break;
        }
    }

    if (targetIndex == -1) {
        printf("Menu dengan ID %s tidak ditemukan.\n", idCari);
        return;
    }

    FnbData *menu = &menuArray[targetIndex];
    const char *pilihanKategori[] = {"Makanan", "Minuman"};
    int pilihanKategoriIndex = 0;
    char nama[50] = "", stokStr[10] = "", hargaStr[10] = "";
    int step = 0;

    // Inisialisasi data menu yang akan diedit
    strncpy(nama, menu->namaMakanan, sizeof(nama) - 1);
    snprintf(stokStr, sizeof(stokStr), "%d", menu->stok);
    snprintf(hargaStr, sizeof(hargaStr), "%.2f", menu->harga);

    // Cari indeks kategori yang sedang dipilih
    for (int i = 0; i < 2; i++) {
        if (strcmp(menu->kategori, pilihanKategori[i]) == 0) {
            pilihanKategoriIndex = i;
            break;
        }
    }

    while (1) {
        system("cls");
        printf("==== Edit Menu ====\n");

        printf("Nama menu  : %s%s\n", step == 0 ? ">" : "", nama);
        printf("Stok       : %s%s\n", step == 1 ? ">" : "", stokStr);
        printf("Harga (Rp) : %s%s\n", step == 2 ? ">" : "", hargaStr);
        printf("Kategori   : ");
        for (int i = 0; i < 2; i++) {
            if (i == pilihanKategoriIndex && step == 3) {
                printf(">[%s] ", pilihanKategori[i]); // Sorot pilihan
            } else if (i == pilihanKategoriIndex) {
                printf("#[%s] ", pilihanKategori[i]); // Sedang dipilih
            } else {
                printf(" [%s] ", pilihanKategori[i]); // Belum dipilih
            }
        }
        printf("\n");

        if (step == 4) { // Konfirmasi
            // Simpan data ke struct
            strncpy(menu->namaMakanan, nama, sizeof(menu->namaMakanan) - 1);
            menu->stok = atoi(stokStr);
            menu->harga = atof(hargaStr);
            strncpy(menu->kategori, pilihanKategori[pilihanKategoriIndex], sizeof(menu->kategori) - 1);

            // Tampilkan konfirmasi menggunakan TombolKonfirmasi
            int konfirmasi = TombolKonfirmasi("Fnb", "Perbarui", menu, "FnbData");
            if (konfirmasi == 1) { // KONFIRMASI
                file = fopen(FILEMENU, "wb");
                if (!file) {
                    printf("Gagal membuka file untuk menulis.\n");
                    return;
                }
                fwrite(menuArray, sizeof(FnbData), totalRecords, file);
                fclose(file);
                printf("Data menu berhasil diperbarui.\n");
                break;
            } else { // BATAL
                printf("Pembaruan menu dibatalkan.\n");
                break;
            }
        }

        char key = getch();
         // Tombol "Esc" untuk membatalkan
        if (key == 27) // 27 adalah kode ASCII untuk tombol "Esc"
        {
            TampilkanPesan("\nProses pembaruan F&B dibatalkan.\n", 2);
            fclose(file);
            return; // Keluar dari fungsi
        }

        if (step == 0) { // Input nama
            if (isalnum(key) || key == ' ' || key == '.') {
                size_t len = strlen(nama);
                if (len < sizeof(nama) - 1) {
                    nama[len] = key;
                    nama[len + 1] = '\0';
                }
            } else if (key == 8 && strlen(nama) > 0) { // Backspace
                nama[strlen(nama) - 1] = '\0';
            } else if (key == KEY_ENTER && strlen(nama) > 0) {
                step++;
            }
        } else if (step == 1) { // Input stok
            if (isdigit(key)) {
                size_t len = strlen(stokStr);
                if (len < sizeof(stokStr) - 1) {
                    stokStr[len] = key;
                    stokStr[len + 1] = '\0';
                }
            } else if (key == 8 && strlen(stokStr) > 0) { // Backspace
                stokStr[strlen(stokStr) - 1] = '\0';
            } else if (key == KEY_ENTER && strlen(stokStr) > 0) {
                int stok = atoi(stokStr);
                if (stok >= 0) {
                    step++;
                } else {
                    printf("Stok tidak boleh negatif.\n");
                }
            }
        } else if (step == 2) { // Input harga
            if (isdigit(key) || key == '.') {
                size_t len = strlen(hargaStr);
                if (len < sizeof(hargaStr) - 1) {
                    hargaStr[len] = key;
                    hargaStr[len + 1] = '\0';
                }
            } else if (key == 8 && strlen(hargaStr) > 0) { // Backspace
                hargaStr[strlen(hargaStr) - 1] = '\0';
            } else if (key == KEY_ENTER && strlen(hargaStr) > 0) {
                double harga = atof(hargaStr);
                if (harga >= 0) {
                    step++;
                } else {
                    printf("Harga tidak boleh negatif.\n");
                }
            }
        } else if (step == 3) { // Pilih kategori
            if (key == KEY_LEFT || key == KEY_UP) {
                pilihanKategoriIndex = (pilihanKategoriIndex - 1 + 2) % 2;
            } else if (key == KEY_RIGHT || key == KEY_DOWN) {
                pilihanKategoriIndex = (pilihanKategoriIndex + 1) % 2;
            } else if (key == KEY_ENTER) {
                step++;
            }
        }
    }
}