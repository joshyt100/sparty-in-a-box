/**
 *@file Crank.h
 *@author Joshua Thomas
 **/
#ifndef CANADIANEXPERIENCE_CRANK_H
#define CANADIANEXPERIENCE_CRANK_H

#include "Component.h"
#include "Cylinder.h"
#include "RotationSource.h"

/**
 * Class Crank represents a crank in the machine.
 */
class Crank : public Component {
public:
    Crank();

    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;
    void Update(double elapsed) override;
    void Reset() override;

    /// Get the crank's rotation source
    /**
     *Gets the source
     *@return &mSource
     **/
    RotationSource* GetSource() { return &mSource; }

    /**
     * Set the cranks speed
     * @param speed
     */
    void SetSpeed(double speed) { mSpeed = speed; }

private:
    cse335::Cylinder mHandle; ///< Handle cylinder for the crank
    RotationSource mSource; ///< Rotation source for the crank
    double mRotation = 0.0; ///< Current rotation in turns
    double mSpeed = 0.0; ///< Speed of the crank in turns per second
};

#endif // CANADIANEXPERIENCE_CRANK_H
