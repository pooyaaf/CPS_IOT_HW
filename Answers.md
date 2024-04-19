## 1) In the Embedded section of the exercise, how can Bluetooth be replaced by RFID? Describe your solution.

HC-05 and HC-06 are popular Bluetooth modules that can be used for wireless communication between devices.

## 2) Is it possible to transfer the necessary information (person ID) between the Bluetooth modules without having to pair them? Explain.

Yes, you can transfer data, including IDs, between Bluetooth modules without pairing. Bluetooth modules like HC-05 and HC-06 can operate in both master and slave modes. In master-slave communication, the master device initiates the connection, and the slave device responds to the master. You can configure one Bluetooth module as a master and the other as a slave. The master can send data to the slave without requiring pairing.

## 3) Solution for Closing Door After Entrance Using Bluetooth

- Proximity Detection:

You can implement a proximity detection system using Bluetooth. When a Bluetooth-enabled device (such as a smartphone) comes within range of the Bluetooth module near the door, it sends a signal to the Arduino indicating valid access. The Arduino then opens the door. Once the device moves out of range, the Arduino closes the door.

- Mobile App Control:

Develop a mobile application that communicates with the Bluetooth module. Users can send commands through the app to unlock the door when they are nearby. The Arduino continuously listens for commands from the app and controls the door accordingly

- Bluetooth Beacons:

Use Bluetooth beacons placed at entrances. When a Bluetooth-enabled device detects the beacon's signal, it sends an unlock signal to the Arduino to open the door. As the device moves away from the beacon's range, the door is automatically closed

- Secure Key Exchange:

Implement a secure key exchange mechanism between the Bluetooth-enabled device and the Arduino. Only authorized devices with the correct key can send unlock commands to the Arduino

- Biometric Authentication:

Use a Bluetooth-enabled biometric authentication device (such as a fingerprint scanner or facial recognition module) for access control. Once the user is authenticated, the Arduino unlocks the door.
