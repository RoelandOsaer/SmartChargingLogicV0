#pragma once
#include "CommunicationHandler.h"
#include <string>
#include <tuple>

/**
 * @class ChargingSessionCommunicationHandler
 * @brief A class to handle communication during a charging session.
 *
 * This class inherits from CommunicationHandler and adds functionality specific
 * to managing a charging session, including tracking the state of charge and
 * battery temperature.
 */
class ChargingSessionCommunicationHandler : public CommunicationHandler {
private:
    /**
     * @brief State of charge of the vehicle's battery.
     *
     * This integer value represents the current state of charge (SOC) as a percentage.
     */
    int state_of_charge;

    /**
     * @brief Temperature of the vehicle's battery.
     *
     * This integer value represents the current temperature of the battery in degrees Celsius.
     */
    int battery_temp;

public:
    /**
     * @brief Constructs a new ChargingSessionCommunicationHandler object.
     *
     * Initializes a new charging session communication handler with default values.
     */
    ChargingSessionCommunicationHandler();

    /**
     * @brief Destroys the ChargingSessionCommunicationHandler object.
     *
     * Cleans up resources used by the charging session communication handler.
     */
    ~ChargingSessionCommunicationHandler();

    /**
     * @brief Updates the state of charge and battery temperature from the car.
     *
     * Retrieves the latest state of charge and battery temperature data from the car and updates the corresponding member variables.
     */
    void update_stats_from_car();

    /**
     * @brief Gets the state of charge and battery temperature.
     *
     * @return A tuple containing the state of charge and battery temperature.
     */
    std::tuple<int, int> get_stats();
};
