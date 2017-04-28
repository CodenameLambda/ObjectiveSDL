#include "version.hh"
#include <SDL.h>


namespace SDL {
    namespace _implementation {
        namespace version {
            SDL_version get_linked_sdl_version() {
                SDL_version version;
                SDL_GetVersion(&version);
                return version;
            }

            SDL_version get_compiled_sdl_version() {
                SDL_version version;
                SDL_GetVersion(&version);
                return version;
            }

            const SDL_version linked = get_linked_sdl_version();
            const SDL_version compiled = get_compiled_sdl_version();
        }
    }

    const Version<> objective_sdl_version({1, 0, 0}, VersionType::alpha);
    const Version<> sdl_linked_version(
            {
                _implementation::version::linked.major,
                _implementation::version::linked.minor,
                _implementation::version::linked.patch
            },
            VersionType::release
    );
    const Version<> sdl_compiled_version(
            {
                _implementation::version::compiled.major,
                _implementation::version::compiled.minor,
                _implementation::version::compiled.patch
            },
            VersionType::release
    );
}
