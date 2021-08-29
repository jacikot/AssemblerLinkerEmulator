%skeleton "lalr1.cc" // -*- C++ -*-
//%require "3.7.6"
%defines

%define api.token.raw
%define api.token.constructor
%define api.value.type variant
//%define parse.assert

%code requires {
  # include <string>
  # include "../inc/tokens.h"
  class Driver;
}

// The parsing context.
%param { Driver& drv }

%code {
# include "../inc/driver.h"
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
        drv.assembler.line++;
        drv.assembler.addLine($2);
    }
|   lines COMMENT {}
;


line:
    %empty {
        $$=tokens::Line();
    }
|   label line {
        $$=$2;
        $$.label=$1;
    }
|   expression {
        $$=tokens::Line();
        $$.exp=$1;
    }
;

label:
    SYMBOL ":" {
        drv.assembler.addSymbol($1);
        $$=$1;
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
        drv.assembler.addToCounter(1); //1B instr
    }
|   MNM1OP operand_jmp {
        tokens::Instr1_op*inst=new tokens::Instr1_op();
        inst->mnemonic=$1;
        inst->operand=$2;
        $$=inst;
    }
|   MNM1REG REG {
        if($1=="push"||$1=="pop"){
            tokens::Instr2_regop*inst=new tokens::Instr2_regop();
            inst->mnemonic=$1;
            inst->reg=$2;
            tokens::Operand op;
            op.adr=tokens::Addressing::REGIND;
            op.reg="sp";
            if($1=="push")op.addend=0b0001;
            else op.addend=0b0100;
            inst->operand=op; 
            drv.assembler.addToCounter(3);
            $$=inst;
        }
        else{
            tokens::Instr1_reg*inst=new tokens::Instr1_reg();
            inst->mnemonic=$1;
            inst->reg=$2;
            $$=inst;
            drv.assembler.addToCounter(2);
        }
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
        drv.assembler.addToCounter(2);
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
        drv.assembler.addToCounter(5); //5B instr
    }
|   SYMBOL {
        tokens::Initializer ini;
        ini.symbol=true;
        ini.name=$1;
        $$=tokens::Operand();
        $$.adr=tokens::Addressing::IMMED;
        $$.ini=ini;
        drv.assembler.addToCounter(5); //5B instr
    }
|   "%" SYMBOL{
        tokens::Initializer ini;
        ini.symbol=true;
        ini.name=$2;
        $$=tokens::Operand();
        $$.adr=tokens::Addressing::REGDIRPOM; //value not from memory pcrel - regdirpom
        $$.ini=ini;
        $$.reg="pc";
        $$.isPCREL=true;
        drv.assembler.addToCounter(5); //5B instr
    }
|   "*" literal {
        tokens::Initializer ini;
        ini.symbol=false;
        ini.value=$2;
        $$=tokens::Operand();
        $$.adr=tokens::Addressing::MEMDIR;
        $$.ini=ini;
        drv.assembler.addToCounter(5); //5B instr
    }
|   "*" SYMBOL {
        tokens::Initializer ini;
        ini.symbol=true;
        ini.name=$2;
        $$=tokens::Operand();
        $$.adr=tokens::Addressing::MEMDIR;
        $$.ini=ini;
        drv.assembler.addToCounter(5); //5B instr
    }
|   "*" REG {
        $$=tokens::Operand();
        $$.adr=tokens::Addressing::REGDIR;
        $$.reg=$2;
        drv.assembler.addToCounter(3); //3B instr
    }
|   "*" "[" REG "]" {
        $$=tokens::Operand();
        $$.adr=tokens::Addressing::REGIND;
        $$.reg=$3;
        drv.assembler.addToCounter(3); //3B instr
    }
|   "*" "[" REG "+" literal "]" {
        tokens::Initializer ini;
        ini.symbol=false;
        ini.value=$5;
        $$=tokens::Operand();
        $$.adr=tokens::Addressing::REGINDPOM;
        $$.ini=ini;
        $$.reg=$3;
        drv.assembler.addToCounter(5); //5B instr
    }
|   "*" "[" REG "+" SYMBOL "]" {
        tokens::Initializer ini;
        ini.symbol=true;
        ini.name=$5;
        $$=tokens::Operand();
        $$.adr=tokens::Addressing::REGINDPOM;
        $$.ini=ini;
        $$.reg=$3;
        drv.assembler.addToCounter(5); //5B instr
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
        drv.assembler.addToCounter(5); //5B instr
    }
|   "$" SYMBOL {
        tokens::Initializer ini;
        ini.symbol=true;
        ini.name=$2;
        $$=tokens::Operand();
        $$.adr=tokens::Addressing::IMMED;
        $$.ini=ini;
        drv.assembler.addToCounter(5); //5B instr

    }
|   "%" SYMBOL{
        tokens::Initializer ini;
        ini.symbol=true;
        ini.name=$2;
        $$=tokens::Operand();
        $$.adr=tokens::Addressing::REGINDPOM; //value from memory pcrel - regindpom
        $$.ini=ini;
        $$.reg="pc";
        $$.isPCREL=true;
        drv.assembler.addToCounter(5); //5B instr
    }
|   literal {
        tokens::Initializer ini;
        ini.symbol=false;
        ini.value=$1;
        $$=tokens::Operand();
        $$.adr=tokens::Addressing::MEMDIR;
        $$.ini=ini;
        drv.assembler.addToCounter(5); //5B instr
    }
|   SYMBOL {
        tokens::Initializer ini;
        ini.symbol=true;
        ini.name=$1;
        $$=tokens::Operand();
        $$.adr=tokens::Addressing::MEMDIR;
        $$.ini=ini;
        drv.assembler.addToCounter(5); //5B instr
    }
|   REG {
        $$=tokens::Operand();
        $$.adr=tokens::Addressing::REGDIR;
        $$.reg=$1;
        drv.assembler.addToCounter(3); //3B instr
    }
|   "[" REG "]" {
        $$=tokens::Operand();
        $$.adr=tokens::Addressing::REGIND;
        $$.reg=$2;
        drv.assembler.addToCounter(3); //3B instr
    }
|   "[" REG "+" literal "]" {
        tokens::Initializer ini;
        ini.symbol=false;
        ini.value=$4;
        $$=tokens::Operand();
        $$.adr=tokens::Addressing::REGINDPOM;
        $$.ini=ini;
        $$.reg=$2;
        drv.assembler.addToCounter(5); //5B instr
    }
|   "[" REG "+" SYMBOL "]" {
        tokens::Initializer ini;
        ini.symbol=true;
        ini.name=$4;
        $$=tokens::Operand();
        $$.adr=tokens::Addressing::REGINDPOM;
        $$.ini=ini;
        $$.reg=$2;
        drv.assembler.addToCounter(5); //5B instr
    }

;

%%

void yy::parser::error (const location_type& l, const std::string& m)
{
  std::cerr << l << ": " << m << '\n';
};

