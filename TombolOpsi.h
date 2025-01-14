int PilihOpsi(const char *master, const char *opsi[], int jumlah);
int ReadAkun();
int ReadFilm();

int PilihOpsi(const char *master, const char *opsi[], int jumlah)
{
    int indeks = 0;
    char key;

    while (1)
    {
        system("cls");

        if(strcmp(master,"Akun") == 0){
            ReadAkun();
            printf("Apakah anda yakin ingin mengganti sandi pada admin utama?\n");
        }
        else if(strcmp(master,"Film") == 0){
            ReadFilm();
        }else{
            TampilkanPesan("Data Belum Tersedia!\n", 1);
        }
        
        for (int i = 0; i < jumlah; i++)
        {
            if (i == indeks)
            {
                printf(" >[%s]\n", opsi[i]);
            }
            else
            {
                printf("  [%s]\n", opsi[i]);
            }
        }

        key = getch();
        if (key == 75 || key == 72) // Panah kiri
            indeks = (indeks - 1 + jumlah) % jumlah;
        if (key == 77 || key == 80) // Panah kanan
            indeks = (indeks + 1) % jumlah;
        if (key == '\r') // Enter
            return indeks;
    }
}
