# G4Horus

A implementation of the HORUS spectrometer geometry and detectors in Geant4.

![G4Horus Default Geometry](doc/g4horus-default.png)

## Quickstart
1) On poseidon or gaia, create a new folder and do

	git clone https://ares1.ikp.uni-koeln.de/gitlab/jmayer/g4horus.git .
	./G4Horus.sh

The project should compile and open a visual interface with a default view should open.

2) Modify `src/DetectorConstruction.cc` to change the target chamber, detectors, and sensitve volumes. Use `./G4Horus.sh` to check your setup.

3) Run `./G4Batch.s` to run the actual simulation.

4) Use `./efficiency.sh` to automatically extract efficiencys from the simulated data.

