# 데이터베이스개론

## 목차
1. ER Model

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