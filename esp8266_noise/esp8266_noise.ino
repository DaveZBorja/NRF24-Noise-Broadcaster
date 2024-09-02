extern "C" {
  #include "user_interface.h"
  #include "osapi.h"
  #include "mem.h"
}

// Callback function for received packets (required but not used here)
void promisc_cb(uint8_t *buf, uint16_t len) {
  // Do nothing
}

void setup() {
  Serial.begin(115200);
  
  // Initialize the Wi-Fi in station mode
  wifi_set_opmode(STATION_MODE);
  
  // Disable the Wi-Fi connection
  wifi_station_disconnect();
  
  // Set the promiscuous mode callback
  wifi_set_promiscuous_rx_cb(promisc_cb);
  
  // Enable promiscuous mode
  wifi_promiscuous_enable(1);
}

void loop() {
  // Generate and send noise on each channel
  for (int channel = 1; channel <= 13; channel++) {
    wifi_set_channel(channel);
    sendNoise();
    delay(10);
  }
}

void sendNoise() {
  // Generate a packet of 128 random bytes
  uint8_t packet[128];
  for (int i = 0; i < sizeof(packet); i++) {
    packet[i] = random(0, 256);
  }
  
  // Send the packet
  wifi_send_pkt_freedom(packet, sizeof(packet), 0);
}
