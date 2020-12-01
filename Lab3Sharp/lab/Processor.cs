namespace Lab3
{
    using System;
    using System.Collections;
    using System.Collections.Generic;
    using System.Linq;

    public class Processor
    {
        public bool IsEmpty => current == null && requests.Count == 0;
        
        public double AverageWaitTime => AllRequests.Sum(r => r.WaitTime) / AllRequests.Count;
        
        public readonly List<Request> AllRequests = new List<Request>();
        
        private List<Request> requests = new List<Request>();
        private Request current;
        private IEnumerator routine;
        
        public void Add(Request request)
        {
            AllRequests.Add(request);
            requests.Add(request);
            requests = requests.OrderByDescending(r => r.Priority).ToList();
            UpdateWaitTime();
        }
        
        private void UpdateWaitTime()
        {
            requests[0].WaitTime = 0;
            for (var i = 1; i < requests.Count; i++)
            {
                var prev = requests[i - 1];
                var request = requests[i];
                request.WaitTime = prev.WaitTime + prev.Time;
            }
        }
        
        public void Update(double dt)
        {
            current = current ?? GetNextRequest();
            if (current != null)
            {
                current.Delay -= dt;
                if (current.Delay <= 0) ProcessRequest();
            }
        }
        
        private void ProcessRequest()
        {
            if (routine.MoveNext())
            {
                ProcessStep();
            }
            else if (routine == current.Routine)
            {
                current.End = DateTime.UtcNow;
                current = GetNextRequest();
            }
            else
            {
                routine = current.Routine;
            }
        }
        
        private void ProcessStep()
        {
            switch (routine.Current)
            {
                case IEnumerator r:
                    routine = r;
                    break;
                case double d:
                    current.Delay = d;
                    break;
            }
        }
        
        private Request GetNextRequest()
        {
            if (requests.Count > 0)
            {
                var request = requests[0];
                requests.RemoveAt(0);
                routine = request.Execute();
                request.Start = DateTime.UtcNow;
                return request;
            }
            return null;
        }
        
        public void Stop()
        {
            current = null;
            requests.Clear();
            AllRequests.Clear();
        }
    }
}