# ifndef CPU_H
# define CPU_H

# define pc 7
# define sp 6


# define zmask 0x1
# define omask 0x2
# define cmask 0x4
# define nmask 0x8

# define trmask 0x2000
# define tlmask 0x4000
# define imask 0x8000



enum IVTEntries{
    ENTRY=0,
    ERROR=1,
    TIMER=2,
    TERMINAL=3
};


class CPU{
    public:
        CPU(){
            regs[pc]=IVTEntries::ENTRY;
        }
        short getPC(){
            return regs[pc]++;
        }
        short getPC2(){
            regs[pc]+=2;
            return regs[pc]-2;
        }

        short getReg(int id){
            return regs[id];
        }

        void addend(int reg,int num){
            regs[reg]+=num;
        }

        void jmp(int addr){
            regs[pc]=addr;
        }

        void jeq(int addr){
            if(psw&zmask)regs[pc]=addr;
        }

        void jne(int addr){
            if(!(psw&zmask))regs[pc]=addr;
        }

        void jgt(int addr){
            if(!(((psw&nmask)>>2)^(psw&omask)|psw&zmask)) regs[pc]=addr;
        }
    private:
        short regs[8];
        short psw;
};


# endif