import java.io.InputStream;
import java.io.OutputStream;
import java.net.Socket;
import java.net.ServerSocket;

import java.time.Instant;

public class Server {
    public static void main (String [] args) {

        // Create a server socket object and start listening for incoming connections.
        try (ServerSocket server_socket = new ServerSocket (Shared.SERVER_PORT)) {

            System.out.println ("Waiting for incoming connection.");

            while (true) {
                // Wait until an incoming connection arrives and accept it.
                try (Socket client_socket = server_socket.accept ()) {

                    System.out.println ("Accepted an incoming connection.");

                    try (
                        OutputStream output = client_socket.getOutputStream ();
                    ) {
			Instant instant = Instant.now();
			long seconds = instant.toEpochMilli() / 1000;
			String timeString = Long.toString(seconds);
			byte[] message = timeString.getBytes();
			output.write(message);
                    }
                    System.out.println ("Client disconnected.");
                }
                catch (Exception e) {
                    System.out.println (e);
                }
            }
        }
        catch (Exception e) {
            System.out.println (e);
        }
    }
}
