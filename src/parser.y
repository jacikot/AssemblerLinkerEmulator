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
  LBRACK  "["
  RBRACK  "]"
  COMMA   ","
  COLON   ":"
  DOLLAR  "$"
  HASH    "#"
  PERCENT "%" 
  NEWLINE "\n"
  GLOBAL  
  EXTERN  
  SECTION 
  WORD    
  SKIP    
  EQU     
//   END    0
  REG
  REG_PC  "pc"
  REG_SP  "sp"
  REG_PSW "psw"
;


%token <std::vector<tokens::Line>> lines
%token <tokens::Line> line
%token <std::string> label
%token <tokens::Expression> expression
%token <tokens::Directive> directive
%token <tokens::Instruction> instruction
%token <std::vector<tokens::Initializer>> symbols
%token <std::string> SYMBOL
%token <int> literal
%token <int> NUMBER
%token <int> HEX
%token <std::string> MNM0
%token <std::string> MNM1OP
%token <std::string> MNM1REG
%token <std::string> MNM2REGOP
%token <std::string> MNM2REGREG
%token <std::string> COMMENT
%token <tokens::Initializer> initializer
%token <std::vector<tokens::Initializer>> initializers
%token <tokens::Instr0> instr0
%token <tokens::Instr1_reg> instr1_reg
%token <tokens::Instr1_op> Instr1_op
%token <tokens::Instr2_regreg> instr2_regreg
%token <tokens::Instr2_regop> instr2_regop
%token <int> operand
%token <int> operand_jmp


%printer { yyo << $$; } <*>;

%%
%start code;

code:   
    lines {}
;

lines:   
    %empty {}
|   lines line {
        drv.assemler.addLine($2);
    }
;

//!!!! labela na kraju svega?
line:
    label line {
        $$=$2;
    }
|   COMMENT "\n" line {
        $$=$3;
    }
|   exspression {
        $$=Line();
        $$.exp=$1;
    }
;

label:
    SYMBOL ":" {
        drv.assembler.addSymbol($1);
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
        $$=tokens::Directive();
        $$.symbols=$2;
        $$.tupe=DirType::GLOBAL;
    }
|   EXTERN symbols {
        $$=tokens::Directive();
        $$.symbols=$2;
        $$.tupe=DirType::EXTERN;
    }
|   SECTION SYMBOL {
        $$=tokens::Directive();
        Initializer ini;
        ini.symbol=true;
        ini.name=$2;
        $$.symbols.push_back(ini);
        $$.tupe=DirType::SECTION;
        drv.assembler.addSection($2)
        drv.assembler.symbolTable.addSection($2);
    }
|   WORD initializers {
        $$=tokens::Directive();
        $$.symbols=$2;
        $$.tupe=DirType::WORD;
        drv.assembler.addToCounter($$.symbols.size()*2);
    }
|   SKIP literal {
        $$=tokens::Directive();
        Initializer ini;
        ini.symbol=false;
        ini.value=$2;
        $$.symbols.push_back(ini);
        $$.tupe=DirType::SKIP;
        drv.assembler.addToCounter($2);
    } 
|   EQU SYMBOL "," literal {
        $$=tokens::Directive();
        Initializer ini;
        ini.symbol=false;
        ini.value=$4;
        $$.symbols.push_back(ini);
        $$.tupe=DirType::EQU;
        $$.toInitialize=$2;
        drv.assembler.addAbsoluteSymbol($2,$4);
    }
|   END {
        //postavi flag u driveru i ako je on postavljen na dalje ne obradjuj tekst
        
    }
;

symbols:
    SYMBOL {
        Initializer ini;
        ini.symbol=true;
        ini.name=$1;
        $$=std::vector<tokens::Initializer>>();
        $$.push_back(ini);
    }
|   symbols "," SYMBOL{
        $$=$1;
        Initializer ini;
        ini.symbol=true;
        ini.name=$3;
        $$.push_back(ini);
    }

;

initializers:
    initializers "," SYMBOL {
        Initializer ini;
        ini.symbol=true;
        ini.name=$3;
        $$=$1;
        $$.push_back(ini);
    }
|   initializers "," literal {
        Initializer ini;
        ini.symbol=false;
        ini.value=$3;
        $$=$1;
        $$.push_back(ini);
    }
|   literal {
        Initializer ini;
        ini.symbol=false;
        ini.value=$1;
        $$=std::vector<tokens::Initializer>>();
        $$.push_back(ini);
    }
|   SYMBOL {
        Initializer ini;
        ini.symbol=true;
        ini.name=$1;
        $$=std::vector<tokens::Initializer>>();
        $$.push_back(ini);
    }
;

literal:
    NUMBER {
        $$=$1;
    }
|   "-" NUMBER {
        $$=-$2;
    }
|   HEX {
        $$=$1;
    }
|   "-" HEX {
        $$=-$2;
    }
;
instruction:
    MNM0
|   MNM1OP operand_jmp
|   MNM1REG REG
|   MNM2REGOP REG "," operand
|   MNM2REGREG REG "," REG
;

operand_jmp:
    literal {
        $$=$1;
    }
|   SYMBOL {
        //uzmi za vrednost simbola iz tabele simbola, apsolutno adresiranje

    }
|   "%" SYMBOL{
        //pc relativno adresiranje
    }
|   "*" literal {
        //sa adrese u memoriji koja ima vr literala
    }
|   "*" SYMBOL {
        //sa adrese u memoriji koja ima vrednost simbola
    }
|   "*" REG {
        //vrednost iz registra
    }
|   "*" "[" REG "]" {
        //vrednost iz memorije adresa iz registra
    }
|   "*" "[" REG "+" literal "]" {
        //vrednost iz memorije adresa iz registra +literal
    }
|   "*" "[" REG "+" SYMBOL "]" {
        //vrednost iz memorije adresa iz registra + symbol
    }

;

operand:
    "$" literal {
        $$=$2;
    }
|   "$" SYMBOL {
        //uzmi za vrednost simbola iz tabele simbola, apsolutno adresiranje

    }
|   "%" SYMBOL{
        //pc relativno adresiranje
    }
|   literal {
        //sa adrese u memoriji koja ima vr literala
    }
|   SYMBOL {
        //sa adrese u memoriji koja ima vrednost simbola
    }
|   REG {
        //vrednost iz registra
    }
|   "[" REG "]" {
        //vrednost iz memorije adresa iz registra
    }
|   "[" REG "+" literal "]" {
        //vrednost iz memorije adresa iz registra +literal
    }
|   "[" REG "+" SYMBOL "]" {
        //vrednost iz memorije adresa iz registra + symbol
    }

;

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