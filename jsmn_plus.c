#include "jsmn_plus.h"
#include "jsmn.h"
#include "string.h"

/**
 * Search for a token within the scope of specified JSON object token. This is especially
 * useful for quickly finding nested JSON tokens whithout using excessive resources.
 */
int jsmn_search(const char *js, jsmntok_t *token_list, int num_tokens,
                int scope_object, const char *search_key)
{
    int i, token_len, num_remaining, skip_count;
    jsmntok_t *token;

    // Verify that this is truly an object
    i = scope_object;
    if(token_list[i].type != JSMN_OBJECT)
    {
        return JSMN_PLUS_ERROR_INVALSCOPE;
    }

    // Loop through each token in this object
    skip_count = 0;
    num_remaining = token_list[i].size;
    while( (i < num_tokens) && (num_remaining > 0) )
    {
        i++; // Increment token index
        token = &token_list[i];
        token_len = token->end - token->start;

        // Skip tokens that are not immediately in this JSON object
        if( (token->type == JSMN_OBJECT) || (token->type == JSMN_ARRAY) )
        {
            skip_count += token->size;
            continue;
        }

        // Skip tokens that are not in this object scope
        if(skip_count > 0)
        {
            skip_count += token->size - 1;
            continue;
        }

        // Update how many tokens remain in this object
        num_remaining += token->size - 1;

        // Check if this is the token we want
        if((token_len == strlen(search_key)) &&
                (memcmp(&js[token->start], search_key, token_len) == 0))
        {
            // Success! Return the index of the token associated with this token
            return i;
        }
    }

    // Failure! Key not found
    return JSMN_PLUS_ERROR_NOTFOUND;
}
