# 데이터베이스개론

## 목차
1. ER Model
2. EER Model
3. Relational Model
4. Relational Algebra
5. Normalization
6. Transaction

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

## 4. Relational Algebra
1. SELECT
    - Relation에서 주어진 <condition>을 만족하는 tuple 출력.
2. PROJECT
    - Relation에서 원하는 Attribute들만 가진 tuple 출력
3. UNION, INTERSECTION, DIFFERENCE
    - 집합에서의 합집합, 교집합, 차집합과 동일
    - 두 Relation의 attibute 개수 및 domain이 같을 때.
4. CARTESIN PRODUCT
    - 두 Relation의 각각의 tuple을 모두 서로 연결하여 합침.
5. JOIN
    - 두 Relation에 속한 각 tuple 중 join condtion을 만족하는 것만 연결하여 합침.


## 5. Normalization (정규화)
- 데이터의 중복을 줄이고 anomaly 방지, 무결성 제약조건을 만족시키기 위해서

1. 1NF
    - 각 tuple은 원자값으로 되어 있다.
    - PK 로 고유하게 식별이 가능하다.

2. 2NF
    - Functinal Dependency (FD) : X에 값에 따라 Y값이 결정 될 때 ```X->Y```
    - Partial Dependency (부분 종속) : Key에 속하지 않은 Y가 키 Set X의 Subset에 의해 종속되어 있을 때. 즉, {X1,X2} -> Y 에서 X1 -> Z 일 때

    - 모든 tuple이 완전 종속이어야 한다.
    - 부분 종속의 경우 테이블을 분리해서 나타낸다.

3. 3NF
    - Transitive Dependency (이행종속) : X -> Y and Y -> Z

    - 어떤 non-prime attribute 도 key X에 의해 tranistive dependency를 만족하면 안된다.
    - 즉, 오로지 기본 키에 의존해야 한다.
    
4. BCNF
    - Super Key X로만 다른 attribute들이 결정되어야 한다.

## 6. Transaction
- Reference : https://d2.naver.com/helloworld/407507
- RDBMS에서 DB에 접근하여 수행하는 작업 단위
- 특징
    - 원자성(Atomicity) : 트랜잭션 모두가 반영되거나, 반영되지 않아야 한다.
    - 일관성(Consistency) : 트랜잭션 이후 DB의 제약, 규칙을 여전히 만족해야 한다.
    - 독립성(Isolation) : 각각의 트랜잭션은 독립적으로 실행되어야 한다.
    - 지속성(Durability) : 트랜잭션이 완료 시 결과는 영구적으로 반영되어야 한다. 

- 트랜잭션 격리 수준 (다른 트랜잭션이 관여하지 못하게 막는 것)
0. read uncommitted : 트랜잭션에서 처리중 or 커밋되지 않은 데이터 읽기 가능.
1. read committed : 커밋 이후에만 접근 가능. 그 전까지 대기(undo -> 데이터 읽음)
2. repeatable read : 한 트랜잭션에서 하나의 스냅샷만 사용.
3. Serializable : 완벽한 읽기 일관성 제공

    
## 7. Index
- 자주 조회되는 column -> index table 제작, SELECT 시 빠르게 조회할 수 있도록
- 대신 INSERT,DELETE,UPDATE 등을 실행할 때 손실 발생. 
- B tree : 자식 노드가 여러개 가능.
- B+ tree : 인덱스(non-leaf), 데이터(leaf) 노드 분리 // 빠르게 데이터(leaf) 노드를 탐색 후 데이터 노드끼리 연결리스트로 연결되어 있다는 특징이 있음(https://www.cs.usfca.edu/~galles/visualization/BPlusTree.html)
