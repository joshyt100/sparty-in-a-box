/**
* @file Box.cpp
 * @author Joshua Thomas
 */

#include "pch.h"
#include "Box.h"
#include <cmath>

/// The background image filename for the box
const std::wstring BoxBackgroundImage = L"/box-background.png";


Box::Box(const std::wstring& imagesDir, int boxSize, int lidSize)
    : mBoxSize(boxSize), mLidSize(lidSize), mLidAngle(LidClosedAngle) // Initialize lid to closed position
{
    // Configure the polygon for the box background
    mBox.Rectangle(-boxSize / 2, 0, boxSize, boxSize);
    mBox.SetImage(imagesDir + BoxBackgroundImage);

    // Configure the polygon for the lid
    mLid.Rectangle(-lidSize / 2, 0, lidSize, lidSize); // Lid positioned with its bottom edge at the hinge
    mLid.SetImage(imagesDir + L"/box-lid.png");

    // Configure the polygon for the foreground
    mForeground.Rectangle(-boxSize / 2, 0, boxSize, boxSize);
    mForeground.SetImage(imagesDir + L"/box-foreground.png");
    std::wcout << L"Box Background Path: " << imagesDir + BoxBackgroundImage<< std::endl;
}

/**
 * Draws the box
 * @param graphics
 */
void Box::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    // Draw the box background
    mBox.DrawPolygon(graphics, GetLocation().x, GetLocation().y);

    // Draw the lid
    graphics->PushState();

    // Translate to the hinge position (top center of the box)
    graphics->Translate(GetLocation().x, GetLocation().y - mBoxSize);

    // Calculate the vertical scale of the lid
    double scale = LidZeroAngleScale + (1-LidZeroAngleScale)* sin(mLidAngle);
    graphics->PushState();
    graphics->Translate(GetLocation().x, GetLocation().y);
    graphics->Scale(1, scale);
    mLid.DrawPolygon(graphics,0,0);
    graphics->PopState();




    // Apply vertical scaling to the lid
    graphics->PopState();
}

/**
 * Function draws the purple foreground
 * @param graphics
 */
void Box::DrawForeground(std::shared_ptr<wxGraphicsContext> graphics)
{
    mForeground.DrawPolygon(graphics, GetLocation().x, GetLocation().y);
}

/**
 * Update the box animation
 * @param delta Amount of time to advance in seconds
 */
void Box::Update(double delta)
{
    Component::Update(delta);	// Upcall

    double openAngle = M_PI / 2;

    if(mOpen && mLidAngle < openAngle)
    {
        mLidAngle += openAngle * delta / LidOpeningTime;

        if(mLidAngle > openAngle)
        {
            mLidAngle = openAngle;
        }
    }
}

/**
 * Resets the state of the box
 */
void Box::Reset()
{
    // Component::Reset();  // Remove this line since Reset() is virtual
    mLidAngle = 0;  // Reset lid to closed position
    mOpen = false;   // For testing, keep it set to true
}