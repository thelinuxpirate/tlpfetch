#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>

#include <netinet/in.h>
#include <net/if.h>
#include <unistd.h>

#include <arpa/inet.h>

char getIp() {
	int n;
	struct ifreq ifr;
	char array[] = "eth0";

	n = socket(AF_INET, SOCK_DGRAM, 0);
	// type of address to retrieve - IPv4 IP address
	ifr.ifr_addr.sa_family = AF_INET;
	// copy the interface name in the ifreq structure
	strncpy(ifr.ifr_name , array , IFNAMSIZ - 1);
	ioctl(n, SIOCGIFADDR, &ifr);
	close(n);

	printf("IP: %s\n", inet_ntoa(((struct sockaddr_in *)&ifr.ifr_addr )->sin_addr));
	return inet_ntoa(((struct sockaddr_in *)&ifr.ifr_addr )->sin_addr);
}

void drawAscii(const char *filename) {
    FILE *file = fopen(filename, "r");

    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    char additionalInfo[256];
    snprintf(additionalInfo, sizeof(additionalInfo), "%s@%s", getenv("USER"), getenv("HOSTNAME"));

    // get the terminal size
    struct winsize w;
    ioctl(0, TIOCGWINSZ, &w);
    int terminalWidth = w.ws_col;

    // cal the width reserved for the file contents | -2 for padding
    int fileContentWidth = terminalWidth - strlen(additionalInfo) - 2; 
    printf("%s\n", additionalInfo);

    // read and print each line of the file, adjusting the width
    char line[1024];
    while (fgets(line, sizeof(line), file) != NULL) {
        printf("%-*s%s", fileContentWidth, line, additionalInfo);
    }

    fclose(file);
}

int main(void) {
	printf("\tHello, TLP!\n");
	getIp();
	drawAscii("pichu.txt");
	return 0;
}
