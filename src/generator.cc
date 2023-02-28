#include <generator.hh>

generator::generator() {
  fGeneralParticleSource = new G4GeneralParticleSource();

  G4SingleParticleSource *sps = fGeneralParticleSource->GetCurrentSource();
  G4ParticleDefinition *particle = G4ParticleTable::GetParticleTable()->FindParticle("e-");

  sps->SetParticleDefinition(particle);
  sps->SetNumberOfParticles(10000);

  // Configure the position distribution
  sps->GetPosDist()->SetPosDisType("Point"); // Point, Beam, Plane, Surface, Volume
  sps->GetPosDist()->SetCentreCoords(G4ThreeVector(0., 0., 0.));
  sps->GetPosDist()->ConfineSourceToVolume("NULL");

  // Configure the angular distribution
  sps->GetAngDist()->SetAngDistType("iso"); // Isotropic, Cosine-law, Beam, User-defined
  sps->GetAngDist()->SetMinTheta(0. * rad);
  sps->GetAngDist()->SetMaxTheta(TMath::Pi() * rad);
  sps->GetAngDist()->SetMinPhi(0 * rad);
  sps->GetAngDist()->SetMaxPhi(TMath::Pi() * 2. * rad);

  // Configure the energy spectrum
  sps->GetEneDist()->SetEnergyDisType("Mono"); // Mono, Lin, Pow, Exp, Gaus, Brem, BBody, Cdg (cosmic diffuse gamma), User, Arb, Epn (energy per nucleon)
  sps->GetEneDist()->SetMonoEnergy(100 * MeV);
}

generator::~generator() {
  delete fGeneralParticleSource;
}

void generator::GeneratePrimaries(G4Event *anEvent) {
  fGeneralParticleSource->GeneratePrimaryVertex(anEvent);
}
