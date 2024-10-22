public class EAC_Variables {
    
    String client_type;
    int currentSpeed;
    int currentDoorStatus;
    String currentMessage;

    public EAC_Variables() {}

    public String getClient_type() {
        return client_type;
    }

    public void setClient_type(String client_type) {
        this.client_type = client_type;
    }

    public int getCurrentSpeed() {
        return currentSpeed;
    }

    public void setCurrentSpeed(int currentSpeed) {
        this.currentSpeed = currentSpeed;
    }

    public int getCurrentDoorStatus() {
        return currentDoorStatus;
    }

    public void setCurrentDoorStatus(int currentDoorStatus) {
        this.currentDoorStatus = currentDoorStatus;
    }

    public String getCurrentMessage() {
        return currentMessage;
    }

    public void setCurrentMessage(String currentMessage) {
        this.currentMessage = currentMessage;
    }

    @Override
    public String toString() {
        return "EAC_Variables{" +
                "client_type='" + client_type + '\'' +
                ", currentSpeed=" + currentSpeed +
                ", currentDoorStatus=" + currentDoorStatus +
                ", currentMessage='" + currentMessage + '\'' +
                '}';
    }
}
