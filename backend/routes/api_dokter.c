#include "../lib/mongoose/mongoose.h"
#include "../lib/dokter/dokter.h"
#include "../lib/jadwal/jadwal.h"
#include "../lib/io/io.h"
#include "routes.h"
#include <stdio.h>
#include <string.h>

void handle_tambah_dokter(struct mg_connection *c, struct mg_http_message *hm, struct Dokter *dokter, int *jumlah_dokter) {

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
    tambah_dokter_manual(dokter, jumlah_dokter, nama, maks, pagi, siang, malam);
    printf("Dokter baru dengan data Nama=%s, MaksShift=%d, Pagi=%d, Siang=%d, Malam=%d berhasil ditambahkan\n", 
           nama, maks, pagi, siang, malam);
    print_dokter(dokter, *jumlah_dokter);
    free(nama);  // malloc dari mg_json_get_str

    // Respon sukses
    mg_http_reply(c, 200,
        "Content-Type: application/json\r\nAccess-Control-Allow-Origin: *\r\n",
        "{ \"status\": \"success\", \"message\": \"Dokter berhasil ditambahkan\" }");
}

void handle_hapus_dokter(struct mg_connection *c, struct mg_http_message *hm, struct Dokter *dokter, int *jumlah_dokter) {

    // Ambil data dari JSON body secara langsung
    double id;
    int valid = mg_json_get_num(hm->body, "$.id", &id);

    // Validasi input
    if (!valid) {
        mg_http_reply(c, 400,
            "Content-Type: application/json\r\nAccess-Control-Allow-Origin: *\r\n",
            "{ \"status\": \"error\", \"message\": \"Field tidak lengkap atau invalid\" }");
        return;
    }

    // Tambahkan dokter
    hapus_dokter(dokter, jumlah_dokter, (int)id);
    printf("Dokter dengan ID %d berhasil dihapus\n", (int)id);
    mg_http_reply(c, 200,
        "Content-Type: application/json\r\nAccess-Control-Allow-Origin: *\r\n",
        "{ \"status\": \"success\", \"message\": \"Dokter berhasil dihapus\" }");
}

void handle_tampilkan_dokter(struct mg_connection *c, struct mg_http_message *hm, struct Dokter *dokter, int jumlah_dokter ) {
    char json[4096];
    tampilkan_dokter(dokter, jumlah_dokter, json, sizeof(json));
    mg_http_reply(c, 200,
        "Content-Type: application/json\r\nAccess-Control-Allow-Origin: *\r\n",
        "%s", json);
}

void handle_buat_jadwal(struct mg_connection *c, struct mg_http_message *hm, struct Dokter *dokter, int jumlah_dokter, struct PelanggaranDokter *pelanggaran, struct EntriJadwal *jadwal, int *jumlah_jadwal){
    buat_jadwal(dokter, jumlah_dokter, pelanggaran, jadwal, jumlah_jadwal);
    printf("Jadwal berhasil dibuat\n");
    mg_http_reply(c, 200,
        "Content-Type: application/json\r\nAccess-Control-Allow-Origin: *\r\n",
        "{ \"status\": \"success\", \"message\": \"Jadwal berhasil dibuat\" }");
    simpan_jadwal_ke_file(jadwal, *jumlah_jadwal, "data/jadwal.csv");

};

void handle_tampilkan_jadwal_bulanan(struct mg_connection *c, struct mg_http_message *hm,
                                     struct EntriJadwal *jadwal, int jumlah_jadwal) {
    char json[4096];
    tampilkan_jadwal_bulanan_json(jadwal, jumlah_jadwal, json, sizeof(json));

    mg_http_reply(c, 200,
        "Content-Type: application/json\r\nAccess-Control-Allow-Origin: *\r\n",
        "%s", json);
    printf("Jadwal bulanan berhasil ditampilkan\n");
}

void handle_tampilkan_jadwal_mingguan(struct mg_connection *c, struct mg_http_message *hm,
                                      struct EntriJadwal *jadwal, int jumlah_jadwal) {
    double minggu_ke_raw;
    int valid = mg_json_get_num(hm->body, "$.minggu", &minggu_ke_raw);
    int minggu_ke = (int) minggu_ke_raw;

    if (!valid || minggu_ke < 1 || minggu_ke > 4) {
        mg_http_reply(c, 400,
            "Content-Type: application/json\r\nAccess-Control-Allow-Origin: *\r\n",
            "{ \"status\": \"error\", \"message\": \"Input minggu harus antara 1-4\" }");
        return;
    }

    int start = (minggu_ke - 1) * 7;
    int end = start + 7;

    char json[4096] = {0};
    strcat(json, "[");

    for (int hari = start; hari < end && hari < jumlah_jadwal; hari++) {
        char entri[256];
        snprintf(entri, sizeof(entri),
            "{ \"hari\": %d, \"pagi\": \"%s\", \"siang\": \"%s\", \"malam\": \"%s\" }%s",
            hari + 1,
            jadwal[hari].pagi,
            jadwal[hari].siang,
            jadwal[hari].malam,
            (hari < end - 1 && hari < jumlah_jadwal - 1) ? "," : ""
        );
        strcat(json, entri);
    }

    strcat(json, "]");

    mg_http_reply(c, 200,
        "Content-Type: application/json\r\nAccess-Control-Allow-Origin: *\r\n",
        "%s", json);
    printf("Jadwal mingguan berhasil ditampilkan untuk minggu ke %d\n", minggu_ke);
}

void handle_tampilkan_jadwal_harian(struct mg_connection *c, struct mg_http_message *hm,
                                    struct EntriJadwal *jadwal, int jumlah_jadwal) {
    double hari_raw;
    int valid = mg_json_get_num(hm->body, "$.hari", &hari_raw);
    int hari = (int) hari_raw;

    // Validasi
    if (!valid || hari < 1 || hari > jumlah_jadwal) {
        mg_http_reply(c, 400,
            "Content-Type: application/json\r\nAccess-Control-Allow-Origin: *\r\n",
            "{ \"status\": \"error\", \"message\": \"Input hari harus antara 1-30\" }");
        return;
    }

    int idx = hari - 1;
    char json[256];
    snprintf(json, sizeof(json),
        "{ \"hari\": %d, \"pagi\": \"%s\", \"siang\": \"%s\", \"malam\": \"%s\" }",
        hari,
        jadwal[idx].pagi,
        jadwal[idx].siang,
        jadwal[idx].malam);

    mg_http_reply(c, 200,
        "Content-Type: application/json\r\nAccess-Control-Allow-Origin: *\r\n",
        "%s", json);
    printf("Jadwal harian berhasil ditampilkan untuk hari ke %d\n", hari);
}
void handle_tampilkan_report_shift(struct mg_connection *c, struct mg_http_message *hm,
                                    struct Dokter *dokter, int jumlah_dokter, struct PelanggaranDokter *pelanggaran) {
    char json[8192];  
    tampilkan_report_shift(dokter, pelanggaran, jumlah_dokter, json, sizeof(json));

    mg_http_reply(c, 200,
        "Content-Type: application/json\r\nAccess-Control-Allow-Origin: *\r\n",
        "%s", json);
}


