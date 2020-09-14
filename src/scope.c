#include "include/scope.h"
#include <string.h>

/**
 * @brief Initializes and allocates the scope struct 
 *        by setting the values to either NULL or 0.
 * 
 * @param[in] NONE
 * @return scope Returns newly allocated scope.
 */
scope_T* init_scope() {
    scope_T* scope = calloc(1, sizeof(struct SCOPE_STRUCT));

    scope->fn_defs = NULL;
    scope->fn_defs_size = 0;

    scope->var_defs = NULL;
    scope->var_defs_size = 0;

    return scope;
}

/**
 * @brief Adds a function definition to global scope.
 * 
 * @param[in] scope Pointer to the scope struct.
 * @param[in] fdef Pointer to node for current function definition.
 * @return fdef Updates scope for function definition node.
 */
AST_T* scope_add_fn_def(scope_T* scope, AST_T* fdef) {
    scope->fn_defs_size += 1;

    if (scope->fn_defs == NULL) {
        scope->fn_defs = calloc(1, sizeof(struct AST_STRUCT*));
    } else {
        scope->fn_defs =
            realloc(
                scope->fn_defs,
                scope->fn_defs_size * sizeof(struct AST_STRUCT**)
            );
    }

    scope->fn_defs[scope->fn_defs_size-1] =
        fdef;

    return fdef;
}

/**
 * @brief Retrieves appropriate function definition from 
 *        global scope by name.
 * 
 * @param[in] scope Pointer to the scope struct.
 * @param[in] fname String of function name.
 * @return fdef Returns function definition node if found 
 *         in global scope or NULL if not found.
 */
AST_T* scope_get_fn_def(scope_T* scope, const char* fname) {
    for (int i = 0; i < scope->fn_defs_size; i++) {
        AST_T* fdef = scope->fn_defs[i];

        if (strcmp(fdef->fn_def_name, fname) == 0) {
            return fdef;
        }
    }

    return NULL;
}

/**
 * @brief Adds a variable definition to global scope.
 * 
 * @param[in] scope Pointer to the scope struct.
 * @param[in] vdef Pointer to node for current variable definition.
 * @return fdef Updates scope for variable definition node.
 */
AST_T* scope_add_var_def(scope_T* scope, AST_T* vdef) {
    if (scope->var_defs == NULL) {
        scope->var_defs = calloc(1, sizeof(struct AST_STRUCT*));
        scope->var_defs[0] = vdef;
        scope->var_defs_size += 1;
    } else {
        scope->var_defs_size += 1;
        scope->var_defs = realloc(
            scope->var_defs,
            scope->var_defs_size * sizeof(struct AST_STRUCT*)  
        );
        scope->var_defs[scope->var_defs_size-1] = vdef;
    }

    return vdef;
}

/**
 * @brief Retrieves appropriate variable definition from 
 *        global scope by name.
 * 
 * @param[in] scope Pointer to the scope struct.
 * @param[in] name String of variable name.
 * @return vdef Returns variable definition node if found 
 *         in global scope or NULL if not found.
 */
AST_T* scope_get_var_def(scope_T* scope, const char* name) {
    for (int i = 0; i < scope->var_defs_size; i++) {
        AST_T* vdef = scope->var_defs[i];

        if (strcmp(vdef->var_def_var_name, name) == 0) {
            return vdef;
        }
    }

    return NULL;
}
