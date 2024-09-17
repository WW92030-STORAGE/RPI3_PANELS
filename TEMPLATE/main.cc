// -*- mode: c++; c-basic-offset: 2; indent-tabs-mode: nil; -*-
// Small example how to use the library.
// For more examples, look at demo-main.cc
//
// This code is public domain
// (but note, that the led-matrix library this depends on is GPL v2)

#include "led-matrix.h"

#include "stdlib/matrices.h"
#include "stdlib/panels.h"

#include "include/grid.h"

using rgb_matrix::RGBMatrix;
using rgb_matrix::Canvas;

std::vector<std::vector<std::vector<bool>>> animation{grid0, grid1, grid2, grid3, grid4, grid5, grid6, grid7, grid8};
int blinkdelay = 0;
int blinkthreshold = 0;
static void anim_loop(int color) {
  std::vector<std::vector<int>> col(ROWS, std::vector<int>(COLS));
  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLS; j++) col[i][j] = color;
  }
  delay(100);
  // Serial.println(rand() % 1024);
  disp(col, grid0);

  blinkdelay++;
  if (blinkdelay >= blinkthreshold) {
    blinkdelay = 0;
    blinkthreshold = (int)(runif(16, 64));
    playAnimation(col, animation, 20, false);
    playAnimation(col, animation, 20, true);
  }
}

int main(int argc, char *argv[]) {
  matrixsetup(argc, argv);

  if (canvas == NULL)
    return 1;

  while (!interrupt_received) {
    // EVERYTHING MEANINGFUL GOES HERE
    anim_loop(0xFFFFFF);
  }

  // Animation finished. Shut down the RGB matrix.
  canvas->Clear();
  delete canvas;

  return 0;
}
