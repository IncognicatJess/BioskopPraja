#ifndef CREATE_SCHEDULE_H
#define CREATE_SCHEDULE_H

// #define FILEFILM "./Database/Film/DataFilm.dat"
// #define TEATERDAT "./Database/Teater/DataTeater.dat"
// #define SCHEDULEDAT "./Database/JadwalTayang/DataJadwalTayang.dat"
#define MAX_SCHEDULE 1000

// Function declarations
void BuatJadwalTayang();
bool ValidasiTanggal(ScheduleData tanggal);
bool ValidasiJam(ScheduleData jam);
// int HitungJamAkhir(int jamAwal, int durasi);
// double HitungHargaTayang(double hargaFilm, double hargaTeater, int jam);
int DigunakanTeater(ScheduleData teater, FILE *file);
bool jamUnik(ScheduleData jamUnik, FILE *file);

void BuatJadwalTayang()
{
    FILE *scheduleFile = fopen(SCHEDULEDAT, "a+b");
    if (!scheduleFile)
    {
        TampilkanPesan("Gagal membuka file jadwal tayang.\n", 2);
        return;
    }

    ScheduleData jadwalBaru;
    memset(&jadwalBaru, 0, sizeof(ScheduleData));

    char judulFilm[50] = "";
    char noTeaterStr[4] = "";
    char tanggalStr[11] = "";
    char jamStr[6] = "";

    int jamAwal = -1; // Jam diinisialisasi dengan nilai tidak valid
    int statusIndex = 0;
    const char *statusOptions[] = {"Now Showing", "Coming Soon", "Ended", "Sold Out", "Pre-sale"};

    int step = 0;

    while (1)
    {
        system("cls");
        ReadFilm();
        ReadTeater();
        ReadSchedule();
        printf("\n\n");
        printf("==== Tambah Jadwal Tayang ====\n");

        printf("\nJudul Film : %s%s", step == 0 ? ">" : "", judulFilm);
        printf("\nNo Teater  : %s%s", step == 1 ? ">" : "", noTeaterStr);
        printf("\nTanggal    : %s%s", step == 2 ? ">" : "", tanggalStr);
        printf("\nJam        : %s%s", step == 3 ? ">" : "", jamStr);
        printf("\nStatus     :");
        for (int i = 0; i < 5; i++)
        {
            if (i == statusIndex && step == 4)
            {
                printf(" >[%s]", statusOptions[i]);
            }
            else
            {
                printf("  [%s]", statusOptions[i]);
            }
        }

        char key = getch();

        if (step == 0)
        { // Input judul film
            if (isalnum(key) || key == ' ')
            {
                size_t len = strlen(judulFilm);
                if (len < 49)
                {
                    judulFilm[len] = key;
                    judulFilm[len + 1] = '\0';
                }
            }
            else if (key == 8 && strlen(judulFilm) > 0)
            {
                judulFilm[strlen(judulFilm) - 1] = '\0';
            }
            else if (key == '\r')
            {
                FILE *filmFile = fopen(FILEFILM, "rb");
                if (!filmFile)
                {
                    printf("Gagal membuka file film.\n");
                    return;
                }

                strncpy(jadwalBaru.judulFilm, judulFilm, sizeof(jadwalBaru.judulFilm) - 1);
                jadwalBaru.judulFilm[sizeof(jadwalBaru.judulFilm) - 1] = '\0';

                bool ditemukan = false;
                MovieData film;
                while (fread(&film, sizeof(MovieData), 1, filmFile))
                {
                    if (strcmp(film.judul, judulFilm) == 0)
                    {
                        ditemukan = true;
                        jadwalBaru.durasi = (int)film.durasi;
                        jadwalBaru.harga = film.harga;
                        break;
                    }
                }
                fclose(filmFile);

                if (!ditemukan)
                {

                    TampilkanPesan("\n\nJudul film tidak ditemukan.\n", 2);
                }
                else
                {
                    step++;
                }
            }
        }
        else if (step == 1)
        { // Input no teater
            if (isdigit(key))
            {
                size_t len = strlen(noTeaterStr);
                if (len < 3)
                {
                    noTeaterStr[len] = key;
                    noTeaterStr[len + 1] = '\0';
                }
            }
            else if (key == 8 && strlen(noTeaterStr) > 0)
            {
                noTeaterStr[strlen(noTeaterStr) - 1] = '\0';
            }
            else if (key == '\r')
            {
                FILE *teaterFile = fopen(TEATERDAT, "rb");
                if (!teaterFile)
                {
                    printf("Gagal membuka file teater.\n");
                    return;
                }

                bool ditemukan = false;
                TeaterData teater;
                while (fread(&teater, sizeof(TeaterData), 1, teaterFile))
                {
                    if (teater.noTeater == atoi(noTeaterStr))
                    {
                        ditemukan = true;
                        jadwalBaru.harga += teater.harga;

                        break;
                    }
                }
                fclose(teaterFile);

                if (!ditemukan)
                {

                    TampilkanPesan("\n\nNo teater tidak ditemukan.\n", 2);
                }
                else
                {
                    jadwalBaru.Teater = atoi(noTeaterStr);
                    step++;
                }
            }
        }
        else if (step == 2)
        { // Input tanggal
            // (Validasi tanggal diimplementasikan di sini)else if (step == 2) { // Input tanggal

            if (isdigit(key) || key == '/')
            {
                size_t len = strlen(tanggalStr);
                if (len < 10)
                {
                    tanggalStr[len] = key;
                    tanggalStr[len + 1] = '\0';
                }
            }
            else if (key == 8 && strlen(tanggalStr) > 0)
            {
                tanggalStr[strlen(tanggalStr) - 1] = '\0';
            }
            else if (key == '\r')
            {
                if (strlen(tanggalStr) == 10 && tanggalStr[2] == '/' && tanggalStr[5] == '/')
                {
                    jadwalBaru.Tanggal.tanggal = atoi(&tanggalStr[0]);
                    jadwalBaru.Tanggal.bulan = atoi(&tanggalStr[3]);
                    jadwalBaru.Tanggal.tahun = atoi(&tanggalStr[6]);

                    if (ValidasiTanggal(jadwalBaru))
                    {
                        step++;
                    }
                    else
                    {
                        TampilkanPesan("\n\nTanggal tidak valid.\n", 2);
                    }
                }
                else
                {
                    TampilkanPesan("\n\nFormat tanggal salah. Gunakan format DD-MM-YYYY.\n", 2);
                }
            }
        }
        else if (step == 3)
        { // Input jam
          // int keyJam = getch();

            if (isdigit(key) || key == ':')
            {
                size_t len = strlen(jamStr);
                if (len < 5)
                {
                    jamStr[len] = key;
                    jamStr[len + 1] = '\0';
                }
                /*                 jamAwal = atoi(&jamStr[0]);

                                int inputJam = jamAwal >= 0 ? jamAwal * 10 + (key - '0') : (key - '0');
                                if (inputJam >= 0 && inputJam <= 23)
                                {
                                    jamAwal = inputJam;
                                }*/
            }
            else if (key == 8 && strlen(jamStr) > 0)
            {
                jamStr[strlen(jamStr) - 1] = '\0';
            }
            /*
            else if (key == 8 && jamAwal >= 0)
            {
                jamAwal /= 10;
            }*/
            else if (key == '\r')
            {
                if (strlen(jamStr) == 5 && jamStr[2] == ':')
                {
                    jadwalBaru.jamTayang.jam = atoi(&jamStr[0]);
                    jadwalBaru.jamTayang.menit = atoi(&jamStr[3]);
                    // jadwalBaru.Teater = atoi(noTeaterStr);
                    jadwalBaru.Berakhir.jam = (jadwalBaru.jamTayang.jam + jadwalBaru.durasi / 60) % 24;
                    jadwalBaru.Berakhir.menit = jadwalBaru.jamTayang.menit + jadwalBaru.durasi % 60;
                    if(jadwalBaru.Berakhir.menit == 60){
                        jadwalBaru.Berakhir.jam += 1;
                        jadwalBaru.Berakhir.menit -= 60;
                    }
                    if (ValidasiJam(jadwalBaru))
                    {
                        if (jamUnik(jadwalBaru, scheduleFile))
                        {
                            if (jadwalBaru.jamTayang.jam >= 20)
                            {
                                jadwalBaru.harga = jadwalBaru.harga + 5000;
                            }
                            step++;
                        }
                        else
                        {
                            int TeaterPemakai = DigunakanTeater(jadwalBaru, scheduleFile);

                            printf("\nJadwal sudah digunakan di Teater %d!\n", TeaterPemakai);
                            sleep(2);
                        }
                    }
                    else
                    {
                        TampilkanPesan("\nJam atau menit tidak valid.\n", 2);
                    }
                }
                else
                {
                    TampilkanPesan("\n\nFormat jam salah. Gunakan format 00:00 24 jam.\n", 2);
                }

                // int hargaMalam = jamAwal;
            }
        }
        else if (step == 4)
        { // Pilih status
            if (key == 75 || key == 72)
                statusIndex = (statusIndex - 1 + 5) % 5;
            else if (key == 77 || key == 80)
                statusIndex = (statusIndex + 1) % 5;
            else if (key == '\r')
            {
                strncpy(jadwalBaru.status, statusOptions[statusIndex], sizeof(jadwalBaru.status) - 1);
                jadwalBaru.status[sizeof(jadwalBaru.status) - 1] = '\0';
                step++;
            }
        }
        else if (step >= 5)
        { // Konfirmasi

            rewind(scheduleFile);
            bool idTerpakai[MAX_SCHEDULE] = {false};
            ScheduleData temp;
            while (fread(&temp, sizeof(ScheduleData), 1, scheduleFile))
            {
                if (strncmp(temp.ID, "SHW", 3) == 0)
                {
                    int idNum = atoi(&temp.ID[3]);
                    if (idNum > 0 && idNum < MAX_SCHEDULE)
                    {
                        idTerpakai[idNum] = true;
                    }
                }
            }

            int idBaru = 1;
            while (idBaru < MAX_SCHEDULE && idTerpakai[idBaru])
            {
                idBaru++;
            }
            snprintf(jadwalBaru.ID, sizeof(jadwalBaru.ID), "SHW%03d", idBaru);

            int konfirmasi = TombolKonfirmasi("Schedule", "Buat", &jadwalBaru, "ScheduleData");
            if (konfirmasi == 1)
            {
                fwrite(&jadwalBaru, sizeof(ScheduleData), 1, scheduleFile);
                TampilkanPesan("Jadwal tayang berhasil ditambahkan.\n", 2);
            }
            else
            {
                TampilkanPesan("Pembuatan jadwal tayang dibatalkan.\n", 2);
            }
            break;
        }
    }

    fclose(scheduleFile);
}

// Fungsi untuk mencari teater yang sudah menggunakan jadwal
int DigunakanTeater(ScheduleData teater, FILE *file)
{
    rewind(file);
    ScheduleData temp;
    while (fread(&temp, sizeof(ScheduleData), 1, file))
    {
        if (temp.Teater == teater.Teater)
        {
            return temp.Teater;
            break;
        }
    }
}

// Fungsi untuk mengecek apakah jadwal jam pada teater sudah digunakan
bool jamUnik(ScheduleData jamUnik, FILE *file)
{
    rewind(file);
    ScheduleData temp;
    while (fread(&temp, sizeof(ScheduleData), 1, file))
    {
        // seleksi teater
        if (temp.Teater == jamUnik.Teater)
        {
            // seleksi tanggal
            if (temp.Tanggal.tanggal == jamUnik.Tanggal.tanggal &&
                temp.Tanggal.bulan == jamUnik.Tanggal.bulan &&
                temp.Tanggal.tahun == jamUnik.Tanggal.tahun)
            {
                // Memeriksa apakah ada tabrakan waktu
                bool isOverlap = (jamUnik.jamTayang.jam < temp.Berakhir.jam ||
                                  (jamUnik.jamTayang.jam == temp.Berakhir.jam && jamUnik.jamTayang.menit < temp.Berakhir.menit)) &&
                                 (temp.jamTayang.jam < jamUnik.Berakhir.jam ||
                                  (temp.jamTayang.jam == jamUnik.Berakhir.jam && temp.jamTayang.menit < jamUnik.Berakhir.menit));

                // Kondisi untuk menghindari tabrakan pada waktu yang sama
                if ((jamUnik.jamTayang.jam == temp.Berakhir.jam && jamUnik.jamTayang.menit == 0) || 
                    (jamUnik.Berakhir.jam == temp.jamTayang.jam && jamUnik.Berakhir.menit == 0))
                {
                    return false; // Tabrakan jika jam tayang baru dimulai tepat saat berakhirnya jadwal yang sudah ada
                }

                if (isOverlap)
                {
                    return false; // Ada tabrakan
                }
            }
        }
    }
    return true;
}

bool ValidasiTanggal(ScheduleData tanggal)
{
    if (tanggal.Tanggal.tahun < 1900 || tanggal.Tanggal.tahun > 2100)
        return false;
    if (tanggal.Tanggal.bulan < 1 || tanggal.Tanggal.bulan > 12)
        return false;

    int hariDalamBulan[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if ((tanggal.Tanggal.tahun % 4 == 0 && tanggal.Tanggal.tahun % 100 != 0) || (tanggal.Tanggal.tahun % 400 == 0))
    {
        hariDalamBulan[1] = 29; // Tahun kabisat
    }

    if (tanggal.Tanggal.tanggal < 1 || tanggal.Tanggal.tanggal > hariDalamBulan[tanggal.Tanggal.bulan - 1])
        return false;

    return true;
}

bool ValidasiJam(ScheduleData jam)
{
    if (jam.jamTayang.jam < 0 || jam.jamTayang.jam > 23)
        return false;
    if (jam.jamTayang.menit < 0 || jam.jamTayang.menit > 59)
        return false;

    return true;
    // return (jam >= 0 && jam <= 23);
}

/*
int HitungJamAkhir(int jamAwal, int durasi)
{
    if (!ValidasiJam(jamAwal))
    {
        return -1; // Invalid jamAwal
    }

    int jamAkhir = (jamAwal + durasi / 60) % 24;
    int menitAkhir = jadwal->durasi % 60;
    return jamAkhir;
}
*/
/*
double HitungHargaTayang(double hargaFilm, double hargaTeater, int jam)
{
    if (!ValidasiJam(jam))
    {
        return -1.0; // Invalid jam
    }

    double hargaTayang = hargaFilm + hargaTeater;

    // Tambahan biaya untuk jam malam (prime time)
    if (jam >= 18 && jam <= 23)
    {
        hargaTayang *= 1.2; // Tambahan 20% untuk jam malam
    }

    return hargaTayang;
}
*/
#endif
