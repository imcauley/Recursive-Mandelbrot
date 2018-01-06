/*
Name: Isaac McAuley 
E-Mail: imcau971@mtroyal.ca
Course: COMP 1633 - 001
Instructor: P. Pospisil
Assignment: 3
File: main.cpp
*/

#include <Magick++.h>
#include <cmath>
#include <iostream>

using namespace std;
using namespace Magick;


struct complex
{
    double real;
    double imaginary;
};

int checkNum(complex c, complex x, int itteration, int maxIt);
double mag(complex x);
void itX(int x,  int imageDim, int maxIt, Image&mandel);
void itY(int x, int y,  int imageDim, int maxIt, Image&mandel);

int main()
{
    
    Image mandel;
    int imageDim;
    int maxIt;
    string filename;
    
    cout << "=== Mandelbrot Image Generator ===" << endl;
    cout << endl;
    cout << "Enter square image dimension: ";
    cin >> imageDim;
    cout << "Enter maximum iteration: ";
    cin >> maxIt;

    mandel.extent(Geometry(imageDim,imageDim));
    itX(0, imageDim, maxIt, mandel);

    mandel.write(“mandel.png");

    return 0;
}

/*
Name: itX

Purpose: iterate recursively over every row of the image

Details: 
         iterates from x to imageDim by adding to x and calling
	 itself

Parameters: 
         int x: starting point
	 int imageDim: end point
	 int maxIt: max iterations for the mandelbrot set
	 Image mandel: final image

Return: Image mandel
 */
void itX(int x, int imageDim, int maxIt, Image&mandel)
{
    if(x < imageDim)
    {
	itY(x, 0, imageDim, maxIt, mandel);
	x++;
	itX(x, imageDim, maxIt, mandel);
    }
}

/*
Name: itY

Purpose: iterate over every pixel in a row

Details:
         goes through every pixel and checks if it is in the mandelbrot
	 set. if it is it will be pure black. if it is outside it will
	 scale the iteration to be a brightness of red and set the
	 pixel to be equal to that.
	 before a pixel value goes into the checkNum function it is 
	 scaled by the function:
	                f(x) = (x -(max/2)) / (max/3)
	 the first part of the function maps 0 to -max/2 and max to 
	 max/2 and max/3 scales the entire image down to a factor of
	 3

Parameters:
         int x: x pixel
	 int y: y pixel value
	 int imageDim: max size
	 int maxIt: max mandelbrot iteration
	 Image mandel: final image

Return: Image mandel
 */
void itY(int x, int y,  int imageDim, int maxIt, Image&mandel)
{
    complex position;
    complex start;
    int iteration;
    Color black = "black";
    Color white = "white";

    if(y < imageDim)
    {
	position.real = (x - (imageDim/2.0)) / (imageDim/3.0) -0.5;
	position.imaginary = (y - (imageDim/2.0)) / (imageDim/3.0);
	
	start.real = 0.0;
	start.imaginary = 0.0;

	iteration = checkNum(start, position, 0, maxIt);

	if(iteration == maxIt)
	    mandel.pixelColor(x, y, black);
	else
	{
	    double value = (iteration * 1.0 / maxIt);
	    ColorRGB fillColor = ColorRGB(value, 0.0, value);
	    mandel.pixelColor(x, y, fillColor);
	}

	y++;
	itY(x, y, imageDim, maxIt, mandel);
    }
}

/*
Name: checkNum

Purpose: check to see if a number is in the mandlebrot set and return how many
         iterations it takes to find out.

Details:
         this function is based off the equation:
	             f(z_n + 1) = z_n^2 + c
	 if any c can be iterated with n z's then c is in the set

         the first check is to see if the iteration is above the user specified
	 max iteration. if it is not it will iterate the z value and check if
	 it is over a magnitude of 2. if it is larger it will break out of the
	 function and return the iteration. 
 
Parameters:
         complex z: iterating complex number
	 complex c: pixel position
	 iteration: how many times the function has ran for a number
	 maxIt: max number of iterations it will check for

Return: integer of how many iterations it takes to find if a number is in the
        mandlebrot set.
 */
int checkNum(complex z, complex c, int iteration, int maxIt)
{
    int inMandel;
    complex temp;

    if(iteration >= maxIt)
	inMandel = iteration;
    else
    {
	temp.real = (z.real * z.real) - (z.imaginary * z.imaginary) + c.real;
	temp.imaginary = (2 * z.real * z.imaginary) + c.imaginary;
	
	if(mag(temp) >= 2)
	    inMandel = iteration;
	else
	    inMandel = checkNum(temp, c, iteration + 1, maxIt);
    }

    return inMandel;
}

/*
Name: mag

Purpose: get the magnitude of a complex number

Details:
         uses the pythagorean theorum of the real and imaginary
	 parts of a complex number to find the length

Parameters: complex number c

Return: double magnitude (length to position)
 */
double mag(complex c)
{
    double magnitude;

    magnitude = (c.real * c.real) + (c.imaginary * c.imaginary);
    magnitude = sqrt(magnitude);

    return magnitude;
}
