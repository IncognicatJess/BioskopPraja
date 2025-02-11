#define MAX_ACCOUNTS 1000

void BuatAkun();
bool ValidasiUsername(const char *username);
bool ValidasiSandi(const char *sandi);
bool UsernameUnik(const char *username, FILE *file);
void TambahAdminDefault(FILE *file);

int CreateAkun()
{

    BuatAkun();
    return 0;
}

void TambahAdminDefault(FILE *file)
{
    AkunData adminDefault;
    memset(&adminDefault, 0, sizeof(AkunData));

    strncpy(adminDefault.ID, "ACT001", sizeof(adminDefault.ID) - 1);
    strncpy(adminDefault.akun, "Admin", sizeof(adminDefault.akun) - 1);
    strncpy(adminDefault.username, "Admin", sizeof(adminDefault.username) - 1);
    strncpy(adminDefault.sandi, "Admin#123", sizeof(adminDefault.sandi) - 1);
    strncpy(adminDefault.jabatan, "Manajer", sizeof(adminDefault.jabatan) - 1);
    strncpy(adminDefault.status, "Mandatory", sizeof(adminDefault.status) - 1);

    fwrite(&adminDefault, sizeof(AkunData), 1, file);
    printf("Admin default (ACT001) telah ditambahkan.\n");
}

void BuatAkun()
{

    FILE *file = fopen(FILENAME, "a+b");
    if (!file)
    {
        printf("Gagal membuka file database.\n");
        return;
    }

    fseek(file, 0, SEEK_END);
    if (ftell(file) == 0)
    {
        TambahAdminDefault(file);
    }
    rewind(file);

    AkunData akunBaru;
    memset(&akunBaru, 0, sizeof(AkunData));

    const char *pilihanAkun[] = {"Admin", "User"};
    const char *jabatanAdmin[] = {"Manajer", "Manajer IT"};
    const char *jabatanUser[] = {"Kasir Tiket", "Kasir FNB"};

    int pilihanAkunIndex = 0, jabatanIndex = 0;
    char username[50] = "", sandi[50] = "";
    int step = 0;

    while (1)
    {

        system("cls");
        ReadAkun();
        printf("==== Tambah Akun ====\n");
        printf("Akun    :");

        for (int i = 0; i < 2; i++)
        {
            if (i == pilihanAkunIndex && step == 0)
            {
                printf(" >[%s]", pilihanAkun[i]);
            }
            else if (i == pilihanAkunIndex)
            {
                printf("  #[%s] ", pilihanAkun[i]);
            }
            else
            {
                printf("  [%s]", pilihanAkun[i]);
            }
        }
        printf("\n");

        printf("Jabatan :");
        const char **jabatanOptions = strcmp(pilihanAkun[pilihanAkunIndex], "Admin") == 0 ? jabatanAdmin : jabatanUser;
        int jabatanOptionsCount = 2;
        for (int i = 0; i < jabatanOptionsCount; i++)
        {
            if (i == jabatanIndex && step == 1)
            {
                printf(" >[%s]", jabatanOptions[i]);
            }
            else if (i == jabatanIndex && step > 1)
            {
                printf("  #[%s] ", jabatanOptions[i]);
            }
            else
            {
                printf("  [%s]", jabatanOptions[i]);
            }
        }
        printf("\n\n");

        printf("Username: %s%s\n", step == 2 ? ">" : "", username);
        printf("Sandi   : %s%s\n\n", step == 3 ? ">" : "", sandi);

        char key = getch();

        // Tombol "Esc" untuk membatalkan
        if (key == 27) // 27 adalah kode ASCII untuk tombol "Esc"
        {
            TampilkanPesan("\nProses pembuatan akun dibatalkan.\n", 2);
            fclose(file);
            return; // Keluar dari fungsi
        }

        if (step == 0)
        {
            if (key == 75)
                pilihanAkunIndex = (pilihanAkunIndex - 1 + 2) % 2;
            if (key == 77)
                pilihanAkunIndex = (pilihanAkunIndex + 1) % 2;
            if (key == '\r')
                step++;
        }
        else if (step == 1)
        {
            if (key == 75)
                jabatanIndex = (jabatanIndex - 1 + jabatanOptionsCount) % jabatanOptionsCount;
            if (key == 77)
                jabatanIndex = (jabatanIndex + 1) % jabatanOptionsCount;
            if (key == '\r')
                step++;
        }
        else if (step == 2)
        {
            if (isalnum(key) || key == '@' || key == '#')
            {
                size_t len = strlen(username);
                if (len < sizeof(username) - 1)
                {
                    username[len] = key;
                    username[len + 1] = '\0';
                }
            }
            else if (key == 8 && strlen(username) > 0)
            {
                username[strlen(username) - 1] = '\0';
            }
            else if (key == '\r' && ValidasiUsername(username) && UsernameUnik(username, file))
            {
                step++;
            }
        }
        else if (step == 3)
        {

            if (isalnum(key) || ispunct(key))
            {
                size_t len = strlen(sandi);
                if (len < sizeof(sandi) - 1)
                {
                    sandi[len] = key;
                    sandi[len + 1] = '\0';
                }
            }
            else if (key == 8 && strlen(sandi) > 0)
            {
                sandi[strlen(sandi) - 1] = '\0';
            }
            else if (key == '\r' && ValidasiSandi(sandi))
            {
                step++;
            }
        }
        else if (step >= 4)
        {
            strncpy(akunBaru.akun, pilihanAkun[pilihanAkunIndex], sizeof(akunBaru.akun) - 1);
            strncpy(akunBaru.jabatan, jabatanOptions[jabatanIndex], sizeof(akunBaru.jabatan) - 1);
            strncpy(akunBaru.username, username, sizeof(akunBaru.username) - 1);
            strncpy(akunBaru.sandi, sandi, sizeof(akunBaru.sandi) - 1);

            int konfirmasiIndex = TombolKonfirmasi("Akun", "Buat", &akunBaru, "AkunData");

            if (konfirmasiIndex == 0)
            {
                memset(&akunBaru, 0, sizeof(AkunData));
                TampilkanPesan("Pembuatan akun dibatalkan.\n",2);
                break;
            }
            else
            {

                rewind(file);
                bool idTerpakai[MAX_ACCOUNTS] = {false};
                AkunData temp;
                while (fread(&temp, sizeof(AkunData), 1, file))
                {
                    if (strncmp(temp.ID, "ACT", 3) == 0)
                    {
                        int idNum = atoi(&temp.ID[3]);
                        if (idNum > 0 && idNum < MAX_ACCOUNTS)
                        {
                            idTerpakai[idNum] = true;
                        }
                    }
                }
                int idBaru = 2;
                while (idBaru < MAX_ACCOUNTS && idTerpakai[idBaru])
                {
                    idBaru++;
                }
                snprintf(akunBaru.ID, sizeof(akunBaru.ID), "ACT%03d", idBaru);

                
                fwrite(&akunBaru, sizeof(AkunData), 1, file);
                
               
                break;
            }
        }
    }

    fclose(file);
}

bool ValidasiUsername(const char *username)
{
    if (strlen(username) == 0)
        return false;

    for (int i = 0; username[i] != '\0'; i++)
    {
        if (!isalnum(username[i]) && username[i] != '@' && username[i] != '_')
        {
            return false;
        }
    }
    return true;
}

bool ValidasiSandi(const char *sandi)
{
    if (strlen(sandi) < 8)
    {
        TampilkanPesan("Sandi minimal 8 karakter.\n", 2);
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
        TampilkanPesan("Sandi harus mengandung huruf, angka, dan karakter khusus.\n", 2);
        return false;
    }

    return true;
}

bool UsernameUnik(const char *username, FILE *file)
{
    rewind(file);
    AkunData temp;
    while (fread(&temp, sizeof(AkunData), 1, file))
    {
        if (strcmp(temp.username, username) == 0)
        {
            TampilkanPesan("Username telah digunakan, coba yang lain.\n", 2);
            return false;
        }
    }
    return true;
}
