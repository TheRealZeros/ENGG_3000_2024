#ifndef BR_ENGINE_H
#define BR_ENGINE_H

class BR_Engine {
    private:
        M_Status motorStatus;
    public:
        BR_Engine();
        M_Status getEngineStatus();
        void setEngineStatus(M_Status motorStatus);
};

#endif // BR_ENGINE_H