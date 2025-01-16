int TombolKonfirmasi(const char *master, const char *opsi, void *data, const char *tipeData)
{
    const char *pilihan[] = {"BATAL", "KONFIRMASI"};
    int indeks = 0;
    char key;

    if (!data || !master || !opsi || !tipeData)
    {
        TampilkanPesan("Parameter tidak valid.\n", 2);
        return -1; // Nilai indikasi error
    }

    while (1)
    {
        system("cls");

        if (strcmp(master, "Akun") == 0 && strcmp(tipeData, "AkunData") == 0)
        {
            AkunData *akun = (AkunData *)data;
            if (strcmp(opsi, "Buat") == 0)
            {
                ReadAkun();
                printf("Apakah anda yakin ingin membuat akun %s dengan username %s dan sandi %s?\n", akun->akun, akun->username, akun->sandi);
            }
            else if (strcmp(opsi, "Perbarui") == 0)
            {
                ReadAkun();
                printf("Apakah anda yakin ingin memperbarui akun %s %s?\n", akun->akun, akun->ID);
            }
            else if (strcmp(opsi, "Hapus") == 0)
            {
                ReadAkun();
                printf("Apakah anda yakin ingin menghapus akun %s %s dengan username %s?\n", akun->akun, akun->ID, akun->username);
            }
            else
            {
                TampilkanPesan("Maaf fitur belum tersedia\n", 2);
            }
        }
        else if (strcmp(master, "Profil") == 0 && strcmp(tipeData, "ProfilData") == 0)
        {
            ProfilData *profil = (ProfilData *)data;
            if (strcmp(opsi, "Edit") == 0)
            {
                printf("Apakah anda yakin ingin memperbarui profil berikut?\n");
                printf("Nama   : %s\n", profil->nama);
                printf("TTL    : %s, %02d/%02d/%04d\n", profil->TTL.tempat, profil->TTL.tanggal, profil->TTL.bulan, profil->TTL.tahun);
                printf("No HP  : %s\n", profil->noHP);
            }
            else
            {
                TampilkanPesan("Maaf fitur belum tersedia\n", 2);
            }
        }
        else
        {
            TampilkanPesan("Tipe data atau fitur belum tersedia.\n", 2);
        }

        for (int i = 0; i < 2; i++)
        {
            if (i == indeks)
            {
                printf(" >[%s]\n", pilihan[i]);
            }
            else
            {
                printf("  [%s]\n", pilihan[i]);
            }
        }

        key = getch();
        if (key == 75 || key == 72) // Panah kiri atau atas
            indeks = (indeks - 1 + 2) % 2;
        else if (key == 77 || key == 80) // Panah kanan atau bawah
            indeks = (indeks + 1) % 2;
        else if (key == '\r') // Enter
            return indeks;
    }
}
