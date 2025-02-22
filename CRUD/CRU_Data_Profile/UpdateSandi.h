void GantiSandi(AkunData *akun, char *Master);

void GantiSandi(AkunData *akun, char *Master)
{
    // Buka file database akun
    FILE *file = fopen(FILENAME, "rb+");
    if (!file)
    {
        perror("Gagal membuka file database");
        return;
    }

    // Jika Master adalah "Profil", maka ganti sandi untuk akun yang sedang login
    if (strcmp(Master, "Profil") == 0)
    {
        while (1)
        {
            system("cls");
            printf(" === DATA AKUN === \n");
            printf("ID       : %s\n", akun->ID);
            printf("Username : %s\n", akun->username);
            printf("\n");

            printf("Sandi lama         : %s\n", akun->sandi);
            printf("Masukkan sandi baru: ");
            char sandi[50] = {0};
            

            
              // Input sandi baru  dan deteksi "Esc"
                int i = 0;
                while (1)
                {
                    char ch = getch(); // Ambil input karakter per karakter

                    if (ch == 27)
                    { // Jika tombol "Esc" ditekan (kode ASCII 27)
                        TampilkanPesan("\nProses pembaruan sandi dibatalkan.\n", 2);
                        fclose(file);
                        return; // Keluar dari fungsi
                    }
                    else if (ch == '\r')
                    {                      // Jika tombol "Enter" ditekan
                        sandi[i] = '\0'; // Akhiri string
                        break;
                    }
                    else if (ch == 8 && i > 0)
                    { // Jika tombol "Backspace" ditekan
                        i--;
                        printf("\b \b"); // Hapus karakter terakhir dari layar
                    }
                    else if (i > 0 || (isalnum(ch) || isalpha(ch) || isdigit(ch) || ispunct(ch)))
                    {
                        sandi[i++] = ch;
                        putchar(ch); // Tampilkan karakter ke layar
                    }
                }


            // Validasi sandi baru
            if (ValidasiSandi(sandi))
            {

                // Konfirmasi perubahan sandi
                int konfirmasi = TombolKonfirmasi("Sandi", "Perbarui", akun, "AkunData");

                if (konfirmasi == 1)
                {
                    // Salin sandi baru ke struktur akun
                    strncpy(akun->sandi, sandi, sizeof(akun->sandi) - 1);
                    akun->sandi[sizeof(akun->sandi) - 1] = '\0';

                    // Cari posisi akun dalam file
                    fseek(file, 0, SEEK_SET);
                    AkunData temp;
                    long posisi = -1;

                    while (fread(&temp, sizeof(AkunData), 1, file))
                    {
                        if (strcmp(temp.ID, akun->ID) == 0)
                        {
                            posisi = ftell(file) - sizeof(AkunData);
                            break;
                        }
                    }

                    // Jika akun ditemukan, timpa sandi lama dengan sandi baru
                    if (posisi != -1)
                    {
                        fseek(file, posisi, SEEK_SET);
                        fwrite(akun, sizeof(AkunData), 1, file);
                        TampilkanPesan("\nSandi berhasil diperbarui!\n", 1);
                        break;
                    }
                    else
                    {
                        TampilkanPesan("\nAkun tidak ditemukan dalam database.\n", 2);
                        break;
                    }
                }
                else
                {
                    TampilkanPesan("\nPerubahan sandi dibatalkan.\n", 2);
                    break;
                }
            }
        }
    }
    else if (strcmp(Master, "Akun") == 0)
    {
        // Jika Master adalah "Akun", maka ganti sandi untuk akun tertentu berdasarkan ID

        char idCari[10] = {0};
        ReadAkun();
        printf("Masukkan ID Akun: ");

        // Input ID akun  dan deteksi "Esc"
        int i = 0;
        while (1)
        {
            char ch = getch(); // Ambil input karakter per karakter

            if (ch == 27)
            { // Jika tombol "Esc" ditekan (kode ASCII 27)
                TampilkanPesan("\nProses pembaruan sandi dibatalkan.\n", 2);
                fclose(file);
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

        AkunData temp;
        bool idDitemukan = false;
        long posisi = -1;

        // Cari akun berdasarkan ID
        while (fread(&temp, sizeof(AkunData), 1, file))
        {
            if (strcmp(temp.ID, idCari) == 0)
            {
                idDitemukan = true;
                posisi = ftell(file) - sizeof(AkunData);
                break;
            }
        }

        if (idDitemukan)
        {
            while (1)
            {
                system("cls");
                ReadAkun();

                printf("ID Akun : %s\n", temp.ID);
                printf("Sandi Lama : %s\n", temp.sandi);
                printf("Masukkan sandi baru: ");
                char sandi[50] = {0};

                // Input sandi baru  dan deteksi "Esc"
                int i = 0;
                while (1)
                {
                    char ch = getch(); // Ambil input karakter per karakter

                    if (ch == 27)
                    { // Jika tombol "Esc" ditekan (kode ASCII 27)
                        TampilkanPesan("\nProses pembaruan sandi dibatalkan.\n", 2);
                        fclose(file);
                        return; // Keluar dari fungsi
                    }
                    else if (ch == '\r')
                    {                      // Jika tombol "Enter" ditekan
                        sandi[i] = '\0'; // Akhiri string
                        break;
                    }
                    else if (ch == 8 && i > 0)
                    { // Jika tombol "Backspace" ditekan
                        i--;
                        printf("\b \b"); // Hapus karakter terakhir dari layar
                    }
                    else if (i > 0 || (isalnum(ch) || isalpha(ch) || isdigit(ch) || ispunct(ch)))
                    {
                        sandi[i++] = ch;
                        putchar(ch); // Tampilkan karakter ke layar
                    }
                }

                // Validasi sandi baru
                if (ValidasiSandi(sandi))
                {

                    // Konfirmasi perubahan sandi
                    int konfirmasi = TombolKonfirmasi("Sandi", "Perbarui", &temp, "AkunData");

                    if (konfirmasi == 1)
                    {
                        strncpy(temp.sandi, sandi, sizeof(temp.sandi) - 1);
                        temp.sandi[sizeof(temp.sandi) - 1] = '\0';

                        // Timpa sandi lama dengan sandi baru
                        fseek(file, posisi, SEEK_SET);
                        fwrite(&temp, sizeof(AkunData), 1, file);
                        TampilkanPesan("\nSandi berhasil diperbarui!\n", 1);
                        break;
                    }
                    else
                    {
                        TampilkanPesan("\nPerubahan sandi dibatalkan.\n", 2);
                        break;
                    }
                }
            }
        }
        else
        {
            TampilkanPesan("\nID akun tidak ditemukan!\n", 2);
        }
    }

    fclose(file);
}