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
#include "image.h"
#include "misc.h"
#include "pnmfile.h"
#include "segment-image.h"

image<rgb>* generate_test_ppm() {
    int h = 100;
    int w = 100;
    image<rgb>* test_im = new image<rgb>(h, w);
    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            rgb t = rgb();
            t.r = x;
            t.g = y;
            t.b = x*y;
            test_im->access[y][x] = t;
        }
    }
    savePPM(test_im, "custom-ppm-for-testing.ppm");
    return test_im;
}

int main(int argc, char **argv) {
  if (argc != 6) {
    fprintf(stderr, "usage: %s sigma k min input(ppm) output(ppm)\n", argv[0]);
    return 1;
  }
  
  float sigma = atof(argv[1]);
  float k = atof(argv[2]);
  int min_size = atoi(argv[3]);
	
  printf("loading input image.\n");
  // image<rgb> *input = loadPPM(argv[4]);

  image<rgb>* test_im = generate_test_ppm();

  printf("processing\n");
  int num_ccs; 
  image<rgb>* seg = segment_image(test_im, sigma, k, min_size, &num_ccs);
  savePPM(seg, argv[5]);

  printf("got %d components\n", num_ccs);
  printf("done! uff...thats hard work.\n");
  
  return 0;
}
