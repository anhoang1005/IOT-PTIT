#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <TaskScheduler.h> // thu vien de xu li da luong
#include <DHT.h>

#define DHTPIN 4 // Chân DATA của DHT11 kết nối với D2 trên ESP8266
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

const char* ssid = "hoangvanan";
const char* password = "hoangvanan";

#define MQTT_SERVER "broker.hivemq.com"
#define MQTT_PORT 1883
#define MQTT_USER "hoangvanan"
#define MQTT_PASSWORD "Anhan10052002"
#define MQTT_LDP_TOPIC "SENSORDATA"
#define MQTT_CONTROL_TOPIC "LEDCONTROL"

WiFiClient wifiClient;
PubSubClient client(wifiClient);

Scheduler runner; // Khởi tạo scheduler để quản lý các nhiệm vụ

int current_ledState1 = LOW;
int last_ledState1 = LOW;
int current_ledState2 = LOW;
int last_ledState2 = LOW;

void setup_wifi() { // Ham ket noi wifi
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

void connect_to_broker() {  // Ham ket noi MQTT broker
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    String clientId = "testtopic";
    clientId += String(random(0xffff), HEX);
    if (client.connect(clientId.c_str(), MQTT_USER, MQTT_PASSWORD)) {
      Serial.println("MQTT connected");
      client.subscribe(MQTT_CONTROL_TOPIC);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 2 seconds");
      delay(2000);
    }
  }
}

void callback(char* topic, byte *payload, unsigned int length) {  // Ham callback su dung khi nhan duoc tin nhan
  Serial.println("-------new message from broker-----");
  Serial.print("topic: ");
  Serial.println(topic);
  Serial.print("message: ");
  Serial.write(payload, length);
  Serial.println();
  if (*payload == 'a') {
    current_ledState1 = HIGH;
    Serial.println(current_ledState1);
  }
  if (*payload == 'b') {
    current_ledState1 = LOW;
    Serial.println(current_ledState1);
  }
  if (*payload == 'c') {
    current_ledState2 = HIGH;
    Serial.println(current_ledState2);
  }
  if (*payload == 'd') {
    current_ledState2 = LOW;
    Serial.println(current_ledState2);
  }
}

void send_data() { // gui du lieu len cloud
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();
  int sensorValue = 1024 - analogRead(A0);
  String sensorValueStr = String(humidity) + "-" + String(temperature) + "-" + String(sensorValue); // Chuyển đổi sensorValue thành chuỗi
  client.publish(MQTT_LDP_TOPIC, sensorValueStr.c_str()); // Gửi chuỗi đi
}

// Xu li luong gui du lieu
Task sendDataTask(2000, TASK_FOREVER, &send_data);

void setup() {
  Serial.begin(115200);
  dht.begin();
  pinMode(5, OUTPUT);
  pinMode(13, OUTPUT);
  Serial.setTimeout(500);
  setup_wifi();
  client.setServer(MQTT_SERVER, MQTT_PORT);
  client.setCallback(callback);
  connect_to_broker();

  // Add the send data task to the scheduler
  runner.addTask(sendDataTask);
  sendDataTask.enable();
}

void loop() {
  client.loop();
  if (!client.connected()) {
    connect_to_broker();
  }

  //digitalWrite(5, HIGH);
  if (last_ledState1 != current_ledState1) {
    last_ledState1 = current_ledState1;
    digitalWrite(5, current_ledState1);
  }
  if (last_ledState2 != current_ledState2) {
    last_ledState2 = current_ledState2;
    digitalWrite(13, current_ledState2);
  }

  // Run tasks in the scheduler
  runner.execute();
}
