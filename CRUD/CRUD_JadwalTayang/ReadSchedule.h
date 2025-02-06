#ifndef READ_SCHEDULE_H
#define READ_SCHEDULE_H

// Deklarasi fungsi
void TampilkanJadwalTayang();
int BandingkanScheduleID(const void *a, const void *b);
int ReadSchedule();

int ReadSchedule() {
    printf("\n==== Data Jadwal Tayang ====\n");
    TampilkanJadwalTayang();
    return 0;
}

void TampilkanJadwalTayang() {
    FILE *file = fopen(SCHEDULEDAT, "rb");
    if (!file) {
        printf("Gagal membuka file %s. Pastikan file tersebut ada.\n", SCHEDULEDAT);
        return;
    }

    ScheduleData jadwal[MAX_SCHEDULE];
    int jumlahJadwal = 0;

    // Membaca semua data dari file
    while (fread(&jadwal[jumlahJadwal], sizeof(ScheduleData), 1, file)) {
        jumlahJadwal++;
    }
    fclose(file);

    // Mengurutkan data berdasarkan ID
    qsort(jadwal, jumlahJadwal, sizeof(ScheduleData), BandingkanScheduleID);

    // Menampilkan tabel
    printf("| %-8s | %-20s | %-8s | %-12s | %-10s | %-10s|%-10s | %-15s | %-15s |\n", 
           "ID", "Judul Film", "Teater", "Tanggal", "Durasi(menit)","Jam Tayang", "Jam Berakhir", "Harga (Rp)", "Status");
    printf("---------------------------------------------------------------------------------------------------------------------------------------------\n");

    for (int i = 0; i < jumlahJadwal; i++) {
        printf("| %-8s | %-20s | %-8d | %02d/%02d/%04d    | %d           | %02d:%02d       | %02d:%02d       | %-15.2f |  %s |\n",
               jadwal[i].ID, jadwal[i].judulFilm, jadwal[i].Teater, 
               jadwal[i].Tanggal.tanggal, jadwal[i].Tanggal.bulan, jadwal[i].Tanggal.tahun, 
               jadwal[i].durasi,
               jadwal[i].jamTayang.jam, jadwal[i].jamTayang.menit, 
               jadwal[i].Berakhir.jam, jadwal[i].Berakhir.menit, 
               jadwal[i].harga,
               jadwal[i].status);
    }
    printf("\n");
}

// Fungsi pembanding untuk qsort berdasarkan ID
int BandingkanScheduleID(const void *a, const void *b) {
    ScheduleData *scheduleA = (ScheduleData *)a;
    ScheduleData *scheduleB = (ScheduleData *)b;

    // Mengurutkan berdasarkan ID
    return strcmp(scheduleA->ID, scheduleB->ID);
}

#endif // READ_SCHEDULE_H
