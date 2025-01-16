/**
 * @file MachineFactory2.cpp
 * @author Josh Thomas
 */

#include "pch.h"
#include "MachineFactory2.h"

#include "Crank.h"

#include "Box.h"
#include "Cam.h"
#include "Shaft.h"
#include "Machine.h"
#include "Pulley.h"

// Comment out the headers after #include "Machine.h"
#if 0
#include "Box.h"
#include "Sparty.h"
#endif

/// The images directory in resources
const std::wstring ImagesDirectory = L"/images";

/**
 * Constructor
 * @param resourcesDir Path to the resources directory
 */
MachineFactory2::MachineFactory2(std::wstring resourcesDir) :
        mResourcesDir(resourcesDir)
{
    mImagesDir = mResourcesDir + ImagesDirectory;
}

/**
 * Factory method to create machine #1
 * @return A shared pointer to the Machine object
 */


#include "Sparty.h"

std::shared_ptr<Machine> MachineFactory2::Create()
{
 // The machine itself
 auto machine = std::make_shared<Machine>();

 // Create a Box component
 auto box = std::make_shared<Box>(mImagesDir, 250, 240);

 // Add the box to the machine
 machine->AddComponent(box);

 // Create Sparty
 auto sparty = std::make_shared<Sparty>(mImagesDir + L"/cat.png", 212, 260, 80, 15);
 // sparty->SetLocation(wxPoint(0, -150));
 machine->AddComponent(sparty);
 auto crank = std::make_shared<Crank>();
 crank->SetLocation(wxPoint(135,-175));
 crank->SetSpeed(0.5);

 auto shaft = std::make_shared<Shaft>();
 shaft->SetLocation(wxPoint(90,-190));
 crank->GetSource()->AddSink(shaft);
 shaft->SetSize(8,55);
 auto pulley1 = std::make_shared<Pulley>(70);


 pulley1->SetLocation(wxPoint(100, -60));

 auto pulley2 = std::make_shared<Pulley>(40);
 pulley2->SetLocation(wxPoint(100, -190));
 shaft->GetSource()->AddSink(pulley2);
 pulley2->BeltTo(pulley1);
 pulley2->GetSource()->AddSink(pulley1);

 auto shaft2 = std::make_shared<Shaft>();
 shaft2->SetLocation(wxPoint(-100, -60));
 shaft2->SetSize(8, 210);
 pulley1->GetSource()->AddSink(shaft2);

 auto pulley4 = std::make_shared<Pulley>(25);
 pulley4->SetLocation(wxPoint(-100, -60));
 shaft2->GetSource()->AddSink(pulley4);


 auto pulley3 = std::make_shared<Pulley>(70);
 pulley3->SetLocation(wxPoint(-100,-190));
 pulley4->GetSource()->AddSink(pulley3);
 pulley4->BeltTo(pulley3);

 auto cam = std::make_shared<Cam>(mImagesDir);
 auto shaftTopLeft = std::make_shared<Shaft>();
 shaftTopLeft->SetSize(8,60);
 shaftTopLeft->SetLocation(wxPoint(-110,-190));
 cam->SetLocation(wxPoint(-80,-190));
 cam->AddActivationTarget(box);
 cam->AddActivationTarget(sparty);
 pulley3->GetSource()->AddSink(shaftTopLeft);
 shaftTopLeft->GetSource()->AddSink(cam);
 machine->AddComponent(shaftTopLeft);
 machine->AddComponent(cam);






 machine->AddComponent(shaft);
 machine->AddComponent(crank);
 machine->AddComponent(shaft2);
 machine->AddComponent(pulley2);
 machine->AddComponent(pulley1);
 machine->AddComponent(pulley3);
 machine->AddComponent(pulley4);


 return machine;
}
