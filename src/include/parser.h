#ifndef PARSER_H
#define PARSER_H
#include "lexer.h"
#include "AST.h"
#include "scope.h"


typedef struct PARSER_STRUCT
{
    lexer_T* lexer;
    token_T* current_token;
    token_T* prev_token;
    scope_T* scope;
} parser_T;

/**
 * @brief Initializes and allocates the parser by setting
 *        the lexer, the current token, and previous token.
 * 
 * @param[in] lexer Pointer to lexer struct
 * @return parser Returns newly allocated parser.
 */
parser_T* init_parser(lexer_T* lexer);

/**
 * @brief Consumes a token and moves to the next if the
 *        current token is the same as the expected token.
 * 
 * @param[in] parser Pointer to parser struct
 * @param[in] token_type Integer value of the value in the token
 * @return void Does not return.
 */
void parser_consume(parser_T* parser, int token_type);

/**
 * @brief Essentially parser main. Begins parsing statements.
 * 
 * @param[in] parser Pointer to parser struct
 * @param[in] scope Pointer to scope struct
 * @return AST_T Returns an abstract syntax tree of proper type(s)
 */
AST_T* parser_parse(parser_T* parser, scope_T* scope);

/**
 * @brief Parses a single statement. A statement ends with a semicolon.
 * 
 * @param[in] parser Pointer to parser struct
 * @param[in] scope Pointer to scope struct
 * @return AST_T Returns an abstract syntax tree of proper type(s)
 */
AST_T* parser_parse_statement(parser_T* parser, scope_T* scope);

/**
 * @brief Parses a list of statements. A statement ends with a semicolon.
 * 
 * @param[in] parser Pointer to parser struct
 * @param[in] scope Pointer to scope struct
 * @return AST_T Returns an abstract syntax tree node of proper type(s)
 */
AST_T* parser_parse_statements(parser_T* parser, scope_T* scope);

/**
 * @brief Parses an expression.
 * 
 * @param[in] parser Pointer to parser struct
 * @param[in] scope Pointer to scope struct
 * @return AST_T Returns an abstract syntax tree node of proper type(s)
 */
AST_T* parser_parse_expr(parser_T* parser, scope_T* scope);

/**
 * @brief Parses a function call.
 * 
 * @param[in] parser Pointer to parser struct
 * @param[in] scope Pointer to scope struct
 * @return AST_T Returns an abstract syntax tree node of proper type(s)
 */
AST_T* parser_parse_fn_call(parser_T* parser, scope_T* scope);

/**
 * @brief Parses a variable definition.
 * 
 * @param[in] parser Pointer to parser struct
 * @param[in] scope Pointer to scope struct
 * @return AST_T Returns an abstract syntax tree of proper type(s)
 */
AST_T* parser_parse_var_def(parser_T* parser, scope_T* scope);

/**
 * @brief Parses a function definition.
 * 
 * @param[in] parser Pointer to parser struct
 * @param[in] scope Pointer to scope struct
 * @return AST_T Returns an abstract syntax tree of proper type(s)
 */
AST_T* parser_parse_fn_def(parser_T* parser, scope_T* scope);

/**
 * @brief Parses a variable.
 * 
 * @param[in] parser Pointer to parser struct
 * @param[in] scope Pointer to scope struct
 * @return AST_T Returns an abstract syntax tree node for variable of proper type.
 */
AST_T* parser_parse_var(parser_T* parser, scope_T* scope);

/**
 * @brief Parses a string.
 * 
 * @param[in] parser Pointer to parser struct
 * @param[in] scope Pointer to scope struct
 * @return AST_T Returns an abstract syntax tree node of type string.
 */
AST_T* parser_parse_string(parser_T* parser, scope_T* scope);

/**
 * @brief Parses a variable definition.
 * 
 * @param[in] parser Pointer to parser struct
 * @param[in] scope Pointer to scope struct
 * @return AST_T Returns an abstract syntax tree of proper type(s)
 */
AST_T* parser_parse_id(parser_T* parser, scope_T* scope);

#endif
