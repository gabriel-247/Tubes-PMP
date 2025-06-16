#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "dokter.h"

// Tambah dokter tanpa interaksi terminal
void tambah_dokter_manual(struct Dokter *dokter, int *jumlah_dokter,
                          const char *nama, int maks, int pagi, int siang, int malam) {
    if (*jumlah_dokter >= DOKTER_MAKS) return;

    struct Dokter *d = &dokter[*jumlah_dokter];
    generate_random_numeric_id(&d->id, 1000, 9999);
    strncpy(d->nama, nama, NAMA_MAKS - 1);
    d->nama[NAMA_MAKS - 1] = '\0';
    d->maks_shift_per_minggu = maks;
    d->preferensi[0] = pagi;
    d->preferensi[1] = siang;
    d->preferensi[2] = malam;
    d->total_shift = 0;
    for (int i = 0; i < 30; i++)
        for (int j = 0; j < 3; j++)
            d->shift_ditugaskan[i][j] = 0;

    (*jumlah_dokter)++;
}

// Menghapus dokter berdasarkan ID
void hapus_dokter(struct Dokter *dokter, int *jumlah_dokter, int id) {
    int indeks = -1;
    for (int i = 0; i < *jumlah_dokter; i++) {
        if (dokter[i].id == id) {
            indeks = i;
            break;
        }
    }

    if (indeks == -1) {
        printf("Dokter dengan ID %d tidak ditemukan.\n", id);
        return;
    }

    for (int i = indeks; i < *jumlah_dokter - 1; i++) {
        dokter[i] = dokter[i + 1];
    }

    (*jumlah_dokter)--;
    printf("Dokter dengan ID %d berhasil dihapus.\n", id);
}

// Mengisi buffer json_dokter dengan isi JSON
void tampilkan_dokter(struct Dokter *dokter, int jumlah_dokter, char *json_dokter, int kapasitas) {
    strcpy(json_dokter, "[");
    for (int i = 0; i < jumlah_dokter; i++) {
        char item[512];
        snprintf(item, sizeof(item),
                 "%s{ \"id\": \"%d\", \"nama\": \"%s\", \"maks\": \"%d\", \"pagi\": \"%d\", \"siang\": \"%d\", \"malam\": \"%d\" }",
                 (i > 0) ? "," : "",
                 dokter[i].id,
                 dokter[i].nama,
                 dokter[i].maks_shift_per_minggu,
                 dokter[i].preferensi[0],
                 dokter[i].preferensi[1],
                 dokter[i].preferensi[2]);

        strncat(json_dokter, item, kapasitas - strlen(json_dokter) - 1);
    }
    strncat(json_dokter, "]", kapasitas - strlen(json_dokter) - 1);
}

// Membaca data dokter dari file CSV dengan kolom id
int baca_dokter_dari_file_csv(struct Dokter *dokter, const char *nama_file) {
    FILE *file = fopen(nama_file, "r");
    if (!file) {
        printf("Tidak dapat membuka file %s\n", nama_file);
        return 0;
    }
    int jumlah_dokter = 0;
    char baris[256];
    // Lewati header
    if (!fgets(baris, sizeof(baris), file)) {
        printf("Gagal membaca header file %s\n", nama_file);
        fclose(file);
        return 0;
    }
    // Membaca setiap baris data
    while (fgets(baris, sizeof(baris), file) && jumlah_dokter < DOKTER_MAKS) {
        // Menghapus karakter baris baru atau spasi di akhir
        baris[strcspn(baris, "\r\n")] = 0;
        // Parsing baris dengan sscanf
        int id, maks_shift, pagi, siang, malam;
        char nama[NAMA_MAKS];
        int parsed = sscanf(baris, "%d,%[^,],%d,%d,%d,%d",
                            &id, nama, &maks_shift, &pagi, &siang, &malam);
        if (parsed != 6) {
            printf("Gagal parsing baris: %s\n", baris);
            continue;
        }
        // Menyimpan data ke struktur
        dokter[jumlah_dokter].id = id;
        strncpy(dokter[jumlah_dokter].nama, nama, NAMA_MAKS - 1);
        dokter[jumlah_dokter].nama[NAMA_MAKS - 1] = '\0'; // Pastikan string null-terminated
        dokter[jumlah_dokter].maks_shift_per_minggu = maks_shift;
        dokter[jumlah_dokter].preferensi[0] = pagi;
        dokter[jumlah_dokter].preferensi[1] = siang;
        dokter[jumlah_dokter].preferensi[2] = malam;
        for (int i = 0; i < 30; i++)
            for (int j = 0; j < 3; j++)
                dokter[jumlah_dokter].shift_ditugaskan[i][j] = 0;
        dokter[jumlah_dokter].total_shift = 0;
        // Debugging: Cetak data yang dibaca
        printf("Dokter dibaca: ID=%d, Nama=%s, MaksShift=%d, Pagi=%d, Siang=%d, Malam=%d\n",
               dokter[jumlah_dokter].id, dokter[jumlah_dokter].nama,
               dokter[jumlah_dokter].maks_shift_per_minggu,
               dokter[jumlah_dokter].preferensi[0],
               dokter[jumlah_dokter].preferensi[1],
               dokter[jumlah_dokter].preferensi[2]);
        jumlah_dokter++;
    }
    fclose(file);
    if (jumlah_dokter == 0) {
        printf("Tidak ada dokter yang berhasil dibaca dari file %s\n", nama_file);
    }
    return jumlah_dokter;
}

void print_dokter(struct Dokter *dokter, int jumlah_dokter) {
    printf("\nDaftar Dokter:\n");
    for (int i = 0; i < jumlah_dokter; i++) {
        printf("ID: %d, Nama: %s, Maks Shift/Minggu: %d, Preferensi (Pagi, Siang, Malam): %d, %d, %d\n",
               dokter[i].id, dokter[i].nama, dokter[i].maks_shift_per_minggu,
               dokter[i].preferensi[0], dokter[i].preferensi[1], dokter[i].preferensi[2]);
    }
}