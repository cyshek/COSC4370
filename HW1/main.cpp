#include <iostream>
#include "BMP.h"    
#include <cmath>

using namespace std;

// This function is used to draw individual points on the ellipse
void Draw_Points(BMP& obj, long x_rad, long y_rad, long x_central, long y_central) {
  int thickness = 3;  // adjust this to change the thickness of the points to make ellipse easier to see
  if (y_rad >= 0) {
    for (int i = -thickness; i <= thickness; i++) {
      for (int j = -thickness; j <= thickness; j++) {
        obj.set_pixel(x_rad + x_central + i, y_rad + y_central + j, 153, 255, 51, 0);   //Set right half to green (for styling)
        obj.set_pixel(-x_rad + x_central + i, y_rad + y_central + j, 255, 255, 51, 0);  //Set left half to blue (for styling)
      }
    }
  }
}

// This function is used to draw the entire top half of the ellipse 
void Draw_Ellipse(BMP& newObj, long x_central, long y_central, long rad_x, long rad_y) {
  long stop_x, stop_y, quad1, quad2, x, y;
  x = 0, y = max(rad_y, 0L);  //Make sure that y is >= 0

  // Calculate values used to draw the top portion of the ellipse
  quad1 = pow(rad_y,2) - (pow(rad_x,2)*rad_y) + (0.25 * pow(rad_x,2));
  stop_x = 2 * pow(rad_y,2) * x;
  stop_y = 2 * pow(rad_x,2) * y;

  // This loop draws the top portion of the ellipse
  while (stop_x < stop_y) {
    Draw_Points(newObj, x, y, x_central, y_central);
    if (quad1 < 0) {
      ++x;
      stop_x += (2 * rad_y * rad_y);
      quad1 += stop_x + pow(rad_y,2);
    } else {
      ++x;
      --y;
      stop_x += (2 * rad_y * rad_y);
      stop_y -= (2 * rad_x * rad_x);
      quad1 += stop_x - stop_y + pow(rad_y,2);
    }
  }

  // Calculate values used to draw the bottom portion of the ellipse
  quad2 = (pow(rad_y,2) * ((x + 0.5) * (x + 0.5))) +
          (pow(rad_x,2) * ((y - 1) * (y - 1))) - (rad_x * rad_x * rad_y * rad_y);

  // This loop draws the bottom portion of the ellipse
  while (y) {
    Draw_Points(newObj, x, y, x_central, y_central);
    if (quad2 > 0) {
      y--;
      stop_y -= (2 * rad_x * rad_x);
      quad2 += pow(rad_x,2) - stop_y;
    } else {
      --y;
      ++x;
      stop_x += (2 * rad_y * rad_y);
      stop_y -= (2 * rad_x * rad_x);
      quad2 += stop_x - stop_y + pow(rad_x,2);
    }
  }
}

int main(){

  // Create a new BMP object with width 1600 pixels and height 2000 pixels
  // The third argument is set to false to indicate that we want a 24-bit bitmap file
  BMP newObj(1600, 2000, false);

  // Set the coordinates of the center of the ellipse to (800, 1000) pixels
  long x_central = 800, y_central = 1000; 

  // Set the x and y radii of the ellipse to 6 times the square root of 64*64
  long rad_x = 6 * sqrt(64 * 64);
  long rad_y = 12 * sqrt(64 * 64);

  // Call the DrawEllipse function with the BMP object and ellipse parameters
  Draw_Ellipse(newObj, x_central, y_central, rad_x, rad_y);

  // Write the BMP object to a file named "output.bmp"
  newObj.write("output.bmp");
  return 0;
}
