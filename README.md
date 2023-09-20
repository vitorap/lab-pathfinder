
# Lab-Pathfinder

## Overview
This project aims to find the route between the entry and exit points of a guaranteed-solvable maze.

## Problem Modeling
The maze is modeled as a Constraint Graph. Each node represents a maze position, and edges connect nodes that are adjacent in the North, South, East, or West directions.

## Search Methods

### Uninformed Search
Depth-First Search (DFS) is employed as it is more time-efficient for deep trees, which is the case for the graph representing this maze.

### Informed Search
The A* algorithm is used to find the shortest possible path when multiple paths exist. Each edge between adjacent nodes has a distance value of one unit. The distance is computed using the formula:  
\( D = \sqrt{(X_a - X_b)^2 + (Y_a - Y_b)^2} \)

## Code Structure

### Main Data Structures
- The maze is represented as a matrix of pointers to graph nodes.
- Each node contains a 4-element array representing connections in the North(0), South(1), East(2), and West(3) directions.

### Execution Steps
1. Initialize the maze without connections.
2. Generate connections starting from the entry node.
3. Continue until a path exists between all nodes, ensuring the graph is connected.
4. Perform DFS and A* searches as described.

## Compilation and Execution
To compile, run `make` from the project directory.  
To execute, run `make run` from the same directory.

**Note**: The code was tested using GCC version 4.8.4 on Ubuntu 14.04.1.

## I/O Specifications
- Input: Specify the maze dimensions when prompted.
- Output: Two mazes are printed with paths marked by '+'. Execution times for both searches are also displayed.

## Experiments Conducted

| Maze Size | DFS Time (s) | A* Time (s) |
|-----------|--------------|-------------|
| 5x5       | 0.000003     | 0.000017    |
| 5x5       | 0.000004     | 0.000015    |
| 5x5       | 0.000003     | 0.000015    |
| 5x5       | 0.000002     | 0.000013    |
| 5x5       | 0.000003     | 0.000016    |
| 10x10     | 0.000011     | 0.000016    |
| 10x10     | 0.000010     | 0.000023    |
| 10x10     | 0.000010     | 0.000019    |
| 15x30     | 0.000048     | 0.000127    |
| 15x30     | 0.000039     | 0.000080    |
| **Average** | 0.000013    | 0.000034    |


## Conclusions
DFS usually finds a path more quickly, while A* finds the shortest path when multiple paths exist, albeit at a slightly higher time cost.

## Additional Instructions for Windows Compilation
Instructions for Compilation on Windows
To compile and run this project on a Windows environment, follow the steps below:

Prerequisites
Ensure the GCC compiler is installed, or install MinGW which includes GCC.
Compilation Steps
Open Command Prompt (CMD)

Navigate to the project directory.
  Compile the Code
    gcc -o lab_pathfinder src/main.c src/fila.c src/global.c src/grafo.c src/labirinto.c src/listaOrd.c src/pilha.c -Iheader

Run the Program
  ./lab_pathfinder.exe
