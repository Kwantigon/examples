#include "shared.h"
#include <time.h>
#include <stdlib.h>

static int server_time (struct tm* result)
{
    // Create client socket object.
    //
    // The object state resides in the operating system kernel.
    // What we have is merely a file descriptor refering to it.

    int client_socket = socket (AF_INET, SOCK_STREAM, 0);
    ASSERT (client_socket != -1, "Failed to create client socket object.");

    // Construct server address.
    //
    // Note the need to use network order inside address fields.

    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    int aton_status = inet_aton (SERVER_ADDR, (in_addr *) &server_address.sin_addr.s_addr);
    ASSERT (aton_status == 1, "Failed to parse server address.");
    server_address.sin_port = htons (SERVER_PORT);

    // Connect to server.
	// Read the time string into buffer.

    int connect_status = connect (client_socket, (struct sockaddr *) &server_address, sizeof (server_address));
    ASSERT (connect_status == 0, "Failed to connect to server.");
    printf ("Established outgoing connection.\n");

    char buffer [SOCKET_BUFFER_SIZE];
    ssize_t read_size = read (client_socket, buffer, sizeof (buffer));
    ASSERT (read_size >= 0, "Failed to read from outgoing connection.");

    // Clean up by closing the socket.
    //
    // Shutdown precedes close to make sure protocol level shutdown is executed completely.
    // Close without shutdown may use RST instead of FIN to terminate connection, dropping data that is in flight.
    //
    // It is also possible to use shutdown to close input and output streams independently.

    int shutdown_status = shutdown (client_socket, SHUT_RDWR);
    ASSERT (shutdown_status == 0, "Failed to shutdown incoming connection.");

    int close_status = close (client_socket);
    ASSERT (close_status == 0, "Failed to close incoming connection.");

	// Convert the string in buffer to time_t (= long int)
	
	printf("Hour: %d\n", result->tm_hour); // silencing compiler

	long int seconds = atol(buffer);
	result = localtime(&seconds);
	return 0;
}

int main() {

	time_t s;
	time(&s);
	struct tm* time = localtime (&s); // just to silence the compiler.

	int i = 0;
	i = server_time(time);
	if (i == 0) {
		printf("%d-", 1900 + time->tm_year);
		printf("%d-", time->tm_mon);
		printf("%d ", time->tm_mday);

		if (time->tm_hour < 10) {
			printf("0%d:", time->tm_hour);
		} else {
			printf("%d:", time->tm_hour);
		}

		if (time->tm_min < 10) {
			printf("0%d:", time->tm_min);
		} else {
			printf("%d:", time->tm_min);
		}

		if (time->tm_sec < 10) {
			printf("0%d:", time->tm_sec);
		} else {
			printf("%d\n", time->tm_sec);
		}
		
	} else {
		printf("%s\n", "Could not get server time.");
	}

	return 0;
}
