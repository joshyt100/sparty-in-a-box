/**
*@file MachineDrawable.h
 *@author Joshua Thomas
 **/

#ifndef CANADIANEXPERIENCE_MACHINEDRAWABLE_H
#define CANADIANEXPERIENCE_MACHINEDRAWABLE_H

#include "Drawable.h"
#include <machine-api.h>
#include "Timeline.h"

/**
 * Adapter class that makes IMachineSystem work as a Drawable
 */
class MachineDrawable : public Drawable {
private:
    /// The machine system we are adapting
    std::shared_ptr<IMachineSystem> mMachine;

    /// The machine's starting time in frames
    int mStartFrame = 0;

    /// The machine's ending time in frames
    int mEndFrame = -1;  // -1 indicates no end frame set

    /// The frame rate for the machine animation
    double mFrameRate = 30.0;

    /// Timeline pointer for animation
    Timeline* mTimeline = nullptr;

public:
    MachineDrawable(const std::wstring& name, std::shared_ptr<IMachineSystem> machine);

    void SetTimeline(Timeline* timeline) override;

    void UpdateMachine();

    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;

    bool HitTest(wxPoint pos) override;

    void SetMachineNumber(int machine);

    int GetMachineNumber() const;

    void SetMachineFrameRate(double frameRate);

    void SetStartFrame(int frame);

    int GetStartFrame() const;

    void SetEndFrame(int frame);

    int GetEndFrame() const;

    wxXmlNode* Save(wxXmlNode* node);

    void Load(wxXmlNode* node);
};

#endif //CANADIANEXPERIENCE_MACHINEDRAWABLE_H
