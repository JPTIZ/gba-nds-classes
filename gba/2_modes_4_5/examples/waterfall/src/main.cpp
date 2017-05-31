enum class LCDControl {
    MODE0 = 0b000,
    MODE1 = 0b001,
    MODE2 = 0b010,
    MODE3 = 0b011,
    MODE4 = 0b100,
    MODE5 = 0b101,
    MODE6 = 0b110,
    MODE7 = 0b111,
    BG2 = 1 << 0xA,
};

constexpr LCDControl operator|(LCDControl one, LCDControl other) {
    return static_cast<LCDControl>(static_cast<unsigned>(one) | static_cast<unsigned>(other));
}

int main() {
    auto& lcd_control = *reinterpret_cast<LCDControl*>(0x4000000);
    lcd_control = LCDControl::MODE4 | LCDControl::BG2;
}
