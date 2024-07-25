# EVSE Controller Project

## Overview

The EVSE (Electric Vehicle Supply Equipment) Controller Project is a comprehensive solution designed to manage electric vehicle charging sessions. This project includes various classes to handle aspects such as communication with the vehicle, authentication, user preferences, and MQTT messaging. The system is structured using a state machine to efficiently manage the charging process.

## Features

- **Charging Management**: Efficient management of charging sessions and communication with the vehicle.
- **User Authentication**: Supports authentication through RFID, QR codes, or payment stations.
- **User Preferences**: Manages user preferences for charging schedules and solar energy usage.
- **MQTT Integration**: Facilitates messaging through MQTT for real-time communication.
- **Inverter Management**: Selects and controls inverters based on the vehicle's requirements.

## Class Descriptions

### `CommunicationHandler`

Handles basic communication operations and session management.

### `ChargingSessionCommunicationHandler`

Extends `CommunicationHandler` to manage communication specific to charging sessions, including updating and retrieving statistics related to the state of charge and battery temperature.

### `InitialCommunicationHandler`

Handles initial communication with the vehicle to determine the required voltage and current settings.

### `AuthenticationManager`

Manages the authentication process, including user authentication and session management.

### `EvseController`

Controls the entire charging process, managing state transitions, handling vehicle communication, and processing user interactions. It also interfaces with MQTT for messaging and updates.

### `Inverter`

Represents and manages an inverter used during the charging process, including operations to start and stop the inverter.

### `ChargingSessionManager`

Oversees the charging session, including performing initial communication with the vehicle, selecting the appropriate inverter, and managing session parameters.

### `MQTTClient`

Handles MQTT communication for sending and receiving messages, including setting up callbacks for message handling.

### `UserPreferences`

Stores and manages user preferences related to solar energy usage and charging schedules.

## Getting Started

To get started with the EVSE Controller Project:

1. **Clone the Repository**

   ```bash
   git clone https://github.com/yourusername/evse-controller.git
   cd evse-controller
   ```
2. **Build the Project**
   Do this via Visual studio 22 or using CMake
   ```bash
   mkdir build
   cd build
   cmake...
   make
   ```
3. **setup The MQTT Broker using Mosquitto**
   - install mosquitto via there website
   - On windows, go to the cmd line and start the MQTT broker with the folowing cmd:
   ```bash
   cd C:\Program_files\mosquitto
   mosquitto -c mosquitto.conf
   ```
5.  **usage**
After building the project, you can start using the EVSE Controller. Here's a brief guide:

- Create an instance of EvseController.
- Call the start_charging_session() method to initiate a charging session.
- Use stop_charging_session() to end a session.
- Use pause_charging_session() to pause a session.
- Manage user authentication with handle_authentication().
- Update user preferences with update_user_preferences().
  
Make sure all required configurations are set up before running the application. Consult the class documentation for detailed instructions on using each component.

## Documentation
The doxygen documentation can be found in the doc folder
