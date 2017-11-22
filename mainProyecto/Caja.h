#pragma once
#include "stdafx.h"
#include "Caja.h"
#include "Coordenadas.h"
#include <random>

class Caja
{
public:
	Caja();
	Caja(std::mt19937& rng);
	Caja(int tipo);
	~Caja();
	void GenerateRandom(std::mt19937& rng);
	void AsignarScore(int tipo);
	void SetLiberable();
	void SetLiberables();
	void QuitarLibertad();
	void Llenar(std::mt19937& rng);
	void AsignarPos(int x, int y);
	void Congelar();
	void Descongelar();
	void Abrir();
	int GetPokemon() const;
	int GetPosX() const;
	int GetPosY() const;
	int GetPunaje() const;
	bool GetEvolucion() const;
	bool GetEstado() const;
	bool Pokebola() const;
	bool EstaAbierta() const;
	bool EstaCongelado() const;

protected:

private:
	int tipoPokemon;
	int valorPuntaje;
	bool esEvolucion = false;
	bool esPokebola = false;
	bool estaAbierta = false;
	bool esLiberable = false;
	bool estaCongelada = false;
	Coordenadas pos;
};

