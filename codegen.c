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
int genfun(TOKEN code) {
    TOKEN tok = code->operands; //FUNCTION
    TOKEN lhs = tok->link;  //FIRST ARGUMENT
    int count = 0;
    while (lhs) {
      genarith(lhs);        
      lhs = lhs->link;
      count ++;
    }

    asmcall(tok->stringval);  
    SYMBOL sym = searchst(tok->stringval);

    if (DEBUGGEN) {
      printf("genfunc\n");
      printf("no of arguments: %d", count);
      dbugprinttok(code);
    }
    if (sym->datatype->basicdt == REAL) {
      return XMM0;
    } else if (sym->datatype->basicdt == INTEGER) {
      return EAX;
    } else {
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
            reg = getreg(WORD);
            if (num >= MINIMMEDIATE && num <= MAXIMMEDIATE)
                asmimmed(MOVL, num, reg);
            break;
        case REAL:
            fl = code->realval;
            reg = getreg(REAL);
            makeflit(fl, nextlabel);
            asmldflit(MOVSD, nextlabel++, reg);
            break;
        }
        break;
    case IDENTIFIERTOK:
        sym = searchst(code->stringval);
        offs = sym->offset - stkframesize;
        if (sym->basicdt == REAL)
        {
            // printf("in identifiertok->if->real\n");fflush(0);
            reg = getreg(REAL);
            asmld(MOVSD, offs, reg, sym->namestring);
        }
        else
        {
            switch (code->basicdt)
            {
            case INTEGER:
                // printf("in identifiertok->integer\n");fflush(0);
                reg = getreg(INTEGER);
                asmld(MOVL, offs, reg, sym->namestring);
                break;
            case REAL:
                // printf("in identifiertok->real\n");fflush(0);
                reg = getreg(REAL);
                asmld(MOVSD, offs, reg, sym->namestring);
                break;
            case POINTER:
                // printf("in identifiertok->pointer\n");fflush(0);
                reg = getreg(POINTER);
                asmld(MOVQ, offs, reg, sym->namestring);
                break;
            }
        }
        break;
    case OPERATOR:
        // printf("in operator\n");fflush(0);
        lhs = code->operands;
        rhs = lhs->link;

        if (code->whichval != FUNCALLOP)
        {

            reg = genarith(lhs);
            if (rhs != NULL && !(lhs->whichval == POINTEROP && rhs->tokentype == NUMBERTOK))
                reg2 = genarith(rhs);
        }

        if (code->whichval == PLUSOP)
        {
            switch (code->basicdt)
            {
            case INTEGER:
                asmrr(ADDL, reg2, reg);
                break;
            case REAL:
                asmrr(ADDSD, reg2, reg);
                break;
            }
        }
        else if (code->whichval == MINUSOP)
        {
            if (rhs == NULL)
            {
                sym = lhs->symentry;
                if (sym->basicdt == REAL)
                {
                    // printf("in operator->if->minusop->real\n");fflush(0);
                    reg2 = getreg(REAL);
                    asmfneg(reg, reg2);
                    reg = reg2;
                    unused(reg2);
                }
                else
                {
                    reg2 = getreg(INTEGER);
                    asmimmed(MOVL, 0, reg2);
                    asmrr(SUBL, reg, reg2);
                    reg ^= reg2;
                    reg2 ^= reg;
                    reg ^= reg2;
                    unused(reg2);
                }
            }
            else
            {
                switch (code->basicdt)
                {
                case INTEGER:
                    asmrr(SUBL, reg2, reg);
                    break;
                case REAL:
                    asmrr(SUBSD, reg2, reg);
                    break;
                }
            }
        }
        else if (code->whichval == TIMESOP)
        {
            // printf("in timesop\n");fflush(0);
            switch (code->basicdt)
            {
            case INTEGER:
                asmrr(IMULL, reg2, reg);
                break;
            case REAL:
                asmrr(MULSD, reg2, reg);
                break;
            }
        }
        else if (code->whichval == FLOATOP)
        {
            // printf("in floatop\n");fflush(0);
            reg2 = getreg(REAL);
            asmfloat(reg, reg2);
            reg ^= reg2;
            reg2 ^= reg;
            reg ^= reg2;
            unused(reg2);
        }
        else if (code->whichval == FIXOP)
        {
            reg2 = getreg(INTEGER);
            asmfix(reg, reg2);
            reg ^= reg2;
            reg2 ^= reg;
            reg ^= reg2;
            unused(reg2);
        }
        else if (code->whichval == FUNCALLOP)
        {
            // printf("in operator->funcallop\n");fflush(0);
            lhs = code->operands->link;
            reg = genarith(lhs);

            // dbugprinttok(code);
            // dbugprinttok(lhs);
            // dbugprinttok(code->operands);

            if (funcallin(code) && lhs->basicdt == REAL)
            {
                // printf("in funcallop->real\n");fflush(0);		//here
                if (reg != XMM0 && registers[XMM0])
                {
                    // printf("in funcallop->real->!xmm0&&registers[xmm0]\n");fflush(0);
                    asmsttemp(XMM0);
                    asmrr(MOVSD, reg, XMM0);
                    asmcall(code->operands->stringval);
                    asmrr(MOVSD, XMM0, reg);
                    asmldtemp(XMM0);
                }
                else if (reg != XMM0)
                {
                    // printf("in funcallop->real->!xmm0\n");fflush(0);
                    asmrr(MOVSD, reg, XMM0);
                    unused(reg);
                    asmcall(code->operands->stringval);
                    registers[XMM0] = 1;
                    reg = XMM0;
                }
                else
                {
                    // printf("in funcallop->real->else\n");fflush(0);
                    asmcall(code->operands->stringval);
                    if (hassaved)
                    {
                        reg2 = getreg(REAL);
                        asmldtemp(reg2);
                        // dbugprinttok(code->operands->link->operands);
                        hassaved = 0;
                    }
                    // dbugprinttok(code->operands);
                    registers[XMM0] = 1;
                    reg = XMM0;
                }
            }
            else
            {
                asmcall(code->operands->stringval);
                asmsttemp(XMM0);
                unused(XMM0);
                hassaved = 1;
            }
        }
        else if (code->whichval == AREFOP)
        {
            // printf("in operator->aref");fflush(0);
            offs = code->operands->link->intval;
            switch (code->basicdt)
            {
            case INTEGER:
                reg2 = getreg(INTEGER);
                asmldr(MOVL, offs, reg, reg2, "^.");
                reg ^= reg2;
                reg2 ^= reg;
                reg ^= reg2;
                break;
            case REAL:
                // printf("in operator->aref->real\n");fflush(0);
                reg2 = getreg(REAL);
                asmldr(MOVSD, offs, reg, reg2, "^.");
                reg ^= reg2;
                reg2 ^= reg;
                reg ^= reg2;
                break;
            case POINTER:
                // printf("in operator->aref->pointer\n");fflush(0);
                reg2 = getreg(POINTER);
                asmldr(MOVQ, offs, reg, reg2, "^.");
                reg ^= reg2;
                reg2 ^= reg;
                reg ^= reg2;
                break;
            }
        }
        // printf("end operator\n");fflush(0);
        if (rhs != NULL && code->whichval != FUNCALLOP && code->whichval != POINTEROP)
            unused(reg2);
        break;
    };
    return reg;
}

/* Generate code for a Statement from an intermediate-code form */
void genc(TOKEN code)
{
    TOKEN tok, lhs, rhs;
    int reg, offs;
    SYMBOL sym;
    int jmp;
    if (DEBUGGEN)
    {
        printf("genc\n");
        dbugprinttok(code);
    };
    if (code->tokentype != OPERATOR)
    {
        printf("Bad code token");
        dbugprinttok(code);
    };
    switch (code->whichval)
    {
    case PROGNOP:
        tok = code->operands;
        while (tok != NULL)
        {
            genc(tok);
            tok = tok->link;
        };
        break;
    case ASSIGNOP: /* Trivial version: handles I := e */
        lhs = code->operands;
        rhs = lhs->link;
        reg = genarith(rhs);               /* generate rhs into a register */
        sym = lhs->symentry;               /* assumes lhs is a simple var  */
        offs = sym->offset - stkframesize; /* net offset of the var   */
        switch (code->basicdt)             /* store value into lhs  */
        {
        case INTEGER:
            asmst(MOVL, reg, offs, lhs->stringval);
            break;
        case REAL:
            asmst(MOVSD, reg, offs, lhs->stringval);
            break;
            /* ...  */
        };
        break;
    case FUNCALLOP:
        genfun(code);
        break;
    case GOTOOP:
        asmjump(JMP, code->operands->intval);
        break;
    case LABELOP:
        asmlabel(code->operands->intval);
        break;
    case IFOP:
        tok = code->operands;
        reg = genarith(tok);
        lhs = tok->link; // THEN PART
        rhs = lhs->link; // ELSE PART
        int curr = nextlabel++;

        if (tok->whichval == EQOP)
        {
            jmp = JE;
        }
        else if (tok->whichval == NEOP)
        {
            jmp = JNE;
        }
        else if (tok->whichval == LTOP)
        {
            jmp = JL;
        }
        else if (tok->whichval == LEOP)
        {
            jmp = JLE;
        }
        else if (tok->whichval == GEOP)
        {
            jmp = JGE;
        }
        else if (tok->whichval == GTOP)
        {
            jmp = JG;
        }
        else
        {
            // printf("error in ifop\n");fflush(0);
        }
        asmjump(jmp, curr);
        if (rhs)
            genc(rhs);
        int end = nextlabel++;
        asmjump(JMP, end);
        asmlabel(curr);
        genc(lhs);
        asmlabel(end);
        break;
    };
}
