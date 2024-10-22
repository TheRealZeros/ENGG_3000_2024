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
            System.out.println("Error creating DatagramSocket");
        }
    }

    public DatagramSocket getSocket() {
        return socket;
    }

    DatagramPacket packet;

    public void setJSON(Variables vars) {
        sendingJSON.put("client_type", vars.getClientType());
        sendingJSON.put("targetSpeed", vars.getTargetSpeed());
        sendingJSON.put("targetDoorStatus", vars.getTargetDoorStatus());
        sendingJSON.put("targetMessage", vars.getTargetMessage());
    }

    public void startNetwork(String ip, int port) {
        try {
            InetAddress address = InetAddress.getByName(ip);
            packet = new DatagramPacket(data, data.length, address, port);
        } catch (UnknownHostException e) {
            e.printStackTrace();
            System.out.println("Unknown host: " + ip);
        }
    }
    public void sendJSON() {
        try {
            socket.send(packet);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public void getJSON(EAC_Variables eacVars) {
        byte[] buffer = new byte[1024];
        DatagramPacket packet = new DatagramPacket(buffer, buffer.length);
        try {
            socket.receive(packet);
            String receivedData = new String(packet.getData(), 0, packet.getLength());
            JSONParser parser = new JSONParser();
            receivedJSON = (JSONObject) parser.parse(receivedData);

            if(receivedJSON.isEmpty()) {
                System.out.println("Error: No data received");
            } else {
                System.out.println("Received data: " + receivedData);
                System.out.println("Got JSON");
            }
            

            if(receivedJSON.get("client_type").equals("CCP")) {
                System.out.println("JSON is from CCP...");
            } else if(receivedJSON.get("client_type").equals("EAC")) {
                eacVars.setClientType((String) receivedJSON.get("client_type"));
                eacVars.setCurrentSpeed((int) receivedJSON.get("currentSpeed"));
                eacVars.setCurrentDoorStatus((int) receivedJSON.get("currentDoorStatus"));
                eacVars.setCurrentMessage((String) receivedJSON.get("currentMessage"));
            } else {
                System.out.println("Error: Unknown client type");
            }

        } catch (Exception e) {
            e.printStackTrace();
            System.out.println("Error receiving data");
        }
    }

    public void printSendingJSON() {
        System.out.println("Sending JSON: " + sendingJSON);
    }

    public void printReceivedJSON() {
        System.out.println("Received JSON: " + receivedJSON);
    }

    public void closeNetwork() {
        socket.close();
    }

}
