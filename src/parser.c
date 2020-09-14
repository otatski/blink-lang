#include "include/parser.h"
#include "include/scope.h"
#include <stdio.h>
#include <string.h>

/**
 * @brief Initializes and allocates the parser by setting
 *        the lexer, the current token, and previous token.
 * 
 * @param[in] lexer Pointer to lexer struct
 * @return parser Returns newly allocated parser.
 */
parser_T* init_parser(lexer_T* lexer) {
    parser_T* parser = calloc(1, sizeof(struct PARSER_STRUCT));
    parser->lexer = lexer;
    parser->current_token = lexer_get_next_token(lexer);
    parser->prev_token = parser->current_token;

    parser->scope = init_scope();

    return parser;
}

/**
 * @brief Consumes a token and moves to the next if the
 *        current token is the same as the expected token.
 * 
 * @param[in] parser Pointer to parser struct
 * @param[in] token_type Integer value of the value in the token
 * @return void Does not return.
 */
void parser_consume(parser_T* parser, int token_type) {
    if (parser->current_token->type == token_type) {
        parser->prev_token = parser->current_token;
        parser->current_token = lexer_get_next_token(parser->lexer);
    } else {
        printf(
            "Unexpected token `%s`, with type %d\n",
            parser->current_token->value,
            parser->current_token->type
        );
        exit(1);
    }
}

/**
 * @brief Essentially parser main. Begins parsing statements.
 * 
 * @param[in] parser Pointer to parser struct
 * @param[in] scope Pointer to scope struct
 * @return AST_T Returns an abstract syntax tree node of proper type(s)
 */
AST_T* parser_parse(parser_T* parser, scope_T* scope) {
    return parser_parse_statements(parser, scope);
}

/**
 * @brief Parses a single statement. A statement ends with a semicolon.
 * 
 * @param[in] parser Pointer to parser struct
 * @param[in] scope Pointer to scope struct
 * @return AST_T Returns an abstract syntax tree node of proper type(s)
 */
AST_T* parser_parse_statement(parser_T* parser, scope_T* scope) {
    switch (parser->current_token->type) {
        case TOKEN_ID: {
            return parser_parse_id(parser, scope);
        }
    }

    return init_ast(AST_NOOP);
}

/**
 * @brief Parses a list of statements. A statement ends with a semicolon.
 * 
 * @param[in] parser Pointer to parser struct
 * @param[in] scope Pointer to scope struct
 * @return AST_T Returns an abstract syntax tree node of proper type(s)
 */
AST_T* parser_parse_statements(parser_T* parser, scope_T* scope) {
    AST_T* compound = init_ast(AST_COMPOUND);
    compound->scope = scope;
    compound->compound_value = calloc(1, sizeof(struct AST_STRUCT*));

    AST_T* ast_statement = parser_parse_statement(parser, scope);
    ast_statement->scope = scope;
    compound->compound_value[0] = ast_statement;
    compound->compound_size += 1;

    while (parser->current_token->type == TOKEN_SEMI) {
        parser_consume(parser, TOKEN_SEMI);

        AST_T* ast_statement = parser_parse_statement(parser, scope);

        if (ast_statement) {
            compound->compound_size += 1;
            // Reallocate memory for the compound statement.
            compound->compound_value = realloc(
                compound->compound_value,
                compound->compound_size * sizeof(struct AST_STRUCT*)
            );
            compound->compound_value[compound->compound_size-1] = ast_statement;
        }
    }

    return compound;
}

/**
 * @brief Parses an expression.
 * 
 * @param[in] parser Pointer to parser struct
 * @param[in] scope Pointer to scope struct
 * @return AST_T Returns an abstract syntax tree node of proper type(s)
 */
AST_T* parser_parse_expr(parser_T* parser, scope_T* scope) {
    switch (parser->current_token->type) {
        case TOKEN_STRING_VALUE: {
            return parser_parse_string(parser, scope);
        }
        case TOKEN_ID: {
            return parser_parse_id(parser, scope);
        }
    }

    return init_ast(AST_NOOP);
}

/**
 * @brief Parses a function call.
 * 
 * @param[in] parser Pointer to parser struct
 * @param[in] scope Pointer to scope struct
 * @return AST_T Returns an abstract syntax tree node of proper type(s)
 */
AST_T* parser_parse_fn_call(parser_T* parser, scope_T* scope) {
    AST_T* fn_call = init_ast(AST_FUNCTION_CALL);

    fn_call->fn_call_name = parser->prev_token->value;
    parser_consume(parser, TOKEN_LPAREN); 

    fn_call->fn_call_args = calloc(1, sizeof(struct AST_STRUCT*));

    AST_T* ast_expr = parser_parse_expr(parser, scope);
    fn_call->fn_call_args[0] = ast_expr;
    fn_call->fn_call_args_size += 1;

    while (parser->current_token->type == TOKEN_COMMA) {
        parser_consume(parser, TOKEN_COMMA);

        AST_T* ast_expr = parser_parse_expr(parser, scope);
        fn_call->fn_call_args_size += 1;
        fn_call->fn_call_args = realloc(
            fn_call->fn_call_args,
            fn_call->fn_call_args_size * sizeof(struct AST_STRUCT*)
        );
        fn_call->fn_call_args[fn_call->fn_call_args_size-1] = ast_expr;
    }
    parser_consume(parser, TOKEN_RPAREN);

    fn_call->scope = scope;

    return fn_call;
}

/**
 * @brief Parses a variable definition.
 * 
 * @param[in] parser Pointer to parser struct
 * @param[in] scope Pointer to scope struct
 * @return AST_T Returns an abstract syntax tree of proper type(s)
 */
AST_T* parser_parse_var_def(parser_T* parser, scope_T* scope) {
    parser_consume(parser, TOKEN_ID); // var
    char* var_def_var_name = parser->current_token->value;
    parser_consume(parser, TOKEN_ID); // var name
    parser_consume(parser, TOKEN_EQUALS);
    AST_T* var_def_value = parser_parse_expr(parser, scope);

    AST_T* var_def = init_ast(AST_VARIABLE_DEFINITION);
    var_def->var_def_var_name = var_def_var_name;
    var_def->var_def_value = var_def_value;

    var_def->scope = scope;

    return var_def;
}

/**
 * @brief Parses a function definition.
 * 
 * @param[in] parser Pointer to parser struct
 * @param[in] scope Pointer to scope struct
 * @return AST_T Returns an abstract syntax tree of proper type(s)
 */
AST_T* parser_parse_fn_def(parser_T* parser, scope_T* scope) {
    AST_T* ast = init_ast(AST_FUNCTION_DEFINITION);
    parser_consume(parser, TOKEN_ID); // fn

    char* fn_name = parser->current_token->value;
    ast->fn_def_name = calloc(
            strlen(fn_name) + 1, sizeof(char)
    );
    strcpy(ast->fn_def_name, fn_name);

    parser_consume(parser, TOKEN_ID); // fn name

    parser_consume(parser, TOKEN_LPAREN); // fn left paren "("

    // Allocate memory for function arguments.
    ast->fn_def_args =
        calloc(1, sizeof(struct AST_STRUCT*));

    // Start parsing arguments
    AST_T* arg = parser_parse_var(parser, scope);
    ast->fn_def_args_size += 1;
    ast->fn_def_args[ast->fn_def_args_size-1] = arg;

    // Continue to parse arguments as long as it is encountering a comma.
    while (parser->current_token->type == TOKEN_COMMA) {
        parser_consume(parser, TOKEN_COMMA);

        ast->fn_def_args_size += 1;
        // Reallocate memory for each argument.
        ast->fn_def_args =
            realloc(
                    ast->fn_def_args,
                    ast->fn_def_args_size * sizeof(struct AST_STRUCT*)
                   );

        AST_T* arg = parser_parse_var(parser, scope);
        ast->fn_def_args[ast->fn_def_args_size-1] = arg;
    }

    parser_consume(parser, TOKEN_RPAREN); // fn right paren ")"
    
    parser_consume(parser, TOKEN_LBRACE); // fn left brace "{"
    
    ast->fn_def_body = parser_parse_statements(parser, scope);

    parser_consume(parser, TOKEN_RBRACE); // fn right brace "}"

    ast->scope = scope;

    return ast;
}

/**
 * @brief Parses a variable.
 * 
 * @param[in] parser Pointer to parser struct
 * @param[in] scope Pointer to scope struct
 * @return AST_T Returns an abstract syntax tree node for variable of proper type.
 */
AST_T* parser_parse_var(parser_T* parser, scope_T* scope) {
    char* token_value = parser->current_token->value;
    parser_consume(parser, TOKEN_ID); // var name or fn call name

    if (parser->current_token->type == TOKEN_LPAREN) {
        return parser_parse_fn_call(parser, scope);
    }

    AST_T* ast_var = init_ast(AST_VARIABLE);
    ast_var->var_name = token_value;

    ast_var->scope = scope;

    return ast_var;
}

/**
 * @brief Parses a string.
 * 
 * @param[in] parser Pointer to parser struct
 * @param[in] scope Pointer to scope struct
 * @return AST_T Returns an abstract syntax tree node of type string.
 */
AST_T* parser_parse_string(parser_T* parser, scope_T* scope) {
    AST_T* ast_string = init_ast(AST_STRING);
    ast_string->string_value = parser->current_token->value;

    parser_consume(parser, TOKEN_STRING_VALUE);

    ast_string->scope = scope;

    return ast_string;
}

/**
 * @brief Parses a variable definition.
 * 
 * @param[in] parser Pointer to parser struct
 * @param[in] scope Pointer to scope struct
 * @return AST_T Returns an abstract syntax tree of proper type(s)
 */
AST_T* parser_parse_id(parser_T* parser, scope_T* scope) {
    if (strcmp(parser->current_token->value, "String") == 0) {
        return parser_parse_var_def(parser, scope);
    } else if (strcmp(parser->current_token->value, "fn") == 0) {
        return parser_parse_fn_def(parser, scope);
    } else {
        return parser_parse_var(parser, scope);
    }
}
