#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>

#define MAXSTRINGLENGTH 1024

void DieWithUserMessage(const char *msg, const char *detail);
void DieWithSystemMessage(const char *msg);
void PrintSocketAddress(const struct sockaddr *address, FILE *stream);

int main(int argc, char *argv[]) {

	if (argc != 2) // Test for correct number of arguments
		DieWithUserMessage("Parameter(s)", "<Server Port/Service>");

	char *service = argv[1]; // First arg: local port/service

	// Construct the server address structure
	struct addrinfo addrCriteria;						//Criteria for address
	memset(&addrCriteria, 0, sizeof(addrCriteria));		//Zero out structure
	addrCriteria.ai_family = AF_UNSPEC;					//Any address family
	addrCriteria.ai_flags = AI_PASSIVE;					//Accept on any address/port
	addrCriteria.ai_socktype = SOCK_DGRAM;				//Only datagram socket
	addrCriteria.ai_protocol = IPPROTO_UDP;				//Only UDP socket

	struct addrinfo *servAddr; // List of server addresses
	int rtnVal = getaddrinfo(NULL, service, &addrCriteria, &servAddr);
	if (rtnVal != 0)
		DieWithUserMessage("getaddrinfo() failed", gai_strerror(rtnVal));

	// Create socket for incoming connections
	int sock = socket(servAddr->ai_family, servAddr->ai_socktype,
		servAddr->ai_protocol);
	if (sock < 0)
		DieWithSystemMessage("socket() failed");

	// Bind to the local address
	if (bind(sock, servAddr->ai_addr, servAddr->ai_addrlen) < 0)
		DieWithSystemMessage("bind() failed");

	// Free address list allocated by getaddrinfo()
	freeaddrinfo(servAddr);

	for (;;) { // Run forever
		struct sockaddr_storage clntAddr; // Client address
		// Set Length of client address structure (in-out parameter)
		socklen_t clntAddrLen = sizeof(clntAddr);

		// Block until receive message from a client
		char buffer[MAXSTRINGLENGTH]; // I/O buffer
		// Size of received message
		ssize_t numBytesRcvd = recvfrom(sock, buffer, MAXSTRINGLENGTH, 0,
			(struct sockaddr *) &clntAddr, &clntAddrLen);
		if (numBytesRcvd < 0)
			DieWithSystemMessage("recvfrom() failed");

		fputs("Handling client ", stdout);
		PrintSocketAddress((struct sockaddr *) &clntAddr, stdout);
		fputc('\n', stdout);
		printf("Server : %s\n", buffer);
/*
		// Send received datagram back to the client
		ssize_t numBytesSent = sendto(sock, buffer, numBytesRcvd, 0,
			(struct sockaddr *) &clntAddr, sizeof(clntAddr));
		if (numBytesSent < 0)
			DieWithSystemMessage("sendto() failed)");
		else if (numBytesSent != numBytesRcvd)
			DieWithUserMessage("sendto()", "sent unexpected number of bytes");
*/
	}
	// NOT REACHED
}



void DieWithUserMessage(const char *msg, const char *detail) {
	fputs(msg, stderr);
	fputs(": ", stderr);
	fputs(detail, stderr);
	fputc('\n', stderr);
	exit(1);
}
void DieWithSystemMessage(const char *msg) {
	perror(msg);
	exit(1);
}

void PrintSocketAddress(const struct sockaddr *address, FILE *stream) {
  // Test for address and stream
	if (address == NULL || stream == NULL)
		return;

	void *numericAddress; // Pointer to binary address
	// Buffer to contain result (IPv6 sufficient to hold IPv4)
	char addrBuffer[INET6_ADDRSTRLEN];
	in_port_t port; // Port to print
	// Set pointer to address based on address family
	switch (address->sa_family) {
	case AF_INET:
		numericAddress = &((struct sockaddr_in *) address)->sin_addr;
		port = ntohs(((struct sockaddr_in *) address)->sin_port);
		break;
	case AF_INET6:
		numericAddress = &((struct sockaddr_in6 *) address)->sin6_addr;
		port = ntohs(((struct sockaddr_in6 *) address)->sin6_port);
		break;
	default:
		fputs("[unknown type]", stream);    // Unhandled type
		return;
	}
	// Convert binary to printable address
	if (inet_ntop(address->sa_family, numericAddress, addrBuffer,
		  sizeof(addrBuffer)) == NULL)
		fputs("[invalid address]", stream); // Unable to convert
	else {
		fprintf(stream, "%s", addrBuffer);
		if (port != 0)                // Zero not valid in any socket addr
		  fprintf(stream, "-%u", port);
	}
}