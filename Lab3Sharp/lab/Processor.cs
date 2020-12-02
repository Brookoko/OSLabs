namespace Lab3
{
    using System;
    using System.Collections;
    using System.Collections.Generic;
    using System.Linq;

    public class Processor
    {
        public bool IsEmpty => current == null && requests.Count == 0;
        
        public readonly List<Request> AllRequests = new List<Request>();
        
        private readonly List<Request> requests = new List<Request>();
        private Request current;
        
        public void Add(Request request)
        {
            AllRequests.Add(request);
            var index = Insert(request);
            UpdateWaitTime(index);
        }
        
        private int Insert(Request request)
        {
            var i = 0;
            while (i < requests.Count && request.Priority <= requests[i].Priority)
            {
                i++;
            }
            requests.Insert(i, request);
            return i;
        }
        
        private void UpdateWaitTime(int startIndex)
        {
            if (startIndex == 0)
            {
                requests[0].WaitTime = 0;
                startIndex++;
            }
            for (var i = startIndex; i < requests.Count; i++)
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
            var routine = current.Routines.Last();
            if (routine.MoveNext())
            {
                ProcessRoutine(routine);
            }
            else if (current.Routines.Count == 1)
            {
                current.End = DateTime.UtcNow;
                current = GetNextRequest();
            }
            else
            {
                current.Routines.Remove(routine);
            }
        }
        
        private void ProcessRoutine(IEnumerator routine)
        {
            switch (routine.Current)
            {
                case IEnumerator r:
                    current.Routines.Add(r);
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
                var routine = request.Execute();
                request.Routines.Add(routine);
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