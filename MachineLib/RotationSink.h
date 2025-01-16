/**
 * @file RotationSink.h
 * @author Josh Thomas
 *
 *
 */
 
#ifndef ROTATIONSINK_H
#define ROTATIONSINK_H

/**
 * RotationSink is an interface that allows objects to receive rotation data.
 */
class RotationSink {
public:
 /// Virtual destructor
 virtual ~RotationSink() = default;

 /// Set the rotation in turns
 /// @param rotation Rotation in turns
 virtual void SetRotation(double rotation) = 0;
};





#endif //ROTATIONSINK_H
