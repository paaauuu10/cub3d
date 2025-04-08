# cub3D - 42 Project | Wolfenstein 3D Clone

## DESCRIPTION
A C raycasting engine using miniLibX that creates a 3D maze from 2D maps. Inspired by the original Wolfenstein 3D game.

## TECHNICAL DETAILS
- Language: C (Norm compliant)
- Graphics: miniLibX library
- Algorithm: DDA raycasting
- Textures: 4 directional wall textures
- Colors: Custom floor/ceiling RGB values
- Movement: WASD + arrow keys
- Maps: .cub configuration files

## REQUIREMENTS
- gcc compiler
- miniLibX (provided by 42)
- X11/MacOS graphical system
- Make

## INSTALLATION
1. Clone repository
2. Run 'make'
3. Execute with './cub3D maps/map.cub'

## CONTROLS
WASD - Movement
Arrows - Camera rotation
ESC - Quit game

## MAP FORMAT EXAMPLE
NO ./path_to_north_texture.xpm
SO ./path_to_south_texture.xpm
WE ./path_to_west_texture.xpm
EA ./path_to_east_texture.xpm
F 220,100,0 # Floor RGB
C 225,30,0 # Ceiling RGB

111111
100001
101101
1N0111
111111

## BONUS IDEAS
- Minimap display
- Collision detection

## NOTES
- Map must be surrounded by walls
- Only 6 valid map characters: 0,1,N,S,E,W
- Textures must be .xpm format
- Follows 42 coding standards
