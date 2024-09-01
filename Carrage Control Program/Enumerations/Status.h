// Status.h file
#ifndef STATUS_H
#define STATUS_H

enum class Status {
    ON,
    OFF,
    ERR
};

enum class D_Status {
    OPEN,
    CLOSE,
    ERR
};

enum class M_Status {
    MOVE,
    STOP,
    PEND,
    ERR
};

enum class C_Status {
    ON,
    OFF,
    CRASH,
    MANSTP,
    ERR
};

#endif // STATUS_H