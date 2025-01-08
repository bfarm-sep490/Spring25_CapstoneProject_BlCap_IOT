using System;
using System.Text;
using System.Threading.Tasks;
using HiveMQtt.Client;
using HiveMQtt.Client.Options;

namespace MqttConsoleApp
{
    class Program
    {
        static async Task Main(string[] args)
        {
            // Create HiveMQ client options
            var options = new HiveMQClientOptions
            {
                Host = "broker.hivemq.com",
                Port = 1883 // Default MQTT port
            };

            // Instantiate the HiveMQ client with options
            var client = new HiveMQClient(options);

            // Event handler for received messages
            client.OnMessageReceived += (sender, args) =>
            {
                // Handle message payload
                string message = Encoding.UTF8.GetString(args.PublishMessage.Payload);
                Console.WriteLine($"Message Received: {message}");
                Console.WriteLine($"Topic: {args.PublishMessage.Topic}");
            };

            try
            {
                // Connect to the broker
                Console.WriteLine("Connecting to MQTT broker...");
                var connectResult = await client.ConnectAsync().ConfigureAwait(false);

                if (connectResult != null)
                {
                    Console.WriteLine("Connected successfully!");

                    // Subscribe to the topic
                    Console.WriteLine("Subscribing to topic...");
                    await client.SubscribeAsync("blcap-sep400/device").ConfigureAwait(false);
                    Console.WriteLine("Subscribed to topic: blcap-sep400/device");

                    Console.WriteLine("Listening for messages. Press Enter to exit...");
                    Console.ReadLine();
                }
                else
                {
                    Console.WriteLine("Failed to connect to MQTT broker.");
                }
            }
            catch (Exception ex)
            {
                Console.WriteLine($"Error: {ex.Message}");
            }
            finally
            {
                // Disconnect from the broker
                if (client.IsConnected())
                {
                    Console.WriteLine("Disconnecting from MQTT broker...");
                    await client.DisconnectAsync().ConfigureAwait(false);
                    Console.WriteLine("Disconnected.");
                }
            }
        }
    }
}
