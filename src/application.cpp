#include "application.h"
#include <stdio.h>
#include <string.h>

void httpRequest(void);
void count(int number);
void blink(int onTime, int offTime);

#define BUFF_SIZE 256
struct time {
    int hours;
    int minutes;
};
int led = D7;
char server[] = "api.vasttrafik.se";
TCPClient client;
unsigned long lastConnectionTime = 0; // last time you connected to the server, in milliseconds
bool lastConnected = false; // state of the connection last time through the main loop
const unsigned long postingInterval = 10*1000; // delay between updates, in milliseconds
bool lastAvailable = false;
//char line[BUFF_SIZE];
struct time servertime={0,0}, realtime={0,0};
int waittime=0;

void setup() {
   //Initialize serial and wait for port to open:
   count(2);
   Serial.begin(9600);
   delay(1000);
   count(5);
}

void loop() {
uint32_t bytesAvail = client.available();
uint32_t ptr=0;
char line[512];
    while (bytesAvail > 0) {
        bytesAvail--;
        line[ptr++] = client.read();
    }
line[ptr] = '\0';

        Serial.println();
        Serial.println();
        Serial.print("-> Created line out of chars:");
        Serial.println();
        Serial.write(line);
        Serial.println();
        Serial.println();

        char key1[] = "servertime";
        char *found = strstr(line, key1);

        if (found != NULL) {
            long index = found - line;
            servertime.hours = (line[index+strlen(key1)+3] - '0')*10 + (line[index+strlen(key1)+4] - '0');
            servertime.minutes = (line[index+strlen(key1)+6] - '0')*10 + (line[index+strlen(key1)+7] - '0');
        }

        char key2[] = "rtTime";
        found = strstr(line, key2);
        if (found != NULL) {
            long index = found - line;
            realtime.hours = (line[index+strlen(key2)+3] - '0')*10 + (line[index+strlen(key2)+4] - '0');
            realtime.minutes = (line[index+strlen(key2)+6] - '0')*10 + (line[index+strlen(key2)+7] - '0');

            //realtime.hours is always equal to or greater than servertime.hours, except at night wrap
            if (realtime.hours < servertime.hours){
                waittime = (24-servertime.hours)*60 + (realtime.hours*60);
            } else {
                waittime = (realtime.hours-servertime.hours)*60;
            }
            //realtime.minutes is always equal to or greater than servertime.minutes, except at hour wrap
            if ((realtime.minutes < servertime.minutes) && (waittime == 0)) {
                //avoid exception if 24 hours have passed
                waittime = 24*60;
            }
            waittime = waittime + realtime.minutes - servertime.minutes;

            Serial.println();
            Serial.println();
            Serial.print("-> Waittime is ");
            Serial.print(waittime);
            Serial.print(" minutes");
            Serial.println();
            Serial.println();
            if (waittime < 20) {
                count(waittime);
            }
        }
        lastAvailable = true;
    //}

    if (client.connected() && lastAvailable && !client.available()) {
        Serial.println("-> Stopping client since no more data.");
        delay(300);
        client.stop();
        lastAvailable = false;
    }

    // if there's no net connection, but there was one last time
    // through the loop, then stop the client:
    if (!client.connected() && lastConnected) {
        Serial.println();
        Serial.println("-> Disconnecting.");
        client.stop();
    }

    // if you're not connected, and ten seconds have passed since
    // your last connection, then connect again and send data:
    if(!client.connected() && (millis() - lastConnectionTime > postingInterval)) {
        Serial.println();
        Serial.println("-> Trying to connect again since ten seconds has passed...");
        httpRequest();
    }
    // store the state of the connection for next time through
    // the loop:
    lastConnected = client.connected();
}

// this method makes a HTTP connection to the server:
void httpRequest() {
    // if there's a successful connection:
    if (client.connect(server, 80)) {
        Serial.println("-> Connecting...");
        // send the HTTP PUT request:
        client.println("GET /bin/rest.exe/v1/departureBoard?authKey=f3c144b3-d974-490e-afc2-ff83d0f7b620&format=json&jsonpCallback=processJSON&id=9021014007900000&direction=9021014001760000&timeSpan=60&maxDeparturesPerLine=1 HTTP/1.1");
        client.println("Host: api.vasttrafik.se");
        client.println("User-Agent: spark.core-wifi");
        client.println("Connection: close");
        client.println();

        // note the time that the connection was made:
        lastConnectionTime = millis();
    } else {
        // if you couldn't make a connection:
        Serial.println("-> Connection failed!");
        Serial.println("-> Disconnecting.");
        client.stop();
    }
}

void count(int number) {
    while (number > 0) {
        blink(200,100);
        number--;
    }
}

void blink(int onTime, int offTime) {
    digitalWrite(led, HIGH);   // Turn ON the LED
    delay(onTime);               // Wait for 1000mS = 1 second
    digitalWrite(led, LOW);    // Turn OFF the LED
    delay(offTime);               // Wait for 1 second
}
