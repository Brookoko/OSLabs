namespace Lab3
{

    using System.Collections.Generic;
    using System.Linq;

    public class Processor
    {
        public bool IsEmpty => requests.Count == 0;
        
        private List<Request> requests = new List<Request>();
        private Request current;
        
        public void Add(Request request)
        {
            requests.Add(request);
            requests = requests.OrderByDescending(r => r.Priority).ToList();
            request.WaitTime = requests
                .TakeWhile(r => r != request)
                .Sum(r => r.Time);
            TryToExecuteRequest();
        }
        
        public void Update(double dt)
        {
            if (current != null)
            {
                if (current.Delay <= 0) UpdateCurrentRequest();
                else current.Delay -= dt;
            }
        }
        
        private void UpdateCurrentRequest()
        {
            if (current.Routine.MoveNext())
            {
                current.Delay = (double) current.Routine.Current;
            }
            else
            {
                current = null;
                TryToExecuteRequest();
            }
        }
        
        private void TryToExecuteRequest()
        {
            if (current == null && requests.Count > 0)
            {
                current = requests[0];
                requests.RemoveAt(0);
                current.Execute();
            }
        }
    }
}