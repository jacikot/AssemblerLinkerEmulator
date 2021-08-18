 # include "../h/tokens.h"
 # include "../h/assembler.h"

using namespace tokens;



//GLOBAL, EXTERN, SECTION, SKIP, WORD, EQU
 int Directive::secondPass(Assembler* asmb){
     switch(type){
         case  DirType::GLOBAL: 
            for(Initializer ini:symbols){
                asmb->setGlobalSymbol(ini.name);
            }
            break;
         case  DirType::EXTERN: break;
         case  DirType::SECTION: 
            break;
         case  DirType::SKIP: break;
         case  DirType::WORD: break;
         case  DirType::EQU: break;
     }
     return 0;
 }


 int Instr0::secondPass(Assembler* asmb){
     switch (mnmMap.find(mnemonic)->second)
     {
        case InstructionType::HALT: break;
        case InstructionType::IRET: break;
        case InstructionType::RET: break;
     }
     return 0;
 }
 int Instr1_op::secondPass(Assembler* asmb){
     switch (mnmMap.find(mnemonic)->second)
     {
        case InstructionType::CALL: break;
        case InstructionType::JMP: break;
        case InstructionType::JEQ: break;
        case InstructionType::JNE: break;
        case InstructionType::JGT: break;
     }
     return 0;
 }
 int Instr1_reg::secondPass(Assembler* asmb){
     switch (mnmMap.find(mnemonic)->second)
     {
        case InstructionType::PUSH: break;
        case InstructionType::POP: break;
        case InstructionType::NOT: break;
        case InstructionType::INT: break;
     }
     return 0;
 }
 int Instr2_regreg::secondPass(Assembler* asmb){
     switch (mnmMap.find(mnemonic)->second)
     {
        case InstructionType::XCHG: break;
        case InstructionType::ADD: break;
        case InstructionType::SUB: break;
        case InstructionType::MUL: break;
        case InstructionType::DIV: break;
        case InstructionType::CMP: break;
        case InstructionType::AND: break;
        case InstructionType::OR: break;
        case InstructionType::XOR: break;
        case InstructionType::TEST: break;
        case InstructionType::SHL: break;
        case InstructionType::SHR: break;
     }
     return 0;
 }
 int Instr2_regop::secondPass(Assembler* asmb){
     switch (mnmMap.find(mnemonic)->second)
     {
        case InstructionType::LDR: break;
        case InstructionType::STR: break;
     }
     return 0;
 }

 std::map<std::string,InstructionType> Instruction::mnmMap;
bool Instruction::initialized=false;
void Instruction::initializeMap(){
    mnmMap.insert({"halt",InstructionType::HALT});
    mnmMap.insert({"iret",InstructionType::IRET});
    mnmMap.insert({"ret",InstructionType::RET});
    mnmMap.insert({"call",InstructionType::CALL});
    mnmMap.insert({"jmp",InstructionType::JMP});
    mnmMap.insert({"jeq",InstructionType::JEQ});
    mnmMap.insert({"jne",InstructionType::JNE});
    mnmMap.insert({"jgt",InstructionType::JGT});
    mnmMap.insert({"int",InstructionType::INT});
    mnmMap.insert({"push",InstructionType::PUSH});
    mnmMap.insert({"pop",InstructionType::POP});
    mnmMap.insert({"not",InstructionType::NOT});
    mnmMap.insert({"xchg",InstructionType::XCHG});
    mnmMap.insert({"add",InstructionType::ADD});
    mnmMap.insert({"sub",InstructionType::SUB});
    mnmMap.insert({"mul",InstructionType::MUL});
    mnmMap.insert({"div",InstructionType::DIV});
    mnmMap.insert({"cmp",InstructionType::CMP});
    mnmMap.insert({"and",InstructionType::AND});
    mnmMap.insert({"or",InstructionType::OR});
    mnmMap.insert({"xor",InstructionType::XOR});
    mnmMap.insert({"test",InstructionType::TEST});
    mnmMap.insert({"shl",InstructionType::SHL});
    mnmMap.insert({"shr",InstructionType::SHR});
    mnmMap.insert({"ldr",InstructionType::LDR});
    mnmMap.insert({"str",InstructionType::STR});
}