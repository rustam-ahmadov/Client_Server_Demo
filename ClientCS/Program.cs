using System.Text;
using System.Text.Json;
using ClientCS;



void SetPerson(Person p)
{
    p.Name = "Rustam";
    p.Age = 28;
};


Person person = new();
SetPerson(person);

Client client = new();
client.SetIPEndPointDefault();
client.SetSocketDefault();
client.Connect();
await client.SendDataAsync<Person>(person);

byte [] receivedData = await client.ReceiveDataAsync();
string dataJs = Encoding.UTF8.GetString(receivedData);
string data1Js = Encoding.ASCII.GetString(receivedData);

string receivedData1 = Encoding.UTF8.GetString(receivedData!);
//Person person1 = JsonSerializer.Deserialize<Person>(receivedData1)!;
System.Console.WriteLine(receivedData1);
//System.Console.WriteLine(person1.Age);

//await client.ReceiveDataAsync();
//client.PrintReceivedDataPerson();

//System.Console.WriteLine("Just for test");

