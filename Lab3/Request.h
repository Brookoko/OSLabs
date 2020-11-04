#ifndef OSLABS_REQUEST_H
#define OSLABS_REQUEST_H

class Request
{
public:
    int id;
    
    explicit Request(double time, int priority)
    {
        id = 0;
        this->time = time;
        this->waitTime = 0;
        this->priority = priority;
    }
    
    int getPriority() const
    {
        return priority;
    }
    
    void setWaitTime(double t)
    {
        waitTime = t;
    }
    
    double getWaitTime() const
    {
        return waitTime;
    }
    
    double getTimeLeft() const
    {
        return time;
    }
    
    void progress(double dt)
    {
        time -= dt;
    }
private:
    double time;
    double waitTime;
    int priority;
};

#endif //OSLABS_REQUEST_H
