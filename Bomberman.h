#ifndef BOMBERMAN_H
#define BOMBERMAN_H
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h> 

#include "Mapa.h"
#include "Personaje.h"
#include "Ladrillo.h"
#include "Bomba.h"
#include "Puerta.h"
#include "Powerup.h"
#include "Interfaz.h"
#include <string>
using namespace sf;
using namespace std;



class Bomberman {
public:
	//--------------------
	vector<Sprite> cesped_mapa;
	vector<Sprite> roca_mapa;
	vector<Sprite> piedra_mapa;
	vector<Ladrillo> ladrillo_mapa;
	vector<Powerup> poderes;
	
	Personaje * player1=nullptr;
	Personaje * player2=nullptr;
	Puerta * puerta_mapa=nullptr;
	
	Music musica_fondo;
	
	SoundBuffer buffer_bajar_escaleras;
	Sound sonido_bajar_escaleras;
	
	Interfaz interfaz;
	
	Vector2i spawn_pj1;
	Vector2i spawn_pj2;
	
	int cantidad_ladrillos;
	int cantidad_pwup=5;
	int nivel=1;
	
	bool pausa_entradas=false;
	//--------------------
	Bomberman(){


		cargar_nivel(nivel,cantidad_ladrillos,musica_fondo,
					 spawn_pj1,spawn_pj2);
		//Generar mapa del juego a partir del mapa
		generar_mapa();
		//jugador 1
		player1=new Personaje(spawn_pj1.x,spawn_pj1.y);
		player1->change_color(125,125,255);
		
		//jugador 2
		player2=new Personaje(spawn_pj2.x,spawn_pj2.y);
		player2->change_color(255,125,125);
		
		if(!buffer_bajar_escaleras.loadFromFile("sounds/pasos_escalera.wav")){
			std::cout<<"error\n";
		}
		sonido_bajar_escaleras.setBuffer(buffer_bajar_escaleras);
		
		//
		cesped_mapa.reserve(60);
		roca_mapa.reserve(60);
		piedra_mapa.reserve(60);
		ladrillo_mapa.reserve(cantidad_ladrillos);
		

		
		
		//generar ladrillos
		ladrillos_random();
		
		//generar poderes
		poderes.reserve(cantidad_pwup);
		pw_aleatorio();
		//generar puerta 
		puerta_mapa=new Puerta;
		puerta_aleatoria();
		
		
		
		
		
	}

	//----------------------------------------------
	void generar_mapa(){
		for(int i=0;i<map_y;++i){
			for(int j=0;j<map_x;++j){
				//cesped
				if(mapa[i][j]=='c'){
					Sprite tempo;
					tempo.setTexture(t_cesped);
					tempo.setScale(scale_x,scale_y);
					tempo.setPosition(texture_x*j,texture_y*i);
					cesped_mapa.push_back(tempo);
					continue;
				}
				//roca
				if(mapa[i][j]=='B'){
					Sprite tempo;
					tempo.setTexture(t_roca);
					tempo.setScale(scale_x,scale_y);
					tempo.setPosition(texture_x*j,texture_y*i);
					roca_mapa.push_back(tempo);
					continue;
				}
				//piedra
				if(mapa[i][j]=='p'){
					Sprite tempo;
					tempo.setTexture(t_piedra);
					tempo.setScale(scale_x,scale_y);
					tempo.setPosition(texture_x*j,texture_y*i);
					piedra_mapa.push_back(tempo);
					continue;
				}
			}
		}
	}
	//----------------------------------------------
	void puerta_aleatoria(){
		srand (time(NULL));
		for(int i=0;i<ladrillo_mapa.size();++i){
			int ladrillo_aleatorio = rand() % ladrillo_mapa.size();
			if(! ladrillo_mapa[ladrillo_aleatorio].contiene_algo){
				puerta_mapa->set_position(ladrillo_mapa[ladrillo_aleatorio].x,ladrillo_mapa[ladrillo_aleatorio].y);
				ladrillo_mapa[ladrillo_aleatorio].contiene_algo=true;
				//cout<<ladrillo_mapa[ladrillo_aleatorio].x<<" "<<ladrillo_mapa[ladrillo_aleatorio].y<<endl;
				break;
			}
		}
	}
	void pw_aleatorio(){
		srand (time(NULL));
		int ladrillo_aleatorio;
		int cont=0;
		while(cont<cantidad_pwup){
			ladrillo_aleatorio= rand() % ladrillo_mapa.size();
			if(! ladrillo_mapa[ladrillo_aleatorio].contiene_algo){
				Powerup pw_temporal(ladrillo_mapa[ladrillo_aleatorio].x,
									ladrillo_mapa[ladrillo_aleatorio].y);
				poderes.push_back(pw_temporal);
				//cout<<"ladrillo en "<<ladrillo_mapa[ladrillo_aleatorio].x<<" "<<ladrillo_mapa[ladrillo_aleatorio].y<<endl;
				ladrillo_mapa[ladrillo_aleatorio].contiene_algo=true;
				cont++;
			}
		}
		//cout<<"puerta en "<<ladrillo_mapa[ladrillo_aleatorio].x<<" "<<ladrillo_mapa[ladrillo_aleatorio].y<<endl;
	}
	//----------------------------------------------
	void ladrillos_random(){
		int cant_acertados=0;
		srand (time(NULL));
		
		while(cant_acertados!=cantidad_ladrillos){
			int x_rand = rand() % map_x + 1;
			int y_rand = rand() % map_y + 1;
			
			if((x_rand==player1->x && y_rand==player1->y) || (x_rand==player1->x+1 && y_rand==player1->y)
				|| (x_rand==player1->x && y_rand==player1->y+1))
				continue;
			if((x_rand==player2->x && y_rand==player2->y) || (x_rand==player2->x-1 && y_rand==player2->y)
				|| (x_rand==player2->x && y_rand==player2->y-1))
				continue;
			
			//cout<<x_rand<<" - "<<y_rand<<endl;
			if(mapa[y_rand][x_rand]=='c'){
				Ladrillo l_temporal(x_rand,y_rand);
				ladrillo_mapa.push_back(l_temporal);
				cant_acertados++;
			}
		}
		
	}
	//----------------------------------------------
	void draw_fondo(RenderWindow &window){
		for(int i=0;i<cesped_mapa.size();++i){
			window.draw(cesped_mapa[i]);
		}
		for(int i=0;i<roca_mapa.size();++i){
			window.draw(roca_mapa[i]);
		}
		for(int i=0;i<piedra_mapa.size();++i){
			window.draw(piedra_mapa[i]);
		}
	}
	//----------------------------------------------
	void buscar_explosiones(int x,int y){
		//cout<<"busvando "<<x <<" "<<y<<endl;
		for(int i=0;i<ladrillo_mapa.size();++i){
			if(ladrillo_mapa[i].x==x && ladrillo_mapa[i].y==y){
				ladrillo_mapa.erase(ladrillo_mapa.begin()+i);
				mapa[y][x]='c';
			}
		}
	}
	//----------------------------------------------
	void mostar_ladrillos(){
		for(int i=0;i<ladrillo_mapa.size();++i){
			cout<<ladrillo_mapa[i].x<<" "<<ladrillo_mapa[i].y<<endl;
		}
		cout<<"////////////////////////////////////////////////"<<endl;
	}
	//----------------------------------------------
	void inputs(RenderWindow &window, Event &evento){
		while(window.pollEvent(evento)) {
			if(evento.type == Event::Closed){
				window.close();	
			}
				
			if(evento.type==Event::KeyPressed){
				if(pausa_entradas)
					return;
				//jugador 1
				if(evento.key.code==Keyboard::Escape){
					clear();
					window.close();
				}
				if(evento.key.code==Keyboard::E ){
					player1->agregar_bomba();
				}
				if(evento.key.code==Keyboard::W){
					player1->s_bomberman.setTexture(t_bomberman_up);
					player1->mover(0,-1);
				}
				if(evento.key.code==Keyboard::S){
					player1->s_bomberman.setTexture(t_bomberman);
					player1->mover(0,1);
				}
				if(evento.key.code==Keyboard::A){
					player1->s_bomberman.setTexture(t_bomberman_left);
					player1->mover(-1,0);
				}
				if(evento.key.code==Keyboard::D){
					player1->s_bomberman.setTexture(t_bomberman_right);
					player1->mover(1,0);
				}
				//jugador2 ?
				if(evento.key.code==Keyboard::O){
					player2->agregar_bomba();
				}
				if(evento.key.code==Keyboard::I){
					player2->s_bomberman.setTexture(t_bomberman_up);
					player2->mover(0,-1);
				}
				if(evento.key.code==Keyboard::K){
					player2->s_bomberman.setTexture(t_bomberman);
					player2->mover(0,1);
				}
				if(evento.key.code==Keyboard::J){
					player2->s_bomberman.setTexture(t_bomberman_left);
					player2->mover(-1,0);
				}
				if(evento.key.code==Keyboard::L){
					player2->s_bomberman.setTexture(t_bomberman_right);
					player2->mover(1,0);
				}
			}
		}
	}
	//----------------------------------------------
	void clear(){
		cesped_mapa.clear();
		piedra_mapa.clear();
		ladrillo_mapa.clear();
		roca_mapa.clear();
		poderes.clear();
	}
	//----------------------------------------------
	void reiniciar_todo(){
		clear();
		
		
		poderes.reserve(cantidad_pwup);
		
		cargar_nivel(nivel,cantidad_ladrillos,musica_fondo,spawn_pj1,spawn_pj2);
		if(nivel==3){
			nivel=0;
		}
		
		player1->refresh(spawn_pj1);
		player2->refresh(spawn_pj2);
		player1->long_bomba=2;
		player2->long_bomba=2;
		
		generar_mapa();
		ladrillos_random();
		puerta_aleatoria();
		pw_aleatorio();
	}
	//----------------------------------------------
	bool draw(RenderWindow &window,Event &evento){
		
		if(musica_fondo.getStatus()!=Music::Status::Playing && pausa_entradas!=true){
			animacion.estado='A';
			musica_fondo.play();
		}
		
		////////////////////////////////////////////DIBUJO
		//entradas de teclado
		inputs(window,evento);
		//------------------------------------
		//dibujar mapa, puerta, ladrillos, personajes(bombas)
		draw_fondo(window);
		puerta_mapa->draw(window);
		
		for(int i=0;i<poderes.size();++i)
			poderes[i].draw(window);
		for(int i=0;i<ladrillo_mapa.size();++i)
			ladrillo_mapa[i].draw(window);
		player1->draw(window);
		player2->draw(window);
		//------------------------------------
		//dibujar puntajes
		//set_puntaje(to_string(3-player1->cantidad_bombas),to_string(3-player2->cantidad_bombas));
		//puntaje_1.setString(to_string(player1->puntaje));
		//puntaje_2.setString(to_string(player2->puntaje));
		interfaz.set_puntaje(player1,player2);
		interfaz.draw(window);
		animacion.draw(window);
		
		
		window.display();
		////////////////////////////////////////////comprobaciones
		//------------------------------------
		//verificar si encontro poderes
		for(int i=0;i<poderes.size();++i){
			if(player1->se_encuentra_en(poderes[i].x,poderes[i].y)){
				player1->long_bomba+=1;
				poderes.erase(poderes.begin()+i);
				continue;
			}
				
			if(player2->se_encuentra_en(poderes[i].x,poderes[i].y)){
				player2->long_bomba+=1;
				poderes.erase(poderes.begin()+i);
				continue;
			}
				
		}
		//------------------------------------
		//verificar que hubo explosiones para eliminar paredes
		if(explosiones.size()>0){
			for(int i=0;i<explosiones.size();++i){
				if(explosiones[i].second==puerta_mapa->x && explosiones[i].first==puerta_mapa->y){
					puerta_mapa->sonido_puerta.play();
				}
				buscar_explosiones(explosiones[i].second,explosiones[i].first);
			}
			explosiones.clear();
			//cout<<"tamanio explosiones "<<explosiones.size()<<endl;
		}
		//------------------------------------
		//en caso uno muera
		if(!player1->vivo || !player2->vivo){
			if(!pausa_entradas){
				animacion.estado='O';
			}
			pausa_entradas=true;
			if(animacion.estado=='N'){
				nivel++;
				if(!player1->vivo){//p1 muerto
					player2->puntaje+=1;
				}
				else{
					player1->puntaje+=1;
				}
				//reiniciar mapa
				reiniciar_todo();
				interfaz.set_puntaje(player1,player2);
				musica_fondo.play();
				animacion.estado='A';
				pausa_entradas=false;
				return false;
			}
		}
		//en caso ambos mueran
		if(!player1->vivo && !player2->vivo){
			if(!pausa_entradas){
				animacion.estado='O';
			}
			pausa_entradas=true;
			if(animacion.estado=='N'){
				musica_fondo.pause();
				explosiones.clear();
				reiniciar_todo();
				musica_fondo.play();
				animacion.estado='A';
				pausa_entradas=false;
				return false;
			}
		}
		//en caso alguien gane
		if(player1->se_encuentra_en(puerta_mapa->x,puerta_mapa->y) || player2->se_encuentra_en(puerta_mapa->x,puerta_mapa->y)){
			musica_fondo.pause();
			//animacion oscurecer
			
			if(!pausa_entradas){
				animacion.estado='O';
			}
			pausa_entradas=true;
			
			if(animacion.estado=='N'){
				sonido_bajar_escaleras.play();
				nivel++;
				while(sonido_bajar_escaleras.getStatus()==Sound::Status::Playing){};
				if(player1->se_encuentra_en(puerta_mapa->x,puerta_mapa->y)){
					player1->puntaje+=1;
				}
				else{
					player2->puntaje+=1;
				}
				//reiniciar mapa
				reiniciar_todo();
				interfaz.set_puntaje(player1,player2);
				musica_fondo.play();
				animacion.estado='A';
				pausa_entradas=false;
			}
			//animacion aparecer
			
			
			return false;
			
			//mostrar_mapa_consola();
		}
		
		return false;
	}
};

#endif

