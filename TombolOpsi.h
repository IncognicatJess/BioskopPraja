int PilihOpsi(const char *master, const char *opsi[], void *data, void *data2, int jumlah);
int ReadAkun();
int ReadFilm();
int ReadFnb();
void ReadProfile(AkunData *akun, ProfilData *profil);
int ReadTeater();
int ReadSchedule();
void BacaTransTiket();

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
        else if (strcmp(master, "Laporan") == 0)
        {
            printf("Silahkan Pilih Laporan Transaski TIket atau F&B.\n\n");
        }
        else if (strcmp(master, "RiwayatTiket") == 0)
        {
            BacaTransTiket();
        }
        else if (strcmp(master, "ScheduleShowing") == 0)
        {
            ReadScheduleShowing();
        }
        else if (strcmp(master, "TicketBooking") == 0)
        {
            Tiket *Pesanan = (Tiket *)data;
            ReadScheduleShowing();

            printf("\nAnda akan melakukan pemesanan berikut: \n\n");
            printf("Film: %s\n", Pesanan->judulFilm);
            printf("Tanggal: %02d/%02d/%04d\n", Pesanan->Tanggal.tanggal, Pesanan->Tanggal.bulan, Pesanan->Tanggal.tahun);
            printf("Jam: %02d:%02d\n", Pesanan->jamTayang.jam, Pesanan->jamTayang.menit);
            printf("ID Teater: %s\n", Pesanan->IDTeater);
            printf("No Teater: %d\n", Pesanan->Teater);
            printf("Jumlah Tiket: %d\n", Pesanan->tiket);
            printf("Harga : Rp. %0.2lf\n", Pesanan->harga);
            printf("\n\n");
        }
        else if (strcmp(master, "Seat") == 0)
        {
            Tiket *Pesanan = (Tiket *)data;
            KursiData *kursiTeater = (KursiData *)data2;
            ReadScheduleShowing();

            printf("\nAnda akan melakukan pemesanan berikut: \n\n");
            printf("Film        : %s\n", Pesanan->judulFilm);
            printf("Tanggal     : %02d/%02d/%04d\n", Pesanan->Tanggal.tanggal, Pesanan->Tanggal.bulan, Pesanan->Tanggal.tahun);
            printf("Jam         : %02d:%02d\n", Pesanan->jamTayang.jam, Pesanan->jamTayang.menit);
            printf("ID Teater   : %s\n", Pesanan->IDTeater);
            printf("No Teater   : %d\n", Pesanan->Teater);
            printf("Jumlah Tiket: %d\n", Pesanan->tiket);
            printf("Harga       : Rp. %0.2lf\n", Pesanan->harga);

            printf("ID Kursi yang dipesan: ");
            // Cetak ID kursi yang dipesan
            for (int i = 0; i < Pesanan->tiket; i++)
            {
                printf("%s", Pesanan->IDkursi[i]);
                if (i < Pesanan->tiket - 1)
                {
                    printf(", ");
                }
            }
            printf("\n\n");
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
