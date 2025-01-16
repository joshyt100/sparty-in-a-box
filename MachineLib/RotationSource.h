/**
 *@file RotationSource.h
 *@author Joshua Thomas
 **/
#ifndef CANADIANEXPERIENCE_ROTATIONSOURCE_H
#define CANADIANEXPERIENCE_ROTATIONSOURCE_H

#include <vector>
#include <memory>

class RotationSink;

/**
 * RotationSource is responsible for providing rotation data
 * to connected sinks.
 */
class RotationSource {
public:
    /// Constructor
    RotationSource() = default;
    /**
     * Copy constructor
     */
    RotationSource(const RotationSource &) = delete;
    /**
     *
     */
    void operator=(const RotationSource &) = delete;
    /**
     * Sets the rotation
     * @param rotation
     */
    void SetRotation(double rotation);
    /**
     * Gets the Rotation
     * @return
     */
    double GetRotation() const { return mRotation; }
    /**
     * Adds Rotation Sink
     * @param sink
     */
    void AddSink(std::shared_ptr<RotationSink> sink);

    /// Propagate the rotation to all sinks
    void PropagateRotation();

private:
    double mRotation = 0.0; ///< Current rotation in turns
    std::vector<std::shared_ptr<RotationSink>> mSinks; ///< Sinks connected to this source
};

#endif // CANADIANEXPERIENCE_ROTATIONSOURCE_H
