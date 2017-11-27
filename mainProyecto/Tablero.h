#pragma once
#include "Caja.h"
#include <iostream>
#include "Coordenadas.h"
#include <random>
#include "Timer.h"


class Tablero
{
public:
	Tablero();
	Tablero(int num[7][7]);
	~Tablero();
	void MatrizPrincipal();
	void Eliminar();
	void RealizarMatch5(int tipo);
	void MoverCajas(const int x, const int y, const char direccion);
	void HayMatchVertical();
	void HayMatchHorizontal();
	void DescongelarCajas();
	void AddScore(Caja & caja);
	void ReAcomodarTablero();
	void QuitarLiberable();
	void RevizaPokebola();
	void SetLevel(int lvl);
	bool HayCajasLiberables();
	bool HayJugadasPosibles();
	bool TerminaJuego() const;
	int MostrarScores(int type) const;
	Caja BuscarCaja(int columna, int fila);
	int BuscarCajaGuardar(int j, int i);
	bool EstaEntre(int limiteInferior, int limiteSuperior, int numero); 
	
	

protected:

private:
	Caja matriz[7][7];
	Timer contador;
	std::mt19937 rng;
	//int contenedor[12];
	int numEvoluciones = 0;
	int numPokemon = 0;
	int scoreTotal = 0;

	int mew = 0;
	int mew2 = 0;

	int pikachu = 0;
	int raichu = 0;

	int kirlia = 0;
	int gardevoir = 0;

	int staravia = 0;
	int staraptor = 0;
	
	int pokebola = 0;

	

};

