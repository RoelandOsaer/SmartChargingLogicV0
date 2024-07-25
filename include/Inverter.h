#pragma once
#include <tuple>

/**
 * @class Inverter
 * @brief A class to manage an inverter's operation.
 *
 * This class provides functionalities to start and stop an inverter, as well as to retrieve its status.
 */
class Inverter {
private:
    /**
     * @brief Indicates if the inverter is active.
     */
    bool inverter_active;

    /**
     * @brief The ID of the inverter.
     */
    int id;

    /**
     * @brief The voltage level of the inverter.
     */
    int voltage;

    /**
     * @brief The current level of the inverter.
     */
    int current;

public:
    /**
     * @brief Constructs a new Inverter object with default values.
     */
    Inverter();

    /**
     * @brief Constructs a new Inverter object with specified voltage, current, and ID.
     *
     * @param vol The voltage level of the inverter.
     * @param cur The current level of the inverter.
     * @param id The ID of the inverter.
     */
    Inverter(int vol, int cur, int id);

    /**
     * @brief Copy constructor.
     *
     * Constructs a new Inverter object as a copy of an existing Inverter object.
     *
     * @param inv The Inverter object to copy.
     */
    Inverter(const Inverter& inv);

    /**
     * @brief Move constructor.
     *
     * Constructs a new Inverter object by transferring resources from an existing Inverter object.
     *
     * @param inv The Inverter object to move.
     */
    Inverter(Inverter&& inv) noexcept;

    /**
     * @brief Copy assignment operator.
     *
     * Assigns the values from an existing Inverter object to this object.
     *
     * @param inv The Inverter object to copy.
     * @return A reference to this Inverter object.
     */
    Inverter& operator=(const Inverter& inv);

    /**
     * @brief Move assignment operator.
     *
     * Assigns the values from an existing Inverter object to this object by transferring resources.
     *
     * @param inv The Inverter object to move.
     * @return A reference to this Inverter object.
     */
    Inverter& operator=(Inverter&& inv) noexcept;

    /**
     * @brief Destroys the Inverter object.
     */
    ~Inverter();

    /**
     * @brief Gets the inverter's voltage and current statistics.
     *
     * @return A tuple containing the voltage and current levels.
     */
    std::tuple<int, int> get_inverter_stats();

    /**
     * @brief Starts the inverter.
     */
    void start_inverter();

    /**
     * @brief Stops the inverter.
     */
    void stop_inverter();
};
