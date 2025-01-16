/**
 * @file MachineSystem.cpp
 * @brief Implementation of the MachineSystem class.
 *
 * This class represents the system that manages different machine types and their animations.
 * It provides methods to set location, draw the machine, handle frame-based animations,
 * and manage the machine's state.
 *
 * @author Josh Thomas
 */

#include "pch.h"
#include "MachineCFactory.h"
#include "MachineFactory2.h"
#include "MachineSystem.h"
#include "Machine.h"

/**
 * Constructor for the MachineSystem class.
 * Initializes the system and sets the default machine to Machine 1.
 *
 * @param resourcesDir The directory containing resources for the machine.
 */
MachineSystem::MachineSystem(std::wstring resourcesDir) : mResourcesDir(resourcesDir)
{
    ChooseMachine(1);
}

/**
 * Sets the location of the machine in the view.
 *
 * @param location The x,y coordinates of the machine's location.
 */
void MachineSystem::SetLocation(wxPoint location)
{
    mLocation = location;
}

/**
 * Retrieves the current location of the machine.
 *
 * @return The current x,y coordinates of the machine's location.
 */
wxPoint MachineSystem::GetLocation()
{
    return mLocation;
}

/**
 * Draws the machine at the specified location using the given graphics context.
 *
 * @param graphics The graphics context used for rendering the machine.
 */
void MachineSystem::DrawMachine(std::shared_ptr<wxGraphicsContext> graphics)
{
    // Translate to the machine's location
    graphics->PushState();
    graphics->Translate(mLocation.x, mLocation.y);

    // Delegate drawing to the current machine
    if (mMachine)
    {
        mMachine->Draw(graphics);
    }

    graphics->PopState();
}

/**
 * Sets the current frame for the machine's animation.
 * This updates the machine's state based on the specified frame.
 *
 * @param frame The frame number to set.
 */
void MachineSystem::SetMachineFrame(int frame)
{
    if (frame < mFrame)
    {
        mFrame = 0;
        Reset();
    }
    std::cout << "set machine frame" << std::endl;
    while (mFrame <= frame)
    {
        mFrame++;
        mTime = mFrame / mFrameRate;
        mMachine->Advance(1.0 / mFrameRate);
        mMachine->SetTime(mTime);
    }
}

/**
 * Sets the frame rate for the machine's animation.
 *
 * @param rate The frame rate in frames per second.
 */
void MachineSystem::SetFrameRate(double rate)
{
    mFrameRate = rate;
}

/**
 * Chooses the machine to use based on the specified machine number.
 *
 * @param machine The machine number to select.
 */
void MachineSystem::ChooseMachine(int machine)
{
    mMachineNumber = machine; // Store the machine number

    if (machine == 1)
    {
        // Use MachineCFactory (as Machine1Factory) to create Machine 1
        MachineCFactory factory(mResourcesDir);
        mMachine = factory.Create();
    }
    else if (machine == 2)
    {
        // Use MachineFactory2 to create Machine 2
        MachineFactory2 factory(mResourcesDir);
        mMachine = factory.Create();
    }
    else
    {
        // Handle additional cases if needed
        mMachine = nullptr;
    }
}

/**
 * Retrieves the current machine number.
 *
 * @return The number of the currently selected machine.
 */
int MachineSystem::GetMachineNumber()
{
    return mMachineNumber;
}

/**
 * Retrieves the current animation time for the machine.
 *
 * @return The current time in seconds.
 */
double MachineSystem::GetMachineTime()
{
    return mTime;
}

/**
 * Sets a flag in the machine system. Currently unused.
 *
 * @param flag The flag value to set.
 */
void MachineSystem::SetFlag(int flag)
{
}

/**
 * Resets the machine to its initial state.
 * Resets the time and frame counters, and clears the machine's state.
 */
void MachineSystem::Reset()
{
    mTime = 0;
    mFrame = 0;
    if (mMachine != nullptr)
    {
        mMachine->Reset();
    }
}
