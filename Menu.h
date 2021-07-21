#ifndef MENU_H
#define MENU_H
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include <stdlib.h>
#include "Mapa.h"
#include "Animacion.h"
#include "Bomberman.h"
#include <time.h> 
using namespace sf;
using namespace std;
struct Menu {
	
	Text start_text;
	Text logo_text;
	
	Music musica_fondo;

	Sound sonido_eleccion;
	Animacion apertura;
	
	Texture t_background;
	Sprite s_background;
	
	bool inicia_juego=false;
	Bomberman juego;
	Menu(){
		
		musica_fondo.openFromFile("songs/menu/menu.wav");
		sonido_eleccion.setBuffer(buffer_eleccion);
		
		t_background.loadFromFile("textures/background.png");
		s_background.setTexture(t_background);
		s_background.setScale(1,0.85);
		
		musica_fondo.setLoop(true);
		musica_fondo.play();
		//sonido_eleccion.setBuffer(buffer_eleccion);
		
		start_text.setFont(fuente);
		logo_text.setFont(fuente);
		
		start_text.setString("Presiona enter");
		start_text.setCharacterSize(70);
		start_text.setPosition(700,630);
		start_text.setFillColor(Color::White);
		////////////////////////////////////////////////
		logo_text.setString("Bomberman");
		logo_text.setCharacterSize(180);
		
		//logo_text.setPosition(700,500);
		logo_text.setFillColor(Color::White);
		
		////////////////////////////////////////////////
		apertura.duracion_animacion=3.7;
		apertura.velocidad_animacion=0.7;
		apertura.estado='A';
		
	}
	bool inputs(RenderWindow &window, Event &evento){
		while(window.pollEvent(evento)) {
			if(evento.type==Event::KeyPressed){
				if(evento.key.code==Keyboard::Escape){
					window.close();
				}
				if(evento.key.code==Keyboard::Return){
					apertura.pantalla.setFillColor(Color(0,0,0,0));
					window.draw(apertura.pantalla);
					window.display();
					musica_fondo.pause();
					
					inicia_juego=true;
					sonido_eleccion.play();
					//while(sonido_eleccion.getStatus()==Music::Status::Playing);
				}
			}
		}
		return false;
	}
	bool draw(RenderWindow &window, Event &evento){
		if(!inicia_juego){
			window.draw(s_background);
			window.draw(start_text);
			window.draw(logo_text);
			apertura.draw(window);
			window.display();
			inputs(window,evento);
		}
		else{
			juego.draw(window,evento);
		}

	}
};

#endif

