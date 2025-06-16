#include "../lib/mongoose/mongoose.h"
#include "../lib/dokter/dokter.h"
#include "routes.h"
#include <stdio.h>
#include <string.h>

void handle_tambah_dokter(struct mg_connection *c, struct mg_http_message *hm) {
    struct Dokter dokter[DOKTER_MAKS];
    int jumlah_dokter = baca_dokter_dari_file(dokter, "data/dokter.csv");

    // Ambil data dari JSON body secara langsung
    char *nama = mg_json_get_str(hm->body, "$.nama");
    double maks_d, pagi_d, siang_d, malam_d;

    int valid = mg_json_get_num(hm->body, "$.maks", &maks_d) &&
                mg_json_get_num(hm->body, "$.pagi", &pagi_d) &&
                mg_json_get_num(hm->body, "$.siang", &siang_d) &&
                mg_json_get_num(hm->body, "$.malam", &malam_d);

    // Validasi input
    if (!nama || !valid) {
        mg_http_reply(c, 400,
            "Content-Type: application/json\r\nAccess-Control-Allow-Origin: *\r\n",
            "{ \"status\": \"error\", \"message\": \"Field tidak lengkap atau invalid\" }");
        if (nama) free(nama);
        return;
    }

    int maks = (int) maks_d;
    int pagi = (int) pagi_d;
    int siang = (int) siang_d;
    int malam = (int) malam_d;

    // Tambahkan dokter
    tambah_dokter_manual(dokter, &jumlah_dokter, nama, maks, pagi, siang, malam);
    free(nama);  // malloc dari mg_json_get_str

    // Simpan ulang ke CSV
    FILE *file = fopen("data/dokter.csv", "w");
    if (!file) {
        mg_http_reply(c, 500,
            "Content-Type: application/json\r\nAccess-Control-Allow-Origin: *\r\n",
            "{ \"status\": \"error\", \"message\": \"Gagal membuka file\" }");
        return;
    }

    // Header + tulis ulang isi dokter
    fprintf(file, "id,Nama,MaksShiftPerMinggu,PagiPref,SiangPref,MalamPref\n");
    for (int i = 0; i < jumlah_dokter; i++) {
        fprintf(file, "%d,%s,%d,%d,%d,%d\n",
            dokter[i].id,
            dokter[i].nama,
            dokter[i].maks_shift_per_minggu,
            dokter[i].preferensi[0],
            dokter[i].preferensi[1],
            dokter[i].preferensi[2]);
    }
    fclose(file);

    // Respon sukses
    mg_http_reply(c, 200,
        "Content-Type: application/json\r\nAccess-Control-Allow-Origin: *\r\n",
        "{ \"status\": \"success\", \"message\": \"Dokter berhasil ditambahkan\" }");
}

void handle_tampilkan_dokter(struct mg_connection *c, struct mg_http_message *hm) {
    struct Dokter dokter[DOKTER_MAKS];
    int jumlah = baca_dokter_dari_file(dokter, "data/dokter.csv");

    char json[4096];
    tampilkan_dokter(dokter, jumlah, json, sizeof(json));

    mg_http_reply(c, 200,
        "Content-Type: application/json\r\nAccess-Control-Allow-Origin: *\r\n",
        "%s", json);
}
