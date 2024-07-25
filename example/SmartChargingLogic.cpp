// SmartChargingLogic.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include "../EvseController.h"
#include "../UserPreferences.h"
#include "../MqttClient.h"
#include <thread>

int main()
{
    //Initialise the client object.
    MQTTClient client("cpp_client", "localhost", 1883);

    //Connect the client to the broker.
    if (!client.connect()) {
        std::cout << "Could not connect to broker\n";
        return 1;
    }
    std::cout << "connected with broker\n";

    //Subscribe to the needed topics.
    std::vector<std::string> topics = { "update_pref","start_charg_ses","check_ev_state","stop_charg_ses"};
    for (int x = 0; x <= topics.size()-1; x++) {
        if (!client.subscribe(topics[x])) {
            std::cerr << "Failed to subscribe to topic: "<<topics[x];
            return 1;
        }
    }
    
    
    //Make an instance of the EVSEController class
    EvseController evse;
    // Set the callback function so receved messages from the user get into the evse object.
    client.set_message_callback([&evse](const std::string& topic, const std::string& message) {
        evse.on_MQTT_message(topic, message);
        });

    // Set the callback function so send messages form the logic can be send by the MQTT.
    evse.set_message_callback([&client](const std::string& topic, const std::string& message) {
        client.on_send_msg_from_logic(topic, message);
        });

    std::cout << "waiting on action from the user.\n";
    while (true)
    {
    }
}