#include <actioninit.hh>

actioninit::actioninit() : G4VUserActionInitialization() {}

actioninit::~actioninit() {}

void actioninit::BuildForMaster() const {
}

void actioninit::Build() const {
  SetUserAction(new generator());
}
