#include <stdio.h>
#include "include/lexer.h"
#include "include/parser.h"
#include "include/runtime.h"
#include "include/io.h"

/**
 * @brief Print help for running blink interpreter.
 * 
 * @param[in] NONE
 * @return int Returns 0 on successful run. 
 */
void print_help() {
    printf("Usage:\nblink.out <filename>\n");
    exit(1);
}

int main(int argc, char* argv[]) {
    if (argc < 2)
        print_help();

    lexer_T* lexer = init_lexer(
        get_file_contents(argv[1])
    );

    parser_T* parser = init_parser(lexer);
    AST_T* root = parser_parse(parser, parser->scope);
    runtime_T* runtime = init_runtime();
    runtime_visit(runtime, root);

    return 0;
}
