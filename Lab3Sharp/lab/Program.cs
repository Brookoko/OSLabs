namespace Lab3
{
    using System;
    using System.Linq;
    using System.Threading.Tasks;

    class Program
    {
        private static readonly Random random = new Random();
        private static readonly Processor processor = new Processor();

        private static bool isTested;
        
        private static async void Intensity()
        {
            for (var i = 1; i <= 60; i++)
            {
                var wait = (int) (1f / i * 1000);
                for (var j = 0; j < i; j++)
                {
                    processor.Add(CreateRequest());
                    await Task.Delay(wait);
                }
                Console.WriteLine($"{i} : {processor.AverageWaitTime}");
                processor.Stop();
            }
            isTested = true;
        }
        
        private static async void Idle()
        {
            for (var i = 1; i <= 5; i++)
            {
                var start = DateTime.UtcNow;
                var proc = new Processor();
                var wait = (int) (1f / i * 1000);
                for (var j = 0; j < i; j++)
                {
                    proc.Add(CreateRequest());
                    await Task.Delay(wait);
                }
                while (!proc.IsEmpty)
                {
                    proc.Update(0.1);
                    await Task.Delay(100);
                }
                var allTime = (DateTime.UtcNow - start).TotalMilliseconds;
                var executeTime = proc.AllRequests.Sum(r => (r.End - r.Start).TotalMilliseconds);
                Console.WriteLine($"{i} : {allTime - executeTime}");
            }
            isTested = true;
        }
        
        private static void Priority()
        {
            for (var j = 0; j < 100; j++)
            {
                processor.Add(CreateRequest());
            }
            for (var i = 1; i <= 32; i++)
            {
                var requests = processor.AllRequests.Where(r => r.Priority == i).ToList();
                var average = requests.Sum(r => r.WaitTime) / requests.Count;
                Console.WriteLine($"{i} : {average}");
            }
            processor.Stop();
            isTested = true;
        }
        
        private static Request CreateRequest()
        {
            var time = 1 + random.NextDouble() * 1;
            var priority = random.Next(1, 33);
            return new Request(time, priority);
        }
        
        static async Task Main(string[] args)
        {
            processor.Add(new TestRequest(1, 1));
            processor.Add(new TestRequest(1, 1));
            processor.Add(new TestRequest(1, 1));
            while (!isTested)
            {
                processor.Update(0.016);
                await Task.Delay(16);
            }
        }
    }
}
