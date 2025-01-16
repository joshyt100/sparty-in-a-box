/**
 *@file ThorHammerFactory.cpp
 *@author Joshua Thomas
 *@brief Factory for thors hammer
 **/

#include "pch.h"
#include "ThorHammerFactory.h"
#include "Actor.h"
#include "PolyDrawable.h"

/**
 *
 * Factory method to create Thor's hammer, Mjölnir.
 * @return Pointer to an Actor object representing the weapon.
 */
std::shared_ptr<Actor> ThorHammerFactory::Create()
{
    // Create the Actor for the weapon
    auto actor = std::make_shared<Actor>(L"Mjölnir");

    // Create the hammer head
    auto hammerHead = std::make_shared<PolyDrawable>(L"Hammer Head");
    hammerHead->SetColor(wxColour(169, 169, 169)); // Dark gray color for the metallic head
    hammerHead->SetPosition(wxPoint(0, 0)); // Starting position
    hammerHead->AddPoint(wxPoint(-30, -20)); // Top-left of the head
    hammerHead->AddPoint(wxPoint(30, -20));  // Top-right of the head
    hammerHead->AddPoint(wxPoint(30, 20));   // Bottom-right of the head
    hammerHead->AddPoint(wxPoint(-30, 20));  // Bottom-left of the head
    actor->SetRoot(hammerHead);

    // Create the handle
    auto handle = std::make_shared<PolyDrawable>(L"Handle");
    handle->SetColor(wxColour(139, 69, 19)); // Brown color for the wooden handle
    handle->SetPosition(wxPoint(0, 20)); // Position at the bottom center of the head
    handle->AddPoint(wxPoint(-5, 0));    // Top-left of the handle
    handle->AddPoint(wxPoint(5, 0));     // Top-right of the handle
    handle->AddPoint(wxPoint(5, 60));    // Bottom-right of the handle
    handle->AddPoint(wxPoint(-5, 60));   // Bottom-left of the handle
    hammerHead->AddChild(handle);        // Attach the handle to the head

    // Add drawables to the actor in the correct drawing order
    actor->AddDrawable(hammerHead);
    actor->AddDrawable(handle);

    return actor;
}
