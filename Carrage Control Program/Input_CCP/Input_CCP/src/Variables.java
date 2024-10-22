public class Variables {

    String client_type;
    int targetSpeed;
    int targetDoorStatus;
    String targetMessage;

    public Variables() {}

    public String getClient_type() {
        return client_type;
    }

    public void setClient_type(String client_type) {
        this.client_type = client_type;
    }

    public int getTargetSpeed() {
        return targetSpeed;
    }

    public void setTargetSpeed(int targetSpeed) {
        this.targetSpeed = targetSpeed;
    }

    public int getTargetDoorStatus() {
        return targetDoorStatus;
    }

    public void setTargetDoorStatus(int targetDoorStatus) {
        this.targetDoorStatus = targetDoorStatus;
    }

    public String getTargetMessage() {
        return targetMessage;
    }

    public void setTargetMessage(String targetMessage) {
        this.targetMessage = targetMessage;
    }

    @Override
    public String toString() {
        return "Variables{" +
                "client_type='" + client_type + '\'' +
                ", targetSpeed=" + targetSpeed +
                ", targetDoorStatus=" + targetDoorStatus +
                ", targetMessage='" + targetMessage + '\'' +
                '}';
    }
    
}
