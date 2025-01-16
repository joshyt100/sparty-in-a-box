/**
 *@file Pulley.h
 *@author Joshua Thomas
 **/

#ifndef CANADIANEXPERIENCE_PULLEY_H
#define CANADIANEXPERIENCE_PULLEY_H

#include "Component.h"
#include "RotationSource.h"
#include "RotationSink.h"
#include "Cylinder.h"
#include <memory>

#include "Polygon.h"

/**
 * Pulley class represents a pulley that rotates and drives other pulleys via belts.
 */
class Pulley : public Component, public RotationSink {
public:
    /**
     * Constructor
     * @param radius Radius of the pulley
     */
    Pulley(double radius);

    /**
     * Draw the pulley.
     * @param graphics Graphics context to draw on
     */
    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;

    /**
     * Update the pulley (unused for now).
     * @param elapsed Elapsed time
     */
    void Update(double elapsed) override {}

    /**
     * Reset the pulley.
     */
    void Reset() override {}

    /**
     * Set the rotation in turns.
     * @param rotation Rotation in turns
     */
    void SetRotation(double rotation) override;

    /**
     * Connect this pulley to another via a belt.
     * @param otherPulley The other pulley to connect to
     */
    void BeltTo(std::shared_ptr<Pulley> otherPulley);

    /**
     * Get the rotation source for this pulley.
     * @return Pointer to the RotationSource
     */
    RotationSource* GetSource() { return &mSource; }

    /**
     * Get the radius of the pulley.
     * @return Radius of the pulley
     */
    double GetRadius() const { return mRadius; }

private:
    double mRadius; ///< Radius of the pulley
    double mRotation = 0.0; ///< Current rotation in turns
    std::shared_ptr<Pulley> mBeltConnectedPulley; ///< Pulley connected via a belt
    RotationSource mSource; ///< Rotation source for this pulley

    cse335::Cylinder mHubLeft; ///< Left hub cylinder
    cse335::Cylinder mHubRight; ///< Right hub cylinder
    /// Polygon for belt
    cse335::Polygon mBelt;
};

#endif // CANADIANEXPERIENCE_PULLEY_H
