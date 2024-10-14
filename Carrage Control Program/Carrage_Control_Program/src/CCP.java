import java.util.Scanner;

public class CCP {

    
    public static void main(String[] args) {
        CCP_Variables carrageVariables = new CCP_Variables();
        CCP_Networking_JSON carrageNetworking = new CCP_Networking_JSON(3009, "192.168.0.167");
        Scanner scanner = new Scanner(System.in);
        
        Boolean running = false;

        if(scanner.nextLine().equals("Start")) {
            running = true;
            carrageNetworking.startNetworking();
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