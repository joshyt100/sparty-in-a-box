/**
 *@file MachineDrawable.cpp
 *@author Joshua Thomas
 **/
#include "pch.h"

/**
 *@file MachineDrawable.cpp
 *@author Joshua Thomas
 **/

#include "MachineDrawable.h"

/**
 * Constructor for machine drawable
 * @param name
 * @param machine
 */
MachineDrawable::MachineDrawable(const std::wstring& name, std::shared_ptr<IMachineSystem> machine)
    : Drawable(name), mMachine(machine) {}

/**
 * Sets timeline
 * @param timeline
 */
void MachineDrawable::SetTimeline(Timeline* timeline)
{
    mTimeline = timeline;
    Drawable::SetTimeline(timeline);
}

/**
 * Updates machine state
 */
void MachineDrawable::UpdateMachine()
{
    if (mTimeline == nullptr || mMachine == nullptr)
        return;

    int frame = mTimeline->GetCurrentFrame();

    if (frame >= mStartFrame && (mEndFrame == -1 || frame <= mEndFrame))
    {
        mMachine->SetMachineFrame(frame - mStartFrame);
    }
    else if (frame < mStartFrame)
    {
        mMachine->SetMachineFrame(0);
    }
    else if (mEndFrame != -1 && frame > mEndFrame)
    {
        mMachine->SetMachineFrame(mEndFrame - mStartFrame);
    }
}

/**
 * Draws the machine
 * @param graphics
 */
void MachineDrawable::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    if (mMachine == nullptr)
        return;

    UpdateMachine();

    graphics->PushState();

    graphics->Translate(mPlacedPosition.x, mPlacedPosition.y);
    graphics->Scale(0.75, 0.75);

    mMachine->SetLocation(wxPoint(0, 0));
    mMachine->DrawMachine(graphics);

    graphics->PopState();
}

/**
 * Overriden hittest
 * @param pos
 * @return
 */
bool MachineDrawable::HitTest(wxPoint pos)
{
    // Simple hit testing - check if point is near the machine's position
    return false; // Implementation pending
}

/**
 * Sets the machine number
 * @param machine
 */
void MachineDrawable::SetMachineNumber(int machine)
{
    mMachine->ChooseMachine(machine);
}

/**
 * Gets machine number
 * @return
 */
int MachineDrawable::GetMachineNumber() const
{
    return mMachine->GetMachineNumber();
}

/**
 * Sets the machine frame rate
 * @param frameRate
 */
void MachineDrawable::SetMachineFrameRate(double frameRate)
{
    mFrameRate = frameRate;
    mMachine->SetFrameRate(frameRate);
}

/**
 * Sets the start frame
 * @param frame
 */
void MachineDrawable::SetStartFrame(int frame)
{
    mStartFrame = frame;
}

/**
 * Gets the start frame
 * @return mStartFrame
 */
int MachineDrawable::GetStartFrame() const
{
    return mStartFrame;
}

/**
 * sets the end frame
 * @param frame
 */
void MachineDrawable::SetEndFrame(int frame)
{
    mEndFrame = frame;
}

/**
 * Returns end frame
 * @return mEndFrame
 */
int MachineDrawable::GetEndFrame() const
{
    return mEndFrame;
}

/**
 * Saves machine
 * @param node
 * @return
 */
wxXmlNode* MachineDrawable::Save(wxXmlNode* node)
{
    auto itemNode = new wxXmlNode(wxXML_ELEMENT_NODE, L"machine");
    itemNode->AddAttribute(L"machine-number", wxString::Format(wxT("%i"), GetMachineNumber()));
    itemNode->AddAttribute(L"start-frame", wxString::Format(wxT("%i"), mStartFrame));
    itemNode->AddAttribute(L"end-frame", wxString::Format(wxT("%i"), mEndFrame));
    return itemNode;
}

/**
 * Loads machine
 * @param node
 */
void MachineDrawable::Load(wxXmlNode* node)
{
    int machineNumber = wxAtoi(node->GetAttribute(L"machine-number", L"1"));
    mStartFrame = wxAtoi(node->GetAttribute(L"start-frame", L"0"));
    mEndFrame = wxAtoi(node->GetAttribute(L"end-frame", L"-1"));
    SetMachineNumber(machineNumber);
}
