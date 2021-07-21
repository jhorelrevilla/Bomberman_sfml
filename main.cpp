#include <iostream>
#include <SFML/Graphics.hpp>
#include "Bomberman.h"
#include "Menu.h"
#include "Mapa.h"

using namespace sf;
using namespace std;

int window_x=1920;
int window_y=1080;
float window_porcentaje=1;
//objetos
Menu *juego=nullptr;
//------------------------------------------------------------------------------
int main(int argc, char *argv[]){
	RenderWindow w(VideoMode(window_x*window_porcentaje,
							window_y*window_porcentaje),"Bomberman",Style::Fullscreen);
	//configuraciones window
	w.setFramerateLimit(30);
	w.setKeyRepeatEnabled(false);
	w.setSize(Vector2u(1920,1080));
	//cargar fuentes,texturas,buffer sonidos
	cargar_fuentes();
	cargar_sonidos();
	cargar_texturas1();
	cargar_dimensiones(window_porcentaje);
	juego=new Menu();
	//mostrar_mapa_consola();
	//bucle
	while(w.isOpen()){
		w.clear(Color(0,0,0));
		Event e;
		juego->draw(w,e);
	}
	return 0;
}

