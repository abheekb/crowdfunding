// Third Client side C/C++ program to demonstrate Socket programming 
#include <stdio.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <unistd.h> 
#include <string.h> 
#define PORT 8086

int main(int argc, char const *argv[]) 
{ 
	int sock = 0, valread; 
	struct sockaddr_in serv_addr; 
	char *hello = "Hello from client"; 
	char *msg;
	char buffer[1024] = {0}; 
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
	{ 
		printf("\n Socket creation error \n"); 
		return -1; 
	} 

	serv_addr.sin_family = AF_INET; 
	serv_addr.sin_port = htons(PORT); 
	
	// Convert IPv4 and IPv6 addresses from text to binary form 
	if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0) 
	{ 
		printf("\nInvalid address/ Address not supported \n"); 
		return -1; 
	} 

	if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
	{ 
		printf("\nConnection Failed \n"); 
		return -1; 
	} 
	send(sock , hello , strlen(hello) , 0 ); 
	printf("Hello message sent\n"); 
	valread = read( sock , buffer, 1024); 
	printf("%s\n",buffer ); 
	
	while(1)
	{	
		bzero(buffer,1024);
		printf("Your message : ");
		fgets(buffer,1024,stdin);
		
		send(sock , buffer , strlen(buffer) , 0 );
		if(!strcmp(buffer,"exit"))
		{
			printf("Exiting\n");
			break;
		}
		bzero(buffer,1024);
		valread=read(sock,buffer,1024);
		if(!strcmp(buffer,"exit"))
		{
			printf("Connection closed by server.\n");
			break;
		}
		printf("server Message : ");
		
		printf("%s\n",buffer);
	} 
	
	return 0; 
} 

