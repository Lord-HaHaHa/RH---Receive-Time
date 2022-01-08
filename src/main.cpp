#include <Arduino.h>
#include <SPI.h>
#include <RH_ASK.h>

void setupDisplay();

RH_ASK driver(2000, 5,4);

void setup() {  
  Serial.begin(74880);
  while(!Serial);
  if(!driver.init())
    Serial.println("init failed");
  setupDisplay();
}

void PrintData(uint8_t* data, uint8_t size) {
   Serial.print(size);
   Serial.print(" : ");
   for (int i=0;i<size;i++){
	   Serial.print(data[i],16);
	   Serial.print(" ");
   }
   Serial.println();
}

String getData() {
  uint8_t buf[8];
  uint8_t buflen = sizeof(buf);
  //RH
  while (!driver.available()){
	  //do nothing
  }
  if(driver.recv(buf, &buflen)){
	    //PrintData(buf,buflen);
    	String output((char*)buf);
		//Serial.println(output);
		return output;
  	}
	else
	{
		return "";
	}

}

void setDisplay(String& time);

void loop() {
  // put your main code here, to run repeatedly:
  String output = getData();
  if (output.length()>0) {
    unsigned long recived = output.toInt();
    unsigned long h = recived / 3600;
    unsigned long m = (recived - (h * 3600)) / 60;
    unsigned long s = recived - ((h * 3600) + (m * 60));
    String time = String(h) + ":" + String(m) + ":" + String(s);
    
    //Display on Matix
	setDisplay(time);
  }
}