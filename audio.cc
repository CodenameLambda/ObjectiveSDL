#include "audio.hh"


namespace SDL {
    Audio::Audio(
        const SDL_AudioSpec audio_spec,
        Uint8* audio_buffer,
        const Uint32 audio_length,
        std::function<void(Uint8*)> free,
        unsigned char volume
    ) {
        this->audio_spec = audio_spec;
        this->audio_buffer = audio_buffer;
        this->audio_length = audio_length;
        this->free = free;
        this->volume = volume;
        // TODO: Callback
    }

    AudioInstance Audio::play(const bool start_automatically) {
        return AudioInstance(*this, 1, start_automatically);
    }

    AudioInstance Audio::loop(const size_t times, const bool start_automatically) {
        return AudioInstance(*this, times, start_automatically);
    }

    AudioInstance Audio::loop(const bool start_automatically) {
        return AudioInstance(*this, 0, start_automatically);
    }

    Audio Audio::load_wav(const std::string file) {
        SDL_AudioSpec audio_spec;
        Uint8* audio_buffer;
        Uint32 audio_length;
        SDL_LoadWAV(file.c_str(), &audio_spec, &audio_buffer, &audio_length);
        return Audio(audio_spec, audio_buffer, audio_length, SDL_FreeWAV);
    }

    Audio::~Audio() {
        this->free(this->audio_buffer);
    }

    void AudioInstance::new_device() {
        this->device = SDL_OpenAudioDevice(
            NULL,
            0,
            &this->source.audio_spec,
            NULL,
            SDL_AUDIO_ALLOW_FORMAT_CHANGE
        );
    }

    AudioInstance::AudioInstance(Audio& audio, const size_t loop, const bool start)
    : source(audio) {
        this->loop = loop;
        this->new_device();
        if (start)
            this->play();
        else
            this->pause();
    }

    void AudioInstance::pause() {
        SDL_PauseAudioDevice(this->device, 1);
    }

    void AudioInstance::stop() {
        SDL_CloseAudioDevice(this->device);
        this->new_device();
    }

    void AudioInstance::play() {
        SDL_PauseAudioDevice(this->device, 0);
    }
}
