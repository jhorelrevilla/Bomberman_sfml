#ifndef MAPA_H
#define MAPA_H
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Animacion.h"
#include <iostream>
#include <vector>
#include <list>
#include <stdlib.h>
#include <time.h> 
using namespace sf;
using namespace std;

#define map_x 17
#define map_y 13
#define number_maps 3

vector<vector<char>> mapa(map_x,vector<char>(map_y,'N'));

char mapa1[map_y][map_x]={
	{'N','M','M','M','M','M','M','M','M','M','M','M','M','M','M','M','N'},
	{'N','M','M','M','M','M','M','M','M','M','M','M','M','M','M','M','N'},
	{'N','B','B','B','B','B','B','B','B','B','B','B','B','B','B','B','N'},
	{'N','B','c','c','c','c','c','c','c','c','c','c','c','c','c','B','N'},
	{'N','B','c','p','c','p','c','p','c','p','c','p','c','p','c','B','N'},
	{'N','B','c','c','c','c','c','c','c','c','c','c','c','c','c','B','N'},
	{'N','B','c','p','c','p','c','p','c','p','c','p','c','p','c','B','N'},
	{'N','B','c','c','c','c','c','c','c','c','c','c','c','c','c','B','N'},
	{'N','B','c','p','c','p','c','p','c','p','c','p','c','p','c','B','N'},
	{'N','B','c','c','c','c','c','c','c','c','c','c','c','c','c','B','N'},
	{'N','B','c','p','c','p','c','p','c','p','c','p','c','p','c','B','N'},
	{'N','B','c','c','c','c','c','c','c','c','c','c','c','c','c','B','N'},
	{'N','B','B','B','B','B','B','B','B','B','B','B','B','B','B','B','N'}
};
char mapa2[map_y][map_x]={
	{'N','M','M','M','M','M','M','M','M','M','M','M','M','M','M','M','N'},
	{'N','M','M','M','M','M','M','M','M','M','M','M','M','M','M','M','N'},
	{'N','B','B','B','B','B','B','B','B','B','B','B','B','B','B','B','N'},
	{'N','B','c','c','c','c','c','c','c','c','c','c','c','c','c','B','N'},
	{'N','B','c','p','p','p','c','p','c','p','c','p','p','p','c','B','N'},
	{'N','B','c','p','c','c','c','c','c','c','c','c','c','p','c','B','N'},
	{'N','B','c','p','c','p','c','p','c','p','c','p','c','p','c','B','N'},
	{'N','B','c','c','c','c','c','c','c','c','c','c','c','c','c','B','N'},
	{'N','B','c','p','c','p','c','p','c','p','c','p','c','p','c','B','N'},
	{'N','B','c','p','c','c','c','c','c','c','c','c','c','p','c','B','N'},
	{'N','B','c','p','p','p','c','p','c','p','c','p','p','p','c','B','N'},
	{'N','B','c','c','c','c','c','c','c','c','c','c','c','c','c','B','N'},
	{'N','B','B','B','B','B','B','B','B','B','B','B','B','B','B','B','N'}
};
char mapa3[map_y][map_x]={
	{'N','M','M','M','M','M','M','M','M','M','M','M','M','M','M','M','N'},
	{'N','M','M','M','M','M','M','M','M','M','M','M','M','M','M','M','N'},
	{'N','B','B','B','B','B','B','B','B','B','B','B','B','B','B','B','N'},
	{'N','B','c','c','c','c','c','c','c','c','c','c','c','c','c','B','N'},
	{'N','B','c','c','c','c','c','c','c','c','c','c','c','c','c','B','N'},
	{'N','B','p','p','p','p','p','c','c','c','p','p','p','p','p','B','N'},
	{'N','B','p','c','c','c','c','c','c','c','c','c','c','c','p','B','N'},
	{'N','B','p','c','c','c','c','c','c','c','c','c','c','c','p','B','N'},
	{'N','B','p','c','c','c','c','c','c','c','c','c','c','c','p','B','N'},
	{'N','B','p','p','p','p','p','c','c','c','p','p','p','p','p','B','N'},
	{'N','B','c','c','c','c','c','c','c','c','c','c','c','c','c','B','N'},
	{'N','B','c','c','c','c','c','c','c','c','c','c','c','c','c','B','N'},
	{'N','B','B','B','B','B','B','B','B','B','B','B','B','B','B','B','N'}
};
//
float scale_x,scale_y;
float texture_x,texture_y;
vector<pair<int,int>> explosiones;
Animacion animacion;
//--------TEXTURAS
Texture t_cesped;
Texture t_roca;
Texture t_piedra;
Texture t_ladrillo;
Texture t_bomberman;
Texture t_bomberman_left;
Texture t_bomberman_right;
Texture t_bomberman_up;
Texture t_bomba;
Texture t_explosion;	
Texture t_muerte;
Texture t_puerta;
Texture t_pwfuego;
//--------FONTS
Font fuente;
//--------BUFFER SONIDO
//
SoundBuffer bf_sound_item;
SoundBuffer bf_sound_colocar_bomba;

//good
SoundBuffer buffer_eleccion;
SoundBuffer buffer_pasos;
SoundBuffer buffer_muerte;
SoundBuffer buffer_explosion;
////////////////////////////////////////////////////////////////////////////
void cargar_fuentes(){
	fuente.loadFromFile("fonts/Titulo.ttf");
}
////////////////////////////////////////////////////////////////////////////
void cargar_sonidos(){
	bf_sound_item.loadFromFile("sounds/pick_item.wav");
	bf_sound_colocar_bomba.loadFromFile("sounds/poner_bomba.wav");
	buffer_explosion.loadFromFile("sounds/explosion.wav");
	buffer_pasos.loadFromFile("sounds/pasos.wav");
	buffer_muerte.loadFromFile("sounds/muerte.wav");
	buffer_eleccion.loadFromFile("sounds/eleccion.wav");
}
////////////////////////////////////////////////////////////////////////////
void cargar_texturas1(){
	t_cesped.loadFromFile("textures/nivel1/cesped.png");
	t_roca.loadFromFile("textures/nivel1/roca.png");
	t_piedra.loadFromFile("textures/nivel1/piedra.png");
	t_ladrillo.loadFromFile("textures/nivel1/ladrillo.png");
	t_bomberman.loadFromFile("textures/nivel1/bomber.png");
	t_bomberman_left.loadFromFile("textures/nivel1/bomber_left.png");
	t_bomberman_right.loadFromFile("textures/nivel1/bomber_right.png");
	t_bomberman_up.loadFromFile("textures/nivel1/bomber_up.png");
	t_bomba.loadFromFile("textures/nivel1/bomba.png");
	t_explosion.loadFromFile("textures/nivel1/explosion.png");
	t_muerte.loadFromFile("textures/nivel1/tumba.png");
	t_puerta.loadFromFile("textures/nivel1/puerta.png");
	t_pwfuego.loadFromFile("textures/nivel1/pw_fuego.png");
}
//--------------------
void cargar_dimensiones(float window_porcentaje){
	scale_x=((1920*window_porcentaje)/map_x)/200;
	scale_y=((1080*window_porcentaje)/map_y)/200;
	
	texture_x=200.0*scale_x;
	texture_y=200.0*scale_y;
}
//--------------------
void mostrar_mapa_consola(){
	for(int y=0;y<map_y;++y){
		for(int x=0;x<map_x;++x){
			cout<<mapa[y][x]<<" ";
		}
		cout<<"\n";
	}
	cout<<"/////////////////////////////"<<endl;
}
//--------------------
void cargar_nivel(int nivel,int &cant_l,Music &musica_fondo,Vector2i &posj1,Vector2i &posj2){
	switch(nivel){
	case 1:
		for(int y=0;y<map_y;++y){
			for(int x=0;x<map_x;++x){
				mapa[y][x]=mapa1[y][x];
			}
		}
		cant_l=30;
		break;
	case 2:
		for(int y=0;y<map_y;++y){
			for(int x=0;x<map_x;++x){
				mapa[y][x]=mapa2[y][x];
			}
		}
		cant_l=35;
		break;
	case 3:
		for(int y=0;y<map_y;++y){
			for(int x=0;x<map_x;++x){
				mapa[y][x]=mapa3[y][x];
			}
		}
		cant_l=40;
		break;
	}
	
	float volumen=2;	
	
	musica_fondo.openFromFile("sounds/musica_fondo.wav");
	musica_fondo.setVolume(volumen);
	musica_fondo.setLoop(true);
	posj1.x=2;posj1.y=3;
	posj2.x=14;posj2.y=11;
}
	
#endif

