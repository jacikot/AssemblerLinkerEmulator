%skeleton "lalr1.cc" // -*- C++ -*-
//%require "3.7.6"
%defines

%define api.token.raw
%define api.token.constructor
%define api.value.type variant
//%define parse.assert

%code requires {
  # include <string>
  # include "../h/tokens.h"
  class Driver;
}

// The parsing context.
%param { Driver& drv }

%code {
# include "../h/driver.h"
}

%locations

%define parse.trace
%define parse.error verbose

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
  GLOBAL  
  EXTERN  
  SECTION 
  WORD    
  SKIP    
  EQU     
  REG_PC  "pc"
  REG_SP  "sp"
  REG_PSW "psw"
  YYEOF 0
;

%token <std::string> REG
%token <std::string> SYMBOL
%token <int> NUMBER
%token <int> HEX
%token <std::string> MNM0
%token <std::string> MNM1OP
%token <std::string> MNM1REG
%token <std::string> MNM2REGOP
%token <std::string> MNM2REGREG
%token <std::string> COMMENT

%type <std::string> lines
%type <tokens::Line> line
%type <std::string> label
%type <int> literal
%type <tokens::Expression*> expression
%type <tokens::Directive*> directive
%type <tokens::Instruction*> instruction
%type <std::vector<tokens::Initializer>> symbols
%type <std::vector<tokens::Initializer>> initializers
%type <tokens::Operand> operand
%type <tokens::Operand> operand_jmp


//%printer { yyo << $$; } <*>;

%%
%start code;

code:   
    lines {}
;

lines:   
    %empty {}
|   lines line {
        drv.assembler.addLine($2);
    }
;

//!!!! labela na kraju svega?
line:
    %empty {}
|   label line {
        $$=$2;
    }
|   COMMENT line {
        $$=$2;
    }
|   expression {
        $$=tokens::Line();
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
        $$=new tokens::Directive();
        $$->symbols=$2;
        $$->type=tokens::DirType::GLOBAL;
    }
|   EXTERN symbols {
        $$=new tokens::Directive();
        $$->symbols=$2;
        $$->type=tokens::DirType::EXTERN;
        for (tokens::Initializer i:$2){
            drv.assembler.addUndefinedSymbol(i.name);
        }
    }
|   SECTION SYMBOL {
        $$=new tokens::Directive();
        tokens::Initializer ini;
        ini.symbol=true;
        ini.name=$2;
        $$->symbols.push_back(ini);
        $$->type=tokens::DirType::SECTION;
        drv.assembler.addSection($2);
    }
|   WORD initializers {
        $$=new tokens::Directive();
        $$->symbols=$2;
        $$->type=tokens::DirType::WORD;
        drv.assembler.addToCounter($$->symbols.size()*2);
    }
|   SKIP literal {
        $$=new tokens::Directive();
        tokens::Initializer ini;
        ini.symbol=false;
        ini.value=$2;
        $$->symbols.push_back(ini);
        $$->type=tokens::DirType::SKIP;
        drv.assembler.addToCounter($2);
    } 
|   EQU SYMBOL "," literal {
        $$=new tokens::Directive();
        tokens::Initializer ini;
        ini.symbol=false;
        ini.value=$4;
        $$->symbols.push_back(ini);
        $$->type=tokens::DirType::EQU;
        $$->toInitialize=$2;
        drv.assembler.addAbsoluteSymbol($2,$4);
    }
;

symbols:
    SYMBOL {
        tokens::Initializer ini;        
        ini.symbol=true;
        ini.name=$1;
        $$=std::vector<tokens::Initializer>();
        $$.push_back(ini);
    }
|   symbols "," SYMBOL{
        $$=$1;
        tokens::Initializer ini;
        ini.symbol=true;
        ini.name=$3;
        $$.push_back(ini);
    }

;

initializers:
    initializers "," SYMBOL {
        tokens::Initializer ini;
        ini.symbol=true;
        ini.name=$3;
        $$=$1;
        $$.push_back(ini);
    }
|   initializers "," literal {
        tokens::Initializer ini;
        ini.symbol=false;
        ini.value=$3;
        $$=$1;
        $$.push_back(ini);
    }
|   literal {
        tokens::Initializer ini;
        ini.symbol=false;
        ini.value=$1;
        $$=std::vector<tokens::Initializer>();
        $$.push_back(ini);
    }
|   SYMBOL {
        tokens::Initializer ini;
        ini.symbol=true;
        ini.name=$1;
        $$=std::vector<tokens::Initializer>();
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
    MNM0 {
        tokens::Instr0* inst=new tokens::Instr0();
        inst->mnemonic=$1;
        $$=inst;
    }
|   MNM1OP operand_jmp {
        tokens::Instr1_op*inst=new tokens::Instr1_op();
        inst->mnemonic=$1;
        inst->operand=$2;
        $$=inst;
    }
|   MNM1REG REG {
        tokens::Instr1_reg*inst=new tokens::Instr1_reg();
        inst->mnemonic=$1;
        inst->reg=$2;
        $$=inst;
    }
|   MNM2REGOP REG "," operand {
        tokens::Instr2_regop*inst=new tokens::Instr2_regop();
        inst->mnemonic=$1;
        inst->reg=$2;
        inst->operand=$4;
        $$=inst;
    }
|   MNM2REGREG REG "," REG{
        tokens::Instr2_regreg*inst=new tokens::Instr2_regreg();
        inst->mnemonic=$1;
        inst->regDST=$2;
        inst->regSRC=$4;
        $$=inst;
    }
;

operand_jmp:
    literal {
        tokens::Initializer ini;
        ini.symbol=false;
        ini.value=$1;
        $$=tokens::Operand();
        $$.adr=tokens::Addressing::IMMED;
        $$.ini=ini;
    }
|   SYMBOL {
        tokens::Initializer ini;
        ini.symbol=true;
        ini.name=$1;
        $$=tokens::Operand();
        $$.adr=tokens::Addressing::IMMED;
        $$.ini=ini;
    }
|   "%" SYMBOL{
        tokens::Initializer ini;
        ini.symbol=true;
        ini.name=$2;
        $$=tokens::Operand();
        $$.adr=tokens::Addressing::PCREL;
        $$.ini=ini;
    }
|   "*" literal {
        tokens::Initializer ini;
        ini.symbol=false;
        ini.value=$2;
        $$=tokens::Operand();
        $$.adr=tokens::Addressing::MEMDIR;
        $$.ini=ini;
    }
|   "*" SYMBOL {
        tokens::Initializer ini;
        ini.symbol=true;
        ini.name=$2;
        $$=tokens::Operand();
        $$.adr=tokens::Addressing::MEMDIR;
        $$.ini=ini;
    }
|   "*" REG {
        $$=tokens::Operand();
        $$.adr=tokens::Addressing::REGDIR;
        $$.reg=$2;
    }
|   "*" "[" REG "]" {
        $$=tokens::Operand();
        $$.adr=tokens::Addressing::REGIND;
        $$.reg=$3;
    }
|   "*" "[" REG "+" literal "]" {
        tokens::Initializer ini;
        ini.symbol=false;
        ini.value=$5;
        $$=tokens::Operand();
        $$.adr=tokens::Addressing::REGINDPOM;
        $$.ini=ini;
        $$.reg=$3;
    }
|   "*" "[" REG "+" SYMBOL "]" {
        tokens::Initializer ini;
        ini.symbol=true;
        ini.name=$5;
        $$=tokens::Operand();
        $$.adr=tokens::Addressing::REGINDPOM;
        $$.ini=ini;
        $$.reg=$3;
    }

;

operand:
    "$" literal {
        tokens::Initializer ini;
        ini.symbol=false;
        ini.value=$2;
        $$=tokens::Operand();
        $$.adr=tokens::Addressing::IMMED;
        $$.ini=ini;
    }
|   "$" SYMBOL {
        tokens::Initializer ini;
        ini.symbol=true;
        ini.name=$2;
        $$=tokens::Operand();
        $$.adr=tokens::Addressing::IMMED;
        $$.ini=ini;

    }
|   "%" SYMBOL{
        tokens::Initializer ini;
        ini.symbol=true;
        ini.name=$2;
        $$=tokens::Operand();
        $$.adr=tokens::Addressing::PCREL;
        $$.ini=ini;
    }
|   literal {
        tokens::Initializer ini;
        ini.symbol=false;
        ini.value=$1;
        $$=tokens::Operand();
        $$.adr=tokens::Addressing::MEMDIR;
        $$.ini=ini;
    }
|   SYMBOL {
        tokens::Initializer ini;
        ini.symbol=true;
        ini.name=$1;
        $$=tokens::Operand();
        $$.adr=tokens::Addressing::MEMDIR;
        $$.ini=ini;
    }
|   REG {
        $$=tokens::Operand();
        $$.adr=tokens::Addressing::REGDIR;
        $$.reg=$1;
    }
|   "[" REG "]" {
        $$=tokens::Operand();
        $$.adr=tokens::Addressing::REGIND;
        $$.reg=$2;
    }
|   "[" REG "+" literal "]" {
        tokens::Initializer ini;
        ini.symbol=false;
        ini.value=$4;
        $$=tokens::Operand();
        $$.adr=tokens::Addressing::REGINDPOM;
        $$.ini=ini;
        $$.reg=$2;
    }
|   "[" REG "+" SYMBOL "]" {
        tokens::Initializer ini;
        ini.symbol=true;
        ini.name=$4;
        $$=tokens::Operand();
        $$.adr=tokens::Addressing::REGINDPOM;
        $$.ini=ini;
        $$.reg=$2;
    }

;

%%

void yy::parser::error (const location_type& l, const std::string& m)
{
  std::cerr << l << ": " << m << '\n';
};

