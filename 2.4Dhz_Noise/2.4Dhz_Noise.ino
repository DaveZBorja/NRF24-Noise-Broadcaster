/*
 *
 Explanation:

    Libraries and Objects:
        The SPI.h, nRF24L01.h, and RF24.h libraries are included for communication.
        An RF24 object is created to handle communication with the NRF24 module.

    Setup Function:
        Initializes the radio.
        Sets the data rate, power level, and disables acknowledgment to facilitate noise broadcasting.

    Loop Function:
        Generates an array of 32 random bytes.
        Iterates through all available channels (0 to 125).
        Sets the radio to the current channel using radio.setChannel.
        Sends the random data on the current channel using radio.write.
        Adds a small delay (5 milliseconds) to avoid overloading the receiver.

Notes:

    Range and Power: Adjust the power level and data rate as needed based on your environment and range requirements.
    Interference: Broadcasting noise may cause interference with other devices operating in the 2.4 GHz band. Use this code responsibly.
    Compliance: Ensure compliance with local regulations regarding radio frequency transmission.

This approach will approximate broadcasting noise across all channels by rapidly switching channels and sending random data packets. This should create noise across the entire 2.4 GHz spectrum that the NRF24 operates on.

*
*/

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

// Create an RF24 object
RF24 radio(9, 10); // CE, CSN

void setup() {
  // Initialize the radio
  radio.begin();
  // Set the data rate to 1Mbps for reliable communication
  radio.setDataRate(RF24_1MBPS);
  // Set the power level to maximum for maximum range
  radio.setPALevel(RF24_PA_MAX);
  // Disable acknowledgment
  radio.setAutoAck(false);
  // Start the radio
  radio.stopListening();
}

void loop() {
  // Generate random data
  byte data[32];
  for (int i = 0; i < 32; i++) {
    data[i] = random(0, 256);
  }

  // Loop through all available channels (0 to 125)
  for (int channel = 0; channel <= 125; channel++) {
    // Set the radio to the current channel
    radio.setChannel(channel);
    // Send the random data
    radio.write(&data, sizeof(data));
    // Optionally, add a small delay to avoid overloading the receiver
    delay(5);
  }
}

