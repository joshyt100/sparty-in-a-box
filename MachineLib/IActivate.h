/**
 * @file IActivate.h
 * @author Josh Thomas
 *
 *
 */
 
#ifndef CANADIANEXPERIENCE_IACTIVATE_H
#define CANADIANEXPERIENCE_IACTIVATE_H

/**
 * Interface for components that respond to the key drop.
 */
class IActivate {
public:
    /// Virtual destructor
    virtual ~IActivate() = default;

    /**
     * Called when the key drops into the cam's hole.
     */
    virtual void OnKeyDrop() = 0;
};

#endif // CANADIANEXPERIENCE_IACTIVATE_H
