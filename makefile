FILE = mandel

mandel: main.cpp
	c++ -g -o mandel main.cpp -fopenmp -I/usr/include/ImageMagick -lMagick++ -lMagickCore
	mandel 
