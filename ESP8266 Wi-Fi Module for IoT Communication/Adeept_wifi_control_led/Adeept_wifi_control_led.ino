/*************************************
File name:Adeept_wifi_control_led
Description:
Website:www.addept.com
E-mail:support@addept.com
Author:felix
Date:2019/6/10
*************************************/
#include<SoftwareSerial.h>    //use the library to commmunicate with esp8266 wifi module
#define rxPin 2               //define rx and tx pin
#define txPin 3

SoftwareSerial mySerial = SoftwareSerial(rxPin,txPin); //creat an object mySerial

//define esp8266 wifi module variate
char judge = 0;
String comdata = "";
//define receive data
String text1 = "\r\n+IPD,0,1:1";
String text2 = "\r\n+IPD,0,1:2";

// put your setup code here, to run once:
void setup() {
  pinMode(13,OUTPUT);
  mySerial.begin(115200);                  // set up a wifi serial communication baud rate 115200
   delay(4000);
   mySerial.println("AT+RST\r\n");         //reset wifi
   delay(5000);     
   delay(5000);     
   mySerial.println("AT+CWMODE=3\r\n");    //set to softAP+station mode
   delay(4000);     
   mySerial.println("AT+CIPMUX=1\r\n");    //set to multi-connection mode
   delay(4000);
   mySerial.println("AT+CIPSERVER=1\r\n"); //set as server
   delay(4000);
   mySerial.println("AT+CIPSTO=7000\r\n"); //keep the wifi connecting 7000 seconds
   delay(4000);
   digitalWrite(13,HIGH);                  //configuration is complete
   delay(1000);
   digitalWrite(13,LOW);
}

// put your main code here, to run repeatedly:
void loop() {
  //receive the data
  while(mySerial.available()>0)
   {  
    comdata += char(mySerial.read());
    delay(1);
   }

   
  //set the judge
  judgement();
  
  //judge the variate "judge"
           switch(judge)
     {
         case 1: while(!mySerial.available()){digitalWrite(13,HIGH); }
                   break;
         case 2: while(!mySerial.available()) {digitalWrite(13,LOW);} 
                   break;     
         default:  break;
     }
}


  //set the judge
void judgement(){
    if (comdata.length() > 0)
    {
        if(comdata==text1){
          judge=1;
        }
        if(comdata==text2){
          judge=2;
        }
        comdata = "";
    }
}
