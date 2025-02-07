void PemilihanKursi(Tiket pesanan)
{
    FILE *file = fopen(SEATDAT, "rb");
    if (!file)
    {
        printf("Gagal membuka file %s. Pastikan file tersebut ada.\n", SEATDAT);
        return;
    }

    KursiData kursi[1000];
    int jumlahKursi = 0;

    // Baca data kursi dari file
    while (fread(&kursi[jumlahKursi], sizeof(KursiData), 1, file))
    {
        jumlahKursi++;
    }
    fclose(file);

    // Filter kursi berdasarkan ID Teater yang dipesan
    KursiData kursiTeater[1000];
    int jumlahKursiTeater = 0;
    for (int i = 0; i < jumlahKursi; i++)
    {
        if (strcmp(kursi[i].IDTeater, pesanan.IDTeater) == 0)
        {
            kursiTeater[jumlahKursiTeater] = kursi[i];
            jumlahKursiTeater++;
        }
    }

    if (jumlahKursiTeater == 0)
    {
        printf("Teater %d belum memiliki kursi, Perbarui data teater!\n", pesanan.Teater);
        sleep(2);
        return;
    }

    // Inisialisasi status kursi
    bool dipilih[1000] = {false}; // Array untuk menandai kursi yang dipilih
    int baris = kursiTeater[0].baris;
    int kolom = kursiTeater[0].kolom;

    // Posisi kursor awal
    int posX = 0, posY = 0;
    int tiketDipilih = 0;

    while (1)
    {
        system("cls");
        printf("==== Pilih Kursi ====\n\n");

        // Tampilkan denah kursi
        for (int i = 0; i < baris; i++)
        {
            for (int j = 0; j < kolom; j++)
            {
                int index = i * kolom + j;
                if (index >= jumlahKursiTeater)
                    break;

                if (i == posY && j == posX)
                {
                    // Highlight kursi yang dipilih
                    if (strcmp(kursiTeater[index].status, "Dipesan") == 0)
                    {
                        printf(" >[ X ] "); // Kursi sudah dipesan
                    }
                    else if (dipilih[index])
                    {
                        printf(" >[ X ] "); // Kursi dipilih oleh pengguna
                    }
                    else
                    {
                        printf(" >[%s] ", kursiTeater[index].ID); // Kursi tersedia
                    }
                }
                else
                {
                    if (strcmp(kursiTeater[index].status, "Dipesan") == 0)
                    {
                        printf(" [ X ] "); // Kursi sudah dipesan
                    }
                    else if (dipilih[index])
                    {
                        printf(" [ X ] "); // Kursi dipilih oleh pengguna
                    }
                    else
                    {
                        printf(" [%s] ", kursiTeater[index].ID); // Kursi tersedia
                    }
                }
            }
            printf("\n");
        }

        printf("\nTekan Enter untuk memilih kursi, Esc untuk keluar.\n");
        printf("Tiket dipilih: %d/%d\n", tiketDipilih, pesanan.tiket);

        // Handle input pengguna
        char key = getch();
        if (key == 27)
        { // Esc untuk keluar
            break;
        }
        else if (key == 13)
        { // Enter untuk memilih kursi
            int index = posY * kolom + posX;
            if (index < jumlahKursiTeater)
            {
                if (strcmp(kursiTeater[index].status, "Dipesan") == 0)
                {
                    TampilkanPesan("Kursi sudah dipesan, silakan pilih kursi lain.", 2);
                }
                else if (dipilih[index])
                {
                    dipilih[index] = false; // Uncheck kursi
                    tiketDipilih--;
                }
                else if (tiketDipilih < pesanan.tiket)
                {
                    dipilih[index] = true; // Check kursi
                    tiketDipilih++;
                }
            }
        }
        else if (key == 75)
        { // Panah kiri
            posX = (posX - 1 + kolom) % kolom;
        }
        else if (key == 77)
        { // Panah kanan
            posX = (posX + 1) % kolom;
        }
        else if (key == 72)
        { // Panah atas
            posY = (posY - 1 + baris) % baris;
        }
        else if (key == 80)
        { // Panah bawah
            posY = (posY + 1) % baris;
        }
    }

    // Simpan kursi yang dipilih ke dalam pesanan
    int kursiTerpilihIndex = 0;
    for (int i = 0; i < jumlahKursiTeater; i++)
    {
        if (dipilih[i])
        {
            strncpy(pesanan.IDkursi[kursiTerpilihIndex], kursiTeater[i].ID, sizeof(pesanan.IDkursi[kursiTerpilihIndex]) - 1);
            pesanan.IDkursi[kursiTerpilihIndex][sizeof(pesanan.IDkursi[kursiTerpilihIndex]) - 1] = '\0';
            kursiTerpilihIndex++;
        }
    }

    // Tampilkan menu opsi setelah pemilihan kursi
    const char *menuPemesananTiket[] = {"KEMBALI", "LANJUT"};
    int pilihan = PilihOpsi("Seat", menuPemesananTiket, &pesanan, kursiTeater, 2);

    switch (pilihan)
    {
    case 0:
        memset(&pesanan, 0, sizeof(Tiket)); // Reset pesanan
        PemilihanFilm();                    // Kembali ke pemilihan film
        break;
    case 1:
        // Hitung total harga
        pesanan.total = pesanan.tiket * pesanan.harga;
        // Lanjut ke transaksi tiket
        InvoiceTiket(&pesanan);
        break;
    }
}