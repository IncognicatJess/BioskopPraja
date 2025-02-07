int TombolKonfirmasi(const char *master, const char *opsi, void *data, const char *tipeData)
{
    const char *pilihan[] = {"BATAL", "KONFIRMASI"};
    int indeks = 0;
    char key;

    if (!data || !master || !opsi || !tipeData)
    {
        TampilkanPesan("Parameter tidak valid.\n", 2);
        return -1; // Nilai indikasi error
    }

    while (1)
    {
        system("cls");

        // Penanganan untuk master "Film"
        if (strcmp(master, "Film") == 0 && strcmp(tipeData, "MovieData") == 0)
        {
            MovieData *film = (MovieData *)data;
            if (strcmp(opsi, "Buat") == 0)
            {
                printf("Apakah anda yakin ingin menambahkan film berikut?\n");

                printf("Judul       : %s\n", film->judul);
                printf("Genre       : %s\n", film->genre);
                printf("Tahun Rilis : %d\n", film->tahunRelease);
                printf("Durasi      : %.0f menit\n", film->durasi);
                printf("Studio      : %s\n", film->studioFilm);
                printf("Bentuk      : %s\n", film->bentuk);
                printf("Harga       : Rp. %.2f\n", film->harga);
                printf("\n");
            }
            else if (strcmp(opsi, "Perbarui") == 0)
            {
                printf("Apakah anda yakin ingin memperbarui film berikut?\n");
                printf("ID          : %s\n", film->ID);
                printf("Judul       : %s\n", film->judul);
                printf("Genre       : %s\n", film->genre);
                printf("Tahun Rilis : %d\n", film->tahunRelease);
                printf("Durasi      : %.0f menit\n", film->durasi);
                printf("Studio      : %s\n", film->studioFilm);
                printf("Bentuk      : %s\n", film->bentuk);
                printf("Harga       : Rp. %.2f\n", film->harga);
                printf("\n");
            }
            else if (strcmp(opsi, "Hapus") == 0)
            {
                printf("Apakah anda yakin ingin menghapus film berikut?\n");
                printf("ID          : %s\n", film->ID);
                printf("Judul       : %s\n", film->judul);
                printf("Genre       : %s\n", film->genre);
                printf("Tahun Rilis : %d\n", film->tahunRelease);
                printf("Durasi      : %.0f menit\n", film->durasi);
                printf("Studio      : %s\n", film->studioFilm);
                printf("Bentuk      : %s\n", film->bentuk);
                printf("Harga       : Rp. %.2f\n", film->harga);
                printf("\n");
            }
            else
            {
                TampilkanPesan("Maaf fitur belum tersedia\n", 2);
            }
        } // Penanganan untuk master "Fnb"
        else if (strcmp(master, "Fnb") == 0 && strcmp(tipeData, "FnbData") == 0)
        {
            FnbData *menu = (FnbData *)data;
            if (strcmp(opsi, "Buat") == 0)
            {
                printf("Apakah anda yakin ingin menambahkan menu berikut?\n");
                printf("Nama        : %s\n", menu->namaMakanan);
                printf("Kategori    : %s\n", menu->kategori);
                printf("Stok        : %d\n", menu->stok);
                printf("Harga       : Rp. %.2f\n", menu->harga);
                printf("\n");
            }
            else if (strcmp(opsi, "Perbarui") == 0)
            {
                printf("Apakah anda yakin ingin memperbarui menu berikut?\n");
                printf("ID          : %s\n", menu->ID);
                printf("Nama        : %s\n", menu->namaMakanan);
                printf("Kategori    : %s\n", menu->kategori);
                printf("Stok        : %d\n", menu->stok);
                printf("Harga       : Rp. %.2f\n", menu->harga);
                printf("\n");
            }
            else if (strcmp(opsi, "Hapus") == 0)
            {
                printf("Apakah anda yakin ingin menghapus menu berikut?\n");
                printf("ID          : %s\n", menu->ID);
                printf("Nama        : %s\n", menu->namaMakanan);
                printf("Kategori    : %s\n", menu->kategori);
                printf("Stok        : %d\n", menu->stok);
                printf("Harga       : Rp. %.2f\n", menu->harga);
                printf("\n");
            }
            else
            {
                TampilkanPesan("Maaf fitur belum tersedia\n", 2);
            }
        }
        // Penanganan untuk master "Sandi"
        else if (strcmp(master, "Sandi") == 0 && strcmp(tipeData, "AkunData") == 0)
        {
            AkunData *akun = (AkunData *)data;
            if (strcmp(opsi, "Perbarui") == 0)
            {
                printf("Apakah anda yakin ingin memperbarui sandi untuk akun berikut?\n");
                printf("ID       : %s\n", akun->ID);
                printf("Username : %s\n", akun->username);
                printf("Sandi Baru: %s\n", akun->sandi); // Tampilkan sandi baru
                printf("\n\n");
            }
            else
            {
                TampilkanPesan("Maaf fitur belum tersedia\n", 2);
            }
        }
        // Penanganan untuk master "Akun"
        else if (strcmp(master, "Akun") == 0 && strcmp(tipeData, "AkunData") == 0)
        {
            AkunData *akun = (AkunData *)data;
            if (strcmp(opsi, "Buat") == 0)
            {
                ReadAkun();
                printf("Apakah anda yakin ingin membuat akun %s dengan username %s dan sandi %s?\n", akun->akun, akun->username, akun->sandi);
            }
            else if (strcmp(opsi, "Perbarui") == 0)
            {
                ReadAkun();
                printf("Apakah anda yakin ingin memperbarui akun %s %s?\n", akun->akun, akun->ID);
            }
            else if (strcmp(opsi, "Hapus") == 0)
            {
                ReadAkun();
                printf("Apakah anda yakin ingin menghapus akun %s %s dengan username %s?\n", akun->akun, akun->ID, akun->username);
            }
            else
            {
                TampilkanPesan("Maaf fitur belum tersedia\n", 2);
            }
        }
        // Penanganan untuk master "Profil"
        else if (strcmp(master, "Profil") == 0 && strcmp(tipeData, "ProfilData") == 0)
        {
            ProfilData *profil = (ProfilData *)data;
            if (strcmp(opsi, "Edit") == 0)
            {
                printf("Apakah anda yakin ingin memperbarui profil berikut?\n");
                printf("Nama   : %s\n", profil->nama);
                printf("TTL    : %s, %02d/%02d/%04d\n", profil->TTL.tempat, profil->TTL.tanggal, profil->TTL.bulan, profil->TTL.tahun);
                printf("No HP  : %s\n", profil->noHP);
                printf("\n\n");
            }
            else
            {
                TampilkanPesan("Maaf fitur belum tersedia\n", 2);
            }
        }
        // Penanganan untuk master "Teater"
        else if (strcmp(master, "Teater") == 0 && strcmp(tipeData, "TeaterData") == 0)
        {
            TeaterData *teater = (TeaterData *)data;
            if (strcmp(opsi, "Buat") == 0)
            {
                ReadTeater();
                printf("Apakah anda yakin ingin menambahkan teater berikut?\n");
                printf("ID          : %s\n", teater->ID);
                printf("No Teater   : %d\n", teater->noTeater);
                printf("Kategori    : %s\n", teater->kategoriTheater);
                printf("Jumlah Kursi: %d\n", teater->jumlahKursi);
                printf("Status      : %s\n", teater->status);
                printf("Harga       : Rp. %0.2lf\n", teater->harga);
                printf("\n\n");
            }
            else if (strcmp(opsi, "Hapus") == 0)
            {
                ReadTeater();
                printf("Apakah anda yakin ingin menghapus teater berikut?\n");
                printf("ID          : %s\n", teater->ID);
                printf("No Teater   : %d\n", teater->noTeater);
                printf("Kategori    : %s\n", teater->kategoriTheater);
                printf("Jumlah Kursi: %d\n", teater->jumlahKursi);
                printf("Status      : %s\n", teater->status);
                printf("Harga       : Rp. %0.2lf\n", teater->harga);
                printf("\n\n");
            }
            else if (strcmp(opsi, "Perbarui") == 0)
            {
                ReadTeater();
                printf("Apakah anda yakin ingin mengedit teater berikut?\n");
                printf("ID          : %s\n", teater->ID);
                printf("No Teater   : %d\n", teater->noTeater);
                printf("Kategori    : %s\n", teater->kategoriTheater);
                printf("Jumlah Kursi: %d\n", teater->jumlahKursi);
                printf("Status      : %s\n", teater->status);
                printf("Harga       : Rp. %0.2lf\n", teater->harga);
                printf("\n\n");
            }
            else
            {
                TampilkanPesan("Maaf fitur belum tersedia\n", 2);
            }
        }
        // Penanganan untuk master "Schedule"
        else if (strcmp(master, "Schedule") == 0 && strcmp(tipeData, "ScheduleData") == 0)
        {
            ScheduleData *jadwal = (ScheduleData *)data;

            if (strcmp(opsi, "Buat") == 0)
            {
                ReadSchedule();
                printf("\n");
                printf("Apakah anda yakin ingin menambahkan jadwal tayang berikut?\n");
                printf("ID          : %s\n", jadwal->ID);
                printf("ID Film     : %s\n", jadwal->IDFilm);
                printf("Judul Film  : %s\n", jadwal->judulFilm);
                printf("Teater      : %d\n", jadwal->Teater);
                printf("Durasi      : %d menit\n", jadwal->durasi);
                printf("Tanggal     : %02d/%02d/%04d\n", jadwal->Tanggal.tanggal, jadwal->Tanggal.bulan, jadwal->Tanggal.tahun);
                printf("Jam         : %02d:%02d - %02d:%02d\n",
                       jadwal->jamTayang.jam, jadwal->jamTayang.menit, jadwal->Berakhir.jam, jadwal->Berakhir.menit);
                printf("Status      : %s\n", jadwal->status);
                printf("Harga       : Rp. %.2lf\n", jadwal->harga);
                printf("\n");
            }
            else if (strcmp(opsi, "Hapus") == 0)
            {
                ReadSchedule();
                printf("\n");
                printf("Apakah anda yakin ingin menghapus jadwal tayang berikut?\n");
                printf("ID          : %s\n", jadwal->ID);
                printf("ID Film     : %s\n", jadwal->IDFilm);
                printf("Judul Film  : %s\n", jadwal->judulFilm);
                printf("Teater      : %d\n", jadwal->Teater);
                printf("Tanggal     : %02d/%02d/%04d\n", jadwal->Tanggal.tanggal, jadwal->Tanggal.bulan, jadwal->Tanggal.tahun);
                printf("Jam         : %02d:%02d - %02d:%02d\n",
                       jadwal->jamTayang.jam, jadwal->jamTayang.menit, jadwal->Berakhir.jam, jadwal->Berakhir.menit);
                printf("Status      : %s\n", jadwal->status);
                printf("Harga       : Rp. %.2lf\n", jadwal->harga);
                printf("\n");
            }
            else if (strcmp(opsi, "Perbarui") == 0)
            {
                ReadSchedule();
                printf("\n");
                printf("Apakah anda yakin ingin memperbarui jadwal tayang berikut?\n");
                printf("ID          : %s\n", jadwal->ID);
                printf("ID Film     : %s\n", jadwal->IDFilm);
                printf("Judul Film  : %s\n", jadwal->judulFilm);
                printf("Teater      : %d\n", jadwal->Teater);
                printf("Tanggal     : %02d/%02d/%04d\n", jadwal->Tanggal.tanggal, jadwal->Tanggal.bulan, jadwal->Tanggal.tahun);
                printf("Jam         : %02d:%02d - %02d:%02d\n",
                       jadwal->jamTayang.jam, jadwal->jamTayang.menit, jadwal->Berakhir.jam, jadwal->Berakhir.menit);
                printf("Status      : %s\n", jadwal->status);
                printf("Harga       : Rp. %.2lf\n", jadwal->harga);
                printf("\n");
            }
            else
            {
                TampilkanPesan("Maaf fitur belum tersedia\n", 2);
            }
        }
        else if (strcmp(master, "Transaksi") == 0 && strcmp(tipeData, "Tiket") == 0)
        {
            Tiket *pesanan = (Tiket *)data;

            if (strcmp(opsi, "Konfirmasi") == 0)
            {
                printf("==== Transaksi Tiket ====\n\n");

                // Tampilkan invoice
                printf("Film        : %s\n", pesanan->judulFilm);
                printf("Tanggal     : %02d/%02d/%04d\n", pesanan->Tanggal.tanggal, pesanan->Tanggal.bulan, pesanan->Tanggal.tahun);
                printf("Jam         : %02d:%02d\n", pesanan->jamTayang.jam, pesanan->jamTayang.menit);
                printf("ID Teater   : %s\n", pesanan->IDTeater);
                printf("No Teater   : %d\n", pesanan->Teater);
                printf("Jumlah Tiket: %d\n", pesanan->tiket);
                printf("Harga Tiket : Rp. %.2lf\n", pesanan->harga);
                printf("Total Harga : Rp. %.2lf\n", pesanan->total);
                printf("\n");
            }else
            {
                TampilkanPesan("Maaf fitur belum tersedia\n", 2);
            }
        }
        else
        {
            TampilkanPesan("Tipe data atau fitur belum tersedia.\n", 2);
        }

        // Tampilkan pilihan "BATAL" dan "KONFIRMASI"
        for (int i = 0; i < 2; i++)
        {
            if (i == indeks)
            {
                printf(" >[%s]", pilihan[i]);
            }
            else
            {
                printf("  [%s]", pilihan[i]);
            }
        }
        printf("\n");

        // Input navigasi
        key = getch();
        if (key == 75 || key == 72) // Panah kiri atau atas
            indeks = (indeks - 1 + 2) % 2;
        else if (key == 77 || key == 80) // Panah kanan atau bawah
            indeks = (indeks + 1) % 2;
        else if (key == '\r') // Enter
            return indeks;
    }
}