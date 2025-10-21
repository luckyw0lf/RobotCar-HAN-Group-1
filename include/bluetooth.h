#ifndef BLUETOOTH_H
#define BLUETOOTH_H

// Initialize Bluetooth communication
void bluetoothInit(void);

// Update function to check for incoming Bluetooth data
void bluetoothUpdate(void);

// Process received command
void processCommand(char* command);

// Send data back to Flutter app
void bluetoothSend(char* message);

#endif