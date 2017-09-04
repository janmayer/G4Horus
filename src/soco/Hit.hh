#pragma once

#include <cassert>
#include <cstdint>
#include <ostream>
#include <vector>

namespace SOCO {

class Hit {
  public:
    uint64_t timestamp;
    uint16_t id;
    uint16_t adc;

  public:
    Hit() = default;

    Hit(const uint16_t id_, const uint16_t adc_, const uint64_t timestamp_);

    inline bool operator==(const Hit& rhs) const
    {
        return (id == rhs.id && adc == rhs.adc && timestamp == rhs.timestamp);
    }

    inline bool operator<(const Hit& rhs) const { return (timestamp < rhs.timestamp); }

    void write(std::ostream& out) const;
};

} // namespace SOCO
