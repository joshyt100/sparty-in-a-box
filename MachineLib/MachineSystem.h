/**
 * @file MachineSystem.h
 * @author Josh Thomas
 *
 *
 */

#ifndef MACHINESYSTEM_H
#define MACHINESYSTEM_H
#include "IMachineSystem.h"
/**
 * @class Machine
 * @brief forward declaration of machine
 */
class Machine;

/**
 * @class MachineSystem
 * @brief System class for machine
 */
class MachineSystem : public IMachineSystem
{
public:
    MachineSystem( std::wstring resourcesDir );
    void SetLocation(wxPoint location) override;
    wxPoint GetLocation() override;
    void DrawMachine(std::shared_ptr<wxGraphicsContext> graphics) override;
    void SetMachineFrame(int frame) override;
    void SetFrameRate(double rate) override;
    void ChooseMachine(int machine) override;
    int GetMachineNumber() override;
    double GetMachineTime() override;
    void SetFlag(int flag) override;
    void Reset();
private:
    /// position of the machine
    wxPoint mLocation = {0, 0};
    int mMachineNumber = 1;                   ///< Current machine number
    std::shared_ptr<Machine> mMachine = nullptr; ///< The current machine
    std::wstring mResourcesDir;               ///< Resources directory for creating machines
    double mFrameRate = 30.0;     ///< Animation frame rate in frames/second
    double mTime = 0.0;             ///< Current animation time in seconds
    int mFrame = 0;               ///< Current frame number

    /// Reset the machine to initial state

};


#endif //MACHINESYSTEM_H
