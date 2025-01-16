/**
* @file Cam.h
 * @author Josh Thomas
 */

#ifndef CANADIANEXPERIENCE_CAM_H
#define CANADIANEXPERIENCE_CAM_H

#include "Component.h"
#include "Cylinder.h"
#include "RotationSink.h"
#include "Polygon.h"
#include <vector>
#include <memory>

class IActivate;

/**
 * The Cam class represents a rotating cam with a hole that triggers a key drop.
 */
class Cam : public Component, public RotationSink {
private:
    /// The cam cylinder
    cse335::Cylinder mCylinder;

    /// The key polygon
    cse335::Polygon mKey;

    /// Width of the cam on the screen in pixels
    const double CamWidth = 17;

    /// Cam diameter
    const double CamDiameter = 60;

    /// How big is the hole in the cam?
    const double HoleSize = 8;

    /// The key image size
    const int KeyImageSize = 20;

    /// The amount the key drops into the hole
    const int KeyDrop = 10;

    /// Duration to hold activation in seconds
    const double ActivationDuration = 1.0;

    /// Current rotation in turns
    double mRotation = 0;

    /// Is the key currently dropped?
    bool mKeyDropped = false;

    /// Previous rotation for detecting transitions
    double mPrevRotation = 0;

    /// Collection of components to activate
    std::vector<std::shared_ptr<IActivate>> mTargets;

    /// Timer for activation duration
    double mActivationTimer = 0;

    /// Is currently in activated state?
    bool mIsActivated = false;

public:
    /// Constructor
    /// @param imagesDir Directory containing the images
    explicit Cam(const std::wstring& imagesDir);

    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;
    void SetRotation(double rotation) override;
    void Reset() override;
    void Update(double elapsed) override;
    void AddActivationTarget(std::shared_ptr<IActivate> target);
};

#endif //CANADIANEXPERIENCE_CAM_H