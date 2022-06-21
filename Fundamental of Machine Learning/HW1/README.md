# Titanic - Machine Learning from Disaster

## 목표 
- Titanic dataset을 이용하여 Decision Tree, KNN, Logistic Regression 구현하기
- https://www.kaggle.com/c/titanic
-----------
## Preprocessing

- Pclass, Sex, Age, SibSp, Parch, Fare, Embarked 만을 사용. 이에 따른 survived 도출.
- Sex(female,male) : Label encoding을 통해 female: 0, male: 1 
- Embarked(C,Q,S) : One-hot encoding 이용

```python
# 필요없는 요소 drop
data = data.drop(['PassengerId','Name','Ticket','Cabin'],axis=1)

# 성별 -> label encoding
encoder1 = LabelEncoder()
encoder1.fit(data.Sex)
data.Sex = encoder1.transform(data.Sex) # female : 0, male : 1

# Embarked -> one hot encoding
data = pd.get_dummies(data, columns=['Embarked']) 

# 비어 있는 행 drop
train_data = data[:600].dropna()
test_data = data[600:].dropna()
```

```python
# Accuracy, F1-Score   
def confusionMatrix(pred):
    cm = confusion_matrix(test_Y,pred)
    print(cm)
    tp,fn,fp,tn =cm[0][0], cm[0][1], cm[1][0],cm[1][1]
    acc = (tp+tn)/(tp+fp+tn+fn)
    prec = tp/(tp+fp)
    recall = tp/(tp+fn)
    f1 = (2*prec*recall) / (prec+recall)

    print('Accurcy :{}, F1-score :{}\n'.format(acc,f1))
```
-------
## KNN

```python
from sklearn.neighbors import KNeighborsClassifier
def KNN(k):
    print("KNN (k={})".format(k))
    neigh = KNeighborsClassifier(n_neighbors=k)
    neigh.fit(train_X, train_Y)
              
    pred = neigh.predict(test_X)
    confusionMatrix(pred)
```
- Output
```
KNN (k=2)
[[129  17]
 [ 63  31]]
Accurcy :0.6666666666666666, F1-score :0.7633136094674556

KNN (k=3)
[[114  32]
 [ 38  56]]
Accurcy :0.7083333333333334, F1-score :0.7651006711409396

KNN (k=4)
[[128  18]
 [ 54  40]]
Accurcy :0.7, F1-score :0.7804878048780488

KNN (k=5)
[[119  27]
 [ 40  54]]
Accurcy :0.7208333333333333, F1-score :0.7803278688524591

```

---------
## Logistic Regression

```python
def logistic(regular,max_iter,C):
    print("max_iter = {}, C = {}".format(max_iter,C))
    log = LogisticRegression(max_iter = max_iter,C=C)
    if(regular):    
        log.fit(X_train_sclaed,train_Y)
        pred = log.predict(X_test_sclaed)
    else:
        log.fit(train_X,train_Y)
        pred = log.predict(test_X)
    confusionMatrix(pred)
```
- 그대로 돌렸으나 발산하여 데이터 정규화를 하였다.
```python
# 평균 0 표준편차 1 : StandardScaler()
scaler = StandardScaler() 

X_train_sclaed = scaler.fit_transform(train_X)
X_test_sclaed = scaler.fit_transform(test_X)
```
- 결과
```
max_iter = 100, C = 1
[[126  20]
 [ 27  67]]
Accurcy :0.8041666666666667, F1-score :0.8428093645484949

max_iter = 100, C = 2
[[124  22]
 [ 27  67]]
Accurcy :0.7958333333333333, F1-score :0.8350168350168349

max_iter = 100, C = 3
[[124  22]
 [ 27  67]]
Accurcy :0.7958333333333333, F1-score :0.8350168350168349

max_iter = 100, C = 4
[[124  22]
 [ 27  67]]
Accurcy :0.7958333333333333, F1-score :0.8350168350168349

max_iter = 100, C = 5
[[124  22]
 [ 27  67]]
Accurcy :0.7958333333333333, F1-score :0.8350168350168349

```
---------
## Decision Tree

- 적절한 max_depth를 설정함에 따라 overfitting을 방지한다.
```python
# Desicion Tree
def model_fitting(max_depth):
    model = DecisionTreeClassifier(criterion="entropy", max_depth=max_depth)
    model.fit(train_X,train_Y)

    plt.figure( figsize=(20,15) )
    tree.plot_tree(model,                
                feature_names = ['Pclass','Sex','Age','SibSp','Parch','Fare','Embarked_C','Embarked_Q','Embarked_S'],
                impurity=True, filled=True,
    )

    pred = model.predict(test_X)
    
    confusionMatrix(pred)
```
- 결과
```
depth 1
[[125  21]
 [ 34  60]]
Accurcy :0.7708333333333334, F1-score :0.8196721311475409

depth 2
[[139   7]
 [ 39  55]]
Accurcy :0.8083333333333333, F1-score :0.8580246913580246

depth 3
[[133  13]
 [ 26  68]]
Accurcy :0.8375, F1-score :0.8721311475409836

depth none
[[115  31]
 [ 29  65]]
Accurcy :0.75, F1-score :0.7931034482758622
```
![depth1](https://user-images.githubusercontent.com/86395683/174788621-39166c63-e877-4f73-b1cb-357bc2c1c9ea.png)
![depth2](https://user-images.githubusercontent.com/86395683/174788626-2981162f-c9de-422a-b045-5d88e9d3f44c.png)
![depth3](https://user-images.githubusercontent.com/86395683/174788609-003fa19d-0620-403c-8581-02774d7aae37.png)
![depth_none](https://user-images.githubusercontent.com/86395683/174788619-9c95625b-d7f5-4412-902e-84d944db1875.png)