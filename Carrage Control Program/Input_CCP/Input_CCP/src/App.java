import java.util.Scanner;

public class App {

    static Network network = new Network();

    public static void main(String[] args) {
        Boolean running = false;
        Scanner scanner = new Scanner(System.in);
        System.out.println("Enter 'start' to start the program");
        String input = scanner.nextLine();
        Variables variables = new Variables();

        if (input.equals("start")) {
            variables.setClientType("CCP");
            variables.setTargetSpeed(0);
            variables.setTargetDoorStatus(0);
            variables.setTargetMessage("ACK");
            network.getJSON();
            
            running = true;
            network.startNetwork("10.20.30.176", 3009);
        }

        while (running) {
            System.out.println("STOP, GO, OPEN, CLOSE, EXIT");

            

            switch(scanner.nextLine()) {
                case "STOP":
                    variables.setTargetSpeed(0);
                    variables.setTargetMessage("STOP");
                    network.sendJSON();
                    variables.toString();
                case "GO":
                    variables.setTargetSpeed(50);
                    variables.setTargetMessage("GO");
                    network.sendJSON();
                    variables.toString();
                case "OPEN":
                    variables.setTargetDoorStatus(1);
                    variables.setTargetMessage("OPEN");
                    network.sendJSON();
                    variables.toString();
                case "CLOSE":
                    variables.setTargetDoorStatus(0);
                    variables.setTargetMessage("CLOSE");
                    network.sendJSON();
                    variables.toString();
                case "EXIT":
                    running = false;
                    network.closeNetwork();
            }
            
        }
    }
    
}
