#include "application.h"
#include <stdio.h>
#include <string.h>

#define BUFF_SIZE 128

// 0 - no serial output
// 1 - print waittime
// 2 - also print debug messages
// 3 - also print http response
#define SPRINTLVL 2

void httpRequest(void);
void count(int number);
void blink(int onTime, int offTime);

int led = D7;
char server[] = "api.vasttrafik.se";
TCPClient client;
unsigned long lastConnectionTime = 0;           // last time you connected to the server, in milliseconds
bool lastConnected = false;                  // state of the connection last time through the main loop
bool lastAvailable = false;
bool timeFound = false;
const unsigned long postingInterval = 10*1000;  // delay between updates, in milliseconds
char buff[BUFF_SIZE];
int waittime=0;
struct time{
    int hours;
    int minutes;
};
struct time servertime={0,0}, realtime={0,0};


void setup() {
   pinMode(led, OUTPUT);
   //Initialize serial and wait for port to open:
   Serial.begin(9600);
   delay(1000);
   count(10);
   if(SPRINTLVL>1) Serial.println(">>> VTDT_V0.7");
   if(SPRINTLVL>1) Serial.println();
}

void loop() {
    while (client.available() && !timeFound) {
        int index=0;
        char c;
        int i = 0;
        do {
            c = client.read();
            if(SPRINTLVL>2) Serial.write(c);
            buff[index++] = c;
            if(i++ > 10) {
                delay(100);
                i = 0;
            }
        } while (c != '\n');
        buff[index] = '\0';

        char key1[] = "servertime";
        char *found = strstr(buff, key1);

        if (found != NULL) {
            long index = found - buff;
            servertime.hours = (buff[index+strlen(key1)+3] - '0')*10 + (buff[index+strlen(key1)+4] - '0');
            servertime.minutes = (buff[index+strlen(key1)+6] - '0')*10 + (buff[index+strlen(key1)+7] - '0');
        }

        char key2[] = "rtTime";
        found = strstr(buff, key2);
        if (found != NULL) {
            long index = found - buff;
            realtime.hours = (buff[index+strlen(key2)+3] - '0')*10 + (buff[index+strlen(key2)+4] - '0');
            realtime.minutes = (buff[index+strlen(key2)+6] - '0')*10 + (buff[index+strlen(key2)+7] - '0');

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

            if(SPRINTLVL>0) Serial.println();
            if(SPRINTLVL>0) Serial.println();
            if(SPRINTLVL>0) Serial.print(">>> Waittime is ");
            if(SPRINTLVL>0) Serial.print(waittime);
            if(SPRINTLVL>0) Serial.print(" minutes!");
            if(SPRINTLVL>0) Serial.println();
            if(SPRINTLVL>0) Serial.println();
            if (waittime < 20) {
                count(waittime);
            }
            timeFound = true;
        }
        lastAvailable = true;
    }

    if (client.connected() && lastAvailable && timeFound) {
        if(SPRINTLVL>1) Serial.println(">>> Stopping client since time found.");
        if(SPRINTLVL>1) Serial.println();
        delay(300);
        client.stop();
        lastAvailable = false;
    }

    if ( client.connected() && lastAvailable && !client.available() ) {
        if(SPRINTLVL>1) Serial.println(">>> Stopping client since no more data.");
        if(SPRINTLVL>1) Serial.println();
        delay(300);
        client.stop();
        lastAvailable = false;
    }

    // if there's no net connection, but there was one last time
    // through the loop, then stop the client:
    if (!client.connected() && lastConnected) {
        if(SPRINTLVL>1) Serial.println(">>> Disconnecting.");
        if(SPRINTLVL>1) Serial.println();
        delay(300);
        client.stop();
    }

    // if you're not connected, and ten seconds have passed since
    // your last connection, then connect again and send data:
    if(!client.connected() && (millis() - lastConnectionTime > postingInterval)) {
        if(SPRINTLVL>1) Serial.println(">>> Trying to connect (again after 10 s)...");
        if(SPRINTLVL>1) Serial.println();
        timeFound = false;
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
        if(SPRINTLVL>1) Serial.println(">>> httpRequest() connecting...");
        if(SPRINTLVL>1) Serial.println();
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
        if(SPRINTLVL>1) Serial.println(">>> Connection failed!");
        if(SPRINTLVL>1) Serial.println(">>> Disconnecting!");
        if(SPRINTLVL>1) Serial.println();
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
