#pragma once

#include <filesystem>
#include <fmt/format.h>
#include "text_files.h"
#include "binary_files.h"

namespace utilities {

void read_write_text_files(){
    std::filesystem::path file_path = R"(D:\sample_file.txt)"; // Windows
    //std::filesystem::path file_path = R"(/path/to/your/input_file.txt)"; // Linux

    std::string content = "\nHello, world!\nThis is a test.";

    //Write the content to the file
    text_files::write_file(file_path,content);

    //Read the content back from the file and print it
    text_files::read_file(file_path);
}

void read_write_binary_files(){
    // Define file path
	std::filesystem::path file_path = R"(D:\sample_file.bin)"; // Windows
    //std::filesystem::path file_path = R"(/path/to/your/input_file.bin)"; // Linux

    // Example content to write (binary data)
    std::vector<char> content = {'H', 'e', 'l', 'l', 'o', ' ', 'B', 'i', 'n', 'a', 'r', 'y', '!'};
    //std::vector<char> content = {0x48, 0x65, 0x6C, 0x6C, 0x6F, 0x00};

    //Write binary data to the file
    binary_files::write_file(file_path,content);

    // Read binary data from file
    std::vector<char> read_content = binary_files::read_file(file_path);

    // Display the read content as text
    if (!read_content.empty()) {
        fmt::print("Read content: {}\n", std::string(read_content.begin(), read_content.end()));
    } else {
        fmt::print("No content read from file.\n");
    }
}

} // namespace utilities
