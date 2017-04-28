#ifndef OBJSDL_GEOMETRY_HH
#define OBJSDL_GEOMETRY_HH

#include <array>
#include <string>
#include <cmath>


namespace SDL {
    template <size_t dim, typename T=double>
    class Vector;


    namespace _implementation {
        namespace geometry {
            template <size_t dim, typename T1, typename T2, typename F>
            auto apply_parts(F f, const Vector<dim, T1>& v1, const Vector<dim, T2>& v2) {
                Vector<dim, decltype(f(v1[0], v2[0]))> out;
                auto iterator1 = v1.begin();
                auto iterator2 = v2.begin();
                for (auto& i : out) {
                    i = f(*iterator1, *iterator2);
                    ++ iterator1;
                    ++ iterator2;
                }
                return out;
            }

            template <size_t dim, typename T, typename F>
            auto apply_parts(F f, const Vector<dim, T>& v) {
                Vector<dim, decltype(f(v[0]))> out;
                auto iterator = v.begin();
                for (auto& i : out) {
                    i = f(*iterator);
                    ++ iterator;
                }
                return out;
            }

            template <typename T>
            bool all(const T& iterable) {
                for (bool i : iterable)
                    if (!i)
                        return false;
                return true;
            }
        }
    }


    template <size_t dim, typename T>
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


    template <size_t id, typename T, size_t num>
    T& get(Vector<num, T>& v) {
        return std::get<id>(v._get_data());
    }


    template <size_t id, typename T, size_t num>
    const T& get(const Vector<num, T>& v) {
        return std::get<id>(v._get_data());
    }


    template <typename T, typename U, size_t dim>
    auto operator+(const Vector<dim, T>& a, const Vector<dim, U>& b) {
        return _implementation::geometry::apply_parts([](const T x, const U y) {
                return x + y;
        }, a, b);
    }


    template <typename T, typename U, size_t dim>
    auto operator-(const Vector<dim, T>& a, const Vector<dim, U>& b) {
        return _implementation::geometry::apply_parts([](const T x, const U y) {
                return x - y;
        }, a, b);
    }


    template <typename T, size_t dim>
    auto operator-(const Vector<dim, T>& v) {
        return _implementation::geometry::apply_parts([](const T x) {
                return x;
        }, v);
    }


    template <typename T, typename U, size_t dim>
    auto operator*(const Vector<dim, T>& a, const Vector<dim, U>& b) {
        return _implementation::geometry::apply_parts([](const T x, const T y) {
                return x * y;
        }, a, b);
    }


    template <typename T, typename U, size_t dim>
    auto operator/(const Vector<dim, T>& a, const Vector<dim, U>& b) {
        return _implementation::geometry::apply_parts([](const T x, const T y) {
                return x / y;
        }, a, b);
    }


    template <typename T, typename U, size_t dim>
    auto operator*(const U& scalar, const Vector<dim, T>& v) {
        return _implementation::geometry::apply_parts([=](const T& x) {
                return scalar * x;
        }, v);
    }


    template <typename T, typename U, size_t dim>
    auto operator*(const Vector<dim, T>& v, const U& scalar) {
        return _implementation::geometry::apply_parts([=](const T& x) {
                return x * scalar;
        }, v);
    }


    template <typename T, typename U, size_t dim>
    auto operator/(const Vector<dim, T>& v, const U& scalar) {
        return _implementation::geometry::apply_parts([=](const T& x) {
                return x / scalar;
        }, v);
    }


    template <typename T, size_t dim>
    T& x(Vector<dim, T>& v) {
        return get<0>(v);
    }


    template <typename T, size_t dim>
    const T& x(const Vector<dim, T>& v) {
        return get<0>(v);
    }


    template <typename T, size_t dim>
    T& y(Vector<dim, T>& v) {
        return get<1>(v);
    }


    template <typename T, size_t dim>
    const T& y(const Vector<dim, T>& v) {
        return get<1>(v);
    }


    template <typename T, size_t dim>
    T& z(Vector<dim, T>& v) {
        return get<2>(v);
    }


    template <typename T, size_t dim>
    const T& z(const Vector<dim, T>& v) {
        return get<2>(v);
    }


    template <typename T, size_t dim>
    T& w(Vector<dim, T>& v) {
        return get<3>(v);
    }


    template <typename T, size_t dim>
    const T& w(const Vector<dim, T>& v) {
        return get<3>(v);
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
        Vector<dim, T> position1;
        Vector<dim, T> position2;

        ScaledMeasurePolytope() {
            this->position2 = Vector<dim, T>();
            this->position2 = Vector<dim, T>();
        }

        ScaledMeasurePolytope(const Vector<dim, T>& scale) {
            this->position1 = Vector<dim, T>();
            this->position2 = scale;
        }

        ScaledMeasurePolytope(const Vector<dim, T>& position1, const Vector<dim, T>& position2) {
            this->position1 = position1;
            this->position2 = position2;
        }

        static ScaledMeasurePolytope<dim, T> polytope_from_center(const Vector<dim, T>& scale) {
            const Vector<dim, T> half_scale = scale / 2;
            return ScaledMeasurePolytope<dim, T>(- half_scale, half_scale);
        }

        static ScaledMeasurePolytope<dim, T> polytope_from_center(
                const Vector<dim, T>& center,
                const Vector<dim, T>& scale
        ) {
            const Vector<dim, T> half_scale = scale / 2;
            return ScaledMeasurePolytope<dim, T>(center - half_scale, center + half_scale);
        }

        void move(const Vector<dim, T>& delta) {
            this->position1 += delta;
            this->position2 += delta;
        }

        ScaledMeasurePolytope<dim, T> moved(const Vector<dim, T>& delta) const {
            return ScaledMeasurePolytope<dim, T>(this->position1 + delta, this->position2 + delta);
        }

        void scale_from_point(const Vector<dim, T>& center, const Vector<dim, T>& scale) {
            this->position1 = (this->position1 - center) * scale + center;
            this->position2 = (this->position2 - center) * scale + center;
        }

        void scale(const Vector<dim, T>& scale) {
            this->scale_from_point((this->position1 + this->position2) / 2, scale);
        }

        void scale_from_origin(const Vector<dim, T>& scale) {
            this->position1 = this->position1 * scale;
            this->position2 = this->position2 * scale;
        }

        ScaledMeasurePolytope<dim, T> scaled_from_point(
                const Vector<dim, T>& center,
                const Vector<dim, T>& scale
        ) const {
            ScaledMeasurePolytope<dim, T> copy = *this;
            copy.scale_from_point(center, scale);
            return copy;
        }

        ScaledMeasurePolytope<dim, T> scaled(const Vector<dim, T>& scale) const {
            ScaledMeasurePolytope<dim, T> copy = *this;
            copy.scale(scale);
            return copy;
        }

        ScaledMeasurePolytope<dim, T> scaled_from_origin(const Vector<dim, T>& scale) const {
            ScaledMeasurePolytope<dim, T> copy = *this;
            copy.scale_from_origin(scale);
            return copy;
        }

        bool empty() const {
            return this->position1 == this->position2;
        }

        T encased_size() const {
            T out = 1;
            for (const auto& i : this->position2 - this->position1)
                out *= i;
            return out;
        }

        void make_trustable() {
            const Vector<dim, T> pos1 = _implementation::geometry::apply_parts(
                std::min,
                this->position1,
                this->position2
            );  // we need the original data to construct position2
            this->position2 = _implementation::geometry::apply_parts(
                std::max,
                this->position1,
                this->position2
            );
            return this->position2;
        }

        ScaledMeasurePolytope<dim, T> trustable() const {
            ScaledMeasurePolytope<dim, T> copy = *this;
            copy.make_trustable();
            return copy;
        }

        ScaledMeasurePolytope<dim, T> intersection(
                ScaledMeasurePolytope<dim, T>& other,
                bool trusted=false,
                bool trust_other=false
        ) {
            if (!trusted)
                this->make_trustable();
            if (!trust_other)
                other.make_trustable();
            return this->trusted_intersection(other);
        }

        ScaledMeasurePolytope<dim, T> trusted_intersection(
                const ScaledMeasurePolytope<dim, T>& other
        ) const {
            const Vector<dim, T> o0 = _implementation::geometry::apply_parts(
                std::max,
                this->position1,
                other.position1
            );
            const Vector<dim, T> o1 = _implementation::geometry::apply_parts(
                std::min,
                this->position2,
                other.position2
            );
            return ScaledMeasurePolytope<dim, T>(o0, o1);
        }

        bool contains(const Vector<dim, T>& point, bool strict=false, bool trusted=false) {
            if (!trusted)
                this->make_trustable();
            return this->trusted_contains(point, strict);
        }

        bool trusted_contains(const Vector<dim, T>& point, bool strict=false) const {
            auto f = [=](const T a, const T b) {
                if (strict)
                    return a < b;
                else
                    return a <= b;
            };

            return (
                _implementation::geometry::all(
                    _implementation::geometry::apply_parts(f, this->position1, point)
                ) &&
                _implementation::geometry::all(
                    _implementation::geometry::apply_parts(f, point, this->position2)
                )
            );
        }

        template <typename U>
        operator ScaledMeasurePolytope<dim, U>() {
            return ScaledMeasurePolytope<dim, U>(this->position1, this->position2);
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
}

#endif
