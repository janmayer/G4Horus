#include "Hit.hh"
#include <stdexcept>
#include <type_traits>

namespace SOCO {

static_assert(std::is_trivial<Hit>::value, "SOCO::Hit must be trivial (see "
                                           "http://en.cppreference.com/w/cpp/"
                                           "concept/TrivialType");

void Hit::write(std::ostream& out) const
{
    out.write(reinterpret_cast<const char*>(&id), sizeof(id));
    out.write(reinterpret_cast<const char*>(&timestamp), sizeof(timestamp));
    out.write(reinterpret_cast<const char*>(&adc), sizeof(adc));

    if (out.bad()) {
        throw std::runtime_error("Hit::write: failed to write hit!");
    }
}

Hit::Hit(const uint16_t id_, const uint16_t adc_, const uint64_t timestamp_)
    : timestamp{timestamp_}
    , id{id_}
    , adc{adc_}
{
}

} // namespace SOCO
