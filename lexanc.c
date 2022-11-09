/* lex1.c         14 Feb 01; 31 May 12; 11 Jan 18       */

/* This file contains code stubs for the lexical analyzer.
   Rename this file to be lexanc.c and fill in the stubs.    */

/* Copyright (c) 2018 Gordon S. Novak Jr. and
   The University of Texas at Austin. */

/*
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "token.h"
#include "lexan.h"
#include <stdbool.h>

int CUTOFF_CHAR_COUNT = 14;
double FLOAT_MAX = 3.402823;
double FLOAT_MIN = 1.175495;
int EXP_MAX = 38;

char* RESERVED_WORDS[] = {"array", "begin", "case", "const", "do", "downto", "else", "end", "file", "for", "function", "goto", "if", "label", "nil", "of", "packed", "procedure", "program", "record", "repeat", "set", "then", "to", "type", "until", "var", "while", "with"};

char* DELIMITERS[] = {",", ";", ":", "(", ")", "[", "]", ".."};

char* OPERATORS[] = {"+", "-", "*", "/", ":=", "=", "<>", "<", "<=", ">=", ">", "^", "."};

//need doubles for precision
double exponents[] = {1e0, 1e1, 1e2, 1e3, 1e4, 1e5, 1e6, 1e7, 1e8, 1e9, 1e10,
1e11, 1e12, 1e13, 1e14, 1e15, 1e16, 1e17, 1e18, 1e19, 1e20,
1e21, 1e22, 1e23, 1e24, 1e25, 1e26, 1e27, 1e28, 1e29, 1e30,
1e31, 1e32, 1e33, 1e34, 1e35, 1e36, 1e37, 1e38, 1e39, 1e40,
1e41, 1e42, 1e43, 1e44, 1e45, 1e46, 1e47, 1e48, 1e49, 1e50,
1e51, 1e52, 1e53, 1e54, 1e55, 1e56, 1e57, 1e58, 1e59, 1e60,
1e61, 1e62, 1e63, 1e64, 1e65, 1e66, 1e67};
/* This file will work as given with an input file consisting only
   of integers separated by blanks:
   make lex1
   lex1
   12345 123    345  357
   */

void skip2char () {
    getchar();
    getchar();
}

/* Skip blanks and whitespace.  Expand this function to skip comments too. */
void skipblanks () {

    int count = 0;
    int c;
    while ((c = peekchar()) != EOF && (c == '{' || c == '(' || c == ' ' || c == '\n' || c == '\t')) {
        //printf("c is %c   ", c);
        if ( c == '(' && peek2char() == '*') {
            //printf("entered!");
            getchar();
            int cur = getchar();
            while ( 1 ) {
                cur = getchar();
                if ( (cur == '*' && peekchar() == ')') || (cur == EOF) ) {
                    break;
                }
            }
        } else if ( c == '(') {
            break; //stop here so we don't skip the first parenthesis
        }
        
        if ( c == '{' ) {
            //printf("\nyes.\n");
            int cur = getchar();
            while ( 1 ) {
                cur = getchar();
                //printf("\ncur is %c\n", cur);
                if ( cur == '}' || (cur == EOF)) {
                    //printf("\nYES!!\n");
                    break;
                }
            }
        }
        count++;
        getchar();
    }
    
    
          
}

/* Get identifiers and reserved words */
TOKEN identifier (TOKEN tok) {
    int count = 0; //must not exceed 15
    int next;

    //https://www.cs.utexas.edu/users/novak/cs37517.html
    while ( (count < 15) && ( ((next = peekchar()) != EOF )) && ((next = peekchar()) != '\n')) {
        //printf("\nwe see peekchar as %d\n", peekchar());
        if ( CHARCLASS[next] == ALPHA || CHARCLASS[next] == NUMERIC) {
            //printf("\nhello there\n");
            getchar(); //consume this character and add to the identifier name
            tok->stringval[count] = next;

            //printf("\n setting string to %c \n", next);
            
            if ( count == CUTOFF_CHAR_COUNT ) {
                while ( CHARCLASS[peekchar()] == ALPHA && peekchar() != EOF && peekchar() != '\n' ) {
                    //printf("\nconsuming... we see %d\n", peekchar());
                    getchar(); //consume unused input
                }
                count++;
                break;
                // getchar();
            }
            count++;
        } else {
            break;
        }
    }

    //printf("\nLAST IS %d\n", peekchar());

    tok->tokentype = IDENTIFIERTOK;
    tok->basicdt = STRINGTYPE;
    tok->stringval[count] = 0;

    for(int i = 0; i <= 28; i++) {
        if (strcmp(RESERVED_WORDS[i], tok->stringval) == 0) {
            tok->tokentype = RESERVED;
            tok->whichval = i + 1;
            break;
        }
    }

    return (tok);

}

TOKEN getstring (TOKEN tok) {
    int cur = peekchar();
    if ( cur == '\'') {
        getchar();
    }

    int count = 0;
    int next;
    int next2;
    while ( (count < 15) && ( (next = peekchar()) != EOF ) && ( (next2 = peek2char()) != EOF ) ) {
        //printf("\nnext is %d, next2 is %d\n", next, next2);
        if (next != '\'') {
            //we are in the middle of the string
            //printf("\nadding %c to str\n", next);
            tok->stringval[count] = next;
            getchar();

            //make sure we do not go above 15 chars
            //if the string does not end within 15 chars,
            //we need to consume the rest of the input
            
            if ( count == CUTOFF_CHAR_COUNT) {
                while ( peek2char() != EOF && peekchar() != '\'' && peekchar() != '\'') {
                    getchar(); //consume unused input
                }

                //at the end of the string there should still be an endquote and eof char, skip those
                skip2char();
            }
            count++;

        } else {
            //next char is apostrophe and there is no double apostrophe, string is over
            if (next2 != '\'') {
                //printf("\ndetected that string is over\n");
                getchar();
                count++;
                break;
            } else {
                //printf("\nnext is %c, next2 is %c, detected two apostrophes in a row\n", next, next2);
                //two apostrophes in a row only counts as one apostrophe
                skip2char();
                //add char to stringval array
                tok->stringval[count] = '\'';
                count++;
            }
        }
    }

    tok->tokentype = STRINGTOK;
    tok->basicdt = STRINGTYPE;
    tok->stringval[count] = 0;
    return (tok);

}

TOKEN special (TOKEN tok) {
    int next;
    int count = 0;
    char thing[3];

    while ( (((next = peekchar()) != EOF )) && ((next = peekchar()) != '\n')) {
        int next2 = peek2char();
        //printf("\nwe see peekchar as %d\n", peekchar());

        if (next == ':' && next2 == '=') {
            tok->tokentype = OPERATOR;
            tok->whichval = 5;
            skip2char();
            return tok;
        }

        if (next == '.' && next2 == '.') {
            tok->tokentype = DELIMITER;
            tok->whichval = 8;
            skip2char();
            return tok;
        }



        if ( CHARCLASS[next] == SPECIAL ) {
            //printf("recognizing special...\n");

            thing[0] = next;

            for(int i = 0; i < 8; i++) {
                    if (strcmp(DELIMITERS[i], thing) == 0) {
                        //printf("DELIMITER!!!!!!!!\n");
                        tok->tokentype = DELIMITER;
                        tok->whichval = i + 1;
                        getchar();
                        return tok;
                    }
                }

            for(int i = 0; i < 13; i++) {
                if (strcmp(OPERATORS[i], thing) == 0) {
                    //printf("OPERATOR!!!!!!!!\n");
                    tok->tokentype = OPERATOR;
                    tok->whichval = i + 1;
                    getchar();
                    return tok;
                }
            }

            if (CHARCLASS[next2] == SPECIAL && next2 != '\n') {
                thing[1] = next2;
            }




            int next2 = peek2char();
            if (CHARCLASS[next2] == SPECIAL && next2 != '\n') { //THIS IS A TWO CHARACTER LONG DELIMITER/OPERATOR
                //printf("recognizing 2 special... saw next2 as %d\n", next2);
                thing[0] = next;
                thing[1] = next2;
                thing[2] = 0;


                for(int i = 0; i < 8; i++) {
                    // printf("result of stringcmp is %d\n", strcmp(DELIMITERS[i], tok->stringval));
                    // printf("test 1 delimiter: %s", DELIMITERS[i]);
                    // printf("test 2 stringval: %s", tok->stringval);
                    if (strcmp(DELIMITERS[i], thing) == 0) {
                        //printf("DELIMITER!!!!!!!!\n");
                        tok->tokentype = DELIMITER;
                        tok->whichval = i + 1;
                        skip2char();
                        return tok;
                    }
                }

                for(int i = 0; i < 13; i++) {
                    if (strcmp(OPERATORS[i], thing) == 0) {
                        //printf("OPERATOR!!!!!!!!\n");
                        tok->tokentype = OPERATOR;
                        tok->whichval = i + 1;
                        skip2char();
                        return tok;
                    }
                }
            } 
        } else {
            break;
        }
    }

    // while ( (((next = peekchar()) != EOF )) && ((next = peekchar()) != '\n')) {
    //     printf("\nwe see peekchar as %d\n", peekchar());
    //     if ( CHARCLASS[next] == SPECIAL ) {
    //         printf("recognizing special...\n");
    //         int next2 = peek2char();
    //         if (CHARCLASS[next2] == SPECIAL && next2 != '\n') { //THIS IS A TWO CHARACTER LONG DELIMITER/OPERATOR
    //             printf("recognizing 2 special... saw next2 as %d\n", next2);
    //             thing[0] = next;
    //             thing[1] = next2;
    //             thing[2] = 0;

    //             // printf("THING[0] IS %c", thing[0]);
    //             // printf("THING[1] IS %c", thing[1]);
    //             // printf("THING[2] IS %c", thing[2]);

    //             for(int i = 0; i < 8; i++) {
    //                 // printf("result of stringcmp is %d\n", strcmp(DELIMITERS[i], tok->stringval));
    //                 // printf("test 1 delimiter: %s", DELIMITERS[i]);
    //                 // printf("test 2 stringval: %s", tok->stringval);
    //                 if (strcmp(DELIMITERS[i], thing) == 0) {
    //                     //printf("DELIMITER!!!!!!!!\n");
    //                     tok->tokentype = DELIMITER;
    //                     tok->whichval = i + 1;
    //                     skip2char();
    //                     return tok;
    //                 }
    //             }

    //             for(int i = 0; i < 13; i++) {
    //                 if (strcmp(OPERATORS[i], thing) == 0) {
    //                     //printf("OPERATOR!!!!!!!!\n");
    //                     tok->tokentype = OPERATOR;
    //                     tok->whichval = i + 1;
    //                     skip2char();
    //                     return tok;
    //                 }
    //             }
    //         } else { //THIS IS A ONE CHARACTER LONG DELIMITER/OPERATOR
    //             printf("recognizing 1 special...\n");
    //             thing[0] = next;
    //             thing[1] = 0;
    //             thing[2] = 0;

    //             // printf("THING[0] IS %c", thing[0]);
    //             // printf("THING[1] IS %c", thing[1]);
    //             // printf("THING[2] IS %c", thing[2]);

    //             for(int i = 0; i < 8; i++) {
    //                 // printf("result of stringcmp is %d\n", strcmp(DELIMITERS[i], tok->stringval));
    //                 // printf("test 1 delimiter: %s", DELIMITERS[i]);
    //                 // printf("test 2 stringval: %s", tok->stringval);
    //                 if (strcmp(DELIMITERS[i], thing) == 0) {
    //                     printf("DELIMITER!!!!!!!!\n");
    //                     tok->tokentype = DELIMITER;
    //                     tok->whichval = i + 1;
    //                     getchar();
    //                     getchar();
    //                     return tok;
    //                 }
    //             }

    //             for(int i = 0; i < 13; i++) {
    //                 if (strcmp(OPERATORS[i], thing) == 0) {
    //                     //printf("OPERATOR!!!!!!!!\n");
    //                     tok->tokentype = OPERATOR;
    //                     tok->whichval = i + 1;
    //                     getchar();
    //                     return tok;
    //                 }
    //             }
    //         }
    //     } else {
    //         break;
    //     }
    // }

    return (tok);
}

/* Get and convert unsigned numbers of all types. */
TOKEN number (TOKEN tok)
  { double num;
    int  c, charval;
    num = 0;
    int next;
    int next2;
    long exp = 0;

    bool POSITIVE_E = false;
    bool IS_SCIENTIFIC = false;
    bool IS_REAL_NUMBER = false;
    bool IS_OVERFLOW = false;

    int num_integer_digits = 0;
    int num_fractional_digits = 0;

    while ( (c = peekchar()) != EOF && CHARCLASS[c] == NUMERIC) {
    //while (CHARCLASS[c] == NUMERIC) {
        num_integer_digits++;
        num = num * 10 + (getchar() - '0');
        if (num >= 2147483648) {
            //printf("detected overflow!\n");
            IS_OVERFLOW = true;
        }
        //printf("seeing num as %f\n", num);

        // if (num_integer_digits == 9 && (c = peekchar()) != EOF && CHARCLASS[c] == NUMERIC) {
        //     while (CHARCLASS[c] == NUMERIC) {
        //         getchar();
        //     }
        // }
    }

    //since we have traversed all NUMERIC characters that appear next to each other and the next
    //character is not an e or . , then this must be an integer number
    if ( ((next = peekchar()) != EOF && next != 'e' && next != '.') || 
        ((next = peekchar()) == '.' && (next2 = peek2char()) == '.') ) { //handle special delimiter case (..)
        //printf("WE HAVE DETECTED A MF INTEGER.\n");
        tok->intval = num;
        if (IS_OVERFLOW) {
            printf("Integer number out of range\n");
            tok->intval = 0;
        }
        tok->tokentype = NUMBERTOK;
        tok->basicdt = INTEGER;
        return (tok);
    }

    IS_REAL_NUMBER = true;

    //if ( (next = peekchar()) == EOF && (next2 = peek2char())  

    //potential EOF error
    //CHECK FOR REAL NUMBER
    //if we have read all the way up to a decimal point and the next number is a
    //NUMERIC, then this must be a REAL number and there must be remaining numbers to read
    //printf("seeing next as %c and next2 as %c\n", peekchar(), peek2char());
    next2 = peek2char();
    if ( (next = peekchar()) == '.' && CHARCLASS[next2] == NUMERIC) {
        //printf("entering here.\n");
        getchar(); //skip decimal point
        //printf("peekchar is %c\n", peekchar());
        while ((next = peekchar()) != EOF && CHARCLASS[next] == NUMERIC) {
            num_fractional_digits++;
            //printf("seeing fractional digit %d\n", num_fractional_digits);
            num = num * 10 + (getchar() - '0');
        }
    }


    //CHECK FOR E
    if ( (c = peekchar()) != EOF && (next = peekchar()) == 'e' ) {
        //printf("I am detecting an EEEEEE\n");
        next2 = peek2char();
        IS_SCIENTIFIC = true;
        if (next2 == '+' || CHARCLASS[next2] == NUMERIC) {
            //printf("i'm seeing a positive exponent\n");
            POSITIVE_E = true;
            if (next2 == '+') {
                skip2char();
            } else {
                getchar();
            }
        } else if (next2 == '-') {
            skip2char();
        }

        while ((c = peekchar()) != EOF && CHARCLASS[peekchar()] == NUMERIC) {
            //we need to store the exponent in a separate variable
            exp = exp * 10 + (getchar() - '0');
        }

        //if exponent is not positive, reverse sign
        exp = POSITIVE_E ? exp : (-exp);
    }

    //heyyEYYYYYY!!!!!
    double mantissa = num / exponents[num_fractional_digits];

    //fix da damn mantissa
    //handles special casing for tolerating high numbers of 0
    while (mantissa <= 1) {
        //printf("exeCUTING!!!!!1\n");
        exp--;
        //add additional numbers to the mantissa
        //subtract from exponent to compensate
        mantissa = mantissa * 10;
    }

    //handle special case e+60
    exp += num_integer_digits - 1;
    mantissa = mantissa / exponents[num_integer_digits - 1];

    /*
    { floating point can range from 1.175495E-38 to 3.402823E+38 }  
    { we will assume that at most 8 significant mantissa digits can be carried. }
    */


    if (exp > EXP_MAX || exp < -EXP_MAX) { //exponent too large
        printf("Floating number out of range\n");
    } else if ( (mantissa > FLOAT_MAX && exp >= EXP_MAX) || (mantissa < FLOAT_MIN && exp <= -EXP_MAX)) { //number too large
        printf("Floating number out of range\n");
	} else { //avoid seg fault
        //properly modify the mantissa based on if the exponent is positive or negative
        tok->realval = exp > 0 ? mantissa * exponents[exp] : mantissa / exponents[-exp];
    }

    tok->tokentype = NUMBERTOK;
    tok->basicdt = REAL;
    return (tok);

  }

