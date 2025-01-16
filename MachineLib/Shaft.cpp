/**
 * @file Shaft.cpp
 * @author Josh Thomas
 */
#include "pch.h"
#include "Shaft.h"



/// The color to draw the shaft
const wxColour ShaftColor = wxColour(220, 220, 220);

/// The line color to draw on the shaft
const wxColour ShaftLineColor = wxColour(100, 100, 100);

/// The width to draw the shaft lines
const int ShaftLineWidth = 1;

/// The number of lines to draw on the shaft
const int ShaftNumLines = 4;

Shaft::Shaft() {
 mShaft.SetColour(ShaftColor);
 mShaft.SetLines(ShaftLineColor, ShaftLineWidth, ShaftNumLines);
}

/**
 * Draws the shaft
 * @param graphics
 */
void Shaft::Draw(std::shared_ptr<wxGraphicsContext> graphics) {
 wxLogDebug("Drawing Shaft at (%d, %d)", GetLocation().x, GetLocation().y);
 mShaft.Draw(graphics, GetLocation().x, GetLocation().y, mRotation);
}

void Shaft::SetRotation(double rotation) {
 mRotation = rotation;
 mSource.SetRotation(rotation);
}
