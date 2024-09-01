#ifndef ICOMPONENTS_H
#define ICOMPONENTS_H
#include "Status.h"

class iComponents {
public:
    virtual ~iComponents() {}

    Status componentStatus;

    virtual Status getStatus() const = 0;
};

#endif // ICOMPONENTS_H