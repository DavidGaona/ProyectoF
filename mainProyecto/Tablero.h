#pragma once
#include "Caja.h"
#include <iostream>
#include "Coordenadas.h"
#include <random>


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
	void SetToZero();
	void QuitarLiberable();
	void RevizaPokebola();
	bool HayCajasLiberables();
	bool HayJugadasPosibles();
	int* MostrarScores() const;
	Caja BuscarCaja(int columna, int fila);
	int BuscarCajaGuardar(int j, int i);
	bool EstaEntre(int limiteInferior, int limiteSuperior, int numero);
	

protected:

private:
	Caja matriz[7][7];
	std::mt19937 rng;
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

