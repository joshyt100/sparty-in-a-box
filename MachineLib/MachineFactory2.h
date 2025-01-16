/**
* @file MachineFactory2.h
 * @author Josh Thomas
 */

#ifndef CANADIANEXPERIENCE_MACHINEFACTORY2_H
#define CANADIANEXPERIENCE_MACHINEFACTORY2_H

#include <memory>
#include <string>

class Machine;
class Shape;

/**
 * Factory for creating Machine #2
 */
class MachineFactory2 {
private:
    /// Path to the resources directory
    std::wstring mResourcesDir;

    /// Path to the images directory
    std::wstring mImagesDir;

public:
    MachineFactory2(std::wstring resourcesDir);

    std::shared_ptr<Machine> Create();
};

#endif //CANADIANEXPERIENCE_MACHINEFACTORY2_H