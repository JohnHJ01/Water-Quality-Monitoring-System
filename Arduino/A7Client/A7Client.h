//A7Client.h
#ifndef _____A7_H__
#define _____A7_H__

#include <SoftwareSerial.h>
#include <Arduino.h>
#include <Client.h>


#define DEFAULT_TIMEOUT     		 10   //seconds
#define DEFAULT_INTERCHAR_TIMEOUT 6500   //miliseconds

class A7Client : public Client { //Was intending to use MQTT library which requires a CLient class. But oh well
	public:
	A7Client(uint8_t rx, uint8_t tx, uint32_t baudRate = 115200); //Create A7Client instance
	bool init();
	bool checkResponse(const char* resp, unsigned int timeout, unsigned int chartimeout);
	void changeBaud();
	bool startGPS(); //Send AT command to start GPS and repeat the data at normal Serial. Deault is once per 5 seconds	
	
	uint8_t hour, minute, seconds, year, month, day;
	uint16_t milliseconds;
  // Floating point latitude and longitude value in degrees.
  	float latitude, longitude;
  // Fixed point latitude and longitude value with degrees stored in units of 1/100000 degrees,
  // and minutes stored in units of 1/100000 degrees.  See pull #13 for more details:
  //   https://github.com/adafruit/Adafruit-GPS-Library/pull/13
  	int32_t latitude_fixed, longitude_fixed;
  	float latitudeDegrees, longitudeDegrees;
  	float geoidheight, altitude;
  	float speed, angle, magvariation, HDOP;
  	char lat, lon, mag;
  	bool fix;
  	uint8_t fixquality, satellites;

	bool readGPS();
	char* lastNMEA();
	uint8_t parseHex( char c);
	bool parse(char* nmea);
	virtual int connect(IPAddress ip, uint16_t port);
	virtual int connect(const char *host, uint16_t port);
	void A7_DEBUG(char *msg);
	virtual size_t write(uint8_t);
	virtual size_t write(char *buf);
	virtual size_t write(const uint8_t *buf, size_t size);
	virtual size_t writeSerial(uint8_t);
	virtual size_t writeSerial(char *buf);
	virtual size_t writeSerial(const uint8_t *buf, size_t size);
	virtual int available();
	virtual int read();
	virtual int read(uint8_t *buf, size_t size);
	virtual int peek();
	virtual void flush();
	virtual void stop();
	virtual uint8_t connected();
	virtual operator bool();
			
	private:	
	SoftwareSerial* serialA7;
	
};

#endif