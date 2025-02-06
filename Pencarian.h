int Pencarian(const char *master, void *data, void *data2);
int ReadAkun();
int ReadFilm();
int ReadFnb();
void ReadProfile(AkunData *akun, ProfilData *profil);
int ReadTeater();
int ReadSchedule();
void PencarianFilm();
void PencarianTanggal();

int main()
{

    return 0;
}

int Pencarian(const char *master, void *data, void *data2)
{
    int indeks = 0;
    char key;

    while (1)
    {
        system("cls");

        if (strcmp(master, "Schedule") == 0)
        {

            FILE *file = fopen(SCHEDULEDAT, "rb");
            FILE *tempFile = fopen(TEMP_SCHEDULEDAT, "wb");

            if (!file)
            {
                TampilkanPesan("Gagal membuka file database jadwal.\n", 2);
                if (file)
                    fclose(file);
                if (tempFile)
                    fclose(tempFile);
                return;
            }

            ReadSchedule();
            // char idCari[10] = {0};

            while (1)
            {
                system("cls");

                const char *menuPencarian[] = {"CARI FILM", "CARI TANGGAL", "KEMBALI"};

                const char *Master = "Film";
                int pilihan = PilihOpsi(Master, menuTeater, NULL, NULL, 5);

                switch (pilihan)
                {
                case 0:
                    system("cls");
                    PencarianFilm();
                    // Fungsi pencarian berdasarkan judul film
                    break;
                case 1:
                    system("cls");
                    PencarianTanggal();
                    // Fungsi pencarian berdasarkan tanggal jadwal tayang
                    break;
                case 2:
                    break;
                }
                if (pilihan == 2)
                {
                    break;
                }
            }

            printf("Masukkan ID jadwal yang ingin dihapus: ");

            // Input ID F&B  dan deteksi "Esc"
            int i = 0;
            while (1)
            {
                char ch = getch(); // Ambil input karakter per karakter

                if (ch == 27)
                { // Jika tombol "Esc" ditekan (kode ASCII 27)
                    TampilkanPesan("\nProses penghapusan jadwal tayang dibatalkan.\n", 2);
                    fclose(file);
                    remove(TEMP_SCHEDULEDAT);
                    return; // Keluar dari fungsi
                }
                else if (ch == '\r')
                {                     // Jika tombol "Enter" ditekan
                    idCari[i] = '\0'; // Akhiri string
                    break;
                }
                else if (ch == 8 && i > 0)
                { // Jika tombol "Backspace" ditekan
                    i--;
                    printf("\b \b"); // Hapus karakter terakhir dari layar
                }
                else if (i < 9 && (isalnum(ch) || ch == ' '))
                { // Hanya terima alfanumerik atau spasi
                    idCari[i++] = ch;
                    putchar(ch); // Tampilkan karakter ke layar
                }
            }

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
