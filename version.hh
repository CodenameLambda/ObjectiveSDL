#ifndef OBJSDL_VERSION_HH
#define OBJSDL_VERSION_HH

#include <array>
#include <vector>


namespace SDL {
    enum class VersionType {
        alpha,
        beta,
        rc,
        release
    };

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

    template <size_t ve>
    std::string to_string(const VersionType vt) {
        switch (vt) {
            case VersionType::alpha:
                return "alpha";
            case VersionType::beta:
                return "beta";
            case VersionType::rc:
                return "RC";
            case VersionType::release:
                return "release";
        }
    }

    template <size_t ve>
    std::string to_string(const Version<ve> v, bool include_release=false) {
        std::string out = "";
        bool first = true;
        for (const auto& i : v) {
            out += std::to_string(v);
            if (first)
                first = false;
            else
                out += '.';
        }
        if (!include_release && v.type == VersionType::release)
            return out;
        else
            return out + " " + to_string(v.type);
    }
}

#endif
