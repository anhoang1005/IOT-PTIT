#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char* ssid = "Vozer MU Wibu";
const char* password = "1234@6789";

#define MQTT_SERVER "broker.hivemq.com"
#define MQTT_PORT 1883
#define MQTT_USER "hoangvanan"
#define MQTT_PASSWORD "Anhan10052002"
#define MQTT_LDP_TOPIC "testtopic"

int current_ledState = LOW;
int last_ledState = LOW;

WiFiClient wifiClient;
PubSubClient client(wifiClient);

void setup_wifi() {
  Serial.println("Connecting to...");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  randomSeed(micros());
  Serial.println("");
  Serial.println("WiFi connected!!!");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void connect_to_broker() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    String clientId = "testtopic";
    clientId += String(random(0xffff), HEX);
    if (client.connect(clientId.c_str(), MQTT_USER, MQTT_PASSWORD)) {
      Serial.println("MQTT connected");
      client.subscribe(MQTT_LDP_TOPIC);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 2 seconds");
      delay(2000);
    }
  }
}

void callback(char* topic, byte *payload, unsigned int length) {
  Serial.println("-------new message from broker-----");
  Serial.print("topic: ");
  Serial.println(topic);
  Serial.print("message: ");
  Serial.write(payload, length);
  Serial.println();
  if (*payload == '1') current_ledState = HIGH;
  if (*payload == '0') current_ledState = LOW;
}

void setup() {
  Serial.begin(115200);
  Serial.setTimeout(500);
  setup_wifi();
  client.setServer(MQTT_SERVER, MQTT_PORT );
  client.setCallback(callback);
  connect_to_broker();
}

void send_data() {
  client.publish(MQTT_LDP_TOPIC, "30.5 - 52 - 512"); 
  delay(2000);
}

void loop() {
  client.loop();
  if (!client.connected()) {
    connect_to_broker();
  }
  if (last_ledState != current_ledState) {
    last_ledState = current_ledState;
    digitalWrite(2, current_ledState);
    Serial.println(current_ledState);
  }
  send_data();
}
