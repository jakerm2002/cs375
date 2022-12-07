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

int recount = 0;
int recount2 = 0;
int nextlabel;    /* Next available label number */
int stkframesize;   /* total stack frame size */
int regs[FMAX + 1];
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

void gencode(TOKEN pcode, int varsize, int maxlabel)
  {  TOKEN name, code;
     name = pcode->operands;
     code = name->link->link;
     nextlabel = maxlabel + 1;
     stkframesize = asmentry(name->stringval,varsize);
     genc(code);
     asmexit(name->stringval);
  }

/* Trivial version: always returns RBASE + 0 */
/* Get a register.   */
/* Need a type parameter or two versions for INTEGER or REAL */
int getreg(int kind) {
	//printf("in getreg\n");fflush(0);
	int i;
	if(kind == INTEGER || kind == BOOLETYPE || kind == POINTER) {
		for(i = RBASE; i <= RMAX; i++) {
			if(regs[i] == 0) {
				regs[i] = 1;
				//printf("end getreg\n");fflush(0);
				return i;
			}
		}
	} else if(kind == REAL || kind == STRINGTYPE) {
		for(i = FBASE; i <= FMAX; i++) {
			if(regs[i] == 0) {
				regs[i] = 1;
				//printf("end getreg\n");fflush(0);
				return i;
			}
		}
	}
}

void clearreg() {
	int i;
	for( i = 0; i < sizeof(regs); i++) {
		regs[i] = 0;
	}
}

void used(int reg) {
	regs[reg] = 1;
}

void unused(int reg) {
	regs[reg] = 0;
}

int funcallin(TOKEN code) {
	//printf("in funcallin");fflush(0);
	if(code->tokentype == OPERATOR && code->whichval == FUNCALLOP)
		return 1;

	if(code->operands != NULL)
		if(funcallin(code->operands))
			return 1;

	if(code->link != NULL)
		if(funcallin(code->link))
			return 1;

	return 0;
}

/* Trivial version */
/* Generate code for arithmetic expression, return a register number */
int genarith(TOKEN code) {
	recount+=1;
	int count = recount;
	//printf("in genarith %d\n", count);fflush(0);
	int num, reg, reg2;
	double fnum;
	int off;
	SYMBOL s;
	TOKEN lhs, rhs;

	switch ( code->tokentype ) {
		case NUMBERTOK:
			//printf("in numbertok\n");fflush(0);
			switch (code->basicdt) {
				case INTEGER:
					//printf("in numbertok->integer\n");fflush(0);
					num = code->intval;
					reg = getreg(INTEGER);
					if ( num >= MINIMMEDIATE && num <= MAXIMMEDIATE )
						asmimmed(MOVL, num, reg);
				break;
				case REAL:
					//printf("in numbertok->real\n");fflush(0);		// here
					fnum = code->realval;
					reg = getreg(REAL);
					makeflit(fnum, nextlabel);
					asmldflit(MOVSD, nextlabel++, reg);
				break;
				case POINTER:
					//printf("in numbertok->pointer\n");fflush(0);
					num = code->intval;
					reg = getreg(POINTER);
					asmimmed(MOVQ, num, reg);
				break;
			}
		break;
		case IDENTIFIERTOK:
			s = searchst(code->stringval);
			off = s->offset - stkframesize;
			if(s->basicdt == REAL) {
				//printf("in identifiertok->if->real\n");fflush(0);
				reg = getreg(REAL);
				asmld(MOVSD, off, reg, s->namestring);
			} else {
				switch(code->basicdt) {
					case INTEGER:
						//printf("in identifiertok->integer\n");fflush(0);
						reg = getreg(INTEGER);
						asmld(MOVL, off, reg, s->namestring);
					break;
					case REAL:
						//printf("in identifiertok->real\n");fflush(0);
						reg = getreg(REAL);
						asmld(MOVSD, off, reg, s->namestring);
					break;
					case POINTER:
						//printf("in identifiertok->pointer\n");fflush(0);
						reg = getreg(POINTER);
						asmld(MOVQ, off, reg, s->namestring);
					break;
				}
			}
		break;
		case STRINGTOK:
			reg = getreg(STRINGTYPE);
			asmlitarg(nextlabel, EDI);
			makeblit(code->stringval, nextlabel++);
		break;
		case OPERATOR:
			//printf("in operator\n");fflush(0);
			lhs = code->operands;
			rhs = lhs->link;

			if(code->whichval != FUNCALLOP) {

				reg = genarith(lhs);
				if(rhs != NULL && !(lhs->whichval == POINTEROP && rhs->tokentype == NUMBERTOK))
					reg2 = genarith(rhs);
			}

			if(code->whichval == PLUSOP) {
				switch(code->basicdt) {
					case INTEGER:
						asmrr(ADDL, reg2, reg);
					break;
					case REAL:
						asmrr(ADDSD, reg2, reg);
					break;
				}
			} else if(code->whichval == MINUSOP) {
				if(rhs == NULL) {
					s = lhs->symentry;
					if(s->basicdt == REAL) {
						//printf("in operator->if->minusop->real\n");fflush(0);
    						reg2 = getreg(REAL);
    						asmfneg(reg, reg2);
    						reg = reg2;
    						unused(reg2);
					} else {
						reg2 = getreg(INTEGER);
						asmimmed(MOVL, 0, reg2);
						asmrr(SUBL, reg, reg2);
						reg ^= reg2;
						reg2 ^= reg;
						reg ^= reg2;
						unused(reg2);
					}
				} else {
					switch(code->basicdt) {
						case INTEGER:
							asmrr(SUBL, reg2, reg);
						break;
						case REAL:
							asmrr(SUBSD, reg2, reg);
						break;
					}
				}
			} else if(code->whichval == TIMESOP) {
				//printf("in timesop\n");fflush(0);
				switch(code->basicdt) {
					case INTEGER:
						asmrr(IMULL, reg2, reg);
					break;
					case REAL:
						asmrr(MULSD, reg2, reg);
					break;
				}
			} else if(code->whichval == FLOATOP) {
				//printf("in floatop\n");fflush(0);
				reg2 = getreg(REAL);
				asmfloat(reg, reg2);
				reg ^= reg2;
				reg2 ^= reg;
				reg ^= reg2;
				unused(reg2);
			} else if(code->whichval == FIXOP) {
				reg2 = getreg(INTEGER);
				asmfix(reg, reg2);
				reg ^= reg2;
				reg2 ^= reg;
				reg ^= reg2;
				unused(reg2);
			} else if(code->whichval == FUNCALLOP) {
				//printf("in operator->funcallop\n");fflush(0);
				lhs = code->operands->link;
				reg = genarith(lhs);

				//dbugprinttok(code);
				//dbugprinttok(lhs);
				//dbugprinttok(code->operands);

				if(funcallin(code) && lhs->basicdt == REAL) {
					//printf("in funcallop->real\n");fflush(0);		//here
					if(reg != XMM0 && regs[XMM0]) {
						//printf("in funcallop->real->!xmm0&&regs[xmm0]\n");fflush(0);
						asmsttemp(XMM0);
						asmrr(MOVSD, reg, XMM0);
						asmcall(code->operands->stringval);
						asmrr(MOVSD, XMM0, reg);
						asmldtemp(XMM0);
					} else if(reg != XMM0) {
						//printf("in funcallop->real->!xmm0\n");fflush(0);
						asmrr(MOVSD, reg, XMM0);
						unused(reg);
						asmcall(code->operands->stringval);
						regs[XMM0] = 1;
						reg = XMM0;
					} else {
						//printf("in funcallop->real->else\n");fflush(0);
						asmcall(code->operands->stringval);
						if(hassaved) {
							reg2 = getreg(REAL);
							asmldtemp(reg2);
							//dbugprinttok(code->operands->link->operands);
							hassaved = 0;
						}
						//dbugprinttok(code->operands);
						regs[XMM0] = 1;
						reg = XMM0;
					}
				} else {
					asmcall(code->operands->stringval);
					asmsttemp(XMM0);
					unused(XMM0);
					hassaved=1;
				}

			} else if(code->whichval == AREFOP) {
				//printf("in operator->aref");fflush(0);
				off = code->operands->link->intval;
				switch (code->basicdt) {
				case INTEGER:
					reg2 = getreg(INTEGER);
					asmldr(MOVL, off, reg, reg2, "^.");
					reg ^= reg2;
					reg2 ^= reg;
					reg ^= reg2;
				break;
				case REAL:
					//printf("in operator->aref->real\n");fflush(0);
					reg2 = getreg(REAL);
					asmldr(MOVSD, off, reg, reg2, "^.");
					reg ^= reg2;
					reg2 ^= reg;
					reg ^= reg2;
				break;
				case POINTER:
					//printf("in operator->aref->pointer\n");fflush(0);
					reg2 = getreg(POINTER);
					asmldr(MOVQ, off, reg, reg2, "^.");
					reg ^= reg2;
					reg2 ^= reg;
					reg ^= reg2;
				break;
				}
			}
			//printf("end operator\n");fflush(0);
			if(rhs != NULL && code->whichval != FUNCALLOP && code->whichval != POINTEROP)
				unused(reg2);
		break;
		default:
			printf("error: nothing happened\n");fflush(0);
			dbugprinttok(code);
	};
	//printf("end genarith %d\n", count);fflush(0);
	//dbugprinttok(code);
	//printf("reg: %d\n", reg);
	return reg;
}


/* Generate code for a Statement from an intermediate-code form */
void genc(TOKEN code) {
	recount2+=1;
	int count = recount2;
	//printf("in genc %d\n", count);fflush(0);
	TOKEN tok, lhs, rhs;
	int reg, reg2, off;
	int label1, label2, jmp;
	SYMBOL s;
	/*
	if(DEBUGGEN) {
		//printf("genc\n");
		dbugprinttok(code);
	};
	*/
	//printf("1\n");fflush(0);

	if(code->tokentype != OPERATOR) {
		//printf("Bad code token");
		//dbugprinttok(code);
	}
	//printf("2\n");fflush(0);
	//dbugprinttok(code);



	switch ( code->whichval ) {
		case PROGNOP:
			//printf("in prognop\n");fflush(0);

			tok = code->operands;
			while ( tok != NULL ) {
				genc(tok);
				tok = tok->link;
			}
		break;
		case ASSIGNOP:
			lhs = code->operands;
			//dbugprinttok(lhs);
			rhs = lhs->link;
			//printf("5\n");fflush(0);
			reg = genarith(rhs);

			if(lhs->tokentype == OPERATOR && lhs->whichval == AREFOP && lhs->operands->tokentype != IDENTIFIERTOK) {
				//printf("in assignop\n");fflush(0);
				reg2 = genarith(lhs->operands);
				s = lhs->operands->symentry;
				off = lhs->operands->link->intval;
				switch (rhs->basicdt) {
					case INTEGER:
						//printf("in genc->assignop->!identifiertok->integer\n");fflush(0);
						asmstr(MOVL, reg, off, reg2, "^. ");
					break;
					case REAL:
						//printf("in genc->assignop->!identifiertok->real\n");fflush(0);
						asmstr(MOVSD, reg, off, reg2, "^. ");
					break;
					case POINTER:
						//printf("in genc->assignop->!identifiertok->pointer\n");fflush(0);
						asmstr(MOVQ,reg, off, reg2, "^. ");
					break;
				}
				if(reg != reg2)
					unused(reg2);
			} else if(lhs->tokentype == OPERATOR && lhs->whichval == AREFOP && lhs->operands->tokentype == IDENTIFIERTOK && lhs->operands->link->tokentype != NUMBERTOK){
				reg2 = genarith(lhs->operands->link);
				s = lhs->operands->symentry;
				off = s->offset - stkframesize;

				switch (rhs->basicdt) {
					case INTEGER:
						//printf("in genc->assignop->=identifiertok->!=numbertok->integer\n");fflush(0);
						asmop(CLTQ);
						asmstrr(MOVL, reg, off, reg2, lhs->operands->stringval);
					break;
					case REAL:
						//printf("in genc->assignop->=identifiertok->!=numbertok->real\n");fflush(0);
						asmop(CLTQ);
						asmstrr(MOVSD, reg, off, reg2, lhs->operands->stringval);
					break;
					case POINTER:
						//printf("in genc->assignop->=identifiertok->!=numbertok->pointer\n");fflush(0);
						asmop(CLTQ);
						asmstrr(MOVQ,reg, off, reg2, lhs->operands->stringval);
					break;
				}
				if(reg != reg2)
					unused(reg2);
			} else if (lhs->tokentype == OPERATOR && lhs->whichval == AREFOP && lhs->operands->tokentype == IDENTIFIERTOK && lhs->operands->link->tokentype == NUMBERTOK) {
				s = lhs->operands->symentry;
				off = s->offset - stkframesize + lhs->operands->link->intval;
				switch (lhs->basicdt) {
					case INTEGER:
						//printf("in genc->assignop->=identifiertok->=numbertok->integer\n");fflush(0);
						asmst(MOVL, reg, off, lhs->stringval);
					break;
					case REAL:
						//printf("in genc->assignop->=identifiertok->=numbertok->real\n");fflush(0);
						asmst(MOVSD, reg, off, lhs->stringval);
					break;
					case POINTER:
						//printf("in genc->assignop->=identifiertok->=numbertok->pointer\n");fflush(0);
						asmst(MOVQ,reg, off, lhs->stringval);
					break;
				}
			} else {
				//printf("1\n");fflush(0);

				s = lhs->symentry;
				off = s->offset - stkframesize;
				if(s->basicdt == REAL) {
					//printf("in genc->assignop->else->if->real\n");fflush(0);
					asmst(MOVSD, reg, off, lhs->stringval);
				} else {

					switch (lhs->basicdt) {
						case INTEGER:
							//printf("in genc->assignop->else->integer\n");fflush(0);
							asmst(MOVL, reg, off, lhs->stringval);
						break;
						case REAL:
							//printf("in genc->assignop->else->real\n");fflush(0);
							asmst(MOVSD, reg, off, lhs->stringval);
						break;
						case POINTER:
							//printf("in genc->assignop->else->pointer\n");fflush(0);
							asmst(MOVQ,reg, off, lhs->stringval);
						break;
					}
				}
			}
			unused(reg);
		break;

		case LABELOP:
			asmlabel(code->operands->intval);
		break;

		case GOTOOP:
			asmjump(0, code->operands->intval);
		break;

		case IFOP:
			//printf("in ifop\n");fflush(0);
			code = code->operands;
			lhs = code->operands;
			rhs = lhs->link;
			reg = genarith(lhs);
			reg2 = genarith(rhs);

			switch(lhs->basicdt) {
				case INTEGER:
					asmrr(CMPL,reg2,reg);
				break;
				case REAL:
					asmrr(CMPSD,reg2,reg);
				break;
				case POINTER:
					asmrr(CMPQ,reg2,reg);
				break;
			}

			unused(reg);
			unused(reg2);

			label1 = nextlabel++;

			if(code->whichval == EQOP) {
				jmp = JE;
			} else if(code->whichval == NEOP) {
				jmp = JNE;
			} else if(code->whichval == LTOP) {
				jmp = JL;
			} else if(code->whichval == LEOP) {
				jmp = JLE;
			} else if(code->whichval == GEOP) {
				jmp = JGE;
			} else if(code->whichval == GTOP) {
				jmp = JG;
			} else {
				//printf("error in ifop\n");fflush(0);
			}
			asmjump(jmp, label1);

			if(code->link->link != NULL) {
				genc(code->link->link);
			}
			label2 = nextlabel++;
			asmjump(0, label2);

			asmlabel(label1);

			genc(code->link);

			asmlabel(label2);
			//printf("end ifop\n");fflush(0);
		break;
		case FUNCALLOP:
			tok = code->operands->link;
			reg = genarith(tok);

			unused(reg);

			asmcall(code->operands->stringval);
			//printf("end genc->funcallop\n");
		break;
	}
	//printf("end genc %d\n", count);fflush(0);
}