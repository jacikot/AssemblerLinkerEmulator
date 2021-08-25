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
        CPU(){
            regs[pc]=Interrupts::ENTRY;
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

        void setReg(int id, short data){
            regs[id]=data;
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

        void xchg(int dst,int src){
            short tmp=regs[dst];
            regs[dst]=regs[src];
            regs[src]=tmp;
        }

        void add(int dst,int src){
            regs[dst]+=regs[src];
        }

        void sub(int dst,int src){
            regs[dst]-=regs[src];
        }

        void mul(int dst,int src){
            regs[dst]*=regs[src];
        }

        void div(int dst,int src){
            regs[dst]/=regs[src];
        }

        void cmp(int dst,int src){
            short j = -regs[1];
            unsigned tmp=(unsigned short)regs[dst]+(unsigned short)j;
            //z
            if(tmp==0) psw|=zmask;
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


        void orop(int dst, int src){
            regs[dst]|=regs[src];
        }

        void xorop(int dst, int src){
            regs[dst]^=regs[src];
        }

        void notop(int dst){
            regs[dst]=~regs[dst];
        }

        void andop(int dst, int src){
            regs[dst]&=regs[src];
        }

        void test(int dst, int src){
            short tmp=regs[dst]&regs[src];
            //z
            if(tmp==0) psw|=zmask;
            else psw&=~zmask;
            //n
            if(tmp&0x8000) psw|=nmask;
            else psw&=~nmask;
        }

        void shl(int dst, int src){
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

        void shr(int dst, int src){
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

        void ldr(int reg,int val){
            regs[reg]=val;
        }

        void notifyInterrupt(int num){
            if(num>7)return;
            interrupts[num]=true;
        }

        int interruptExist(){
            if((psw&imask))return -1;
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


    private:
        short regs[9];
        bool interrupts[8];
};


# endif