// Persistence of Vision Ray Tracer version Include File
// File: PlotUtilities.inc
// Last updated: Jul 5 2014
// Description: Make 3d coordinate system, Make 3d plot, Read file, ... 


// Make a coordinate grid
#macro Make_Coord_Grid(Xstart, Xend, StepX, 
                       Ystart, Yend, StepY, 
                       Zstart, Zend, StepZ,
                       Thickness, Color, 
                       XAxisLabel, YAxisLabel, ZAxisLabel)

  #local Plastic_Texture = texture{
      pigment{color Color}
      finish{diffuse 0.6
             ambient 0.6
             specular 0.5
             roughness 0.05}
  }
  #local AxisX = cylinder{
    <Xstart, Ystart, Zstart>,
    <Xend, Ystart, Zstart>,
    Thickness
    texture{Plastic_Texture}
  }
  #local AxisY = cylinder{
    <Xstart, Ystart, Zstart>,
    <Xstart, Yend, Zstart>,
    Thickness
    texture{Plastic_Texture}
  }
  #local AxisZ = cylinder{
    <Xstart, Ystart, Zstart>,
    <Xstart, Ystart, Zend>,
    Thickness
    texture{Plastic_Texture}
  }
  text{ttf "timrom.ttf" XAxisLabel 0.01, 0
      texture{Plastic_Texture}
      scale 0.08
      rotate<90, 0, 0>
      translate<Xstart+StepX, Ystart, Zstart-2*StepZ>}
  text{ttf "timrom.ttf" YAxisLabel 0.01, 0
      texture{Plastic_Texture}
      scale 0.08
      rotate<0, 0, 90>
      translate<Xend+2*StepX, Ystart+StepY, Zend>}
  text{ttf "timrom.ttf" ZAxisLabel 0.01, 0
      texture{Plastic_Texture}
      scale 0.08
      rotate<90, -90, 0>
      translate<Xend+2*StepX, Ystart, Zstart+StepZ>}

  union{
    #local CounterX = 0;
    #local CounterY = 0;
    #local CounterZ = 0;
    #while(CounterX <= (Xend-Xstart)/StepX)
      //#debug concat("Value is= ", str(CounterX, 3, 1), "\n")
      object{AxisZ
             translate<CounterX*StepX, 0, 0>}
      object{AxisY
             translate<CounterX*StepX, 0, (Zend-Zstart)>}
      #if (CounterX > 0 & CounterX < (Xend-Xstart)/StepX)
        text{ttf "timrom.ttf" str(Xstart+CounterX*StepX, 3, 1), 0.02, 0
             pigment{color Black}
             scale 0.05
             rotate<90, 0, 0>
             translate<Xstart+CounterX*StepX, Ystart, Zstart-StepZ>}
      #end
      #local CounterX = CounterX + 1;
    #end
    #while(CounterY <= (Yend-Ystart)/StepY)
      object{AxisZ
             translate<0, CounterY*StepY, 0>}
      object{AxisX
             translate<0, CounterY*StepY, (Zend-Zstart)>}
      #if (CounterY > 0 & CounterY < (Yend-Ystart)/StepY)
        text{ttf "timrom.ttf" str(Ystart+CounterY*StepY, 3, 1), 0.02, 0
             pigment{color Black}
             scale 0.05
             rotate<0, 0, 90>
             translate<Xend+StepX, Ystart+CounterY*StepY-StepY/2, Zend>}
      #end
      #local CounterY = CounterY + 1;
    #end
    #while(CounterZ <= (Zend-Zstart)/StepZ)
      object{AxisY
             translate<0, 0, CounterZ*StepZ>}
      object{AxisX
             translate<0, 0, CounterZ*StepZ>}
      #if (CounterZ > 0 & CounterZ < (Zend-Zstart)/StepZ)
        text{ttf "timrom.ttf" str(Zstart+CounterZ*StepZ, 3, 1), 0.02, 0
             pigment{color Black}
             scale 0.05
             rotate<90, -90, 0>
             translate<Xend+StepX, Ystart, Zstart+CounterZ*StepZ-StepZ/2.>}
      #end
      #local CounterZ = CounterZ + 1;
    #end
  }
#end


// Make a sphere as plotting symbol
#macro Make_Sphere(Xcoord, Ycoord, Zcoord, Size_sph, Color_sph)
  #local TransVal = 0.3;
  #local Texture_Sphere= 
    texture{
      pigment{color Color_sph transmit TransVal}
      finish{diffuse 0.6
             ambient 0.6
             specular 0.5
             roughness 0.05}
    }
  
  sphere{<Xcoord, Ycoord, Zcoord>, Size_sph
         texture{Texture_Sphere}
  }
#end


// Plot symbols
#macro Plot3d(X, Y, Z, Color, Symbol_Size)
  #local N = dimension_size(X, 1);
  #local Index = 0;
  #while(Index < N)
    Make_Sphere(X[Index], Z[Index], Y[Index], Symbol_Size, Color)
    #declare Index = Index + 1;
  #end
#end


// Read file with coordinates
#macro Read_File(Filename, Res_arr)
  #local Nrows = dimension_size(Res_arr, 1);
  #local Ncols = dimension_size(Res_arr, 2);
  #fopen MyFile Filename read
  
  #local Myarr = array[Nrows][Ncols];
  #local N = 0;
  #while(N < Nrows)
    #local M = 0;
    #while(M < Ncols)
      #read(MyFile, Var)
      #local Myarr[N][M] = Var;
      #local M = M + 1;
    #end
    #local N = N + 1;
  #end
  
  #local Res_arr = array[Ncols];
  #local M = 0;
  #while(M < Ncols)
    #local N = 0;
    #local Temp_arr = array[Nrows];
    #while(N < Nrows)
      #local Temp_arr[N] = Myarr[N][M];
      #local N = N + 1;
    #end
    #local Res_arr[M] = Temp_arr; 
    #local M = M + 1;
  #end
#end
