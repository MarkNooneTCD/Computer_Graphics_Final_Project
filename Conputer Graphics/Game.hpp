#pragma once
#include "Constants.hpp"
#include "Shader.hpp"
#include "Mesh.hpp"
#include "Geometry.hpp"

void display();
void updateScene();
void keypress(int key, int x, int y);
void processNormalKeys(unsigned char key, int x, int y);
void init();