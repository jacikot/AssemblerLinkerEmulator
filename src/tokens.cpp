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
            asmb->setNewSection(symbols.front().name);
            break;
         case  DirType::SKIP: 
            asmb->skip(symbols.front().value);
            break;
         case  DirType::WORD: 
            for(Initializer ini:symbols){
                if(ini.symbol){
                    asmb->initSymbol(ini.name);
                }
                else{
                    asmb->initLiteral(ini.value);
                }
            }
         break;
         case  DirType::EQU: break;
     }
     return 0;
 }


 int Instr0::secondPass(Assembler* asmb){
     asmb->initInstr0(mnmMap.find(mnemonic)->second);
     return 0;
 }
 
 int Instr1_op::secondPass(Assembler* asmb){
     asmb->initInstr2REGOP(mnmMap.find(mnemonic)->second,"UND",operand);
     return 0;
 }
 int Instr1_reg::secondPass(Assembler* asmb){
     asmb->initInstr2REGREG(mnmMap.find(mnemonic)->second,reg,"UND"); //src reg is not used
     return 0;
 }
 int Instr2_regreg::secondPass(Assembler* asmb){
     asmb->initInstr2REGREG(mnmMap.find(mnemonic)->second,regDST,regSRC); 
     return 0;
 }
 int Instr2_regop::secondPass(Assembler* asmb){
     asmb->initInstr2REGOP(mnmMap.find(mnemonic)->second,reg,operand);
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