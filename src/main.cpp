#include <Arduino.h>
#include <SPI.h>
#include <RH_ASK.h>

void setupDisplay();

const int DEVICE_ID = 1; 

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
  uint8_t buf[32];
  uint8_t buflen = sizeof(buf);
  while (!driver.available()){
	  //do nothing
  }
  if(driver.recv(buf, &buflen)){
	    //PrintData(buf,buflen);
      String sbuf((char *)buf);
      Serial.println(sbuf);
      char i = sbuf.charAt(0);
      String s = String(i);
      int index = s.toInt();

      if(index == DEVICE_ID){
        String output((char*)buf+1);
        //Serial.println(output);
        return output;
      }
      else{
        return "";
      }
    	  
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
  Serial.println(output);
  if (output.length()>0) {
    unsigned long recived = output.toInt();
    unsigned long h = recived / 3600;
    unsigned long m = (recived - (h * 3600)) / 60;
    unsigned long s = recived - ((h * 3600) + (m * 60));
    char time[32];
    sprintf (time, "%02ld:%02ld:%02ld", h, m, s);
    String text = String(time);
    //Display on Matix
	  setDisplay(text);
  }
}