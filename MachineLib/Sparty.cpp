/**
 * @file Sparty.cpp
 * @author Josh
 */

#include "pch.h"
#include "Sparty.h"

/// Spring wire size in pixels
const double SpringWireSize = 2;

/// Color to draw the spring
const wxColour SpringColor = wxColour(220, 220, 220);

/// Sparty popup time in seconds
const double SpartyPopupTime = 0.25;

Sparty::Sparty(const std::wstring& imagePath, int size, double extendedLength, double springWidth, int numLinks)
    : mUncompressedLength(extendedLength), mSpringWidth(springWidth), mNumLinks(numLinks), mAnimationTime(SpartyPopupTime)
{
    // Configure the polygon for Sparty's image
    mSparty.Rectangle(-size / 2, extendedLength / 2, size, size);
    mSparty.SetImage(imagePath);

    // Initialize animation variables
    mCompressedLength = extendedLength * 0.2;
    mCurrentLength = mCompressedLength;
    mElapsedTime = 0;
    mDecompressing = false; // Initially not decompressing
    mHasDecompressed = false;
}

void Sparty::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    // Draw the spring
    DrawSpring(graphics, GetLocation().x, GetLocation().y, mCurrentLength, mSpringWidth, mNumLinks);

    // Draw Sparty at the top of the spring with oscillatory offsets
    mSparty.DrawPolygon(
        graphics,
        GetLocation().x + mOscillationOffsetX,
        GetLocation().y - mCurrentLength - 125 + mOscillationOffsetY
    );
}

void Sparty::DrawSpring(std::shared_ptr<wxGraphicsContext> graphics, int x, int y, double length, double width, int numLinks)
{
    auto path = graphics->CreatePath();

    double y1 = y;
    double linkLength = length / numLinks;

    // Left and right X values
    double xR = x + width / 2;
    double xL = x - width / 2;

    path.MoveToPoint(x, y1);

    for (int i = 0; i < numLinks; i++)
    {
        auto y2 = y1 - linkLength;
        auto y3 = y2 - linkLength / 2;

        path.AddCurveToPoint(xR, y1, xR, y3, x, y3);
        path.AddCurveToPoint(xL, y3, xL, y2, x, y2);

        y1 = y2;
    }
    graphics->SetPen(wxPen(SpringColor, SpringWireSize));
    graphics->StrokePath(path);
}

void Sparty::Update(double elapsed) {
    if (mDecompressing) {
        // Sparty is decompressing
        mElapsedTime += elapsed;
        double t = mElapsedTime / mAnimationTime;
        if (t > 1.0) {
            t = 1.0;
            mDecompressing = false;
            mHasDecompressed = true;  // Mark that Sparty has fully decompressed once
            // Reset oscillation parameters at this point if needed
            mElapsedOscillationTime = 0.0;
            mAmplitudeX = 20.0;
            mAmplitudeY = 10.0;
        }

        mCurrentLength = mCompressedLength + t * (mUncompressedLength - mCompressedLength);
    } else {
        // Only oscillate if Sparty has ever fully decompressed
        if (mHasDecompressed) {
            mElapsedOscillationTime += elapsed;

            // Calculate offsets using damped sine wave
            mOscillationOffsetX = mAmplitudeX * sin(2 * M_PI * mOscillationFrequencyX * mElapsedOscillationTime);
            mOscillationOffsetY = mAmplitudeY * sin(2 * M_PI * mOscillationFrequencyY * mElapsedOscillationTime);

            // Apply damping
            mAmplitudeX *= mDampingFactor;
            mAmplitudeY *= mDampingFactor;

            // Stop oscillation when amplitude is negligible
            if (mAmplitudeX < 0.1 && mAmplitudeY < 0.1) {
                mOscillationOffsetX = 0.0;
                mOscillationOffsetY = 0.0;
            }
        } else {
            // If never decompressed, no oscillation
            mOscillationOffsetX = 0.0;
            mOscillationOffsetY = 0.0;
        }
    }
}

void Sparty::Reset()
{
    mCurrentLength = mCompressedLength;
    mElapsedTime = 0;
    mDecompressing = false;
    // Do not reset mHasDecompressed here if you want Sparty to remain
    // considered decompressed if it happened once.
    // If you do want to reset that state, set mHasDecompressed = false;
}
