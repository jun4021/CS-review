#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#define SERVER_TCP_PORT	40010	
#define BUFLEN		1024	

int main( int argc, char **argv ) {
	int	n, bytes_to_read;
	int 	sd, new_sd, client_len, port;
	struct 	sockaddr_in6 	server, client;
	char 	*bp, buf[BUFLEN];
	char * copy = malloc(145);

	port = SERVER_TCP_PORT;
		
	/* Create a stream socket */
	if ((sd = socket(AF_INET6, SOCK_STREAM, 0)) == -1) {
		fprintf(stderr, "Can't create a socket\n");
		exit(1);
	}
	
	/* Bind an address to the socket */
	bzero((char *)&server, sizeof(struct sockaddr_in6));
	server.sin6_family = AF_INET6;
	server.sin6_port = htons(port);
	server.sin6_addr = in6addr_any;
	if ( bind( sd, ( struct sockaddr * )&server, sizeof( server ) ) == - 1) {
		fprintf(stderr, "Can't bind name to socket\n");
		exit(1);
	}
	
	/* queue up to 6 connect requests */
	listen(sd, 6);
	printf("waiting\n");
	int cnt =0;
	while (1) {
		client_len = sizeof(client);
		if ((new_sd = accept(sd, (struct sockaddr *)&client, &client_len)) == -1) {
			  fprintf(stderr, "Can't accept client\n");
			  exit(1);
		}
		printf("accept !\n");

		/*read data to buf*/
		bp = buf;
		bytes_to_read = 30;
		while ((n = read(new_sd, bp, bytes_to_read)) > 0) {
			  bp += n;
			  bytes_to_read -= n;
		}
		printf("%s\n",buf);
		
		/* copy data : buf -> copy  + merge 5 tokens*/
		strncat(copy, buf,28);
		if(cnt==4){
			strcat(copy,"\n");
		}
		else{
			strcat(copy,",");
		}
    	

		/* close new_socket*/
		close(new_sd);

		/*number of token to receive*/
		cnt ++;

		/*send merge_tokens to my IPv4 client*/
		if(cnt==5){
			client_len = sizeof(client);
			if ((new_sd = accept(sd, (struct sockaddr *)&client, &client_len)) == -1) {
			  fprintf(stderr, "Can't accept client\n");
			  exit(1);
			}
			/*copy : 145 Bytes*/
			if(write(new_sd,copy,145)<0){
				printf("fail !\n");
				exit(1);
			}
			printf("complete !\n");
			close(new_sd);

			break;
		}
	}
	close(sd);
	return(0);
}