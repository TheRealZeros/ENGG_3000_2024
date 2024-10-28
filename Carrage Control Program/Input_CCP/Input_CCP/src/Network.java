import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.SocketException;
import java.net.UnknownHostException;

import org.json.simple.JSONObject;
import org.json.simple.parser.JSONParser;

public class Network {

    JSONObject sendingJSON = new JSONObject();
    JSONObject receivedJSON = new JSONObject();
    
    byte[] data = sendingJSON.toString().getBytes();
    public static DatagramSocket socket;

    static {
        try {
            socket = new DatagramSocket();
        } catch (SocketException e) {
            e.printStackTrace();
            System.out.println("Network: Error creating DatagramSocket");
        }
    }

    public DatagramSocket getSocket() {
        return socket;
    }

    DatagramPacket packet;

    public void startNetwork(String ip, int port) {
        try {
            InetAddress address = InetAddress.getByName(ip);
            packet = new DatagramPacket(data, data.length, address, port);
        } catch (UnknownHostException e) {
            e.printStackTrace();
            System.out.println("Network: Unknown host: " + ip);
        }
    }

    public void setJSON(Variables vars) {
        sendingJSON.put("client_type", vars.getClientType());
        sendingJSON.put("targetSpeed", vars.getTargetSpeed());
        sendingJSON.put("targetDoorStatus", vars.getTargetDoorStatus());
        sendingJSON.put("targetMessage", vars.getTargetMessage());
        System.out.println("JSON: Set CCP json to variables" + vars.toString());
    }

    public void setJSON(EAC_Variables vars) {
        sendingJSON.put("client_type", vars.getClientType());
        sendingJSON.put("currentSpeed", vars.getCurrentSpeed());
        sendingJSON.put("currentDoorStatus", vars.getCurrentDoorStatus());
        sendingJSON.put("currentMessage", vars.getCurrentMessage());
        System.out.println("JSON: Set EAC json to variables" + vars.toString());
    }


    public void sendJSON() {
        try {
            socket.send(packet);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public void getJSON(EAC_Variables eacVars, String expectedIP) {

        System.out.println("JSON: Attempting to get JSON...");

        byte[] buffer = new byte[1024];
        DatagramPacket packet = new DatagramPacket(buffer, buffer.length);
        try {
            socket.setSoTimeout(5000);
            socket.receive(packet);

            // Print a message indicating a packet was received
            System.out.println("Network: Packet received!");

            String receivedData = new String(packet.getData(), 0, packet.getLength());
            
            // Verify that the packet is from the correct source
            if (!packet.getAddress().getHostAddress().equals(expectedIP)) {
                System.out.println("Network: Received packet from unexpected IP address: " + packet.getAddress().getHostAddress());
                return;
            }
    
            JSONParser parser = new JSONParser();
            receivedJSON = (JSONObject) parser.parse(receivedData);
    
            if(receivedJSON.isEmpty()) {
                System.out.println("JSON: ERROR No data received");
            } else {
                System.out.println("JSON: Received data: " + receivedData);
                System.out.println("JSON: Got JSON!");
            }
            
            // Handle the JSON data
            if(receivedJSON.get("client_type").equals("CCP")) {
                System.out.println("JSON: JSON is from CCP...");
            } else if(receivedJSON.get("client_type").equals("EAC")) {
                eacVars.setClientType((String) receivedJSON.get("client_type"));
                eacVars.setCurrentSpeed((int) receivedJSON.get("currentSpeed"));
                eacVars.setCurrentDoorStatus((int) receivedJSON.get("currentDoorStatus"));
                eacVars.setCurrentMessage((String) receivedJSON.get("currentMessage"));
            } else {
                System.out.println("JSON: Unknown client type");
            }
    
        } catch (Exception e) {
            //e.printStackTrace();
            System.out.println("JSON: Error receiving data");
        }
    }
    
    public void getJSON(Variables vars, String expectedIP) {

        System.out.println("JSON: Attempting to get JSON...");

        byte[] buffer = new byte[1024];
        DatagramPacket packet = new DatagramPacket(buffer, buffer.length);
        try {
            socket.setSoTimeout(5000);
            socket.receive(packet);

            // Print a message indicating a packet was received
            System.out.println("Network: Packet received!");

            String receivedData = new String(packet.getData(), 0, packet.getLength());
            
            // Verify that the packet is from the correct source
            if (!packet.getAddress().getHostAddress().equals(expectedIP)) {
                System.out.println("Network: Received packet from unexpected IP address: " + packet.getAddress().getHostAddress());
                return;
            }
    
            JSONParser parser = new JSONParser();
            receivedJSON = (JSONObject) parser.parse(receivedData);
    
            if(receivedJSON.isEmpty()) {
                System.out.println("JSON: ERROR No data received");
            } else {
                System.out.println("JSON: Received data: " + receivedData);
                System.out.println("JSON: Got JSON!");
            }
            
            // Handle the JSON data
            if(receivedJSON.get("client_type").equals("EAC")) {
                System.out.println("JSON: JSON is from EAC...");
            } else if(receivedJSON.get("client_type").equals("CCP")) {
                vars.setClientType((String) receivedJSON.get("client_type"));
                vars.setTargetSpeed((int) receivedJSON.get("targetSpeed"));
                vars.setTargetDoorStatus((int) receivedJSON.get("targetDoorStatus"));
                vars.setTargetMessage((String) receivedJSON.get("targetMessage"));
            } else {
                System.out.println("JSON: Unknown client type");
            }
    
        } catch (Exception e) {
            //e.printStackTrace();
            System.out.println("JSON: Error receiving data");
        }
    }


    public void printSendingJSON() {
        System.out.println("JSON: Sending JSON: " + sendingJSON);
    }

    public void printReceivedJSON() {
        System.out.println("JSON: Received JSON: " + receivedJSON);
    }

    public void closeNetwork() {
        socket.close();
    }

}
