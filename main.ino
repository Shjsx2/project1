#include <WiFi.h>
#include <ArduinoWebsockets.h>

using namespace websockets;

const char* ssid     = "Poop"; // Change this to your WiFi SSID
const char* password = "00000000"; // Change this to your WiFi password

#define haptics 2

int haplevel = 1;//vibration frequency 5最大 1最小

int a = 51, b = 102, c = 153, d = 204, e = 255;

boolean powerstate = true;//toggle on (没写)
String uart = "";

WebsocketsClient client;
const char* server = "localhost:8080"

double intensity = 0.0; // current vibration intensity
unsigned long lastReceivedTime = 0; // last time a message was received from server

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(haptics, OUTPUT);
  digitalWrite(haptics, LOW);
  //unable to vibrate without connecting to WIFI
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  /** Websocket initialization */
  client.onMessage(onMessage);
  client.onEvent(event);

  client.connect(server);
}

void onMessage(WebsocketsMessage message) {
  Serial.print("Got Message: ");
  Serial.println(message.data());

  // parse message
  // check if data is parsable to double
  double receivedIntensity = message.data().toDouble();
  if (receivedIntensity != 0.0) {
    intensity = message.data().toDouble();
  }
  lastReceivedTime = millis();
  Serial.print("Intensity: ");
  Serial.println(intensity);
  Serial.print("Last Received Time: ");
  Serial.println(lastReceivedTime);
}

void onEvents(WebsocketsEvent event, String data) {
    if(event == WebsocketsEvent::ConnectionOpened) {
        Serial.println("Connnection Opened");
    } else if(event == WebsocketsEvent::ConnectionClosed) {
        Serial.println("Connnection Closed");
    } else if(event == WebsocketsEvent::GotPing) {
        Serial.println("Got a Ping");
    } 
}


void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available() > 0) {
    uart = Serial.readString();
    haplevel = uart.toInt();
  }

  client.poll(); // receive new message from server

  if (powerstate == true) {
    if (haplevel == 1) {
      for (int i = 0; i < a; i++) { //由于存储器位数的限制，i的范围为0~255
        analogWrite(haptics, i); //输出逐渐升高的电平
        delay(10);//有延迟停留，让人眼能分辨光亮暗的变化
      }
      for (int i = a; i > 0; i--) { //输出逐渐降低的电平
        analogWrite(haptics, i);
        delay(10);
      }
    } else if (haplevel == 2) {
      for (int i = 0; i < b; i++) { //由于存储器位数的限制，i的范围为0~255
        analogWrite(haptics, i); //输出逐渐升高的电平
        delay(10);//有延迟停留，让人眼能分辨光亮暗的变化
      }
      for (int i = b; i > 0; i--) { //输出逐渐降低的电平
        analogWrite(haptics, i);
        delay(10);
      }
    } else if (haplevel == 3) {
      for (int i = 0; i < c; i++) { //由于存储器位数的限制，i的范围为0~255
        analogWrite(haptics, i); //输出逐渐升高的电平
        delay(10);//有延迟停留，让人眼能分辨光亮暗的变化
      }
      for (int i = c; i > 0; i--) { //输出逐渐降低的电平
        analogWrite(haptics, i);
        delay(10);
      }
    } else if (haplevel == 4) {
      for (int i = 0; i < d; i++) { //由于存储器位数的限制，i的范围为0~255
        analogWrite(haptics, i); //输出逐渐升高的电平
        delay(10);//有延迟停留，让人眼能分辨光亮暗的变化
      }
      for (int i = d; i > 0; i--) { //输出逐渐降低的电平
        analogWrite(haptics, i);
        delay(10);
      }
    } else if (haplevel == 5) {
      for (int i = 0; i < e; i++) { //由于存储器位数的限制，i的范围为0~255
        analogWrite(haptics, i); //输出逐渐升高的电平
        delay(10);//有延迟停留，让人眼能分辨光亮暗的变化
      }
      for (int i = e; i > 0; i--) { //输出逐渐降低的电平
        analogWrite(haptics, i);
        delay(10);
      }
    }
    if (powerstate == false) {
      digitalWrite(haptics, HIGH);
      delay(100);
      digitalWrite(haptics, LOW);
      delay(100);
      digitalWrite(haptics, HIGH);
      delay(100);
      digitalWrite(haptics, LOW);
      delay(100);
      digitalWrite(haptics, HIGH);
      delay(100);
      digitalWrite(haptics, LOW);
      delay(100);
    }
  } else {
    if (powerstate == true) {
      digitalWrite(haptics, HIGH);
      delay(100);
      digitalWrite(haptics, LOW);
      delay(100);
      digitalWrite(haptics, HIGH);
      delay(100);
      digitalWrite(haptics, LOW);
      delay(100);
    }
  }
}
