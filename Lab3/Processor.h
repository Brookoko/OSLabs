#ifndef OSLABS_PROCESSOR_H
#define OSLABS_PROCESSOR_H

#include "Request.h"
#include <queue>
#include <vector>

class Processor
{
public:
    Processor();
    void addRequest(Request request);
    void process(double dt);
    double getAverageWaitTime();
private:
    struct CustomCompare
    {
        bool operator()(const Request& lhs, const Request& rhs)
        {
            return lhs.getPriority() < rhs.getPriority();
        }
    };
    
    struct PriorityQueue: std::priority_queue<Request, std::vector<Request>, CustomCompare> {
        auto begin() const
        {
            return c.begin();
        }
        auto end() const
        {
            return c.end();
        }
        Request get(int index)
        {
            return c[index];
        }
    };
    
    PriorityQueue requests;
    Request current = Request(0, 0);
    
    void updateWaitTime();
};

#endif //OSLABS_PROCESSOR_H
