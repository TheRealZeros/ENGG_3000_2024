import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import org.json.simple.JSONObject;
import org.json.simple.parser.JSONParser;

public class Network {

    JSONObject sendingJSON = new JSONObject();
    JSONObject receivedJSON = new JSONObject();
    byte[] data = sendingJSON.toString().getBytes();
    DatagramSocket socket = new DatagramSocket();

    public void setJSON(Variables vars) {
        json.put("client_type", vars.getClientType());
        json.put("targetSpeed", vars.getTargetSpeed());
        json.put("targetDoorStatus", vars.getTargetDoorStatus());
        json.put("targetMessage", vars.getTargetMessage());
    }

    public void startNetwork(String ip, int port) {
        InetAddress address = InetAddress.getByName(ip);
        DatagramPacket packet = new DatagramPacket(data, data.length, address, port);
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
            receivedJSON = parser.parse(receivedData);
            System.out.println("Got JSON");

            if(receivedJSON.get("client_type").equals("CCP")) {
                System.out.println("JSON is from CCP...");
            } else if(receivedJSON.get("client_type").equals("EAC")) {
                eacVars.setClient_type(receivedJSON.get("client_type"));
                eacVars.setCurrentSpeed(receivedJSON.get("currentSpeed"));
                eacVars.setCurrentDoorStatus(receivedJSON.get("currentDoorStatus"));
                eacVars.setCurrentMessage(receivedJSON.get("currentMessage"));
            } 

        } catch (Exception e) {
            e.printStackTrace();
            System.out.println("Error receiving data");
        }
    }

    public void closeNetwork() {
        socket.close();
    }

}
