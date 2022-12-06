/* codgen.c       Generate Assembly Code for x86         07 May 18   */

/* Copyright (c) 2018 Gordon S. Novak Jr. and The University of Texas at Austin
 */

/* Starter file for CS 375 Code Generation assignment.           */
/* Written by Gordon S. Novak Jr.                  */

/* This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License (file gpl.text) for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA. */

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "token.h"
#include "symtab.h"
#include "lexan.h"
#include "genasm.h"
#include "codegen.h"
#include "pprint.h"

void genc(TOKEN code);

/* Set DEBUGGEN to 1 for debug printouts of code generation */
#define DEBUGGEN 0

int nextlabel;    /* Next available label number */
int stkframesize; /* total stack frame size */
int registers[32];
int hassaved = 0;

int op_to_inst_int[50];
int op_to_inst_real[50];
int op_to_inst_point[50];

int ifc_to_jinst[50];

/* Top-level entry for code generator.
   pcode    = pointer to code:  (program foo (output) (progn ...))
   varsize  = size of local storage in bytes
   maxlabel = maximum label number used so far

Add this line to the end of your main program:
    gencode(parseresult, blockoffs[blocknumber], labelnumber);
The generated code is printed out; use a text editor to extract it for
your .s file.
         */

/* Clear register used tables to mark all registers free.  */
void clearreg()
{
    for (int i = 0; i < sizeof(registers); i++)
    {
        registers[i] = 0;
    }
}

/* Mark a register unused */
void unused(int reg)
{
    registers[reg] = 0;
}

/* Mark a register used */
void used(int reg)
{
    registers[reg] = 1;
}

/* Make a register non-volatile by moving it if necessary.
   Result is the (possibly new) register number.   */
int nonvolatile(int reg);

/* Save caller-saves floating point registers on stack if in use */
void savereg();

/* Restore caller-saves floating point registers from stack if in use */
void restorereg();

/* test if there is a function call within code: 1 if true, else 0 */
int funcallin(TOKEN code)
{
    // printf("in funcallin");fflush(0);
    if (code->tokentype == OPERATOR && code->whichval == FUNCALLOP)
        return 1;

    if (code->operands != NULL)
        if (funcallin(code->operands))
            return 1;

    if (code->link != NULL)
        if (funcallin(code->link))
            return 1;

    return 0;
}

/* find the op number that is equivalent to named function, if any */
int findfunop(char str[]);

/* Generate code for a function call */
int genfun(TOKEN code)
{
    TOKEN tok = code->operands; // FUNCTION
    TOKEN lhs = tok->link;      // FIRST ARGUMENT
    int count = 0;
    while (lhs)
    {
        genarith(lhs);
        lhs = lhs->link;
        count++;
    }

    asmcall(tok->stringval);
    SYMBOL sym = searchst(tok->stringval);

    if (DEBUGGEN)
    {
        printf("genfunc\n");
        printf("no of arguments: %d", count);
        dbugprinttok(code);
    }
    if (sym->datatype->basicdt == REAL)
    {
        return XMM0;
    }
    else if (sym->datatype->basicdt == INTEGER)
    {
        return EAX;
    }
    else
    {
        return RAX;
    }
}

/* find the correct MOV op depending on type of code */
int moveop(TOKEN code);

/* Generate code for array references and pointers */
/* In Pascal, a (^ ...) can only occur as first argument of an aref. */
/* If storereg < 0, generates a load and returns register number;
   else, generates a store from storereg. */
int genaref(TOKEN code, int storereg);

void gencode(TOKEN pcode, int varsize, int maxlabel)
{
    TOKEN name, code;
    name = pcode->operands;
    code = name->link->link;
    nextlabel = maxlabel + 1;
    stkframesize = asmentry(name->stringval, varsize);
    genc(code);
    asmexit(name->stringval);
}

/* Trivial version: always returns RBASE + 0 */
/* Get a register.   */
/* Need a type parameter or two versions for INTEGER or REAL */
int getreg(int kind)
{
    if (kind == INTEGER || kind == BOOLETYPE || kind == POINTER)
    {
        for (int i = RBASE; i <= RMAX; i++)
        {
            if (registers[i] == 0)
            {
                registers[i] = 1;
                // printf("end getreg\n");fflush(0);
                return i;
            }
        }
    }
    else if (kind == REAL || kind == STRINGTYPE)
    {
        for (int i = FBASE; i <= FMAX; i++)
        {
            if (registers[i] == 0)
            {
                registers[i] = 1;
                // printf("end getreg\n");fflush(0);
                return i;
            }
        }
    }
}

/* Trivial version */
/* Generate code for arithmetic expression, return a register number */
int genarith(TOKEN code)
{
    int num, reg, reg2;
    float fl;
    SYMBOL sym;
    int offs;
    TOKEN lhs, rhs;
    if (DEBUGGEN)
    {
        printf("genarith\n");
        dbugprinttok(code);
    };
    switch (code->tokentype)
    {
    case NUMBERTOK:
        switch (code->basicdt)
        {
        case INTEGER:
            num = code->intval;
            reg = getreg(INTEGER);
            if (num >= MINIMMEDIATE && num <= MAXIMMEDIATE)
                asmimmed(MOVL, num, reg);
            break;
        case REAL:
            fl = code->realval;
            reg = getreg(REAL);
            int label = nextlabel++;
            makeflit(fl, label);
            asmldflit(MOVSD, label, reg);
            break;
        }
        break;

    case STRINGTOK:
        num = nextlabel++;
        makeblit(code->stringval, num);
        reg = EDI;
        asmlitarg(num, reg);
        break;

    case IDENTIFIERTOK: // If not a function
        sym = code->symentry;
        offs = sym->offset - stkframesize;
        switch (code->basicdt)
        {
        case INTEGER:
            reg = getreg(INTEGER);
            asmld(MOVL, offs, reg, code->stringval);
            break;
        case REAL:
            reg = getreg(REAL);
            asmld(MOVSD, offs, reg, code->stringval);
            break;
        case POINTER:
            reg = getreg(POINTER);
            asmld(MOVQ, offs, reg, code->stringval);
            break;
        }
        break;

        // INCLUDE CHECK TO SEE IF RHS IS A FUNCALL, AND IF SO, SAVE ALL VOLATILE REGISTER
        // INCLUDE CHECK TO SEE IF ARGUMENT IS A FUNCALL

    case OPERATOR:
        if (code->whichval == AREFOP)
        {
            // reg = genaref(code, reg2);
        }
        else if (code->whichval == FUNCALLOP)
        {
            reg = genfun(code);
        }
        else if (code->whichval == FLOATOP)
        {
            lhs = code->operands;
            reg2 = genarith(lhs);
            reg = getreg(REAL);
            asmfloat(reg2, reg);
            unused(reg2);
        }
        else if (code->whichval == FIXOP)
        {
            lhs = code->operands;
            reg2 = genarith(lhs);
            reg = getreg(INTEGER);
            asmfix(reg2, reg);
            unused(reg2);
        }
        else if (code->basicdt == INTEGER)
        {
            lhs = code->operands;
            rhs = lhs->link;
            reg = genarith(lhs);
            if (rhs)
            {
                if (funcallin(rhs))
                {
                    asmsttemp(reg);
                    unused(reg);
                    reg2 = genarith(rhs);
                    asmldtemp(reg);
                    asmrr(op_to_inst_int[code->whichval], reg2, reg);
                    unused(reg2);
                }
                else
                {
                    reg2 = genarith(rhs);
                    asmrr(op_to_inst_int[code->whichval], reg2, reg);
                    unused(reg2);
                }
            }
            else
            {
                reg2 = getreg(REAL);
                asmfneg(reg, reg2);
                reg = reg2;
                unused(reg2);
            }
        }
        else if (code->basicdt == REAL)
        {
            lhs = code->operands;
            rhs = lhs->link;
            reg = genarith(lhs);
            if (rhs)
            {
                if (funcallin(rhs))
                {
                    asmsttemp(reg);
                    unused(reg);
                    reg2 = genarith(rhs);
                    asmldtemp(reg);
                    asmrr(op_to_inst_real[code->whichval], reg2, reg);
                    unused(reg2);
                }
                else
                {
                    reg2 = genarith(rhs);
                    asmrr(op_to_inst_real[code->whichval], reg2, reg);
                    unused(reg2);
                }
            }
            else
            {
                reg2 = getreg(REAL);
                asmfneg(reg, reg2);
                reg = reg2;
                unused(reg2);
            }
        }
        else
        {
            printf("Error");
            return -1;
        }
        break;
    };

    return reg;
}

/* Generate code for a Statement from an intermediate-code form */
void genc(TOKEN code)
  {  TOKEN tok, lhs, rhs;
     int reg, offs;
     SYMBOL sym;
     clearreg();

     if (DEBUGGEN) {
      printf("genc\n");
	    dbugprinttok(code);
     };

     if ( code->tokentype != OPERATOR ) { 
          printf("Bad code token");
      	  dbugprinttok(code);
      };

     switch ( code->whichval ) {
      case PROGNOP:  tok = code->operands;
                	   while ( tok != NULL ) {
                       genc(tok);
                		   tok = tok->link;
                	   }; 
                	   break;

      case ASSIGNOP: lhs = code->operands;      /* Trivial version: handles I := e */
                	   rhs = lhs->link;
                	   reg = genarith(rhs);              /* generate rhs into a register */
                	   sym = lhs->symentry;              /* assumes lhs is a simple var  */
                	   offs = sym->offset - stkframesize; /* net offset of the var   */
                     switch (code->basicdt) {          /* store value into lhs  */
                       case INTEGER: asmst(MOVL, reg, offs, lhs->stringval);
                                     break;
                       case REAL: asmst(MOVSD, reg, offs, lhs->stringval);  
                                  break;
                                 /* ...  */
                     };
                     break; 

      case GOTOOP: asmjump(JMP, code->operands->intval);
                   break;

      case LABELOP: asmlabel(code->operands->intval);
                    break;

      case IFOP:  tok = code->operands;
                  reg = genarith(tok);        
                  lhs = tok->link; //THEN PART
                  rhs = lhs->link; //ELSE PART
                  int curr = nextlabel++;
                  asmjump(ifc_to_jinst[tok->whichval], curr);
                  if (rhs) 
                    genc(rhs);
                  int end = nextlabel++;
                  asmjump(JMP, end);
                  asmlabel(curr);
                  genc(lhs);
                  asmlabel(end);
                  break;

      case FUNCALLOP: genfun(code);
                      break;
	   };
  }

void initalisetables()
{
    op_to_inst_int[PLUSOP] = ADDL;
    op_to_inst_int[MINUSOP] = SUBL;
    op_to_inst_int[TIMESOP] = IMULL;
    op_to_inst_int[DIVIDEOP] = DIVL;
    op_to_inst_int[ANDOP] = ANDL;
    op_to_inst_int[OROP] = ORL;
    op_to_inst_int[EQOP] = op_to_inst_int[LEOP] = op_to_inst_int[LTOP] = op_to_inst_int[GEOP] = op_to_inst_int[GTOP] = op_to_inst_int[NEOP] = CMPL;

    op_to_inst_real[PLUSOP] = ADDSD;
    op_to_inst_real[MINUSOP] = SUBSD;
    op_to_inst_real[TIMESOP] = MULSD;
    op_to_inst_real[DIVIDEOP] = DIVSD;
    op_to_inst_real[NOTOP] = NEGSD;
    op_to_inst_real[EQOP] = op_to_inst_real[LEOP] = op_to_inst_real[LTOP] = op_to_inst_real[GEOP] = op_to_inst_real[GTOP] = op_to_inst_real[NEOP] = CMPSD;

    op_to_inst_point[PLUSOP] = ADDQ;
    op_to_inst_point[MINUSOP] = SUBQ;
    op_to_inst_point[TIMESOP] = IMULQ;
    op_to_inst_point[ANDOP] = ANDQ;
    op_to_inst_point[NOTOP] = NOTQ;
    op_to_inst_point[OROP] = ORQ;
    op_to_inst_point[EQOP] = op_to_inst_point[LEOP] = op_to_inst_point[LTOP] = op_to_inst_point[GEOP] = op_to_inst_point[GTOP] = op_to_inst_point[NEOP] = CMPQ;

    ifc_to_jinst[EQOP] = JE;
    ifc_to_jinst[NEOP] = JNE;
    ifc_to_jinst[LTOP] = JL;
    ifc_to_jinst[LEOP] = JLE;
    ifc_to_jinst[GEOP] = JGE;
    ifc_to_jinst[GTOP] = JG;
}
