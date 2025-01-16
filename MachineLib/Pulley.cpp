/**
 *@file Pulley.cpp
 *@author Joshua Thomas
 **/
#include "pch.h"
#include "Pulley.h"

/// Pulley constants for rendering
const wxColour PulleyColor = wxColour(205, 250, 5);
/**
 * const for line color
 */
const wxColour PulleyHubLineColor = wxColour(139, 168, 7);
const wxColour BeltColor = wxColour(0, 0, 0);           ///< Black belt color
/**
 * Pulley hub line width
 */
const int PulleyHubLineWidth = 4;
const double PulleyHubWidth = 4;          ///< Width of the hub on each side
/**
 * Divisor for pulley
 */
const double PulleyHubLineCountDiviser = 6.0;

Pulley::Pulley(double radius) : mRadius(radius) {
    // Configure the left hub
    mHubLeft.SetSize(radius, PulleyHubWidth);
    mHubLeft.SetColour(PulleyColor);
    mHubLeft.SetLines(PulleyHubLineColor, PulleyHubLineWidth, static_cast<int>(radius / PulleyHubLineCountDiviser));

    // Configure the right hub
    mHubRight.SetSize(radius, PulleyHubWidth);
    mHubRight.SetColour(PulleyColor);
    mHubRight.SetLines(PulleyHubLineColor, PulleyHubLineWidth, static_cast<int>(radius / PulleyHubLineCountDiviser));
}

void Pulley::Draw(std::shared_ptr<wxGraphicsContext> graphics) {
    double x = GetLocation().x;
    double y = GetLocation().y;

    // Draw the left hub, slightly to the left
    mHubLeft.Draw(graphics, x - PulleyHubWidth / 2, y, mRotation);

    // Draw the right hub, slightly to the right
    mHubRight.Draw(graphics, x + PulleyHubWidth / 2, y, mRotation);

    // // Draw the belt if connected to another pulley
    // if (mBeltConnectedPulley) {
    //     auto otherLocation = mBeltConnectedPulley->GetLocation();
    //
    //     // Create the belt using a Polygon
    //     cse335::Polygon belt;
    //     belt.SetColor(BeltColor);
    //
    //     // Define the rectangle representing the belt
    //     belt.Rectangle(0,0, 5,125);
    //
    //
    //     // Draw the belt polygon
    //     belt.DrawPolygon(graphics, x, y);
    // }


}

void Pulley::SetRotation(double rotation) {
    mRotation = rotation;
    mSource.SetRotation(rotation);  // Propagate rotation to attached sinks

    // Propagate rotation to the connected pulley via the belt
    if (mBeltConnectedPulley) {
        double speedRatio = mRadius / mBeltConnectedPulley->GetRadius();
        mBeltConnectedPulley->SetRotation(rotation * speedRatio);
    }
}

void Pulley::BeltTo(std::shared_ptr<Pulley> otherPulley) {
    mBeltConnectedPulley = otherPulley;
}
