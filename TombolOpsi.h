int PilihOpsi(const char *master, const char *opsi[], void *data, void *data2, int jumlah);
int ReadAkun();
int ReadFilm();
int ReadFnb();
void ReadProfile(AkunData *akun, ProfilData *profil);
int ReadTeater();
int ReadSchedule();

int PilihOpsi(const char *master, const char *opsi[], void *data, void *data2, int jumlah)
{
    int indeks = 0;
    char key;

    while (1)
    {
        system("cls");

        if (strcmp(master, "Akun") == 0)
        {
            ReadAkun();
        }
        else if (strcmp(master, "Film") == 0)
        {
            ReadFilm();
        }
        else if (strcmp(master, "Profil") == 0 && data != NULL)
        {
            AkunData *akun = (AkunData *)data;
            ProfilData *profil = (ProfilData *)data2;
            ReadProfile(akun, profil);
        }
        else if (strcmp(master, "Teater") == 0)
        {
            ReadTeater();
        }
        else if (strcmp(master, "Fnb") == 0)
        {
            ReadFnb();
        }
        else if (strcmp(master, "Schedule") == 0)
        {
            ReadSchedule();
            
        }
        else
        {
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
