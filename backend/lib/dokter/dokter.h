#ifndef DOKTER_H
#define DOKTER_H
#include "../random_id/random_id.h"
#define NAMA_MAKS 50
#define DOKTER_MAKS 100

struct Dokter {
    int id; // ID dokter
    char nama[NAMA_MAKS];
    int maks_shift_per_minggu;
    int preferensi[3]; // 0: pagi, 1: siang, 2: malam (0 = diinginkan, 1 = tidak diinginkan)
    int shift_ditugaskan[30][3]; // Melacak shift untuk 30 hari, 3 shift per hari
    int total_shift; // Total shift yang ditugaskan
};

void tampilkan_dokter(struct Dokter *dokter, int jumlah_dokter, char *json_dokter, int kapasitas);
void tambah_dokter_manual(struct Dokter *dokter, int *jumlah_dokter,
                          const char *nama, int maks, int pagi, int siang, int malam);
int baca_dokter_dari_file_csv(struct Dokter *dokter, const char *nama_file);
void print_dokter(struct Dokter *dokter, int jumlah_dokter);
void hapus_dokter(struct Dokter *dokter, int *jumlah_dokter, int id);

#endif

