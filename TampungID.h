ProfilData validasiID(const char *username, const char *password) {
    ProfilData profil; // Struktur untuk menyimpan data profil
    AkunData akun; // Struktur untuk membaca data akun dari file
    FILE *file = fopen(FILENAME, "rb");
    if (!file) {
        printf("Gagal membuka file database.\n");
        strcpy(akun.ID, ""); // Atur ID kosong jika gagal
        return profil; // Kembalikan profil kosong
    }

    while (fread(&akun, sizeof(AkunData), 1, file)) {
        if (strcmp(akun.username, username) == 0 && strcmp(akun.sandi, password) == 0) {
            fclose(file);
            // Isi data profil
           // strcpy(profil.ID, akun.ID);
            //strcpy(profil.username, akun.username);
            //strcpy(profil.jabatan, akun.jabatan);
            return profil; // Kembalikan profil yang sesuai
        }
    }

    fclose(file);
    strcpy(profil.ID, ""); // Atur ID kosong jika tidak ditemukan
    return profil; // Kembalikan profil kosong
}

