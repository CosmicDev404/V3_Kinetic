#include <Servo.h>
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WebSocketsServer.h>

const int inA = 3; //!rx pin
const int inB = D1;
const int inC = D2;
const int inD = 1; //!tx pin
const int enA = D6;
const int enB = D7;
const int lightCove = D0; //status/ accessory light

Servo ser;

int servo = 45; //servo centre, change it as per servo arrangement
int left = 0;
int right = 0;
bool lstate = 0;

unsigned long lastPacket = 0;
unsigned long ltime = 0;

const char* AP_SSID = "V3 Kinetic";
const char* AP_PASSWORD = "AgiI-BAS0007(404)";

ESP8266WebServer server(80);
WebSocketsServer webSocket = WebSocketsServer(81);

const char webpage[] PROGMEM = R"rawliteral(!put web controller html code here!)rawliteral";

void webSocketEvent(uint8_t num, WStype_t type, uint8_t *payload, size_t length) { //data extract from web controller
  if (type == WStype_TEXT) {
    int tempServo, tempLeft, tempRight;

    if (sscanf((char*)payload, "%d,%d,%d", &tempServo, &tempLeft, &tempRight) == 3) {
      lastPacket = millis();
      if (tempServo != servo) { //give commands only when changed
        servo = tempServo;
        ser.write(servo);
      }
      if (tempLeft != left) {
        left = tempLeft;
        m1(left);
      }
      if (tempRight != right) {
        right = tempRight;
        m2(right);
      }
      if (tempLeft == 0 && tempRight == 0 && tempServo == 45){cove(true);} else {cove(false);} //park indicator
    }
  }
}

void m1(int value){ //motor 1 controller
  int speed = map(abs(value), 1, 4, 100, 255);
  if (value > 0 && value < 5){
    digitalWrite(inB, HIGH);
    digitalWrite(inA, LOW);
  } else if (value < 0 && value > -5){//castor braking
    digitalWrite(inB, LOW);
    digitalWrite(inA, HIGH);
  } else if (value == 0) {
    speed = 0;
  }
   else{//hard stop
    speed = 255;
    digitalWrite(inA, LOW);
    digitalWrite(inB, LOW);
  }
  analogWrite(enA, speed);
}

void m2(int value){ //motor 2 controller
  int speed = map(abs(value), 1, 4, 100, 255);
  if (value > 0 && value < 5){
    digitalWrite(inD, HIGH);
    digitalWrite(inC, LOW);
  } else if (value < 0 && value > -5){
    digitalWrite(inD, LOW);
    digitalWrite(inC, HIGH);
  } else if (value == 0){//castor braking
    speed = 0;
  }
  else{//hard stop
    speed = 255;
    digitalWrite(inC, LOW);
    digitalWrite(inD, LOW);
  }
  analogWrite(enB, speed);
}

void cove(bool input){ //simple inbuilt led controller function
  if (input){
    digitalWrite(lightCove, LOW);
  } else{
    digitalWrite(lightCove, HIGH);
  }
}

void setup() {
  Serial.end();
  ser.attach(D5, 544, 2400); 

  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(inA, OUTPUT);
  pinMode(inB , OUTPUT);
  pinMode(inC , OUTPUT);
  pinMode(inD , OUTPUT);
  pinMode(lightCove, OUTPUT);

  WiFi.mode(WIFI_AP);
  WiFi.softAP(AP_SSID, AP_PASSWORD);

  server.on("/", HTTP_GET, []() {
    server.send_P(200, "text/html", webpage);
  });

  server.begin();
  analogWriteRange(255); //set range to familiar 0-255
  webSocket.begin();
  webSocket.onEvent(webSocketEvent);
}

void loop() {
  server.handleClient();
  webSocket.loop();
  if (millis()-lastPacket >= 250){ //connection lost -> park
    ser.write(50); 
    m1(5); //triggers else case => both inputs low => safely parked car
    m2(5);
    if (millis()-ltime >= 250){ //blinking for connection
      cove(lstate);
      lstate = !lstate;
      ltime = millis();
    }
  }
}
