#include <SDL.h>


namespace SDL {
    class HapticDevice {
        SDL_Haptic* device;

        public:
        HapticDevice(SDL_Haptic*);

        static HapticDevice open(size_t index);  // TODO
        static HapticDevice open_from_joystick();  // TODO (Joystick&)

    };

    class HapticEffect {
        SDL_HapticEffect effect;

        HapticEffect(SDL_HapticEffect);
    };

    class HapticDirection {
        SDL_HapticDirection direction;

        HapticDirection(SDL_HapticDirection);
    };

    namespace haptic_effects {
    }
}
