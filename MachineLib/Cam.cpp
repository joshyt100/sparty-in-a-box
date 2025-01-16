/**
 * @file Cam.cpp
 * @author Josh Thomas
 */

#include "pch.h"
#include "Cam.h"
#include "IActivate.h"

/**
 * Constructor
 * @param imagesDir Directory containing the images
 */
Cam::Cam(const std::wstring& imagesDir)
{
    // Configure the key polygon
    mKey.SetImage(imagesDir + L"/key.png");
    mKey.Rectangle(-KeyImageSize/2, 0, KeyImageSize, KeyImageSize);

    // Configure the cylinder
    mCylinder.SetSize(CamDiameter, CamWidth);
    mCylinder.SetColour(*wxWHITE);
    mCylinder.SetBorderColor(*wxBLACK);
}

/**
 * Update the component
 * @param elapsed Time elapsed since last update
 */
void Cam::Update(double elapsed)
{
    Component::Update(elapsed);

    if (mIsActivated)
    {
        mActivationTimer += elapsed;
        if (mActivationTimer >= ActivationDuration)
        {
            // Time to reset
            mIsActivated = false;
            mActivationTimer = 0;
            mKeyDropped = false;

            // Reset all targets
            for (auto target : mTargets)
            {
                target->OnKeyDrop();  // This second call will reset them
            }
        }
    }
}

/**
 * Draw the cam
 * @param graphics Graphics context to draw on
 */
void Cam::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    graphics->PushState();

    auto loc = GetLocation();
    graphics->Translate(loc.x, loc.y);

    // Draw the cam cylinder vertically, negative rotation to reverse direction
    mCylinder.Draw(graphics, -CamDiameter/2 + 25, -CamWidth/2, -mRotation);

    // Calculate hole position based on reversed rotation
    double angle = -mRotation * 2 * M_PI;

    // The hole moves up and down within the cylinder
    double holeY = (CamDiameter/3) * sin(angle);

    // Draw hole with elliptical distortion based on angle
    double scaleY = std::abs(cos(angle));
    graphics->SetBrush(*wxBLACK_BRUSH);
    graphics->SetPen(*wxTRANSPARENT_PEN);
    graphics->DrawEllipse(0,
                         holeY - (HoleSize/2 * scaleY),
                         HoleSize, HoleSize * scaleY);

    // Draw the key
    double keyY = -KeyImageSize - (mKeyDropped ? KeyDrop : 0);
    mKey.DrawPolygon(graphics, 5, keyY);

    graphics->PopState();
}

/**
 * Set the rotation of the cam
 * @param rotation The rotation amount in turns
 */
void Cam::SetRotation(double rotation)
{
    mRotation = rotation;

    // Only check for new activations if we're not currently activated
    if (!mIsActivated)
    {
        // Use negative rotation for angle calculations
        double angle = -rotation * 2 * M_PI;
        double prevAngle = -mPrevRotation * 2 * M_PI;

        // Key drops when hole reaches top position (sin near 1)
        if (sin(prevAngle) < 0.95 && sin(angle) >= 0.95)
        {
            mKeyDropped = true;
            mIsActivated = true;
            mActivationTimer = 0;

            // Notify all registered components
            for (auto target : mTargets)
            {
                target->OnKeyDrop();
            }
        }
    }

    mPrevRotation = rotation;
}

/**
 * Reset the cam to its initial state
 */
void Cam::Reset()
{
    mKeyDropped = false;
    mRotation = 0;
    mPrevRotation = 0;
    mIsActivated = false;
    mActivationTimer = 0;
}

/**
 * Add a component that should be activated when the key drops
 * @param target Component that implements IActivate
 */
void Cam::AddActivationTarget(std::shared_ptr<IActivate> target)
{
    mTargets.push_back(target);
}