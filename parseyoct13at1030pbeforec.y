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
#include <string.h>

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
  statement  :  BEGINBEGIN statement endpart
                                       { $$ = makeprogn($1,cons($2, $3)); }
             |  IF expr THEN statement endif   { $$ = makeif($1, $2, $4, $5); }
             |  REPEAT statement_list UNTIL expr    {$$ = makerepeat($1, $2, $3, $4); }
             |  assignment
             |  funcall
             |  FOR assignment TO expr DO statement { $$ = makefor(1, $1, $2, $3, $4, $5, $6); }
             |  GOTO NUMBER
             |  label
             ;
  statement_list : statement SEMICOLON statement_list   { $$ = cons($1, $3); }
             | statement
             ;
  endpart    :  SEMICOLON statement endpart    { $$ = cons($2, $3); }
             |  END                            { $$ = NULL; }
             ;
  endif      :  ELSE statement                 { $$ = $2; }
             |  /* empty */                    { $$ = NULL; }  %prec thenthen
             ;
  assignment :  variable ASSIGN expr           { $$ = binop($2, $1, $3); }
             ;
  expr       :  expr compare_op simple_expression                 { $$ = binop($2, $1, $3); }
             |  simple_expression 
             ;
  term       :  term times_op factor              { $$ = binop($2, $1, $3); }
             |  factor
             ;
  factor     :  unsigned_constant
             |  variable
             |  funcall
             |  LPAREN expr RPAREN             { $$ = $2; }
             ;
  variable   : IDENTIFIER { $$ = findid($1); }
             ;
  idlist     : IDENTIFIER COMMA idlist { $$ = cons($1, $3); }
             | IDENTIFIER { $$ = cons($1, NULL); }
             ;
  lblock     : cblock
             ;
  cdef       : IDENTIFIER EQ constant { instconst($1, $3); }
             ;
  cdef_list  : cdef SEMICOLON cdef_list
             | cdef SEMICOLON
  cblock     : CONST cdef_list tblock  { $$ = $3; }
             | tblock
  	  	  	 ;
  tblock     : vblock
  	  	     ;
  vblock     : VAR varspecs block { $$ = $3; }
             | block
             ;
  varspecs   : vargroup SEMICOLON varspecs
             | vargroup SEMICOLON
             ;
  vargroup   : idlist COLON type { instvars($1, $3); }
             ;
  type       : IDENTIFIER { $$ = findtype($1); }
             ;
  block      : BEGINBEGIN statement endpart { $$ = makeprogn($1,cons($2, $3)); }
             ;
  funcall    : IDENTIFIER LPAREN expr_list RPAREN  { $$ = makefuncall($2, $1, $3); }
             ;
  expr_list  : expr COMMA expr_list            { $$ = cons($1, $3); }
             | expr 
             ;
  compare_op : EQ | LT | GT | NE | LE | GE | IN
             ;
  simple_expression : sign term                 { $$ = unaryop($1, $2); }
             | term
             | simple_expression plus_op term   { $$ = binop($2, $1, $3); }
             ;
  sign       : PLUS | MINUS
             ;
  plus_op    : PLUS | MINUS | OR
             ;
  times_op   : TIMES | DIVIDE | DIV | MOD | AND
             ;
  label      : NUMBER COLON statement
             ;
  unsigned_constant : NUMBER | NIL | STRING
             ;
  constant   : sign IDENTIFIER          { $$ = unaryop($1, $2); }
             | IDENTIFIER
             | sign NUMBER              { $$ = unaryop($1, $2); }
             | NUMBER
             | STRING
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

/*
TOKEN binop(TOKEN op, TOKEN lhs, TOKEN rhs)        /* reduce binary operator */
  /*{ op->operands = lhs;          /* link operands to operator       */
    //lhs->link = rhs;             /* link second operand to first    */
    //rhs->link = NULL;            /* terminate operand list          */
    /*if (DEBUG & DB_BINOP)
       { printf("binop\n");
         dbugprinttok(op);
         dbugprinttok(lhs);
         dbugprinttok(rhs);
       };
    return op;
  }
*/

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




//******* part 2 methods
/*
	TOKEN findid(TOKEN tok) {
	SYMBOL sym, typ;
	char error_details[1024];
	sym = searchst(tok->stringval);
	if (sym == 0) {
		sprintf(error_details, "Identifier %s not found.\n", tok->stringval);
		yyerror(error_details);
		return tok;
	}
	if (sym->kind == CONSTSYM) {
		if (sym->basicdt == INTEGER) {
			tok->tokentype = NUMBERTOK;
			tok->basicdt = INTEGER;
			tok->intval = sym->constval.intnum;
		} else if (sym->basicdt == REAL) {
			tok->tokentype = NUMBERTOK;
			tok->basicdt = REAL;
			tok->realval = sym->constval.realnum;
		} else if (sym->basicdt == STRINGTYPE) {
			tok->tokentype = STRINGTOK;
			tok->basicdt = STRINGTYPE;
			strcpy(tok->stringval, sym->constval.stringconst);
		} else {
			yyerror("Invalid Const ID");
		}

	} else {

		tok->symentry = sym;
		typ = sym->datatype;
		tok->symtype = typ;
		if (sym->kind == FUNCTIONSYM) {
			tok->basicdt = sym->datatype->basicdt;
		} else if (typ->kind == BASICTYPE || typ->kind == POINTERSYM) {
			tok->basicdt = typ->basicdt;
		}
	}
	return tok;
	
}

void  instconst(TOKEN idtok, TOKEN consttok) {
	SYMBOL sym, typesym;
	TOKEN temptok;
	
	if (consttok->tokentype == OPERATOR) {
		temptok = consttok->operands;
	} else {
		temptok = consttok;
	}
	sym = insertsym(idtok->stringval);
	if (temptok->tokentype == STRINGTOK) {
		typesym = searchst("char");
		strcpy(sym->constval.stringconst, temptok->stringval);
	} else if (temptok->tokentype == NUMBERTOK && temptok->basicdt == REAL) {
		typesym = searchst("real");
		sym->constval.realnum = temptok->realval;
	} else if (temptok->tokentype == NUMBERTOK && temptok->basicdt == INTEGER) {
		typesym = searchst("integer");
		sym->constval.intnum = temptok->intval;
	} else {
		yyerror("Invalid const");
		return;
	}	
	sym->kind = CONSTSYM;
	sym->datatype = typesym;
	sym->basicdt = typesym->basicdt;
}
*/

//add da constant to da symbol table


void  instconst(TOKEN idtok, TOKEN consttok) {
    printf("helllo fron instconst\n");
    SYMBOL sym;
    sym = insertsym(idtok->stringval);
    
    //basic dt is enough and symtype won't matter
    //add the appropriate value
    if (consttok->tokentype == NUMBERTOK) {
        if (consttok->basicdt == INTEGER) {
            sym->constval.intnum = consttok->intval;
            sym->basicdt = INTEGER;
        } else if (consttok->basicdt == REAL) {
            sym->constval.realnum = consttok->realval;
             sym->basicdt = REAL;
        } else if (consttok->basicdt == STRINGTYPE){
            sym->basicdt = STRING;
            strcpy(sym->constval.stringconst, consttok->stringval);
        } else {
            yyerror("fail");
        }
    }
    
    sym->kind = CONSTSYM;
    printf("goodbye from instconst\n");
}


/* old
void  instconst(TOKEN idtok, TOKEN consttok) {
    printf("helllo fron instconst\n");
    SYMBOL sym;
    sym = insertsym(idtok->stringval);
    //basic dt is enough and symtype won't matter
    sym->basicdt = consttok->tokentype;

    //add the appropriate value
    if (consttok->tokentype == NUMBERTOK) {
        if (consttok->basicdt == INTEGER) {
            sym->constval.intnum = consttok->intval;
        } else if (consttok->basicdt == REAL) {
            sym->constval.realnum = consttok->realval;
        } else if (consttok->basicdt == STRINGTYPE){
            strcpy(sym->constval.stringconst, consttok->stringval);
        } else {
            yyerror("fail");
        }
    }
    sym->kind = CONSTSYM;
    printf("goodbye from instconst\n");
}
*/




TOKEN findid(TOKEN tok) { /* the ID token */

    SYMBOL sym = searchst(tok->stringval);

    if ( sym->kind == CONSTSYM ) {
        /* tok->basicdt = sym->basicdt; */
        if (sym->basicdt == INTEGER) {
            tok->intval = sym->constval.intnum;
            tok->tokentype = NUMBERTOK;
            tok->basicdt = INTEGER;
        }
        if (sym->basicdt == REAL) {
            tok->realval = sym->constval.realnum;
            tok->tokentype = NUMBERTOK;
            tok->basicdt = REAL;
        }
        if (sym->basicdt == STRINGTYPE) {
            strcpy(tok->stringval, sym->constval.stringconst);
            tok->tokentype = STRINGTOK;
            tok->basicdt = STRINGTYPE;
        }
    } else {
        tok->symentry = sym;
        SYMBOL typ = sym->datatype;
        tok->symtype = typ;
        if ( typ->kind == BASICTYPE || typ->kind == POINTERSYM) {
            tok->basicdt = typ->basicdt;
        }
    }
    
    return tok; 
}

int op_arithmetic(TOKEN op) {
    int action = op->whichval;
    printf("RETURNING %d\n", (action >= 1 && action <= 4) || (action == DIVOP || action == MODOP));
    return (action >= 1 && action <= 4) || (action == DIVOP || action == MODOP);
}


//return the data type of a token or operator token
int infer_type(TOKEN tok) {
    if (tok->tokentype == IDENTIFIERTOK || tok->tokentype == NUMBERTOK) {
        return tok->basicdt;
    }

    if (tok->tokentype == STRINGTOK) {
        return STRINGTYPE;
    }

    if (tok->tokentype == OPERATOR) {
        if (tok->whichval == FLOATOP) {
            return REAL;
        }
        if (tok->whichval == FUNCALLOP) {
            printf("inferring funcall type as %d\n", tok->operands->basicdt);
            return tok->operands->basicdt;
        }
        if (tok->whichval == FIXOP) {
            return INTEGER;
        }
        return infer_type(tok->operands);
    }

    return -1; //err
}

TOKEN binop(TOKEN op, TOKEN lhs, TOKEN rhs)        /* reduce binary operator */
  { 
    
    int lhs_typ = infer_type(lhs);
    int rhs_typ = infer_type(rhs);

    printf("binop seeing lhs_typ as %d and rhs_typ as %d\n", lhs_typ, rhs_typ);


    //convert to float before performing arithmetic operation
    //if this is an assignment, convert to either float or int depending on what is on lhs
    if ( (lhs_typ == REAL && rhs_typ == INTEGER) ) {
        if (op_arithmetic(op)) {
            rhs = makefloat(rhs);
        }
        if (op->whichval == ASSIGNOP) {
            rhs = makefloat(rhs);
        }
    }
    if ( (lhs_typ == INTEGER && rhs_typ == REAL) ) {
        if (op_arithmetic(op)) {
            lhs = makefloat(lhs); 
        }
        if (op->whichval == ASSIGNOP) {
            rhs = makefix(rhs);
        }
    }
    
    op->operands = lhs;          /* link operands to operator       */
    lhs->link = rhs;             /* link second operand to first    */
    rhs->link = NULL;            /* terminate operand list          */
    if (DEBUG & DB_BINOP)
       { printf("binop\n");
         dbugprinttok(op);
         dbugprinttok(lhs);
         dbugprinttok(rhs);
       };
    return op;
  }



//// makefloat forces the item tok to be floating, by floating a constant
//// or by inserting a FLOATOP operator
//TOKEN makefloat(TOKEN tok) {
//    /* tok->basicdt = REAL;
//    tok->realval = (double) tok->intval;
//    return tok; */
//
//
//    /* tok->basicdt = REAL;
//    tok->realval = (double) tok->intval; */
//    TOKEN floatTok = makeop(FLOATOP);
//    floatTok->basicdt = REAL;
//    floatTok->operands = tok;
//    /* tok->realval = (double) tok->intval;
//    tok->basicdt = REAL; */
//    floatTok->operands->link = NULL;
//
//    return floatTok;
//}
//
//// makefix forces the item tok to be integer, by truncating a constant
//// or by inserting a FIXOP operator
//TOKEN makefix(TOKEN tok) {
//    /* tok->basicdt = INTEGER;
//    tok->intval = (int) tok->realval;
//    return tok; */
//
//    /* tok->basicdt = INTEGER;
//    tok->intval = (int) tok->realval; */
//    TOKEN fixTok = makeop(FIXOP);
//    fixTok->basicdt = INTEGER;
//    fixTok->operands = tok;
//    /* tok->basicdt = INTEGER;
//    tok->intval = (int) tok->realval; */
//    fixTok->operands->link = NULL;
//
//    return fixTok;
//}
//





TOKEN makefloat(TOKEN tok) {
	TOKEN t1;
	if (tok->tokentype == NUMBERTOK && tok->basicdt == INTEGER) {
		printf("executing makefloat 1\n");
        tok->basicdt = REAL;
		tok->realval = tok->intval;
		t1 = tok;
	} else if (tok->tokentype == IDENTIFIERTOK) {
		printf("executing makefloat 2\n");
        t1 = makeop(FLOATOP);
		t1->operands = tok;
	} else {
		printf("executing makefloat 4\n");
        /* t1 = makeop(FLOATOP);
		t1->operands = tok; */
        return tok;
	}
	return t1;
}

//TOKEN makefloat(TOKEN tok) {
//	TOKEN t1;
//	if (tok->tokentype == NUMBERTOK && tok->basicdt == INTEGER) {
//        printf("makefloat executing 1\n");
//		tok->basicdt = REAL;
//		tok->realval = tok->intval;
//		t1 = tok;
//	} else {
//		printf("makefloat executing 2\n");
//        t1 = makeop(FLOATOP);
//		t1->operands = tok;
//
//        
//        /* t1->basicdt = REAL; */
//	}
//	return t1;
//}
/* makefix forces the item tok to be integer, by truncating a constant
   or by inserting a FIXOP operator */
TOKEN makefix(TOKEN tok) {
    printf("HELLO FROM MAKEFIX\n");
	TOKEN t1;
	if (tok->tokentype == NUMBERTOK && tok->basicdt == REAL) {
		printf("makeFIX executing 1\n");
        tok->basicdt = INTEGER;
		tok->intval = tok->realval;
		t1 = tok;
	} else {
		printf("makeFIX executing 2\n");
        t1 = makeop(FIXOP);
		t1->operands = tok;
	}
	return t1;
}


TOKEN unaryop(TOKEN op, TOKEN lhs) {
	op->operands = lhs;          /* link operands to operator       */
	lhs->link = NULL;             /* terminate operand list    */
	if (DEBUG) { 
		printf("unaryop\n");
	    dbugprinttok(op);
	    dbugprinttok(lhs);
	};
	return op;
}


TOKEN makerepeat(TOKEN tok, TOKEN statements, TOKEN tokb, TOKEN expr) {
	int cur_labelnumber = labelnumber;
	TOKEN tok1;
	TOKEN label_tok = makelabel();
	TOKEN goto_tok = makegoto(cur_labelnumber); 
	if (DEBUG) {
		printf("initializing repeat\n");
		dbugprinttok(statements);
		dbugprinttok(expr);
	}
	makeprogn(tok, statements);
	tok1 = makeprogn(talloc(), 0);
	/* tokb has the if condition */
	makeif(tokb, expr, tok1, goto_tok);
	cons(tok, tokb);
	cons(label_tok, tok);
	return makeprogn(talloc(), label_tok);
}

//****** end of part 2 methods










/* makefuncall makes a FUNCALL operator and links it to the fn and args.
   tok is a (now) unused token that is recycled. */

TOKEN makefuncall(TOKEN tok, TOKEN fn, TOKEN args) {
    SYMBOL sym = searchst(fn->stringval);
    if (sym->kind == FUNCTIONSYM) {
        printf("EXECUTING!!!!\n");
        /* tok->basicdt = sym->datatype->basicdt; */
        fn->basicdt = sym->datatype->basicdt;
    }

    tok->tokentype = OPERATOR;
    tok->operands = fn;
    tok->whichval = FUNCALLOP;
    fn->link = args;


    
    if(DEBUG){
        printf("makefuncall\n");
        dbugprinttok(fn);
        dbugprinttok(args);
    }

    /* tok->basicdt = tok->operands->link->basicdt; */
	return tok;
}
/* 
TOKEN makefuncall(TOKEN tok, TOKEN fn, TOKEN args) {
	TOKEN t1 = makeop(FUNCALLOP);
	findid(fn);
	return binop(t1, fn, args);
} */



TOKEN makeop(int opnum){
    TOKEN tok = talloc();
    tok->tokentype = OPERATOR;
    tok->whichval = opnum;
    if (DEBUG) {
      printf("makeop\n");
      dbugprinttok(tok);
    }
    return tok;
}

TOKEN copytok(TOKEN origtok) {
  TOKEN tok = talloc();
  tok->tokentype = origtok->tokentype;
  tok->basicdt = origtok->basicdt;
  tok->link = origtok->link;
  tok->symtype = origtok->symtype;
  tok->symentry = origtok->symentry;
  tok->whichval = origtok->whichval;
  tok->intval = origtok->intval;
  tok->realval = origtok->realval;
  if (DEBUG) {
    printf("copytok\n");
    dbugprinttok(tok);
  }
  return tok;
}


TOKEN makefor(int sign, TOKEN tok, TOKEN assign, TOKEN tokb, TOKEN expr, TOKEN tokc, TOKEN statements) {
    tok = makeprogn(tok, assign);
    TOKEN if_part = talloc();
    TOKEN then_part = talloc();

    //for loop needs to end when i >= expr
    TOKEN less_than_op = makeop(LEOP);

    then_part = makeprogn(then_part, statements);
    if_part = makeif(if_part, less_than_op, then_part, NULL);

    //duplicate i token
    TOKEN i_to_lim = copytok(assign->operands);
    //need 3 tokens, link i to lim, and i := (i + 1) 
    TOKEN set_i = copytok(assign->operands); //for i :=
    TOKEN change_i = copytok(assign->operands); //for (i + 1)

    //link i to lim
    i_to_lim->link = expr;

    //for checking if i <= lim
    less_than_op->operands = i_to_lim;

    //for i :=
    TOKEN set = makeop(ASSIGNOP);

    //for i := i + 1
    TOKEN change = makeop(PLUSOP);

    
    //link if to <=
    if_part->operands = less_than_op;
    less_than_op->link = then_part;

    //create tree for i :=
    set->operands = set_i;
    set_i->link = change;


    //create goto links
    TOKEN l = makelabel();
    assign->link = l;
    TOKEN goto_tok = makegoto(labelnumber - 1);
    set->link = goto_tok;

    //create tree for (i + 1)
    change->operands = change_i;
    change_i->link = makeintc(1);
    
    //link funcall to assignment :=
    statements->link = set;
    l->link = if_part;
    if (DEBUG) {
         printf("makefor\n");
         dbugprinttok(tok);
    }
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


    if (DEBUG)
    { printf("makeprogram\n");
        /* dbugprinttok(tok);
        dbugprinttok(statements); */
    };
    return tok;
}

//creates a label which contains a number that identifies it
TOKEN makelabel() {
    TOKEN l = talloc();
    l->tokentype = OPERATOR;
    l->whichval = LABELOP;

    TOKEN num = makeintc(labelnumber);
    labelnumber++;

    l->operands = num;
    //num->link = NULL; //no more operands
    return l;
}

TOKEN makegoto(int label) {
    TOKEN tok = talloc();
    tok->tokentype = OPERATOR;
    tok->whichval = GOTOOP;
    TOKEN l_tok = makeintc(label);
    //we must assign the goto operator (tok) to the label reference
    tok->operands = l_tok;
    //l_tok->link = NULL; //no more operands
    return tok;
}

TOKEN makeintc(int num) {
    TOKEN tok = talloc();
    tok->basicdt = INTEGER;
    tok->intval = num; //set the value to num
    tok->tokentype = NUMBERTOK;
    return tok;
}

TOKEN findtype(TOKEN tok) {
    //look up type name
    SYMBOL sym = searchst(tok->stringval);
    tok->symtype = sym; //put the result in symtype
    return tok;
}

/* install variables in symbol table */
void instvars(TOKEN idlist, TOKEN typetok) {
    SYMBOL sym, typesym; int align;
    typesym = typetok->symtype;
    align = alignsize(typesym);
    while ( idlist != NULL ) /* for each id */ {
        sym = insertsym(idlist->stringval);
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
