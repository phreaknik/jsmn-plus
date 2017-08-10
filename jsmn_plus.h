#ifndef __JSMN_PLUS_H_
#define __JSMN_PLUS_H_

#include "jsmn.h"
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

enum jsmnpluserr {
  /* The specified string was not found in the token list */
  JSMN_PLUS_ERROR_NOTFOUND = JSMN_ERROR_PART + 1,
  /* Speciffied scope object is not of JSMN_OBJECT type */
  JSMN_PLUS_ERROR_INVALSCOPE,
};


/*
 * Search for a token within the scope of specified JSON object token. This is especially
 * useful for quickly finding nested JSON tokens whithout using excessive resources.
 */
int jsmn_search(const char *js, jsmntok_t *token_list, int num_tokens,
                int scope_object, const char *search_key);

#ifdef __cplusplus
}
#endif

#endif /* __JSMN_PLUS_H_ */
