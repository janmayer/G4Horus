#ifndef G4HORUS_DUMMYCHAMBER_H
#define G4HORUS_DUMMYCHAMBER_H

class G4LogicalVolume;

class DummyChamber {
  public:
    explicit DummyChamber(G4LogicalVolume* worldLV);
    ~DummyChamber() = default;
    DummyChamber(const DummyChamber&) = delete;
    DummyChamber(DummyChamber&&) = delete;
    DummyChamber& operator=(const DummyChamber&) = delete;
    DummyChamber& operator=(DummyChamber&&) = delete;
};

#endif //G4HORUS_DUMMYCHAMBER_H
