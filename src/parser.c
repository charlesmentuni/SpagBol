#include "include/parser.h"
#include <stdio.h>
#include <string.h>

parser_T* init_parser(lexer_T* lexer){
    parser_T* parser = calloc(1, sizeof(struct PARSER_STRUCT));
    parser->lexer = lexer;
    parser->current_token = lexer_get_next_token(parser->lexer);
    return parser;
}

void parser_eat(parser_T* parser, int token_type){
    // Checks that the token is expected and moves to the next one.
    // token_type is the expected token.
    if (parser->current_token->type == token_type){
        parser->current_token = lexer_get_next_token(parser->lexer);
    }
    else{
        printf("Hey buddy, you've got an unexpected token. Fix it. '%s', %d", parser->current_token->value, parser->current_token->type);
        exit(1);
    }
}

AST_T* parser_parse(parser_T* parser){
    return parser_parse_statements(parser);
}

AST_T* parser_parse_statement(parser_T* parser){
    switch(parser->current_token->type){
        case(TOKEN_ID) : return parser_parse_id(parser);
    }

}

AST_T* parser_parse_statements(parser_T* parser){
    printf("yes\n");
    fflush(stdout);

    AST_T* compound = init_ast(AST_COMPOUND); // Sets up am AST for a compound statement
    compound->compound_value = calloc(1, sizeof(struct AST_STRUCT)); 

    // The compound statement will have at least one value, which will be an AST struct
    AST_T* ast_statement = parser_parse_statement(parser); 
    compound->compound_value[0]=ast_statement;

    /*
    int count =0;

    while (parser->current_token->type == TOKEN_SEMI){
        count+=1;
        printf("%d", count);
        fflush(stdout);
        parser_eat(parser, TOKEN_SEMI);
        
        // This can be implemented more effectively
        AST_T* ast_statement = parser_parse_statement(parser);

        compound->compound_size+=1;
        
        compound->compound_value = realloc(compound->compound_value, 
                                            compound->compound_size*sizeof(struct AST_STRUCT));
        

        compound->compound_value[compound->compound_size-1]=ast_statement;
    }*/
    return compound;

}

AST_T* parser_parse_expr(parser_T* parser){
    switch(parser->current_token->type){
        case(TOKEN_STRING): return parser_parse_string(parser);
    }

}

AST_T* parser_parse_factor(parser_T* parser){}

AST_T* parser_parse_term(parser_T* parser){}

AST_T* parser_parse_function_call(parser_T* parser){}

AST_T* parser_parse_variable(parser_T* parser){
    char* variable_name = parser->current_token->value; // Function or variable name
    parser_eat(parser,TOKEN_ID);
    if (parser->current_token->type == TOKEN_LPAREN){
        parser_parse_function_call(parser);
    }
    AST_T* variable = init_ast(AST_VARIABLE);
    variable->variable_name = variable_name; 

    return variable;
}

AST_T* parser_parse_string(parser_T* parser){
    // Sets string value and then eats it. This is defined in the parser current token.
    
    char * string_value = parser->current_token->value;
    parser_eat(parser, TOKEN_STRING);

    AST_T* string = init_ast(AST_STRING);

    string->string_value = string_value;
    printf("\nExpected Output : %s\n", string->string_value);
    fflush(stdout);
    return string;

}

AST_T* parser_parse_variable_definition(parser_T* parser){
    // Eats "v"
    parser_eat(parser, TOKEN_ID);

    char* variable_name = parser->current_token->value;

    // Eats the variable name and equals sign
    parser_eat(parser, TOKEN_ID);
    parser_eat(parser, TOKEN_EQUALS);

    AST_T* variable_value = parser_parse_expr(parser);

    AST_T* full_variable_definition = init_ast(AST_VARIABLE_DEFINITION);
    full_variable_definition->variable_definition_variable_name = variable_name;
    full_variable_definition->variable_definition_value = variable_value;

    return full_variable_definition;

}


AST_T* parser_parse_id(parser_T* parser){
    if(strcmp(parser->current_token->value, "v") == 0){
        return parser_parse_variable_definition(parser);
    }
    else {
        return parser_parse_variable(parser);
    }

}