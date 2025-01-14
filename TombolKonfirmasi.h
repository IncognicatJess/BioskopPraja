
int TombolKonfirmasi(const char *master, char opsi[10], AkunData *data);

int TombolKonfirmasi(const char *master, char opsi[10], AkunData *data)
{
    const char *pilihan[] = {"BATAL", "KONFIRMASI"};
    int indeks = 0;
    char key;

    while (1)
    {
        system("cls");
        //CRUD AKUN
        if (strcmp(master, "Akun") == 0)
        {
            ReadAkun();
            //CREATE
            if (strcmp(opsi, "Buat") == 0)
            {
                printf("Apakah anda yakin ingin membuat akun %s dengan username %s dan sandi %s\n", data->akun, data->username, data->sandi);
            }else if(strcmp(opsi, "Perbarui")==0){
                printf("Apakah anda yakin ingin memperbarui %s %s?\n", data->akun, data->ID);
            }
            //DELETE
            else if (strcmp(opsi, "Hapus") == 0)
            {
                printf("Apakah anda yakin ingin menghapus %s %s dengan username %s\n", data->akun, data->ID, data->username);
            }
            else
            {
                TampilkanPesan("Maaf fitur belum tersedia\n", 2);
            }
        }
        else
        {
            TampilkanPesan("Belum ada data!", 2);
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