# 알고리즘

## 목차
1. Sorting
## 1. Sorting
  1. Bubble sort
  - 인접한 두 원소 비교 후 swap, 한 칸씩 전진
  - 모든 원소 검사 후 다음 cycle 반복 진행
  - 평균, 최선, 최악 모두 ```O(n^2)```

  2. Selection sort
  - 가장 작은 수부터 찾아 정렬하는 알고리즘(해당 자리에 넣을 원소 찾기)
  - 평균, 최선, 최악 모두 ```O(n^2)```
  
  3. Insertion sort
    - 각 요소를 차례로 알맞은 위치에 삽입
    - 최선(이미 정렬되어 있는 경우) ```O(n)```, 평균, 최악 ```O(n^2)```
  4. Quick sort
  - 기준 원소 pivot 을 사용하여 왼쪽 오른쪽으로 정렬 (divide)
  - 분할된 두 배열도 재귀적으로 반복한다.
  - pivot 값이 최소나 최대로 지정되면 최악 ```O(n^2)``` 최선,평균의 경우 ```O(nlog n)```
  Q.  JAVA Arrays.sort() : DualPivotQuicksort -> 배열의 크기에 따라 Insertion < Quick < Merge 순으로 사용
    - DualPivotQuicksort은 Quick sort의 최악을 줄이기 위해 pivot을 두개 사용하여 3개로 분할해 정렬하는 알고리즘이다.
  5. Merge sort
  - 요소를 쪼개고 순차적으로 비교하며 정렬 -> 순차적으로 접근한다는 특징으로 linkedlist 정렬에 효율적
  - ```O(nlog n)```

  Q. Python sorted(), list.sort() -> Tim sort(Merge + insertion)
  - https://d2.naver.com/helloworld/0315536
  6. Heap sort
  - Heap 자료구조를 이용한 정렬로 이미 정렬된 배열에 요소를 추가하는 게 용이하다.

  Q. Quick, Merge, Heap 각각의 강점?
    - Quick : 평균적으로 가장 빠르다. But n이 작을 때, function call(재귀) overhead가 증가 
    - Merge : 한정된 메모리에서 데이터 양이 다 불러올 수 없을 정도로 많을 때.
    - Heap : 정렬된 배열에 새로운 값을 추가할 때 ```O(log n)``` 빠름.

## 2. Spanning Tree
  - 최소 연결 그래프(간선의 개수 node-1)
  - Mininmum Spanning Tree(MST) : 간선들의 가중치 합이 최소인 트리
  - 구현방법
    1. Kruskal 알고리즘 : Greedy -> 가중치 낮은 순으로 선택, 사이클 생성 X 
      - Union-find 알고리즘 : 같은 집합은 하나의 트리로 묶고(union) 새로 추가하는 정점이 같은 집합인지 (find)
      - 시간복잡도는 간선 가중치를 정렬하는 게 핵심.
    2. Prim 알고리즘 : 인접 정점 중 최소 정점 선택. 정점 한 칸씩 확장되어 구현. 
       
## 3. 최단 거리 알고리즘
  1. 다익스트라(Dijkstra) : 인접 해 있는 정점까지의 최단 거리를 기록 및 갱신 -> 방문하지 않은 정점 중 최단거리인 정점으로
    - 간선의 가중치가 양수일 때만 가능하다 
    - Why? 이미 방문한 곳은 갱신되지 않으며 음수 가중치의 경우 거리가 감소할 가능성이 있음.
  2. Bellman-Ford : 음수 가중치에서도 사용 가능. 대신 cycle이 음수 가중치면 불가
    - 각 정점의 모든 간선에서 확인을 거침.

## 4. 문자열 패턴 매칭
  - 문자열 t(len = N), 에서 패턴 p(len=M)을 찾는 알고리즘
  1. brute force : ```O(NM)```
  2. KMP 알고리즘(https://bowbowbow.tistory.com/6) : 이미 검사한 부분에서 접두사, 접미사가 일치하는 부분 문자열만큼 skip
  3. Boyer-Moore : 패턴 뒷부분에서부터 검증, 불일치 시 해당 문자가 패턴에 없을 시 p칸 skip // 해당 문자가 패턴에 있을 경우 뒤에서 부터 순서를 세 그만큼 skip

