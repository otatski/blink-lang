#include "include/AST.h"

/**
 * @brief Initializes and allocates the abstract syntax tree by setting
 *        the type, and setting the remaining values to NULL or 0.
 * 
 * @param[in] type Integer value of the node type.
 * @return parser Returns newly allocated abstract syntax tree.
 */
AST_T* init_ast(int type) {
    AST_T* ast = calloc(1, sizeof(struct AST_STRUCT));
    ast->type = type;

    ast->scope = NULL;

    // AST_VARIABLE_DEFINITION
    ast->var_def_var_name = NULL;
    ast->var_def_value = NULL;

    // AST_FUNCTION_DEFINITION
    ast->fn_def_body = NULL;
    ast->fn_def_name = NULL;
    ast->fn_def_args = NULL;
    ast->fn_def_args_size = 0;

    // AST_VARIABLE
    ast->var_name = NULL;

    // AST_FUNCTION_CALL
    ast->fn_call_name = NULL;
    ast->fn_call_args = NULL;
    ast->fn_call_args_size = 0;

    // AST_STRING
    ast->string_value = NULL;

    // AST_COMPOUND
    ast->compound_value = NULL;
    ast->compound_size = 0;

    return ast;
}
