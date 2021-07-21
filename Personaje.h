#ifndef PERSONAJE_H
#define PERSONAJE_H
#include "Mapa.h"
#include "Bomba.h"


struct Personaje {
	Sprite s_bomberman;
	
	vector<Bomba> bombas;
	int x,y;
	int cantidad_bombas=0;
	bool vivo=true;
	
	
	Sound sonido_pasos;
	
	
	Sound sonido_muerte;
	
	int r=255,g=255,b=255;
	float volumen=4;
	
	
	vector<Sound> sonido_bomba;
	vector<Sound> sonido_colocar_bomba;
	int puntaje=0;
	
	int long_bomba=2;
	
	Personaje(int x=0,int y=0){
		//cargar_sonidos();
		sonido_bomba.resize(3);
		sonido_colocar_bomba.resize(3);
		for(int i=0;i<3;++i){
			sonido_bomba[i].setBuffer(buffer_explosion);
			sonido_bomba[i].setVolume(3);
			sonido_colocar_bomba[i].setBuffer(bf_sound_colocar_bomba);
			sonido_colocar_bomba[i].setVolume(4);
		}
		//
		
		
		this->x=x;
		this->y=y;
		mapa[y][x]='j';
		
		s_bomberman.setTexture(t_bomberman);
		s_bomberman.setScale(scale_x,scale_y);
		s_bomberman.setPosition(texture_x * x,
								texture_y * y);
		
		
		
		sonido_pasos.setBuffer(buffer_pasos);
		sonido_pasos.setVolume(4);
		
		
		sonido_muerte.setBuffer(buffer_muerte);
		
		sonido_muerte.setVolume(0.7);
	}
	//---------------------------//
	void set_position(int x, int y){
		mapa[y][x]='c';
		this->x=x;
		this->y=y;
		s_bomberman.setPosition(texture_x * x,
								texture_y * y);
		mapa[y][x]='j';
	}
	//---------------------------//
	void mover(int x_t,int y_t){
		if(vivo){
			if((mapa[y+y_t][x+x_t]=='c' || mapa[y+y_t][x+x_t]=='S' || mapa[y+y_t][x+x_t]=='x') && mapa[y+y_t][x+x_t]!='j'){
				if(mapa[y][x]!='b'){
					mapa[y][x]='c';
				}
				x+=x_t;y+=y_t;
				
				s_bomberman.setPosition(texture_x * x,
										texture_y * y);
				mapa[y][x]='j';
				sonido_pasos.play();
				
			}
		}
	}
	//---------------------------//
	void refresh(Vector2i &posj1){
		cantidad_bombas=0;
		bombas.clear();
		vivo=true;
		s_bomberman.setTexture(t_bomberman);
		
		set_position(posj1.x,posj1.y);
		mapa[y][x]='c';
	}
	//---------------------------//
	void agregar_bomba(){
		if(vivo && mapa[y][x]!='b'){
			if(cantidad_bombas<3){
				Bomba b_temporal(&sonido_bomba[cantidad_bombas],long_bomba,x,y);
				sonido_colocar_bomba[cantidad_bombas].play();
				bombas.push_back(b_temporal);
				cantidad_bombas++;
			}
		}
	}
	bool se_encuentra_en(int x,int y){
		if(this->x==x && this->y==y){
			return true;
		}
		return false;
	}
	//---------------------------//
	void draw(RenderWindow &window){
		window.draw(s_bomberman);
		if(mapa[y][x]=='x' && vivo){
			//perdiste
			s_bomberman.setTexture(t_muerte);
			sonido_muerte.play();
			vivo=false;
			
		}
		for(int i=0;i<bombas.size();++i){
			//window.draw(bombas[i]);
			if(bombas[i].draw(window)){
				//sonido_bomba.play();
				bombas.erase(bombas.begin()+i);
				cantidad_bombas--;
			}
		}
		
	}
	//---------------------------//
	//---------------------------//
	void change_color(int r,int g,int b){
		this->r=r;
		this->g=g;
		this->b=b;
		s_bomberman.setColor(Color(r,g,b));
	}
//-----------------------------------------------------

};

#endif

