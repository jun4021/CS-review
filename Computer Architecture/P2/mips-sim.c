#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<arpa/inet.h>

typedef struct R_type{

    unsigned long op: 6;
    unsigned long rs: 5;
    unsigned long rt: 5;
    unsigned long rd: 5;
    unsigned long shamt: 5;
    unsigned long funct: 6;

}R_type;

typedef struct I_type{

    unsigned long op: 6;
    unsigned long rs: 5;
    unsigned long rt: 5;
    unsigned short constant: 16;

}I_type;

typedef struct J_type{

    unsigned long op: 6;
    unsigned long address: 26;
}J_type;

int regist[32]={0,};
unsigned int pc = 0;

unsigned int* in_memory;
unsigned char* da_memory;



void R_read(R_type * R){
    /* Shift operation */
    int address =0;
    int temp1 =0;
    unsigned int rt = regist[R->rt];
    unsigned int rs = regist[R->rs];
    switch (R->funct)
    {
    case 0: // sll
        
        regist[R->rd] = (regist[R->rt] << R->shamt);

        break;
    case 2: // srl
        
        regist[R->rd] = (rt >> R->shamt);

        break;
    case 3: // sra
        break;
    case 4: //sllv
        break;
    case 6: //srlv
        break;
    case 7: //srav
        break;

    case 8: //jr
        pc = regist[R->rs];
     
        break;

    case 9: //jalr
        break;
    case 12: //syscall
        switch(regist[2]){
            case 1:
                printf("%d",regist[4]);
                break;
            case 4:
                address = regist[4];
                if(address >= 0x10000000){
                    char temp = *(da_memory + address - 0x10000000);
                    
                    while(temp != '\0'){
                        printf("%c",temp);
                        address += 1;
                        temp = *(da_memory + address - 0x10000000);
                    }
                }
                break;
            case 5:
                
                scanf("%d",&temp1);
                regist[2] = temp1;
                break;
            default:
                break;
        }
        
        break;
    case 16: //mfhi
        break;
    case 17: //mthi
        break;
    case 18: //mflo
        break;
    case 19: //mtlo
        break;
    case 24: //mult
        break;
    case 25: //multu
        break;
    case 26: //div
        break;
    case 27: //divu
        break;

    case 32: //add
        
        regist[R->rd] = (regist[R->rs] + regist[R->rt]);
        break;
    case 33: //addu
        
        regist[R->rd] = (regist[R->rs] + regist[R->rt]);
        break;
    case 34: //sub
        
        regist[R->rd] = (regist[R->rs] - regist[R->rt]);
        break;
    case 35: //subu
        
        regist[R->rd] = (regist[R->rs] - regist[R->rt]);
        break;
    case 36: //and
        
        regist[R->rd] = (regist[R->rs] & regist[R->rt]);
        break;
    case 37: //or
        
        regist[R->rd] = (regist[R->rs] | regist[R->rt]);
        break;

    case 38: //xor
        break;
    case 39: //nor
        break;

    case 42: //slt
        
        regist[R->rd] = (regist[R->rs] < regist[R->rt]);
        break;

    case 43: //sltu
        
        regist[R->rd] = (rs < rt);
        break;        

    default: //unknown
        
        break;
    }

}

void J_read(J_type * J){
    int address = 0;
    switch (J->op)
    {
    case 2: // j
        
        address = (pc & 0xf0000000) + J->address << 2;
        
       
        pc = address;
        
        break;
    case 3: // jal
        address = (pc & 0xf0000000) + J->address << 2;
        regist[31] = pc;
        pc = address;
        
        break;
    default:
        break;
    }
   
    
}

void I_read(I_type * I){
    unsigned int address;
    unsigned int imm;
    short imme = I->constant;
    switch (I->op)
    {
    case 4: // beq
        
        if(regist[I->rs] == regist[I->rt]){ 
            signed short imm = I->constant;
            pc+= imm *4;
        }
        break;
    case 5: // bne
        
        if(regist[I->rs] != regist[I->rt]){ 
            signed short imm = I->constant;
            pc+= imm *4;
        }
        
        break;
    case 8: // addi *
        
        regist[I->rt] = regist[I->rs] + imme;

        break;
    case 9: // addiu
        
        regist[I->rt] = regist[I->rs] + imme;
        


        break;
    case 10: // slti *
        regist[I->rt] = (regist[I->rs] < I->constant);

        break;
    case 11: // sltiu
        imm = I->constant;
        regist[I->rt] = (regist[I->rs] < imm);
        break;
    case 12: // andi *
        regist[I->rt] = (regist[I->rs] & I->constant);

        break;
    case 13: // ori *
        regist[I->rt] = (regist[I->rs] | I->constant);
      
        break;
    case 14: // xori

        break;
    case 15: // lui *
        regist[I->rt] = I->constant<<16;
        break;
    
    case 32: // lb

        break;
    case 33: // lh

        break;    
    case 35: // lw
       
        address = regist[I->rs]+I->constant;
        
        if(address >= 0x10000000){
        
            int temp = *(int*)(da_memory + address - 0x10000000);
            temp = ntohl(temp);
            regist[I->rt] = temp;
        }

        else{
            int temp = *(int*)(in_memory + address);
            temp = ntohl(temp);
            regist[I->rt] = temp;
        }

        break;    
    case 36: // lbu
        break;    
    case 37: // lhu

        break;    
    case 40: // sb

        break;    
    case 41: // sh

        break;
    case 43: // sw
        address = regist[I->rs]+I->constant;
        if(address >= 0x10000000){
            int temp = regist[I->rt];
            for(int i=3;i>=0;i--){
                *(da_memory + address - 0x10000000 +i) = temp %0x100;
                temp = temp >> 8;
            }
        }
        else{
            printf("x\n");
        }

        break;    
        
    
    default:
        printf("unknown instruction ");
        break;
    }

    
}

void R_type_trans(unsigned int inst, R_type * R){
    R->funct = (inst&0x3F); // 6 bits funct
    inst = inst >> 6;

    R->shamt = (inst&0x1F); // 5 bits shamt 
    inst = inst >> 5;
    
    R->rd = (inst&0x1F);
    inst = inst >> 5;

    R->rt = (inst&0x1F);
    inst = inst >> 5;

    R->rs = (inst&0x1F);
    inst = inst >> 5;

    R->op = (inst&0x3F);
}

void I_type_trans(unsigned int inst, I_type * I){

    I->constant = (inst&0xFFFF); // 16 bits 
    inst = inst >> 16;

    I->rt = (inst&0x1F); // 5 bits  
    inst = inst >> 5;
    
    I->rs = (inst&0x1F);
    inst = inst >> 5;

    
    I->op = (inst&0x3F);

}

void J_type_trans(unsigned int inst, J_type * J){
    J->address = (inst&0x3FFFFFF); // 26 bits 
    inst = inst >> 26;

    J->op = (inst&0x3F);
}

void type_check(unsigned int inst){
    unsigned int temp = inst;
    inst = inst >> 26;
    switch (inst)
    {
        case 0:
        {
            /*R_type*/
            R_type *instruction1 = malloc(sizeof(R_type));
            R_type_trans(temp,instruction1);
            R_read(instruction1);
            break;
        }
        case 2:        
        case 3:
        {
            /*J_type*/
            J_type *instruction2 = malloc(sizeof(J_type));
            J_type_trans(temp,instruction2);
            J_read(instruction2);
        }
            break;
        default:
        {
            /*I-type*/
            I_type *instruction3 = malloc(sizeof(I_type));
            I_type_trans(temp,instruction3);
            I_read(instruction3);
            break;
        }
    } 
}

void print_reg(){
    for(int i=0;i<32;i++){
        printf("$%d: 0x%08x \n", i,regist[i]);
    }
    printf("PC: 0x%08x\n",pc);
}

void print_data(){
    for(int i=0;i<100;i++)
        printf("%x ",da_memory[i]);
}

int main(int argc, char* argv[])
{
    FILE *fp =0;
    int read_flag = 0;
    int inst_num = 0;
    int num = atoi(argv[1]); // argv[1]

    in_memory = malloc(sizeof(int)*16384);
    memset(in_memory,0xffffffff,16384);
    da_memory = malloc(sizeof(char)*65536);
    memset(da_memory,0xff,65536);
    
    /* Data file */
    FILE * fp2 = 0;
    fp2 = fopen(argv[3],"rb"); // argv[3]
    if (fp2 != 0){
        read_flag =fread(da_memory,65536,1,fp2);
        
    }

    /*instruction */
    fp = fopen(argv[2],"rb"); //argv[2]
    fread(in_memory,16384,1,fp);
    fclose(fp);

    if (fp == 0){
        printf("Error: Cannot Open");
        return 0;
    }
    
  
    for(int i=0;i<num;i++){        

        int inst = *(in_memory + pc/4);
        inst = ntohl(inst);
        pc +=4;
        if(inst==0xffffffff){
            printf("unknown instruction\n");

            break;
        }
            
        type_check(inst);
     
    }
    /*Print output*/
    print_reg();
    return 0;

}
