//Christoph Schweiger (I/SO-43A) | August 2024
/*
#include <Arduino.h>
#include <WiFi.h>

void blink();
void wave();
void printWebsite(WiFiClient&);
void processClientRequests(WiFiClient&);
void pochen();

const char* ssid = "ESP32_LED";
const char* password = "kanyewest";

int blinkGeschlossenSpeed = 10;
int blinkOffenSpeed = 10;
int waveBB = 0;
int speedWave = 2;
int breakOnMaxWave = 500;
int waveMaxBrightness = 100;

int aufladen = 0;
int abladen = 255;

int waveCounter = 0;
int pochCounter = 0;

boolean auf = true;
boolean ab = true;

WiFiServer server(80); // PORT: 80 (Standard for HTTP)

// Variable to store the HTTP request
String header;

String pinOffenStatus = "aus";
String pinGeschlossenStatus = "aus";
String blinkStatus = "aus";
String waveStatus = "aus";
String pochStatus = "aus";

int pinOffen = 13;
int pinGeschlossen = 12;

unsigned long currentTime = millis();

unsigned long previousTime = 0; 

const long timeoutTime = 2000;

void setup() {
  pinMode(pinOffen, OUTPUT);
  pinMode(pinGeschlossen, OUTPUT);
  Serial.begin(115200);


  WiFi.softAP(ssid, password);

  Serial.println("Access Point available");
  Serial.print("IP address: ");
  Serial.println(WiFi.softAPIP());
  Serial.print("The password is: ");
  Serial.println(password);
  server.begin();
}

void loop() {
  WiFiClient client = server.available();
  if (client) {
    currentTime = millis();
    previousTime = currentTime;
    Serial.println("New Client.");
    String currentLine = "";
    while (client.connected() && currentTime - previousTime <= timeoutTime) {
      currentTime = millis();
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        header += c;
        if (c == '\n') {
          if (currentLine.length() == 0) {
            
            processClientRequests(client);
            
            // Display the HTML web page
            printWebsite(client);
            
            break;
          } else {
            currentLine = "";
          }
        } else if (c != '\r') {  
          currentLine += c;      
        }
      }
    }
    header = "";
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
  if(waveCounter >= 6){
    aufladen = 0;
    auf = true;
    waveStatus = "aus";
    pochStatus = "an";
  }
  if(pochCounter >= 10){
    pochStatus = "aus";
  }
  if(blinkStatus=="an"){
    blink();
  }
  if(waveStatus=="an"){
    wave();
  }
  if(pochStatus=="an"){
    pochen();
  }
}



void processClientRequests(WiFiClient& client){
  // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
  // and a content-type so the client knows what's coming, then a blank line:
  client.println("HTTP/1.1 200 OK");
  client.println("Content-type:text/html");
  client.println("Connection: close");
  client.println();
  
  // turns the GPIOs on and off
  if (header.indexOf("GET /26/on") >= 0) {
    Serial.println("GPIO 26 on");
    pinGeschlossenStatus="an";              
    analogWrite(pinGeschlossen, 255);
  } else if (header.indexOf("GET /26/off") >= 0) {
    Serial.println("GPIO 26 off");
    pinGeschlossenStatus="aus";
    analogWrite(pinGeschlossen, 0);
  } else if (header.indexOf("GET /27/on") >= 0) {
    Serial.println("GPIO 27 on");
    pinOffenStatus="an";
    analogWrite(pinOffen, 255);
  } else if (header.indexOf("GET /27/off") >= 0) {
    Serial.println("GPIO 27 off");
    pinOffenStatus="aus";
    analogWrite(pinOffen, 0);
  } else if(header.indexOf("GET /blink/off") >= 0) {
    Serial.println("blink aus");
    analogWrite(pinGeschlossen, 0);
    analogWrite(pinOffen, 0);
    blinkStatus = "aus";
  } else if(header.indexOf("GET /blink/on") >= 0) {
    Serial.println("blink ein");
    blinkStatus = "an";
  } else if(header.indexOf("GET /wave/off") >= 0){
    pochCounter = 0;
    waveCounter = 0;
    Serial.println("wave aus");
    analogWrite(pinOffen, 0);
    analogWrite(pinGeschlossen, 0);
    waveStatus = "aus";
    pochStatus = "aus";
  } else if(header.indexOf("GET /wave/on") >= 0){
    Serial.println("wave ein");
    waveStatus = "an";
    //wave();
    aufladen=waveBB;
    abladen=255;//waveMaxBrightness;
  } else if (header.indexOf("GET /setBlinkSpeed?value=") >= 0) {
    int pos = header.indexOf("GET /setBlinkSpeed?value=") + 25;
    String valueStr = header.substring(pos);
    blinkGeschlossenSpeed = valueStr.toInt();
    Serial.println("Set Blink Speed to: " + String(blinkGeschlossenSpeed));
  } else if (header.indexOf("GET /setwaveBB?value=") >= 0) {
    int pos = header.indexOf("GET /setwaveBB?value=") + 21;
    String valueStr = header.substring(pos);
    int index = valueStr.indexOf(" HTTP/1.1");
    if(index != -1){
      valueStr.remove(index, 9);
    }
    waveBB = valueStr.toInt();
    aufladen = waveBB; //for animation synchronisation
    Serial.println("Set waveBB to: " +valueStr);
  } else if (header.indexOf("GET /setSpeedWave?value=") >= 0){
    int pos = header.indexOf("GET /setSpeedWave?value=") + 24;
    String valueStr = header.substring(pos);
    int index = valueStr.indexOf(" HTTP/1.1");
    if(index != -1){
      valueStr.remove(index, 9);
    }
    speedWave = valueStr.toInt();
    Serial.println("Set wave speed to: "+valueStr);
  } else if(header.indexOf("GET /breakOnMaxWave?value=")>= 0){
    int pos = header.indexOf("GET /breakOnMaxWave?value=") + 26;
    String valueStr = header.substring(pos);
    int index = valueStr.indexOf(" HTTP/1.1");
    if(index != -1){
      valueStr.remove(index, 9);
    }
    breakOnMaxWave = valueStr.toInt();
    Serial.println("Set breakOnMaxWave to: "+valueStr);
  } else if(header.indexOf("GET /waveMaxBrightness?value=")>= 0){
    int pos = header.indexOf("GET /waveMaxBrightness?value=") + 29;
    String valueStr = header.substring(pos);
    int index = valueStr.indexOf(" HTTP/1.1");
    if(index != -1){
      valueStr.remove(index, 9);
    }
    waveMaxBrightness = valueStr.toInt();
    abladen = waveMaxBrightness;
    Serial.println("Set waveMaxBrightness to: "+valueStr);
  }
}

void printWebsite(WiFiClient& client){
  client.println("<!DOCTYPE html><html>");
  client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
  client.println("<link rel=\"icon\" href=\"data:,\">");
  // CSS to style the on/off buttons 
  // Feel free to change the background-color and font-size attributes to fit your preferences
  client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center; color: white}");
  client.println(".button { background-color: #F50537; border: none; color: white; padding: 16px 40px;");
  client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
  client.println(".button2 {background-color: #555555;}</style></head>");
  
  client.println("<body style=\"background-color: #000000;\"><h1>LED Steuerung</h1>");
  
  client.println("<p>LED offen - Status</p>");
  if(pinOffenStatus=="aus"){     
    client.println("<p><a href=\"/27/on\"><button class=\"button\">AN</button></a></p>");
  } else {
    client.println("<p><a href=\"/27/off\"><button class=\"button button2\">AUS</button></a></p>");
  }
  
  client.println();

  client.println("<p>LED geschlossen - Status</p>"); 
  if(pinGeschlossenStatus=="aus"){
    client.println("<p><a href=\"/26/on\"><button class=\"button\">AN</button></a></p>");
  } else {
    client.println("<p><a href=\"/26/off\"><button class=\"button button2\">AUS</button></a></p>");
  }

  client.println();
  client.println("<p>Blink-Animation starten</p>"); 
  if(blinkStatus=="aus"){     
    client.println("<p><a href=\"/blink/on\"><button class=\"button\">AN</button></a></p>");
  } else {
    client.println("<p><a href=\"/blink/off\"><button class=\"button button2\">AUS</button></a></p>");
  }
  client.println();

  
  client.println("<p>Geschw. Blink Ani. [0-200ms]</p>");
  client.println("<input type=\"range\" min=\"0\" max=\"200\" value=\""+String(blinkGeschlossenSpeed)+"\" id=\"blinkSpeed\" onchange=\"updateBlinkSpeedGeschlossen(this.value)\">");
  client.println("<p id='blinkspeedP'>"+String(blinkGeschlossenSpeed)+"ms</p>");
  client.println();

  client.println("<p>Wellen-Animation starten</p>"); 
  if(waveStatus=="aus"){     
    client.println("<p><a href=\"/wave/on\"><button class=\"button\">AN</button></a></p>");
  } else {
    client.println("<p><a href=\"/wave/off\"><button class=\"button button2\">AUS</button></a></p>");
  }
  
  client.println("<p>Black Offset [0-200]</p>");
  client.println("<input type=\"range\" min=\"0\" max=\"200\" value=\""+String(waveBB)+"\" id=\"waveBB\" onchange=\"updateWaveBB(this.value)\">");
  client.println("<p id='waveBBP'>"+String(waveBB)+"</p>");
  client.println();

  client.println("<p>Pause zwischen Helligkeitswechsel</p>");
  client.println("<input type=\"range\" min=\"0\" max=\"20\" value=\""+String(speedWave)+"\" id=\"speedWave\" onchange=\"updateSpeedWave(this.value)\">");
  client.println("<p id='speedwaveP'>"+String(speedWave)+"ms</p>");
  client.println();

  client.println("<p>Pause bei Maximalhelligkeit</p>");
  client.println("<input type=\"range\" min=\"0\" max=\"500\" value=\""+String(breakOnMaxWave)+"\" id=\"breakOnMaxWave\" onchange=\"updateOnMaxWave(this.value)\">");
  client.println("<p id='speedwaveP'>"+String(breakOnMaxWave)+"ms</p>");
  client.println();

  client.println("<p>Maximalhelligkeit</p>");
  client.println("<input type=\"range\" min=\"0\" max=\"100\" value=\""+String(waveMaxBrightness)+"\" id=\"waveMaxBrightness\" onchange=\"updateWaveMaxBrightness(this.value)\">");
  client.println("<p id='waveMaxBrightnessP'>"+String(waveMaxBrightness)+"%</p>");
  client.println();
  
  client.println("</body></html>");
  client.println("<script>");
  client.println("function updateBlinkSpeedGeschlossen(value) {");
  client.println("  document.getElementById('blinkspeedP').textContent=value.toString()+'ms';");
  client.println("  var xhr = new XMLHttpRequest();");
  client.println("  xhr.open('GET', '/setBlinkSpeed?value=' + value, true);");
  client.println("  xhr.send();");
  client.println("}");
  client.println("function updateWaveBB(value) {");
  client.println("  console.log(value);");
  client.println("  document.getElementById('waveBBP').textContent=value.toString();");
  client.println("  var xhr = new XMLHttpRequest();");
  client.println("  xhr.open('GET', '/setwaveBB?value=' + value, true);");
  client.println("  xhr.send();");
  client.println("}");

  client.println("function updateSpeedWave(value) {");
  client.println("  console.log(value);");
  client.println("  document.getElementById('speedwaveP').textContent=value.toString()+'ms';");
  client.println("  var xhr = new XMLHttpRequest();");
  client.println("  xhr.open('GET', '/setSpeedWave?value=' + value, true);");
  client.println("  xhr.send();");
  client.println("}");

  client.println("function updateWaveMaxBrightness(value) {");
  client.println("  console.log(value);");
  client.println("  document.getElementById('waveMaxBrightnessP').textContent=value.toString()+'%';");
  client.println("  var xhr = new XMLHttpRequest();");
  client.println("  xhr.open('GET', '/waveMaxBrightness?value=' + value, true);");
  client.println("  xhr.send();");
  client.println("}");

  client.println("function updateOnMaxWave(value) {");
  client.println("  console.log(value);");
  client.println("  document.getElementById('breakOnMaxWave').textContent=value.toString()+'ms';");
  client.println("  var xhr = new XMLHttpRequest();");
  client.println("  xhr.open('GET', '/breakOnMaxWave?value=' + value, true);");
  client.println("  xhr.send();");
  client.println("}");
  client.println("</script>");
}

void blink(){
  analogWrite(pinOffen, 255);
  analogWrite(pinGeschlossen, 0);
  delay(blinkGeschlossenSpeed);
  analogWrite(pinOffen, 0);
  analogWrite(pinGeschlossen, 255);
  delay(blinkGeschlossenSpeed);
}

/*void wave(){
  if(aufladen < 255){
    aufladen = aufladen +1;
    analogWrite(pinOffen, aufladen);
    analogWrite(pinGeschlossen, 255-aufladen);
    delay(speedWave);
    abladen = int((waveBB*255)/100);
  }
  else if(aufladen==255 && abladen < 255){
    abladen = abladen + 1;
    analogWrite(pinGeschlossen, abladen);
    analogWrite(pinOffen, 255-abladen);
    delay(speedWave);
  }
  if(abladen>=255){
    aufladen = int((waveBB*255)/100);
  }

  Serial.print("||| aufladen: "); Serial.print(aufladen); Serial.print(" ||| abladen: "); Serial.print(abladen); Serial.print(" |||"); Serial.println(waveBB);
}*/
/*
void wave(){
  if(auf){
    aufladen = aufladen + 1;
    analogWrite(pinOffen, aufladen);
    if(aufladen >= int(255*(waveMaxBrightness*0.01))){ //replace 255 with white OFFSET (if required)
      auf = false;
    }
  }else{
    aufladen = aufladen - 1;
    analogWrite(pinOffen, aufladen);
    if(aufladen <= waveBB){
      auf=true;
    }
  }

  if(ab){
    abladen = abladen - 1;
    analogWrite(pinGeschlossen, abladen);

    if(abladen <= waveBB){
      ab = false;
    }
  }else{
    abladen = abladen + 1;
    analogWrite(pinGeschlossen, abladen);

    if(abladen >= int(255*(waveMaxBrightness*0.01))){ //replace 255 with white OFFSET (if required)
      ab = true;
    }
  }

  if(abladen == waveBB || aufladen== waveBB || abladen == 255 || aufladen == 255){
    delay(breakOnMaxWave);
  }else{
    delay(speedWave);
  }
}  
*/
/*
void wave(){
  for(int i=0; i<3; i++){
    if(auf){
      aufladen = aufladen + 1;
      analogWrite(pinOffen, aufladen);
      if(aufladen >= 255){ //replace 255 with white OFFSET (if required)
        auf = false;
      }
    }else{
      aufladen = aufladen - 1;
      analogWrite(pinOffen, aufladen);
      if(aufladen <= 0){
        auf=true;
      }
    }

    if(ab){
      abladen = abladen - 1;
      analogWrite(pinGeschlossen, abladen);

      if(abladen <= 0){
        ab = false;
      }
    }else{
      abladen = abladen + 1;
      analogWrite(pinGeschlossen, abladen);

      if(abladen >= 255){ //replace 255 with white OFFSET (if required)
        ab = true;
      }
    }

    //Serial.print("||| aufladen: "); Serial.print(aufladen); Serial.println(waveBB);

    if(abladen == waveBB || aufladen== waveBB || abladen == 255 || aufladen == 255){
      waveCounter = waveCounter + 1;
      delay(132);
    }else{
      delay(2);
    }
  }
} */
/*
void pochen(){
  if(auf){
    aufladen = aufladen + 1;
    analogWrite(pinOffen, aufladen);
    analogWrite(pinGeschlossen, aufladen);
    if(aufladen >= 255){ //replace 255 with white OFFSET (if required)
      auf = false;
    }
  }else{
    aufladen = aufladen - 1;
    analogWrite(pinOffen, aufladen);
    if(aufladen <= 0){
      auf=true;
    }
  }



  if(aufladen == 0 || aufladen == 255){
    pochCounter = pochCounter + 1;
    delay(132);
  }else{
    delay(2);
  }
}

*/