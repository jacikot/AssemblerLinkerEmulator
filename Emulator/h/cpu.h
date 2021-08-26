# ifndef CPU_H
# define CPU_H

# define pc 7
# define sp 6
# define pswr 8


# define zmask 0x1
# define omask 0x2
# define cmask 0x4
# define nmask 0x8

# define trmask 0x2000
# define tlmask 0x4000
# define imask 0x8000

# define psw regs[8]


enum Interrupts{
    ENTRY=0,
    ERRORIVT=1,
    TIMER=2,
    TERMINAL=3
};


class CPU{
    public:
        CPU();

        short getPC();

        short getPC2();

        short getReg(int id);

        void setReg(int id, short data);

        void addend(int reg,int num);

        void jmp(int addr);

        void jeq(int addr);

        void jne(int addr);

        void jgt(int addr);

        void xchg(int dst,int src);

        void add(int dst,int src);

        void sub(int dst,int src);

        void mul(int dst,int src);

        void div(int dst,int src);

        void cmp(int dst,int src);


        void orop(int dst, int src);

        void xorop(int dst, int src);

        void notop(int dst);

        void andop(int dst, int src);

        void test(int dst, int src);

        void shl(int dst, int src);

        void shr(int dst, int src);

        void ldr(int reg,int val);

        void notifyInterrupt(int num);

        int interruptExist();


    private:
        short regs[9];
        bool interrupts[8];
};


# endif