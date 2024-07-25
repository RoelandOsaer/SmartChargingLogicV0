#pragma once
#include "UserPreferences.h"
#include "Inverter.h"
#include "CommunicationHandler.h"
#include "InitialCommunicationHandler.h"
#include "ChargingSessionCommunicationHandler.h"
#include <vector>

/**
 * @class ChargingSessionManager
 * @brief A class to manage the charging sessions for electric vehicles.
 *
 * This class provides functionalities to handle initial communication with the car,
 * manage the charging session, and interact with the inverter and user preferences.
 */
class ChargingSessionManager {
private:
    /**
     * @brief The voltage level for the charging session.
     */
    int voltage;

    /**
     * @brief The current level for the charging session.
     */
    int current;

    /**
     * @brief The session ID for the charging session.
     */
    int session_id;

    /**
     * @brief Indicates if it is the first communication after initialization.
     */
    bool first_comm_after_init;

    /**
     * @brief User preferences for the charging session.
     */
    UserPreferences* used_preference;

    /**
     * @brief The inverter used for the charging session.
     */
    Inverter* used_inverter;

    /**
     * @brief Handler for initial communication with the car.
     */
    InitialCommunicationHandler* init_comm_handler;

    /**
     * @brief Handler for communication during the charging session.
     */
    ChargingSessionCommunicationHandler* session_comm_handler;

public:
    /**
     * @brief Constructs a new ChargingSessionManager object.
     */
    ChargingSessionManager();

    /**
     * @brief Destroys the ChargingSessionManager object.
     */
    ~ChargingSessionManager();

    /**
     * @brief Performs initial communication with the car.
     *
     * @return True if the initial communication is successful, false otherwise.
     */
    bool do_initial_comm_with_car();

    /**
     * @brief Performs communication with the car during the charging session.
     *
     * @return True if the charging communication is successful, false otherwise.
     */
    bool do_charging_comm_with_car();

    /**
     * @brief Chooses the inverter for the charging session.
     *
     * @return True if the inverter is successfully chosen, false otherwise.
     */
    bool chose_inverter();

    /**
     * @brief Gets the voltage level for the charging session.
     *
     * @return The voltage level.
     */
    int get_voltage() const;

    /**
     * @brief Gets the current level for the charging session.
     *
     * @return The current level.
     */
    int get_current() const;

    /**
     * @brief Starts the inverter for the charging session.
     */
    void start_inverter();

    /**
     * @brief Stops the inverter for the charging session.
     */
    void stop_inverter();

    /**
     * @brief Gets the state of charge of the car.
     *
     * @return The state of charge.
     */
    int get_state_of_charge();
};
