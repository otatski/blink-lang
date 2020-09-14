#ifndef AST_H
#define AST_H
#include <stdlib.h>

typedef struct AST_STRUCT
{
    enum {
        AST_VARIABLE_DEFINITION,
        AST_FUNCTION_DEFINITION,
        AST_VARIABLE,
        AST_FUNCTION_CALL,
        AST_STRING,
        AST_COMPOUND,
        AST_NOOP
    } type;

    struct SCOPE_STRUCT* scope;

    /* AST_VARIABLE_DEFINITION */
    char* var_def_var_name;
    struct AST_STRUCT* var_def_value;

    /* AST_FUNCTION_DEFINITION */
    struct AST_STRUCT* fn_def_body;
    char* fn_def_name;
    struct AST_STRUCT** fn_def_args;
    size_t fn_def_args_size;

    /* AST_VARIABLE */
    char* var_name;

    /* AST_FUNCTION_CALL */
    char* fn_call_name;
    struct AST_STRUCT** fn_call_args;
    size_t fn_call_args_size;

    /* AST_STRING */
    char* string_value;

    /* AST_COMPOUND */
    struct AST_STRUCT** compound_value;
    size_t compound_size;
} AST_T;

/**
 * @brief Initializes and allocates the abstract syntax tree by setting
 *        the type, and setting the remaining values to NULL or 0.
 * 
 * @param[in] type Integer value of the node type.
 * @return parser Returns newly allocated abstract syntax tree.
 */
AST_T* init_ast(int type);
#endif
