#ifndef UTILS_H_
#define UTILS_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#ifndef MAX_H_
    #define MAX_H_
    #define MAX(a, b) ((a) > (b) ? (a) : (b))
#endif

#ifndef MIN_H_
    #define MIN_H_
    #define MIN(a, b) ((a) < (b) ? (a) : (b))
#endif

#ifndef LOG_H_
    #define LOG_H_
    #define PRINT(...)                             \
            printf("%s:%i: ", __FILE__, __LINE__); \
            printf(__VA_ARGS__);                   \
            printf("\n")
    #define WARN(...)           \
            printf("\033[0;33mWARN:\033[0m");    \
            PRINT(__VA_ARGS__)
    #define RAISE(...)          \
            printf("\033[0;31mERROR:\033[0m");    \
            PRINT(__VA_ARGS__);  \
            exit(1)
#endif

#ifndef bool
    #define bool char
    #define true 1
    #define false 0
#endif

#ifndef UINT_
    #define UINT_
    typedef unsigned int uint;
#endif

// #ifndef STRCON_
    // #define STRCON_
    // ///@brief Retorna se uma string contem um caracter
    // bool strcon(const char *str, char c) {
    //     for (uint i = 0; i < strlen(str); i++) 
    //         if (c == str[i]) return true;

    //     return false;
    // }
// #endif

#endif