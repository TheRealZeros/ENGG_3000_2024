#ifndef BR_CCP_Variables_H
#define BR_CCP_Variables_H

#include <string>
#include "../Components/BR_Variables.h"

class BR_CCP_Variables {
    private:
        std::string ccpType = "ccp";
        std::string ccpMessage;
        std::string ccpClientID;
        std::string ccpTimestamp;
        std::string ccpAction;
        std::string ccpStatus;
        std::string ccpStationID;
    public:
        // Getters
        std::string getCcpType() const {
            return ccpType;
        }

        std::string getCcpMessage() const {
            return ccpMessage;
        }

        std::string getCcpClientID() const {
            return ccpClientID;
        }

        std::string getCcpTimestamp() const {
            return ccpTimestamp;
        }

        std::string getCcpAction() const {
            return ccpAction;
        }

        std::string getCcpStatus() const {
            return ccpStatus;
        }

        std::string getCcpStationID() const {
            return ccpStationID;
        }

        // Setters
        void setCcpType(const std::string& type) {
            ccpType = type;
        }

        void setCcpMessage(const std::string& message) {
            ccpMessage = message;
        }

        void setCcpClientID(const std::string& clientID) {
            ccpClientID = clientID;
        }

        void setCcpTimestamp(const std::string& timestamp) {
            ccpTimestamp = timestamp;
        }

        void setCcpAction(const std::string& action) {
            ccpAction = action;
        }

        void setCcpStatus(const std::string& status) {
            ccpStatus = status;
        }

        void setCcpStationID(const std::string& stationID) {
            ccpStationID = stationID;
        }
};

#endif // BR_CCP_Variables_H