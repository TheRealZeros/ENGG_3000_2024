// External Libraries
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.util.Scanner;

// Internal Libraries

public class CCP_Networking_Input extends Thread {

    private static volatile Scanner scanner = new Scanner(System.in);
    private static volatile String eacMessage = "";
    private static volatile String ccpMessage = "";
    private static volatile boolean running = true;

    // Class-level DatagramSocket, accessible in all methods and threads
    private static DatagramSocket socket;

    public static void main(String[] args) {

        int port = 3009;
        String address = "192.168.0.167";   // TODO: ENSURE THIS GETS CHANGED 

        try {
            // Initialise the DatagramSocket to handle both sending and receiving
            socket = new DatagramSocket(port);

            // THREAD FOR RECEIVING UDP PACKET
            Thread receivingThread = new Thread(() -> {
                byte[] receivedData = new byte[1024];  // Buffer for received data

                try {
                    while (running && !socket.isClosed()) {
                        // Create a packet to receive data
                        DatagramPacket receivedPacket = new DatagramPacket(receivedData, receivedData.length);

                        // Function to receive data on the new packet
                        socket.receive(receivedPacket);

                        // Convert the received byte data into string
                        String receivedMessage = new String(receivedPacket.getData(), 0, receivedPacket.getLength());

                        // Clears the buffer (the set data received in bytes)
                        receivedData = new byte[1024];

                        // Ignore UDP Packets from itself
                        if(!receivedMessage.startsWith("CCP: ")) {
                            eacMessage = receivedMessage;
                            System.out.println(eacMessage);
                        } else {
                            receivedMessage = "";
                        }
                        
                    }
                } catch (Exception e) {
                    if (running && !socket.isClosed()) {
                        e.printStackTrace();  // Print stack trace if there's an issue while running
                    }
                } finally {
                    
                }
            });

            receivingThread.start();  // Start the receiving thread

            // THREAD FOR SENDING UDP PACKET
            Thread sendingThread = new Thread(() -> {
                try {
                    while (true) {
                        // Sending data
                        System.out.println("Enter message to send to the EAC below");
                        System.out.println("Commands: 'exit','LMS','LMR'");
                        System.out.println("----------------------------");
                        if (scanner.hasNextLine()) {
                            String cmdLineInputMessage = scanner.nextLine();

                            // Exiting program
                            if (cmdLineInputMessage.equals("exit")) {
                                running = false;
                                closeSocket();  // Only close the socket, not the scanner
                                break;
                            } else if(cmdLineInputMessage.equals("LMS")) {
                                System.out.println("============");
                                System.out.println(getCCPMessage());
                            } else if(cmdLineInputMessage.equals("LMR")) {
                                System.out.println("============");
                                System.out.println(getEACMessage());
                            }

                            // Sets the sending message as the cmdLineInputMessage
                            String sendingMessage = "CCP: " + cmdLineInputMessage;

                            ccpMessage = sendingMessage;

                            // Sets the data to send in bytese
                            byte[] sendData = ccpMessage.getBytes();

                            // Set IP Address to send packets to
                            InetAddress IPAddress = InetAddress.getByName(address);

                            // Create packet to send data
                            DatagramPacket sendingPacket = new DatagramPacket(sendData, sendData.length, IPAddress, port);

                            // Function to send data on the socket
                            socket.send(sendingPacket);

                            // Prints the message being sent

                            if(!cmdLineInputMessage.equals("LMS") || !cmdLineInputMessage.equals("LMR")) {
                                System.out.println("============");
                                System.out.println("Message sent");
                                System.out.println("============");
                            } else {
                                System.out.println("============");
                            }

                        } else {
                            break; // If scanner has no next line, exit loop
                        }
                    }
                } catch (Exception e) {
                    e.printStackTrace();
                } finally {
                   
                }
            });

            sendingThread.start();

            // Wait for the sending thread to finish before closing the scanner
            sendingThread.join();

        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            // Close the scanner only after the sending thread has completed
            closeScanner();
        }
    }

    static void closeSocket() {
        if (socket != null && !socket.isClosed()) {
            socket.close();
        }
        System.out.println("========  Socket closed.");
    }

    static void closeScanner() {
        if (scanner != null) {
            scanner.close();
            System.out.println("======== Scanner closed.");
        }
    }

    static String getEACMessage() {
        return eacMessage;
    }

    static String getCCPMessage() {
        return ccpMessage;
    }
}
