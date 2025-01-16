/**
 * @file Shaft.h
 * @author Josh Thomas
 *
 *
 */

#ifndef CANADIANEXPERIENCE_SHAFT_H
#define CANADIANEXPERIENCE_SHAFT_H

#include "Component.h"
#include "RotationSink.h"
#include "Cylinder.h"
#include "RotationSource.h"

/**
 * The Shaft class represents a rotating shaft in the machine.
 */
class Shaft : public Component, public RotationSink {
public:
    /// Constructor
    Shaft();

    /// Draw the shaft
    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;

    /// Update the shaft (no behavior yet)
    /**
     *update not overriden
     *@param elapsed
     **/
    void Update(double elapsed) override {}

    /// Reset the shaft
    void Reset() override {}

    /// Set the rotation in turns
    /// @param rotation Rotation in turns
    void SetRotation(double rotation) override;

    /**
     * Sets the size
     * @param diameter
     * @param length
     */
    void SetSize(int diameter, int length)
    {
        mShaft.SetSize(diameter, length);
    }

    /**
     * Gets rotation source
     * @return &mSource
     */
    RotationSource *GetSource() {return &mSource;}


private:
    cse335::Cylinder mShaft; ///< The graphical representation of the shaft
    double mRotation = 0.0; ///< Current rotation in turns
    /// Source member variable
    RotationSource mSource;
};

#endif // CANADIANEXPERIENCE_SHAFT_H
