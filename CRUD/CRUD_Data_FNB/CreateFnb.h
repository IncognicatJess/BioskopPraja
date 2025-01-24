#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <stdbool.h>

//#define FILEMENU "./Database/Fnb/Menu.dat"
#define MAX_ID 1000
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_ENTER '\r'


void BuatMenu();

int CreateFnb() {
    BuatMenu();
    return 0;
}
void BuatMenu() {
    FILE *file = fopen(FILEMENU, "a+b");
    if (!file) {
        printf("Gagal membuka file database\n");
        return;
    }

    FnbData menu;
    memset(&menu, 0, sizeof(FnbData));

    const char *pilihanKategori[] = {"Makanan", "Minuman"};
    int pilihanKategoriIndex = 0;
    int step = 0;
    char key;

    char nama[50] = "", stokStr[10] = "", hargaStr[10] = "";

    while (1) {
        system("cls"); // Bersihkan layar untuk tampilan baru
        printf("==== Tambah Menu ====\n");

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
            strncpy(menu.namaMakanan, nama, sizeof(menu.namaMakanan) - 1);
            menu.stok = atoi(stokStr);
            menu.harga = atof(hargaStr);
            strncpy(menu.kategori, pilihanKategori[pilihanKategoriIndex], sizeof(menu.kategori) - 1);

            // Tampilkan konfirmasi menggunakan TombolKonfirmasi
            int konfirmasi = TombolKonfirmasi("Fnb", "Buat", &menu, "FnbData");
            if (konfirmasi == 1) { // KONFIRMASI
                // Generate ID baru
                bool idTerpakai[MAX_ID] = {false};
                FnbData temp;
                rewind(file);
                while (fread(&temp, sizeof(FnbData), 1, file)) {
                    if (strncmp(temp.ID, "FNB", 3) == 0) {
                        int idNum = atoi(&temp.ID[3]);
                        if (idNum > 0 && idNum < MAX_ID) {
                            idTerpakai[idNum] = true;
                        }
                    }
                }

                int idBaru = 1;
                while (idBaru < MAX_ID && idTerpakai[idBaru]) {
                    idBaru++;
                }
                snprintf(menu.ID, sizeof(menu.ID), "FNB%03d", idBaru);

                // Tulis ke file
                fwrite(&menu, sizeof(FnbData), 1, file);
                printf("Menu berhasil ditambahkan!\n");
                break;
            } else { // BATAL
                printf("Pembuatan menu dibatalkan.\n");
                break;
            }
        }

        key = getch();
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

    fclose(file);
}