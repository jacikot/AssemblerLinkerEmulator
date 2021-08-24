# include "emulator.h"
# include <vector>
# include <map>
# include "cpu.h"

void Emulator::storeToOperand(int addr, int regs){
    short val=cpu.getReg(REGD(regs));
    switch(ADDRL(addr)){
        case Addressing::MEMDIR: 
            short a=memory.read2(cpu.getPC2());
            memory.store2(a,val);
            return;
        case Addressing::REGDIR:
            cpu.setReg(REGS(regs),val);
            return;
        case Addressing::REGIND:
            short a=cpu.getReg(REGS(regs));
            switch(ADDRH(addr)){
                case 0b0000: break;
                case 0b0001:
                    a-=2;
                case 0b0011:
                    cpu.addend(REGS(reg),-2);
                    break;
                case 0b0010:
                    a+=2;
                case 0b0100:
                    cpu.addend(REGS(reg),2);
                    break;
            }
            memory.store2(a,val);
            return;
        case Addressing::REGINDPOM: 
            short a=cpu.getReg(REGS(regs))+ memory.read2(cpu.getPC2());
            switch(ADDRH(addr)){
                case 0b0000: break;
                case 0b0001:
                    a-=2;
                case 0b0011:
                    cpu.addend(REGS(reg),-2);
                    break;
                case 0b0010:
                    a+=2;
                case 0b0100:
                    cpu.addend(REGS(reg),2);
                    break;
            }
            return memory.store2(a,val);
        default:
            //error - impossible to store immed and regdirpom
            return;
}

int Emulator::getOperand(int addr, int regs){
    switch(ADDRL(addr)){
        case Addressing::IMMED: 
            return memory.read2(cpu.getPC2());
        case Addressing::MEMDIR: 
            short a=memory.read2(cpu.getPC2());
            return memory.read2(a);
        case Addressing::REGDIR: 
            return cpu.getReg(REGS(regs));
        case Addressing::REGIND:
            short a=cpu.getReg(REGS(regs));
            switch(ADDRH(addr)){
                case 0b0000: break;
                case 0b0001:
                    a-=2;
                case 0b0011:
                    cpu.addend(REGS(reg),-2);
                    break;
                case 0b0010:
                    a+=2;
                case 0b0100:
                    cpu.addend(REGS(reg),2);
                    break;
            }
            return memory.read2(a);
        case Addressing::REGINDPOM: 
            short a=cpu.getReg(REGS(regs))+ memory.read2(cpu.getPC2());
            switch(ADDRH(addr)){
                case 0b0000: break;
                case 0b0001:
                    a-=2;
                case 0b0011:
                    cpu.addend(REGS(reg),-2);
                    break;
                case 0b0010:
                    a+=2;
                case 0b0100:
                    cpu.addend(REGS(reg),2);
                    break;
            }
            return memory.read2(a);
        case Addressing::REGDIRPOM: 
            return cpu.getReg(REGS(regs))+ memory.read2(cpu.getPC2());
        default:
            //error
            return -1;
    }
}

int Emulator::emulate(){
    if(readInput()<0)return -1;
    memory.initialize(content);
    while(!finished){
        char byte=memory.read1(cpu.getPC());
        switch(byte){
            case InstructionType::HALT:
                finished=true;
                break;
            case InstructionType::IRET:
                pop(pswr);
            case InstructionType::RET:
                pop(pc);
                break;
            case InstructionType::INT:
                char reg=memory.read1(cpu.getPC());
                push(pswr);
                short operand=memory.read2((cpu.getReg(REGD(reg))%8)*2);
                cpu.setReg(pc,operand);
                break;
            case InstructionType::CALL:
                push(pc);
            case InstructionType::JMP:
                char reg=memory.read1(cpu.getPC());
                char addr=memory.read1(cpu.getPC());
                short operand=getOperand(addr,reg);
                cpu.jmp(operand);
                break;
            case InstructionType::JEQ:
                char reg=memory.read1(cpu.getPC());
                char addr=memory.read1(cpu.getPC());
                short operand=getOperand(addr,reg);
                cpu.jeq(operand);
                break;
            case InstructionType::JNE:
                char reg=memory.read1(cpu.getPC());
                char addr=memory.read1(cpu.getPC());
                short operand=getOperand(addr,reg);
                cpu.jne(operand);
                break;
            case InstructionType::JGT:
                char reg=memory.read1(cpu.getPC());
                char addr=memory.read1(cpu.getPC());
                short operand=getOperand(addr,reg);
                cpu.jgt(operand);
                break;
            case InstructionType::XCHG:
                char reg=memory.read1(cpu.getPC());
                cpu.xchg(REGD(reg),REGS(reg));
                break;
            case InstructionType::ADD:
                char reg=memory.read1(cpu.getPC());
                cpu.add(REGD(reg),REGS(reg));
                break;
            case InstructionType::SUB:
                char reg=memory.read1(cpu.getPC());
                cpu.sub(REGD(reg),REGS(reg));
                break;
            case InstructionType::MUL:
                char reg=memory.read1(cpu.getPC());
                cpu.mul(REGD(reg),REGS(reg));
                break;
            case InstructionType::DIV:
                char reg=memory.read1(cpu.getPC());
                cpu.div(REGD(reg),REGS(reg));
                break;
            case InstructionType::CMP:
                char reg=memory.read1(cpu.getPC());
                cpu.cmp(REGD(reg),REGS(reg));
                break;
            case InstructionType::AND:
                char reg=memory.read1(cpu.getPC());
                cpu.andop(REGD(reg),REGS(reg));
                break;
            case InstructionType::OR:
                char reg=memory.read1(cpu.getPC());
                cpu.orop(REGD(reg),REGS(reg));
                break;
            case InstructionType::XOR:
                char reg=memory.read1(cpu.getPC());
                cpu.xorop(REGD(reg),REGS(reg));
                break;
            case InstructionType::NOT:
                char reg=memory.read1(cpu.getPC());
                cpu.notop(REGD(reg));
                break;
            case InstructionType::TEST:
                char reg=memory.read1(cpu.getPC());
                cpu.test(REGD(reg),REGS(reg));
                break;
            case InstructionType::SHL:
                char reg=memory.read1(cpu.getPC());
                cpu.shl(REGD(reg),REGS(reg));
                break;
            case InstructionType::SHR:
                char reg=memory.read1(cpu.getPC());
                cpu.shr(REGD(reg),REGS(reg));
                break;
            case InstructionType::LDR:
                char reg=memory.read1(cpu.getPC());
                char addr=memory.read1(cpu.getPC());
                short operand=getOperand(addr,reg);
                cpu.ldr(REGD(reg),operand);
                break;
            case InstructionType::STR:
                char reg=memory.read1(cpu.getPC());
                char addr=memory.read1(cpu.getPC());
                storeToOperand(addr,reg);
                break;
            default: 
                //error
                break;
        }
    }
    

}

void Emulator::pop(int regD){
    char reg=sp|(regD<<4);
    char addr=Addressing::REGIND|(0b0100<<4);
    short operand=getOperand(addr,reg);
    cpu.ldr(regD,operand);
}

void Emulator::push(int regD){
    char reg=sp|(regD<<4);
    char addr=Addressing::REGIND|(0b0001<<4);
    storeToOperand(addr,reg);
}

int Emulator::readInput(){
    if(reader.open(inputFile)<0)return -1;
    content=reader.read();
    reader.close();
    return 0;
}
