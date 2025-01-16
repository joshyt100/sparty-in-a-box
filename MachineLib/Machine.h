/**
 * @file Machine.h
 * @author Josh Thomas
 *
 *
 */
 
#ifndef CANADIANEXPERIENCE_MACHINE_H
#define CANADIANEXPERIENCE_MACHINE_H

#include <vector>
#include <memory>
#include "Component.h"

/**
 * Class that represents a machine.
 */
class Machine {
public:
    /// Constructor
    Machine() = default;

    /// Add a component to the machine
    /// @param component The component to add
    void AddComponent(std::shared_ptr<Component> component);

    /// Set the location of the machine on the screen
    /// @param location The location to set
    void SetLocation(wxPoint location);

    /// Draw all components in the machine
    /// @param graphics Graphics context to draw on
    void Draw(std::shared_ptr<wxGraphicsContext> graphics);
    /// Set the machine's time
    /// @param time The current machine time in seconds
    void SetTime(double time);

    /// Advance the machine by a given time increment
    /// @param elapsed Time to advance in seconds
    void Advance(double elapsed);

    /// Reset the machine to its initial state
    void Reset();



private:
    wxPoint mLocation = {0, 0}; ///< Location of the machine on the screen
    std::vector<std::shared_ptr<Component>> mComponents; ///< List of components in the machine
};

#endif // CANADIANEXPERIENCE_MACHINE_H
