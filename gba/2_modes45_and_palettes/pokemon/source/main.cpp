#include "gba_video.h"
#include "mode4.h"

int main() {
    using namespace gba;
    {
        using namespace video;
        set_mode(4);
        enable_bg(2);
    }
    return 0;
}
