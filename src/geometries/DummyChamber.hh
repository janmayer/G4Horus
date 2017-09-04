#pragma once

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
