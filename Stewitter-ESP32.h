/*
  Stewitter-ESP32.h - Arduino-IDE for ESP32 library to Post messages to Twitter with OAuth.
*/


#ifndef Stewitter_ESP32_H
#define Stewitter_ESP32_H

#include <Arduino.h>
#include <WiFi.h>

class Stewitter
{
private:
	WiFiClient client;
    String httpBody;
	const char *token;
	int statusCode;
	uint8_t parseStatus;
	bool flag = false;
public:
	Stewitter(const char *token);
	bool post(const char *msg);
    bool lastMention(void);
	bool checkStatus(Print *debug = NULL);
	int  wait(Print *debug = NULL);
	int  status(void) { return statusCode; }
    String& response(void) { return httpBody; }
};

#endif	//Stewitter_ESP32_H
