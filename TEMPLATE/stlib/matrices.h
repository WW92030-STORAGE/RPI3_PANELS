#ifndef NORMALEXISTING_MATRICES_H
#define NORMALEXISTING_MATRICES_H

#include "led-matrix.h"

#include <unistd.h>
#include <math.h>
#include <iostream>
#include <signal.h>
#include <ctime>
#include <vector>
#include <cstdint>

using rgb_matrix::RGBMatrix;
using rgb_matrix::Canvas;

// Global Variables

Canvas* canvas = nullptr;
const int ROWS = 32;
const int COLS = 128;

// Setup the matrices

volatile bool interrupt_received = false;
static void InterruptHandler(int signo) {
  interrupt_received = true;
}

void matrixsetup(int argc, char *argv[]) {
  srand(std::time(0));
  RGBMatrix::Options defaults;
  defaults.hardware_mapping = "regular";  // or e.g. "adafruit-hat"
  defaults.rows = ROWS;
  defaults.cols = COLS;
  defaults.chain_length = 1;
  defaults.parallel = 1;
  defaults.show_refresh_rate = true;
  canvas = RGBMatrix::CreateFromFlags(&argc, &argv, &defaults);

    // It is always good to set up a signal handler to cleanly exit when we
  // receive a CTRL-C for instance. The DrawOnCanvas() routine is looking
  // for that.
  signal(SIGTERM, InterruptHandler);
  signal(SIGINT, InterruptHandler);
}

// RNG

double rng() { // Random uniform distribution
  return rand() / (RAND_MAX + 1.0);
}

double runif(double a, double b) { // Random uniform [a, b)
  return (rng() * (b - a)) + a;
}

std::vector<uint8_t> protogen() {
	std::vector<uint8_t> res(3, 0);
	for (int i = 0; i < 3; i++) res.push_back(runif(0, 256));
	return res;
}

std::vector<uint8_t> protogenfullhue() {
	std::vector<uint8_t> res(3, 0);
	uint8_t partition = runif(0, 256);
	int pos = runif(0, 6);
	switch (pos) {
    case 0:
      res = std::vector<uint8_t>({255, partition, 0});
    case 1:
      res = std::vector<uint8_t>({255 - partition, 255, 0});
    case 2:
      res = std::vector<uint8_t>({0, 255, partition});
    case 3:
      res = std::vector<uint8_t>({0, 255 - partition, 255});
    case 4:
      res = std::vector<uint8_t>({partition, 0, 255});
    default:
      res = std::vector<uint8_t>({255, 255 - partition, 0});
  }
	return res;
}

std::vector<uint8_t> fromint(int x) {
	return std::vector<uint8_t>({(x>>16) % 256, (x>>8) % 256, x % 256});
}

int fromvec(std::vector<uint8_t> color) {
	return ((color[0])<<16) + ((color[1])<<16) + color[2];
}

// Displaying outputs

static void disp(std::vector<std::vector<int>> col, std::vector<std::vector<bool>> grid) {
  canvas->Fill(0, 0, 0);

  for (int i = 0; i < col.size() && i < grid.size(); i++) {
	for (int j = 0; j < col[i].size() && j < grid[i].size(); j++) {
		std::vector<uint8_t> color = fromint(col[i][j]);
		if (grid[i][j]) canvas->SetPixel(j, i, color[0], color[1], color[2]);
	}
  }
}

void delay(int d) {
	usleep(d * 1000);
}

void playAnimation(std::vector<std::vector<int>> col, std::vector<std::vector<std::vector<bool>>> anim, int d, bool backward) {
  for (int i = 0; i < anim.size(); i++) {
    int index = (backward) ? (anim.size() - 1 - i) : i;
    disp(col, anim[index]);
    delay(d);
  }
}

#endif
