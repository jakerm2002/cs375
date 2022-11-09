%{     /* pars1.y    Pascal Parser      Gordon S. Novak Jr.  ; 08 Jul 22   */

/* Copyright (c) 2022 Gordon S. Novak Jr. and
   The University of Texas at Austin. */

/* 14 Feb 01; 01 Oct 04; 02 Mar 07; 27 Feb 08; 24 Jul 09; 02 Aug 12;
   30 Jul 13; 25 Jul 19 ; 28 Feb 22 */

/*
; This program is free software; you can redistribute it and/or modify
; it under the terms of the GNU General Public License as published by
; the Free Software Foundation; either version 2 of the License, or
; (at your option) any later version.

; This program is distributed in the hope that it will be useful,
; but WITHOUT ANY WARRANTY; without even the implied warranty of
; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
; GNU General Public License for more details.

; You should have received a copy of the GNU General Public License
; along with this program; if not, see <http://www.gnu.org/licenses/>.
  */


/* NOTE:   Copy your lexan.l lexical analyzer to this directory.      */

       /* To use:
                     make pars1y              has 1 shift/reduce conflict
                     pars1y                   execute the parser
                     i:=j .
                     ^D                       control-D to end input

                     pars1y                   execute the parser
                     begin i:=j; if i+j then x:=a+b*c else x:=a*b+c; k:=i end.
                     ^D

                     pars1y                   execute the parser
                     if x+y then if y+z then i:=j else k:=2.
                     ^D

           You may copy pars1.y to be parse.y and extend it for your
           assignment.  Then use   make parser   as above.
        */

        /* Yacc reports 1 shift/reduce conflict, due to the ELSE part of
           the IF statement, but Yacc's default resolves it in the right way.*/

#include <stdio.h>
#include <ctype.h>
#include <assert.h>
#include "token.h"
#include "lexan.h"
#include "symtab.h"
#include "parse.h"
#include "pprint.h"
#include "string.h"

        /* define the type of the Yacc stack element to be TOKEN */

#define YYSTYPE TOKEN

TOKEN parseresult;

%}

/* Order of tokens corresponds to tokendefs.c; do not change */

%token IDENTIFIER STRING NUMBER   /* token types */

%token PLUS MINUS TIMES DIVIDE    /* Operators */
%token ASSIGN EQ NE LT LE GE GT POINT DOT AND OR NOT DIV MOD IN

%token COMMA                      /* Delimiters */
%token SEMICOLON COLON LPAREN RPAREN LBRACKET RBRACKET DOTDOT

%token ARRAY BEGINBEGIN           /* Lex uses BEGIN */
%token CASE CONST DO DOWNTO ELSE END FILEFILE FOR FUNCTION GOTO IF LABEL NIL
%token OF PACKED PROCEDURE PROGRAM RECORD REPEAT SET THEN TO TYPE UNTIL
%token VAR WHILE WITH

%right thenthen ELSE // Same precedence, but "shift" wins.

%%

program : PROGRAM IDENTIFIER LPAREN idlist RPAREN SEMICOLON lblock DOT { parseresult = makeprogram($2, $4, $7); }
             ;
  statement  :  BEGINBEGIN statement endpart   { printf("AAAA!!\n"); $$ = makeprogn($1,cons($2, $3)); }
             |  IF expr THEN statement endif   { printf("AAAAAAAAAAAA!!\n"); $$ = makeif($1, $2, $4, $5); }
             |  FOR {printf("seeing FOR\n");} assignment TO {printf("done with TO.\n");} expr DO {printf("done with DO.\n");} statement	{printf("done with FOR.\n");}{ $$ = makefor(1, $1, $2, $3, $4, $5, $6); printf("hey fucker\n"); }
             |  assignment                     { printf("seeing statement!!\n"); }
             |  funcall                         { printf("funcall done.\n"); }
             ;
  endpart    :  SEMICOLON {printf("saw semicolon\n");} statement endpart    { $$ = cons($2, $3); }
             |  END                            { $$ = NULL; }
             ;
  endif      :  ELSE statement                 { $$ = $2; }
             |  /* empty */                    { $$ = NULL; }  %prec thenthen
             ;
  assignment :  variable ASSIGN expr           { $$ = binop($2, $1, $3); printf("binop done.\n");}
             ;
  expr       :  expr PLUS term                 { $$ = binop($2, $1, $3); }
             |  term 
             ;
  term       :  term TIMES factor              { $$ = binop($2, $1, $3); }
             |  factor
             ;
  factor     :  LPAREN expr RPAREN             { $$ = $2; }
             |  variable
             |  NUMBER
             |  STRING
             ;
  variable   : IDENTIFIER  { $$ = findid($1); }
             ;
  idlist    : IDENTIFIER COMMA idlist { $$ = cons($1, $3); }
             | IDENTIFIER { $$ = cons($1, NULL); }
             ;
  lblock     :  cblock
             ;
  cblock     :  tblock
  	  	  	 ;
  tblock     :  vblock
  	  	     ;
  vblock     : VAR varspecs block { $$ = $3; }
             | block
             ;
  varspecs   : vargroup SEMICOLON varspecs
             | vargroup SEMICOLON
             ;
  vargroup   : idlist COLON type { instvars($1, $3); }
             ;
  type       : simpletype
             ;
  simpletype : IDENTIFIER { $$ = findtype($1); }
             ; /* $1->symtype returns type */
  block      : BEGINBEGIN { printf("seeing block!!\n");} statement { printf("done w statement\n");} endpart { printf("finished block!!\n"); $$ = makeprogn($1,cons($2, $3)); }
             ;
  funcall    : IDENTIFIER {printf("seeting indenfitier in the funcall\n");} LPAREN {printf("lparen funcall\n");} expr_list RPAREN {printf("rparen funcall\n");} {printf("HEY FUCKER\n");}{/*execute function*/}
             ;
  expr_list  : expr COMMA expr_list            { $$ = cons($1, $3); }
             | expr 
             ;
%%

/* You should add your own debugging flags below, and add debugging
   printouts to your programs.

   You will want to change DEBUG to turn off printouts once things
   are working.
  */

#define DEBUG        31             /* set bits here for debugging, 0 = off  */
#define DB_CONS       1             /* bit to trace cons */
#define DB_BINOP      2             /* bit to trace binop */
#define DB_MAKEIF     4             /* bit to trace makeif */
#define DB_MAKEPROGN  8             /* bit to trace makeprogn */
#define DB_PARSERES  16             /* bit to trace parseresult */

 int labelnumber = 0;  /* sequential counter for internal label numbers */

   /*  Note: you should add to the above values and insert debugging
       printouts in your routines similar to those that are shown here.     */

TOKEN cons(TOKEN item, TOKEN list)           /* add item to front of list */
  { item->link = list;
    if (DEBUG & DB_CONS)
       { printf("cons\n");
         dbugprinttok(item);
         dbugprinttok(list);
       };
    return item;
  }

TOKEN binop(TOKEN op, TOKEN lhs, TOKEN rhs)        /* reduce binary operator */
  { op->operands = lhs;          /* link operands to operator       */
    printf("lhs is %x\n", lhs->intval);
    lhs->link = rhs;             /* link second operand to first    */
    rhs->link = NULL;            /* terminate operand list          */
    if (DEBUG & DB_BINOP)
       { printf("binop\n");
         dbugprinttok(op);
         dbugprinttok(lhs);
         dbugprinttok(rhs);
       };
    printf("op->operands is %x\n", op->operands->intval);
    printf("binop returning token with address %p\n", &op);
    return op;
  }

TOKEN makeif(TOKEN tok, TOKEN exp, TOKEN thenpart, TOKEN elsepart)
  {  tok->tokentype = OPERATOR;  /* Make it look like an operator   */
     tok->whichval = IFOP;
     if (elsepart != NULL) elsepart->link = NULL;
     thenpart->link = elsepart;
     exp->link = thenpart;
     tok->operands = exp;
     if (DEBUG & DB_MAKEIF)
        { printf("makeif\n");
          dbugprinttok(tok);
          dbugprinttok(exp);
          dbugprinttok(thenpart);
          dbugprinttok(elsepart);
        };
     return tok;
   }

TOKEN makeprogn(TOKEN tok, TOKEN statements)
  {  tok->tokentype = OPERATOR;
     tok->whichval = PROGNOP;
     tok->operands = statements;
     if (DEBUG & DB_MAKEPROGN)
       { printf("makeprogn\n");
         dbugprinttok(tok);
         dbugprinttok(statements);
       };
     return tok;
   }







//FUUUUUUCKKKKKKKK
TOKEN makeop(int opnum) {
	TOKEN tok = talloc();
	tok->tokentype = OPERATOR;
	tok->whichval = opnum;
	return tok;
}
TOKEN copytok(TOKEN origtok) {
	TOKEN tok = talloc();
    printf("fuck\n");
	memcpy(tok, origtok, sizeof(struct tokn));
    printf("fucking done!!!\n");
	return tok;
}
TOKEN fillintc(TOKEN tok, int num) {
	tok->tokentype = NUMBERTOK;
	tok->intval = num;
	tok->basicdt = INTEGER;
	return tok;
}

TOKEN makefor(int sign, TOKEN tok, TOKEN asg, TOKEN tokb, TOKEN endexpr,
              TOKEN tokc, TOKEN statement) {
    //printf("hello from makefor\n");
    int cur_labelnumber = labelnumber;
	TOKEN label_tok = makelabel();
	TOKEN goto_tok = makegoto(cur_labelnumber); 
	/* copy assignment operator for use in multiple situations */
   // printf("hello from makefor 1.5\n");
   // printf("%p ops\n", &asg);
   // printf("%p value of asg\n", asg);
	TOKEN assign_var = copytok(asg->operands);
    printf("finished with makefor\n");
    return assign_var;  
}
//FUCUKKKKKSADJASNAOJBFDJFN







//creates a label which contains a number that identifies it
TOKEN makelabel() {
    TOKEN l = talloc();
    l->tokentype = OPERATOR;
    l->whichval = LABELOP;

    //int labelnumber defined 147
    TOKEN num = makeintc(labelnumber);
    labelnumber++;

    l->operands = num;
    num->link = NULL; //no more operands
    return l;
}

TOKEN makegoto(int label) {
    TOKEN tok = talloc();
    tok->tokentype = OPERATOR;
    tok->whichval = GOTOOP;
    TOKEN l_tok = makeintc(label);
    //we must assign the goto operator (tok) to the label reference
    tok->operands = l_tok;
    l_tok->link = NULL; //no more operands
    return tok;
}

/* makes a new integer number token with num as its value */
TOKEN makeintc(int num) {
    TOKEN tok = talloc();
    tok->basicdt = INTEGER;
    tok->intval = num; //set the value to num
    tok->tokentype = NUMBERTOK;
    return tok;
}

TOKEN makeprogram(TOKEN name, TOKEN args, TOKEN statements) {

    //token for program
    TOKEN tok = talloc();
    tok->tokentype = OPERATOR;
    tok->whichval = PROGRAMOP;
    tok->operands = name;

    //need graph1 to point to a progn
    TOKEN progn_tok = makeprogn(talloc(), args);
    
    //make graph1 token point to progn token
    name->link = progn_tok;

    //need to link progn to statements
    progn_tok->link = statements;

    printf("makeprogram\n");


    /* if (DEBUG & DB_MAKEPROGN)
    { printf("makeprogn\n");
        dbugprinttok(tok);
        dbugprinttok(statements);
    }; */
    return tok;
}

TOKEN findtype(TOKEN tok) {
    //look up type name
    SYMBOL sym = searchst(tok->stringval);
    tok->symentry = sym;
    printf("findtype\n");
    tok->symtype = sym; //put the result in symtype
    return tok;
}

TOKEN findid(TOKEN tok) {
    /* the ID token */
    SYMBOL sym = searchst(tok->stringval);
    tok->symentry = sym;
    SYMBOL typ = sym->datatype;
    tok->symtype = typ;
    if ( typ->kind == BASICTYPE ||
    typ->kind == POINTERSYM)
    tok->basicdt = typ->basicdt;
    return tok; 
}

void instvars(TOKEN idlist, TOKEN typetok) {
    SYMBOL sym, typesym; int align;
    typesym = typetok->symtype;
    align = alignsize(typesym);
    while ( idlist != NULL ) /* for each id */
    { sym = insertsym(idlist->stringval);
    sym->kind = VARSYM;
    sym->offset = /* "next" */
    wordaddress(blockoffs[blocknumber],
    align);
    sym->size = typesym->size;
    blockoffs[blocknumber] = /* "next" */
    sym->offset + sym->size;
    sym->datatype = typesym;
    sym->basicdt = typesym->basicdt;
    idlist = idlist->link;
    };
}

int wordaddress(int n, int wordsize)
  { return ((n + wordsize - 1) / wordsize) * wordsize; }
 
void yyerror (char const *s)
{
  fprintf (stderr, "%s\n", s);
}

int main(void)          /*  */
  { int res;
    initsyms();
    res = yyparse();
    printst();       /* to shorten, change to:  printstlevel(1);  */
    printf("yyparse result = %8d\n", res);
    if (DEBUG & DB_PARSERES) dbugprinttok(parseresult);
    ppexpr(parseresult);           /* Pretty-print the result tree */
    /* uncomment following to call code generator. */
     /* 
    gencode(parseresult, blockoffs[blocknumber], labelnumber);
 */
  }
