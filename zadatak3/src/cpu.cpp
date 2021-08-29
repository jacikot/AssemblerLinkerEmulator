# include "../inc/cpu.h"
# include <iostream>
using namespace std;

CPU::CPU(){
    regs[pc]=Interrupts::ENTRY;
}
short CPU::getPC(){
    return regs[pc]++;
}
short CPU::getPC2(){
    regs[pc]+=2;
    return regs[pc]-2;
}

short CPU::getReg(int id){
    return regs[id];
}

void CPU::setReg(int id, short data){
    regs[id]=data;
}

void CPU::addend(int reg,int num){
    regs[reg]+=num;
}

void CPU::jmp(int addr){
    regs[pc]=addr;
}

void CPU::jeq(int addr){
    if(psw&zmask)regs[pc]=addr;
}

void CPU::jne(int addr){
    if(!(psw&zmask))regs[pc]=addr;
}

void CPU::jgt(int addr){
    if(!(((psw&nmask)>>2)^(psw&omask)|psw&zmask)) regs[pc]=addr;
}

void CPU::xchg(int dst,int src){
    short tmp=regs[dst];
    regs[dst]=regs[src];
    regs[src]=tmp;
}

void CPU::add(int dst,int src){
    regs[dst]+=regs[src];
}

void CPU::sub(int dst,int src){
    regs[dst]-=regs[src];
}

void CPU::mul(int dst,int src){
    regs[dst]*=regs[src];
}

void CPU::div(int dst,int src){
    regs[dst]/=regs[src];
}

void CPU::cmp(int dst,int src){
    short j = -regs[src];
    unsigned tmp=(unsigned short)regs[dst]+(unsigned short)j;
    //z
    if((tmp&0xFFFF)==0) {
        psw|=zmask;
    }
    else psw&=~zmask;
    //o
    if( 
        ((regs[dst]&0x8000)&&!(regs[src]&0x8000)&&!(tmp&0x8000))||
        (!(regs[dst]&0x8000)&&(regs[src]&0x8000)&&(tmp&0x8000))
    ) psw|=omask;
    else psw&=~omask;
    //c
    if(tmp&0x10000) psw|=cmask;
    else psw&=~cmask;
    //n
    if(tmp&0x8000) psw|=nmask;
    else psw&=~nmask;
}


void CPU::orop(int dst, int src){
    regs[dst]|=regs[src];
}

void CPU::xorop(int dst, int src){
    regs[dst]^=regs[src];
}

void CPU::notop(int dst){
    regs[dst]=~regs[dst];
}

void CPU::andop(int dst, int src){
    regs[dst]&=regs[src];
}

void CPU::test(int dst, int src){
    short tmp=regs[dst]&regs[src];
    //z
    if(tmp==0) psw|=zmask;
    else psw&=~zmask;
    //n
    if(tmp&0x8000) psw|=nmask;
    else psw&=~nmask;
}

void CPU::shl(int dst, int src){
    short tmp=regs[dst]<<(regs[src]-1);
    //c
    if(tmp&0x8000) psw|=cmask;
    else psw&=~cmask;
    regs[dst]=tmp<<1;
    //z
    if(regs[dst]==0) psw|=zmask;
    else psw&=~zmask;
    //n
    if(regs[dst]&0x8000) psw|=nmask;
    else psw&=~nmask;
}

void CPU::shr(int dst, int src){
    short tmp=regs[dst]>>(regs[src]-1);
    //c
    if(tmp&0x1) psw|=cmask;
    else psw&=~cmask;
    regs[dst]=tmp>>1;
    //z
    if(regs[dst]==0) psw|=zmask;
    else psw&=~zmask;
    //n
    if(regs[dst]&0x8000) psw|=nmask;
    else psw&=~nmask;
}

void CPU::ldr(int reg,int val){
    regs[reg]=val;
}

void CPU::notifyInterrupt(int num){
    if(num>7)return;
    interrupts[num]=true;
}

void CPU::maskInterrupts(){
    psw|=imask;
}

int CPU::interruptExist(){
    if((psw&imask)&&!interrupts[Interrupts::ERRORIVT])return -1;
    for(int i=0;i<8;i++){
        switch(i){
            case Interrupts::TIMER:
                if((psw&trmask)||!interrupts[i]) break;
                interrupts[i]=false;
                return i;
            case Interrupts::TERMINAL:
                if((psw&tlmask)||!interrupts[i]) break;
                interrupts[i]=false;
                return i;
            default:
                if(!interrupts[i]) break;
                interrupts[i]=false;
                return i;
        }
    }
    return -1;
}