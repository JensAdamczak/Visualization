#include "colors.inc"
#include "Math.inc"
#include "PlotUtilities.inc"

#declare Filename = "/Users/adamczak/Desktop/Testfile.csv"
#declare Data = array[100][3];
Read_File(Filename, Data)

#declare X = Data[0];
#declare Y = Data[1];
#declare Z = Data[2];

camera{
  location<1.6, 1.2, -1.0>
  look_at<0.25, 0.25, 0.5>
}

light_source{<4, 4, -4> color White}

background{color LightWood}

Make_Coord_Grid(
  0, 1.0, 0.1, 
  0, 1.0, 0.1,
  0, 1.0, 0.1, 
  0.005, White 
  "X-Axis", "Y-Axis", "Z-Axis"
)

Plot3d(X, Y, Z, Red, 0.025)
