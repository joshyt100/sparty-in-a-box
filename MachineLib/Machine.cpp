/**
 * @file Machine.cpp
 * @author Josh Thomas
 */

#include "pch.h"
#include "Machine.h"

#include "Box.h"

/**
 * Add a component to the machine
 * @param component The component to add
 */
void Machine::AddComponent(std::shared_ptr<Component> component)
{
    mComponents.push_back(component);
}

/**
 * Set the location of the machine on the screen
 * @param location The location to set
 */
void Machine::SetLocation(wxPoint location)
{
    mLocation = location;
    // Update each component's relative location
    for (auto& component : mComponents)
    {
        wxPoint relativeLocation = component->GetLocation();
        component->SetLocation({mLocation.x + relativeLocation.x, mLocation.y + relativeLocation.y});
    }
}

/**
 * Draw all components in the machine
 * @param graphics Graphics context to draw on
 */
void Machine::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    for (auto& component : mComponents)
    {
        component->Draw(graphics);
    }
    // Draw foregrounds separately after other components
    for (const auto& component : mComponents)
    {
        component->DrawForeground(graphics);
    }
}


void Machine::SetTime(double time)
{
    std::cout << "set time is being called";
    for (auto& component : mComponents)
    {
        component->SetTime(time);
    }
}

void Machine::Advance(double elapsed)
{
    std::cout<<"advance is being called" << std::endl;
    for (auto& component : mComponents)
    {
        component->Update(elapsed);
    }
}

void Machine::Reset()
{
    for (auto& component : mComponents)
    {
        component->Reset();
    }
}
