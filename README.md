

# # Cub3D Project!

  

Cub3D is a modern reinterpretation of the classic 3D maze game, inspired by the legendary game 'Wolfenstein 3D'. This project showcases a simple yet effective rendering of a 3D environment using ray-casting techniques. Cub3D not only demonstrates the power of graphical computations but also serves as an homage to the roots of 3D gaming.

  
  

## Features

  

-  **Ray-Casting Engine**: Implements the core mechanics of the 3D rendering using ray-casting.

-  **Map Customization**: Allows users to design and play in custom maps.

-  **Texture Handling**: Supports various textures.

-  **Dynamic Movement**: Smooth player movement and controls within the 3D space.

-  **Collision Detection**: Efficient collision algorithms to ensure realistic movement constraints.

  

## Installation

  

1. Clone the repository:

`git clone [URL of your repository]`

2. Navigate to the project directory:

`cd cub-3D`

3. Compile the project (make sure you have the necessary compilers and libraries installed):

`make`

  

## Usage

  

To run Cub3D, execute the following command in the project directory:

`./cub3D maps/valid_map****.cub`

**Controls**

WASD for player control, and < & > for view.

  

## Map Configuration
Maps are defined using a simple configuration file. Here's an example format:
```
111111
100101
100E01
100001
111111
```
In this file, `1` represents walls, `0` the walkable path, and `E` denotes the begin position of the player and the direction of his view (`E`ast, `W`est, `N`orth & `S`outh).
In addition to the map layout, the configuration file allows you to specify textures for walls and colors for the floor and ceiling. Here's how you can define them:

 -- **Wall Textures**: Specify the textures for each side of the wall (North, South, West, East) using the following format:
- `NO ./assets/texture_no.xpm` - Texture for the North-facing wall.
- `SO ./assets/texture_so.xpm` - Texture for the South-facing wall.
- `WE ./assets/texture_we.xpm` - Texture for the West-facing wall.
- `EA ./assets/texture_ea.xpm` - Texture for the East-facing wall.  

 -- **Floor and Ceiling Colors**: Define the RGB color values for the floor and ceiling:
- `F 220,100,0` - Color for the Floor (RGB format).
- `C 225,30,0` - Color for the Ceiling (RGB format).
