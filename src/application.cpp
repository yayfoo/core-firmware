#include "application.h"

void blink(int onTime, int offTime);
void count(int number);
String http_get(char const* hostname, String path);

#define DEBUG true
int led = D7;
const char* query = "/bin/rest.exe/v1/departureBoard?authKey=f3c144b3-d974-490e-afc2-ff83d0f7b620&format=xml&id=9021014007900000&direction=9021014001760000&timeSpan=30&maxDeparturesPerLine=1";

void setup()
{
	pinMode(led, OUTPUT);
    blink(200,1000);
	if(DEBUG) Serial.begin(9600);
    if(DEBUG) blink(2000,0);
    if(DEBUG) delay(5000);
    if(DEBUG) Serial.println("setup() done!");
}

void loop()
{
    blink(200,0);

    if(DEBUG) Serial.println();
    if(DEBUG) Serial.println("Connecting...");
    String resp = http_get("api.vasttrafik.se", query);
    if(DEBUG && NULL!=resp) Serial.println(resp);

    if(DEBUG) Serial.println();
    if(DEBUG) Serial.println("Wait ten seconds.");
    delay(10 * 1000);
}

TCPClient client;
char buffer[512];

String http_get(char const* hostname, String path)
{
	if (client.connect(hostname, 80)) {
		client.print("GET ");
		client.print(path);
		client.print(" HTTP/1.0\n");
		client.print("HOST: ");
		client.println(hostname);
		client.print("\n");
		client.flush();
	}
    else
    {
		if(DEBUG) Serial.println("Connection failed!");
		client.stop();
		return NULL;
	}

	// Block until first byte is read.
	client.read();
	for (unsigned int i = 0; i < sizeof(buffer) && client.available(); i++)
    {
		char c = client.read();
		if (c == -1)
        {
			break;
		}
		buffer[i] = c;
	}
	client.stop();

	String response(buffer);
	return response.substring(4);

/*	String response(buffer);
	int bodyPos = response.indexOf("\r\n\r\n");
	if (bodyPos == -1)
    {
		if(DEBUG) Serial.println("Can not find http response body");
		return NULL;
	}
	return response.substring(bodyPos + 4);
*/
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
