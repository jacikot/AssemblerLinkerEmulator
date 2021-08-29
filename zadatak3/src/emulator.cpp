# include "../inc/emulator.h"
# include "../inc/cpu.h"
# include "../inc/exceptions.h"

# include <iostream>
# include <vector>
# include <map>


void Emulator::storeToOperand(int addr, int regs){
    short val=cpu.getReg(REGD(regs));
    unsigned short a;
    switch(ADDRL(addr)){
        case Addressing::MEMDIR: 
            a=memory.read2(cpu.getPC2());
            memory.store2(a,val);
            return;
        case Addressing::REGDIR:
            cpu.setReg(REGS(regs),val);
            return;
        case Addressing::REGIND:
            a=cpu.getReg(REGS(regs));
            switch(ADDRH(addr)){
                case 0b0000: break;
                case 0b0001:
                    a-=2;
                case 0b0011:
                    cpu.addend(REGS(regs),-2);
                    break;
                case 0b0010:
                    a+=2;
                case 0b0100:
                    cpu.addend(REGS(regs),2);
                    break;
            }
            memory.store2(a,val);
            return;
        case Addressing::REGINDPOM: 
            a=memory.read2(cpu.getPC2())+cpu.getReg(REGS(regs));
            switch(ADDRH(addr)){
                case 0b0000: break;
                case 0b0001:
                    a-=2;
                case 0b0011:
                    cpu.addend(REGS(regs),-2);
                    break;
                case 0b0010:
                    a+=2;
                case 0b0100:
                    cpu.addend(REGS(regs),2);
                    break;
            }
            return memory.store2(a,val);
        default:
            cpu.notifyInterrupt(Interrupts::ERRORIVT);
            return;
    }
}



int Emulator::getOperand(int addr, int regs){
    unsigned short a;
    switch(ADDRL(addr)){
        case Addressing::IMMED: 
            return memory.read2(cpu.getPC2());
        case Addressing::MEMDIR: 
            a=memory.read2(cpu.getPC2());
            return memory.read2(a);
        case Addressing::REGDIR: 
            return cpu.getReg(REGS(regs));
        case Addressing::REGIND:
            a=cpu.getReg(REGS(regs));
            switch(ADDRH(addr)){
                case 0b0000: break;
                case 0b0001:
                    a-=2;
                case 0b0011:
                    cpu.addend(REGS(regs),-2);
                    break;
                case 0b0010:
                    a+=2;
                case 0b0100:
                    cpu.addend(REGS(regs),2);
                    break;
            }
            return memory.read2(a);
        case Addressing::REGINDPOM: 
            a=memory.read2(cpu.getPC2())+cpu.getReg(REGS(regs));
            switch(ADDRH(addr)){
                case 0b0000: break;
                case 0b0001:
                    a-=2;
                case 0b0011:
                    cpu.addend(REGS(regs),-2);
                    break;
                case 0b0010:
                    a+=2;
                case 0b0100:
                    cpu.addend(REGS(regs),2);
                    break;
            }
            return memory.read2(a);
        case Addressing::REGDIRPOM: 
            return memory.read2(cpu.getPC2()) +cpu.getReg(REGS(regs));
        default:
            cpu.notifyInterrupt(Interrupts::ERRORIVT);
            return -1;
    }
}

void Emulator::reset(){
    memory.initialize(content);
    unsigned short startAddr=memory.read2(Interrupts::ENTRY);
    cpu.setReg(pc,startAddr);
    cpu.setReg(sp,SP_START);
    cpu.setReg(pswr,0);
    
    terminal.init(&memory,&cpu);
    timer.init(&memory,&cpu);
}

int Emulator::init(){
    if(readInput()<0)return -1;
    memory.initialize(content);
    reset();
}

int Emulator::emulate(){
    short operand;
    while(!finished){
        unsigned char byte=memory.read1(cpu.getPC());
        char reg;
        char addr;
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
                reg=memory.read1(cpu.getPC());
                push(pc); //proveri
                push(pswr);
                cpu.maskInterrupts();
                operand=memory.read2((cpu.getReg(REGD(reg))%8)*2);
                cpu.setReg(pc,operand);
                break;
            case InstructionType::CALL:
                push(pc);
            case InstructionType::JMP:
                reg=memory.read1(cpu.getPC());
                addr=memory.read1(cpu.getPC());
                operand=getOperand(addr,reg);
                cpu.jmp(operand);
                break;
            case InstructionType::JEQ:
                reg=memory.read1(cpu.getPC());
                addr=memory.read1(cpu.getPC());
                operand=getOperand(addr,reg);
                cpu.jeq(operand);
                break;
            case InstructionType::JNE:
                reg=memory.read1(cpu.getPC());
                addr=memory.read1(cpu.getPC());
                operand=getOperand(addr,reg);
                cpu.jne(operand);
                break;
            case InstructionType::JGT:
                reg=memory.read1(cpu.getPC());
                addr=memory.read1(cpu.getPC());
                operand=getOperand(addr,reg);
                cpu.jgt(operand);
                break;
            case InstructionType::XCHG:
                reg=memory.read1(cpu.getPC());
                cpu.xchg(REGD(reg),REGS(reg));
                break;
            case InstructionType::ADD:
                reg=memory.read1(cpu.getPC());
                cpu.add(REGD(reg),REGS(reg));
                break;
            case InstructionType::SUB:
                reg=memory.read1(cpu.getPC());
                cpu.sub(REGD(reg),REGS(reg));
                break;
            case InstructionType::MUL:
                reg=memory.read1(cpu.getPC());
                cpu.mul(REGD(reg),REGS(reg));
                break;
            case InstructionType::DIV:
                reg=memory.read1(cpu.getPC());
                cpu.div(REGD(reg),REGS(reg));
                break;
            case InstructionType::CMP:
                reg=memory.read1(cpu.getPC());
                cpu.cmp(REGD(reg),REGS(reg));
                break;
            case InstructionType::AND:
                reg=memory.read1(cpu.getPC());
                cpu.andop(REGD(reg),REGS(reg));
                break;
            case InstructionType::OR:
                reg=memory.read1(cpu.getPC());
                cpu.orop(REGD(reg),REGS(reg));
                break;
            case InstructionType::XOR:
                reg=memory.read1(cpu.getPC());
                cpu.xorop(REGD(reg),REGS(reg));
                break;
            case InstructionType::NOT:
                reg=memory.read1(cpu.getPC());
                cpu.notop(REGD(reg));
                break;
            case InstructionType::TEST:
                reg=memory.read1(cpu.getPC());
                cpu.test(REGD(reg),REGS(reg));
                break;
            case InstructionType::SHL:
                reg=memory.read1(cpu.getPC());
                cpu.shl(REGD(reg),REGS(reg));
                break;
            case InstructionType::SHR:
                reg=memory.read1(cpu.getPC());
                cpu.shr(REGD(reg),REGS(reg));
                break;
            case InstructionType::LDR:
                reg=memory.read1(cpu.getPC());
                addr=memory.read1(cpu.getPC());
                operand=getOperand(addr,reg);
               cpu.ldr(REGD(reg),operand);
                break;
            case InstructionType::STR:
                reg=memory.read1(cpu.getPC());
                addr=memory.read1(cpu.getPC());
                storeToOperand(addr,reg);
                break;
            default: 
                cpu.notifyInterrupt(Interrupts::ERRORIVT);
                break;
        }
        terminal.printout(); //print out character to stdout if exist
        terminal.readin(); //read character entered by keyboard if exist
        timer.tick(); //check timer
        interrupts();
    }
}

void Emulator::interrupts(){
    int interrupt=cpu.interruptExist();
    if(interrupt==-1)return;
    if(interrupt!=0){
        push(pc);
        push(pswr);
        cpu.maskInterrupts();
        short addr=memory.read2(interrupt*2);
        cpu.setReg(pc,addr);
    }
    else{
        reset();
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
    if(reader.open(inputFile)<0){
        throw EmulatorException("Input file cannot be opened!");
    }
    content=reader.read();
    reader.close();
    return 0;
}
