#include <stdexcept>
#include <utility>
#include <fmt/format.h>
#include "canvas.h"

namespace raw{

    Canvas::Canvas(std::size_t width, std::size_t height, const Configuration& config)
        : m_width{width}, m_height{height}, m_config{config} {

        fmt::println("Regular constructor");
        m_pixels = new Pixel*[m_width];
        for (std::size_t i = 0; i < m_width; ++i) {
            m_pixels[i] = new Pixel[m_height];
        }
        ++s_canvas_count;
    }

    //Copy constructor
    Canvas::Canvas(const Canvas& src)
        : Canvas(src.m_width, src.m_height, src.m_config) {
            fmt::println("Copy constructor");
        for (std::size_t i = 0; i < m_width; ++i) {
            for (std::size_t j = 0; j < m_height; ++j) {
                m_pixels[i][j] = src.m_pixels[i][j];
            }
        }
    }

    //Move constructor in terms of the swap method
    Canvas::Canvas(Canvas&& other) noexcept
        : m_config{other.m_config}  // Initialize the reference member
    {
        fmt::println("Move constructor");
        swap(other); // Steal the data from other and let it die.
    }


    //Destructor
    Canvas::~Canvas() {
        for (std::size_t i = 0; i < m_width; ++i) {
            delete[] m_pixels[i];
        }
        delete[] m_pixels;
        fmt::println("Canvas destroyed");

        //Decrement the canvas count
        --s_canvas_count;
    }

    Canvas Canvas::create_default_canvas(const Configuration& config) {
        //return Canvas(800, 600); // Default dimensions
        return Canvas(DEFAULT_WIDTH, DEFAULT_HEIGHT, config);
    }

    std::size_t Canvas::get_total_canvas_count() {
        return s_canvas_count;
    }

    //Copy assignment operator with the copy and swap idiom
    Canvas& Canvas::operator=(const Canvas& rhs) {
        fmt::println("Copy assignment operator");
        Canvas temp(rhs);
        swap(temp);
        return *this;
    }

    //Move assignment operator through the swap method
    Canvas& Canvas::operator=(Canvas&& other) noexcept {
        fmt::println("Move assignment operator");
        if (this == &other) {
            return *this;
        }
        swap(other);
        //doint this does not guarantee that the contents of this is immediately cleaned up. Instead,
        //the contents of this escapes through other to the caller of the move assignment operator and thus
        //might stay alive longer than expected.
        return *this;
    }

   
    void Canvas::modify_pixel(std::size_t x, std::size_t y, const Pixel& pixel) {
        verify_coordinate(x, y);
        m_pixels[x][y] = pixel;
    }

    Pixel& Canvas::retrieve_pixel(std::size_t x, std::size_t y) {
        verify_coordinate(x, y);
        return m_pixels[x][y];
    }

    void Canvas::swap(Canvas& other) noexcept {
        std::swap(m_width, other.m_width);
        std::swap(m_height, other.m_height);
        std::swap(m_pixels, other.m_pixels);
    }

    void Canvas::print() const {
        for (std::size_t x = 0; x < m_width; ++x) {
            for (std::size_t y = 0; y < m_height; ++y) {
                const Pixel& pixel = m_pixels[x][y];
                auto color = pixel.get_color();
                fmt::print("#{0:06X} ", color);
            }
            fmt::print("\n");
        }
    }

    void Canvas::verify_coordinate(std::size_t x, std::size_t y) const {
        if (x >= m_width || y >= m_height) {
            throw std::out_of_range("Invalid coordinate");
        }
    }

    void swap(Canvas& first, Canvas& second) noexcept {
        first.swap(second);
    }

}   // namespace raw