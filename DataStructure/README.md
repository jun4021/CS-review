# 자료구조개론

1. Stack, Queue
2. Tree
3. Graph
4. Sorting

## 1. Stack, Queue
### Stack
```Last In First Out```

```Top```만 호출 가능
### Queue
```First In First Out```

들어간 순서대로 호출 가능

### Priority Queue
```Heap```을 이용한 우선순위에 따라 정렬되는 ```Queue```

Queue에 원소를 추가, 삭제하는데 ```O(log n)``` 필요

## 2. Tree
### Binary Tree
루트 노드를 기준으로 두개 이하의 서브 트리를 갖는 자료구조
탐색 연산은 ```O(h)```로 트리의 높이와 관련되어 있다.

### Red-Black Tree
Red-Black Tree 는 다음의 성질들을 만족하는 BST 이다.

이진 트리의 편향성을 방지할 수 있다.

1. 각 노드는 ```Red``` or ```Black```이라는 색깔을 갖는다.
2. ```Root node``` 의 색깔은 ```Black```이다.
3. 각 ```leaf node``` 는 ```black```이다.
4. 어떤 노드의 색깔이 ```red```라면 두 개의 ```children``` 의 색깔은 모두 ```black``` 이다.
5. 각 노드에 대해서 노드로부터 ```descendant leaves``` 까지의 단순 경로는 모두 같은 수의 ```black nodes``` 들을 포함하고 있다. 이를 해당 노드의 ```Black-Height```라고 한다. cf) Black-Height: 노드 x 로부터 노드 x 를 포함하지 않은 leaf node 까지의 simple path 상에 있는 black nodes 들의 개수

## 3. Graph
### 구현 방법

1. 인접 행렬

```vertex``` 끼리의 ```weight``` 값을 각 행렬의 요소로 갖는다. ```Edge``` 수에 무관하나 ```Matrix```의 크기가 ```V^2``` 로 매우 크다.

2. 인접 리스트

한 ```vertex```의 인접한 ```vertex```를 확인 가능하며 ```E+V``` 로 비교적 적은 메모리를 차지한다. 단, weight 표기에 별도의 노력이 필요하다.
### 탐색
1. DFS

```Stack``` 자료구조를 사용하여 구현.

2. BFS

```Queue``` 자료구조를 사용하여 구현. 최단 경로를 보장한다.

## 4. Sorting

1. Selection sort

가장 작은 수부터 찾아 정렬하는 알고리즘

```O(n^2)```

2. Bubble sort

오른쪽 요소와 비교 후 정렬 반복

```O(n^2)```

3. Insertion sort

각 요소를 차례로 알맞은 위치에 삽입

```O(n) ~ O(n^2)```

4. Quick sort

pivot 을 사용하여 왼쪽 오른쪽으로 정렬

```O(nlog n) ~ O(n^2)```

5. Merge sort

divide and merge 

```O(nlog n)```
