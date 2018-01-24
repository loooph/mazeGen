#include <iostream>
#include <fstream>
#include "Maze.hpp"

int main (int argc, char** args)
{

    if ( argc != 4 )
    {
        throw std::runtime_error( "wrong number of arguments!" );
    }
    std::ofstream ofs( args[3] );
    Maze m1(static_cast<unsigned int> ( std::stoul( args[1] ) ), static_cast<unsigned int> ( std::stoul( args[2] ) ) );
    ofs << m1;
    return 0;
}
