import java.util.Scanner;

public class CCP {
    
    public static void main(String[] args) {
        CCP_Variables carrageVariables = new CCP_Variables();
        CCP_Networking_JSON carrageNetworking = new CCP_Networking_JSON(3009, "10.20.30.176", carrageVariables);
        Scanner scanner = new Scanner(System.in);
        
        Boolean running = false;

        System.out.println("Wanna start?");

        if(scanner.nextLine().equals("Start")) {
            System.out.println("CBA Enter JSON Shit:");
            carrageVariables.carrageSpeed = scanner.nextInt();
            System.out.println(carrageVariables.carrageSpeed);

            scanner.nextLine();
            carrageVariables.message = scanner.nextLine();

            carrageVariables.carrageSpeed = scanner.nextInt();
            scanner.nextLine();
            carrageVariables.doorStatus = scanner.nextLine();
            System.out.println("k");

            running = true;
            carrageNetworking.startNetworking(running);
        } else if(scanner.nextLine().equals("Exit")) {
            running = false;
            carrageNetworking.stopNetworking();
            scanner.close();
        }

        while(running) {
            carrageVariables.updateCCPMessage();
            carrageVariables.updateLowLevelValues();
        }

    }   
}