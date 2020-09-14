#ifndef RUNTIME_H
#define RUNTIME_H
#include "AST.h"

typedef struct RUNTIME_STRUCT
{
} runtime_T;

/**
 * @brief Initializes and allocates the runtime struct
 * 
 * @param[in] NONE
 * @return parser Returns newly allocated runtime.
 */
runtime_T* init_runtime();

/**
 * @brief Ensures that when the runtime visits a node that the
 *        appropriate action is taken depending on node type.
 * 
 * @param[in] runtime Pointer to the runtime struct.
 * @param[in] node Pointer to the visited node in the AST.
 * @return parser Returns abstract syntax tree node of proper type.
 */
AST_T* runtime_visit(runtime_T* runtime, AST_T* node);

/**
 * @brief Adds the variable definition to global scope
 * 
 * @param[in] runtime Pointer to the runtime struct.
 * @param[in] node Pointer to the visited node in the AST.
 * @return parser Returns abstract syntax tree node of proper type.
 */
AST_T* runtime_visit_var_def(runtime_T* runtime, AST_T* node);

/**
 * @brief Adds the function definition to global scope
 * 
 * @param[in] runtime Pointer to the runtime struct.
 * @param[in] node Pointer to the visited node in the AST.
 * @return parser Returns abstract syntax tree node of proper type.
 */
AST_T* runtime_visit_fn_def(runtime_T* runtime, AST_T* node);

/**
 * @brief Adds the variable name to global scope
 * 
 * @param[in] runtime Pointer to the runtime struct.
 * @param[in] node Pointer to the visited node in the AST.
 * @return parser Returns abstract syntax tree node of proper type.
 */
AST_T* runtime_visit_var(runtime_T* runtime, AST_T* node);

/**
 * @brief Adds the function name to global scope
 * 
 * @param[in] runtime Pointer to the runtime struct.
 * @param[in] node Pointer to the visited node in the AST.
 * @return parser Returns abstract syntax tree node of proper type.
 */
AST_T* runtime_visit_fn_call(runtime_T* runtime, AST_T* node);

/**
 * @brief Gives abstract syntax tree on of type String.
 * 
 * @param[in] runtime Pointer to the runtime struct.
 * @param[in] node Pointer to the visited node in the AST.
 * @return parser Returns abstract syntax tree node of proper type.
 */
AST_T* runtime_visit_string(runtime_T* runtime, AST_T* node);

/**
 * @brief Gives abstract syntax tree on of type Compound.
 * 
 * @param[in] runtime Pointer to the runtime struct.
 * @param[in] node Pointer to the visited node in the AST.
 * @return parser Returns abstract syntax tree node of proper type.
 */
AST_T* runtime_visit_compound(runtime_T* runtime, AST_T* node);
#endif
