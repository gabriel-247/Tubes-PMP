#include "../lib/mongoose/mongoose.h"
#include "routes.h"

void handle_tes_post(struct mg_connection *c, struct mg_http_message *hm) {
  char *nama = mg_json_get_str(hm->body, "$.nama");
  char *pesan = mg_json_get_str(hm->body, "$.pesan");

  if (nama && pesan) {
    mg_http_reply(c, 200,
      "Content-Type: application/json\r\nAccess-Control-Allow-Origin: *\r\n",
      "{ \"status\": \"tes post berhasil brokk\", \"nama\": \"%s\", \"pesan\": \"%s\" }\n",
      nama, pesan);
    free(nama);
    free(pesan);
  } else {
    mg_http_reply(c, 400,
      "Content-Type: application/json\r\nAccess-Control-Allow-Origin: *\r\n",
      "{ \"status\": \"error\", \"message\": \"Missing fields\" }\n");
  }
}
