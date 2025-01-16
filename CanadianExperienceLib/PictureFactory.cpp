/**
 * @file PictureFactory.cpp
 *
 * @author Joshua Thomas
 *
 */

#include "pch.h"
#include "PictureFactory.h"
#include "Picture.h"
#include "HaroldFactory.h"
#include "SpartyFactory.h"
#include "Actor.h"
#include "ThorHammerFactory.h"
#include "ImageDrawable.h"
#include "MachineDrawable.h"
#include <machine-api.h>


/// Directory within resources that contains the images.
const std::wstring ImagesDirectory = L"/images";


/**
 * Factory method to create a new picture.
 * @param resourcesDir Directory that contains the resources for this application
 * @return The created picture
 */
std::shared_ptr<Picture> PictureFactory::Create(std::wstring resourcesDir)
{
    auto imagesDir = resourcesDir + ImagesDirectory;

    auto picture = std::make_shared<Picture>();

    // Create the background and add it
    auto background = std::make_shared<Actor>(L"Background");
    background->SetClickable(false);
    background->SetPosition(wxPoint(0, 0));
    auto backgroundI =
            std::make_shared<ImageDrawable>(L"Background", imagesDir + L"/Background2.png");
    background->AddDrawable(backgroundI);
    background->SetRoot(backgroundI);
    picture->AddActor(background);

    // Create and add Harold
    HaroldFactory haroldFactory;
    auto harold = haroldFactory.Create(imagesDir);

    // This is where Harold will start out.
    harold->SetPosition(wxPoint(150, 600));
    picture->AddActor(harold);

    // Create and add Sparty
    SpartyFactory spartyFactory;
    auto sparty = spartyFactory.Create(imagesDir);


    sparty->SetPosition(wxPoint(650, 620));
    picture->AddActor(sparty);

    // Create the machine
    MachineSystemFactory machineFactory(resourcesDir);
    auto machineSystem = machineFactory.CreateMachineSystem();
    machineSystem->ChooseMachine(1); // Choose the machine number

    auto timeline = picture->GetTimeline();
    timeline->SetFrameRate(30);
    // Create MachineDrawable
    auto machineDrawable = std::make_shared<MachineDrawable>(L"Machine", machineSystem);
    machineDrawable->SetPosition(wxPoint(175, 300)); // Set its position
    machineDrawable->SetMachineFrameRate(30);
    machineDrawable->SetStartFrame(0);
    machineDrawable->SetEndFrame(150);

    // Create an actor for the machine
    auto machineActor = std::make_shared<Actor>(L"Machine");
    machineActor->SetPosition(wxPoint(175, 300)); // Set the actor's base position
    machineActor->AddDrawable(machineDrawable);   // Add the machine drawable
    machineActor->SetRoot(machineDrawable);       // Set the root drawable
    picture->AddActor(machineActor);              // Add the actor to the picture

    // Create Machine 2
    MachineSystemFactory machineFactory2(resourcesDir);
    auto machineSystem2 = machineFactory2.CreateMachineSystem();
    machineSystem2->ChooseMachine(2);

    auto machineDrawable2 = std::make_shared<MachineDrawable>(L"Machine2", machineSystem2);
    machineDrawable2->SetPosition(wxPoint(500, 300));  // Different position than Machine 1
    machineDrawable2->SetMachineFrameRate(30);
    machineDrawable2->SetStartFrame(200);  // Start after Machine 1 ends
    machineDrawable2->SetEndFrame(600);



    auto machineActor2 = std::make_shared<Actor>(L"Machine2");
    machineActor2->SetPosition(wxPoint(500, 300));
    machineActor2->AddDrawable(machineDrawable2);
    machineActor2->SetRoot(machineDrawable2);
    picture->AddActor(machineActor2);


    return picture;
}


