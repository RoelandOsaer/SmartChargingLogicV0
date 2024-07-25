#pragma once
#include "CommunicationHandler.h"
#include <string>
#include <tuple>

/**
 * @class InitialCommunicationHandler
 * @brief A class to handle initial communication with a car.
 *
 * This class inherits from CommunicationHandler and adds functionality specific
 * to managing the initial communication, including retrieving required voltage
 * and current information.
 */
class InitialCommunicationHandler : public CommunicationHandler {
private:
    /**
     * @brief Required voltage for the car.
     *
     * This integer value represents the voltage required by the car during the initial communication phase.
     */
    int required_voltage;

    /**
     * @brief Required current for the car.
     *
     * This integer value represents the current required by the car during the initial communication phase.
     */
    int required_current;

public:
    /**
     * @brief Constructs a new InitialCommunicationHandler object.
     *
     * Initializes a new initial communication handler with default values.
     */
    InitialCommunicationHandler();

    /**
     * @brief Destroys the InitialCommunicationHandler object.
     *
     * Cleans up resources used by the initial communication handler.
     */
    ~InitialCommunicationHandler();

    /**
     * @brief Gets the required voltage and current from the car.
     *
     * Retrieves the required voltage and current information from the car during the initial communication phase.
     *
     * @return A tuple containing the required voltage and current.
     */
    std::tuple<int, int> get_initial_information_from_car();
};
