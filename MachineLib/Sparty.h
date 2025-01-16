/**
* @file Sparty.h
 * @author Josh Thomas
 */

#ifndef CANADIANEXPERIENCE_SPARTY_H
#define CANADIANEXPERIENCE_SPARTY_H

#include "Polygon.h"
#include "Component.h"
#include <string>

#include "IActivate.h"

/**
 * Sparty class that represents Sparty with a spring.
 */
class Sparty : public Component, public IActivate
{
public:
    /**
     * Constructor for Sparty
     * @param imagePath Path to Sparty's image
     * @param size Size to draw Sparty (width and height)
     * @param extendedLength Length of the spring when fully extended
     * @param springWidth Width of the spring
     * @param numLinks Number of links (loops) in the spring
     */
    Sparty(const std::wstring& imagePath, int size, double extendedLength, double springWidth, int numLinks);

    /**
     * Draw Sparty and the spring
     * @param graphics Graphics context to draw on
     */
    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;

    /**
     * Update the animation
     * @param elapsed Time elapsed since the last update
     */
    void Update(double elapsed) override;

    /**
     * Reset Sparty to the initial compressed state
     */
    void Reset() override;

    /**
     * triggers sparty decompress
     */
    void OnKeyDrop() override
 {
     mDecompressing = !mDecompressing
     ;}

private:
    cse335::Polygon mSparty; ///< Polygon for Sparty's image
    double mCompressedLength; ///< Length of the spring when fully compressed
    double mSpringWidth; ///< Width of the spring
    int mNumLinks; ///< Number of links (loops) in the spring
 bool mHasDecompressed = false; ///< Indicates if Sparty has fully decompressed at least once.

    double mCurrentLength; ///< Current length of the spring
    double mUncompressedLength; ///< Length of the spring when fully decompressed
    double mAnimationTime; ///< Total time for decompression animation
    double mElapsedTime; ///< Elapsed time during animation
    bool mDecompressing; ///< Flag to indicate if Sparty is decompressing
 double mAmplitudeX = 20.0; ///< Initial amplitude for horizontal oscillation
 double mAmplitudeY = 10.0; ///< Initial amplitude for vertical oscillation
 double mDampingFactor = 0.95; ///< Damping factor to reduce amplitude per update
 double mOscillationFrequencyX = 4.0; ///< Frequency of horizontal oscillation (Hz)
 double mOscillationFrequencyY = 3.0; ///< Frequency of vertical oscillation (Hz)
 double mElapsedOscillationTime = 0.0; ///< Time elapsed for oscillation
 double mOscillationOffsetX = 0.0; ///< Current horizontal oscillation offset
 double mOscillationOffsetY = 0.0; ///< Current vertical oscillation offset


    /**
     * Draws the spring
     * @param graphics
     * @param x
     * @param y
     * @param length
     * @param width
     * @param numLinks
     */
    void DrawSpring(std::shared_ptr<wxGraphicsContext> graphics, int x, int y, double length, double width,
                    int numLinks);
};

#endif // CANADIANEXPERIENCE_SPARTY_H
