/*
 * hostname.c
 *
 *  Created on: 2013/04/30
 *      Author: RyzeVia
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(int argc, char** argv) {
	struct sockaddr_in addr;
	struct hostent *host;
	char a[200], *b;

	host = gethostbyname(argv[1]);
	if (host != NULL ) {
		addr.sin_addr = *(struct in_addr *) (host->h_addr_list[0]);
		printf("ip=%x\n", addr.sin_addr);
		printf("%s\n", inet_ntoa(addr.sin_addr));
	}

	return EXIT_SUCCESS;
}
