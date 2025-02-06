#define MAX_TRANSC 10000
#define MAX_JAM 10 // Maksimal jam tayang per tanggal adalah 10
#define MAX_SHOWING 50

typedef struct
{
    int tanggal;
    int bulan;
    int tahun;
} TanggalTayangTransc;

typedef struct
{
    int jam;
    int menit;
} JamTayangTransc;

/*
typedef struct
{
    int jam;
    int menit;
} JamTayangAkhirTransc;

*/

typedef struct
{
    int tanggal;
    int bulan;
    int tahun;
} TanggalTransc;

typedef struct
{
    char ID[10];
    char IDFilm[10];
    char IDTeater[10];
    char judulFilm[50];
    int Teater;
    char IDkursi[10];
    char kategori[10];
    char bentuk[10];
    TanggalTayangTransc Tanggal;
    JamTayangTransc jamTayang;
    int tiket;
    // char status[20];
    double harga;
    double total;
    char metodePembayaran[10];
    double nominal;
    char catatan[1000];
    TanggalTransc tanggalTransc;
} Tiket;

void PemilihanFilm();

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
                    printf("  >[%s]\t",filmUnik[i]);
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
              //printf(" \n%s[%s]\t", (i == indeksJam && step == 2) ? ">" : " ", jamUnik[i]);

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
                    printf("Jumlah tiket harus antara 1 dan 20. Silakan coba lagi.\n");
                    getch(); // Tunggu input pengguna
                }
                else
                {
                    break; // Keluar dari loop jika pemesanan valid
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

    // Tampilkan hasil pemesanan
    printf("\nPemesanan Berhasil!\n");
    printf("Film: %s\n", filmUnik[indeksJudul]);
    printf("Tanggal: %s\n", tanggalUnik[indeksTanggal]);
    printf("Jam: %s\n", jamUnik[indeksJam]);
    printf("Jumlah Tiket: %d\n", jumlahTiket);
}
