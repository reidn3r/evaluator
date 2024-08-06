#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include "../utils/list.h"

/*PROBLEMA POSSIVELMENTE ESTA NA LINHA 66 ONDE É DECLARADO O CHAR NUM_STR
    CASO DERMOS UM PRINT NO ESPAÇO DE MEMÓRIA DELE, VEREMOS QUE PRA TODA ITERAÇÃO
    O ENDEREÇO DE MEMÓRIA É O MESMO, OU SEJA, ELE ESTÁ MUDANDO CADA NÓ QUE UTILIZOU


 */




// Função para verificar se um caractere é um espaço em branco
bool is_whitespace(char c) {
    return isspace(c);
}

// Função para verificar se um caractere é um dígito
bool is_digit(char c) {
    return isdigit(c);
}

// Função para verificar se um caractere é um operador aritmético
bool is_operator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

// Função para analisar a string e retornar uma lista de tokens
node* string2tokens(char* string) {
    node* tokens = NULL;
    int current_position = 0;
    int length = strlen(string);
    char copy[length];

    while (current_position < length) {
        char* last_elem = lastElem(tokens);
        strcpy(copy, string);
        char* current_char = copy + current_position;
        current_char[1] = '\0';

        if (is_whitespace(current_char[0])) {
            // Ignora espaços em branco e avança para o próximo caractere
            current_position++;
            continue;
        }

        // Um número inteiro pode ser positivo ou negativo
        // Para se reconhecer um número negativo, primeiro verifica-se se o caractere atual é '-'
        // Se for o caso, temos duas possibilidades de ser um número negativo: ser o começo da expressão ou o token anterior ser '+-*/('
        // Para o segundo caso, verifica-se se existem tokens, se o último adicionado foi um caractere, e se pertence a '+-*/(' respectivamente
        if (is_digit(current_char[0]) || (current_char[0] == '-' && ( // TODO: não reconhece números negativos corretamente
                current_position == 0 || 
                (!isEmpty(tokens) && is_operator(last_elem[0]) && strlen(last_elem) > 1) || last_elem[0] == '('))) {
            // Reconhece números inteiros e números negativos
            int start_position = current_position;
            if (current_char[0] == '-') {
                current_position++;
            }

            while (current_position < length && is_digit(string[current_position])) {
                current_position++;
            }

            char num_str[12]; // Buffer para armazenar o número como string (considerando um int de 32 bits)
            // Copia o número da string para o buffer
            strncpy(num_str, string + start_position, current_position - start_position);
            num_str[current_position - start_position] = '\0';
            listAppend(num_str, &tokens); // TODO: atualmente converte pra int, mesmo que a função não seja capaz de receber um int

        } else if (is_operator(current_char[0])) {
            // Reconhece operadores aritméticos
            listAppend(current_char, &tokens);
            current_position++;
        } else if (current_char[0] == '(' || current_char[0] == ')') {
            // Reconhece parênteses
            listAppend(current_char, &tokens);
            current_position++;
        } else {
            // Levanta uma exceção para caracteres inesperados
            fprintf(stderr, "Caractere inesperado: %c\n", current_char[0]);
            exit(EXIT_FAILURE);
        }
    }

    return tokens;
}