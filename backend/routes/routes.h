#ifndef ROUTES_H
#define ROUTES_H

#include "../lib/mongoose/mongoose.h"

void handle_tes_get(struct mg_connection *c, struct mg_http_message *hm);
void handle_tes_post(struct mg_connection *c, struct mg_http_message *hm);
void handle_tampilkan_dokter(struct mg_connection *c, struct mg_http_message *hm);
void handle_tambah_dokter(struct mg_connection *c, struct mg_http_message *hm);

#endif

