#ifndef AST_H
#include <stdlib.h>
#define AST_H
typedef struct AST_STRUCT {
    enum {
        AST_VARIABLE_DEFINITION,
        AST_VARIABLE,
        AST_FUCNTION_CALL,
        AST_STRING,
        AST_COMPOUND
    } type;

    // When variables are defined
    char* variable_definition_variable_name;
    struct AST_STRUCT* variable_definition_value;

    // When variables are used
    char* variable_name;

    // For Functions
    struct AST_STRUCT** function_call_arguments;
    char* function_call_name;
    size_t function_call_arguments_size;

    // For Strings
    char* string_value;

    // For Compound Statements
    struct AST_STRUCT** compound_value;
    size_t compound_size;

    
} AST_T;

AST_T* init_ast(int type);



#endif