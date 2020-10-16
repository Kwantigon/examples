import java.io.InputStream;
import java.io.PrintWriter;
import java.io.OutputStream;
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.net.Socket;

import java.time.LocalDateTime;
import java.time.OffsetDateTime;

public class Client {
    static public LocalDateTime ServerTime () {

        // Create a socket object and connect it to the server.
        try (Socket server_socket = new Socket (Shared.SERVER_ADDR, Shared.SERVER_PORT)) {

            System.out.println ("Established outgoing connection.");

            try (
                // Wrap the socket streams in appropriate readers and writers.
                InputStream input = server_socket.getInputStream ();
                InputStreamReader reader = new InputStreamReader (input);
                BufferedReader buffered = new BufferedReader (reader);
            ) {
		String timeString = buffered.readLine();
                //System.out.println ("Received message: " + timeString);

		// Convert the timeString to epoch seconds
		try {
		    long seconds = Long.parseLong(timeString);
		    LocalDateTime serverTime = LocalDateTime.ofEpochSecond(seconds, 0, OffsetDateTime.now().getOffset());
		    return serverTime;
		}
		catch (NumberFormatException nfe) {
		    System.out.println("Server returned wrong format.");
		    return null;
            	}
	      }
        }
        catch (Exception e) {
            System.out.println (e);
	}
	// mvn compiler is complaining about a missing return statement.
	// This part should not be reached.
	return null;
    }

    public static void main (String[] args) {
	LocalDateTime timeNow = ServerTime();
	int hour = timeNow.getHour();
        int min = timeNow.getMinute();
        int sec = timeNow.getSecond();
        int yy = timeNow.getYear();
        int mm = timeNow.getMonthValue();
        int dd = timeNow.getDayOfMonth();
        System.out.printf("%d-%d-%d ", yy, mm, dd);

	if (hour < 10) {
	    System.out.printf("0%d:", hour);
	} else {
	    System.out.printf("%d:", hour);
	}
	if (min < 10) {
	    System.out.printf("0%d:", min);
	} else {
	    System.out.printf("%d:", min);
	}
	if (sec < 10) {
	    System.out.printf("0%d", sec);
	} else {
	    System.out.printf("%d\n", sec);
	}
    }
}
