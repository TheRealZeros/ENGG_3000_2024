#include "Status.h"

const char* getStatusString(Status status) {
    switch (status) {
        case Status::ON: return "ON";
        case Status::OFF: return "OFF";
        case Status::ERR: return "ERR";
        default: return "UNKNOWN";
    }
}

const char* getStatusString(D_Status status) {
    switch (status) {
        case D_Status::OPEN: return "OPEN";
        case D_Status::CLOSE: return "CLOSE";
        case D_Status::ERR: return "ERR";
        default: return "UNKNOWN";
    }
}

const char* getStatusString(M_Status status) {
    switch (status) {
        case M_Status::MOVE: return "MOVE";
        case M_Status::STOP: return "STOP";
        case M_Status::PEND: return "PEND";
        case M_Status::ERR: return "ERR";
        default: return "UNKNOWN";
    }
}

const char* getStatusString(C_Status status) {
    switch (status) {
        case C_Status::ON: return "ON";
        case C_Status::OFF: return "OFF";
        case C_Status::CRASH: return "CRASH";
        case C_Status::MANSTP: return "MANSTP";
        case C_Status::ERR: return "ERR";
        default: return "UNKNOWN";
    }
}

