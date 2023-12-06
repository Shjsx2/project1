#include <WiFi.h>
#include <ArduinoWebsockets.h>

using namespace websockets;

const char* ssid     = "NETGEAR75"; // Change this to your WiFi SSID
const char* password = "rustictrail325"; // Change this to your WiFi password

#define haptics 2

int haplevel = 1;//vibration frequency 5最大 1最小

boolean powerstate = true;//toggle on (没写)
String uart = "";

WebsocketsServer server;
const char* url = "localhost:8080";

double intensity = 0.0; // current vibration intensity
unsigned long lastReceivedTime = 0; // last time a message was received from server
const unsigned long TIMEOUT_MS = 1000000;

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
  server.listen(8080);
  Serial.println(server.available());
}

void handleMessage(WebsocketsMessage message) {
  Serial.print("Got Message: ");
  Serial.println(message.data());

  // parse message
  // check if data is parsable to double
  double receivedIntensity = message.data().toDouble();
  intensity = message.data().toDouble();
  lastReceivedTime = millis();
  Serial.print("Intensity: ");
  Serial.println(intensity);
  Serial.print("Last Received Time: ");
  Serial.println(lastReceivedTime);
}

void loop() {
  // put your main code here, to run repeatedly:
  auto client = server.accept();
  if (client.available()) {
    auto msg = client.readBlocking();
    handleMessage(msg);
  }

  unsigned long currentTime = millis();
  if (currentTime - lastReceivedTime > TIMEOUT_MS) {
    powerstate = false;
    analogWrite(haptics, 0); 
  } else {
    powerstate = true;
  }

  if (powerstate) {
    haplevel = intensity * 255 > 255 ? 255 : intensity * 255;
    analogWrite(haptics, haplevel);
  }
}
