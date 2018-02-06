//
// Created by loooph on 24.01.2018.
//

#ifndef MAZEGEN_MAZE_HPP
#define MAZEGEN_MAZE_HPP


#include <unordered_set>
#include <vector>
#include <list>
#include <cstdlib>
#include <ctime>
#include <iostream>

class Maze
{
public:
    Maze() = default;

    /**
     * @brief constructs random maze of a given size
     * @param h height, number of cells
     * @param w width, number of cells
     */
    Maze( unsigned int h, unsigned int w );

    /**
     * @brief prints the grid of the maze
     * @param out stream to write into
     * @param maze to print the grid of
     * @return out
     */
    friend std::ostream &operator<< (std::ostream &out, const Maze &maze);

private:
    /**
     * @brief elements pointing to a root node, they are connected to
     */
    std::vector<unsigned int> connectivityTree;

    /**
     * @brief grid to print
     */
    std::vector<std::vector<bool>> grid;

    /**
     * @brief walls of the maze
     * Numbered from top left to bottom right.
     * First all vertical walls followed by all horizontal walls.
     */
    std::vector<bool> walls;

    /**
     * @brief initializes grid with a given size, creates walls and empty cells
     * @param h height, number of cells
     * @param w width, number of cells
     */
    void initGrid( unsigned int h, unsigned int w );

    /**
     * @brief initializes components with a given size, each node will get their respective component
     * @param h height, number of cells
     * @param w width, number of cells
     */
    void initConnectivityTree (unsigned int h, unsigned int w);

    /**
     * @brief initializes walls with a given size,
     * @param h height, number of cells
     * @param w width, number of cells
     */
    void initWalls (unsigned int h, unsigned int w);

    /**
     * @brief generates random maze on the current object
     * Removes random walls until all cells are connected
     * @param h height, number of cells
     * @param w width, number of cells
     */
    void genMaze(unsigned int h, unsigned int w);

    /**
     * @brief checks whether 2 cells are connected
     * @param c1 first cell
     * @param c2 second cell
     * @return true, if there exists a path from c1 to c2 or vise versa
     * @post find will be called in the process
     */
    bool isConnected(unsigned int c1, unsigned int c2);

    /**
     * @brief joins the connectivity trees of 2 cells
     * @param c1 first cell
     * @param c2 second cell
     */
    void connectCells (unsigned int c1, unsigned int c2);

    /**
     * @brief builds the grid of walls
     * @param h height, number of cells
     * @param w width, number of cells
     */
    void buildGrid (unsigned int h, unsigned int w);

    /**
     * @brief finds the root of a node in the connectivity tree and lets the node point directly to the root
     * @param c node to find the root of
     * @return root of the node
     * @post c-th value of connectivityTree is equal to find( c )
     */
    unsigned int find (unsigned int c);
};


#endif //MAZEGEN_MAZE_HPP
