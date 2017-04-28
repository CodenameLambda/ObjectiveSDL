#ifndef OBJSDL_VERSION_HH
#define OBJSDL_VERSION_HH

#include <array>
#include <vector>


namespace SDL {
    namespace _implementation {
        enum VersionType {
            alpha,
            beta,
            rc,
            release
        };
    }

    using VersionType = _implementation::VersionType;


    template <size_t version_elements=3>
    class Version : public std::array<size_t, version_elements> {
        public:
        VersionType type;

        template <typename... V>
        Version(V... args, const VersionType type)
        : std::array<size_t, version_elements>(args...), type(type) {
        }

        template <typename C>
        void __version_init(C v, const VersionType type) {
            auto iterator = v.begin();
            for (auto& i : *this) {
                i = *iterator;
                ++ iterator;
            }
            this->type = type;
        }

        Version(std::initializer_list<size_t> v, const VersionType type) {
            this->__version_init(v, type);
        }

        Version(const std::vector<size_t> v, const VersionType type) {
            this->__version_init(v, type);
        }
    };

    template <size_t ve>
    bool operator<(const Version<ve> a, const Version<ve> b) {
        for (size_t i = 0; i < a.size(); ++i)
            if (a[i] > b[i])
                return false;
            else if (a[i] < b[i])
                return true;
        return false;
    }

    template <size_t ve>
    bool operator<=(const Version<ve> a, const Version<ve> b) {
        return a < b || a == b;
    }

    template <size_t ve>
    bool operator==(const Version<ve> a, const Version<ve> b) {
        for (size_t i = 0; i < a.size(); ++i)
            if (a[i] != b[i])
                return false;
        return true;
    }

    template <size_t ve>
    bool operator!=(const Version<ve> a, const Version<ve> b) {
        return !(a == b);
    }

    template <size_t ve>
    bool operator>=(const Version<ve> a, const Version<ve> b) {
        return ! (a < b);
    }

    template <size_t ve>
    bool operator>(const Version<ve> a, const Version<ve> b) {
        return ! (a < b) && ! (a == b);
    }

    extern const Version<> objective_sdl_version;
    extern const Version<> sdl_linked_version;
    extern const Version<> sdl_compiled_version;
}


#endif
