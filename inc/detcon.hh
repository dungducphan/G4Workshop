#pragma once

#include <G4VUserDetectorConstruction.hh>
#include <globals.hh>
#include <G4NistManager.hh>
#include <G4Box.hh>
#include <G4LogicalVolume.hh>
#include <G4PVPlacement.hh>
#include <G4SystemOfUnits.hh>

#include <TMath.h>

class G4VPhysicalVolume;
class G4LogicalVolume;

class detcon : public G4VUserDetectorConstruction {
  public:
    detcon();
    virtual ~detcon();

    virtual G4VPhysicalVolume* Construct();
};
