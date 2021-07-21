#ifndef LADRILLO_H
#define LADRILLO_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <stdlib.h>
#include "Mapa.h"
#include <time.h> 
using namespace sf;
using namespace std;

struct Ladrillo {
	int x,y;

	Sprite s_pared;
	bool contiene_algo=false;
	//---------------------//
	Ladrillo(int x=0,int y=0){
		
		s_pared.setTexture(t_ladrillo);
		s_pared.setScale(scale_x,scale_y);
		s_pared.setPosition(texture_x*x,texture_y*y);
		
		this->x=x;
		this->y=y;
		mapa[y][x]='l';
	}
	void draw(RenderWindow &window){
		window.draw(s_pared);
	}
};

#endif

