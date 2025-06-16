#ifndef RESPONSE_H
#define RESPONSE_H

// Fungsi untuk membalas response JSON dengan header CORS
void mg_http_reply_json(struct mg_connection *c, int code, const char *body);

#endif
