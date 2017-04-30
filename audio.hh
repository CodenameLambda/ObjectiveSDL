#include <SDL.h>
#include <functional>


namespace SDL {
    class AudioInstance;

    class Audio {
        bool paused;
        SDL_AudioSpec audio_spec;
        Uint8* audio_buffer;
        Uint32 audio_length;
        std::function<void(Uint8*)> free;

        public:
        unsigned char volume;

        Audio(
            const SDL_AudioSpec audio_spec,
            Uint8* audio_buffer,
            const Uint32 audio_length,
            std::function<void(Uint8*)> free,
            unsigned char volume=SDL_MIX_MAXVOLUME  // 0 - 128
        );

        AudioInstance play(const bool start_automatically=true);
        AudioInstance loop(const size_t times, const bool start_automatically=true);
        AudioInstance loop(const bool start_automatically=true);

        static Audio load_wav(const std::string file);

        ~Audio();

        friend class AudioInstance;
    };

    class AudioInstance {
        Audio& source;
        size_t loop;
        SDL_AudioDeviceID device;

        void new_device();

        public:
        AudioInstance(Audio&, const size_t loop, const bool start_automatically=true);

        void pause();
        void stop();
        void play();
    };
}
