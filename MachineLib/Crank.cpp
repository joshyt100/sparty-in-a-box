/**
 *@file Crank.cpp
 *@author Joshua Thomas
 **/
#include "pch.h"
#include "Crank.h"

/// The width of the crank on the screen in pixels
const int CrankWidth = 10;

/// The length of the crank in pixels
const int CrankLength = 50;

/// How much to the left of the crank X the handle starts in pixels
const int HandleStartX = -10;

/// The diameter to draw the crank handle
const int HandleDiameter = 7;

/// How long the handle is in pixels
const int HandleLength = 40;

/// Crank color
const wxColour CrankColor = wxColour(220, 220, 220);

/// Line color for the crank handle
const wxColour CrankHandleLineColor = wxColour(100, 100, 100);

Crank::Crank()
{
    // Configure the crank handle
    mHandle.SetSize(HandleDiameter, HandleLength);
    mHandle.SetColour(CrankColor);
    mHandle.SetLines(CrankHandleLineColor, 1, 4);
}

/**
 * Draws the crank
 * @param graphics
 */
void Crank::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    wxBrush crankBrush(CrankColor);
    graphics->SetBrush(crankBrush);
    graphics->SetPen(*wxTRANSPARENT_PEN);
    double angle = mRotation * 2.0 * M_PI; // Convert turns to radians

    double handleY = GetLocation().y + cos(angle) * CrankLength / 2;
    mHandle.Draw(graphics, GetLocation().x + HandleStartX, handleY - 10, mRotation);
    // Draw the crank rectangle vertically
    graphics->DrawRectangle(GetLocation().x - CrankWidth / 2, GetLocation().y - CrankLength / 2, CrankWidth, CrankLength * cos(angle));

    // Calculate the Y position for the handle

    // Draw the handle
}

/**
 * Updates the cranks rotation
 * @param elapsed
 */
void Crank::Update(double elapsed)
{
    // Advance the crank's rotation
    mRotation += elapsed * mSpeed;

    // Set the rotation in the source and propagate
    mSource.SetRotation(mRotation);
}

/**
 * Resets the crank
 */
void Crank::Reset()
{
    mRotation = 0.0; // Reset rotation
    mSource.SetRotation(0.0);
}
