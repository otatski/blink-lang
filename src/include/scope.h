#ifndef SCOPE_H
#define SCOPE_H
#include "AST.h"

typedef struct SCOPE_STRUCT
{
    AST_T** fn_defs;
    size_t fn_defs_size;

    AST_T** var_defs;
    size_t var_defs_size;
} scope_T;

/**
 * @brief Initializes and allocates the scope struct 
 *        by setting the values to either NULL or 0.
 * 
 * @param[in] NONE
 * @return scope Returns newly allocated scope.
 */
scope_T* init_scope();

/**
 * @brief Adds a function definition to global scope.
 * 
 * @param[in] scope Pointer to the scope struct.
 * @param[in] fdef Pointer to node for current function definition.
 * @return fdef Updates scope for function definition node.
 */
AST_T* scope_add_fn_def(scope_T* scope, AST_T* fdef);

/**
 * @brief Retrieves appropriate function definition from 
 *        global scope by name.
 * 
 * @param[in] scope Pointer to the scope struct.
 * @param[in] fname String of function name.
 * @return fdef Returns function definition node if found 
 *         in global scope or NULL if not found.
 */
AST_T* scope_get_fn_def(scope_T* scope, const char* fname);

/**
 * @brief Adds a variable definition to global scope.
 * 
 * @param[in] scope Pointer to the scope struct.
 * @param[in] vdef Pointer to node for current variable definition.
 * @return fdef Updates scope for variable definition node.
 */
AST_T* scope_add_var_def(scope_T* scope, AST_T* vdef);

/**
 * @brief Retrieves appropriate variable definition from 
 *        global scope by name.
 * 
 * @param[in] scope Pointer to the scope struct.
 * @param[in] name String of variable name.
 * @return vdef Returns variable definition node if found 
 *         in global scope or NULL if not found.
 */
AST_T* scope_get_var_def(scope_T* scope, const char* name);
#endif
