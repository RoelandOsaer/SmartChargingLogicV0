#include "MQTTclient.h"
#include <iostream>
#include <string>

//Normall constructor
MQTTClient::MQTTClient(const std::string& id, const std::string& host, int port)
    : id_(id), host_(host), port_(port) {
    mosquitto_lib_init();
    mosq_ = mosquitto_new(id.c_str(), true, this);
    if (!mosq_) {
        throw std::runtime_error("Failed to create mosquitto instance");
    }
    //connect the callback function for incomming connections and messages.
    mosquitto_connect_callback_set(mosq_, on_connect);
    mosquitto_message_callback_set(mosq_, on_message);
}

// Destructor
MQTTClient::~MQTTClient() {
    disconnect();
    mosquitto_destroy(mosq_);
    mosquitto_lib_cleanup();
}

// Set the callback for received messages from the user to the logic
void MQTTClient::set_message_callback(std::function<void(const std::string&, const std::string&)> callback)
{
    message_callback_ = callback;
}


// Callback function for handling incoming MQTT messages 
void MQTTClient::on_message(struct mosquitto* mosq, void* userdata, const struct mosquitto_message* message) {
    MQTTClient* client = static_cast<MQTTClient*>(userdata); // Retrieve the client object
    std::cout << "msg_receved\n";
    if (message) {
        // Convert payload to string
        std::string msg_payload(static_cast<char*>(message->payload), message->payloadlen);
        
        // Call the user-provided callback and send topic and msg throug.
        if (client->message_callback_) {
            client->message_callback_(message->topic, msg_payload);
        }
    }
}

// Callback function to handle ACK from connected clients
void MQTTClient::on_connect(struct mosquitto* mosq, void* userdata, int result) {
    if (result == 0) {
        std::cout << "Client connected successfully." << std::endl;
    }
    else {
        std::cerr << "Client connection failed: " << mosquitto_strerror(result) << std::endl;
    }
}



// Connect to the MQTT broker
bool MQTTClient::connect() {
    int ret = mosquitto_connect(mosq_, host_.c_str(), port_, 60);
    if (ret != MOSQ_ERR_SUCCESS) {
        std::cerr << "Unable to connect: " << mosquitto_strerror(ret) << std::endl;
        return false;
    }
    //int test = mosquitto_loop_start(mosq_);
    running_ = true;
    loop_thread_ = std::thread(&MQTTClient::loop, this);
    return true;
}

// Disconnect from the MQTT broker
void MQTTClient::disconnect() {
    running_ = false;
    if (loop_thread_.joinable()) {
        loop_thread_.join();
    }
    mosquitto_disconnect(mosq_);
}

// The loop function to handle events
void MQTTClient::loop() {
    while (running_) {
        int ret = mosquitto_loop(mosq_, -1, 1);
        if (ret != MOSQ_ERR_SUCCESS) {
            std::cerr << "Error in mosquitto loop: " << mosquitto_strerror(ret) << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(1)); // Prevent busy loop on error
            reconnect();
        }
    }
}

void MQTTClient::reconnect() {
    while (running_) {
        int ret = mosquitto_reconnect(mosq_);
        if (ret == MOSQ_ERR_SUCCESS) {
            std::cout << "Reconnected to the broker successfully." << std::endl;
            break;
        }
        else {
            std::cerr << "Reconnection failed: " << mosquitto_strerror(ret) << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(5));
        }
    }
}

void MQTTClient::on_send_msg_from_logic(const std::string& topic, const std::string& message)
{
    std::cout << "sending msg to user\n";
    publish(topic, message);
}

// Publish a message to a topic
bool MQTTClient::publish(const std::string& topic, const std::string& message) {
    int ret = mosquitto_publish(mosq_, nullptr, topic.c_str(), message.size(), message.c_str(), 0, false);
    if (ret != MOSQ_ERR_SUCCESS) {
        std::cerr << "Failed to publish message: " << mosquitto_strerror(ret) << std::endl;
        return false;
    }
    return true;
}

// Subscribe to a topic
bool MQTTClient::subscribe(const std::string& topic) {
    int ret = mosquitto_subscribe(mosq_, nullptr, topic.c_str(), 0);
    if (ret != MOSQ_ERR_SUCCESS) {
        std::cerr << "Failed to subscribe to topic: " << mosquitto_strerror(ret) << std::endl;
        return false;
    }
    return true;
}




