#include "application.h"

void blink(int onTime, int offTime);

// We name pin D0 as led
int led = D7;

TCPClient client;
byte server[] = { 193, 44, 177, 70 }; // api.vasttrafik.se

// This routine runs only once upon reset
void setup()
{
  // Initialize D0 pin as an output
  pinMode(led, OUTPUT);

  delay(5000);
  blink(200,1000);
  Serial.begin(9600);
  blink(2000,0);
  delay(5000);
  Serial.println("Entered setup()...");

  // Setup http-data request format
  if (client.connect(server, 80))
  {
    Serial.println("Client Connected!");
    client.println("GET /bin/rest.exe/v1/departureBoard?authKey=f3c144b3-d974-490e-afc2-ff83d0f7b620&format=xml&id=9021014007900000&direction=9021014001760000&timeSpan=30&maxDeparturesPerLine=1 HTTP/1.0");
    client.println();
  }
  else
  {
    Serial.println("Failed to connect client to server!");
  }

}

// This routine loops forever
void loop()
{
  // Request http-data from host
  // Parse remaining minutes
  // Blink LED corresponding to remaining minutes
  while (client.available())
  {
    char c = client.read();
    Serial.print(c);
  }

  if (!client.connected())
  {
    Serial.println();
    Serial.println("Client disconnected!");
    client.stop();
    for(;;)
    Serial.print("x");
  }

}

void count(int number)
{
    while (number > 0)
    {
        blink(200,100);
        number--;
    }
}

void blink(int onTime, int offTime)
{
  digitalWrite(led, HIGH);   // Turn ON the LED
  delay(onTime);               // Wait for 1000mS = 1 second
  digitalWrite(led, LOW);    // Turn OFF the LED
  delay(offTime);               // Wait for 1 second
}
