#ifndef UPDATE_SCHEDULE_H
#define UPDATE_SCHEDULE_H

// Deklarasi fungsi
void PerbaruiJadwal();
int UpdateSchedule();
bool ValidasiTanggalUpdate(ScheduleData *tanggal);
bool ValidasiJamUpdate(ScheduleData *jam);
bool jamUnikUpdate(ScheduleData *jamUnikUpdate, FILE *file);
int DigunakanTeaterUpdate(ScheduleData *teater, FILE *file);

int UpdateSchedule()
{
    printf("\n==== Perbarui Jadwal ====\n");
    PerbaruiJadwal();
    return 0;
}

void PerbaruiJadwal()
{

    FILE *scheduleFile = fopen(SCHEDULEDAT, "rb");
    if (!scheduleFile)
    {
        printf("Gagal membuka file %s. Pastikan file tersebut ada.\n", SCHEDULEDAT);
        return;
    }

    // Variabel Sebagai pembanding dengan data yang ada di file
    ScheduleData jadwalLain;
    // memset(&jadwalLain, 0, sizeof(ScheduleData));

    char judulFilm[50] = "";
    char noTeaterStr[4] = "";
    char tanggalStr[11] = "";
    char jamStr[6] = "";

    // Baca semua record ke dalam memori
    ScheduleData jadwal[MAX_SCHEDULE];
    int jumlahJadwal = 0;

    // Membaca semua data dari file
    while (fread(&jadwal[jumlahJadwal], sizeof(ScheduleData), 1, scheduleFile))
    {
        jumlahJadwal++;
    }
    fclose(scheduleFile);

    ReadSchedule();

    // Cari record yang ingin di-edit
    char idCari[10];
    printf("Masukkan ID jadwal yang ingin diperbarui: ");
    scanf("%9s", idCari);

    // Mencari jadwal berdasarkan ID
    int targetIndex = -1;
    for (int i = 0; i < jumlahJadwal; i++)
    {
        if (strcmp(jadwal[i].ID, idCari) == 0)
        {
            targetIndex = i;
            break;
        }
    }

    // Jika jadwal tidak ditemukan
    if (targetIndex == -1)
    {
        printf("Jadwal dengan ID %s tidak ditemukan.\n", idCari);
        return;
    }

    ScheduleData *jadwalBaru = &jadwal[targetIndex];

    int step = 0;
    int statusIndex = 0;
    const char *statusOptions[] = {"Now Showing", "Coming Soon", "Ended", "Sold Out", "Pre-sale"};

    /* // Menampilkan data saat ini
     printf("\nData saat ini:\n");
     printf("| %-8s | %-20s | %-8d | %02d/%02d/%04d    | %d menit    | %02d:%02d       | %02d:%02d       | Rp %-15.2f |\n",
            dataJadwal->ID, dataJadwal->judulFilm, dataJadwal->Teater,
            dataJadwal->Tanggal.tanggal, dataJadwal->Tanggal.bulan, dataJadwal->Tanggal.tahun,
            dataJadwal->durasi,
            dataJadwal->jamTayang.jam, dataJadwal->jamTayang.menit,
            dataJadwal->Berakhir.jam, dataJadwal->Berakhir.menit,
            dataJadwal->harga);
 */
    // Input data baru

    while (1)
    {
        system("cls");
        ReadFilm();
        ReadTeater();
        ReadSchedule();
        printf("\n\n");
        printf("==== Edit Jadwal Tayang ====\n");

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
        printf("\n");

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

                strncpy(jadwalBaru->judulFilm, judulFilm, sizeof(jadwalBaru->judulFilm) - 1);
                jadwalBaru->judulFilm[sizeof(jadwalBaru->judulFilm) - 1] = '\0';

                bool ditemukan = false;
                MovieData film;
                while (fread(&film, sizeof(MovieData), 1, filmFile))
                {
                    if (strcmp(film.judul, judulFilm) == 0)
                    {
                        ditemukan = true;
                        jadwalBaru->durasi = (int)film.durasi;
                        jadwalBaru->harga = film.harga;
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
                        jadwalBaru->harga += teater.harga;

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
                    jadwalBaru->Teater = atoi(noTeaterStr);
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
                    jadwalBaru->Tanggal.tanggal = atoi(&tanggalStr[0]);
                    jadwalBaru->Tanggal.bulan = atoi(&tanggalStr[3]);
                    jadwalBaru->Tanggal.tahun = atoi(&tanggalStr[6]);

                    if (ValidasiTanggalUpdate(jadwalBaru))
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
        {
            if (isdigit(key) || key == ':')
            {
                size_t len = strlen(jamStr);
                if (len < 5)
                {
                    jamStr[len] = key;
                    jamStr[len + 1] = '\0';
                }
            }
            else if (key == 8 && strlen(jamStr) > 0)
            {
                jamStr[strlen(jamStr) - 1] = '\0';
            }

            else if (key == '\r')
            {
                if (strlen(jamStr) == 5 && jamStr[2] == ':')
                {
                    jadwalBaru->jamTayang.jam = atoi(&jamStr[0]);
                    jadwalBaru->jamTayang.menit = atoi(&jamStr[3]);
                    // jadwalBaru.Teater = atoi(noTeaterStr);
                    jadwalBaru->Berakhir.jam = (jadwalBaru->jamTayang.jam + jadwalBaru->durasi / 60) % 24;
                    jadwalBaru->Berakhir.menit = jadwalBaru->jamTayang.menit + jadwalBaru->durasi % 60;
                    if (jadwalBaru->Berakhir.menit == 60)
                    {
                        jadwalBaru->Berakhir.jam += 1;
                        jadwalBaru->Berakhir.menit -= 60;
                    }
                    if (ValidasiJamUpdate(jadwalBaru))
                    {
                        if (jamUnikUpdate(jadwalBaru, scheduleFile))
                        {
                            if (jadwalBaru->jamTayang.jam >= 20)
                            {
                                jadwalBaru->harga = jadwalBaru->harga + 5000;
                            }
                            step++;
                        }
                        else
                        {
                            int TeaterPemakai = DigunakanTeaterUpdate(jadwalBaru, scheduleFile);

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
                strncpy(jadwalBaru->status, statusOptions[statusIndex], sizeof(jadwalBaru->status) - 1);
                jadwalBaru->status[sizeof(jadwalBaru->status) - 1] = '\0';
                step++;
            }
        }
        else if (step >= 5)
        { // Konfirmasi

            // Konfirmasi perubahan
            int konfirmasi = TombolKonfirmasi("Schedule", "Perbarui", jadwalBaru, "ScheduleData");
            if (konfirmasi == 1)
            { // Jika disetujui
                scheduleFile = fopen(SCHEDULEDAT, "wb");
                if (!scheduleFile)
                {
                    TampilkanPesan("Gagal membuka file untuk menyimpan perubahan.\n", 2);
                    return;
                }
                fwrite(jadwal, sizeof(ScheduleData), jumlahJadwal, scheduleFile);
                fclose(scheduleFile);
                printf("Jadwal dengan ID %s berhasil diperbarui.\n", idCari);
                sleep(1);
                break;
            }
            else
            {
                TampilkanPesan("Perubahan jadwal dibatalkan.\n", 1);
                break;
            }
        }
    }
    fclose(scheduleFile);
}

// Fungsi untuk mencari teater yang sudah menggunakan jadwal
int DigunakanTeaterUpdate(ScheduleData *teater, FILE *file)
{
    file = fopen(SCHEDULEDAT, "rb");
    rewind(file);
    ScheduleData temp;
    while (fread(&temp, sizeof(ScheduleData), 1, file))
    {
        if (temp.Teater == teater->Teater)
        {
            return temp.Teater;
            fclose(file);
            break;
        }
    }
}

// Fungsi untuk mengecek apakah jadwal jam pada teater sudah digunakan
bool jamUnikUpdate(ScheduleData *jamUnikUpdate, FILE *file)
{
    file = fopen(SCHEDULEDAT, "rb");
    rewind(file); // Kembali ke awal file
    ScheduleData temp;

    while (fread(&temp, sizeof(ScheduleData), 1, file))
    {
        // Seleksi teater
        if (temp.Teater == jamUnikUpdate->Teater)
        {
            // Seleksi tanggal
            if (temp.Tanggal.tanggal == jamUnikUpdate->Tanggal.tanggal &&
                temp.Tanggal.bulan == jamUnikUpdate->Tanggal.bulan &&
                temp.Tanggal.tahun == jamUnikUpdate->Tanggal.tahun)
            {

                int start1 = jamUnikUpdate->jamTayang.jam * 60 + jamUnikUpdate->jamTayang.menit;
                int end1 = jamUnikUpdate->Berakhir.jam * 60 + jamUnikUpdate->Berakhir.menit;
                int start2 = temp.jamTayang.jam * 60 + temp.jamTayang.menit;
                int end2 = temp.Berakhir.jam * 60 + temp.Berakhir.menit;

                bool isOverlap = !(end1 <= start2 || start1 >= end2);

                // Memeriksa apakah ada tabrakan waktu
                /* bool isOverlap = (jamUnikUpdate->jamTayang.jam * 60 + jamUnikUpdate->jamTayang.menit <
                                   temp.Berakhir.jam * 60 + temp.Berakhir.menit) &&
                                  (temp.jamTayang.jam * 60 + temp.jamTayang.menit <
                                   jamUnikUpdate->Berakhir.jam * 60 + jamUnikUpdate->Berakhir.menit);
 */
                if (isOverlap)
                {
                    fclose(file); // Tutup file sebelum keluar
                    return false; // Ada tabrakan
                }
            }
        }
    }
    fclose(file); // Pastikan file ditutup
    return true;  // Tidak ada tabrakan
}

bool ValidasiTanggalUpdate(ScheduleData *tanggal)
{
    if (tanggal->Tanggal.tahun < 1900 || tanggal->Tanggal.tahun > 2100)
        return false;
    if (tanggal->Tanggal.bulan < 1 || tanggal->Tanggal.bulan > 12)
        return false;

    int hariDalamBulan[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if ((tanggal->Tanggal.tahun % 4 == 0 && tanggal->Tanggal.tahun % 100 != 0) || (tanggal->Tanggal.tahun % 400 == 0))
    {
        hariDalamBulan[1] = 29; // Tahun kabisat
    }

    if (tanggal->Tanggal.tanggal < 1 || tanggal->Tanggal.tanggal > hariDalamBulan[tanggal->Tanggal.bulan - 1])
        return false;

    return true;
}

bool ValidasiJamUpdate(ScheduleData *jam)
{
    if (jam->jamTayang.jam < 0 || jam->jamTayang.jam > 23)
        return false;
    if (jam->jamTayang.menit < 0 || jam->jamTayang.menit > 59)
        return false;

    return true;
    // return (jam >= 0 && jam <= 23);
}

#endif // UPDATE_SCHEDULE_H
