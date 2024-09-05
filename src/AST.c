#include "include/AST.h"

AST_T* init_ast(int type){
    // When variables are defined
    AST_T* ast = calloc(1, sizeof(AST_T));

    ast->type = type;
    ast->variable_definition_variable_name = (void*)0;
    ast->variable_definition_value= (void*)0;

    // When variables are used
    ast->variable_name = (void*)0;

    // For Functions
    ast->function_call_arguments= (void*)0;
    ast->function_call_name= (void*)0;
    ast->function_call_arguments_size=0;

    // For Strings
    ast->string_value=(void*)0;

    // For Compound Statements
    ast->compound_value=(void*)0;
    ast->compound_size=1;

    return ast;
}