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
#include "codegen.h"

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
  statement  :  BEGINBEGIN statement endpart                                    { $$ = makeprogn($1,cons($2, $3)); }
             |  IF expr THEN statement endif                                    { $$ = makeif($1, $2, $4, $5); }
             |  REPEAT statement_list UNTIL expr                                {$$ = makerepeat($1, $2, $3, $4); }
             |  assignment
             |  funcall
             |  FOR assignment TO expr DO statement                             { $$ = makefor(1, $1, $2, $3, $4, $5, $6); }
             |  WHILE expr DO statement                                         { $$ = makewhile($1, $2, $3, $4); }
             |  GOTO NUMBER                                                     { $$ = dogoto($1, $2); }
             |  label
             ;
  statement_list : statement SEMICOLON statement_list                           { $$ = cons($1, $3); }
             | statement
             ;
  endpart    :  SEMICOLON statement endpart                                     { $$ = cons($2, $3); }
             |  END                                                             { $$ = NULL; }
             ;
  endif      :  ELSE statement                                                  { $$ = $2; }
             |  /* empty */                                                     { $$ = NULL; }  %prec thenthen
             ;
  assignment :  variable ASSIGN expr                                            { $$ = binop($2, $1, $3); }
             ;
  expr       :  expr compare_op simple_expression                               { $$ = binop($2, $1, $3); }
             |  simple_expression 
             ;
  term       :  term times_op factor                                            { $$ = binop($2, $1, $3); }
             |  factor
             ;
  factor     :  unsigned_constant
             |  variable
             |  funcall
             |  LPAREN expr RPAREN                                              { $$ = $2; }
             |  NOT factor                                                      { $$ = unaryop($1, $2); }
             ;
  variable   : IDENTIFIER                                                       { $$ = findid($1); }
             |  variable LBRACKET expr_list RBRACKET                            { $$ = arrayref($1, $2, $3, $4); }
             |  variable DOT IDENTIFIER                                         { $$ = reducedot($1, $2, $3); }
             |  variable POINT                                                  { $$ = dopoint($1, $2); }
             ;
             ;
  idlist     : IDENTIFIER COMMA idlist                                          { $$ = cons($1, $3); }
             | IDENTIFIER                                                       { $$ = cons($1, NULL); }
             ;
  numlist    : NUMBER COMMA numlist                                             { instlabel($1); }
             | NUMBER                                                           { instlabel($1); }
             ;
  lblock     : LABEL numlist SEMICOLON cblock                                   { $$ = $4; }
             | cblock
             ;
  cdef       : IDENTIFIER EQ constant                                           { instconst($1, $3); }
             ;
  cdef_list  : cdef SEMICOLON cdef_list
             | cdef SEMICOLON
  cblock     : CONST cdef_list tblock                                           { $$ = $3; }
             | tblock
  	  	  	 ;
  tdef       : IDENTIFIER EQ type                                               { insttype($1, $3); }
             ;
  tdef_list  : tdef SEMICOLON tdef_list 
             | tdef SEMICOLON     
  tblock     : TYPE tdef_list vblock                                            { $$ = $3; }
             | vblock
  	  	     ;
  vdef       : idlist COLON type                                                { instvars($1, $3); }
             ;
  vdef_list  : vdef SEMICOLON vdef_list
             | vdef SEMICOLON
             ;
  vblock     : VAR vdef_list block                                              { $$ = $3; }
             | block
             ;
  simple_type: IDENTIFIER                                                       { $$ = findtype($1); }
             | LPAREN idlist RPAREN                                             { $$ = instenum($2); }
             | constant DOTDOT constant                                         { $$ = instdotdot($1, $2, $3);}
             ;
  simple_type_list : simple_type COMMA simple_type_list                         { $$ = cons($1, $3); }
		     | simple_type                                                      { $$ = cons($1, NULL); }
		     ;
  type       : simple_type
             | ARRAY LBRACKET simple_type_list RBRACKET OF type		            { $$ = instarray($3, $6); }
             | RECORD field_list END                                            { $$ = instrec($1, $2); }
             | POINT IDENTIFIER                                                 { $$ = instpoint($1, $2); }
             ;
  fields     : idlist COLON type                                                { $$ = instfields($1, $3); }
             ;
  field_list : fields SEMICOLON field_list                                      { $$ = nconc($1, $3); }
             | fields                      
             ;
  block      : BEGINBEGIN statement endpart                                     { $$ = makeprogn($1,cons($2, $3)); }
             ;
  funcall    : IDENTIFIER LPAREN expr_list RPAREN                               { $$ = makefuncall($2, $1, $3); }
             ;
  expr_list  : expr COMMA expr_list                                             { $$ = cons($1, $3); }
             | expr 
             ;
  compare_op : EQ | LT | GT | NE | LE | GE | IN
             ;
  simple_expression : sign term                                                 { $$ = unaryop($1, $2); }
             | term
             | simple_expression plus_op term                                   { $$ = binop($2, $1, $3); }
             ;
  sign       : PLUS | MINUS
             ;
  plus_op    : PLUS | MINUS | OR
             ;
  times_op   : TIMES | DIVIDE | DIV | MOD | AND
             ;
  label      : NUMBER COLON statement                                           { $$ = dolabel($1, $2, $3); }
             ;
  unsigned_constant : NUMBER 
             | NIL                                                              { $$ = makeintc(0); } 
             | STRING
             ;
  constant   : sign IDENTIFIER                                                  { $$ = unaryop($1, $2); }
             | IDENTIFIER
             | sign NUMBER                                                      { $$ = unaryop($1, $2); }
             | NUMBER
             | STRING
             ;

%%

/* You should add your own debugging flags below, and add debugging
   printouts to your programs.

   You will want to change DEBUG to turn off printouts once things
   are working.
  */

#define DEBUG         32             /* set bits here for debugging, 0 = off  */
#define DB_CONS       1             /* bit to trace cons */
#define DB_BINOP      2             /* bit to trace binop */
#define DB_MAKEIF     4             /* bit to trace makeif */
#define DB_MAKEPROGN  8             /* bit to trace makeprogn */
#define DB_PARSERES  16             /* bit to trace parseresult */

 int labelnumber = 0;  /* sequential counter for internal label numbers */

 int labels[100];

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


void  instconst(TOKEN idtok, TOKEN consttok) {
    SYMBOL sym, type;
    TOKEN tokToCopy;

    if (consttok->tokentype == OPERATOR) {
		tokToCopy = consttok->operands;
	} else {
		tokToCopy = consttok;
	}
    //add in symtype
    sym = insertsym(idtok->stringval);
    if (tokToCopy->tokentype == NUMBERTOK) {
        if (tokToCopy->basicdt == INTEGER) {
            sym->basicdt = INTEGER;
            type = searchst("integer");
            sym->constval.intnum = tokToCopy->intval;
        } else if (tokToCopy->basicdt == REAL) {
            sym->basicdt = REAL;
            type = searchst("real");
            sym->constval.realnum = tokToCopy->realval;
        } else {
            yyerror("fail");
        }
    } else if (tokToCopy->tokentype == STRINGTOK) {
        type = searchst("char");
        sym->basicdt = STRING;
        strcpy(sym->constval.stringconst, tokToCopy->stringval);
    }

    sym->datatype = type;
    sym->kind = CONSTSYM;
}

//return the data type of a token or operator token
int infer_type(TOKEN tok) {
    if (tok->tokentype == IDENTIFIERTOK || tok->tokentype == NUMBERTOK) {
        return tok->basicdt;
    } else if (tok->tokentype == STRINGTOK) {
        return STRINGTYPE;
    } else if (tok->tokentype == OPERATOR) {
        if (tok->whichval == FLOATOP) {
            return REAL;
        } else if (tok->whichval == FUNCALLOP) {
            printf("inferring funcall type as %d\n", tok->operands->basicdt);
            return tok->operands->basicdt;
        } else if (tok->whichval == FIXOP) {
            return INTEGER;
        }
        return infer_type(tok->operands);
    }

    return -1;
}

int check_op_simple(TOKEN op) {
    int action = op->whichval;
    return (action >= 1 && action <= 4) || (action == DIVOP || action == MODOP);
}


TOKEN findid(TOKEN tok) { 
    SYMBOL sym = searchst(tok->stringval);

    if ( sym->kind == CONSTSYM ) {
        tok->basicdt = sym->basicdt;
        if (sym->basicdt == STRINGTYPE) {
            strcpy(tok->stringval, sym->constval.stringconst);
            tok->tokentype = STRINGTOK;
        } else if (sym->basicdt == REAL) {
            tok->tokentype = NUMBERTOK;
            tok->realval = sym->constval.realnum;
        } else if (sym->basicdt == INTEGER) {
            tok->intval = sym->constval.intnum;
            tok->tokentype = NUMBERTOK;
        }
    } else {
        tok->symentry = sym;
        tok->basicdt = sym->datatype->basicdt;
        tok->symtype = sym->datatype;
    }
    return tok; 
}


TOKEN binop(TOKEN op, TOKEN lhs, TOKEN rhs)        /* reduce binary operator */
  { 
    
    int typ_lhs = infer_type(lhs);
    int typ_rhs = infer_type(rhs);

    if ( (typ_lhs == REAL && typ_rhs == INTEGER) ) {
        if (check_op_simple(op)) {
            rhs = makefloat(rhs);
        }
        if (op->whichval == ASSIGNOP) {
            rhs = makefloat(rhs);
        }
    }
    if ( (typ_lhs == INTEGER && typ_rhs == REAL) ) {
        if (check_op_simple(op)) {
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


TOKEN makefloat(TOKEN tok) {
	if (tok->tokentype == NUMBERTOK && tok->basicdt == INTEGER) {
        tok->basicdt = REAL;
		tok->realval = tok->intval;
		return tok;
	} else if (tok->tokentype == IDENTIFIERTOK) {
        TOKEN floatTok = makeop(FLOATOP);
		floatTok->operands = tok;
        return floatTok;
	} else {
        return tok;
	}
	return tok;
}

/* makefix forces the item tok to be integer, by truncating a constant
   or by inserting a FIXOP operator */
TOKEN makefix(TOKEN tok) {
	if (tok->tokentype == NUMBERTOK && tok->basicdt == REAL) {
        tok->basicdt = INTEGER;
		tok->intval = tok->realval;
		return tok;
	} else {
        TOKEN fixTok = makeop(FIXOP);
		fixTok->operands = tok;
        return fixTok;
	}
	return tok;
}


TOKEN unaryop(TOKEN op, TOKEN lhs) {
	op->operands = lhs;
	lhs->link = NULL;
	if (DEBUG) { 
		printf("unaryop\n");
	    dbugprinttok(op);
	    dbugprinttok(lhs);
	};
	return op;
}


TOKEN makerepeat(TOKEN tok, TOKEN statements, TOKEN tokb, TOKEN expr) {
	makeprogn(tok, statements);
	TOKEN repeatTok = makeprogn(talloc(), 0);
    TOKEN goto_tok = makegoto(labelnumber); 
	makeif(tokb, expr, repeatTok, goto_tok);
    TOKEN l_tok = makelabel();
	l_tok->link = tok;
    tok->link = tokb;
	return makeprogn(talloc(), l_tok);
}


// concatenate two token lists
TOKEN nconc(TOKEN lista, TOKEN listb) {
    TOKEN newList = lista;
    if (lista==NULL)
    return lista;
    else {
        while(newList->link) {
            newList = newList->link;
        }
        newList->link = listb;
    }

    if (DEBUG) {
        printf("nconc\n");
    }
    return newList;
}

// action for the goto
TOKEN dogoto(TOKEN tok, TOKEN labeltok) {
    int currentLabelNumber;
    int i = 0;
    while (i < labelnumber) {
      if (labels[i] == labeltok->intval) {
        currentLabelNumber = i; 
      }
      i++;
    }
    tok = makegoto(currentLabelNumber);
    if (DEBUG) {
      printf("hello from dogoto\n");
    }
    return tok;
}

// action for label
// basically the same as goto
TOKEN dolabel(TOKEN labeltok, TOKEN tok, TOKEN statement) {
    int i = 0;
    int currentLabelNumber;
    while (i < labelnumber) {
      if (labels[i] == labeltok->intval) {
        currentLabelNumber = i; 
      }
      i++;
    }
    TOKEN intTok = makeintc(currentLabelNumber);
    labeltok = makeop(LABELOP);
    labeltok->operands = intTok;
    labeltok->link = statement;
    tok = makeprogn(tok, labeltok);
    if (DEBUG) {
      printf("dolabel\n");
    }
    return tok;
}

/* instlabel installs a user label into the label table */
void instlabel (TOKEN num) {
    labels[labelnumber++] = num->intval;  
}

// while statement structure
TOKEN makewhile(TOKEN tok, TOKEN expr, TOKEN tokb, TOKEN statement) {
    if (tok != NULL) {
        TOKEN label = makelabel();
        
        tok = makeprogn(tok, label);
        int currentlabel = labelnumber - 1;
        TOKEN gototok = makegoto(currentlabel);
        statement->link = gototok;
        TOKEN bodytok = makeprogn(tokb, statement);

        TOKEN iftok = talloc();
        iftok = makeif(iftok, expr, bodytok, NULL);
        label->link = iftok;
        if (DEBUG) {
            printf("makewhile\n");
            dbugprinttok(tok);
        }
        return tok;
    }
    return NULL;
}

/* makesubrange makes a SUBRANGE symbol table entry, puts the pointer to it
   into tok, and returns tok. */
TOKEN makesubrange(TOKEN tok, int low, int high) {
    if (tok != NULL) {
        SYMBOL subrangeSymbol = symalloc();
        subrangeSymbol->lowbound = low;
        subrangeSymbol->highbound = high;
        subrangeSymbol->kind = SUBRANGE;
        subrangeSymbol->size = basicsizes[INTEGER];
        subrangeSymbol->basicdt = INTEGER;
        tok->symtype = subrangeSymbol;
        return tok;
    }
    if (DEBUG) {
        printf("makesubrange\n");
    }
}

/* instenum installs an enumerated subrange in the symbol table,
   e.g., type color = (red, white, blue)
   by calling makesubrange and returning the token it returns. */
TOKEN instenum(TOKEN idlist) {
    int size = 0;
    TOKEN arr = copytok(idlist);
    for (int i = 0; arr; i++) {
        instconst(arr, makeintc(size));
        arr = arr->link;
        size++;
    }
    TOKEN tok = makesubrange(idlist, 0, size - 1);
    if (DEBUG){
        printf("instenum\n");
    }
    return tok;
}

/* instdotdot installs a .. subrange in the symbol table.
   dottok is a (now) unused token that is recycled. */
TOKEN instdotdot(TOKEN lowtok, TOKEN dottok, TOKEN hightok) {
    int highBound = hightok->intval;
    int lowBound = lowtok->intval;
    return makesubrange(dottok, lowBound, highBound);
}

/* insttype will install a type name in symbol table.
   typetok is a token containing symbol table pointers. */
void  insttype(TOKEN typename, TOKEN typetok) {
    SYMBOL typeSymbol = searchins(typename->stringval);
    typeSymbol->kind = TYPESYM;
    typeSymbol->size = typetok->symtype->size;
    typeSymbol->datatype = typetok->symtype;
    if (DEBUG) {
        printf("insttype\n");
    }
}

/* instpoint will install a pointer type in symbol table */
TOKEN instpoint(TOKEN tok, TOKEN typename) {
    if (tok != NULL) {
        SYMBOL typeSymbol = searchins(typename->stringval);
        SYMBOL pointerSymbol = symalloc();
        pointerSymbol->size = basicsizes[POINTER];
        pointerSymbol->basicdt = POINTER;
        pointerSymbol->datatype = typeSymbol;
        pointerSymbol->kind = POINTERSYM;
        tok->symtype = pointerSymbol;
    } else {
        return NULL;
    }
    if (DEBUG) {
        printf("instpoint\n");
        dbugprinttok(tok);
    }
    return tok;
}

/* instrec will install a record definition.  Each token in the linked list
   argstok has a pointer its type.  rectok is just a trash token to be
   used to return the result in its symtype */
TOKEN instrec(TOKEN rectok, TOKEN argstok) {
    SYMBOL recordSymbol = symalloc();
    int count = 0; 
    int next = 0;
    int align;
    recordSymbol->kind = RECORDSYM;
    SYMBOL prev = NULL;
    for (int i = 0; argstok; i++){
        align = alignsize(argstok->symtype);
        SYMBOL currentRecordField = makesym(argstok->stringval);
        currentRecordField->datatype = argstok->symtype;
        currentRecordField->size = currentRecordField->datatype->size;
        currentRecordField->offset = wordaddress(next, align);
        next = currentRecordField->offset + currentRecordField->size;
        if (count == 0) {
            recordSymbol->datatype = currentRecordField;
            prev = currentRecordField;
        } else {
            prev->link = currentRecordField;
            prev = currentRecordField;
        }
        count++;
        argstok = argstok->link;
        currentRecordField->link = NULL;
    }
    recordSymbol->size = wordaddress(next, 16); 
    rectok->symtype = recordSymbol;
    if (DEBUG) {
        printf("instrect\n");
    }
    return rectok;
}

/* instfields will install type in a list idlist of field name tokens:
   re, im: real    put the pointer to REAL in the RE, IM tokens.
   typetok is a token whose symtype is a symbol table pointer.
   Note that nconc() can be used to combine these lists after instrec() */
TOKEN instfields(TOKEN idlist, TOKEN typetok) {
    TOKEN tok = idlist;
    SYMBOL typeSymbol = typetok->symtype;
    for (int i = 0; tok; i++) {
        tok->symtype = typeSymbol;     
        tok = tok->link;
    }
    if (DEBUG) {
        printf("instfields\n");
    }
    return idlist;
}

/* makearef makes an array reference operation.
   off is be an integer constant token
   tok (if not NULL) is a (now) unused token that is recycled. */
TOKEN makearef(TOKEN var, TOKEN off, TOKEN tok) {
     int flag = 0;
    if (tok != NULL) { 
        if (var->whichval == AREFOP) {
            TOKEN plusToken = makeop(PLUSOP);
            TOKEN temp = var->operands->link;
            temp->link = off;
            plusToken->operands = temp;
            var->operands->link = plusToken;
            var->basicdt = var->symentry->basicdt;
            return var;
        }
    } 
    TOKEN arefToken = makeop(AREFOP);
    var->link = off;
    arefToken->operands = var;
    arefToken->symentry = var->symentry; 
    arefToken->basicdt = arefToken->symentry->basicdt; 
    if (DEBUG) {
        printf("makearef\n");
    }
    return arefToken;
}

/* reducedot handles a record reference.
   dot is a (now) unused token that is recycled. */
TOKEN reducedot(TOKEN var, TOKEN dot, TOKEN field) {
    SYMBOL record = var->symentry;
    SYMBOL currentRecordField = record->datatype->datatype;
    int offset = 0;
    while(currentRecordField) {
        if (strcmp(currentRecordField->namestring, field->stringval) == 0) {
            offset = currentRecordField->offset;
            var->symentry = currentRecordField;
            break;
        } else {
            currentRecordField = currentRecordField->link;
        }
    }
    dot = makearef(var, makeintc(offset), dot);
    if (DEBUG) {
        printf("reducedot\n");
    }
    return dot;
}

/* arrayref processes an array reference a[i]
   subs is a list of subscript expressions.
   tok and tokb are (now) unused tokens that are recycled. */
TOKEN arrayref(TOKEN arr, TOKEN tok, TOKEN subs, TOKEN tokb) {
    if (subs->link) {
    TOKEN timesop = makeop(TIMESOP);
    int low = arr->symtype->lowbound;
    int high = arr->symtype->highbound;
    int size = (arr->symtype->size / (high - low + 1));

    TOKEN s = copytok(subs);
    s->link = NULL;
    TOKEN elesize = makeintc(size);
    elesize->link = s;
    timesop->operands = elesize;

    TOKEN nsize = makeintc(-1 * size * low);
    nsize->link = timesop;
    TOKEN plusop = makeop(PLUSOP);
    plusop->operands = nsize;

    TOKEN subarref = makearef(arr, plusop, tokb);
    
    subarref->symtype = arr->symtype->datatype;
    if (DEBUG) {
        printf("arrayref\n");
        printf("multiple : %d, %d, %d, %d\n", size, low, size * low, size * low * -1);
        printf("low : %d, high : %d, total size : %d, size of ele %d", low, high, arr->symtype->size, size);
        dbugprinttok(arr);
        dbugprinttok(subs);
       // dbugprinttok(plusop);
    }
    return arrayref(subarref, tok, subs->link, tokb);
  } else {
    TOKEN timesop = makeop(TIMESOP);
    int low = arr->symtype->lowbound;
    int high = arr->symtype->highbound;
    int size = (arr->symtype->size / (high - low + 1));

    TOKEN elesize = makeintc(size);
    elesize->link = subs;
    timesop->operands = elesize;

    TOKEN nsize = makeintc(-1 * size * low);
    nsize->link = timesop;
    TOKEN plusop = makeop(PLUSOP);
    plusop->operands = nsize;


    if (DEBUG) {
        printf("arrayref base\n");
        printf("low : %d, high : %d, total size : %d, size of ele %d", low, high, arr->symtype->size, size);
        dbugprinttok(arr);
        dbugprinttok(subs);
        dbugprinttok(plusop);
    }
    return makearef(arr, plusop, tokb);
  }
}

/* dopoint handles a ^ operator.  john^ becomes (^ john) with type record
   tok is a (now) unused token that is recycled. */
TOKEN dopoint(TOKEN var, TOKEN tok) {
    tok->operands = var;
    tok->symentry = var->symentry->datatype->datatype;
    if (DEBUG) {
        printf("dopoint\n");
    }
    return tok;
}

/* instarray installs an array declaration into the symbol table.
   bounds points to a SUBRANGE symbol table entry.
   The symbol table pointer is returned in token typetok. */
TOKEN instarray(TOKEN bounds, TOKEN typetok) {
    if (bounds->link) {
        typetok = instarray(bounds->link, typetok);
    }
    SYMBOL symbolSubRange = bounds->symtype;
    SYMBOL typeSymbol = typetok->symtype;
    SYMBOL arraySymbol = symalloc();
    arraySymbol->highbound = symbolSubRange->highbound;
    arraySymbol->lowbound = symbolSubRange->lowbound;
    arraySymbol->kind = ARRAYSYM;
    arraySymbol->datatype = typeSymbol;
    arraySymbol->size = (arraySymbol->highbound - arraySymbol->lowbound +  1) * (typeSymbol->size);
    typetok->symtype = arraySymbol;
    return typetok;
    if (DEBUG) {
        printf("instarray\n");
    }
}


/* makefuncall makes a FUNCALL operator and links it to the fn and args.
   tok is a (now) unused token that is recycled. */
TOKEN makefuncall(TOKEN tok, TOKEN fn, TOKEN args) {
    if (strcmp(fn->stringval, "new") == 0) {
        tok = makeop(ASSIGNOP);
        tok->operands = args;
        SYMBOL typeSymbol = args->symtype;
        typeSymbol = typeSymbol->datatype;
        TOKEN functionCallToken = talloc();
        functionCallToken->tokentype = OPERATOR;
        functionCallToken->whichval = FUNCALLOP;
        functionCallToken->operands = fn;
        fn->link = makeintc(typeSymbol->size);
        args->link = functionCallToken;
    }
    else if (strcmp(fn->stringval, "writeln") == 0) {
        if (args->basicdt == REAL) {
            strcpy(fn->stringval, "writelnf");
        }
        if (args->tokentype == STRINGTOK) {
            strcpy(fn->stringval, "writeln");
        } else {
            strcpy(fn->stringval, "writelni");
        }
        tok->whichval = FUNCALLOP;
        tok->operands = fn;
        tok->tokentype = OPERATOR;
        fn->link=args; 
    }
    else {
        tok->tokentype = OPERATOR;
        tok->whichval = FUNCALLOP;
        tok->operands = fn;
        fn->link=args;
    }
    if (DEBUG) {
        printf("makefuncall\n");
    }
    return tok;
}

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
    TOKEN tok = talloc();
    tok->tokentype = OPERATOR;
    tok->whichval = PROGRAMOP;
    tok->operands = name;
    TOKEN progn_tok = makeprogn(talloc(), args);
    name->link = progn_tok;
    progn_tok->link = statements;
    if (DEBUG) {
        printf("makeprogram\n");
    }
    return tok;
}

TOKEN makelabel() {
    TOKEN l = talloc();
    l->tokentype = OPERATOR;
    l->whichval = LABELOP;
    TOKEN num = makeintc(labelnumber);
    labelnumber++;
    l->operands = num;
    return l;
}

TOKEN makegoto(int label) {
    TOKEN tok = talloc();
    tok->tokentype = OPERATOR;
    tok->whichval = GOTOOP;
    TOKEN l_tok = makeintc(label);
    tok->operands = l_tok;
    return tok;
}

TOKEN makeintc(int num) {
    TOKEN tok = talloc();
    tok->basicdt = INTEGER;
    tok->intval = num; 
    tok->tokentype = NUMBERTOK;
    return tok;
}

TOKEN findtype(TOKEN tok) {
    SYMBOL sym = searchst(tok->stringval);
    if (sym->kind == TYPESYM) {
        sym = sym->datatype;
    } else if (sym->kind == BASICTYPE) {
        tok->symtype = sym; 
        tok->basicdt = sym->basicdt; 
    }
    tok->symtype = sym;
    if (DEBUG) {
        printf("findtype\n");
    }
    return tok;
}

void instvars(TOKEN idlist, TOKEN typetok) {
    int align;
    SYMBOL type, sym; 
    type = typetok->symtype;
    align = alignsize(type);
    while (idlist != NULL)  {  
        sym = insertsym(idlist->stringval);
        sym->kind = VARSYM; 
        sym->offset = wordaddress(blockoffs[blocknumber],align);
        sym->size = type->size;
        blockoffs[blocknumber] = sym->offset + sym->size;
        sym->datatype = type;
        sym->basicdt = type->basicdt;
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
    
    /* gencode(parseresult, blockoffs[blocknumber], labelnumber); */
 
  }
