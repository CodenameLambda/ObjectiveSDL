#include "touch.hh"
#include <SDL.h>

namespace SDL {
    void record_gesture() {
        SDL_RecordGesture(-1);
    }
}
