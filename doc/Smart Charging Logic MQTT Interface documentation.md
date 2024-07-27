# Smart Charging Logic MQTT Interface Guide

This document provides an overview of how to interact with the Smart Charging Logic system using the MQTT interface. Below are the commands the system can handle, the topics they should be published to, and the responses you can expect.

## MQTT Topics and Commands

The MQTT interface is structured to handle various commands related to managing and monitoring the charging process. Each command is associated with a specific topic and may require certain payload data.

### 1. Update User Preferences
- **Topic**: `update_pref`
- **Payload**: A string representing the new schedule.
- **Description**: Updates the user preferences with the provided schedule.
- **Response**: None.

### 2. Start Charging Session
- **Topic**: `start_charg_ses`
- **Payload**: None
- **Description**: Initiates a new charging session.
- **Response**: Confirmation message indicating the session has started (on topic: charg_ses).

### 3. Check EV State
- **Topic**: `check_ev_state`
- **Payload**: None
- **Description**: Checks the current state of the electric vehicle.
- **Response**: The current state of the electric vehicle (on topic: ev_state).

#### 4. Stop Charging Session
- **Topic**: `stop_charg_ses`
- **Payload**: None
- **Description**: Stops the current charging session.
- **Response**: Confirmation message indicating the session has stopped (on topic: charg_ses).

#### 5. Note
More commands are needed for the full integration of the Smart Charging Logic.