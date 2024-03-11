#include <Arduino.h>

volatile bool receivedFlag = false;
String inputString = "";  // A String to store incoming data
char startMarker = '<';   // Start of message
char endMarker = '>';     // End of message
bool readInProgress = false;

void setup() {
    Serial.begin(9600); // Start serial communication at 9600 baud rate
    attachInterrupt(digitalPinToInterrupt(2), serialEvent, CHANGE); // Attaching the interrupt
}

void loop() {
    if (receivedFlag) {
        // Process the received string if it's valid
        if (validateChecksum(inputString)) {
            Serial.println("Checksum valid.");
            parseMessage(inputString);
            sendConfirmation();
        } else {
            Serial.println("Checksum invalid.");
        }

        // Clear the string for new input and reset the flag
        inputString = "";
        receivedFlag = false;
    }
}

void serialEvent() {
    while (Serial.available()) {
        char inChar = (char)Serial.read();

        if (inChar == startMarker) {
            readInProgress = true;
            inputString = "";  // Clear the string
        } else if (inChar == endMarker) {
            readInProgress = false;
            receivedFlag = true;
        } else if (readInProgress) {
            inputString += inChar;  // Only add characters inside start and end markers
        }
    }
}

bool validateChecksum(String message) {
    // Extract the checksum from the end of the message
    int checksumIndex = message.lastIndexOf('*');
    if (checksumIndex == -1) {
        return false;
    }

    String checksumStr = message.substring(checksumIndex + 1);
    message = message.substring(0, checksumIndex);
    int checksumReceived = checksumStr.toInt();

    // Calculate the checksum of the message
    int checksumCalculated = calculateChecksum(message);

    // Compare the calculated checksum with the received one
    return (checksumReceived == checksumCalculated);
}

int calculateChecksum(String message) {
    int checksum = 0;
    for (unsigned int i = 0; i < message.length(); i++) {
        checksum ^= message[i];  // Simple XOR checksum
    }
    return checksum;
}

void sendConfirmation() {
    Serial.println("CMD:CONFIRM");  // Example confirmation message
}

void parseMessage(String message) {
  // Assuming the message format is "COMMAND:PAYLOAD"
  int delimiterIndex = message.indexOf(':');
  if (delimiterIndex == -1) {
    Serial.println("Invalid message format");
    return;
  }

  String command = message.substring(0, delimiterIndex);
  String payloadStr = message.substring(delimiterIndex + 1);
  int payload = payloadStr.toInt(); // Convert payload to integer

  // Handle different commands
  if (command == "CMD1") {
    handleCommand1(payload);
  } else if (command == "CMD2") {
    handleCommand2(payload);
  }
  // Add more commands as needed
}

void handleCommand1(int payload) {
  // Process the payload for command 1
  Serial.print("Handling CMD1 with payload: ");
  Serial.println(payload);
  // Implement the logic for CMD1
}

void handleCommand2(int payload) {
  // Process the payload for command 2
  Serial.print("Handling CMD2 with payload: ");
  Serial.println(payload);
  // Implement the logic for CMD2
}

// Add more command handling functions as necessary
