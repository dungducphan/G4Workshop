#include <detcon.hh>

detcon::detcon() : G4VUserDetectorConstruction() {}

detcon::~detcon() {}

G4VPhysicalVolume *detcon::Construct() {
    G4NistManager *nist = G4NistManager::Instance();
    G4bool checkOverlaps = true;

    // Getting the ${STL_DIR} env variable
    auto stlPath = getenv("STL_DIR");

    // World
    G4double worldSize = 10 * cm;
    G4Material *worldMat = nist->FindOrBuildMaterial("G4_Galactic");
    G4Box *solidWorld = new G4Box("solidWorld", 0.5 * worldSize, 0.5 * worldSize, 0.5 * worldSize);
    G4LogicalVolume *logicWorld = new G4LogicalVolume(solidWorld, worldMat, "logicWorld");
    G4VPhysicalVolume *physWorld = new G4PVPlacement(0, G4ThreeVector(), logicWorld, "physWorld", 0, false, 0,
                                                     checkOverlaps);

    // Test Sphere
    G4LogicalVolume *logic_sphere;
    ImportCADModel(Form("%s/Sphere.stl", stlPath),
                   logic_sphere,
                   "logic_sphere",
                   nist->FindMaterial("G4_Fe"));
    new G4PVPlacement(0,
                      G4ThreeVector(),
                      logic_sphere,
                      "phys_sphere",
                      logicWorld,
                      false,
                      0,
                      checkOverlaps);

    return physWorld;
}

void detcon::ImportCADModel(std::string aSTLFilePath,
                            G4LogicalVolume *logic_CAD,
                            std::string logicVolName,
                            G4Material *material,
                            G4VisAttributes *visualAttr) {
    auto mesh_CAD = CADMesh::TessellatedMesh::FromSTL(aSTLFilePath);
    G4VSolid *solid_CAD = mesh_CAD->GetSolid();
    logic_CAD = new G4LogicalVolume(solid_CAD, material, logicVolName);
    logic_CAD->SetVisAttributes(visualAttr);
}

