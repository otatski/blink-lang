#include "include/runtime.h"
#include "include/scope.h"
#include <stdio.h>
#include <string.h>

/**
 * @brief Builting function for Blink's print function.
 * 
 * @param[in] runtime Pointer to the runtime struct.
 * @param[in] args List of arguments for the Print function.
 * @param[in] args_size Integer of arguments size.
 * @return parser Abstract syntax tree node of proper type.
 */
static AST_T* builtin_fn_print(runtime_T* runtime, AST_T** args, int args_size) {
    for (int i = 0; i < args_size; i++) {
        AST_T* visited_ast = runtime_visit(runtime, args[i]);

        switch (visited_ast->type) {
            case AST_STRING: {
                printf("%s\n", visited_ast->string_value);
                break;
            }
            default: {
                printf("%p\n", visited_ast);
                break;
            }
        }
    }

    return init_ast(AST_NOOP);
}

/**
 * @brief Initializes and allocates the runtime struct
 * 
 * @param[in] NONE
 * @return parser Returns newly allocated runtime.
 */
runtime_T* init_runtime() {
    runtime_T* runtime = calloc(1, sizeof(struct RUNTIME_STRUCT));

    return runtime;
}

/**
 * @brief Ensures that when the runtime visits a node that the
 *        appropriate action is taken depending on node type.
 * 
 * @param[in] runtime Pointer to the runtime struct.
 * @param[in] node Pointer to the visited node in the AST.
 * @return parser Returns abstract syntax tree node of proper type.
 */
AST_T* runtime_visit(runtime_T* runtime, AST_T* node) {
    switch (node->type) {
        case AST_VARIABLE_DEFINITION: {
            return runtime_visit_var_def(runtime, node);
        }
        case AST_FUNCTION_DEFINITION: {
            return runtime_visit_fn_def(runtime, node);
        }
        case AST_VARIABLE: {
            return runtime_visit_var(runtime, node);
        }
        case AST_FUNCTION_CALL: {
            return runtime_visit_fn_call(runtime, node);
        }
        case AST_STRING: {
            return runtime_visit_string(runtime, node);
        }
        case AST_COMPOUND: {
            return runtime_visit_compound(runtime, node);
        }
        case AST_NOOP: {
            return node;
        }
    }

    printf("Uncaught statement of type `%d`\n", node->type);
    exit(EXIT_FAILURE);

    return init_ast(AST_NOOP);
}

/**
 * @brief Adds the variable definition to global scope
 * 
 * @param[in] runtime Pointer to the runtime struct.
 * @param[in] node Pointer to the visited node in the AST.
 * @return parser Returns abstract syntax tree node of proper type.
 */
AST_T* runtime_visit_var_def(runtime_T* runtime, AST_T* node) {
    scope_add_var_def(
        node->scope,
        node        
    ); 

    return node;
}

/**
 * @brief Adds the function definition to global scope
 * 
 * @param[in] runtime Pointer to the runtime struct.
 * @param[in] node Pointer to the visited node in the AST.
 * @return parser Returns abstract syntax tree node of proper type.
 */
AST_T* runtime_visit_fn_def(runtime_T* runtime, AST_T* node) {
    scope_add_fn_def(
        node->scope,
        node        
    );

    return node;
}

/**
 * @brief Adds the variable name to global scope
 * 
 * @param[in] runtime Pointer to the runtime struct.
 * @param[in] node Pointer to the visited node in the AST.
 * @return parser Returns abstract syntax tree node of proper type.
 */
AST_T* runtime_visit_var(runtime_T* runtime, AST_T* node) {
    AST_T* vdef = scope_get_var_def(
        node->scope,
        node->var_name
    );
    
    if (vdef != NULL) {
        return runtime_visit(runtime, vdef->var_def_value);
    }

    printf("Undefined var `%s`\n", node->var_name);
    exit(EXIT_FAILURE);
}

/**
 * @brief Adds the function name to global scope
 * 
 * @param[in] runtime Pointer to the runtime struct.
 * @param[in] node Pointer to the visited node in the AST.
 * @return parser Returns abstract syntax tree node of proper type.
 */
AST_T* runtime_visit_fn_call(runtime_T* runtime, AST_T* node) {
    if (strcmp(node->fn_call_name, "print") == 0) {
        return builtin_fn_print(runtime, node->fn_call_args, node->fn_call_args_size);
    }

    AST_T* fdef = scope_get_fn_def(
        node->scope,
        node->fn_call_name
    );

    if (fdef == NULL) {
        printf("Undefined method `%s`\n", node->fn_call_name);
        exit(1);
    }

    for (int i = 0; i < (int) node->fn_call_args_size; i++) {
        // grab the var from the fn def args
        AST_T* ast_var = (AST_T*) fdef->fn_def_args[i];

        // grab the value from the fn call args
        AST_T* ast_value = (AST_T*) node->fn_call_args[i];

        // consumee a new var def with the value of the argument
        // in the fn call.
        AST_T* ast_vardef = init_ast(AST_VARIABLE_DEFINITION);
        ast_vardef->var_def_value = ast_value;

        // copy the name from the fn def argument into the new
        // var def
        ast_vardef->var_def_var_name = (char*) calloc(strlen(ast_var->var_name) + 1, sizeof(char));
        strcpy(ast_vardef->var_def_var_name, ast_var->var_name);

        // push our var def into the fn body scope.
        scope_add_var_def(fdef->fn_def_body->scope, ast_vardef);
    }
    
    return runtime_visit(runtime, fdef->fn_def_body);
}

/**
 * @brief Gives abstract syntax tree on of type String.
 * 
 * @param[in] runtime Pointer to the runtime struct.
 * @param[in] node Pointer to the visited node in the AST.
 * @return parser Returns abstract syntax tree node of proper type.
 */
AST_T* runtime_visit_string(runtime_T* runtime, AST_T* node) {
    return node;
}

/**
 * @brief Gives abstract syntax tree on of type Compound.
 * 
 * @param[in] runtime Pointer to the runtime struct.
 * @param[in] node Pointer to the visited node in the AST.
 * @return parser Returns abstract syntax tree node of proper type.
 */
AST_T* runtime_visit_compound(runtime_T* runtime, AST_T* node) {
    for (int i = 0; i < node->compound_size; i++) {
        runtime_visit(runtime, node->compound_value[i]);
    }

    return init_ast(AST_NOOP);
}
