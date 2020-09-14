#include "include/token.h"
#include <stdlib.h>

/**
 * @brief Initializes and allocates new token.
 *        Sets the type and value to the provided parameters 
 * 
 * @param[in] type Integer value of the type.
 * @param[in] value String of the value.
 * @return token Returns newly allocated token.
 */
token_T* init_token(int type, char* value) {
    token_T* token = calloc(1, sizeof(struct TOKEN_STRUCT));
    token->type = type;
    token->value = value;

    return token;
}
