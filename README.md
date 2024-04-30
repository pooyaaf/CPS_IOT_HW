# HW1 - CPS - Entry and Exit Management System IoT

### Table of Contents  
- [Introduction](#introduction)
- [Background](#background)
- [Visual Results](#visual-results)
    - [Accept Scenario](#accept-scenario)
    - [Decline Scenario](#decline-scenario)
- [Code Explanation](#code-explanation) 
    - [Proteus and Embedded Modules](#proteus-and-arduino)  
    - [Main Web Server](#main-web-server)
    - [Administrator Client](#administrator-client)  
- [Conclusion](#conclusion) 


# Introduction

The goal of this project is to implement a system for managing entry and exit based on the Internet of Things (IoT) for a hypothetical company. The system consists of the following components:

1. Embedded System: This includes sensors and hardware modules. An RFID sensor is used to identify employees by reading their RFID tags (10-digit codes). A servo motor controls the opening and closing of the door, and two LED lights and monitors display the entry status and employee information.

2. Cloud (Web Server): A simple web server maintains a list of authorized individuals. Anyone not on this list is denied entry.

3. Monitoring System: A software application that connects to the web server via WebSocket and displays real-time event details.

The overall process works as follows: When an individual approaches the entrance, the RFID sensor reads their tag. The Arduino board sends this information to the web server for authentication. If authorized, the green LED turns on, the person's information is displayed, and the door opens. If not authorized, the red LED turns on, "Access Denied" is displayed, and the door remains closed.

The project involves setting up the hardware simulation in Proteus, implementing the web server and monitoring application using Qt framework in C++, and integrating all components. Additionally, there are bonus tasks like measuring end-to-end delays and using WebSocket for communication between the embedded system and the web server.

# Background

This project integrates several current industry concepts. Below is a brief overview of some of the key concepts involved:

- Internet of Things (IoT): The Internet of Things refers to the network of physical objects or "things" embedded with sensors, software, and other technologies that enable these objects to connect and exchange data with other devices and systems over the internet. IoT allows for the integration of the physical and digital worlds, enabling remote monitoring, control, and automation of various processes and activities. The concept of IoT has gained significant traction in recent years, with applications spanning across industries such as healthcare, manufacturing, transportation, and home automation.

- RFID (Radio Frequency Identification): RFID is a wireless technology that uses radio waves to identify and track objects, people, or animals. It uses readers and tags to transfer data via radio waves. A reader can communicate with a tag some distance away (between a few centimeters and 20 meters, depending on the type of RFID). Active RFID tags have batteries, which they can tap to send information to a reader. Passive RFID tags do not have batteries; they use a reader’s electromagnetic energy to communicate with the reader. There are also semi-passive RFID tags, meaning a battery runs the circuitry while communication is powered by the RFID reader. RFID is more expensive, bulkier and more prone to physical and electrical damages. Unlike barcodes, RFID can be read if they are not within the reader's line of sight.

    - How Does RFID Work?

        Every RFID system consists of three components: a scanning antenna, a transceiver and a transponder. When the scanning antenna and transceiver are combined, they are referred to as an RFID reader or interrogator. There are two types of RFID readers -- fixed readers and mobile readers. The RFID reader is a network-connected device that can be portable or permanently attached. It uses radio waves to transmit signals that activate the tag. Once activated, the tag sends a wave back to the antenna, where it is translated into data. The transponder is in the RFID tag itself. The read range for RFID tags varies based on factors including the type of tag, type of reader, RFID frequency and interference in the surrounding environment or from other RFID tags and readers. Tags that have a stronger power source also have a longer read range.

    - RFID Use in Industries:
        - Retail
        - Pharmaceutical and Health Care
        - Airline baggage
        - Passport
        - Libraries
        - Animal tagging

    - RFID Use Cases:
        - Item-level inventory
        - Tracking and monitoring
        - Timing
        - Management material
        - Logistics & supply chain visibility

    - Types of RFID Systems:
        - Low-frequency RFID systems
        - High-frequency RFID system
        - UHF RFID systems
        - Microwave RFID systems

- Proteus: Proteus is a professional software suite for circuit simulation and microcontroller programming. It provides a virtual environment for designing, testing, and simulating electronic circuits and embedded systems. In the context of this project, Proteus plays a crucial role in simulating the embedded system component, which includes the Arduino board, RFID sensor, servo motor, LED, and other hardware modules. By using Proteus, the project can be thoroughly tested and debugged in a virtual environment before deploying it on physical hardware, saving time and resources.

Incorporating a monitoring system in this project offers several advantages:

- Real-time Visibility: The monitoring system provides real-time visibility into the entry and exit events, allowing administrators or authorized personnel to monitor the activity instantly.
- Event Logging and Auditing: The system can maintain a log of all entry and exit events, which can be useful for auditing purposes, identifying potential security breaches, or analyzing traffic patterns.
- Centralized Management: With a dedicated monitoring application, the system can be managed and monitored from a centralized location, eliminating the need for physical presence at the entry point.
- Enhanced Security: By having a monitoring system in place, any unauthorized access attempts or suspicious activities can be quickly detected and addressed, improving the overall security of the premises.
- Data Analysis: The event data collected by the monitoring system can be analyzed to gain insights into employee attendance, peak hours, and other relevant metrics, which can aid in making informed decisions regarding resource allocation or operational efficiency.


Lastly, It's important to note the importance of the Qt framework in our project. This framework provides a comprehensive set of tools and libraries that are well-suited for developing the web server and monitoring application components of this project. Its cross-platform support ensures the applications can run on multiple operating systems without significant code changes. Qt's networking and web development modules simplify the implementation of the HTTP and WebSocket communication protocols required for the web server and client-server interactions. Additionally, Qt's GUI development capabilities enable the creation of a user-friendly monitoring application interface.

# Visual Results

Before we can describe our code and its components, we will demonstrate the result of this project. The demonstration includes both the scenarios where the user has/doesn't have access to open the door as well as the Proteus setup and configuration.

To run the program, we first need to build and run the web server configuration in QT environment.

![Server is Up!](./Images/server-up.png)

We also need the Proteus configuration below which consists of the following modules: ENC28J60 (ethernet), LM016L (LCD), Servo motor, LED (x2 with resistors), Arduino Uno, Terminal Windows (optional), Not Gate. 

![Proteus Config](./Images/proteus-configuration.png)

Please also note to set the appropriate IP for the ENC28J60 module.

![Ethernet Config](./Images/ethernet-config.png)

Lastly, note that we also need to build and run the client (administrator) configuration in QT environment if we want to monitor users' activities.

## Accept Scenario

In our database, we will authorise all RFIDs with the following format. Note that you can change this code to your own liking.

```
Database::Database()
{
    for (int i = 0; i < 10; ++i) {
        QJsonObject member;
        member["username"] = "ali" + QString::number(i);
        member["rfid"] = "123456789" + QString::number(i);
        members.append(member);
    }
}
```

For instance, `1234567890` is a valid ID. As it is shown below, on valid inputs, the green led will turn on, the door will roate 90 degrees and the appropriate message is shown. Moreover, the time and rfid value are shown on the LCD module. 

![Proteus Accept Scenario](./Images/accept-scenario.png)

On the server side, if we have the admin requirements, we can successfully log in to our account.

![Server Accept Scenario](./Images/server-accept-scenario.png)

As an admin, we also have the privilege to observe users' activities. For example, we can see that there have been one successful and one unsucceful entry attemps at April 30, 2024 at 12:38 and 12:39 respectively.  

![Server History](./Images/history.png)

> **Note:** Please note that after we have had at least one succeful entry, the server interface will also show the last successful entry record on the left side.

![Server User Entry Record](./Images/server-left-panel.png)


## Decline Scenario

On another hand, on invalid inputs, the red led will turn on, the door will stay closed and the *Access Denied* message is shown. Moreover, the *Access Denied* and rfid value are shown on the LCD module. 

![Proteus Decline Scenario](./Images/decline-scenario.png)

On the server side, if we have don't have the admin requirements, we cannot successfully log in to our account.

![Server Decline Scenario](./Images/server-accept-scenario.png)


# Code Explanation

Our coding structure consists of four main foulders *Client, Embedded, Proteus, Server* which represent their respective roles in our application. Aside from the *Proteus* folder which includes the required simulation data for the application, other code files need to be built and compiled. 

## Proteus and Embedded Modules

This section consists of one *main.ino* file. The following is a short explanation on it. 

- Library Includes:
The code includes three libraries: EtherCard.h for Ethernet functionality, Servo.h for controlling the servo motor, and LiquidCrystal.h for interfacing with the LCD display.

- LiquidCrystal Object Initialization:
An instance of the LiquidCrystal class is created, specifying the pins to which the LCD is connected.

- Global Variables:
    - *RFid*: A string variable to store the RFID tag data.
    - *count*: An integer variable used for counting purposes.
    - *myservo*: A Servo object to control the servo motor.

- MAC and IP Address Configuration:
Configuration of MAC and IP addresses for the Ethernet module.

- Static Callback Function (my_result_cb):
A callback function that handles the response from a web server. It parses the response and performs actions based on the received data, such as displaying messages on the LCD and controlling the servo motor.

- Setup Function:
Initialization of serial communication, servo motor, LCD display, Ethernet module, and configuration of IP addresses.
A loop that waits for the Ethernet module to establish a connection.

- Loop Function:
    - Calls *ether.packetLoop()* to handle incoming Ethernet packets.
    - Calls *handleInput()* function to handle input from the serial port.

- handleInput Function:
    - Checks if there is data available on the serial port.
    - If data is available, it reads the RFID tag data.
    - Clears the LCD display and prints the RFID tag data.
    - Constructs a URL query string containing the RFID tag data and the time delay since the last RFID scan.
    - Calls *ether.browseUrl()* to send an HTTP request to a web server with the RFID data as parameters.
    - Passes the *my_result_cb* function as a callback to handle the server response.

## Main Web Server

The following is a brief explanation on each of the *Web Server* files.


- **database**: This code defines the `Database` class, which simulates a database for user authentication and logging purposes. In its constructor, it initializes a list of predefined user data containing usernames and corresponding RFID tags. The class provides methods to retrieve a username based on an RFID tag (`getUsername`), check if an RFID tag is valid (`isValid`), and add login time information for a given RFID tag (`addLogInTime`). Additionally, it provides methods to retrieve the last login entry (`getLastLog`) and retrieve all login data in JSON format (`getLogs`).
The `getUsername` method iterates through the list of members to find a matching RFID tag and returns the corresponding username. The `isValid` method checks if a given RFID tag exists in the database. The `addLogInTime` method records the login time for a user identified by an RFID tag, appending the login entry to the data list. The `getLastLog` method retrieves the most recent login entry, while the `getLogs` method converts all login data to JSON format for retrieval. Overall, this class provides basic functionality for user authentication and logging within the simulated database.

- **httpserver**: This code implements an HTTP server using the Qt framework. In the constructor of the `HttpServer` class, it creates an instance of `QHttpServer` and defines a route for handling requests to "/enter_door". When a request is received, it extracts the RFID tag and delay parameter from the request, checks the validity of the RFID tag against the database, records the login time, and emits a signal with the login information. It then calculates and logs the delay between receiving the request and responding. Finally, it sets up a response header for the server and starts listening on port 80. If the server fails to listen on a port, it emits a warning message.
The `QHttpServer` instance handles incoming HTTP requests and executes the specified route handler for each request. The route handler extracts relevant information from the request, interacts with the database to authenticate users and record login times, and sends a response back to the client. After processing the request, the server sets up a response header indicating the server identity and returns the response to the client. This setup allows the server to listen for incoming connections on port 80 and respond to requests for entering the door with authentication and logging functionality.

- **main**: It initializes a Qt application instance and creates a database object. Subsequently, it initializes both a WebSocket server and an HTTP server, passing the database object to both. Additionally, it establishes a connection between the HTTP server and the WebSocket server, enabling communication between them. Finally, it enters the event loop by calling `a.exec()`, allowing the application to run and respond to events until termination. Overall, this code orchestrates the setup and operation of both WebSocket and HTTP servers within a Qt application, facilitating real-time communication and HTTP request handling.

- **websocketserver**: This code defines a `WebSocketServer` class within a Qt application. It initializes the server with a specified port and debug mode, and sets up connections for incoming WebSocket connections. When a new WebSocket connection is established, it connects various signals to corresponding slots for message processing and client management. Upon receiving a text message from a client, the server processes it (`message`). If the message indicates a login attempt (`"login"`), it checks the credentials against predefined values (`USERNAME` and `PASSWORD`) and responds accordingly. If the message requests log data (`"log"`), the server retrieves logs from the database (`database->getLogs()`) and sends them back to the client. Messages with unrecognized types trigger warnings and exceptions. Additionally, the class handles notifications for new user data by sending JSON-formatted data (`QJsonDocument(data).toJson()`) to connected clients (`m_clients`). Disconnection events are managed by removing disconnected clients from the client list (`m_clients`).

## Administrator Client

The following is a brief explanation on each of the *Administrator Client* files.

- **cpsapplication**: This file defines the `Application` class within the `CPS` namespace. The constructor initializes objects for the main window, history window, and client, and establishes connections between signals and slots for various events, such as button clicks and server connections. The destructor deallocates memory for these objects. Additionally, it provides methods to show the main window, update the history window with data, and display the history window. Overall, the `Application` class manages the user interface and interactions for the application.

- **cpsbutton**: This code defines the `Button` class within the `CPS` namespace. The constructor initializes a QPushButton with a specified text and sets its font size, height, and style sheet. The style sheet defines the appearance of the button, including text color, background color, and hover effect. Overall, the `Button` class creates customized buttons for use within the application.

- **cpshistorywindow**: This code defines the `HistoryWindow` class in the `CPS` namespace, representing a window for displaying history data in an IoT monitoring system. In its constructor, it sets up the window's properties like size, title, icon, and background color, and initializes a `QListWidget` `_list` to display history entries. The `update` function populates this list with data provided in a JSON array, creating formatted strings for each entry and adding them to the list. The `show` function ensures the window is displayed when requested, while the `closeEvent` function clears the list when the window is closed to remove all history entries. Overall, this class manages the display and updating of a history window in the application.

- **cpslabel**: This code defines the `Label` class within the `CPS` namespace, representing a customized label widget for the application. In its constructor, it initializes a QLabel with a specified text and sets properties such as font size, height, and margin. The label is configured to have a fixed height of 70 pixels and a margin of 10 pixels on all sides. Overall, the `Label` class creates styled labels for use within the application.

- **cpsmainwindow**: This code defines the `MainWindow` class within the `CPS` namespace, representing the main window of an IoT monitoring system application. In its constructor, it sets up various widgets and layouts, including input fields for server address, username, and password, buttons for connecting to the server and viewing history, and labels for displaying user details such as username, date, and time. It also configures the window's properties like size, title, icon, and background color.
The class provides several public methods for setting user details such as username, date, and time, as well as slots for handling UI interactions like button clicks. These slots dynamically update the UI based on user actions, such as enabling/disabling the connect button and displaying user details when available.
Private helper functions are used to set up connections between UI elements, configure the global style of the window, set up the window layout, and handle the window's close event. Overall, this class manages the UI logic and behavior of the main window in the IoT monitoring system application.

- **cpstextfield**: This file defines a custom text input field widget called `TextField` within the `CPS` namespace. It sets specific properties for the input field, including font size, height, text margins, placeholder text, and style sheet. The style sheet customizes the appearance of the input field, removing the default border, setting text and background colors, and defining different styles for hover and focus states. Overall, `TextField` provides a consistent and visually appealing text input field for use within the application.

- **cpswindowsapitools**: This header file `cpswindowsapitools.h` defines a template function `setWindowsThemeToDark` within the `CPS` namespace. The function adjusts a window's appearance to a dark theme on Windows operating systems using the `DwmSetWindowAttribute` function from the Windows API. Conditional compilation directives ensure that the function is only compiled on Windows platforms. Overall, this header provides a utility for setting windows to dark mode on Windows systems.


# Conclusion

some random text.

---

[Answers](Answers.md)
