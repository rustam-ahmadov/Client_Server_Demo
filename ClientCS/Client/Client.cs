using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Text.Json;

namespace ClientCS
{
    public class Client
    {

        public IPAddress Ip { get; set; } = IPAddress.Parse("127.0.0.1");
        public int Port { get; set; } = 8080;
        private IPEndPoint? endPoint;
        private Socket? socket;

        private byte[]? bufferData;
        void SetIPEndPoint(IPAddress ip, int port)
        {
            endPoint = new(ip, port);
        }
        public void SetIPEndPointDefault()
        {
            endPoint = new(Ip, Port);
        }
        public void SetSocket(AddressFamily addressFamily, SocketType socketType, ProtocolType protocolType)
        {
            socket = new(addressFamily, socketType, protocolType);
            
        }
        public void SetSocketDefault()
        {
            socket = new(
                addressFamily: AddressFamily.InterNetwork,//IPv4
                socketType: SocketType.Stream,//TCP
                protocolType: ProtocolType.Tcp
            );
            IPEndPoint clientEndPoint = new(IPAddress.Parse("127.0.0.1"),8008);            
            socket.Bind(clientEndPoint);
        }
        public void Connect(){
            socket!.Connect(endPoint!);
        }
        public async Task<int> SendDataAsync<T>(T data)
        {
            string jsonData = JsonSerializer.Serialize<T>(data);
            bufferData = Encoding.ASCII.GetBytes(jsonData);
            return await socket!.SendAsync(bufferData, SocketFlags.None);
        }
        public async Task<byte[]> ReceiveDataAsync()
        {
            bufferData = new byte[65000];
            await socket!.ReceiveAsync(bufferData, SocketFlags.None);
            return bufferData;
        }

        public void PrintReceivedDataPerson()
        {
            string receivedData = Encoding.UTF32.GetString(bufferData!);
            Person person = JsonSerializer.Deserialize<Person>(receivedData) ?? new() { Name = "Unknown", Age = 0 };
            System.Console.WriteLine(person.Name);
            System.Console.WriteLine(person.Age);
        }
        public void PrintReceivedDataJson()
        {
            string receivedData = Encoding.UTF32.GetString(bufferData!);
            System.Console.WriteLine(receivedData);
        }



    }
}