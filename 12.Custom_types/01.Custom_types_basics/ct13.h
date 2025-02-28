/*
    . Introducing the copy assignment operator
*/
#pragma once

#include <cstdint>
#include <fmt/format.h>
#include <memory>

namespace ct13
{

    struct Position {
        unsigned int x{0};
        unsigned int y{0};
    };

    class Pixel {
    public:
        Pixel() = default;
        Pixel(uint32_t color, unsigned int x, unsigned int y);
        
        // Copy constructor for deep copy
        Pixel(const Pixel& other);

        //Copy assignement operator
        Pixel& operator=(const Pixel& source);

        ~Pixel();
        
        // Getters and setters for color
        uint32_t get_color() const;
        void set_color(uint32_t color);

        // Getters and setters for raw pointer (m_pos)
        unsigned int get_x() const;
        unsigned int get_y() const;
        void set_x(unsigned int x);
        void set_y(unsigned int y);

        // Getters and setters for smart pointer (m_smart_pos)
        unsigned int get_smart_x() const;
        unsigned int get_smart_y() const;
        void set_smart_x(unsigned int x);
        void set_smart_y(unsigned int y);

    private:
        uint32_t m_color{0xFF000000};
        Position* m_pos{nullptr}; // Raw pointer for position
        std::unique_ptr<Position> m_smart_pos; // Smart pointer for position
    };


    //Implementations
    // Constructor
    Pixel::Pixel(uint32_t color, unsigned int x, unsigned int y)
        : m_color{color}, 
          m_pos{new Position{x, y}}, 
          m_smart_pos{std::make_unique<Position>(Position{x, y})} 
    {
    }

    // Copy constructor for deep copy with raw pointer and smart pointer
    Pixel::Pixel(const Pixel& other)
        : m_color{other.m_color}, 
          m_pos{new Position{*other.m_pos}}, 
          m_smart_pos{std::make_unique<Position>(*other.m_smart_pos)} 
    {
        fmt::print("Pixel deep copied (with both raw and smart pointers)\n");
    }

    //Copy assignment operator 
    Pixel& Pixel::operator=(const Pixel& source){

        //Self assignment check
        if(this == & source){
            return *this;
        }

        //Copy the color
        m_color = source.m_color;

        //Deep copies
        if(m_pos != nullptr){
            delete m_pos; // Clean the old memory
        }
        m_pos = new Position{*source.m_pos};

        //Do the same for the smart pointer
        m_smart_pos = std::make_unique<Position>(*source.m_smart_pos);

        fmt::print("Pixel copy-assigned (with both raw and smart pointers)\n");
        return *this;
    }

    // Destructor to clean up raw pointer
    Pixel::~Pixel() {
        delete m_pos; // Clean up memory allocated by raw pointer
        fmt::print("Pixel destroyed\n");
    }

       // Get color
    uint32_t Pixel::get_color() const {
        return m_color;
    }

    // Set color
    void Pixel::set_color(uint32_t color) {
        m_color = color;
    }

    // Getters for raw pointer position (m_pos)
    unsigned int Pixel::get_x() const {
        return m_pos->x;
    }

    unsigned int Pixel::get_y() const {
        return m_pos->y;
    }

    // Setters for raw pointer position (m_pos)
    void Pixel::set_x(unsigned int x) {
        m_pos->x = x;
    }

    void Pixel::set_y(unsigned int y) {
        m_pos->y = y;
    }

    // Getters for smart pointer position (m_smart_pos)
    unsigned int Pixel::get_smart_x() const {
        return m_smart_pos->x;
    }

    unsigned int Pixel::get_smart_y() const {
        return m_smart_pos->y;
    }

    // Setters for smart pointer position (m_smart_pos)
    void Pixel::set_smart_x(unsigned int x) {
        m_smart_pos->x = x;
    }

    void Pixel::set_smart_y(unsigned int y) {
        m_smart_pos->y = y;
    }
    
} // namespace ct13
