
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <AsyncElegantOTA.h>
#include <Arduino.h>
#include <config.h>
#include <creds.h>
#include <hand_data.h>
#include <esp_now.h>
#include <hand.h>
#include <display.h>

AsyncWebServer server(80);

// MAC address of the sender ESP32 
uint8_t broadcastAddress[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

sPosition read_ESPNOW_ValPositions(const String& input) {
  if (debug >= 2) {
    Serial.println("\n\n@read_ESPNOW_ValPositions()");
  }
  

  sPosition result;

  result.pinkyF = (byte) strtol(input.substring(0, 2).c_str(), NULL, 16);
  result.ringF = (byte) strtol(input.substring(2, 4).c_str(), NULL, 16);
  result.middleF = (byte) strtol(input.substring(4, 6).c_str(), NULL, 16);
  result.indexF = (byte) strtol(input.substring(6, 8).c_str(), NULL, 16);
  result.thumbF = (byte) strtol(input.substring(8, 10).c_str(), NULL, 16);
  result.wrist = (byte) strtol(input.substring(10, 12).c_str(), NULL, 16);
 
  if (debug >= 2) {
    Serial.println("Input string: " + input);
    Serial.println("Output sPosition:");
    Serial.println("PinkyF: " + String(result.pinkyF) + ", RingF: " + String(result.ringF) +
                   ", MiddleF: " + String(result.middleF) + ", IndexF: " + String(result.indexF) +
                   ", ThumbF: " + String(result.thumbF) + ", Wrist: " + String(result.wrist));
  }

  return result;
}


// Callback when data is received
void OnESPNOW_DataRecv(const uint8_t * mac_addr, const uint8_t *incomingData, int len) {
  if (debug >= 2) {
    Serial.println("\n\n@OnDataRecv()");
  }
  
  char incomingDataChar[len+1];
  memcpy(incomingDataChar, incomingData, len);
  incomingDataChar[len] = '\0';

  if (debug >= 2) {
    Serial.println("Packet received");
    // Print MAC address of the sender
    Serial.print("MAC: ");
    for (int i = 0; i < 6; i++){
      Serial.print(mac_addr[i], HEX);
      if (i < 5){
        Serial.print(":");
      }
    }
    Serial.println();

    // Print incoming data
    Serial.print("Data: ");
    Serial.println(incomingDataChar);
  }

  sPosition receivedPos = read_ESPNOW_ValPositions(String(incomingDataChar));
  // Do something with receivedPos
  // if(true){
  //   if(isObsene(currentPos)){
  //     childMode();
  //   }
  // }
  currentPos = receivedPos;
  displaySpos(currentPos);
  moveHand(currentPos);

  // ledBacklight = 2*currentPos.wrist;
  // s(LCD_pwm_LedChannel_TFT, ledBacklight);
  // Enables power to the servos. 
  if(currentPos.wrist>20){
    digitalWrite(22,HIGH);
  }else{
    digitalWrite(22,LOW);
  }

}

void ESPNOW_Setup(){
  Serial.println("\n\n@ESPNOW_Setup()");

  bool AP_Result = WiFi.softAP(AP_SSID, AP_PASSWORD);
  
  if(AP_Result) {
    Serial.print("AP SSID: ");
    Serial.println(AP_SSID);
  } else {
    Serial.println("Failed to create AP.");
  }

  WiFi.mode(WIFI_AP_STA);
  
  // Init ESP-NOW
  if (esp_now_init() == ESP_OK) {
    Serial.println("ESP-NOW Started OK");
    return;
  }
  else if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  


  // Once ESPNow is successfully Init, we will register for recv CB to
  // get recv packer info
  esp_now_register_recv_cb(OnESPNOW_DataRecv);

  // Add peer
  esp_now_peer_info_t peerInfo = {0}; // Initialize to zeroes
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;
  peerInfo.ifidx = ESP_IF_WIFI_STA; // Use the station interface
  
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }
}

void printAPSSID() {
  Serial.print("AP SSID: ");
  Serial.println(AP_SSID);
}


void setupWebServer(){
  Serial.println("\n\n@setupWebServer()");
  

  // Connect to Wi-Fi
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(200, "text/plain", hand_Firmware_version);
  });

  AsyncElegantOTA.begin(&server);    // Start AsyncElegantOTA
  server.begin();
  Serial.println("HTTP server started");

}



String sPositionToHex(const sPosition& pos) {
  if (debug >= 2) {
    Serial.println("\n\n@sPositionToHex()");
  }
  String result = "";
  result += String(pos.pinkyF, HEX);
  result += String(pos.ringF, HEX);
  result += String(pos.middleF, HEX);
  result += String(pos.indexF, HEX);
  result += String(pos.thumbF, HEX);
  result += String(pos.wrist, HEX);

  if (debug >= 2) {
    Serial.println("Input sPosition:");
    Serial.println("PinkyF: " + String(pos.pinkyF) + ", RingF: " + String(pos.ringF) +
                  ", MiddleF: " + String(pos.middleF) + ", IndexF: " + String(pos.indexF) +
                  ", ThumbF: " + String(pos.thumbF) + ", Wrist: " + String(pos.wrist));
    Serial.println("Output string: " + result);
  }

  return result;
}

void send_ESPNOW_ValPositions(const sPosition& pos) {
  if (debug >= 2) {
    Serial.println("\n\n@send_ESPNOW_ValPositions()");
  }
  String data = sPositionToHex(pos);
  if (debug >= 2) {
    Serial.println("Sending data: " + data);
  }
  esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *)data.c_str(), data.length());
  if (result == ESP_OK) {
    if (debug >= 2) {
      Serial.println("Sent with success");
    }
  } else if (result == ESP_ERR_ESPNOW_NOT_INIT) {
    if (debug >= 2) {
      Serial.println("ESPNOW not Init.");
    }
  } else if (result == ESP_ERR_ESPNOW_ARG) {
    if (debug >= 2) {
      Serial.println("Invalid Argument");
    }
  } else if (result == ESP_ERR_ESPNOW_INTERNAL) {
    if (debug >= 2) {
      Serial.println("Internal Error");
    }
  } else if (result == ESP_ERR_ESPNOW_NO_MEM) {
    if (debug >= 2) {
      Serial.println("ESP_ERR_ESPNOW_NO_MEM");
    }
  } else if (result == ESP_ERR_ESPNOW_NOT_FOUND) {
    if (debug >= 2) {
      Serial.println("Peer not found.");
    }
  } else {
    if (debug >= 2) {
      Serial.println("Not sure what happened");
    }
  }
}

void read_Wifi_ValPositions() {
  if (debug >= 2) {
    Serial.println("\n\n@read_Wifi_ValPositions()");
  }
  return;
}

void read_BT_ValPositions() {
  if (debug >= 2) {
    Serial.println("\n\n@read_BT_ValPositions()");
  }
  return;
}


void wirelessSetup(){
  Serial.println("\n\n@wirelessSetup()");
  if (wireless_mode == "ESPNOW") {
    // setup espnow
    Serial.println("Wireless Mode: ESPNOW");
    ESPNOW_Setup();
  } else if (wireless_mode == "WiFi") {
    // setup wifi
    Serial.println("WiFi");
    setupWebServer();
  } else {
    Serial.println("No wireless mode selected");
  }
}