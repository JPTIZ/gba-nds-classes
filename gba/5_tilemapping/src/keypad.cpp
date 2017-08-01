#include "keypad.h"

#include <array>
#include <bitset>
#include <experimental/array>

using gba::keypad::Keypad;

static auto key_time = std::array<int, 10>{};
static auto keypad_keys = std::experimental::make_array(
        Keypad::RIGHT,
        Keypad::START,
        Keypad::SELECT,
        Keypad::B,
        Keypad::R,
        Keypad::DOWN,
        Keypad::A,
        Keypad::UP,
        Keypad::LEFT,
        Keypad::L);

namespace gba {

void keypad::update_input() {
    for (auto& key: keypad_keys) {
        auto& time = key_time[key];
        if (time < 0) {
            time = 0;
        }
        if (pressed(key)) {
            ++time;
            if (time > 400) {
                time = 400;
            }
        } else {
            time = -1;
        }
    }
}

bool gba::keypad::triggered(const Keypad& key) {
    auto& time = key_time[key];
    return time == 1;
}

bool gba::keypad::released(const Keypad& key) {
    return key_time[key] < 0;
}

bool gba::keypad::down(const Keypad& key) {
    return key_time[key] > 0;
}

}
