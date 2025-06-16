#include "mongoose.h"
#include "routes/routes.h"
#define DOKTER_MAKS 100

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
      handle_tampilkan_dokter(c, hm);
      
    // POST /api/tambah_dokter
    } else if (match(hm->method, "POST") && match(hm->uri, "/api/tambah_dokter")) {
      handle_tambah_dokter(c, hm);

    } else if (match(hm->method, "OPTIONS")) {
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
  struct mg_mgr mgr; //Event management structure that holds a list of active connections, together with some housekeeping information
  mg_mgr_init(&mgr); //Initialize event manager structure
  mg_http_listen(&mgr, "http://localhost:8001", handle_request, NULL); //Create HTTP listener
  printf("Server aktif di http://localhost:8001\n");

  for (;;) mg_mgr_poll(&mgr, 1000);
  mg_mgr_free(&mgr); //Close all connections, and free all resources.
  return 0;
}
