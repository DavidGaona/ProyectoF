#include "stdafx.h"
#include "Caja.h"
using namespace std;

Caja::Caja()
{
	
}


Caja::Caja(std::mt19937& rng)
{
	GenerateRandom(rng);
	AsignarScore(tipoPokemon);
}

Caja::Caja(int tipo)
{
	tipoPokemon = tipo;
	AsignarScore(tipo);
}


Caja::~Caja()
{
}

void Caja::GenerateRandom(std::mt19937 & rng)
{
	std::uniform_int_distribution<int> numAleatorio(0, 8);
	tipoPokemon = numAleatorio(rng);
	if (tipoPokemon == 0)
	{
		tipoPokemon = numAleatorio(rng);
	}
	//else if (tipoPokemon == 2 || tipoPokemon == 4 || tipoPokemon == 6 || tipoPokemon == 8 )
	//{
	//	tipoPokemon = numAleatorio(rng);
	//}

}

void Caja::AsignarScore(int tipo)
{
	switch (tipo)
	{
	case 1:
		valorPuntaje = 100; //mew
		break;

	case 2:
		valorPuntaje = 200; //mewtwo
		esEvolucion = true;

		break;

	case 3:
		valorPuntaje = 4; // pikachu
		break;

	case 4:
		valorPuntaje = 20; // raichu
		esEvolucion = true;
		break;

	case 5:
		valorPuntaje = 20; // Kirlia
		break;

	case 6:
		valorPuntaje = 69; // Gardevoir
		esEvolucion = true;
		break;

	case 7:
		valorPuntaje = 6; // staravia
		break;

	case 8:
		valorPuntaje = 66; // staraptor
		esEvolucion = true;
		break;

	case 0:
		valorPuntaje = 80; //pokebola
		esPokebola = true;
		break;
	}
}

void Caja::SetLiberable()
{
	esLiberable = true;
	Congelar();
}

void Caja::SetLiberables()
{
	esLiberable = true;
}

void Caja::QuitarLibertad()
{
	esLiberable = false;
}

void Caja::Llenar(std::mt19937 & rng)
{
	esLiberable = false;
	GenerateRandom(rng);
	AsignarScore(tipoPokemon);
}

void Caja::AsignarPos(int x, int y)
{
	pos.x = x;
	pos.y = y;
}

void Caja::Congelar()
{
	estaCongelada = true;
}

void Caja::Descongelar()
{
	estaCongelada = false;
}

void Caja::Abrir()
{
	estaAbierta = true;
}

int Caja::GetPokemon() const
{
	return tipoPokemon;
}

int Caja::GetPosX() const
{
	return pos.x;
}

int Caja::GetPosY() const
{
	return pos.y;
}

int Caja::GetPunaje() const
{
	return valorPuntaje;
}

bool Caja::GetEstado() const
{
	return esLiberable;
}

bool Caja::Pokebola() const
{
	return  esPokebola;
}

bool Caja::EstaAbierta() const
{
	return estaAbierta;
}

bool Caja::EstaCongelado() const
{
	return estaCongelada;
}

bool Caja::GetEvolucion() const
{
	return esEvolucion;
}



