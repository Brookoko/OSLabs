namespace Lab3
{
    using System;
    using System.Collections;

    public class Request
    {
        private static int num;
        
        public int Id { get; }
        
        public double Time { get; }
        
        public int Priority { get; }
        
        public double Delay { get; set; }
        
        public double WaitTime { get; set; }
        
        public IEnumerator Routine { get; private set; }
        
        public Request(double time, int priority)
        {
            Id = num++;
            Time = time;
            Priority = priority;
        }
        
        public void Execute()
        {
            Routine = StartRoutine();
        }
        
        private IEnumerator StartRoutine()
        {
            yield return Time;
        }
    }
}