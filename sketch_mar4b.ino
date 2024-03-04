#include <WiFi.h>
#include <HTTPClient.h>
#include <TFT_eSPI.h>  // Hardware-specific library
#include <SPI.h>

const char* ssid = "WaterDoctor";
const char* password = "";

const char* serverUrl = "https://water-doctor-server.up.railway.app/post-values";  // Replace with your server IP

TFT_eSPI tft = TFT_eSPI();
void setup() {
  tft.init();
  tft.setRotation(3);
  tft.fillScreen(TFT_BLACK);
  Serial.begin(115200);

  pinMode(18, INPUT);

  pinMode(5, INPUT);

  WiFi.begin(ssid, password);

  // while (WiFi.status() != WL_CONNECTED) {
  //   // delay(1000);
  //   // tft.setCursor(36, 50);
  //   // tft.setTextColor(TFT_WHITE);  // Set text colour to white and background to black
  //   // tft.println("Connecting to WiFi...");
  // }
  for (int i=1; i<3; i++) {
    tftWifiConnecting();
  }
  tftWifiConnected();
  // tft.fillScreen(TFT_BLACK);
  // tft.println("Connected to WiFi");
  int t1 = 0;
  int t2 = 0;
  while(t1!=10) {
    tftDrinkableInfo();
    t1++;
  }
   while(t2!=10) {
    tftNotDrinkableInfo();
    t2++;
  }
}

void sendPostRequest(int value1, int value2) {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;

    http.begin(serverUrl);
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");

    String postData = "value1=";
    postData += String(value1);
    postData += "&value2=";
    postData += String(value2);

    Serial.println(postData);

    int httpResponseCode = http.POST(postData);

    if (httpResponseCode > 0) {
      String response = http.getString();
      Serial.println("POST request sent");
      Serial.print("Server response: ");
      Serial.println(response);
    } else {
      Serial.print("Error code: ");
      Serial.println(httpResponseCode);
    }

    http.end();
  } else {
    Serial.println("WiFi not connected");
  }
}


void tftDisplayDefaults() {
  tft.setTextSize(2);
  tft.setCursor(36, 50);
  tft.setTextColor(TFT_WHITE);  // Set text colour to white and background to black
}

void tftWifiConnecting() {
  // tft.setRotation(3);
  // tft.fillScreen(TFT_BLACK);
  // setup();
  // tft.setTextSize(2);
  // tft.setCursor(36, 50);
  // tft.setTextColor(TFT_WHITE);  // Set text colour to white and background to black
  tftDisplayDefaults();
  tft.println("Connecting to WiFi.");
  delay(1000);
  // tft.setCursor(36, 50);
  // tft.setTextColor(TFT_WHITE);  // Set text colour to white and background to black
  tftDisplayDefaults();
  tft.println("Connecting to WiFi..");
  delay(1000);
  // tft.setCursor(36, 50);
  // tft.setTextColor(TFT_WHITE);  // Set text colour to white and background to black
  tftDisplayDefaults();
  tft.println("Connecting to WiFi...");
  delay(1000);
  tft.fillScreen(TFT_BLACK);
}

void tftWifiConnected() {
  tftDisplayDefaults();
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_GREEN);
  tft.println("Connected to WiFi");
  delay(3000);
}

void tftDrinkableInfo() {
  tftDisplayDefaults();
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_CYAN);
  int value = digitalRead(18);
  Serial.println(value);
  int value1 = digitalRead(5);
  String val = String(value);
  val += " ";
  val += String(value1);
  Serial.println(val);
  sendPostRequest(value, value1);

  // tft.setTextColor(TFT_WHITE);  // Set text colour to white and background to black
  tft.println("Water is clean");
  delay(2000);
}

void tftNotDrinkableInfo() {
  tftDisplayDefaults();
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_RED);
  tft.println("Not preferable to");
  tft.setCursor(36, 70);
  tft.println("Drink!!!");
  delay(2000);
}
void loop() {
  // int value = digitalRead(18);
  // Serial.println(value);
  // int value1 = digitalRead(5);
  // String val = String(value);
  // val += " ";
  // val += String(value1);
  // Serial.println(val);
  // sendPostRequest(value, value1);

  // tft.setTextColor(TFT_WHITE);  // Set text colour to white and background to black
  // tft.println(value1);
  // delay(1000);
  setup();
}