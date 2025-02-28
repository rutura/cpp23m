#pragma once

#include <vector>
#include <string>
#include <cmath>
#include <iostream>

#include <ftxui/dom/elements.hpp>       // for text, Element, hbox, vbox, border
#include <ftxui/screen/screen.hpp>      // for Screen
#include <ftxui/component/component.hpp> // for Input, Renderer, ScreenInteractive
#include <ftxui/component/screen_interactive.hpp> // for ScreenInteractive

#include <SFML/Graphics.hpp>

/*
    Ftxui based calculator
*/
namespace it_1
{
    using namespace ftxui;

    //Functions to do the operations
    double add(double a, double b){ return a + b;}
    double subtract(double a, double b){ return a - b;}
    double multiply(double a, double b){ return a * b;}
    double divide(double a, double b){return b != 0 ? a / b : 0;}


    void app(){

        // UI state variables
        double num1 = 0;
        double num2 = 0;
        double result = 0;
        bool is_calculated = false;

        // Input boxes for numbers
        std::string num1_str = "0";
        std::string num2_str = "0";
        auto input1 = Input(&num1_str, "Enter first number");
        auto input2 = Input(&num2_str, "Enter second number");

        // Operation selector menu
        std::vector<std::string> operations = { "Add", "Subtract", "Multiply", "Divide" };
        int operation_index {0};
        auto operation_menu = Menu(&operations, &operation_index);


        // Calculate button
        auto button = Button("Calculate", [&] {
            num1 = std::stod(num1_str);
            num2 = std::stod(num2_str);

            // Perform the selected operation using function overloading
            switch (operation_index) {
                case 0: result = add(num1, num2); break;
                case 1: result = subtract(num1, num2); break;
                case 2: result = multiply(num1, num2); break;
                case 3: result = divide(num1, num2); break;
            }

            is_calculated = true;
        });

        // Renderer for the UI components
        auto container = Container::Vertical({
            input1,
            input2,
            operation_menu,
            button
        });

        auto renderer = Renderer(container, [&]() {
            return vbox({
                text("Basic Calculator") | bold | center,
                separator(),
                hbox(text("First Number: "), input1->Render()) | center,
                hbox(text("Second Number: "), input2->Render()) | center,
                hbox(text("Operation: "), operation_menu->Render()) | center,
                button->Render() | center,
                separator(),
                is_calculated ? text("Result: " + std::to_string(result)) | bold | center : text("")
            }) | border;
        });

        //Launch the UI
        auto screen = ScreenInteractive::TerminalOutput();
        screen.Loop(renderer);

    }
    
} // namespace it_1

/*
    . Sfml show the distance between points.
    . Distance shown as text.
*/
namespace it_2
{
    // Function to calculate the Euclidean distance between two points
    double calculate_distance(const double origin[2], const double mouse_position[2]) {
        double dx = mouse_position[0] - origin[0];
        double dy = mouse_position[1] - origin[1];
        return std::sqrt(dx * dx + dy * dy);
    }


    void init(sf::RenderWindow &window, sf::Font &font, 
                    sf::Text &origin_text, sf::Text &mouse_text, 
                    sf::Text &distance_text, const double origin[2]) {

        window.create(sf::VideoMode(800, 600), "Distance from Origin to Mouse Position");

        if (!font.loadFromFile("arial.ttf")) {
            std::cerr << "Error loading font. Make sure the font file is in the same directory as the binary.\n";
            return;
        }

        origin_text.setFont(font);
        origin_text.setCharacterSize(24);
        origin_text.setFillColor(sf::Color::White);
        origin_text.setPosition(50, 50);

        mouse_text.setFont(font);
        mouse_text.setCharacterSize(24);
        mouse_text.setFillColor(sf::Color::White);
        mouse_text.setPosition(50, 100);

        distance_text.setFont(font);
        distance_text.setCharacterSize(24);
        distance_text.setFillColor(sf::Color::White);
        distance_text.setPosition(50, 150);
    }

    void process_events(sf::RenderWindow &window) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
    }


    void render(sf::RenderWindow &window, sf::Text &origin_text, sf::Text &mouse_text, sf::Text &distance_text) {
        window.clear(sf::Color::Black);
        window.draw(origin_text);
        window.draw(mouse_text);
        window.draw(distance_text);
        window.display();
    }

    void app(){
        double origin[2] = {0.0, 0.0};
        double mouse_position[2] = {0.0, 0.0};
        double distance = 0.0;

        sf::RenderWindow window;
        sf::Font font;
        sf::Text origin_text, mouse_text, distance_text;

        init(window, font, origin_text, mouse_text, distance_text, origin);

        //Set up the event loop
        while (window.isOpen())
        {
            process_events(window);

            //Additional processing

            //Get the mouse position
            sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
            mouse_position[0] = static_cast<double>(mouse_pos.x);
            mouse_position[1] = static_cast<double>(mouse_pos.y);

            // Calculate distance from origin to mouse position
            distance = calculate_distance(origin, mouse_position);

            // Update the displayed text
            origin_text.setString("Origin Point: (" + std::to_string(origin[0]) + ", " + std::to_string(origin[1]) + ")");
            mouse_text.setString("Mouse Position: (" + std::to_string(mouse_position[0]) + ", " + std::to_string(mouse_position[1]) + ")");
            distance_text.setString("Distance from Origin: " + std::to_string(distance));


            //render
            render(window, origin_text, mouse_text, distance_text);
        }

    }
    
} // namespace it_2


namespace it_3
{

    void init(sf::RenderWindow &window, sf::Font &font, sf::Text &distance_text) {

        window.create(sf::VideoMode(800, 600), "Distance from Origin to Mouse Position");

        if (!font.loadFromFile("arial.ttf")) {
            std::cerr << "Error loading font. Make sure the font file is in the 'fonts' directory." << std::endl;
        }

        distance_text.setFont(font);
        distance_text.setCharacterSize(24);
        distance_text.setFillColor(sf::Color::White);
        distance_text.setPosition(50, 550);
    }


    void process_events(sf::RenderWindow &window, bool &running) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                running = false;
            }
        }
    }

    void render(sf::RenderWindow &window, const double origin[2], const double mouse_position[2], double distance, sf::Text &distance_text) {
        window.clear(sf::Color::Black);

        sf::CircleShape origin_point(5);
        origin_point.setFillColor(sf::Color::Red);
        origin_point.setPosition(origin[0] - origin_point.getRadius(), origin[1] - origin_point.getRadius());

        sf::CircleShape mouse_point(5);
        mouse_point.setFillColor(sf::Color::Green);
        mouse_point.setPosition(mouse_position[0] - mouse_point.getRadius(), mouse_position[1] - mouse_point.getRadius());

        distance_text.setString(std::to_string(distance));

        window.draw(origin_point);
        window.draw(mouse_point);
        window.draw(distance_text);
        window.display();
    }

    void app(int argc, char* argv[]){

        if (argc < 3) {
            std::cerr << "Usage: " << argv[0] << " <origin_x> <origin_y>" << std::endl;
            return;
        }

        double origin[2];
        origin[0] = std::stod(argv[1]);
        origin[1] = std::stod(argv[2]);

        sf::RenderWindow window;
        sf::Font font;
        sf::Text distance_text;

        init(window, font, distance_text);

        double mouse_position[2] = {0.0, 0.0};
        double distance = 0.0;

        bool running {true};

        //Event loop
        while (running)
        {
            process_events(window,running);

            sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
            mouse_position[0] = static_cast<double>(mouse_pos.x);
            mouse_position[1] = static_cast<double>(mouse_pos.y);

            distance = it_2::calculate_distance(origin, mouse_position);

            render(window,origin,mouse_position,distance,distance_text);
        }
        

    }
    
} // namespace it_3
