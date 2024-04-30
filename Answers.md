## 1) In the Embedded section of the exercise, how can Bluetooth be replaced by RFID? Describe your solution.

HC-05 and HC-06 are popular Bluetooth modules that can be used for wireless communication between devices.

Instead of using an RFID reader and tags, the system could utilize Bluetooth Low Energy (BLE) technology. Each employee would have a dedicated BLE device, such as a smartphone or a specialized BLE tag/beacon. The embedded system at the entrance would incorporate a Bluetooth module capable of scanning for and connecting to nearby BLE devices.

The process would work as follows:

    1. The embedded system would continuously scan for BLE devices in the vicinity of the entrance.

    2. When an employee's BLE device comes within range, the embedded system would attempt to establish a connection with it.

    3. Upon successful connection, the embedded system would request the unique identifier (e.g., MAC address or a custom ID) of the employee's BLE device.

    4. This identifier would then be used in place of the RFID tag's code for authentication with the web server.

    5. The rest of the process, including sending the identifier to the web server, receiving the authentication response, and controlling the door and display, would remain the same as the original RFID-based implementation.

Using Bluetooth instead of RFID offers a few advantages:

- Compatibility: Most modern smartphones and devices support BLE, eliminating the need for dedicated RFID tags.
- Range: Bluetooth typically has a longer range compared to RFID, potentially allowing for earlier detection of employees approaching the entrance.
- Two-way communication: Bluetooth enables two-way communication between the embedded system and the employee's device, opening up possibilities for additional features or data exchange.

However, it's important to note that Bluetooth implementation may require additional considerations, such as power management for the embedded system's Bluetooth module, handling potential connection issues, and ensuring secure communication between devices.

## 2) Is it possible to transfer the necessary information (person ID) between the Bluetooth modules without having to pair them? Explain.

Yes, you can transfer data, including IDs, between Bluetooth modules without pairing. Bluetooth modules like HC-05 and HC-06 can operate in both master and slave modes. In master-slave communication, the master device initiates the connection, and the slave device responds to the master. You can configure one Bluetooth module as a master and the other as a slave. The master can send data to the slave without requiring pairing.

In a typical BLE communication scenario, there are two roles: the peripheral and the central. The peripheral is the device that advertises its presence and offers services, while the central is the device that scans for and connects to peripherals.

To transfer data without pairing, the following process can be followed:

    1. Advertising Mode: The peripheral device (e.g., the employee's BLE tag or smartphone) would continuously advertise its presence by broadcasting advertising packets containing the person's ID or other relevant information.

    2. Scanning Mode: The central device (the embedded system's Bluetooth module) would continuously scan for these advertising packets from nearby peripherals.

    3. Data Extraction: When the central device detects an advertising packet from a peripheral, it can extract the person's ID or any other data included in the packet.

This method of data transfer is known as *broadcaster* mode in BLE terminology. It allows for one-way communication without the need for an explicit connection or pairing between devices.

The advantages of using this approach include:

- Simplicity: No pairing or connection setup is required, making the process more straightforward and efficient.
- Energy efficiency: Broadcasting advertising packets consumes less power than maintaining an active connection, which can be beneficial for battery-powered devices like smartphones or BLE tags.
- Scalability: Multiple peripherals can advertise their data simultaneously, and the central device can detect and process data from multiple sources.

However, it's important to note that this broadcaster mode has limitations in terms of data throughput and security. The advertising packets have a limited size, restricting the amount of data that can be transmitted. Additionally, the data is broadcasted in plaintext, which may raise security concerns in certain applications.

If larger amounts of data need to be transferred or if secure communication is required, a traditional BLE connection with pairing and encryption can be established after the initial detection phase.

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
