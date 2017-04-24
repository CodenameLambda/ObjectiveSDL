#include <array>
#include <string>
#include <cmath>


template <size_t dim, typename T=double>
class Vector {
    std::array<T, dim> data;

    public:
    static constexpr size_t dimension = dim;

    Vector(const bool zero_initialized=true) {
        if (zero_initialized)
            this->data = {0};
    }

    Vector(const std::initializer_list<T>& data)
        : Vector(data.begin(), data.end()) {}

    template <typename I, typename J>
    Vector(I begin, const J& end) {
        this->data = {0};
        size_t index = 0;
        while(begin != end) {
            this->data[index] = *begin;
            ++ begin;
            ++ index;
        }
    }

    typename std::array<T, dim>::iterator begin() {
        return this->data.begin();
    }

    typename std::array<T, dim>::const_iterator begin() const {
        return this->data.cbegin();
    }

    typename std::array<T, dim>::const_iterator cbegin() const {
        return this->data.cbegin();
    }

    typename std::array<T, dim>::iterator end() {
        return this->data.end();
    }

    typename std::array<T, dim>::const_iterator end() const {
        return this->data.cend();
    }

    typename std::array<T, dim>::const_iterator cend() const {
        return this->data.cend();
    }

    double length() const {
        double sum = 0;
        for (const auto& i : *this)
            sum += i * i;
        return std::sqrt(sum);
    }

    long double precise_length() const {
        long double sum = 0;
        for (const auto& i : *this)
            sum += i * i;
        return std::sqrt(sum);
    }

    T& operator[](const size_t index) {
        return data[index];
    }

    const T& operator[](const size_t index) const {
        return data[index];
    }

    template <typename U>
    operator Vector<dim, U>() const {
        Vector<dim, U> out(false);
        auto iterator = out.begin();
        for (const T& i : *this) {
            *iterator = i;
            ++ iterator;
        }
        return out;
    }

    decltype(data)& _get_data() {
        return this->data;
    }

    const decltype(data)& _get_data() const {
        return this->data;
    }
};


namespace std {
    template <size_t id, typename T, size_t num>
    T& get(Vector<num, T>& v) {
        return std::get<id>(v._get_data());
    }


    template <size_t id, typename T, size_t num>
    const T& get(const Vector<num, T>& v) {
        return std::get<id>(v._get_data());
    }
}


template <typename T, typename U, size_t dim>
auto operator+(const Vector<dim, T>& a, const Vector<dim, U>& b) {
    Vector<dim, decltype(a[0] + b[0])> out(false);
    auto iterator = out.begin();
    auto other = b.begin();
    for (const auto& i : a) {
        *iterator = i + *other;
        ++ iterator;
        ++ other;
    }
    return out;
}


template <typename T, typename U, size_t dim>
auto operator-(const Vector<dim, T>& a, const Vector<dim, U>& b) {
    Vector<dim, decltype(a[0] - b[0])> out(false);
    auto iterator = out.begin();
    auto other = b.begin();
    for (const auto& i : a) {
        *iterator = i - *other;
        ++ iterator;
        ++ other;
    }
    return out;
}


template <typename T, size_t dim>
auto operator-(const Vector<dim, T>& a) {
    Vector<dim, decltype(-a[0])> out(false);
    auto iterator = out.begin();
    for (const auto& i : a) {
        *iterator = -i;
        ++ iterator;
    }
    return out;
}


template <typename T, size_t dim>
T& x(Vector<dim, T>& v) {
    return std::get<0>(v);
}


template <typename T, size_t dim>
const T& x(const Vector<dim, T>& v) {
    return std::get<0>(v);
}


template <typename T, size_t dim>
T& y(Vector<dim, T>& v) {
    return std::get<1>(v);
}


template <typename T, size_t dim>
const T& y(const Vector<dim, T>& v) {
    return std::get<1>(v);
}


template <typename T, size_t dim>
T& z(Vector<dim, T>& v) {
    return std::get<2>(v);
}


template <typename T, size_t dim>
const T& z(const Vector<dim, T>& v) {
    return std::get<2>(v);
}


template <typename T, size_t dim>
T& w(Vector<dim, T>& v) {
    return std::get<3>(v);
}


template <typename T, size_t dim>
const T& w(const Vector<dim, T>& v) {
    return std::get<3>(v);
}


template <typename T>
using Vector2 = Vector<2, T>;

template <typename T>
using Vector3 = Vector<3, T>;

template <typename T>
using Vector4 = Vector<3, T>;

template <size_t dim>
using VectorS = Vector<dim, size_t>;

template <size_t dim>
using VectorI = Vector<dim, int>;

template <size_t dim>
using VectorF = Vector<dim, float>;

template <size_t dim>
using VectorD = Vector<dim, double>;

using Vector2S = Vector<2, size_t>;
using Vector3S = Vector<3, size_t>;
using Vector4S = Vector<4, size_t>;
using Vector2I = Vector<2, int>;
using Vector3I = Vector<3, int>;
using Vector4I = Vector<4, int>;
using Vector2F = Vector<2, float>;
using Vector3F = Vector<3, float>;
using Vector4F = Vector<4, float>;
using Vector2D = Vector<2, double>;
using Vector3D = Vector<3, double>;
using Vector4D = Vector<4, double>;


template <size_t dim, typename T=double>
struct ScaledMeasurePolytope {
    Vector<dim, T> position;
    Vector<dim, T> scale;

    ScaledMeasurePolytope() {
        this->position = Vector<dim, T>();
        this->scale = Vector<dim, T>();
    }

    ScaledMeasurePolytope(const Vector<dim, T>& scale) {
        this->position = Vector<dim, T>();
        this->scale = scale;
    }

    ScaledMeasurePolytope(const Vector<dim, T>& position, const Vector<dim, T>& scale) {
        this->position = position;
        this->scale = scale;
    }

    static ScaledMeasurePolytope<dim, T> polytope_from_center(const Vector<dim, T>& scale) {
        return ScaledMeasurePolytope<dim, T>(- scale/2, scale);
    }

    static ScaledMeasurePolytope<dim, T> polytope_from_center(
            const Vector<dim, T>& center,
            const Vector<dim, T>& scale
    ) {
        return ScaledMeasurePolytope<dim, T>(center - scale/2, scale);
    }

    void move(const Vector<dim, T>& delta) {
        this->position += delta;
    }

    void move_scaled(Vector<dim, T> delta) {
        auto iterator = delta.begin();
        for (const auto& i : this->scale) {
            *iterator *= i;
            ++ iterator;
        }
        this->move(delta);
    }

    ScaledMeasurePolytope<dim, T> moved(const Vector<dim, T>& delta) const {
        return ScaledMeasurePolytope<dim, T>(this->position + delta, scale);
    }

    ScaledMeasurePolytope<dim, T> moved_scaled(Vector<dim, T>& delta) const {
        auto iterator = delta.begin();
        for (const auto& i : this->scale) {
            *iterator *= i;
            ++ iterator;
        }
        return this->moved(delta);
    }

    void scale_in_place(const Vector<dim, T>& scale) {
        auto iterator = this->scale.begin();
        for (const auto& i : scale) {
            *iterator *= i;
            ++ iterator;
        }
    }

    void scale_from_center(const Vector<dim, T>& scale) {
        auto position_iterator = this->position.begin();
        auto scale_iterator = this->scale.begin();
        for (const auto& i : scale) {
            *position_iterator *= i;
            *scale_iterator *= i;
            ++ position_iterator;
            ++ scale_iterator;
        }
    }

    ScaledMeasurePolytope<dim, T> scaled_in_place(Vector<dim, T> scale) const {
        auto iterator = scale.begin();
        for (auto& i : scale) {
            i *= *iterator;
            ++ iterator;
        }
        return ScaledMeasurePolytope<dim, T>(this->position, scale);
    }

    ScaledMeasurePolytope<dim, T> scaled_from_center(Vector<dim, T> scale) const {
        Vector<dim, T> position = this->position;
        auto iterator = scale.begin();
        auto position_iterator = position.begin();
        for (auto& i : scale) {
            *position_iterator *= i;
            i *= *iterator;
            ++ position_iterator;
            ++ iterator;
        }
        return ScaledMeasurePolytope<dim, T>(this->position, scale);
    }

    bool empty() const {
        for (const auto& i : scale)
            if (i != 0)
                return false;
        return true;
    }

    T encased_size() const {
        T out = 1;
        for (const auto& i : scale)
            out *= i;
        return out;
    }
};


template <typename T>
using Rectangle = ScaledMeasurePolytope<2, T>;

template <typename T>
using Cuboid = ScaledMeasurePolytope<3, T>;

template <typename T>
using ScaledTesseract = ScaledMeasurePolytope<4, T>;

template <size_t dim>
using ScaledMeasurePolytopeS = ScaledMeasurePolytope<dim, size_t>;

template <size_t dim>
using ScaledMeasurePolytopeI = ScaledMeasurePolytope<dim, int>;

template <size_t dim>
using ScaledMeasurePolytopeF = ScaledMeasurePolytope<dim, float>;

template <size_t dim>
using ScaledMeasurePolytopeD = ScaledMeasurePolytope<dim, double>;

using RectangleS = ScaledMeasurePolytope<2, size_t>;
using RectangleI = ScaledMeasurePolytope<2, int>;
using RectangleF = ScaledMeasurePolytope<2, float>;
using RectangleD = ScaledMeasurePolytope<2, double>;
using CuboidS = ScaledMeasurePolytope<2, size_t>;
using CuboidI = ScaledMeasurePolytope<2, int>;
using CuboidF = ScaledMeasurePolytope<2, float>;
using CuboidD = ScaledMeasurePolytope<2, double>;
using ScaledTesseractS = ScaledMeasurePolytope<2, size_t>;
using ScaledTesseractI = ScaledMeasurePolytope<2, int>;
using ScaledTesseractF = ScaledMeasurePolytope<2, float>;
using ScaledTesseractD = ScaledMeasurePolytope<2, double>;
