#include <iostream>
#include <fstream>
#include "json.hpp"

using json = nlohmann::json;

int main()
{
    std::cout << "Hello C++ AI world \n";

    // Read a simple JSON example.
    std::ifstream f("../data/sample.json");
    // Opens an input file stream (ifstream) to read the file located at the path mentioned
    //  ../ means one directory up from the current folder, f is now a file stream object we can read from
    if (!f.is_open())
    {
        std::cerr << "Could not open sample.json\n";
        return 1;
    }

    json data;
    // Declares a variable data of type json (from nlohmann/json).
    // This will hold the content od the JSON file in the memory

    f >> data;
    // Reads the content of the file stream 'f' into the JSOn object 'data'
    // The >> operator parses the JSON text and converts it into a C++ JSON object.

    std::cout << "Read JSON content:\n"
              << data.dump(4) << "\n";
    // data.dump(4) converts the JSOn object to a string with the indentation of 4 spaces,
    // makes it easy to read.

    return 0;
}