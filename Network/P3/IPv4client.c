#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#define SERVER_TCP_PORT	50000 
#define BUFLEN			1024

/*clear the buffer*/
void clear_buf(char * buf,int len){
	for(int i=0;i<len;i++){
		if(buf[i]==0){
			break;
		}
		buf[i]=0;
	}
	return;
}

/*connect to my IPv6 server*/
void *connect_v6(void *arg){
	int 	bytes_to_read;
	int 	sd, port;
	struct 	sockaddr_in6 	server;
	char 	*host, *bp,*rst, str[BUFLEN]={0,};
    char addr[16];

	host = "2001:0:c38c:c38c:3400:a34:824c:3910"; // we should change host IP
	port = 40010;
		
	if ((sd = socket(AF_INET6, SOCK_STREAM, 0)) == -1) {
		fprintf(stderr, "Can't create a socket\n");
		exit(1);
	}

	/*setting before connect*/
	bzero((char *)&server, sizeof(struct sockaddr_in6));
	server.sin6_family = AF_INET6;
	server.sin6_port = htons(port);
    inet_pton(AF_INET6, host, (void *)&addr);
	memcpy((void *)&server.sin6_addr,(void *)&addr,16);

	/* Connecting to the server */
	if (connect(sd, (struct sockaddr *)&server, sizeof(server)) == -1) {
		fprintf(stderr, "Can't connect\n");
		exit(1);
	}

	/*read tokens*/
	bytes_to_read = BUFLEN;
    bp = str;
	if(read(sd, bp, bytes_to_read)==-1) {
        printf("read error\n");
	}

	/*copy to rst + return rst*/
    rst = malloc(145);
	strcpy(rst,str);
	close(sd);
	return rst;
}

int main() {
	int 	n, bytes_to_read;
	int 	sd, port;
	struct 	hostent 	*hp;
	struct 	sockaddr_in 	server;
	char 	*host, *bp, rbuf[BUFLEN]={0,}, sbuf[BUFLEN]={0,};
	pthread_t threadID;

	host = "3.17.53.130";
	port = SERVER_TCP_PORT;
		
	if ((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		fprintf(stderr, "Can't create a socket\n");
		exit(1);
	}

	bzero((char *)&server, sizeof(struct sockaddr_in));
	server.sin_family = AF_INET;
	server.sin_port = htons(port);
	if ((hp = gethostbyname(host)) == NULL) {
		fprintf(stderr, "Can't get server's address\n");
		exit(1);
	}
	bcopy(hp->h_addr, (char *)&server.sin_addr, hp->h_length);

	/* Connecting to the server */
	if (connect(sd, (struct sockaddr *)&server, 
	sizeof(server)) == -1) {
		fprintf(stderr, "Can't connect\n");
		exit(1);
	}
	printf("Connected: server's address is %s\n", hp->h_name);	
	
	bytes_to_read = BUFLEN;
	int wr_cnt =0 ;
	/*If while ends, it should be connected to IPv6 server to get token*/
	while (wr_cnt < 6) {

		/*read two packets*/
		bp = rbuf;
		if(n=read(sd,bp,bytes_to_read)<=0){
			printf("error\n");
			exit(1);
		}
		bp+=n;
		printf("%s",rbuf);
		if(n=read(sd,bp,bytes_to_read)<=0){
			printf("error\n");
			exit(1);
		}
		bp+=n;
		printf("%s",rbuf);
		
		/*write data format : finish with '\n' */
		int len=0;
		fgets(sbuf,sizeof(sbuf),stdin);

		/*length of sbuf*/	
		for(int i=0;i<BUFLEN;i++){
			if(sbuf[i]=='\n'){
				len = i+1;
			}
		}

		/*copy to str*/
		char * str =malloc(sizeof(len));
		for(int i=0;i<len;i++){
			str[i] = sbuf[i];
		}
		write(sd,str,len);
		
		/*clear buffer*/
		clear_buf(rbuf,BUFLEN);
		clear_buf(sbuf,BUFLEN);
		wr_cnt++;
	}
	
	/*read*/
	bp = rbuf;
	if(n=read(sd,bp,bytes_to_read)<=0){
		printf("error\n");
		exit(1);
	}
	bp+=n;
	printf("%s",rbuf);

	/*Connect with IPv6 with new Thread*/ 
	sleep(10); // wait for IPv6 get token

	char * result = NULL;
	pthread_create(&threadID,NULL,connect_v6,NULL);
	pthread_join(threadID,(void **)&result);

	/*get 5 token in result and write*/
	write(sd,result,145);

	/*read the result of connection*/
	bp = rbuf;
	if(n=read(sd,bp,bytes_to_read)<=0){
		printf("error\n");
		exit(1);
	}
	bp+=n;
	printf("%s",rbuf);

	close(sd);
	return(0);
}