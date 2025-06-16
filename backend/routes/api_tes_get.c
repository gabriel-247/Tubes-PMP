#include "../lib/mongoose/mongoose.h"
#include "routes.h"

void handle_tes_get(struct mg_connection *c, struct mg_http_message *hm) {
  mg_http_reply(c, 200,
    "Content-Type: application/json\r\nAccess-Control-Allow-Origin: *\r\n",
    "{ \"message\": \"Boss!! tes get amann\" }\n");
}
