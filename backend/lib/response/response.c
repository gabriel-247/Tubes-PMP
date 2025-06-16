#include "response.h"

// Fungsi utilitas untuk reply JSON dengan CORS
void mg_http_reply_json(struct mg_connection *c, int code, const char *body) {
  mg_http_reply(c, code,
    "Content-Type: application/json\r\n"
    "Access-Control-Allow-Origin: *\r\n",
    "%s\n", body);
}
