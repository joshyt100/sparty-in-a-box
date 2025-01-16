/**
* @file Box.h
 * @author Josh Thomas
 */

#ifndef CANADIANEXPERIENCE_BOX_H
#define CANADIANEXPERIENCE_BOX_H

#include "Polygon.h"
#include "Component.h"
#include <string>

#include "IActivate.h"

/**
 * A box component for the machine.
 */
class Box : public Component, public IActivate {
public:
    /**
     * Constructor for box
     * @param imagesDir
     * @param boxSize
     * @param lidSize
     */
    Box(const std::wstring& imagesDir, int boxSize, int lidSize);

    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;

    void Update(double elapsed) override;
    void Reset() override;
    void DrawForeground(std::shared_ptr<wxGraphicsContext> graphics) override;
    /**
     * Onkeydrop signals for when the box lid should open according to the cam
     */
    void OnKeyDrop() override {mOpen = !mOpen;}

private:
    // Constants for lid angles and scaling

    static constexpr double LidClosedAngle = 0;        ///< Angle when lid is closed
    static constexpr double LidOpenAngle = M_PI/2;     ///< Angle when lid is fully open
    static constexpr double LidZeroAngleScale = 0.02;   ///< Scale when lid is closed

    cse335::Polygon mBox;       ///< The box background polygon
    cse335::Polygon mLid;       ///< Polygon for lid
    cse335::Polygon mForeground; ///< Foreground polygon
    int mBoxSize;              ///< Size of the box in pixels
    int mLidSize;              ///< Size of the lid in pixels
    /// Time in seconds for lid to fully open
    const double LidOpeningTime = 1.0;

    /// Current angle of the lid in radians
    double mLidAngle = 0;

    /// Flag indicating if box should be opening
    bool mOpen = false;  // Set to true initially for testing
};

#endif // CANADIANEXPERIENCE_BOX_H