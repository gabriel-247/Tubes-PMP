#include "mongoose.h"
#include "routes/routes.h"
#include "lib/dokter/dokter.h"
#include "lib/jadwal/jadwal.h"
#include "lib/io/io.h"
#include <stdio.h>
#include <stdlib.h>

struct Dokter dokter[50];
struct EntriJadwal jadwal[30];
struct PelanggaranDokter pelanggaran[50];
int jumlah_dokter = 0;
int jumlah_jadwal = 0;
char nama_file_dokter[] = "data/dokter.csv";
char nama_file_jadwal[] = "data/jadwal.csv";

int match(struct mg_str s, const char *cstr) {
  return (s.len == strlen(cstr) && strncmp(s.buf, cstr, s.len) == 0);
}

void handle_request(struct mg_connection *c, int ev, void *ev_data) {
  if (ev == MG_EV_HTTP_MSG) {
    struct mg_http_message *hm = (struct mg_http_message *) ev_data;

    // GET /api/hello
    if (match(hm->method, "GET") && match(hm->uri, "/api/tes_get")) {
      handle_tes_get(c, hm);

    // POST /api/nama
    } else if (match(hm->method, "POST") && match(hm->uri, "/api/tes_post")) {
      handle_tes_post(c, hm);

    // GET /api/tampilkan_dokter
    } else if (match(hm->method, "GET") && match(hm->uri, "/api/tampilkan_dokter")) {
      handle_tampilkan_dokter(c, hm, dokter, jumlah_dokter);
      
    // POST /api/tambah_dokter
    } else if (match(hm->method, "POST") && match(hm->uri, "/api/tambah_dokter")) {
      handle_tambah_dokter(c, hm, dokter, &jumlah_dokter);

    //POST/api/hapus_dokter 
    } else if (match(hm->method, "POST") && match(hm->uri, "/api/hapus_dokter")) {
      handle_hapus_dokter(c, hm, dokter, &jumlah_dokter);

    // POST /buat/buat_jadwal 
    }else if (match(hm->method, "POST") && match(hm->uri, "/api/buat_jadwal")) {
      handle_buat_jadwal(c, hm, dokter, jumlah_dokter, pelanggaran, jadwal, &jumlah_jadwal);

      // POST /api/tampilkan_jadwal_bulanan
    }else if (match(hm->method, "POST") && match(hm->uri, "/api/tampilkan_jadwal_bulanan")) {
      handle_tampilkan_jadwal_bulanan(c, hm, jadwal, jumlah_jadwal);
      // POST /api/tampilkan_jadwal_mingguan
    }else if (match(hm->method, "POST") && match(hm->uri, "/api/tampilkan_jadwal_mingguan")) {
      handle_tampilkan_jadwal_mingguan(c, hm, jadwal, jumlah_jadwal);
      
      // POST /api/tampilkan_jadwal_harian
    }else if (match(hm->method, "POST") && match(hm->uri, "/api/tampilkan_jadwal_harian")) {
      handle_tampilkan_jadwal_harian(c, hm, jadwal, jumlah_jadwal);
      // POST /api/tampilkan_report_shift
    }else if (match(hm->method, "POST") && match(hm->uri, "/api/tampilkan_report_shift")) {
      handle_tampilkan_report_shift(c, hm, dokter, jumlah_dokter, pelanggaran);
    }else if (match(hm->method, "OPTIONS")) {
      mg_http_reply(c, 200,
        "Access-Control-Allow-Origin: *\r\n"
        "Access-Control-Allow-Methods: GET, POST, OPTIONS\r\n"
        "Access-Control-Allow-Headers: Content-Type\r\n\r\n", "");

    // File statis
    } else {
      struct mg_http_serve_opts opts = {.root_dir = "web_root"};
      mg_http_serve_dir(c, hm, &opts);
    }
  }
}

int main(void) {
  jumlah_dokter = baca_dokter_dari_file(dokter, nama_file_dokter); // Read doctors from file when starting the server
  printf("Berhasil membaca %d dokter dari file.\n", jumlah_dokter);

  struct mg_mgr mgr; //Event management structure that holds a list of active connections
  mg_mgr_init(&mgr); //Initialize event manager structure
  mg_http_listen(&mgr, "http://localhost:8001", handle_request, NULL); //Create HTTP listener
  printf("Server aktif di http://localhost:8001\n");

  for (;;) mg_mgr_poll(&mgr, 1000);
  mg_mgr_free(&mgr); //Close all connections, and free all resources.
  return 0;
}
