#ifndef LEXER_H
#define LEXER_H
#include "token.h"


typedef struct LEXER_STRUCT
{
    char c;
    unsigned int i;
    char* contents;
} lexer_T;

/**
 * @brief Initializes lexer and allocates memory for string of  
 *        characters from the contents of the input file.
 *        During initialization, the contents are set to the 
 *        contents of the input file, the character index is set 
 *        to 0, and the current character is set to the first character 
 *        of the contents.
 * 
 * @param[in] contents String of character from the input file
 * @return lexer Newly allocated lexer struct
 */
lexer_T *init_lexer(char* contents);

/**
 * @brief Inspects each character ensuring that it is not a NULL 
 *        character and that the character index is less than the
 *        amount of characters in the context. After doing so, 
 *        it moves the pointer to the next character.
 * 
 * @param[in] lexer Pointer to lexer struct
 * @return void Does not return.
 */
void lexer_advance(lexer_T* lexer);

/**
 * @brief Inspects each character and skips whitespace and newlines. 
 *        If either are encountered then the function lexer_advance 
 *        is called and the pointer is incremented to the next character.
 * 
 * @param[in] lexer Pointer to lexer struct
 * @return void Does not return.
 */
void lexer_skip_whitespace(lexer_T* lexer);

/**
 * @brief Inspects each character and skips whitespace and newlines. 
 *        If either are encountered then the function lexer_advance 
 *        is called and the pointer is incremented to the next character.
 * 
 * @param[in] lexer Pointer to lexer struct
 * @return void Does not return.
 */
token_T *lexer_get_next_token(lexer_T* lexer);


/**
 * @brief Inspects each character and adds it to the string as long as
 *        it does not encounter another quote ( " ).
 * 
 * @param[in] lexer Pointer to lexer struct
 * @return token Returns a String token.
 */
token_T* lexer_collect_string(lexer_T* lexer);

/**
 * @brief Inspects each character and adds it to the value
 *        as long as the current character is alphanumeric.
 * 
 * @param[in] lexer Pointer to lexer struct
 * @return token Returns an ID token.
 */
token_T *lexer_collect_id(lexer_T *lexer);

/**
 * @brief Advances the token
 * 
 * @param[in] lexer Pointer to lexer struct
 * @param[in] token Pointer to token struct
 * @return token Returns a token,
 */
token_T *lexer_advance_with_token(lexer_T *lexer, token_T *token);

/**
 * @brief Allocates memory for current character and returns.
 * 
 * @param[in] lexer Pointer to lexer struct
 * @return str Returns newly allocated String.
 */
char *lexer_get_current_char_as_string(lexer_T *lexer);
#endif
