import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import org.json.simple.JSONObject;
import org.json.simple.parser.JSONParser;
import org.json.simple.parser.ParseException;
import java.util.logging.Level;
import java.util.logging.Logger;

public class CCP_Networking_JSON {
    // Logger for logging messages and errors
    private static final Logger LOGGER = Logger.getLogger(CCP_Networking_JSON.class.getName());

    // Boolean for controlling the networking threads
    private volatile boolean running = true;

    // Datagram socket for sending and receiving UDP packets
    private DatagramSocket socket;

    // IP Address of the remote server
    private InetAddress ipAddress; 

    // Port for UDP communication
    private int port = 3009;

    // Address to connect to
    private String address = "10.20.30.176";

    // ccp Variables
    private CCP_Variables ccpVariables;

    public CCP_Networking_JSON(int port, String address, CCP_Variables ccpVariables) {
        this.port = port;
        this.address = address;
        this.ccpVariables = ccpVariables;

        try {
            // Initialise the DatagramSocket with the specified port
            this.socket = new DatagramSocket(port);
            // Resolve the IP address to connect to
            this.ipAddress = InetAddress.getByName(address);
            // Set socket timeout to avoid indefinite blocking
            this.socket.setSoTimeout(5000); // 5 seconds socket timeout
        } catch (Exception e) {
            // Log any exceptions during socket initialization
            LOGGER.log(Level.SEVERE, "Failed to initialise DatagramSocket", e);
        }
    }

    // Start networking threads for sending and receiving UDP packets
    public void startNetworking(Boolean running) {
        while (running) {
            // Start the networking threads for sending and receiving
            // receiveMCP();
            
            // try {
            //     Thread.sleep(1000); // 1 second delay
            // } catch (InterruptedException e) {
            //     Thread.currentThread().interrupt();
            //     LOGGER.log(Level.WARNING, "Thread interrupted", e);
            // }
            
            // sendMCP();
            
            // try {
            //     Thread.sleep(3000); // 3 second delay
            // } catch (InterruptedException e) {
            //     Thread.currentThread().interrupt();
            //     LOGGER.log(Level.WARNING, "Thread interrupted", e);
            // }
    
            receiveEAC();
            
            try {
                Thread.sleep(5000); // 5 second delay
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt();
                LOGGER.log(Level.WARNING, "Thread interrupted", e);
            }
            
            sendEAC();
            
            try {
                Thread.sleep(2000); // 2 second delay
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt();
                LOGGER.log(Level.WARNING, "Thread interrupted", e);
            }
        }
    }

    // Stop all networking threads and close the socket
    public void stopNetworking() {
        running = false;
        closeSocket();
    }

    // Close the socket safely
    private void closeSocket() {
        if (socket != null && !socket.isClosed()) {
            socket.close();
        }
        LOGGER.info("Socket closed.");
    }

    // Thread for receiving packets from EAC
    private void receiveEAC() {
        Thread eacReceivingThread = new Thread(() -> {
            byte[] receivedData = new byte[1024]; // Buffer for received data
            try {
                while (running && !socket.isClosed()) {
                    receivingPacket(ccpVariables.eacMessageCCP, receivedData);
                }
            } catch (Exception e) {
                if (running && !socket.isClosed()) {
                    LOGGER.log(Level.SEVERE, "Error receiving EAC packets", e);
                }
            }
        });
        eacReceivingThread.start(); // Start the EAC receiving thread
    }

    // Thread for receiving packets from MCP
    private void receiveMCP() {
        Thread mcpReceivingThread = new Thread(() -> {
            byte[] receivedData = new byte[1024]; // Buffer for received data
            try {
                while (running && !socket.isClosed()) {
                    receivingPacket(CCP_Variables.mcpMessageCCP, receivedData);
                }
            } catch (Exception e) {
                if (running && !socket.isClosed()) {
                    LOGGER.log(Level.SEVERE, "Error receiving MCP packets", e);
                }
            }
        });
        mcpReceivingThread.start(); // Start the MCP receiving thread
    }

    // Thread for sending packets to EAC
    private void sendEAC() {
        Thread eacSendingThread = new Thread(() -> {
            try {
                while (running) {
                    ccpVariables.updateCCPMessage();
                    sendingPacket(ccpVariables.ccpMessageEAC);
                    System.out.println(ccpVariables.carrageSpeed);
                    LOGGER.info("Sending CCP Message to EAC as: " + ccpVariables.ccpMessageEAC);
                    Thread.sleep(1000); // Add delay for network stability
                }
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt();
                LOGGER.warning("EAC Sending Thread interrupted.");
            } catch (Exception e) {
                LOGGER.log(Level.SEVERE, "Error sending CCP to EAC", e);
            }
        });
        eacSendingThread.start(); // Start the EAC sending thread
    }

    // Thread for sending packets to MCP
    private void sendMCP() {
        Thread mcpSendingThread = new Thread(() -> {
            try {
                while (running) {
                    sendingPacket(CCP_Variables.ccpMessageMCP);
                    LOGGER.info("Sending CCP Message to MCP as: " + CCP_Variables.ccpMessageMCP);
                    Thread.sleep(1000); // Add delay for network stability
                }
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt();
                LOGGER.warning("MCP Sending Thread interrupted.");
            } catch (Exception e) {
                LOGGER.log(Level.SEVERE, "Error sending CCP to MCP", e);
            }
        });
        mcpSendingThread.start(); // Start the MCP sending thread
    }

    // Method to send a UDP packet with JSON data
    private void sendingPacket(JSONObject json) {
        try {
            // Convert JSON object to string
            String sendingMessage = json.toString();
            // Convert string to byte array for sending
            byte[] sendData = sendingMessage.getBytes();
            // Create packet with data, address, and port
            DatagramPacket sendingPacket = new DatagramPacket(sendData, sendData.length, ipAddress, port);
            // Send the packet through the socket
            socket.send(sendingPacket);
        } catch (Exception e) {
            // Log any exceptions during sending
            LOGGER.log(Level.SEVERE, "Error sending packet", e);
        }
    }

    // Method to receive a UDP packet and parse JSON data
    private void receivingPacket(JSONObject json, byte[] buffer) {
        try {
            // Create a packet to receive data
            DatagramPacket receivedPacket = new DatagramPacket(buffer, buffer.length);
            // Receive data into the packet
            socket.receive(receivedPacket);
            // Convert received data to string
            String receivedMessage = new String(receivedPacket.getData(), 0, receivedPacket.getLength());

            // Parse the received string into a JSON object
            JSONParser parser = new JSONParser();
            JSONObject tempJSON = (JSONObject) parser.parse(receivedMessage);

            // Update the target JSON object based on the type of message received
            if (tempJSON.get("client_type").equals("EAC")) {
                json.put("client_type", tempJSON.get("client_type"));
                json.put("currentSpeed", tempJSON.get("currentSpeed"));
                json.put("dStatus", tempJSON.get("dStatus"));
                json.put("mStatus", tempJSON.get("mStatus"));
            } else if (tempJSON.get("Type").equals("MCP")) {
                json.put("Type", tempJSON.get("Type"));
            }

            // Ignore packets sent from CCP itself
            if (!tempJSON.get("Type").equals("CCP")) {
                LOGGER.info("Received JSON: " + json);
            }
        } catch (ParseException e) {
            // Log parsing errors
            LOGGER.warning("Error parsing received packet: " + e.getMessage());
        } catch (Exception e) {
            // Log other exceptions during receiving
            LOGGER.log(Level.SEVERE, "Error receiving packet", e);
        }
    }

}