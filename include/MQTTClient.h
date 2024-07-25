#pragma once
#include <mosquitto.h>
#include <string>
#include <thread>
#include <functional>
#include <atomic>

/**
 * @class MQTTClient
 * @brief A class to manage MQTT client operations.
 *
 * This class provides functionalities to connect, disconnect, publish, and subscribe to MQTT topics,
 * as well as handling incoming and outgoing messages.
 */
class MQTTClient {
private:
    /**
     * @brief Static callback function for handling incoming MQTT messages.
     *
     * @param mosq The Mosquitto client instance.
     * @param userdata User data provided in the callback.
     * @param message The received Mosquitto message.
     */
    static void on_message(struct mosquitto* mosq, void* userdata, const struct mosquitto_message* message);

    /**
     * @brief Static callback function for handling MQTT connection events.
     *
     * @param mosq The Mosquitto client instance.
     * @param userdata User data provided in the callback.
     * @param result The connection result.
     */
    static void on_connect(struct mosquitto* mosq, void* userdata, int result);

    /**
     * @brief Loop function for running the Mosquitto network loop in a separate thread.
     */
    void loop();

    /**
     * @brief Attempts to reconnect the MQTT client to the broker.
     */
    void reconnect();

    /**
     * @brief The Mosquitto client instance.
     */
    struct mosquitto* mosq_;

    /**
     * @brief The client ID for the MQTT client.
     */
    std::string id_;

    /**
     * @brief The host address of the MQTT broker.
     */
    std::string host_;

    /**
     * @brief The port number of the MQTT broker.
     */
    int port_;

    /**
     * @brief The thread running the Mosquitto network loop.
     */
    std::thread loop_thread_;

    /**
     * @brief Indicates if the MQTT client is running.
     */
    std::atomic<bool> running_;

    /**
     * @brief Callback function for handling incoming MQTT messages.
     */
    std::function<void(const std::string&, const std::string&)> message_callback_;

public:
    /**
     * @brief Constructs a new MQTTClient object.
     *
     * @param id The client ID for the MQTT client.
     * @param host The host address of the MQTT broker.
     * @param port The port number of the MQTT broker.
     */
    MQTTClient(const std::string& id, const std::string& host, int port);

    /**
     * @brief Destroys the MQTTClient object.
     */
    ~MQTTClient();

    /**
     * @brief Connects the MQTT client to the broker.
     *
     * @return True if the connection is successful, false otherwise.
     */
    bool connect();

    /**
     * @brief Disconnects the MQTT client from the broker.
     */
    void disconnect();

    /**
     * @brief Publishes a message to a specified MQTT topic.
     *
     * @param topic The MQTT topic to publish the message to.
     * @param message The message to publish.
     * @return True if the message is published successfully, false otherwise.
     */
    bool publish(const std::string& topic, const std::string& message);

    /**
     * @brief Subscribes to a specified MQTT topic.
     *
     * @param topic The MQTT topic to subscribe to.
     * @return True if the subscription is successful, false otherwise.
     */
    bool subscribe(const std::string& topic);

    /**
     * @brief Callback function for sending MQTT messages from the logic to the user.
     *
     * @param topic The MQTT topic to send the message to.
     * @param message The message to send.
     */
    void on_send_msg_from_logic(const std::string& topic, const std::string& message);

    /**
     * @brief Sets the callback function for handling incoming messages from the user to the logic.
     *
     * @param callback The callback function.
     */
    void set_message_callback(std::function<void(const std::string&, const std::string&)> callback);
};
