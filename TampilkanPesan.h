void TampilkanPesan(const char *pesan, int waktu);

void TampilkanPesan(const char *pesan, int waktu)
{
    printf("%s\n", pesan);
    fflush(stdout);
    sleep(waktu);
}