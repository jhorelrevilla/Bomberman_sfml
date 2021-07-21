#ifndef BOMBA_H
#define BOMBA_H
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include <stdlib.h>
#include "Mapa.h"
#include <time.h> 
using namespace sf;
using namespace std;

struct Bomba{
	//animacion
	Clock reloj;
	Time contador;
	int color_g_b=0;	
	bool condicion=true;
	int velocidad=8;
	char estado='N';
	//sprites y texturas
	Sprite s_bomba;
	vector<Sprite> restos_explosion;
	vector<pair<int,int>> pos_paredes;
	//posiciones 
	int x,y;
	//explosion
	int long_bomba=2;
	float crecimiento_bomba=0.0001;
	float new_scale_x;
	float new_scale_y;
	int num_bomba;
	Sound *sonido_bomba;
	//--------------------
	Bomba(Sound *sonido_bomba,int long_bomba,int x=0,int y=0){
		
		this->x=x;
		this->y=y;
		this->num_bomba=num_bomba;
		this->sonido_bomba=sonido_bomba;
		
		mapa[y][x]='b';
		s_bomba.setTexture(t_bomba);
		s_bomba.setScale(scale_x,scale_y);
		s_bomba.setPosition(texture_x * x,texture_y * y);
		
		new_scale_x=scale_x;
		new_scale_y=scale_y;
		this->long_bomba=long_bomba;
		

	}
	void calcular_paredes_choque(){
		for(int i=1;i<long_bomba;++i){//derecha
			if(mapa[y][x+i]=='p' || mapa[y][x+i]=='B' )
				break;
			//if(mapa1[y][x+i]=='c' || mapa1[y][x+i]=='l' || mapa1[y][x+i]=='j'){
			Sprite explosion;
			explosion.setTexture(t_explosion);
			explosion.setScale(scale_x,scale_y);
			explosion.setPosition(texture_x * (x+i),texture_y * y);
			restos_explosion.push_back(explosion);
			if(mapa[y][x+i]=='l'){
				pair<int,int> t_pair(y,x+i);
				pos_paredes.push_back(t_pair);
				break;
			}
			//}
		}
		for(int i=1;i<long_bomba;++i){//izquierda
			if(mapa[y][x-i]=='p' || mapa[y][x-i]=='B' )
				break;
			//if(mapa1[y][x-i]=='c' || mapa1[y][x-i]=='l' || mapa1[y][x-i]=='j' ){
			Sprite explosion;
			explosion.setTexture(t_explosion);
			explosion.setScale(scale_x,scale_y);
			explosion.setPosition(texture_x * (x-i),texture_y * y);
			restos_explosion.push_back(explosion);
			if(mapa[y][x-i]=='l'){
				pair<int,int> t_pair(y,x-i);
				pos_paredes.push_back(t_pair);
				break;
			}
			//}
		}
		for(int i=1;i<long_bomba;++i){//arriba
			if(mapa[y+i][x]=='p' || mapa[y+i][x]=='B')
				break;
			//if(mapa1[y+i][x]=='c' || mapa1[y+i][x]=='l' || mapa1[y+i][x]=='j' ){
			Sprite explosion;
			explosion.setTexture(t_explosion);
			explosion.setScale(scale_x,scale_y);
			explosion.setPosition(texture_x * x,texture_y * (y+i));
			restos_explosion.push_back(explosion);
			if(mapa[y+i][x]=='l'){
				pair<int,int> t_pair(y+i,x);
				pos_paredes.push_back(t_pair);
				break;
			}
			//}
		}
		for(int i=1;i<long_bomba;++i){//abajo
			if(mapa[y-i][x]=='p' || mapa[y-i][x]=='B')
				break;
			//if(mapa1[y-i][x]=='c' || mapa1[y-i][x]=='l' || mapa1[y-i][x]=='j'){
			Sprite explosion;
			explosion.setTexture(t_explosion);
			explosion.setScale(scale_x,scale_y);
			explosion.setPosition(texture_x * x,texture_y * (y-i));
			restos_explosion.push_back(explosion);
			if(mapa[y-i][x]=='l'){
				pair<int,int> t_pair(y-i,x);
				pos_paredes.push_back(t_pair);
				break;
			}
			//}
			
		}
	}
	bool draw(RenderWindow &window){
		contador=reloj.getElapsedTime();
		if(contador.asSeconds()<3 && estado=='N'){
			new_scale_x+=crecimiento_bomba;
			new_scale_y+=crecimiento_bomba;
			s_bomba.setScale(new_scale_x,new_scale_y);
			s_bomba.setColor(Color(255,255-color_g_b,255-color_g_b));
			window.draw(s_bomba);
			color_g_b+=velocidad;
			if(255-color_g_b<=0){
				color_g_b=0;
			}
			return false;
		}
		//bomba explota
		if(estado=='N'){
			calcular_paredes_choque();
			reloj.restart();
			estado='E';
			sonido_bomba->play();
			window.draw(s_bomba);
			return false;
			
		}
		if(contador.asSeconds()<0.31 && estado=='E'){
			s_bomba.setTexture(t_explosion);
			s_bomba.setColor(Color(255,255,255));
			window.draw(s_bomba);
			mapa[y][x]='x';
			for(int i=0;i<restos_explosion.size();++i){
				window.draw(restos_explosion[i]);
				Vector2f posicion_explosiones=restos_explosion[i].getPosition();
				posicion_explosiones.x/=texture_x;
				posicion_explosiones.y/=texture_y;
				mapa[(int)posicion_explosiones.y][(int)posicion_explosiones.x]='x';
			}
			return false;
		}
		
		//eliminar Ladrillo
		if(pos_paredes.size()){
			for(int i=0;i<pos_paredes.size();++i){
				explosiones.push_back(pos_paredes[i]);
			}
		}
		//eliminar explosiones
		mapa[y][x]='c';
		for(int i=0;i<restos_explosion.size();++i){
			Vector2f posicion_explosiones=restos_explosion[i].getPosition();
			posicion_explosiones.x/=texture_x;
			posicion_explosiones.y/=texture_y;
			//cout<<posicion_explosiones.x<<endl;
			mapa[(int)posicion_explosiones.y][(int)posicion_explosiones.x]='c';
		}
		
		return true;
	}
};

#endif
