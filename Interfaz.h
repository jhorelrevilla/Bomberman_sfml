#ifndef INTERFAZ_H
#define INTERFAZ_H
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include <stdlib.h>
#include "Mapa.h"

#include <time.h> 
using namespace sf;
using namespace std;

struct Interfaz {
	Text puntaje_1;
	Text puntaje_2;
	Sprite s_personaje1;
	Sprite s_personaje2;
	
	vector<Sprite> cant_bombas_p1;
	vector<Sprite> cant_bombas_p2;
	int bombas_p1=0;
	int bombas_p2=0;
	Interfaz(){
		Vector2i pos_player1(1,1);
		Vector2i pos_player2(9,1);
		//letras
		puntaje_1.setFont(fuente);
		puntaje_2.setFont(fuente);
		
		puntaje_1.setCharacterSize(70);
		puntaje_2.setCharacterSize(70);
		
		puntaje_1.setColor(Color::White);
		puntaje_2.setColor(Color::White);
		
		puntaje_1.setPosition(texture_x * (pos_player1.x+1),
							  texture_y * pos_player1.y);
		puntaje_2.setPosition(texture_x * (pos_player2.x+1),
							  texture_y * pos_player2.y);
		//Sprite
		s_personaje1.setTexture(t_bomberman);
		s_personaje1.setScale(scale_x,scale_y);
		s_personaje1.setPosition(texture_x * pos_player1.x,
								texture_y * pos_player1.y);
		s_personaje1.setColor(Color(125,125,255));
		
		s_personaje2.setTexture(t_bomberman);
		s_personaje2.setScale(scale_x,scale_y);
		s_personaje2.setPosition(texture_x * pos_player2.x,
								texture_y * pos_player2.y);
		s_personaje2.setColor(Color(255,125,125));
		///
		cant_bombas_p1.reserve(3);
		for(int i=0;i<3;++i){
			Sprite bomba_temporal;
			bomba_temporal.setTexture(t_bomba);
			bomba_temporal.setScale(scale_x,scale_y);
			bomba_temporal.setPosition(texture_x * (pos_player1.x+i),
									 texture_y * (pos_player1.y-1));
			cant_bombas_p1.push_back(bomba_temporal);
		}
			
		cant_bombas_p2.reserve(3);
		for(int i=0;i<3;++i){
			Sprite bomba_temporal;
			bomba_temporal.setTexture(t_bomba);
			bomba_temporal.setScale(scale_x,scale_y);
			bomba_temporal.setPosition(texture_x * (pos_player2.x+i),
									   texture_y * (pos_player2.y-1));
			cant_bombas_p2.push_back(bomba_temporal);
		}
	}
		
	void set_puntaje(Personaje *player1,Personaje *player2){		
		string p1=to_string(player1->puntaje);
		string p2=to_string(player2->puntaje);
		puntaje_1.setString(p1);
		puntaje_2.setString(p2);
		bombas_p1=3-player1->cantidad_bombas;
		bombas_p2=3-player2->cantidad_bombas;
	}
		
	void draw(RenderWindow &window){
		window.draw(puntaje_1);
		window.draw(puntaje_2);
		window.draw(s_personaje1);
		window.draw(s_personaje2);
		for(int i=0;i<bombas_p1;++i)
			window.draw(cant_bombas_p1[i]);
		for(int i=0;i<bombas_p2;++i)
			window.draw(cant_bombas_p2[i]);
		//window.draw(s_player2);
	}
};

#endif

