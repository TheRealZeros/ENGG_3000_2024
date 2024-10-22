import java.net.SocketException;
import java.util.Scanner;

public class App {

    static Network network = new Network();

    public static void main(String[] args) throws SocketException {
        Boolean running = false;
        Scanner scanner = new Scanner(System.in);
        System.out.println("Enter 'Start' to start the program");
        String input = scanner.nextLine();
        Variables variables = new Variables();
       EAC_Variables EACvariables = new EAC_Variables();

if (input.equals("Start")) {
    network.startNetwork("192.168.215.193", 3009);

    variables.setClientType("CCP");
    variables.setTargetSpeed(0);
    variables.setTargetDoorStatus(0);
    variables.setTargetMessage("ACK");
    
    network.setJSON(variables);

    System.out.println("Sending Acknowledgement...");
    network.printSendingJSON();

    network.sendJSON();

    network.getSocket().setSoTimeout(20000);

    boolean ackReceived = false;
    long startTime = System.currentTimeMillis();

    while (!ackReceived && (System.currentTimeMillis() - startTime) < 20000) {
        // network.getJSON(EACvariables);
        if (EACvariables.getClientType().equals("EAC") && EACvariables.getCurrentMessage().equals("ACK")) {
            System.out.println("Connected to EAC");
            ackReceived = true;
            running = true;
        }
    }

    if (!ackReceived) {
        System.out.println("Error connecting to EAC");
    }
} else if (input.equals("Exit")) {
    scanner.close();
} else if (input.equals("Override")) {
    running = true;
    network.startNetwork("192.168.215.193", 3009);

    variables.setClientType("CCP");
    variables.setTargetSpeed(0);
    variables.setTargetDoorStatus(0);
    variables.setTargetMessage("ACK");

    
    network.setJSON(variables);

    System.out.println("Sending Acknowledgement...");
    network.printSendingJSON();

    network.sendJSON();
}

        while (running) {
            System.out.println("===========================");
            System.out.println("STOP, GO, OPEN, CLOSE, EXIT");

            switch(scanner.nextLine()) {
                case "STOP":
                    variables.setTargetSpeed(0);
                    System.out.println("Updating Speed:" + variables.getTargetSpeed());
                    variables.setTargetMessage("STOP");
                    System.out.println("Updating Message:" + variables.getTargetMessage());
                    network.setJSON(variables);
                    network.sendJSON();
                    network.printSendingJSON();
                    break;
                case "GO":
                    variables.setTargetSpeed(50);
                    System.out.println("Updating Speed:" + variables.getTargetSpeed());
                    variables.setTargetMessage("GO");
                    System.out.println("Updating Message:" + variables.getTargetMessage());
                    network.setJSON(variables);
                    network.sendJSON();
                    network.printSendingJSON();
                    break;
                case "OPEN":
                    variables.setTargetDoorStatus(1);
                    System.out.println("Updating Door:" + variables.getTargetDoorStatus());
                    variables.setTargetMessage("OPEN");
                    System.out.println("Updating Message:" + variables.getTargetMessage());
                    network.setJSON(variables);
                    network.sendJSON();
                    network.printSendingJSON();
                    break;
                case "CLOSE":
                    variables.setTargetDoorStatus(0);
                    System.out.println("Updating Door:" + variables.getTargetDoorStatus());
                    variables.setTargetMessage("CLOSE");
                    System.out.println("Updating Message:" + variables.getTargetMessage());
                    network.setJSON(variables);
                    network.sendJSON();
                    network.printSendingJSON();
                    break;
                case "EXIT":
                    System.out.println("Exiting...");
                    running = false;
                    scanner.close();
                    network.closeNetwork();
                    break;
            }
            
        }
    }
    
}
