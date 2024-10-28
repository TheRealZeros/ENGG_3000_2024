import java.net.SocketException;
import java.util.Scanner;

public class App {

    static Network network = new Network();
    static String ip = "10.0.2.154";
    static int port = 3009;

    public static void main(String[] args) throws SocketException {
        Boolean running = false;
        Scanner scanner = new Scanner(System.in);
        System.out.println("Enter 'Start' to start the program");
        String input = scanner.nextLine();
        Variables variables = new Variables();
       EAC_Variables EACvariables = new EAC_Variables();

    if (input.equals("Start")) {
        network.startNetwork(ip, port);

        variables.setClientType("CCP");
        variables.setTargetSpeed(0);
        variables.setTargetDoorStatus(0);
        variables.setTargetMessage("ACK");
        
        network.setJSON(variables);

        
        network.getSocket().setSoTimeout(20000);

        long startTime = System.currentTimeMillis();

        while (!running && System.currentTimeMillis() - startTime < 20000) {
            
            if (EACvariables.getClientType().equals("EAC") && EACvariables.getCurrentMessage().equals("ACK")) {
                System.out.println("CCP: Sending Acknowledgement...");
                network.sendJSON();
                network.printSendingJSON();

                System.out.println("CCP: Connected to EAC");
                running = true;
            } else {
                try {
                    System.out.println("CCP: Awaiting Acknowledgement...");
                    Thread.sleep(500);
                    network.getJSON(EACvariables, ip);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
        }


    } else if (input.equals("Exit")) {
        scanner.close();
    } else if (input.equals("Override")) {
        network.startNetwork(ip, port);

        variables.setClientType("CCP");
        variables.setTargetSpeed(0);
        variables.setTargetDoorStatus(0);
        variables.setTargetMessage("ACK");

        
        network.setJSON(variables);

        System.out.println("CCP: Sending Acknowledgement...");
        network.printSendingJSON();

        network.sendJSON();
    } else if(input.equals("Test")) {
        network.startNetwork(ip, port);

        EACvariables.setClientType("EAC");
        EACvariables.setCurrentSpeed(0);
        EACvariables.setCurrentDoorStatus(0);
        EACvariables.setCurrentMessage("ACK");

        network.setJSON(EACvariables);

        System.out.println("EAC: Sending Acknowledgement...");
        network.sendJSON();
        network.printSendingJSON();

        network.getSocket().setSoTimeout(60000);

        long startTime = System.currentTimeMillis();

        while (!running) {
            if((System.currentTimeMillis() - startTime) < 60000) {
                try {
                    Thread.sleep(500);
                    network.getJSON(EACvariables, ip);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }  
            }  else if(EACvariables.getClientType().equals("CCP") && EACvariables.getCurrentMessage().equals("ACK")) {
                System.out.println("EAC: Connected to CCP... lol");
                running = true;
            }
            
        }
        
    
    } else {

        while (running) {

            variables.setClientType("CCP");
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
            
            try {
                Thread.sleep(2000);
                network.getJSON(EACvariables, ip);
                EACvariables.toString();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
            
        }
    }
    }   
}
