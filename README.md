# Sorting_server

This is a study project of Erel Shtossel for first degree in CS for Bar-Ilan University.

This software is a server that can calculate a cheap way to go from one point to another in a matrix.

Given a matrix via a client, the server uses A* algorithm to find the cheapest way between two given points.

The format is as follows:
Commas between numbers and an enter (\n) at the end of the line. 
If you want to set a block that cannot be reached, set it to -1.

The server accepts multiple connections (up till 10 at a time) and automatically shut down after 2 minutes.

To use this software:
1. Download and compile this code with `g++ -std=c++14 *.cpp`.
2. Run the program: the default port is set to 5600. You can give another port as an argument to the run command.
3. Connect to the server and send your matrix to calculate.
