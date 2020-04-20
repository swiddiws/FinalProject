/*
Copyright (C) 2006 Pedro Felzenszwalb

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA
*/

#include <cstdio>
#include <cstdlib>
#include <image.h>
#include <misc.h>
#include <pnmfile.h>
#include "segment-image.h"

int main(int argc, char **argv) {
  if (argc != 6) {
    fprintf(stderr, "usage: %s sigma k min input(ppm) output(ppm)\n", argv[0]);
    return 1;
  }
  
  float sigma = atof(argv[1]);
  float k = atof(argv[2]);
  int min_size = atoi(argv[3]);
	
  printf("loading input image.\n");
  image<rgb> *input = loadPPM(argv[4]);
	
  printf("processing\n");
  int num_ccs; 
  image<rgb> *seg = segment_image(input, sigma, k, min_size, &num_ccs); 
  savePPM(seg, argv[5]);

  printf("got %d components\n", num_ccs);
  printf("done! uff...thats hard work.\n");

  return 0;
}

/*

    Note listed below for current understanding of this code.

    Start,
   Note listed below for current understanding of this code.


    IMAGE Object
        A PPM file is imported via a image<rgb> object.
        Basically the class holds a 2-D matrix, that at
        each (x,y) coordinate then holds a rgb object. A
        rgb object simple holds the pixels content in terms 
        of red, green and blue shade from 0-255.

        Attempt at Visualization (hypothetical 3 x 3 pixel image):

               0          1       2
         0  [(0,0,0), (1,0,0), (2,0,0)]
         1  [(0,1,0), (1,1,2), (2,1,2)]
         2  [(0,2,0), (1,2,2), (2,2,4)]

         Such that image->access[0][1] return a rgb object (0,1,0).
         Such that image->access[0][1].r return a int 0.

    Next,

        image is separated to image<float> for each red, blue and green colors.

        Attempt at Visualization (for red image):
             0  1  2
         0  [0, 1, 2]
         1  [0, 1, 2]
         2  [0, 1, 2]
   
   Next,

        looks like a smooth function is called. Cannot figure out the math behind it.
        
        Attempt at Visualization (for red image with sigma=0.5):

             0      1           2
         0  [0, 1072693248, 1073741824]
         1  [0, 1072693248, 1073741824]
         2  [0, 1072693248, 1073741824]

=======
                   0            1         2
         0  [(255,20,30), (10,222,1), (56,4,87)]
         1  [(255,20,30), (10,222,1), (56,78,87)]
         2  [(1,12,13), (54,56,75), (10,86,7)]

         Such that image->access[0][1] return a rgb object (255,20,30).
         Such that image->access[0][1].r return a int 255.

*/
