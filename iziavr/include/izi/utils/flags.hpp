#pragma once

#include <izi/utils/bitmask.hpp>

namespace izi {
namespace utils {

struct Flags 
{
    template<uint8_t f>
    void set_flag() { 
        _flags |= utils::bitmask<f>::mask; 
    }

    template<uint8_t f>
    bool get_flag() const {
        return _flags & utils::bitmask<f>::mask;
    }

private:
    uint8_t _flags;
};

} // namepsace utils
} // namsepace izi