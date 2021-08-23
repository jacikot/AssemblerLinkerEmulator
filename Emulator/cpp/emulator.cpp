# include "emulator.h"
# include <vector>
# include <map>

int Emulator::getOperand(int addr, int regs){
    switch(addr){
        case Addressing::IMMED: 
            return memory.read2(cpu.getPC2());
        case Addressing::MEMDIR: 
            short a=memory.read2(cpu.getPC2());
            return memory.read2(cpu.getPC2());
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
            case InstructionType::INT:
                char reg=memory.read1(cpu.getPC());
                REGD(reg); //nastavi ovo
            case InstructionType::JMP:
                char reg=memory.read1(cpu.getPC());
                char addr=memory.read1(cpu.getPC());
                short operand=getOperand(addr,reg);
                cpu.setPC(operand);
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
            default: 
                //error
                break;
        }
    }
    

}

int Emulator::readInput(){
    if(reader.open(inputFile)<0)return -1;
    content=reader.read();
    reader.close();
    return 0;
}
