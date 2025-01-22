#define TEMP_SEATDAT "./Database/Teater/TempDataKursi.dat"

void HapusKursi(char idHapus[10]);
int DeleteKursi(char idHapus[10]);

int DeleteKursi(char idHapus[10]) {
    HapusKursi(idHapus);
    return 0;
}
void HapusKursi(char idHapus[10]) {
    FILE *file = fopen(SEATDAT, "rb");
    FILE *tempFile = fopen(TEMP_SEATDAT, "wb");

    if (!file || !tempFile) {
        printf("Gagal membuka file database kursi.\n");
        if (file) fclose(file);
        if (tempFile) fclose(tempFile);
        return;
    }

    KursiData kursi;
    bool ditemukan = false;

    while (fread(&kursi, sizeof(KursiData), 1, file)) {
        if (strcmp(kursi.IDTeater, idHapus) == 0) {
            ditemukan = true;
        } else {
            fwrite(&kursi, sizeof(KursiData), 1, tempFile);
        }
    }

    fclose(file);
    fclose(tempFile);

    if (ditemukan) {
        remove(SEATDAT);
        if (rename(TEMP_SEATDAT, SEATDAT) != 0) {
            printf("Gagal mengganti nama file sementara.\n");
        } else {
            printf("Kursi dari Teater ID %s berhasil dihapus.\n", idHapus);
        }
    } else {
        remove(TEMP_SEATDAT);
        printf("Kursi dengan ID teater %s tidak ditemukan.\n", idHapus);
    }
}
