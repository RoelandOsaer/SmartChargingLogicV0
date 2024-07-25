#pragma once
#include <string>

/**
 * @class AuthenticationManager
 * @brief A class to manage authentication processes.
 *
 * This class provides functionalities to authenticate the payment methode, check authentication status,
 * and deauthenticate payment sesion.
 */
class AuthenticationManager {
private:
    /**
     * @brief Indicates if the authentication is active.
     *
     * This boolean value represents whether the current session is authenticated.
     */
    bool active;

public:
    /**
     * @brief Constructs a new AuthenticationManager object.
     *
     * Initializes a new authentication manager with default values.
     */
    AuthenticationManager();

    /**
     * @brief Destroys the AuthenticationManager object.
     *
     * Cleans up resources used by the authentication manager.
     */
    ~AuthenticationManager();

    /**
     * @brief Authenticates the payment session with a given key.
     *
     * Checks the provided key and sets the authentication status accordingly.
     *
     * @param key The authentication key.
     * @return True if the authentication is successful, false otherwise.
     */
    bool authenticate(std::string key);

    /**
     * @brief Checks if the payment session is authenticated.
     *
     * @return True if the payment session is authenticated, false otherwise.
     */
    bool is_authenticated();

    /**
     * @brief Deauthenticates the session.
     *
     * Resets the authentication status to inactive.
     */
    void deauthenticate();
};
