String ssid = "Krish";
String password = "krishna1";
String APIKEY="ZS8ECY3BJRLJRCJ9";     // Replace with your Thingspeak apikey
String strdistance = "";
String server = "184.106.153.149"; //api.thingspeak.com
int pirpin = 34;
String Status = "false";
String parkingStatus = "false";
long currentValue = 0.00;
long previousValue = 0.00;

void setup() {
  pinMode(pirpin,INPUT);
  Serial1.begin(115200);
  Serial.begin(115200);
  delay(100);
  Serial.println("Started...");
  Serial1.println("AT+CWMODE=1\r");
  delay(1000);
  connectWifi();
}

void connectWifi() {
  String cmd = "AT+CWJAP=\"" + ssid + "\",\"" + password + "\"";
  Serial.println(cmd);
  Serial1.println(cmd);
  delay(4000);

  if (Serial1.find("OK")) {
    Serial.println("Connected!");
  }
  else {
    connectWifi();
    Serial.println("Cannot connect to wifi");
  }
}

void loop () {
  

  if(digitalRead(34)== HIGH)
  {
    currentValue = 1;
    Serial.println("intrusion detected");
    Serial.println(currentValue);
    httppost();
   }
  else
  {
    currentValue =0;
    httppost();
  }    
   
 }
 

void httppost() {

  Serial1.println("AT+CIPSTART=\"TCP\",\"" + server + "\",80");//start a TCP connection.
  delay(500);
  if ( Serial1.find("OK")) {
    Serial.println("TCP connection ready");
  } 
  else{
   Serial.println("TCP connection not ready");
  }
    String getStr = "GET /update?api_key=";
    getStr += APIKEY;
    getStr +="&field1=";
    getStr += String(currentValue);
    getStr += "\r\n\r\n";  
    String postRequest = "POST /update/ HTTP/1.1\n""Host: "+ server +"\n" "Connection: close\n""X-THINGSPEAKAPIKEY:"+APIKEY+"\n""Content-Type: application/x-www-form-urlencoded\n""Content-Length:"+getStr.length()+"\n\n";
     postRequest+=getStr;             
  String sendCmd = "AT+CIPSEND=";//determine the number of caracters to be sent.

  Serial1.print(sendCmd);
  Serial1.println(postRequest.length() );

  delay(500);

  if (Serial1.find(">")) {
    Serial.println("Sending.."); Serial1.print(postRequest);

    if ( Serial1.find("SEND OK")) {
      Serial.println("Packet sent");
      while (Serial1.available()) {
        String tmpRSerial1 = Serial1.readString();
        Serial.println(tmpRSerial1);
      }

      // close the connection
      Serial1.println("AT+CIPCLOSE");
    }
  }
}

/*long microsecondsToInches(long microseconds){
  
  return microseconds / 74 / 2;

}
 
long microsecondsToCentimeters(long microseconds){
  
  return microseconds / 29 / 2;
  
}*/

