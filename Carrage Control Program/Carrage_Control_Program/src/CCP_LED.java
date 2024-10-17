public class CCP_LED {

    // Enum to represent the state of the carriage
    public enum CarriageState {
        STATIONARY,
        MOVING,
        IN_BETWEEN
    }

    // Method to set LED color based on carriage state
    public static void setLED(CarriageState state) {
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
    private static void turnRedLED() {
        System.out.println("LED is RED: Carriage is stationary.");
    }

    // Simulating turning the Green LED on
    private static void turnGreenLED() {
        System.out.println("LED is GREEN: Carriage is moving.");
    }

    // Simulating turning the Yellow LED on
    private static void turnYellowLED() {
        System.out.println("LED is YELLOW: Carriage is between stationary and moving.");
    }

    public static void main(String[] args) {
        // Test with different carriage states
        setLED(CarriageState.STATIONARY);
        setLED(CarriageState.MOVING);
        setLED(CarriageState.IN_BETWEEN);
    }
}

