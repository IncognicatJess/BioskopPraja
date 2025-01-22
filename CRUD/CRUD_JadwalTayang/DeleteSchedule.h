#ifndef DELETE_SCHEDULE_H
#define DELETE_SCHEDULE_H


// Deklarasi fungsi
void HapusSchedule();

int DeleteSchedule()
{
    printf("\n==== Hapus Jadwal ====\n");
    HapusSchedule();
    return 0;
}

void HapusSchedule()
{
    FILE *file = fopen(SCHEDULEDAT, "rb");
    FILE *tempFile = fopen(TEMP_SCHEDULEDAT, "wb");

    if (!file)
    {
        TampilkanPesan("Gagal membuka file database jadwal.\n",2);
        if (file)
            fclose(file);
        if (tempFile)
            fclose(tempFile);
        return;
    }

    ReadSchedule();
    char idHapus[10];
    printf("Masukkan ID jadwal yang ingin dihapus: ");
    scanf("%9s", idHapus);

    ScheduleData jadwal;
    ScheduleData jadwalDihapus;
    bool ditemukan = false;

    // Membaca data dari file utama dan menyaring data yang akan dihapus
    while (fread(&jadwal, sizeof(ScheduleData), 1, file))
    {
        if (strcmp(jadwal.ID, idHapus) == 0)
        {
            ditemukan = true;
            jadwalDihapus = jadwal;
        }
        else
        {
            fwrite(&jadwal, sizeof(ScheduleData), 1, tempFile);
        }
    }

    fclose(file);
    fclose(tempFile);

    if (ditemukan)
    {

        int konfirmasi = TombolKonfirmasi("Schedule", "Hapus", &jadwalDihapus, "ScheduleData");
        if (konfirmasi == 1)
        {
            remove(SCHEDULEDAT);
            rename(TEMP_SCHEDULEDAT, SCHEDULEDAT);
            printf("Jadwal dengan ID %s berhasil dihapus.\n", idHapus);
            sleep(2);
        }
        else
        {
            printf("Penghapusan dibatalkan.\n");
            remove(TEMP_SCHEDULEDAT);
            sleep(2);
        }
    }
    else
    {
        remove(TEMP_SCHEDULEDAT);
        printf("Jadwal dengan ID %s tidak ditemukan.\n", idHapus);
        sleep(2);
    }
}

#endif // DELETE_SCHEDULE_H
