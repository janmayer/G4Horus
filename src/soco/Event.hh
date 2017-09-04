#ifndef SOCO_EVENT_HH
#define SOCO_EVENT_HH

#include <cassert>
#include <cstdint>
#include <limits>
#include <ostream>
#include <vector>

#include "Hit.hh"

namespace SOCO {

constexpr uint64_t SOCO_EVENT_MAGIC = UINT64_C(0x534f434f45564e54);
constexpr uint64_t SOCO_META_MAGIC = UINT64_C(0x4d45544144415441);
constexpr uint64_t SOCO_DATA_MAGIC = UINT64_C(0x00534f434f444154);

struct EventHeader {
    uint64_t magic;
    uint64_t event_count;
};

struct EventMetadataHeader {
    uint64_t magic;
    size_t size;
};

class Event {
  public:
    std::vector<Hit> hits;
    uint16_t trigger_id;
    uint64_t timestamp;

  public:
    Event() noexcept;

    Event(uint16_t trigger, uint64_t ts, std::vector<Hit>&& hits_);

    void clear() noexcept;

    void write(std::ostream& out) const;
};

} // namespace SOCO

#endif // SOCO_EVENT_HH
