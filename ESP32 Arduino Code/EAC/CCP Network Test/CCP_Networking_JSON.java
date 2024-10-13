// External Libraries
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.util.Scanner;
import org.json.simple.JSONObject;
import org.json.simple.parser.JSONParser;

// Internal Libraries
import src.CCP_Variables;

public class CCP_Networking_JSON extends Thread {

    // Scanner for user input
    private static volatile Scanner scanner = new Scanner(System.in);

    // Boolean for receiving UDP Thread, enables to close socket
    private static volatile boolean running = true;

    // Single Socket for both Receiving and Sending
    private static DatagramSocket socket;

    public static void main(String[] args) {

        int port = 3009;
        String address = "192.168.0.167";   // TODO: ENSURE THIS GETS CHANGED 

        try {
            // Initialise the DatagramSocket to handle both sending and receiving
            socket = new DatagramSocket(port);

            // THREAD FOR RECEIVING UDP PACKET
            Thread receivingThread = new Thread(() -> {
                
                // Buffer for received data
                byte[] receivedData = new byte[1024];  
                
                try {
                    while (running && !socket.isClosed()) {
                        
                        // Create a packet to receive data
                        DatagramPacket receivedPacket = new DatagramPacket(receivedData, receivedData.length);

                        // Function to receive data from the socket and add to the new packet
                        socket.receive(receivedPacket);

                        // Convert the received data into a string
                        String receivedMessage = new String(receivedPacket.getData(), 0, receivedPacket.getLength());

                        // Clears the buffer (the set data received in bytes)
                        receivedData = new byte[1024];
                        
                        // Convert the received message into a temp JSON Object
                        JSONParser parser = new JSONParser();
                        JSONObject tempJSON = (JSONObject) parser.parse(receivedMessage);

                        // Sets the tempJSON objects into each of the eacJSON objects
                        CCP_Variables.eacMessage.put("Type", tempJSON.get("Type"));   
                        CCP_Variables.eacMessage.put("currentSpeed", tempJSON.get("currentSpeed"));
                        CCP_Variables.eacMessage.put("dStatus", tempJSON.get("dStatus"));
                        CCP_Variables.eacMessage.put("mStatus", tempJSON.get("mStatus"));

                        // Ignore UDP Packets sent from CCP
                        if(!tempJSON.get("Type").equals("CCP")) {
                            // Prints the eacMessage
                            System.out.println("Rececived From EAC: ");
                            System.out.println(CCP_Variables.eacMessage);
                        } else {
                            // Clears the tempJSON 
                            tempJSON = new JSONObject();
                            // Clears the received message
                            receivedMessage = "";
                        }
                    }
                } catch (Exception e) {
                    if (running && !socket.isClosed()) {
                        e.printStackTrace();  
                    }
                } 

            });
            receivingThread.start();  // Start the receiving thread

            // THREAD FOR SENDING UDP PACKET
            Thread sendingThread = new Thread(() -> {
                try {
                    while (true) {
                        // Sending data
                        System.out.println("Enter message to send to the EAC below");
                        System.out.println("Commands: 'exit','LMS','LMR','STAT'");
                        System.out.println("----------------------------");

                        if (scanner.hasNextLine()) {
                            String cmdLineInputMessage = scanner.nextLine();
                            String sendingMessage = cmdLineInputMessage;
                            
                            switch (cmdLineInputMessage) {
                                case "exit":
                                    running = false;
                                    closeSocket();
                                    break;

                                case "LMS":
                                    System.out.println("============");
                                    System.out.println(CCP_Variables.ccpMessage);
                                    break;

                                case "LMR":
                                    System.out.println("============");
                                    System.out.println(CCP_Variables.eacMessage);
                                    break;

                                case "STAT":
                                    System.out.println("============");
                                    System.out.println("Requesting Status from EAC...");
                                    sendingMessage = CCP_Variables.statMessage.toString();
                                    break;

                                default:
                                    System.out.println("==============================");
                                    System.out.println("Sending wildcard '" + cmdLineInputMessage + "' Command to EAC...");
                                    CCP_Variables.ccpMessage.put("Message", cmdLineInputMessage);
                                    sendingMessage = CCP_Variables.ccpMessage.toString();
                                    break;
                            }

                                // Sets the data to send in bytes
                                byte[] sendData = sendingMessage.getBytes();

                                // Set IP Address to send packets to
                                InetAddress IPAddress = InetAddress.getByName(address);

                                // Create packet to send data
                                DatagramPacket sendingPacket = new DatagramPacket(sendData, sendData.length, IPAddress, port);

                                // Function to send data on the socket
                                socket.send(sendingPacket);
                        
                            // Prints the message being sent

                            if(!sendingMessage.equals("LMS") && !sendingMessage.equals("LMR")) {
                                System.out.println("--- Message sent");
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

}
