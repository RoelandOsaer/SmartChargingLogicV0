#pragma once
#include "AuthenticationManager.h"
#include "ChargingSessionManager.h"
#include "UserPreferences.h"
#include "SetupState.h"
#include <functional>
#include <thread>
#include <atomic>

/**
 * @class EvseController
 * @brief A class to manage the Electric Vehicle Supply Equipment (EVSE) controller.
 *
 * This class provides functionalities to manage the EVSE controller, including authentication,
 * charging session management, user preferences, and communication with the car.
 */
class EvseController {
private:
    /**
     * @brief Manages authentication processes.
     */
    AuthenticationManager* auth_manager;

    /**
     * @brief Manages charging sessions.
     */
    ChargingSessionManager* session_manager;

    /**
     * @brief User preferences used during operation.
     */
    UserPreferences used_preference;

    /**
     * @brief User preferences when offline.
     */
    UserPreferences offline_preference;

    /**
     * @brief Current setup state of the EVSE controller.
     */
    SetupState current_state;

    /**
     * @brief Indicates if the car is currently charging.
     */
    bool car_is_charging;

    /**
     * @brief Indicates if the charging session is pauzed.
     */
    bool charging_session_is_pauzed;

    /**
     * @brief The state of charge when charging starts.
     */
    int start_state_of_charge;

    /**
     * @brief The state of charge when charging stops.
     */
    int stop_state_of_charge;

    /**
     * @brief Callback function to send messages.
     */
    std::function<void(const std::string&, const std::string&)> send_message_callback_;

    /**
     * @brief Message for the user.
     */
    std::string msg_for_user;

    /**
     * @brief Periodic communication with the car.
     */
    void periodic_comm_with_car();

    /**
     * @brief Starts periodic communication with the car.
     */
    void start_periodic_comm_with_car();

    /**
     * @brief Stops periodic communication with the car.
     */
    void stop_periodic_comm_with_car();

    /**
     * @brief Indicates if the periodic communication is running.
     */
    std::atomic<bool> running_;

    /**
     * @brief Thread for periodic communication.
     */
    std::thread periodic_thread_;

    /**
     * @brief Checks if the current time is within the specified schedule.
     *
     * @param schedule The schedule to check against.
     * @return True if within the time window, false otherwise.
     */
    bool is_within_time_window(const std::string& schedule);

    /**
     * @brief Charges the car using solar energy.
     *
     * @return The amount of energy charged using solar.
     */
    int get_car_charged_with_solar();

    /**
     * @brief Charges the car using grid energy.
     *
     * @return The amount of energy charged using grid.
     */
    int get_car_charged_on_grid();

    /**
     * @brief Indicates if solar energy is available.
     */
    bool availabe_solar_enegie;

public:
    /**
     * @brief Constructs a new EvseController object.
     */
    EvseController();

    /**
     * @brief Destroys the EvseController object.
     */
    ~EvseController();

    /**
     * @brief Starts a new charging session.
     */
    void start_charging_session();

    /**
     * @brief Stops the current charging session.
     */
    void stop_charging_session();

    /**
     * @brief Pauses the current charging session.
     */
    void pauze_charging_session();

    /**
     * @brief Handles authentication with the provided key.
     *
     * @param key The authentication key.
     * @return True if authentication is successful, false otherwise.
     */
    bool handle_authentication(std::string key);

    /**
     * @brief Updates the user preferences.
     *
     * @param preference The new user preferences.
     */
    void update_user_preferences(const UserPreferences& preference);

    /**
     * @brief Processes an event in the state machine.
     *
     * @tparam Func The type of the function to process the event.
     * @param func The function to process the event.
     * @param event The event to process.
     * @param current_state The current state of the setup.
     * @return True if the event is processed successfully, false otherwise.
     */
    template <typename Func>
    bool process_event(Func func, SetupEvent event, SetupState& current_state);

    /**
     * @brief Handles the idle state in the state machine.
     *
     * @param event The event to handle.
     * @param current_state The current state of the setup.
     */
    void handle_idle_state(SetupEvent event, SetupState& current_state);

    /**
     * @brief Handles the car connected state in the state machine.
     *
     * @param event The event to handle.
     * @param current_state The current state of the setup.
     */
    void handle_car_connected_state(SetupEvent event, SetupState& current_state);

    /**
     * @brief Handles the initial communication done state in the state machine.
     *
     * @param event The event to handle.
     * @param current_state The current state of the setup.
     */
    void handle_initial_comm_done_state(SetupEvent event, SetupState& current_state);

    /**
     * @brief Handles the inverter chosen state in the state machine.
     *
     * @param event The event to handle.
     * @param current_state The current state of the setup.
     */
    void handle_inverter_chosen_state(SetupEvent event, SetupState& current_state);

    /**
     * @brief Checks the state of the electric vehicle.
     */
    void checking_ev_state();

    /**
     * @brief Callback function for receiving messages from MQTT.
     *
     * @param topic The MQTT topic.
     * @param message The MQTT message.
     */
    void on_MQTT_message(const std::string& topic, const std::string& message);

    /**
     * @brief Sets the callback function for outgoing MQTT messages.
     *
     * @param callback The callback function.
     */
    void set_message_callback(std::function<void(const std::string&, const std::string&)>callback);

    /**
     * @brief Sends a message to the user.
     *
     * @param topic The topic of the message.
     * @param message The message content.
     */
    void send_message_to_user(const std::string& topic, const std::string& message);
};
