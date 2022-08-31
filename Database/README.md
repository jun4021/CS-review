# 데이터베이스개론

## 목차
1. ER Model
2. EER Model

## 1. ER Model
- Entity (개체)
    - ER Diagram에서 사각형으로 표시한다.
    - 각각의 Entity는 key attribute를 포함한다.
- Attribute
    - ER diagram에서 원형으로 표시한다.
- Relationship
    - 둘 이상의 Entity 사이의 관계를 나타낸다.
    - ER diagram에서 마름모로 표시한다.

- Relationship의 종류
    - 1:1, 1:M, M:N
    - Total(모든 Entity가 참여 ```=```), Partial(몇몇의 Entity만 참여 ```-```)

    ![image](https://user-images.githubusercontent.com/86395683/187480474-502e5c3e-cceb-41cf-9feb-c9e39c8a806a.png)

- Recursive Relationship
    - 같은 Entity 사이의 관계를 나타낸 것이다.
    - 서로 다른 role(역할이) 필요
    ![image](https://user-images.githubusercontent.com/86395683/187481117-3dea4a2e-d6e2-4cc6-9772-756af18fd1ee.png)

- Weak Entity 
    - 해당 Entity는 자신의 PK가 없어 다른 Entity에 종속되는 개체이다.
    - 대신 Partial Key를 보유해 다른 Owner Entity의 PK와 함께 식별한다.
    
    ### (Example) 
    ![image](https://user-images.githubusercontent.com/86395683/187482134-3749b4b9-279e-43cc-9a9c-3c4d2afee17c.png)
    - ```Players```의 partial key: ```pnumber```
    - ```Players```의 key: ```{tname, pnumber}```

## 2. EER Model
- Superclass / Subclass
    - SubClass는 Superclass의 attribute + 고유한 attribute 추가로 보유.
- Specialization / Generalization
    - Specialization : Superclass에서 고유한 attribute에 따라 subclass 분류
    - Generalization : Subclass들의 공통된 attribute을 통해 Superclass 생성 

## 3. Relational Model
![image](https://user-images.githubusercontent.com/86395683/187621553-d7b72729-7f33-4074-a68a-c4cbcdfd6a93.png)

- Key
    - Super Key: 튜플을 식별할 수 있는 유일한 Attribute Set 
    - Candidate Key: 유일성, 최소성을 가진 Attribute
    - Primary Key: Candidate key 중 하나를 선택하여 RDBM에서 튜플을 식별한다.

- Integrity Constraints
    - Key integrity: 어떤 tuple도 같은 key를 가져서는 안된다.
    - Entity Integrity: PK는 NULL일 수 없다.

- Referential integrity(참조 무결성)
    - 서로 참조하고 받는 relation(FK에 의해)에서 tuple이 INSERT, DELETE, UPDATE되는 경우 참조 무결성을 위반할 수 있다.
    - Reject하거나 CACADE를 통해 NULL, DEFAULT로 작성하여 해결 가능하다.