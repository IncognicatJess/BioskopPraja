void ReadProfile(AkunData *akun, ProfilData *profil);

void ReadProfile(AkunData *akun, ProfilData *profil) {
    FILE *file = fopen(PROFILDAT, "rb");

    if (!file) {
        printf("Gagal membuka file %s. Pastikan file tersebut ada.\n", PROFILDAT);
        return;
    }

    // Membaca data profil dari file
    if (fread(profil, sizeof(ProfilData), 1, file) != 1) {
        memset(profil, 0, sizeof(ProfilData)); // Jika kosong, reset profil
    }
    fclose(file);

    system("cls");
    printf("=== PROFIL ===\n");
    printf("ID       : %s\n", akun->ID);
    printf("Username : %s\n", akun->username);
    printf("Nama     : %s\n", profil->nama[0] ? profil->nama : "-");

    // Cek validitas TTL
    if (profil->TTL.tempat[0] && profil->TTL.tanggal > 0 && profil->TTL.bulan > 0 && profil->TTL.tahun > 0) {
        printf("TTL      : %s, %02d/%02d/%04d\n", 
               profil->TTL.tempat, profil->TTL.tanggal, profil->TTL.bulan, profil->TTL.tahun);
    } else {
        printf("TTL      : -\n");
    }

    printf("Jabatan  : %s\n", akun->jabatan);
    printf("No HP    : %s\n", profil->noHP[0] ? profil->noHP : "-");
    printf("\n\n");
}
