#ifndef ANIMACION_H
#define ANIMACION_H
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h> 
using namespace sf;
using namespace std;

struct Animacion {
	float color_pantalla=0;
	RectangleShape pantalla;
	
	Time contador;
	Clock reloj;
	int c=0;
	char estado='N';
	float velocidad_animacion=15;
	float duracion_animacion=1;
	bool realizando_animacion=false;
	Animacion(int pantalla_x=1920,int pantalla_y=1080){
		pantalla.setSize(Vector2f(pantalla_x,pantalla_y));
		pantalla.setFillColor(Color(0,0,0,0));
	}
	///
	void draw(RenderWindow &window){
		if(estado=='O'){
			if(!realizando_animacion){
				color_pantalla=0;
				reloj.restart();
				realizando_animacion=true;
			}
			contador=reloj.getElapsedTime();
			if(contador.asSeconds()<duracion_animacion){
				pantalla.setFillColor(Color(0,0,0,color_pantalla));
				window.draw(pantalla);
				if((color_pantalla+velocidad_animacion)<=255){
					color_pantalla+=velocidad_animacion;
					estado='O';
					return;
				}
				pantalla.setFillColor(Color(0,0,0,255));
				window.draw(pantalla);
				realizando_animacion=false;
				estado='N';
			}
		}
		if(estado=='A'){
			if(!realizando_animacion){
				color_pantalla=0;
				reloj.restart();
				realizando_animacion=true;
			}
			contador=reloj.getElapsedTime();
			if(contador.asSeconds()<duracion_animacion){
				
				pantalla.setFillColor(Color(0,0,0,255-color_pantalla));
				window.draw(pantalla);
				if((color_pantalla+velocidad_animacion)<=255){
					color_pantalla+=velocidad_animacion;
					estado='A';
					return;
				}
				pantalla.setFillColor(Color(0,0,0,0));
				window.draw(pantalla);
				estado='N';
				realizando_animacion=false;
			}
		}
	}
};

#endif
