#ifndef G4HORUS_CADHELPER_HH
#define G4HORUS_CADHELPER_HH

inline std::string GetCadFile(const std::string& file)
{
    const char* val = std::getenv("G4HORUS_CAD_DIR");
    if (val == nullptr) {
        return std::string("../cad/") + file;
    } else {
        return std::string(val) + "/" + file;
    }
}

#endif //G4HORUS_CADHELPER_HH
