#define MAX_TEATER 1000

void BuatTeater();
bool ValidasiNoTeater(const char *noTeater);
bool ValidasiJumlahKursi(const char *jumlahKursi, int kelas);
bool ValidasiHarga(const char *hargaStr);
void TampilkanPesan(const char *pesan, int waktu);
int TombolKonfirmasi(const char *master, const char *opsi, void *data, const char *tipeData);
int CreateKursi(TeaterData kursiTeater, int kelas);

int CreateTeater()
{
    BuatTeater();
    return 0;
}

void BuatTeater()
{
    FILE *file = fopen(TEATERDAT, "a+b");
    if (!file)
    {
        TampilkanPesan("Gagal membuka file database.", 2);
        return;
    }

    TeaterData teaterBaru;
    memset(&teaterBaru, 0, sizeof(TeaterData));

    const char *statusOptions[] = {"Open", "Closed", "Maintenance"};
    const char *kategoriOptions[] = {"Reguler", "Premiere", "Mini Studio"};

    int statusIndex = 0, kategoriIndex = 0;
    char noTeaterStr[4] = "", jumlahKursiStr[6] = "", hargaStr[10] = "";
    int step = 0;

    while (1)
    {
        system("cls");
        ReadTeater();
        printf("==== Tambah Teater ====");

        printf("\nNomor Teater: %s%s", step == 0 ? ">" : "", noTeaterStr);
        printf("\nKategori    :");
        for (int i = 0; i < 3; i++)
        {
            if (i == kategoriIndex && step == 1)
            {
                printf(" >[%s]", kategoriOptions[i]);
            }
            else if (i == kategoriIndex && step > 1)
            {
                printf("  #[%s] ", kategoriOptions[i]);
            }
            else
            {
                printf("  [%s]", kategoriOptions[i]);
            }
        }
        printf("\nJumlah Kursi: %s%s", step == 2 ? ">" : "", jumlahKursiStr);
        printf("\nHarga       : Rp. %s%s", step == 3 ? ">" : "", hargaStr);
        printf("\nStatus      :");
        for (int i = 0; i < 3; i++)
        {
            if (i == statusIndex && step == 4)
            {
                printf(" >[%s]", statusOptions[i]);
            }
            else if (i == statusIndex && step > 4)
            {
                printf("  #[%s] ", statusOptions[i]);
            }
            else
            {
                printf("  [%s]", statusOptions[i]);
            }
        }

        char key = getch();

           // Tombol "Esc" untuk membatalkan
        if (key == 27) // 27 adalah kode ASCII untuk tombol "Esc"
        {
            TampilkanPesan("\nProses pembuatan teater dibatalkan.\n", 2);
            fclose(file);
            return; // Keluar dari fungsi
        }

        if (step == 0)
        { // Input nomor teater
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
            else if (key == '\r' && ValidasiNoTeater(noTeaterStr))
            {
                // Validasi nomor teater tidak boleh sama
                rewind(file);
                TeaterData temp;
                bool noTeaterSama = false;
                while (fread(&temp, sizeof(TeaterData), 1, file))
                {
                    if (temp.noTeater == atoi(noTeaterStr))
                    {
                        noTeaterSama = true;
                        break;
                    }
                }
                if (noTeaterSama)
                {
                    TampilkanPesan("\n\nNomor teater sudah ada. Gunakan nomor lain.\n", 2);
                }
                else
                {
                    step++;
                }
            }
        }
        else if (step == 1)
        { // Pilih kategori
            if (key == 75)
                kategoriIndex = (kategoriIndex - 1 + 3) % 3;
            if (key == 77)
                kategoriIndex = (kategoriIndex + 1) % 3;
            if (key == '\r')
                step++;
        }
        else if (step == 2)
        { // Input jumlah kursi
            if (isdigit(key))
            {
                size_t len = strlen(jumlahKursiStr);
                if (len < 5)
                {
                    jumlahKursiStr[len] = key;
                    jumlahKursiStr[len + 1] = '\0';
                }
            }
            else if (key == 8 && strlen(jumlahKursiStr) > 0)
            {
                jumlahKursiStr[strlen(jumlahKursiStr) - 1] = '\0';
            }
            else if (key == '\r' && ValidasiJumlahKursi(jumlahKursiStr, kategoriIndex))
            {
                step++;
            }else{
                if(kategoriIndex == 0){TampilkanPesan("\nKelas Reguler Mencakup 120, 150 dan 200 kursi! ",2);
                }
                else if(kategoriIndex == 1){TampilkanPesan("\nKelas Premiere Mencakup 20, 30 dan 50 kursi! ",2);
                }
                else if(kategoriIndex == 2){TampilkanPesan("\nKelas Mini Studio Mencakup 80, 90 dan 100 kursi! ",2);
                }
            }
        }
        else if (step == 3)
        { // Input harga
            if (isdigit(key) || key == '.')
            {
                size_t len = strlen(hargaStr);
                if (len < 9)
                {
                    hargaStr[len] = key;
                    hargaStr[len + 1] = '\0';
                }
            }
            else if (key == 8 && strlen(hargaStr) > 0)
            {
                hargaStr[strlen(hargaStr) - 1] = '\0';
            }
            else if (key == '\r' && ValidasiHarga(hargaStr))
            {
                double harga = atof(hargaStr);
                if (harga < 1000)
                {
                    TampilkanPesan("\n\nHarga minimal Rp 1.000.\n", 2);
                }
                else
                {
                    step++;
                }
            }
        }
        else if (step == 4)
        { // Pilih status
            if (key == 75)
                statusIndex = (statusIndex - 1 + 3) % 3;
            if (key == 77)
                statusIndex = (statusIndex + 1) % 3;
            if (key == '\r')
                step++;
        }
        else if (step >= 5)
        { // Konfirmasi
            teaterBaru.noTeater = atoi(noTeaterStr);
            strncpy(teaterBaru.kategoriTheater, kategoriOptions[kategoriIndex], sizeof(teaterBaru.kategoriTheater) - 1);
            teaterBaru.jumlahKursi = atoi(jumlahKursiStr);
            teaterBaru.harga = atof(hargaStr);
            strncpy(teaterBaru.status, statusOptions[statusIndex], sizeof(teaterBaru.status) - 1);

            // Generate ID
            rewind(file);
            bool idTerpakai[MAX_TEATER] = {false};
            TeaterData temp;
            while (fread(&temp, sizeof(TeaterData), 1, file))
            {
                if (strncmp(temp.ID, "TTR", 3) == 0)
                {
                    int idNum = atoi(&temp.ID[3]);
                    if (idNum > 0 && idNum < MAX_TEATER)
                    {
                        idTerpakai[idNum] = true;
                    }
                }
            }

            int idBaru = 1;
            while (idBaru < MAX_TEATER && idTerpakai[idBaru])
            {
                idBaru++;
            }
            snprintf(teaterBaru.ID, sizeof(teaterBaru.ID), "TTR%03d", idBaru);

            int konfirmasi = TombolKonfirmasi("Teater", "Buat", &teaterBaru, "TeaterData");
            if (konfirmasi == 1)
            {
                CreateKursi(teaterBaru, kategoriIndex);
                fwrite(&teaterBaru, sizeof(TeaterData), 1, file);
                TampilkanPesan("Teater berhasil ditambahkan.\n", 2);
            }
            else
            {
                TampilkanPesan("\nPembuatan teater dibatalkan.\n", 2);
            }
            break;
        }
    }

    fclose(file);
}

bool ValidasiNoTeater(const char *noTeater)
{
    return strlen(noTeater) > 0 && strlen(noTeater) <= 3;
}

bool ValidasiJumlahKursi(const char *jumlahKursi, int kelas)
{
    int Kursi = atoi(jumlahKursi);
    switch (kelas)
    {
    // Validasi jumlah kursi Reguler
    case 0:
        if (Kursi == 120 || Kursi == 150 || Kursi == 200)
        {
            return true;
        }
        break;
    // Validasi jumlah kursi Premiere
    case 1:
        if (Kursi == 20 || Kursi == 30 || Kursi == 50)
        {
            return true;
        }
        break;
    // Validasi jumlah kursi Mini Studio
    case 2:
        if (Kursi == 80 || Kursi == 90 || Kursi == 100)
        {
            return true;
        }
        break;
    default:
        return false;
        break;
    }
    return false;
    // return strlen(jumlahKursi) > 0 && atoi(jumlahKursi) > 0;
}

bool ValidasiHarga(const char *hargaStr)
{
    double harga = atof(hargaStr);
    return harga > 0;
}
