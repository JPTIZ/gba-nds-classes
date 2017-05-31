#ifndef GBA_IO_H
#define GBA_IO_H

#include <cstdint>

namespace gba::io {

inline volatile auto register_at(unsigned address) {
  return (std::uint16_t*)address;
}

}

#endif
