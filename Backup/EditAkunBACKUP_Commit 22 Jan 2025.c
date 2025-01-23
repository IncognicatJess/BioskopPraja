
void EditAkun()
{
    FILE *file = fopen(FILENAME, "rb");
    if (!file)
    {
        printf("Gagal membuka file database.\n");
        return;
    }

    // Baca semua record ke memori
    AkunDataUpdate akunArray[100]; 
    int totalRecords = 0;

    //Perulangan menghitung berapa banyak record/struct
    while (fread(&akunArray[totalRecords], sizeof(AkunDataUpdate), 1, file) == 1)
    {
        totalRecords++;
    }
    fclose(file);

    // Search for the record to edit
    char idCari[10];
    printf("Masukkan ID akun yang ingin diedit: ");
    scanf("%9s", idCari);

    int targetIndex = -1;
    for (int i = 0; i < totalRecords; i++)
    {
        if (strcmp(akunArray[i].ID, idCari) == 0)
        {
            targetIndex = i;
            break;
        }
    }

    //Jika ID tidak ditemukan
    if (targetIndex == -1)
    {
        printf("Akun dengan ID %s tidak ditemukan.\n", idCari);
        return;
    }

    AkunDataUpdate *akun = &akunArray[targetIndex];
    int step = 0;
    int jabatanIndex = 0;
    const char *jabatanOptions[2];

    if (strcmp(akun->akun, "Admin") == 0)
    {
        if (strcmp(akun->ID, "ACT001") == 0)
        {
            printf("Edit untuk Admin utama. Hanya sandi yang dapat diubah.\n");
            while (1)
            {
                printf("\nSandi baru: ");
                char sandi[50];
                scanf("%49s", sandi);

                if (ValidasiSandiUpdate(sandi))
                {
                    const char *opsiKonfirmasi[] = {"BATAL", "KONFIRMASI"};
                    int pilihan = PilihOpsi("Akun", opsiKonfirmasi, 2);

                    if (pilihan == 1) // Konfirmasi
                    {
                        strncpy(akun->sandi, sandi, sizeof(akun->sandi) - 1);
                        akun->sandi[sizeof(akun->sandi) - 1] = '\0';
                        printf("Sandi berhasil diperbarui.\n");
                        break;
                    }
                    else // Batal
                    {
                        printf("Perubahan dibatalkan.\n");
                        break;
                    }
                }
                else
                {
                    TampilkanPesan("Sandi tidak valid. Coba lagi.", 2);
                    system("cls");
                    ReadAkun();
                    printf("==== Edit Akun ====\n\n");
                    printf("Edit untuk Admin utama. Hanya sandi yang dapat diubah.\n");
                }
            }
            fclose(file);
            return;
        }
        else
        {
            jabatanOptions[0] = "Manajer";
            jabatanOptions[1] = "Manajer IT";
        }
    }
    else if (strcmp(akun->akun, "User") == 0)
    {
        jabatanOptions[0] = "Kasir Tiket";
        jabatanOptions[1] = "Kasir FNB";
    }

    while (1)
    {
        system("cls");
        ReadAkun(); // Refresh screen with account data
        printf("==== Edit Akun ====\n");
        printf("\nID: %s\n", akun->ID);
        printf("Akun: %s\n", akun->akun);

        // Display jabatan options
        printf("Jabatan: ");
        for (int i = 0; i < 2; i++)
        {
            if (i == jabatanIndex && step == 0)
            {
                printf(" >[%s]", jabatanOptions[i]);
            }
            else
            {
                printf("  [%s]", jabatanOptions[i]);
            }
        }
        printf("\n");

        printf("Username: %s%s\n", step == 1 ? ">" : "", akun->username);
        printf("Sandi: %s%s\n", step == 2 ? ">" : "", akun->sandi);

        const char *pilihanKonfirmasi[] = {"BATAL", "KONFIRMASI"};
        printf("Konfirmasi: ");
        for (int i = 0; i < 2; i++)
        {
            if (i == step - 3)
            {
                printf(" >[%s]", pilihanKonfirmasi[i]);
            }
            else
            {
                printf("  [%s]", pilihanKonfirmasi[i]);
            }
        }
        printf("\n");

        char key = getch();
        if (step == 0)
        {
            if (key == 75)
                jabatanIndex = (jabatanIndex - 1 + 2) % 2;
            if (key == 77)
                jabatanIndex = (jabatanIndex + 1) % 2;
            if (key == '\r')
            {
                strncpy(akun->jabatan, jabatanOptions[jabatanIndex], sizeof(akun->jabatan) - 1);
                akun->jabatan[sizeof(akun->jabatan) - 1] = '\0';
                step++;
            }
        }
        else if (step == 1)
        {
            printf("Masukkan username baru: ");
            char username[50];
            scanf("%49s", username);
            if (ValidasiUsernameUpdate(username, file)) // Assume NULL for simplicity
            {
                strncpy(akun->username, username, sizeof(akun->username) - 1);
                akun->username[sizeof(akun->username) - 1] = '\0';
                step++;
            }
            else
            {
                TampilkanPesan("Username sudah digunakan atau tidak valid.", 2);
            }
        }
        else if (step == 2)
        {
            printf("Masukkan sandi baru: ");
            char sandi[50];
            scanf("%49s", sandi);
            if (ValidasiSandiUpdate(sandi))
            {
                strncpy(akun->sandi, sandi, sizeof(akun->sandi) - 1);
                akun->sandi[sizeof(akun->sandi) - 1] = '\0';
                step++;
            }
            else
            {
                TampilkanPesan("Sandi tidak valid. Coba lagi.", 2);
            }
        }
        else if (step >= 3)
        {
            int konfirmasiIndex = step - 3;
            if (key == 75 || key == 77)
            {
                konfirmasiIndex = 1 - konfirmasiIndex;
                step = 3 + konfirmasiIndex;
            }
            else if (key == '\r')
            {
                if (konfirmasiIndex == 0)
                {
                    TampilkanPesan("Pengeditan dibatalkan.\n", 2);
                    break;
                }
                else
                {
                    file = fopen(FILENAME, "wb");
                    if (!file)
                    {
                        printf("Gagal membuka file untuk menulis.\n");
                        return;
                    }
                    fwrite(akunArray, sizeof(AkunDataUpdate), totalRecords, file);
                    fclose(file);
                    TampilkanPesan("Data berhasil diperbarui.\n", 2);
                    break;
                }
            }
        }
    }
}