import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.util.Scanner;

public class Main {

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        DatagramSocket socket = null;

        try {
            socket = new DatagramSocket();
            InetAddress receiverAddress = InetAddress.getByName("10.20.30.176"); 

            while (true) {
                System.out.print("Enter message to send (or type 'exit' to quit): ");
                String message = scanner.nextLine();

                if (message.equalsIgnoreCase("exit")) {
                    break;
                }

                byte[] buffer = message.getBytes();

                // Create the packet to send (data, length, destination address, destination port)
                DatagramPacket packet = new DatagramPacket(buffer, buffer.length, receiverAddress, 9876);

                // Send the packet
                socket.send(packet);
                System.out.println("Packet sent.");
            }
        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            if (socket != null && !socket.isClosed()) {
                // Close the socket
                socket.close();
            }
            scanner.close();
        }
    }
}