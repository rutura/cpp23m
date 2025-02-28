#pragma once

#include <cstdint>

namespace ct6
{
    class Pixel {
        public: 
            Pixel();
            Pixel(uint32_t color, unsigned int x, unsigned int y);
            ~Pixel();

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
} // namespace ct6
