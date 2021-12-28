# Socket Programming

## 목표 
- IPv4 client를 구현해 IPv4 server와 통신한다.
- 서로 다른 IPv6 5 client에게 random token을 받는 IPv6 server를 구현한다.
- 구현한 IPv6 server 와 IPv4 client을 이용해 token을 client에게 송신한다.(단, IPv4 client는 IPv4 server와 통신이 끊기지 않고 동시에 연결된다.)
- 마지막으로 그 token을 처음에 연결한 socket을 이용해 IPv4 client에게 확인을 받는다.
-----------
## IPv4 client
- SERVER_TCP_PORT : IPv4 server에서 정한 Port number이다.
- main 함수 속 host : IPv4 server의 IP address이다.

- socket()을 통해 socket을 생성해 IP, port 정보를 담고 connect()한다. 
- 그 후 server와 read,write을 번갈아 가면서 정보를 주고 받는다. 이때 이는 IPv6 client 측에서 token을 IPv6 server에 보낼 때까지 반복이다. 이후 token을 보내는 write 전까지 sleep.
------------
## IPv6 server
- SERVER_TCP_PORT : IPv6 server의 port number이다.

- 마찬가지로 socket()을 통해 socket을 생성하고 IP, port 정보를 담고 bind()해 client의 request를 기다린다.
- 총 6개의 client에게 request가 온다(token client 5/ IPv4 client 1). 하나씩 처리하기 위해 listen의 큐를 6개로 잡아두고 한 client씩 accpet한다.
- 처음 다섯 Request는 read()를 통해 token을 읽고 close()한다.
- 여섯 번째는 받은 token을 합쳐 IPv4 client에게 write()한 후 close()한다.

-------------
## IPv4 client
- sleep()이 종료된 후 새 thread를 생성해 IPv6 server와 통신한다. 
- pthread_create()을 통해 connect_v6()를 호출해 token을 read()한다.
- pthread_join()을 통해 token을 result에 반환한다.
- 그 후 아까 연결해 둔 IPv4에게 write한 후 결과를 기다린다.

--------------
## 특이사항
- Linux 환경에서 IPv6는 오로지 Link address만 지원하기 때문에 miredo를 설치 후 Global address를 확인한다.

```
$ sudo apt-get install miredo
$ ifconfig
```
- thread 구현을 위해 사용한 pthread는 gcc로 컴파일 할 때 -lpthread 를 추가해 컴파일 해야한다. 
```
$ gcc -g -o -lpthread IPv4client.c IPv4client
```

-------------
## 문제점
- 오로지 규칙적인 read/write 시에만 다음 같이 사용할 수 있다. 그로 인해 조금 코드가 단순히 그 과정을 나열한 형태가 되었는데 이를 개선해야한다.
- 서버에서 "\n"로 종료되는 형태만 읽어내어 이 문자열 처리하는데 꽤나 애를 먹었다. 당시 조금 중구난방하게 결과물만 나오도록 코드를 짠 경향이 있다.
