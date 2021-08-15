%skeleton "lalr1.cc" // -*- C++ -*-
//%require "3.7.6"
%defines

%define api.token.raw
%define api.token.constructor
%define api.value.type variant
//%define parse.assert

%code requires {
  # include <string>
  class driver;
}

// The parsing context.
%param { driver& drv }

%locations

%define parse.trace
%define parse.error verbose


%code {
# include "driver.h"
#include "tokens.h"
}

%define api.token.prefix {TOK_}

//da li treba svima dodeliti vrednost
%token
  MINUS   "-"
  PLUS    "+"
  STAR    "*"
  SLASH   "/"
  LPAREN  "("
  RPAREN  ")"
  COMMA   ","
  COLON   ":"
  DOLLAR  "$"
  PERCENT "%" 
  HASH    "#"
  NEWLINE "\n"
  GLOBAL  ".global"
  EXTERN  ".extern"
  SECTION ".section"
  WORD    ".word"
  SKIP    ".skip"
  EQU     ".equ"
  END     ".end"
;


%token <std::vector<tokens::Line>> lines
%token <tokens::Line> line
%token <std::string> label
%token <tokens::Expression> expression
%token <tokens::Directive> directive
%token <tokens::Instruction> instruction
%token <std::vector<std::string>> symbols
%token <std::string> SYMBOL "symbol"
%token <int> literal
%token <int> NUMBER "number"
%token <int> HEX "hex"
%token <std::string> COMMENT "comment"
%token <tokens::Initializer> initializer
%token <std::vector<tokens::Initializer>> initializers
%token <tokens::Instr0> instr0
%token <tokens::Instr1_reg> instr1_reg
%token <tokens::Instr1_op> Instr1_op
%token <tokens::Instr2_regreg> instr2_regreg
%token <tokens::Instr2_regop> instr2_regop


%printer { yyo << $$; } <*>;

%%
%start code;

code:   
    lines {}
;

lines:   
    %empty {
        $$=new vector<tokens::Line>();
    }
|   lines line {
        $1->push_back($2);
        $$=$1;
    }
;

//!!!! labela na kraju svega?
line:
    label line {}
|   COMMENT "\n" line {}
|   exspression {
        $$=new Line();
        $$.exp=$1;

    }
;

label:
    SYMBOL ":" {
        //dodaj labelu u tabelu simbola
    }
;

expression:
    directive {
        $$=$1;
    }
|   instruction {
        $$=$1;
    }
;

directive:
    GLOBAL symbols {
        //simbole zameni u tabeli simbola sa globalnim ako postoje ili ih dodaj
    }
|   EXTERN symbols {
        //isto oznaci kao globalne i nedefinisane
    }
|   SECTION SYMBOL {
        //dodaj u tabelu sekcija, resetuj brojac adresa
    }
|   WORD initializers {
        //inicijalizuj prostor vrednostima iz liste inicijalizatora
    }
|   SKIP literal {
        //counter povecaj za vrednost literala
    } 
|   EQU SYMBOL "," literal {
        //u tabelu simbola dodaj novi simbol sa vrednoscu literala
    }
|   END {
        //postavi flag u driveru i ako je on postavljen na dalje ne obradjuj tekst
    }
;

initializers:
    initializers "," SYMBOL {
        //vrednost inicijalizatora postavi na vrednost iz tabele simbola
    }
|   initializers "," literal {
        //vrednost literala
    }
|   literal {

    }
|   initializer {

    }
;

literal:
    NUMBER {
        $$=$1;
    }



%start unit;
unit: assignments exp  { drv.result = $2; };

assignments:
  %empty                 {}
| assignments assignment {};

assignment:
  "identifier" ":=" exp { drv.variables[$1] = $3; };

%left "+" "-";
%left "*" "/";
exp:
  "number"
| "identifier"  { $$ = drv.variables[$1]; }
| exp "+" exp   { $$ = $1 + $3; }
| exp "-" exp   { $$ = $1 - $3; }
| exp "*" exp   { $$ = $1 * $3; }
| exp "/" exp   { $$ = $1 / $3; }
| "(" exp ")"   { $$ = $2; }
%%

void
yy::parser::error (const location_type& l, const std::string& m)
{
  std::cerr << l << ": " << m << '\n';
}