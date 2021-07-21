#ifndef POWERUP_H
#define POWERUP_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <stdlib.h>
#include "Mapa.h" 
using namespace sf;
using namespace std;

struct Powerup {
	int x,y;
	
	Sprite s_pwup;
	
	//---------------------//
	Powerup(int x=0,int y=0){
		
		s_pwup.setTexture(t_pwfuego);
		s_pwup.setScale(scale_x,scale_y);
		s_pwup.setPosition(texture_x*x,texture_y*y);
		
		this->x=x;
		this->y=y;
		//mapa1[y][x]='S';
	}
	void draw(RenderWindow &window){
		window.draw(s_pwup);
	}
	void set_position(int x, int y){
		s_pwup.setPosition(texture_x * x,
							 texture_y * y);
		this->x=x;
		this->y=y;
	}
};

#endif

