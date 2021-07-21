#ifndef PUERTA_H
#define PUERTA_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <stdlib.h>
#include "Mapa.h" 
using namespace sf;
using namespace std;

struct Puerta {
	int x,y;
	
	Sprite s_puerta;
	SoundBuffer buffer_puerta;
	Sound sonido_puerta;
	//---------------------//
	Puerta(int x=0,int y=0){
		buffer_puerta.loadFromFile("sounds/puerta.wav");
		sonido_puerta.setBuffer(buffer_puerta);
		
		s_puerta.setTexture(t_puerta);
		s_puerta.setScale(scale_x,scale_y);
		s_puerta.setPosition(texture_x*x,texture_y*y);
		
		this->x=x;
		this->y=y;
		//mapa1[y][x]='S';
	}
	void draw(RenderWindow &window){
		window.draw(s_puerta);
	}
	void set_position(int x, int y){
		s_puerta.setPosition(texture_x * x,
									texture_y * y);
		this->x=x;
		this->y=y;
	}
};

#endif

