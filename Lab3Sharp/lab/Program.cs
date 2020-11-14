namespace Lab3
{
    using System.Threading.Tasks;

    class Program
    {
        static async Task Main(string[] args)
        {
            var processor = new Processor();
            processor.Add(new Request(3, 10));
            processor.Add(new Request(3, 1));
            processor.Add(new Request(3, 5));
            while (!processor.IsEmpty)
            {
                processor.Update(0.016);
                await Task.Delay(16);
            }
        }
    }
}
