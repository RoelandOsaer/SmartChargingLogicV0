#pragma once
#include <string>

/**
 * @class UserPreferences
 * @brief A class to manage user preferences related to solar usage and scheduling.
 *
 * This class provides functionalities to set and get user preferences, such as solar usage and schedules,
 * and to validate these preferences.
 */
class UserPreferences {
private:
    /**
     * @brief The percentage of solar energy usage.
     */
    int solar_usage;

    /**
     * @brief The schedule for solar energy usage.
     */
    std::string schedule;

public:
    /**
     * @brief Constructs a new UserPreferences object with default values.
     */
    UserPreferences();

    /**
     * @brief Constructs a new UserPreferences object with specified solar usage and schedule.
     *
     * @param solar_usage The percentage of solar energy usage.
     * @param schedule The schedule for solar energy usage.
     */
    UserPreferences(int solar_usage, const std::string& schedule);

    /**
     * @brief Copy constructor.
     *
     * Constructs a new UserPreferences object as a copy of an existing UserPreferences object.
     *
     * @param preference The UserPreferences object to copy.
     */
    UserPreferences(const UserPreferences& preference);

    /**
     * @brief Destroys the UserPreferences object.
     */
    ~UserPreferences();

    /**
     * @brief Gets the percentage of solar energy usage.
     *
     * @return The percentage of solar energy usage.
     */
    int get_solar_usage() const;

    /**
     * @brief Gets the schedule for solar energy usage.
     *
     * @return The schedule for solar energy usage.
     */
    std::string get_schedule() const;

    /**
     * @brief Sets the percentage of solar energy usage.
     *
     * @param solar_usage The new percentage of solar energy usage.
     */
    void set_solar_usage(int solar_usage);

    /**
     * @brief Sets the schedule for solar energy usage.
     *
     * @param schedule The new schedule for solar energy usage.
     */
    void set_schedule(const std::string& schedule);

    /**
     * @brief Checks if the given solar usage percentage is valid.
     *
     * @param percentage The percentage to validate.
     * @return True if the percentage is valid, false otherwise.
     */
    bool is_valid_solar_usage_percentage(int percentage) const;

    /**
     * @brief Checks if the given schedule is valid.
     *
     * @param schedule The schedule to validate.
     * @return True if the schedule is valid, false otherwise.
     */
    bool is_valid_schedule(const std::string& schedule) const;

    /**
     * @brief Sets the schedule based on a string input.
     *
     * This function processes the input string to update the schedule.
     *
     * @param input The input string for the new schedule.
     */
    void set_schedule_with_string(const std::string& input);
};
