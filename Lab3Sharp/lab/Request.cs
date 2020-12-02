namespace Lab3
{
    using System;
    using System.Collections;
    using System.Collections.Generic;

    public class Request
    {
        private static int num;
        
        public int Id { get; }
        
        public double Time { get; protected set; }
        
        public int Priority { get; }
        
        public double Delay { get; set; }
        
        public double WaitTime { get; set; }
        
        public List<IEnumerator> Routines { get; } = new List<IEnumerator>();
        
        public DateTime Start { get; set; }
        
        public DateTime End { get; set; }
        
        public Request(double time, int priority)
        {
            Id = num++;
            Time = time;
            Priority = priority;
        }
        
        public IEnumerator Execute()
        {
            return StartRoutine();
        }
        
        protected virtual IEnumerator StartRoutine()
        {
            yield return Time;
        }
    }
    
    public class TestRequest : Request
    {
        public TestRequest(double time, int priority) : base(time, priority)
        {
        }
        
        protected override IEnumerator StartRoutine()
        {
            yield return Wait();
            Console.WriteLine("test");
        }
        
        private IEnumerator Wait()
        {
            if (Time < 0) yield break;
            yield return 0.1f;
            Time -= 0.1f;
            yield return Wait();
        }
    }
}