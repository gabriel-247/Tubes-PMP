#ifndef JSON_UTILS_H
#define JSON_UTILS_H

#include "../mongoose/mongoose.h"

// Ambil string dari JSON body (alokasi memory, jangan lupa free)
char *json_get_str(struct mg_http_message *hm, const char *json_path);

// Ambil long/integer dari JSON
long json_get_long(struct mg_http_message *hm, const char *json_path, long default_val);

// Ambil boolean dari JSON
bool json_get_bool(struct mg_http_message *hm, const char *json_path, bool default_val);

#endif
