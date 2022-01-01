# MIPS CPU simulator (Single Cycle)

## 목표 
- 주어진 instruction들을 읽고 처리하는 simulator 만들기.
-----------
## 예시
- 입력하는 instruction 
<img src="https://user-images.githubusercontent.com/86395683/147848487-58a13a93-7fa6-4478-adb0-2340becf84e0.PNG">

- assembly code
<img src="https://user-images.githubusercontent.com/86395683/147848486-f6d1d7fc-ac58-4a44-82dc-994b68932619.PNG">

- 각 register 별 결과
<img src="https://user-images.githubusercontent.com/86395683/147848488-6880fe34-707e-486e-b019-abb250f381a6.PNG">

---------
## 간단한 MIPS 소개
- MIPS instruction은 크게 세 가지 종류로 나뉜다. (R/I/J type)
    ### R-type

    |Operation|rs|rt|rd|shamt|funct|
    |----|-----|-----|-----|-----|-----|
    |6bits|5bits|5bits|5bits|5bits|6bits|

     
    * operation : 명령어를 구분하는 코드번호, R-type의 경우 0이다.
    * rs : destination register
    * rt : source register 1
    * rd : source register 2
    * shamt : shift 연산 시 필요한 인수
    * funct : R-type 명령어를 구분하기 위한 코드넘버
        
    ### I-type

    |Operation|rs|rt|constant or address|
    |-----|-----|-----|-----|
    |6bits|5bits|5bits|16bits|


    * operation : 명령어를 구분하는 코드넘버.
    * rs : destination register
    * rt : source register
    * constant : 주소나 상수를 나타내는 16 bit 수.
        
    ### J-type

    |Operation|target|
    |----|-----|
    |6bits|26bits|

    
    * operation : 명령어를 구분하는 코드넘버 (J-type은 2 or 3).
    * target : jump하는 다음 명령어의 위치를 나타내는 정보
        * 실제로 이동하는 주소는 pc의 앞 4bit에 (target<<2)를 이어 붙인 곳이다. 

    [Details](https://opencores.org/projects/plasma/opcodes)

---------

## 주의사항
1. 실제 CPU와 달리 lw, sw 명령어의 구현을 확인하기 위해 data memory를 별도로 할당 및 필요한 data 정보가 data file로 구성되어 있다. 이때 simulator 상의 memory 주소는 0x10000000 - 0x10010000 으로 이루어진다.
2. 모든 register의 초기값은 0x00000000이다.
3. simulator의 결과물은 각 register 별 값의 변화와 PC이다.
4. 필요에 의해 몇 가지 명령어는 구현하지 않았다.

---------

## 구현
1. 주어진 data file, instruction file을 주어진 메모리에 저장한다.

2. 사용자에게 입력받은 instruction 개수를 통해 한 instruction씩(32bits) 불러온다. 이때 쓰여있는 endian이 다르므로 ntohl()를 통해 바꿔 처리해준다.

3. type_check()를 통해 받은 instruction의 type을 확인하여 각 type에 맞게 trans(),read() 함수를 호출해 처리한다. 이때 type 구분은 앞 6bits 인 operation으로 하기에 받은 inst 인수를 shift 연산을 통해 operation으로 처리 후 확인하였다.

```
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
```

4. trans()는 instruction 정보를 각 type 구조체의 요소에 맞게 대입해 저장하는 함수이다. 
```
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
```
5. 그 후 read()를 통해 type 별로 명령어를 구분해 그 명령어에 맞게 처리해준다.

6. 0xFFFFFFFF를 확인하거나, 입력받은 instruction 수만큼 처리 후 print_reg()를 통해 register의 값들과 PC를 출력한다.

---------
## 결과
- linux 환경에서 컴파일 후 다음 방식으로 출력하였다.
```
$./mips-sim 100 test.inst test1.data  
```
