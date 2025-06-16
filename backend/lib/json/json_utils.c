#include "json_utils.h"
#include <stdlib.h>

char *json_get_str(struct mg_http_message *hm, const char *json_path) {
  return mg_json_get_str(hm->body, json_path); // malloc'd → harus di-free
}

long json_get_long(struct mg_http_message *hm, const char *json_path, long default_val) {
  long val;
  return mg_json_get_long(hm->body, json_path, &val) ? val : default_val;
}

bool json_get_bool(struct mg_http_message *hm, const char *json_path, bool default_val) {
  bool val;
  return mg_json_get_bool(hm->body, json_path, &val) ? val : default_val;
}
