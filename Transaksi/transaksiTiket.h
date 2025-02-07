#define MAX_TRANSC 10000
#define MAX_JAM 10 // Maksimal jam tayang per tanggal adalah 10
#define MAX_SHOWING 50

void PemilihanFilm();
void PemilihanKursi(Tiket pesanan);

void PemesananTiket()
{
    ReadScheduleShowing();
    PemilihanFilm();

    // FUNGSI PEMILIHAN FILM
    // FUNGSI PEMILIHAN KURSI
    // FUNGSI INVOICE
}

void PemilihanFilm()
{

    FILE *file = fopen(SCHEDULEDAT, "rb");
    if (!file)
    {
        printf("Gagal membuka file %s. Pastikan file tersebut ada.\n", SCHEDULEDAT);
        return;
    }

    Tiket Pesanan;
    JamTayangTransc jamTayang;
    ScheduleData jadwal[MAX_SHOWING];
    int jumlahJadwal = 0;

    while (fread(&jadwal[jumlahJadwal], sizeof(ScheduleData), 1, file))
    {
        jumlahJadwal++;
    }
    fclose(file);

    // Filter film unik dengan status "Now Showing"
    char filmUnik[MAX_SHOWING][50];
    int jumlahFilmUnik = 0;
    for (int i = 0; i < jumlahJadwal; i++)
    {
        if (strcmp(jadwal[i].status, "Now Showing") == 0)
        { // Hanya ambil film dengan status "Now Showing"
            bool sudahAda = false;
            for (int j = 0; j < jumlahFilmUnik; j++)
            {
                if (strcmp(jadwal[i].judulFilm, filmUnik[j]) == 0)
                {
                    sudahAda = true;
                    break;
                }
            }
            if (!sudahAda)
            {
                strcpy(filmUnik[jumlahFilmUnik], jadwal[i].judulFilm);
                jumlahFilmUnik++;
            }
        }
    }

    // Jika tidak ada film dengan status "Now Showing"
    if (jumlahFilmUnik == 0)
    {
        printf("Tidak ada film yang sedang tayang.\n");
        return;
    }

    int step = 0;
    int indeksJudul = 0, indeksTanggal = 0, indeksJam = 0;
    int jumlahTiket = 1;
    char key;

    char tanggalUnik[MAX_SHOWING][15];
    int jumlahTanggalUnik = 0;
    char jamUnik[MAX_SHOWING][6];
    int jumlahJamUnik = 0;

    while (1)
    {
        system("cls");
        ReadScheduleShowing();
        printf("\n");

        printf("==== Pemesanan Tiket ====\n\n");

        // Tampilkan pilihan film (hanya "Now Showing")
        printf("Pilih Film:\t");
        for (int i = 0; i < jumlahFilmUnik; i++)
        {
            // printf(" %s[%s]\t", (i == indeksJudul && step == 0) ? ">" : " ", filmUnik[i]);

            if (i == indeksJudul && step == 0)
            {
                printf("  >[%s]\t", filmUnik[i]);
            }
            else if (i == indeksJudul)
            {
                printf("  #[%s]\t ", filmUnik[i]);
            }
            else
            {
                printf("   [%s]\t", filmUnik[i]);
            }
        }

        // Tampilkan pilihan tanggal jika step >= 1
        if (step >= 1)
        {
            printf("\n\nPilih Tanggal:\t");
            jumlahTanggalUnik = 0;

            for (int i = 0; i < jumlahJadwal; i++)
            {
                if (strcmp(jadwal[i].judulFilm, filmUnik[indeksJudul]) == 0 &&
                    strcmp(jadwal[i].status, "Now Showing") == 0)
                { // Pastikan status "Now Showing"
                    char buffer[15];
                    sprintf(buffer, "%02d/%02d/%04d", jadwal[i].Tanggal.tanggal, jadwal[i].Tanggal.bulan, jadwal[i].Tanggal.tahun);

                    bool sudahAda = false;
                    for (int j = 0; j < jumlahTanggalUnik; j++)
                    {
                        if (strcmp(buffer, tanggalUnik[j]) == 0)
                        {
                            sudahAda = true;
                            break;
                        }
                    }
                    if (!sudahAda)
                    {
                        strcpy(tanggalUnik[jumlahTanggalUnik], buffer);
                        jumlahTanggalUnik++;
                    }
                }
            }

            for (int i = 0; i < jumlahTanggalUnik; i++)
            {
                //  printf(" %s[%s]\t", (i == indeksTanggal && step == 1) ? ">" : " ", tanggalUnik[i]);

                if (i == indeksTanggal && step == 1)
                {
                    printf("  >[%s]\t", tanggalUnik[i]);
                }
                else if (i == indeksTanggal)
                {
                    printf("  #[%s]\t ", tanggalUnik[i]);
                }
                else
                {
                    printf("   [%s]\t", tanggalUnik[i]);
                }
            }
        }

        // Tampilkan pilihan jam jika step >= 2
        if (step >= 2)
        {
            printf("\n\nPilih Jam:\t");
            jumlahJamUnik = 0;

            // Ambil tanggal yang dipilih
            int tanggal, bulan, tahun;
            sscanf(tanggalUnik[indeksTanggal], "%d/%d/%d", &tanggal, &bulan, &tahun);

            // Filter jam tayang berdasarkan tanggal yang dipilih dan status "Now Showing"
            for (int i = 0; i < jumlahJadwal; i++)
            {
                if (strcmp(jadwal[i].judulFilm, filmUnik[indeksJudul]) == 0 &&
                    jadwal[i].Tanggal.tanggal == tanggal &&
                    jadwal[i].Tanggal.bulan == bulan &&
                    jadwal[i].Tanggal.tahun == tahun &&
                    strcmp(jadwal[i].status, "Now Showing") == 0)
                { // Pastikan status "Now Showing"
                    char buffer[6];
                    sprintf(buffer, "%02d:%02d", jadwal[i].jamTayang.jam, jadwal[i].jamTayang.menit);

                    bool sudahAda = false;
                    for (int j = 0; j < jumlahJamUnik; j++)
                    {
                        if (strcmp(buffer, jamUnik[j]) == 0)
                        {
                            sudahAda = true;
                            break;
                        }
                    }
                    if (!sudahAda)
                    {
                        strcpy(jamUnik[jumlahJamUnik], buffer);
                        jumlahJamUnik++;
                    }
                }
            }

            for (int i = 0; i < jumlahJamUnik; i++)
            {
                // printf(" \n%s[%s]\t", (i == indeksJam && step == 2) ? ">" : " ", jamUnik[i]);

                if (i == indeksJam && step == 2)
                {
                    printf("  >[%s]\t", jamUnik[i]);
                }
                else if (i == indeksJam)
                {
                    printf("  #[%s]\t ", jamUnik[i]);
                }
                else
                {
                    printf("   [%s]\t", jamUnik[i]);
                }
            }
        }

        // Tampilkan input jumlah tiket jika step == 3
        if (step == 3)
        {
            printf("\n\nJumlah Tiket: [%d]\n", jumlahTiket);
        }

        // Handle input pengguna
        key = getch();
        if (key == 27)
        { // Esc untuk keluar
            printf("Pemesanan dibatalkan.\n");
            return;
        }
        else if (key == 13)
        { // Enter untuk lanjut
            if (step < 3)
            {
                step++;
            }
            else
            {
                // Validasi jumlah tiket
                if (jumlahTiket < 1 || jumlahTiket > 20)
                {
                    printf("Jumlah tiket maksimal 20!\n");
                    getch();
                    return;
                }
                else
                {

                    // Tampilkan hasil pemesanan

                    // Menyimpan data sebagai pesanan
                    strncpy(Pesanan.judulFilm, filmUnik[indeksJudul], sizeof(Pesanan.judulFilm) - 1);
                    Pesanan.judulFilm[sizeof(Pesanan.judulFilm) - 1] = '\0';

                    Pesanan.Tanggal.tanggal = atoi(&tanggalUnik[indeksTanggal][0]);
                    Pesanan.Tanggal.bulan = atoi(&tanggalUnik[indeksTanggal][3]);
                    Pesanan.Tanggal.tahun = atoi(&tanggalUnik[indeksTanggal][6]);

                    Pesanan.jamTayang.jam = atoi(&jamUnik[indeksJam][0]);
                    Pesanan.jamTayang.menit = atoi(&jamUnik[indeksJam][3]);

                    Pesanan.tiket = jumlahTiket;

                    // perulangan untuk membandingkan pesanan dengan scheduldata

                    // Tampilkan hasil pemesanan

                    for (int i = 0; i < jumlahJadwal; i++)
                    {
                        int judul = strcmp(jadwal[i].judulFilm, Pesanan.judulFilm);

                        // Perulangan mencocokkan pesanan dengan jadwal tayang yang tersedia
                        if (judul == 0 && jadwal[i].Tanggal.tanggal == Pesanan.Tanggal.tanggal &&
                            jadwal[i].Tanggal.bulan == Pesanan.Tanggal.bulan &&
                            jadwal[i].Tanggal.tahun == Pesanan.Tanggal.tahun &&
                            jadwal[i].jamTayang.jam == Pesanan.jamTayang.jam &&
                            jadwal[i].jamTayang.menit == Pesanan.jamTayang.menit)
                        {
                            // Setelah cocok dapatkan ID,No Teater dari jadwal tayang tersebut serta jumlah tiket

                            strncpy( Pesanan.judulFilm, jadwal[i].judulFilm, sizeof(Pesanan.judulFilm));
                            Pesanan.judulFilm[sizeof(Pesanan.judulFilm) - 1] = '\0';

                            strncpy(Pesanan.IDTeater, jadwal[i].IDTeater, sizeof(Pesanan.IDTeater));
                            Pesanan.IDTeater[sizeof(Pesanan.IDTeater) - 1] = '\0';

                            Pesanan.Tanggal.tanggal = jadwal[i].Tanggal.tanggal;
                            Pesanan.Tanggal.bulan = jadwal[i].Tanggal.bulan;
                            Pesanan.Tanggal.tahun = jadwal[i].Tanggal.tahun;
                            Pesanan.jamTayang.jam = jadwal[i].jamTayang.jam;
                            Pesanan.jamTayang.menit = jadwal[i].jamTayang.menit;

                            Pesanan.Teater = jadwal[i].Teater;
                            Pesanan.tiket = jumlahTiket;
                            Pesanan.harga = jadwal[i].harga;
                            break; // Keluar dari perulangan setelah menemukan jadwal yang cocok
                        }
                        else if (i == jumlahJadwal - 1)
                        {
                            TampilkanPesan("Jadwal tayang tidak sesuai!", 2);
                            return; // Keluar dari fungsi jika tidak ada jadwal yang cocok
                        }
                    }

                    break; // Keluar dari loop jika pemesanan valid
                    //}
                }
            }
        }
        else if (key == 75 || key == 77)
        { // Panah kiri/kanan
            if (step == 0)
            {
                indeksJudul = (key == 75) ? (indeksJudul - 1 + jumlahFilmUnik) % jumlahFilmUnik : (indeksJudul + 1) % jumlahFilmUnik;
            }
            else if (step == 1)
            {
                indeksTanggal = (key == 75) ? (indeksTanggal - 1 + jumlahTanggalUnik) % jumlahTanggalUnik : (indeksTanggal + 1) % jumlahTanggalUnik;
            }
            else if (step == 2)
            {
                indeksJam = (key == 75) ? (indeksJam - 1 + jumlahJamUnik) % jumlahJamUnik : (indeksJam + 1) % jumlahJamUnik;
            }
            else if (step == 3)
            {
                jumlahTiket = (key == 75) ? (jumlahTiket - 1 > 0 ? jumlahTiket - 1 : 1) : (jumlahTiket + 1 <= 20 ? jumlahTiket + 1 : 20);
            }
        }
    }

  
    const char *menuPemesananTiket[] = {"KEMBALI", "PILIH KURSI"};

    int pilihan = PilihOpsi("TicketBooking", menuPemesananTiket, &Pesanan, NULL, 2);

    switch (pilihan)
    {
    case 0:
        break;
    case 1:
        system("cls");
        PemilihanKursi(Pesanan);
        break;
    }
    if (pilihan == 0)
    {
        memset(&Pesanan, 0, sizeof(Tiket));
        tampilkanPemesananTiket();
    }

    //    printf("Klik sembarang tombol untuk kembali!");
    //  getch();
}
