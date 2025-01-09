#define FILENAME "./Database/Akun/DataAkun.dat"


typedef struct
{
    char ID[10];
    char akun[20];
    char username[50];
    char sandi[50];
    char jabatan[20];
    char status[50];
} AkunDataUpdate;

void EditAkun();
bool ValidasiUsernameUpdate(const char *username, FILE *file);
bool ValidasiSandiUpdate(const char *sandi);
int PilihOpsi(const char *judul, const char *opsi[], int jumlah);

int UpdateAkun()
{
    printf("==== Edit Akun ====\n");
    EditAkun();
    return 0;
}



int PilihOpsi(const char *judul, const char *opsi[], int jumlah)
{
    int indeks = 0;
    char key;

    while (1)
    {
        system("cls");
        ReadAkun();
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

void EditAkun()
{
    FILE *file = fopen(FILENAME, "r+b");
    if (!file)
    {
        printf("Gagal membuka file database.\n");
        return;
    }

    char idCari[10];
    printf("Masukkan ID akun yang ingin diedit: ");
    scanf("%s", idCari);

    AkunDataUpdate akun;
    bool ditemukan = false;

    while (fread(&akun, sizeof(AkunDataUpdate), 1, file))
    {
        if (strcmp(akun.ID, idCari) == 0)
        {
            ditemukan = true;
            break;
        }
    }

    if (!ditemukan)
    {
        printf("Akun dengan ID %s tidak ditemukan.\n", idCari);
        fclose(file);
        return;
    }

    char username[50], sandi[50];
    int jabatanIndex = 0, step = 0;
    const char *jabatanOptions[2];

    if (strcmp(akun.akun, "Admin") == 0)
    {
        if (strcmp(akun.ID, "ACT001") == 0)
        {
            printf("Edit untuk Admin utama. Hanya sandi yang dapat diubah.\n");
            while (1)
            {
                printf("\nSandi baru: ");
                scanf("%s", sandi);

                if (ValidasiSandiUpdate(sandi))
                {
                    const char *opsiKonfirmasi[] = {"BATAL", "KONFIRMASI"};
                    int pilihan = PilihOpsi("Konfirmasi perubahan sandi:", opsiKonfirmasi, 2);

                    if (pilihan == 1) // Konfirmasi
                    {
                        strncpy(akun.sandi, sandi, sizeof(akun.sandi) - 1);
                        fseek(file, -sizeof(AkunDataUpdate), SEEK_CUR);
                        fwrite(&akun, sizeof(AkunDataUpdate), 1, file);
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
    else if (strcmp(akun.akun, "User") == 0)
    {
        jabatanOptions[0] = "Kasir Tiket";
        jabatanOptions[1] = "Kasir FNB";
    }

    while (1)
    {
        system("cls");
        ReadAkun();
        printf("==== Edit Akun ====\n");
        printf("\nID: %s\n", akun.ID);
        printf("Akun: %s\n", akun.akun);
        
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

        printf("Username: %s%s\n", step == 1 ? ">" : "", akun.username);
        printf("Sandi: %s%s\n", step == 2 ? ">" : "", akun.sandi);

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
                strncpy(akun.jabatan, jabatanOptions[jabatanIndex], sizeof(akun.jabatan) - 1);
                step++;
            }
        }
        else if (step == 1)
        {
            printf("Masukkan username baru: ");
            scanf("%s", username);
            if (ValidasiUsernameUpdate(username, file))
            {
                strncpy(akun.username, username, sizeof(akun.username) - 1);
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
            scanf("%s", sandi);
            if (ValidasiSandiUpdate(sandi))
            {
                strncpy(akun.sandi, sandi, sizeof(akun.sandi) - 1);
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
                    TampilkanPesan("Pengeditan dibatalkan.\n",2);
                    break;
                }
                else
                {
                    fseek(file, -sizeof(AkunDataUpdate), SEEK_CUR);
                    fwrite(&akun, sizeof(AkunDataUpdate), 1, file);
                    TampilkanPesan("Data berhasil diperbarui.\n",2);
                    break;
                }
            }
        }
    }

    fclose(file);
}

bool ValidasiUsernameUpdate(const char *username, FILE *file)
{
    if (strlen(username) == 0)
        return false;

    rewind(file);
    AkunDataUpdate akun;
    while (fread(&akun, sizeof(AkunDataUpdate), 1, file))
    {
        if (strcmp(akun.username, username) == 0)
        {
            return false;
        }
    }

    for (int i = 0; username[i] != '\0'; i++)
    {
        if (!isalnum(username[i]) && username[i] != '@' && username[i] != '_')
        {
            return false;
        }
    }
    return true;
}

bool ValidasiSandiUpdate(const char *sandi)
{
    if (strlen(sandi) < 8)
    {
        TampilkanPesan("Sandi minimal 8 karakter.\n",2);
        return false;
    }

    bool adaHuruf = false, adaAngka = false, adaSpesial = false;
    for (int i = 0; sandi[i] != '\0'; i++)
    {
        if (isalpha(sandi[i]))
            adaHuruf = true;
        else if (isdigit(sandi[i]))
            adaAngka = true;
        else if (ispunct(sandi[i]))
            adaSpesial = true;
    }

        if (!adaHuruf || !adaAngka || !adaSpesial)
    {
        TampilkanPesan("Sandi harus mengandung huruf, angka, dan karakter khusus.\n",2);
        return false;
    }

    return true;
}

