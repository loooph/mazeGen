//
// Created by loooph on 24.01.2018.
//

#include "Maze.hpp"

Maze::Maze (unsigned int h, unsigned int w)
{
    this->initGrid(h, w);
    this->initConnectivityTree(h, w);
    this->initWalls(h, w);
    this->genMaze(h, w);
    this->buildGrid(h, w);
}

void Maze::initGrid (unsigned int h, unsigned int w)
{
    this->grid.resize( 2 * h + 1 );
    for( auto& a: this->grid )
    {
        a.resize( 2 * w + 1 , true );
    }

    // create empty cells between walls
    for( size_t i = 1; i < this->grid.size(); i += 2 )
    {
        for( size_t k = 1; k < this->grid.at( i ).size(); k += 2 )
        {
            grid.at( i ).at( k ) = false;
        }
    }

}

void Maze::initConnectivityTree (unsigned int h, unsigned int w)
{
    this->connectivityTree.resize( h * w );
    for ( unsigned int i = 0; i < this->connectivityTree.size(); ++i )
    {
        this->connectivityTree.at( i ) = i;
    }
}

void Maze::initWalls (unsigned int h, unsigned int w)
{
    this->walls.resize( 2 * h * w - h - w, true );
}

void Maze::genMaze (unsigned int h, unsigned int w)
{
    srand(static_cast<unsigned int> ( time( nullptr ) ) );

    unsigned int c1, c2;
    unsigned int i = 0;

    /**
     * @brief h * w - 1 walls have to be removed between unconnected cells, so that every cell will be connected
     */
    while ( i < h * w - 1 )
    {
        unsigned int wall = static_cast<unsigned int> ( rand() ) % this->walls.size();

        if ( !this->walls.at( wall ) )
        {
            continue;
        }
        else
        {
            if ( wall < h * ( w - 1 ) )
            {
                c1 = ( wall / ( w - 1 ) ) * ( w ) + wall % ( w - 1 );    // left cell
                c2 = c1 + 1;                                             // right cell
            }
            else
            {
                c1 = wall + h - h * w;  // upper cell
                c2 = c1 + w;            // lower cell
            }
            if ( this->isConnected(c1, c2) )
            {
                continue;
            }
            else
            {
                this->walls.at( wall ) = false;
                this->connectCells(c1, c2);
            }
        }
        ++i;
    }
}

bool Maze::isConnected (unsigned int c1, unsigned int c2)
{
    return this->find(c1 ) == this->find(c2 );
}

void Maze::connectCells (unsigned int c1, unsigned int c2)
{
    this->connectivityTree.at( this->find( c2 ) ) = this->find( c1 );
}

void Maze::buildGrid (unsigned int h, unsigned int w)
{
    for (size_t i = 1; i < this->grid.size() - 1; ++i )
    {
        for (size_t k = 1; k < this->grid.at( i ).size() - 1; ++k )
        {
            if ( i & 1 && !( k & 1 ) ) // i odd, k even
            {
                if ( !this->walls.at( ( i / 2 ) * ( w - 1 ) + k / 2 - 1 ) )
                {
                    this->grid.at( i ).at( k ) = false;
                }
            }
            else if ( !( i & 1) && k & 1 ) // i even, k odd
            {
                if ( !this->walls.at( ( i / 2 - 1 ) * w + k / 2 + h * ( w - 1 ) ) )
                {
                    this->grid.at( i ).at( k ) = false;
                }
            }
        }
    }
}

std::ostream &operator<< (std::ostream &out, const Maze &maze)
{
    out << maze.grid.size() << ' ' << maze.grid.at( 0 ).size() << "\n1 1\n"
        << maze.grid.size() - 2 << ' ' << maze.grid.at( 0 ).size() - 2 << std::endl;

    for (size_t i = 0; i < maze.grid.size(); ++i)
    {
        for (size_t k = 0; k < maze.grid.at( i ).size(); ++k)
        {
            if ( !maze.grid.at( i ).at( k ) )
            {
                out << ' ';
            }
            else
            {
                out << "█";
            }
        }
        out << std::endl;
    }
    return out;
}

unsigned int Maze::find ( unsigned int c )
{
    unsigned int root = c;
    while ( root != this->connectivityTree.at( root ) )
    {
        root = this->connectivityTree.at( root );
    }
    this->connectivityTree.at( c ) = root;
    return root;
}
