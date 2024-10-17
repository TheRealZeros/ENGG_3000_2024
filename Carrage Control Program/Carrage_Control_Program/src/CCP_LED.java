public class CCP_LED {

    // Enum to represent the state of the carriage
    public enum CarriageState {
        STATIONARY,
        MOVING,
        IN_BETWEEN
    }

    // Reference to CCP_Variables for state checking
    private CCP_Variables variables;

    public CCP_LED(CCP_Variables variables) {
        this.variables = variables;
    }

    // Determine the carriage state based on the variables
    public CarriageState getCarriageState() {
        int speed = variables.lowLevelCarrageSpeed; // Reading speed from CCP_Variables

        if (speed == 0) {
            return CarriageState.STATIONARY;
        } else if (speed > 0 && speed < 100) { // Assuming some in-between threshold (adjust as needed)
            return CarriageState.IN_BETWEEN;
        } else {
            return CarriageState.MOVING;
        }
    }

    // Method to set LED color based on carriage state
    public void setLED(CarriageState state) {
        switch (state) {
            case STATIONARY:
                turnRedLED();
                break;
            case MOVING:
                turnGreenLED();
                break;
            case IN_BETWEEN:
                turnYellowLED();
                break;
            default:
                System.out.println("Unknown carriage state");
        }
    }

    // Simulating turning the Red LED on
    private void turnRedLED() {
        System.out.println("LED is RED: Carriage is stationary.");
    }

    // Simulating turning the Green LED on
    private void turnGreenLED() {
        System.out.println("LED is GREEN: Carriage is moving.");
    }

    // Simulating turning the Yellow LED on
    private void turnYellowLED() {
        System.out.println("LED is YELLOW: Carriage is between stationary and moving.");
    }

    // Update method to regularly check state and update LED
    public void updateLED() {
        CarriageState state = getCarriageState();
        setLED(state);
    }

    public static void main(String[] args) {
        // Example: Initialize CCP_Variables and CCP_LED
        CCP_Variables variables = new CCP_Variables();
        CCP_LED ccpLED = new CCP_LED(variables);

        // Regularly update the LED state based on carriage status
        while (true) {
            ccpLED.updateLED();
            try {
                Thread.sleep(1000); // Adjust the update frequency as needed
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt();
            }
        }
    }
}
