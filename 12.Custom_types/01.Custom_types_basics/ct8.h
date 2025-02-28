/*
    . Exploring copy constructors
        . The compiler can generate one if you don't have one defined.
        . You can also default it, and it will do blind member wise copy.
        . We can set up our own copy constructor.
        . The next bit will show why copy constructors to do deep copies.
*/
#pragma once

#include <cstdint>
#include <fmt/format.h>

namespace ct8
{
    class Pixel {
    public: 
        Pixel() = default;
        Pixel(uint32_t color, unsigned int x, unsigned int y);
        //Set up a copy constructor
        //Pixel(const Pixel& other) = default;
        Pixel(const Pixel& source);

        uint32_t get_color() const;
        void set_color(uint32_t color);

        unsigned int get_x() const;
        void set_x(unsigned int x);

        unsigned int get_y() const;
        void set_y(unsigned int y);

    private: 
        uint32_t m_color{0xFF000000};
        unsigned int m_pos_x{0};
        unsigned int m_pos_y{0};
    };

    //Implementations
    inline Pixel::Pixel(uint32_t color, unsigned int x, unsigned int y)
        : m_color{color}, 
        m_pos_x{x}, 
        m_pos_y{y} 
    {
        fmt::print("Pixel created\n");
    }

    //Copy constructor
    inline Pixel::Pixel(const Pixel& source)
        : m_color{source.m_color},
        m_pos_x{source.m_pos_x},
        m_pos_y{source.m_pos_y}
    {
        fmt::print("Pixel copy created\n");
    }

    inline uint32_t Pixel::get_color() const {
        return m_color; 
    }

    inline void Pixel::set_color(uint32_t color) {
        m_color = color; 
    }

    inline unsigned int Pixel::get_x() const {
        return m_pos_x; 
    }

    inline void Pixel::set_x(unsigned int x) {
        m_pos_x = x; 
    }

    inline unsigned int Pixel::get_y() const {
        return m_pos_y; 
    }

    inline void Pixel::set_y(unsigned int y) {
        m_pos_y = y; 
    }
} // namespace ct8
