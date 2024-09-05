#include "include/lexer.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define TRUE 0
#define FALSE 1


lexer_T* init_lexer(char* contents) {
    lexer_T* lexer = calloc(1, sizeof(struct LEXER_STRUCT));
    lexer->contents = contents;
    lexer->i = 0;
    lexer->c = contents[lexer->i]; // Sets c to be the first character in the file
    return lexer;
}

void lexer_advance(lexer_T* lexer) {
    if (lexer->c != '\0' && lexer->i < strlen(lexer->contents)) {
        
        lexer->i += 1; // Increments the i value by 1
        lexer->c = lexer->contents[lexer->i];
    }
}

void lexer_skip_whitespace(lexer_T* lexer) {
    // Spaces are seen as any other characters in this languages.
    while (lexer->c == 10) { // Checks if it's a newline
        lexer_advance(lexer); // Advances the lexer by 1, thereby skipping the whitespace
    }
}

char* lexer_get_current_char_as_string(lexer_T* lexer){
    char * str = calloc(2, sizeof(char));
    str[0] = lexer->c;
    str[1] = '\0';
    return str;
}

token_T* lexer_get_next_token(lexer_T* lexer) {
    int token_type = TOKEN_ID;
    while(lexer->c != '\0' && lexer->i < strlen(lexer->contents)) {
        lexer_skip_whitespace(lexer);

        if(lexer->c == '#'){
            token_type = TOKEN_EQUALS;
        }
        else if (lexer->c == '"'){
            token_type = TOKEN_SEMI;
        }
        else if (lexer->c == '$'){
            token_type = TOKEN_RPAREN;
        }
        else if (lexer->c == '@'){
            token_type = TOKEN_LPAREN;
        }
        else if (lexer->c == ';'){
            return lexer_collect_string(lexer);
        }
        else{
            return lexer_collect_id(lexer);
        }
        
   
        
        
        return lexer_advance_with_token(lexer, init_token(token_type, lexer_get_current_char_as_string(lexer)));

    }
    

    return (void*)0;
}

token_T* lexer_advance_with_token(lexer_T* lexer, token_T* token){
    lexer_advance(lexer);
    return token;
}

token_T* lexer_collect_id(lexer_T* lexer){
    // Variables are one character long unless extended by adding an _
    // Examples: a, a_b, a_b_c

    int var_ext = TRUE;
    // The identifier will always be at least one
    int string_length = 1;
    char * tempC =  &(lexer->contents[lexer->i]);

    // Checks if next character is an _
    
    while (var_ext == TRUE){
        var_ext = FALSE;
        if (lexer->contents[(lexer->i)+1] == '_'){
            // Advances twice to the next character which will be a part of the variable name
            // A character after an _ will always be part of the identifier.
            lexer_advance(lexer);
            lexer_advance(lexer);
            string_length+=2;
            var_ext=TRUE;
        }

    }
    lexer_advance(lexer);
    char * result = calloc((string_length+1), sizeof(char));
    strncpy(result, tempC, string_length);
    result[string_length] = '\0';
    return init_token(TOKEN_ID, result);
}

token_T* lexer_collect_string(lexer_T* lexer){

    lexer_advance(lexer);
    
    char * tempC =  &(lexer->contents[lexer->i]);

    int string_length = 0;
    while (lexer->c != ';'){
        string_length+=1;
        lexer_advance(lexer);
    }
    lexer_advance(lexer);
    char * result = calloc((string_length+1), sizeof(char));
    strncpy(result, tempC, string_length);
    result[string_length] = '\0';
    return init_token(TOKEN_STRING, result);
}

