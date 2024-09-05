
#include <stdio.h>
#include <stdlib.h>
#include "include/lexer.h"
#include "include/parser.h"

int main() {
    printf("va_b_c#@;hello world;$");//\"p@a_b_c$\"\n");
    fflush(stdout);
    lexer_T* hello = init_lexer("va_b_c#;hello world;\"");//\n\"p@a_b_c$\"");
    fflush(stdout);
    parser_T* parser = init_parser(hello);
    fflush(stdout);
    AST_T* abstract_syntax_tree = parser_parse(parser);
    printf("Actual Output : %s", abstract_syntax_tree->variable_definition_value->string_value);

    return 0;
}