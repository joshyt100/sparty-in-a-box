/**
 * @file Component.h
 * @author Josh Thomas
 *
 *
 */
 
#ifndef CANADIANEXPERIENCE_COMPONENT_H
#define CANADIANEXPERIENCE_COMPONENT_H

#include <wx/graphics.h>
#include <memory>

/**
 * Base class for components in the machine.
 */
class Component {
public:
    /// Constructor
    Component() = default;

    /// Virtual destructor
    virtual ~Component() = default;

    /// Set the location of the component
    /// @param location The x, y location to set
    void SetLocation(wxPoint location) { mLocation = location; }

    /// Get the location of the component
    /// @return The current x, y location
    wxPoint GetLocation() const { return mLocation; }

    /// Set the time for the component
    /// @param time The current time
    void SetTime(double time) { mTime = time; }

    /// Get the current time for the component
    /// @return The current time
    double GetTime() const { return mTime; }

    /// Set the speed of the component
    /// @param speed The speed to set
    void SetSpeed(double speed) { mSpeed = speed; }

    /// Get the speed of the component
    /// @return The current speed
    double GetSpeed() const { return mSpeed; }

    /**
     * Draw the component.
     * Must be overridden by derived classes.
     * @param graphics Graphics context to draw on
     */
    virtual void Draw(std::shared_ptr<wxGraphicsContext> graphics) = 0;
    /**
     * Virtual function to be drawn for the box
     * Must be overriden
     * @param graphics
     */
    virtual void DrawForeground(std::shared_ptr<wxGraphicsContext> graphics) {}

    /**
     * Update the component.
     * Must be overridden by derived classes.
     * @param elapsed Time elapsed since the last update
     */
    virtual void Update(double elapsed);

    /**
     * Reset the component to its initial state.
     */
    virtual void Reset() = 0;

private:
    wxPoint mLocation = {0, 0}; ///< Location of the component
    double mTime = 0.0;         ///< Time associated with the component
    double mSpeed = 0.0;        ///< Speed of the component
};

#endif // CANADIANEXPERIENCE_COMPONENT_H
