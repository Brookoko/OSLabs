#include "Processor.h"

Processor::Processor()
{
    current.id = -1;
}

void Processor::addRequest(Request request)
{
    requests.push(request);
    updateWaitTime();
    if (current.id == -1) current = request;
}

void Processor::updateWaitTime()
{
    requests.get(0).setWaitTime(0);
    for (int i = 1; i < requests.size(); ++i)
    {
        auto prev = requests.get(i - 1);
        requests.get(i).setWaitTime(prev.getWaitTime() + prev.getTimeLeft());
    }
}

void Processor::process(double dt)
{
    current.progress(dt);
    if (current.getTimeLeft() <= 0)
    {
        current.id = -1;
        if (!requests.empty())
        {
            current = requests.top();
            requests.pop();
        }
    }
}

double Processor::getAverageWaitTime()
{
    double waitTime = 0;
    for(auto const& req: requests)
    {
        waitTime += req.getWaitTime();
    }
    return waitTime / requests.size();
}
