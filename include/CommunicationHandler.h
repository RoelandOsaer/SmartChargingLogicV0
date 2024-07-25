#pragma once
#include <string>

/**
 * @class CommunicationHandler
 * @brief A class to handle communication sessions.
 *
 * This class provides functionalities to manage communication sessions,
 * including session identification and tracking the status of the last message sent.
 */
class CommunicationHandler {
protected:
    /**
     * @brief Session ID for the communication handler.
     *
     * This integer value uniquely identifies a communication session.
     */
    int session_id;

    /**
     * @brief Status of the last message sent.
     *
     * This boolean value indicates whether the last message was successfully sent.
     */
    bool last_msg_send;

public:
    /**
     * @brief Constructs a new CommunicationHandler object.
     *
     * Initializes a new communication handler with default values.
     */
    CommunicationHandler();

    /**
     * @brief Destroys the CommunicationHandler object.
     *
     * Cleans up resources used by the communication handler.
     */
    ~CommunicationHandler();

    /**
     * @brief Gets the session ID.
     *
     * @return The session ID of the communication handler.
     */
    int get_session_id();

    /**
     * @brief Sets the session ID.
     *
     * @param session_id The new session ID to be set.
     */
    void set_session_id(int session_id);

    /**
     * @brief Checks if the last message was sent.
     *
     * @return True if the last message was sent, false otherwise.
     */
    bool is_last_msg_send();
};
