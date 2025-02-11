#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_ENTER '\r'

void EditAkun();

int UpdateAkun()
{
    printf("==== Edit Akun ====\n");
    EditAkun();
    return 0;
}

void EditAkun()
{
    FILE *file = fopen(FILENAME, "rb");
    if (!file)
    {
        printf("Gagal membuka file database.\n");
        return;
    }

    // Baca semua record ke memori
    AkunData akunArray[100];
    int totalRecords = 0;

    while (fread(&akunArray[totalRecords], sizeof(AkunData), 1, file) == 1)
    {
        totalRecords++;
    }
    fclose(file);

    // Cari record yang ingin di-edit
    char idCari[10] = {0};
    printf("Masukkan ID akun yang ingin diedit: ");

    int i = 0;
    while (1)
    {
        char ch = getch(); // Ambil input karakter per karakter

        if (ch == 27)
        { // Jika tombol "Esc" ditekan (kode ASCII 27)
            TampilkanPesan("\nProses pembaruan akun dibatalkan.\n", 2);
            fclose(file);
            return; // Keluar dari fungsi
        }
        else if (ch == '\r')
        {                      // Jika tombol "Enter" ditekan
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

    int targetIndex = -1;
    for (int i = 0; i < totalRecords; i++)
    {
        if (strcmp(akunArray[i].ID, idCari) == 0)
        {
            targetIndex = i;
            break;
        }
    }

    // Jika ID tidak ditemukan
    if (targetIndex == -1)
    {
        printf("Akun dengan ID %s tidak ditemukan.\n", idCari);
        return;
    }

    AkunData *akun = &akunArray[targetIndex];
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

                

                if (ValidasiSandi(sandi))
                {
                    int pilihan = TombolKonfirmasi("Akun", "Perbarui", akun, "AkunData");
                    if (pilihan == 1)
                    { // Konfirmasi
                        strncpy(akun->sandi, sandi, sizeof(akun->sandi) - 1);
                        akun->sandi[sizeof(akun->sandi) - 1] = '\0';
                        printf("Sandi berhasil diperbarui.\n");
                        break;
                    }
                    else
                    { // Batal Edit
                        printf("Perubahan dibatalkan.\n");
                        break;
                    }
                }
                else
                {
                    //TampilkanPesan("Sandi tidak valid. Coba lagi.", 2);
                    system("cls");
                    ReadAkun();
                    printf("==== Edit Akun ====\n\n");
                    printf("Edit untuk Admin utama. Hanya sandi yang dapat diubah.\n");
                }
            }
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

    char username[50], sandi[50];
    strncpy(username, akun->username, sizeof(username) - 1);
    strncpy(sandi, akun->sandi, sizeof(sandi) - 1);

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
                printf(" >[%s] ", jabatanOptions[i]); // Sorot pilihan
            }
            else if (i == jabatanIndex)
            {
                printf(" #[%s] ", jabatanOptions[i]); // Sedang dipilih
            }
            else
            {
                printf("  [%s] ", jabatanOptions[i]); // Belum dipilih
            }
        }
        printf("\n");

        printf("Username: %s%s\n", step == 1 ? ">" : "", username);
        printf("Sandi: %s%s\n", step == 2 ? ">" : "", sandi);

        printf("\nGunakan panah kiri/kanan untuk navigasi, Enter untuk konfirmasi.\n");

        char key = getch();

        // Tombol "Esc" untuk membatalkan
        if (key == 27) // 27 adalah kode ASCII untuk tombol "Esc"
        {
            TampilkanPesan("\nProses pembaruan akun dibatalkan.\n", 2);
            fclose(file);
            return; // Keluar dari fungsi
        }

        if (step == 0)
        { // Pilih jabatan
            if (key == KEY_LEFT || key == KEY_UP)
            {
                jabatanIndex = (jabatanIndex - 1 + 2) % 2;
            }
            else if (key == KEY_RIGHT || key == KEY_DOWN)
            {
                jabatanIndex = (jabatanIndex + 1) % 2;
            }
            else if (key == KEY_ENTER)
            {
                strncpy(akun->jabatan, jabatanOptions[jabatanIndex], sizeof(akun->jabatan) - 1);
                akun->jabatan[sizeof(akun->jabatan) - 1] = '\0';
                step++;
            }
        }
        else if (step == 1)
        { // Input username
            if (isalnum(key) || key == '_' || key == '.')
            {
                size_t len = strlen(username);
                if (len < sizeof(username) - 1)
                {
                    username[len] = key;
                    username[len + 1] = '\0';
                }
            }
            else if (key == 8 && strlen(username) > 0)
            { // Backspace
                username[strlen(username) - 1] = '\0';
            }
            else if (key == KEY_ENTER)
            {
                if (ValidasiUsername(username))
                {
                    FILE *file = fopen(FILENAME, "rb");
                    if (!file)
                    {
                        printf("Gagal membuka file database untuk validasi username.\n");
                        return;
                    }
                    if (UsernameUnik(username, file))
                    {
                        step++;
                    }
                    else
                    {
                        TampilkanPesan("Username sudah digunakan.", 2);
                    }
                    fclose(file);
                }
                else
                {
                    TampilkanPesan("Username tidak valid.", 2);
                }
            }
        }
        else if (step == 2)
        { // Input sandi
            if (isalnum(key) || key == '_' || key == '.' || key == '!')
            {
                size_t len = strlen(sandi);
                if (len < sizeof(sandi) - 1)
                {
                    sandi[len] = key;
                    sandi[len + 1] = '\0';
                }
            }
            else if (key == 8 && strlen(sandi) > 0)
            { // Backspace
                sandi[strlen(sandi) - 1] = '\0';
            }
            else if (key == KEY_ENTER)
            {
                if (ValidasiSandi(sandi))
                {
                    step++;
                }
                else
                {
                    TampilkanPesan("Sandi tidak valid.", 2);
                }
            }
        }
        else if (step >= 3)
        { // Konfirmasi
            strncpy(akun->username, username, sizeof(akun->username) - 1);
            strncpy(akun->sandi, sandi, sizeof(akun->sandi) - 1);

            int konfirmasiIndex = TombolKonfirmasi("Akun", "Perbarui", akun, "AkunData");
            if (konfirmasiIndex == 1)
            { // Konfirmasi
                file = fopen(FILENAME, "wb");
                if (!file)
                {
                    printf("Gagal membuka file untuk menulis.\n");
                    return;
                }
                fwrite(akunArray, sizeof(AkunData), totalRecords, file);
                fclose(file);
                TampilkanPesan("\nData berhasil diperbarui.\n", 2);
                break;
            }
            else
            { // Batal
                TampilkanPesan("\nPengeditan dibatalkan.\n", 2);
                break;
            }
        }
    }
}