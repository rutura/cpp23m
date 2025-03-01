#pragma once

#include <SFML/Graphics.hpp>
#include <array>
#include <span>
#include "../pieces/tetromino.h"

class Board{
public:
    static constexpr int WIDTH = 10;
    static constexpr int HEIGHT = 20;
    static constexpr float BLOCK_SIZE = 30.0f;

    inline static const std::array<sf::Color, 8> BLOCK_COLORS = {
        sf::Color::Black,      // Empty
        sf::Color::Cyan,       // I
        sf::Color::Yellow,     // O
        sf::Color(128, 0, 128),// T (Purple)
        sf::Color::Green,      // S
        sf::Color::Red,        // Z
        sf::Color::Blue,       // J
        sf::Color(255, 165, 0) // L (Orange)
    };

    Board() {
        grid.fill({});
        locked_grid.fill({});
    }

    void initialize(){
        //Sect all cells to empty (0)
        grid.fill({});
        locked_grid.fill({});
    }

    void clear_board(){
        grid.fill({});
        locked_grid.fill({});
    }

    void update_tetromino(const Tetromino& tetromino) {
        // Clear only moving pieces, keep locked ones
        for (int y = 0; y < HEIGHT; ++y) {
            for (int x = 0; x < WIDTH; ++x) {
                if (!locked_grid[y][x]) {
                    grid[y][x] = 0;
                }
            }
        }

        auto shape = tetromino.get_shape();
        int type = static_cast<int>(tetromino.get_type());
        int pos_x = tetromino.get_pos_x();
        int pos_y = tetromino.get_pos_y();

        //Looping through the 4x4 grid of the tetromino
        for (int y = 0; y < Tetromino::GRID_SIZE; ++y) {
            for (int x = 0; x < Tetromino::GRID_SIZE; ++x) {
                if (shape[y][x]) {
                    //If the spot is turned on in the tetromino, turn it on in the board
                    int board_x = pos_x + x;
                    int board_y = pos_y + y;
                    if (board_x >= 0 && board_x < WIDTH && board_y >= 0 && board_y < HEIGHT) {
                        grid[board_y][board_x] = type; // The types are mapped to colors in the BoardEntity class draw method.
                    }
                }
            }
        }
    }

    void lock_current_piece(const Tetromino& tetromino) {
        auto shape = tetromino.get_shape();
        int type = static_cast<int>(tetromino.get_type());
        int pos_x = tetromino.get_pos_x();
        int pos_y = tetromino.get_pos_y();

        for (int y = 0; y < Tetromino::GRID_SIZE; ++y) {
            for (int x = 0; x < Tetromino::GRID_SIZE; ++x) {
                if (shape[y][x]) {
                    int board_x = pos_x + x;
                    int board_y = pos_y + y;

                   //Set locked state if not out of bounds
                    if (board_x >= 0 && board_x < WIDTH && board_y >= 0 && board_y < HEIGHT) {
                        locked_grid[board_y][board_x] = true;
                    }
                }
            }
        }
    }

    // returns true if the piece is out of bounds or collides with locked pieces
    bool is_collision(const Tetromino& tetromino) const {
        auto shape = tetromino.get_shape();
        int pos_x = tetromino.get_pos_x();
        int pos_y = tetromino.get_pos_y();

        for (int y = 0; y < Tetromino::GRID_SIZE; ++y) {
            for (int x = 0; x < Tetromino::GRID_SIZE; ++x) {
                if (shape[y][x]) {
                    int board_x = pos_x + x;
                    int board_y = pos_y + y;
                    
                    if (board_x < 0 || board_x >= WIDTH || board_y >= HEIGHT) {
                        return true;
                    }
                    
                    // Check collision with locked pieces
                    if (board_y >= 0 && locked_grid[board_y][board_x]) {
                        return true;
                    }
                }
            }
        }
        return false;
    }

    std::span<const std::array<int, WIDTH>> get_grid() const {
        return grid;
    }

    bool is_line_complete(int row) const {
        for (int x = 0; x < WIDTH; ++x) {
            if (!locked_grid[row][x]) return false;
        }
        return true;
    }

    void clear_line(int row) {
        // Move all rows above down
        for (int y = row; y > 0; --y) {
            grid[y] = grid[y - 1];
            locked_grid[y] = locked_grid[y - 1];
        }
        // Clear top row
        grid[0].fill(0);
        locked_grid[0].fill(false);
    }

    /*
        1. The loop starts from the bottom row (HEIGHT - 1) and moves upwards (--y).
        2. When a complete line is found (is_line_complete(y)), it is cleared (clear_line(y)).
        3. The lines_cleared counter is incremented.
        4. The ++y statement increments y to recheck the same row index in the next iteration 
            because the rows above have shifted down.
        5. The loop control (--y) will then decrement y in the next iteration, effectively 
            keeping y at the same value it was before the ++y statement.
    */
    int clear_complete_lines() {
        int lines_cleared = 0;
        for (int y = HEIGHT - 1; y >= 0; --y) {
            if (is_line_complete(y)) {
                clear_line(y);
                ++lines_cleared;
                ++y; // Check the same row again as everything shifted down
            }
        }
        return lines_cleared;
    }

    bool is_game_over(const Tetromino& tetromino) const {
        // If a newly spawned piece immediately collides, game is over
        return is_collision(tetromino);
    }

private:
    std::array< std::array<int, WIDTH> , HEIGHT> grid; 
    std::array<std::array<bool, WIDTH>, HEIGHT> locked_grid{};
};