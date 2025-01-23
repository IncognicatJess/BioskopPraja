void EditTeater();
int UpdateKursi(TeaterData *kursiTeater, int kelas);

int UpdateTeater()
{
    EditTeater();
    return 0;
}

void EditTeater()
{
    FILE *file = fopen(TEATERDAT, "rb+");
    if (!file)
    {
        printf("Gagal membuka file database teater.\n");
        return;
    }

    TeaterData teaterArray[MAX_TEATER];
    int totalRecords = 0;

    while (fread(&teaterArray[totalRecords], sizeof(TeaterData), 1, file) == 1)
    {
        totalRecords++;
    }

    char idCari[10];
    ReadTeater();
    printf("Masukkan ID teater yang ingin diedit: ");
    scanf("%9s", idCari);

    int targetIndex = -1;
    for (int i = 0; i < totalRecords; i++)
    {
        if (strcmp(teaterArray[i].ID, idCari) == 0)
        {
            targetIndex = i;
            break;
        }
    }

    if (targetIndex == -1)
    {
        printf("Teater dengan ID %s tidak ditemukan.\n", idCari);
        sleep(2);
        fclose(file);
        return;
    }

    TeaterData *teater = &teaterArray[targetIndex];
    const char *statusOptions[] = {"Open", "Closed", "Maintenance"};
    const char *kategoriOptions[] = {"Reguler", "Premiere", "Mini Studio"};

    int statusIndex = 0, kategoriIndex = 0;
    char noTeaterStr[4] = "", jumlahKursiStr[6] = "", hargaStr[10] = "";
    int step = 0;

    snprintf(noTeaterStr, sizeof(noTeaterStr), "%d", teater->noTeater);
    snprintf(jumlahKursiStr, sizeof(jumlahKursiStr), "%d", teater->jumlahKursi);
    snprintf(hargaStr, sizeof(hargaStr), "%.2f", teater->harga);

    for (int i = 0; i < 3; i++)
    {
        if (strcmp(teater->kategoriTheater, kategoriOptions[i]) == 0)
        {
            kategoriIndex = i;
            break;
        }
    }

    for (int i = 0; i < 3; i++)
    {
        if (strcmp(teater->status, statusOptions[i]) == 0)
        {
            statusIndex = i;
            break;
        }
    }

    while (1)
    {
        system("cls");
        ReadTeater();
        printf("==== Edit Teater ====\n");
        printf("\nID           : %s", teater->ID);
        printf("\nNomor Teater : %s%s", step == 0 ? ">" : "", noTeaterStr);
        printf("\nKategori     :");
        for (int i = 0; i < 3; i++)
        {
            if (i == kategoriIndex && step == 1)
            {
                printf(" >[%s]", kategoriOptions[i]);
            }
            else
            {
                printf("  [%s]", kategoriOptions[i]);
            }
        }
        printf("\nJumlah Kursi : %s%s", step == 2 ? ">" : "", jumlahKursiStr);
        printf("\nHarga        : Rp. %s%s", step == 3 ? ">" : "", hargaStr);
        printf("\nStatus       :");
        for (int i = 0; i < 3; i++)
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
        { // Edit nomor teater
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
        { // Edit kategori
            if (key == 75)
                kategoriIndex = (kategoriIndex - 1 + 3) % 3;
            if (key == 77)
                kategoriIndex = (kategoriIndex + 1) % 3;
            if (key == '\r')
                step++;
        }
        else if (step == 2)
        { // Edit jumlah kursi
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
        { // Edit harga
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
                //Validasi harga minimal Rp. 1000
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
        { // Edit status
            if (key == 75)
                statusIndex = (statusIndex - 1 + 3) % 3;
            if (key == 77)
                statusIndex = (statusIndex + 1) % 3;
            if (key == '\r')
                step++;
        }
        else if (step >= 5)
        {
            teater->noTeater = atoi(noTeaterStr);
            strncpy(teater->kategoriTheater, kategoriOptions[kategoriIndex], sizeof(teater->kategoriTheater) - 1);
            teater->jumlahKursi = atoi(jumlahKursiStr);
            teater->harga = atof(hargaStr);
            strncpy(teater->status, statusOptions[statusIndex], sizeof(teater->status) - 1);

            int konfirmasi = TombolKonfirmasi("Teater", "Perbarui", teater, "TeaterData");
            if (konfirmasi == 1)
            {
                // Tulis ulang semua data ke file
                UpdateKursi(teater, kategoriIndex);
                rewind(file);
                fwrite(teaterArray, sizeof(TeaterData), totalRecords, file);
                // Potong ukuran file (opsional)
                ftruncate(fileno(file), totalRecords * sizeof(TeaterData));
                TampilkanPesan("Data teater berhasil diperbarui.\n", 2);
            }
            else
            {
                TampilkanPesan("Pembaruan teater dibatalkan.\n", 2);
            }
            break;
        }
    }

    fclose(file);
}
