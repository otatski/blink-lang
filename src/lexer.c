#include "include/lexer.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>


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
lexer_T *init_lexer(char* contents) {
    lexer_T *lexer = calloc(1, sizeof(struct LEXER_STRUCT));
    lexer->contents = contents;
    lexer->i = 0;
    lexer->c = contents[lexer->i];

    return lexer;
}

/**
 * @brief Inspects each character ensuring that it is not a NULL 
 *        character and that the character index is less than the
 *        amount of characters in the context. After doing so, 
 *        it moves the pointer to the next character.
 * 
 * @param[in] lexer Pointer to lexer struct
 * @return void Does not return.
 */
void lexer_advance(lexer_T* lexer) {
    if (lexer->c != '\0' && lexer->i < strlen(lexer->contents)) {
        lexer->i += 1;
        lexer->c = lexer->contents[lexer->i];
    }
}

/**
 * @brief Inspects each character and skips whitespace and newlines. 
 *        If either are encountered then the function lexer_advance 
 *        is called and the pointer is incremented to the next character.
 * 
 * @param[in] lexer Pointer to lexer struct
 * @return void Does not return.
 */
void lexer_skip_whitespace(lexer_T* lexer) {
    while (lexer->c == ' ' || lexer->c == '\n') {
        lexer_advance(lexer);
    }
}

/**
 * @brief Inspects each character and skips whitespace and newlines. 
 *        If either are encountered then the function lexer_advance 
 *        is called and the pointer is incremented to the next character.
 * 
 * @param[in] lexer Pointer to lexer struct
 * @return void Does not return.
 */
token_T *lexer_get_next_token(lexer_T* lexer) {
    while (lexer->c != '\0' && lexer->i < strlen(lexer->contents)) {
        if (lexer->c == ' ' || lexer->c == 10) {
            lexer_skip_whitespace(lexer);
        }

        if (isalnum(lexer->c)) {
            return lexer_collect_id(lexer);
        }

        if (lexer->c == '"') {
            return lexer_collect_string(lexer);
        }

        switch (lexer->c) {
            case '=': {
                return lexer_advance_with_token(
                    lexer, 
                    init_token(TOKEN_EQUALS, lexer_get_current_char_as_string(lexer)));
            }
            case ';': {
                return lexer_advance_with_token(
                    lexer, 
                    init_token(TOKEN_SEMI, lexer_get_current_char_as_string(lexer)));
            }
            case '(': {
                return lexer_advance_with_token(
                    lexer, 
                    init_token(TOKEN_LPAREN, lexer_get_current_char_as_string(lexer)));
            }
            case ')': {
                return lexer_advance_with_token(
                    lexer, 
                    init_token(TOKEN_RPAREN, lexer_get_current_char_as_string(lexer)));
            }
            case '{': {
                return lexer_advance_with_token(
                    lexer, 
                    init_token(TOKEN_LBRACE, lexer_get_current_char_as_string(lexer)));
            }
            case '}': {
                return lexer_advance_with_token(
                    lexer, 
                    init_token(TOKEN_RBRACE, lexer_get_current_char_as_string(lexer)));
            }
            case ',': {
                return lexer_advance_with_token(
                    lexer, 
                    init_token(TOKEN_COMMA, lexer_get_current_char_as_string(lexer)));
            }
        }
    }

    return init_token(TOKEN_EOF, "\0");
}


/**
 * @brief Inspects each character and adds it to the string as long as
 *        it does not encounter another quote ( " ).
 * 
 * @param[in] lexer Pointer to lexer struct
 * @return token Returns a String token.
 */
token_T* lexer_collect_string(lexer_T* lexer) {
    lexer_advance(lexer);

    char* value = calloc(1, sizeof(char));
    value[0] = '\0';

    while (lexer->c != '"')  {
        char* s = lexer_get_current_char_as_string(lexer);
        value = realloc(value, (strlen(value) + strlen(s) + 1) * sizeof(char));
        strcat(value, s);

        lexer_advance(lexer);
    }

    lexer_advance(lexer);

    return init_token(TOKEN_STRING_VALUE, value);
}

/**
 * @brief Inspects each character and adds it to the value
 *        as long as the current character is alphanumeric.
 * 
 * @param[in] lexer Pointer to lexer struct
 * @return token Returns an ID token.
 */
token_T *lexer_collect_id(lexer_T *lexer) {
    char *value = calloc(1, sizeof(char));
    value[0] = '\0';

    while (isalnum(lexer->c)) {
        char *s = lexer_get_current_char_as_string(lexer);
        value = realloc(value, (strlen(value) + strlen(s) + 1) * sizeof(char));
        strcat(value, s);

        lexer_advance(lexer);
    }

    return init_token(TOKEN_ID, value);
}

/**
 * @brief Advances the token
 * 
 * @param[in] lexer Pointer to lexer struct
 * @param[in] token Pointer to token struct
 * @return token Returns a token,
 */
token_T *lexer_advance_with_token(lexer_T *lexer, token_T *token) {
    lexer_advance(lexer);

    return token;
}

/**
 * @brief Allocates memory for current character and returns.
 * 
 * @param[in] lexer Pointer to lexer struct
 * @return str Returns newly allocated String.
 */
char *lexer_get_current_char_as_string(lexer_T *lexer) {
    char *str = calloc(2, sizeof(char));
    str[0] = lexer->c;
    str[1] = '\0';

    return str;
}
