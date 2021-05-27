#include <WiFi.h>

const char * ssid = "ID";
const char * password = "PASSWORD";
int sensorSom = 25;
int eixoX = 34;
int eixoY = 35;
int sw = 15;
int led = 3;

WiFiServer wifiServer(80);

void setup() {
  Serial.begin(115200);
  pinMode(15, OUTPUT);
  delay(1000);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting..");
  }

  Serial.print("Connected to WiFi. IP:");
  Serial.print(WiFi.localIP());
  wifiServer.begin();

  pinMode(sensorSom, INPUT);
  pinMode(sw, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {
  WiFiClient client = wifiServer.available();

  if(client) {
    while(client.connected()) {

      while (client.available() > 0) {
        String c = client.readStringUntil('\n');

        if(c == "1 Sobe") {
          if(digitalRead(sensorSom) == true) {
            Serial.println("POW");
            Serial.print("3 ");
            Serial.print("Sobe");
            Serial.print("\n");
          }

          if(analogRead(eixoX) <= 1000) {
            Serial.println("SOBE");
            Serial.print("1 ");
            Serial.print(analogRead(eixoX));
            Serial.print("\n");
          }
          if(analogRead(eixoX) >= 3000) {
            Serial.println("BAIXO");
            Serial.print("1 ");
            Serial.print(analogRead(eixoX));
            Serial.print("\n");
          }
          if(analogRead(eixoY) >= 3000) {
            Serial.println("ESQUERDA");
            Serial.print("2 ");
            Serial.print(analogRead(eixoY));
            Serial.print("\n");
          }
          if(analogRead(eixoY) <= 1000) {
            Serial.println("DIREITA");
            Serial.print("2 ");
            Serial.print(analogRead(eixoY));
            Serial.print("\n");
          }
          
          delay(30);
        }
      }
    }
  }

}
