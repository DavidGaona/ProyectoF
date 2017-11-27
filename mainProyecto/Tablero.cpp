#include "stdafx.h"
#include "Tablero.h"
#include "Caja.h"
using namespace std;

Tablero::Tablero()
	:
	rng(std::random_device() ())

{
	for (int i = 0; i < 7; ++i)
	{
		for (int j = 0; j < 7; j++)
		{
			matriz[i][j] = Caja(rng);
			matriz[i][j].AsignarPos(j + 1, i + 1);				// pos.x = columnas = j
		}														// pos.y = filas = i
	}

	numEvoluciones = 0;
	numPokemon = 0;
	scoreTotal = 0;
	mew = 0;
	mew2 = 0;
	pikachu = 0;
	raichu = 0;
	kirlia = 0;
	gardevoir = 0;
	staravia = 0;
	staraptor = 0;
	pokebola = 0;
}

Tablero::Tablero(int num[7][7])
{
	
	for (int i = 0; i < 7; ++i)
	{
		for (int j = 0; j < 7; j++)
		{
			matriz[i][j] = Caja(num[i][j]);
			matriz[i][j].AsignarPos(j + 1, i + 1);				
		}														
	}

}


Tablero::~Tablero()
{
}

void Tablero::MatrizPrincipal()
{
	for (int i = 0; i < 7; ++i)
	{
		for (int j = 0; j < 7 ; j++)
		{
			if (i == 0 && j == 0)
			{
				cout <<  "********************************" << endl;
				cout << "*  ";
				cout << matriz[i][j].GetPokemon() << "   ";
			}

			else if (i == 6 && j == 6)
			{
				cout << matriz[i][j].GetPokemon();
				cout << "   *" << endl;
				cout << "********************************" << endl;
			}
			else if (j == 0)
			{
				cout << "*  ";
				cout << matriz[i][j].GetPokemon() << "   ";
			}
			else if (j == 6)
			{
				cout << matriz[i][j].GetPokemon();
				cout << "   *";
			}
			else
			{
				cout << matriz[i][j].GetPokemon() << "   ";
			}
			
		}
		cout << endl;
		cout << endl;
	}
}

void Tablero::Eliminar()														// i = filas
{																				// j = columnas
	HayMatchVertical();
	HayMatchHorizontal();
	RevizaPokebola();
	while (HayCajasLiberables())
	{
		for (int i = 0; i < 7; ++i)
		{
			for (int j = 0; j < 7; j++)
			{
				HayMatchVertical();
				HayMatchHorizontal();
				if (matriz[i][j].GetEstado())
				{
					if (i == 0)
					{
						AddScore(matriz[i][j]);							//anade el puntaje que se gana por liberar la caja
						matriz[i][j].Llenar(rng);						//Llena la caja con un numero aleatorio
						matriz[i][j].Congelar();						//Congela la caja para que no se vuelva a llenar
						MatrizPrincipal();								//Devuelve la vista del tablero
						cout << endl;
						cout << endl;
					}
					else
					{
						matriz[i - 1][j].Congelar();					//Congela la caja que cambie con la liberable
						std::swap(matriz[i][j], matriz[i - 1][j]);		//Cambia la caja liberable, con la que se encuentre una fila arriba de esta y en la misma columna
						MatrizPrincipal();
						cout << endl;
						cout << endl;
					}
				}
			} 
		}
		DescongelarCajas();
		HayMatchVertical();
		HayMatchHorizontal();
	}					  
}


void Tablero::RealizarMatch5(int tipo)
{
	for (int i = 0; i < 7; ++i)
	{
		for (int j = 0; j < 7; j++)
		{
			if (matriz[i][j].GetPokemon() == tipo)
			{
				matriz[i][j].SetLiberable();

			}
		}
	}
}

void Tablero::MoverCajas(const int x, const int y, const char direccion)
{
	if (EstaEntre(0, 8, x) && EstaEntre(0, 8, y) &&
		direccion == 'R' || direccion == 'r' ||
		direccion == 'L' || direccion == 'l' || 
		direccion == 'U' || direccion == 'u' || 
		direccion == 'D' || direccion == 'd' )
	{
		if (BuscarCaja(x, y).GetPokemon() == 0)
		{
			cout << " No puedes mover las pokebolas! " << endl;
		}

		else if ( (direccion == 'R' || direccion == 'r') && !(7 == x) )					// pos.x = columnas = j																						// pos.y = filas = i
		{
			if (BuscarCaja(x + 1, y).GetPokemon() == 0)
			{
				cout << " No hacia una pokebola! " << endl;
			}
			else
			{
				std::swap(matriz[y - 1][x - 1], matriz[y - 1][x]);
			}
		}

		else if ((direccion == 'L' || direccion == 'l') && !(1 == x))
		{
			if (BuscarCaja(x - 1, y).GetPokemon() == 0)
			{
				cout << " No hacia una pokebola! " << endl;
			}
			else
			{
				std::swap(matriz[y - 1][x - 1], matriz[y - 1][x - 2]);
			}
		}

		else if ((direccion == 'U' || direccion == 'u') && !(1 == y) )
		{
			if ((BuscarCaja(x, y - 1).GetPokemon() == 0))
			{
				cout << " No hacia una pokebola! " << endl;
			}
			else
			{
				std::swap(matriz[y - 1][x - 1], matriz[y - 2][x - 1]);
			}
		}

		else if ((direccion == 'D' || direccion == 'd') && !(7 == y) )
		{
			if ((BuscarCaja(x, y + 1).GetPokemon() == 0))
			{
				cout << " No hacia una pokebola! " << endl;
			}
			else
			{
				std::swap(matriz[y - 1][x - 1], matriz[y][x - 1]);
			}
		}

		else
		{
			cout << " No te salgas del tablero! " << endl;
			MatrizPrincipal();
		}
									
		HayMatchHorizontal();
		HayMatchVertical();
		if (HayCajasLiberables())
		{
		//	Eliminar();
		}
		else
		{
			if ((direccion == 'R' || direccion == 'r') && !(7 == x) &&						// pos.x = columnas = j
				!((BuscarCaja(x, y).GetPokemon() == 0)) &&									// pos.y = filas = i
				!((BuscarCaja(x + 1, y).GetPokemon() == 0)))
			{
				std::swap(matriz[y - 1][x - 1], matriz[y - 1][x]);
			}

			else if ((direccion == 'L' || direccion == 'l') && !(1 == x) &&
				!((BuscarCaja(x, y).GetPokemon() == 0)) &&
				!((BuscarCaja(x - 1, y).GetPokemon() == 0)))
			{
				std::swap(matriz[y - 1][x - 1], matriz[y - 1][x - 2]);
			}

			else if ((direccion == 'U' || direccion == 'u') && !(1 == y) &&
				!((BuscarCaja(x, y).GetPokemon() == 0)) &&
				!((BuscarCaja(x, y - 1).GetPokemon() == 0)))
			{
				std::swap(matriz[y - 1][x - 1], matriz[y - 2][x - 1]);
			}

			else if ((direccion == 'D' || direccion == 'd') && !(7 == y) &&
				!((BuscarCaja(x, y).GetPokemon() == 0)) &&
				!((BuscarCaja(x, y + 1).GetPokemon() == 0)))
			{
				std::swap(matriz[y - 1][x - 1], matriz[y][x - 1]);
			}
		}
	}
	else
	{
		cout << "Posiciones invalidas, por favor ingrese posiciones entre 1 y 7, siendo estos ultimos 2 incluidos " << endl;
	}
}

void Tablero::HayMatchVertical()
{
	for (int i = 0; i < 7; ++i)
	{
		for (int j = 0; j < 7; j++)
		{
			if (i <= 2 &&													//Revisa si es hay un match 5 vertical
				matriz[i][j].GetPokemon()!=0 &&
				!(matriz[i][j].EstaCongelado()) &&
				matriz[i][j].GetPokemon() == matriz[i+1][j].GetPokemon() &&  
				matriz[i][j].GetPokemon() == matriz[i+2][j].GetPokemon() &&
				matriz[i][j].GetPokemon() == matriz[i+3][j].GetPokemon() &&
				matriz[i][j].GetPokemon() == matriz[i+4][j].GetPokemon())
			{
				int type = matriz[i][j].GetPokemon();
				RealizarMatch5(type);
			}
			else if (i <= 3 &&												//Revisa si es hay un match 4 vertical
				matriz[i][j].GetPokemon() != 0 &&
				!(matriz[i][j].GetEvolucion()) &&
				!(matriz[i][j].EstaCongelado()) &&
				matriz[i][j].GetPokemon() == matriz[i+1][j].GetPokemon() &&
				matriz[i][j].GetPokemon() == matriz[i+2][j].GetPokemon() &&
				matriz[i][j].GetPokemon() == matriz[i+3][j].GetPokemon())
			{

				if (i == 0 && j == 0)										//primer caso:
				{															//Que sea la fila 0 y la columna 0
					matriz[i][j].SetLiberable();
					matriz[i + 1][j].SetLiberable();
					matriz[i + 2][j].SetLiberable();
					matriz[i + 3][j].SetLiberable();
					matriz[i + 4][j].SetLiberable();
					matriz[i][j + 1].SetLiberable();
					matriz[i + 1][j + 1].SetLiberable();
					matriz[i + 2][j + 1].SetLiberable();
					matriz[i + 3][j + 1].SetLiberable();
				}
				else if (i == 0 && j == 6)									//segundo caso:
				{															//Que sea la fila 0 y la columna 6
					matriz[i][j].SetLiberable();
					matriz[i + 1][j].SetLiberable();
					matriz[i + 2][j].SetLiberable();
					matriz[i + 3][j].SetLiberable();
					matriz[i + 4][j].SetLiberable();
					matriz[i][j - 1].SetLiberable();
					matriz[i + 1][j - 1].SetLiberable();
					matriz[i + 2][j - 1].SetLiberable();
					matriz[i + 3][j - 1].SetLiberable();
				}
				else if (i == 3 && j == 0)									//Tercer caso:
				{															//Que sea la fila 3 y la columna 0
					matriz[i][j].SetLiberable();
					matriz[i - 1][j].SetLiberable();
					matriz[i - 2][j].SetLiberable();
					matriz[i - 3][j].SetLiberable();
					matriz[i - 4][j].SetLiberable();
					matriz[i][j + 1].SetLiberable();
					matriz[i - 1][j + 1].SetLiberable();
					matriz[i - 2][j + 1].SetLiberable();
					matriz[i - 3][j + 1].SetLiberable();
				}
				else if (i == 3 && j == 6)									//Cuarto caso:
				{															//Que sea la fila 3 y la columna 6
					matriz[i][j].SetLiberable();
					matriz[i + 1][j].SetLiberable();
					matriz[i + 2][j].SetLiberable();
					matriz[i + 3][j].SetLiberable();
					matriz[i - 1][j].SetLiberable();
					matriz[i][j - 1].SetLiberable();
					matriz[i + 1][j - 1].SetLiberable();
					matriz[i + 2][j - 1].SetLiberable();
					matriz[i + 3][j - 1].SetLiberable();
				}
				else if (j == 0 && (i == 1 || i == 2))						//Quinto caso:
				{															//Que sea la fila 1 o 2 y la columna 0
					matriz[i][j].SetLiberable();
					matriz[i + 1][j].SetLiberable();
					matriz[i + 2][j].SetLiberable();
					matriz[i + 3][j].SetLiberable();
					matriz[i + 4][j].SetLiberable();
					matriz[i - 1][j].SetLiberable();
					matriz[i][j + 1].SetLiberable();
					matriz[i + 1][j + 1].SetLiberable();
					matriz[i + 2][j + 1].SetLiberable();
					matriz[i + 3][j + 1].SetLiberable();
				}
				else if (j == 6 && (i == 1 || i == 2))						//Sexto caso:
				{															//Que sea la fila 1 o 2 y la columna 6
					matriz[i][j].SetLiberable();
					matriz[i + 1][j].SetLiberable();
					matriz[i + 2][j].SetLiberable();
					matriz[i + 3][j].SetLiberable();
					matriz[i + 4][j].SetLiberable();
					matriz[i - 1][j].SetLiberable();
					matriz[i][j - 1].SetLiberable();
					matriz[i + 1][j - 1].SetLiberable();
					matriz[i + 2][j - 1].SetLiberable();
					matriz[i + 3][j - 1].SetLiberable();
				}
				else if (i == 0)											//Septimo caso:
				{															//Que sea fila 0
					matriz[i][j].SetLiberable();
					matriz[i + 1][j].SetLiberable();
					matriz[i + 2][j].SetLiberable();
					matriz[i + 3][j].SetLiberable();
					matriz[i + 4][j].SetLiberable();
					matriz[i][j + 1].SetLiberable();
					matriz[i + 1][j + 1].SetLiberable();
					matriz[i + 2][j + 1].SetLiberable();
					matriz[i + 3][j + 1].SetLiberable();
					matriz[i][j - 1].SetLiberable();
					matriz[i + 1][j - 1].SetLiberable();
					matriz[i + 2][j - 1].SetLiberable();
					matriz[i + 3][j - 1].SetLiberable();
				}
				else if (i == 3)
				{															//Octavo caso:
					matriz[i][j].SetLiberable();							//Que sea fila 3
					matriz[i + 1][j].SetLiberable();
					matriz[i + 2][j].SetLiberable();
					matriz[i + 3][j].SetLiberable();
					matriz[i - 1][j].SetLiberable();
					matriz[i][j + 1].SetLiberable();
					matriz[i + 1][j + 1].SetLiberable();
					matriz[i + 2][j + 1].SetLiberable();
					matriz[i + 3][j + 1].SetLiberable();
					matriz[i][j - 1].SetLiberable();
					matriz[i + 1][j - 1].SetLiberable();
					matriz[i + 2][j - 1].SetLiberable();
					matriz[i + 3][j - 1].SetLiberable();
				}
				else
				{															//Noveno Caso(caso por defecto):
					matriz[i][j].SetLiberable();							//Que no sea ninguno de los anteriores
					matriz[i + 1][j].SetLiberable();
					matriz[i + 2][j].SetLiberable();
					matriz[i + 3][j].SetLiberable();
					matriz[i + 4][j].SetLiberable();
					matriz[i - 1][j].SetLiberable();
					matriz[i][j + 1].SetLiberable();
					matriz[i + 1][j + 1].SetLiberable();
					matriz[i + 2][j + 1].SetLiberable();
					matriz[i + 3][j + 1].SetLiberable();
					matriz[i][j - 1].SetLiberable();
					matriz[i + 1][j - 1].SetLiberable();
					matriz[i + 2][j - 1].SetLiberable();
					matriz[i + 3][j - 1].SetLiberable();
				}
			}
			else if ( i <= 4 &&												//Revisa si es hay un match 3 vertical
				matriz[i][j].GetPokemon() != 0 &&
				!(matriz[i][j].EstaCongelado()) &&
				matriz[i][j].GetPokemon() == matriz[i+1][j].GetPokemon() &&
				matriz[i][j].GetPokemon() == matriz[i+2][j].GetPokemon())
			{
				matriz[i][j].SetLiberable();
				matriz[i+1][j].SetLiberable();
				matriz[i+2][j].SetLiberable();
			}
	//			else if ( i <= 5 &&
	//				matriz[i][j].GetEvolucion() &&							//Revisa si es hay un match 2 vertical
	//				matriz[i][j].GetPokemon() != 0 &&
	//				!(matriz[i][j].EstaCongelado()) &&
	//				matriz[i][j].GetPokemon() == matriz[i+1][j].GetPokemon())
	//			{
	//				matriz[i][j].SetLiberable();
	//				matriz[i+1][j].SetLiberable();
	//			}
		}
	}

}

void Tablero::HayMatchHorizontal()
{
	for (int i = 0; i < 7 ; ++i)
	{
		for (int j = 0; j < 7; j++)
		{
			if (j <= 2 &&															//Revisa si es hay un match 5 horizontal
				matriz[i][j].GetPokemon() != 0 &&
				!(matriz[i][j].EstaCongelado()) &&
				matriz[i][j].GetPokemon() == matriz[i][j + 1].GetPokemon() &&
				matriz[i][j].GetPokemon() == matriz[i][j + 2].GetPokemon() &&
				matriz[i][j].GetPokemon() == matriz[i][j + 3].GetPokemon() &&
				matriz[i][j].GetPokemon() == matriz[i][j + 4].GetPokemon())
			{
				int type = matriz[i][j].GetPokemon();
				RealizarMatch5(type);
			}

			else if ( j <= 3 &&													//Revisa si es hay un match 4 horizontal
				matriz[i][j].GetPokemon() != 0 &&
				!(matriz[i][j].GetEvolucion()) && 
				!(matriz[i][j].EstaCongelado()) &&
				matriz[i][j].GetPokemon()== matriz[i][j+1].GetPokemon()&& // 3
				matriz[i][j].GetPokemon()== matriz[i][j+2].GetPokemon()&& // 4
				matriz[i][j].GetPokemon()== matriz[i][j+3].GetPokemon())  // 5
			{
				if ( i == 0 && j == 0)											//primer caso:
				{																//Que sea la fila 0 y la columna 0
					matriz[i][j].SetLiberable();
					matriz[i][j+1].SetLiberable();
					matriz[i][j+2].SetLiberable();
					matriz[i][j+3].SetLiberable();
					matriz[i][j+4].SetLiberable();
					matriz[i+1][j].SetLiberable();
					matriz[i+1][j+1].SetLiberable();
					matriz[i+1][j+2].SetLiberable();
					matriz[i+1][j+3].SetLiberable();
				}
				else if (i == 6 && j == 0)										//segundo caso:
				{																//Que sea la fila 6 y la columna 0
					matriz[i][j].SetLiberable();
					matriz[i][j + 1].SetLiberable();
					matriz[i][j + 2].SetLiberable();
					matriz[i][j + 3].SetLiberable();
					matriz[i][j + 4].SetLiberable();
					matriz[i - 1][j].SetLiberable();
					matriz[i - 1][j + 1].SetLiberable();
					matriz[i - 1][j + 2].SetLiberable();
					matriz[i - 1][j + 3].SetLiberable();
				}
				else if (i == 0 && j == 3)										//Tercer caso:
				{																//Que sea la fila 0 y la columna 3
					matriz[i][j].SetLiberable();
					matriz[i][j + 1].SetLiberable();
					matriz[i][j + 2].SetLiberable();
					matriz[i][j + 3].SetLiberable();
					matriz[i][j - 1].SetLiberable();
					matriz[i + 1][j].SetLiberable();
					matriz[i + 1][j + 1].SetLiberable();
					matriz[i + 1][j + 2].SetLiberable();
					matriz[i + 1][j + 3].SetLiberable();
				}
				else if (i == 6 && j == 3)										//Cuarto caso:
				{																//Que sea la fila 6 y la columna 3
					matriz[i][j].SetLiberable();
					matriz[i][j + 1].SetLiberable();
					matriz[i][j + 2].SetLiberable();
					matriz[i][j + 3].SetLiberable();
					matriz[i][j - 1].SetLiberable();
					matriz[i - 1][j].SetLiberable();
					matriz[i - 1][j + 1].SetLiberable();
					matriz[i - 1][j + 2].SetLiberable();
					matriz[i - 1][j + 3].SetLiberable();
				}
				else if (i == 0 && ( j == 1 || j == 2 ))						//Quinto caso:
				{																//Que sea la fila 0 y la columna 1 o 2
					matriz[i][j].SetLiberable();
					matriz[i][j + 1].SetLiberable();
					matriz[i][j + 2].SetLiberable();
					matriz[i][j + 3].SetLiberable();
					matriz[i][j + 4].SetLiberable();
					matriz[i][j - 1].SetLiberable();
					matriz[i + 1][j].SetLiberable();
					matriz[i + 1][j + 1].SetLiberable();
					matriz[i + 1][j + 2].SetLiberable();
					matriz[i + 1][j + 3].SetLiberable();
				}
				else if ( i == 6 && ( j == 1 || j == 2 ) )						//Sexto caso:
				{																//Que sea la fila 6 y la columna 1 o 2
					matriz[i][j].SetLiberable();
					matriz[i][j + 1].SetLiberable();
					matriz[i][j + 2].SetLiberable();
					matriz[i][j + 3].SetLiberable();
					matriz[i][j + 4].SetLiberable();
					matriz[i][j - 1].SetLiberable();
					matriz[i - 1][j].SetLiberable();
					matriz[i - 1][j + 1].SetLiberable();
					matriz[i - 1][j + 2].SetLiberable();
					matriz[i - 1][j + 3].SetLiberable();
				}
				else if ( j == 0 )												//Septimo caso:
				{																//Que sea columna 0

					matriz[i][j].SetLiberable();
					matriz[i][j + 1].SetLiberable();
					matriz[i][j + 2].SetLiberable();
					matriz[i][j + 3].SetLiberable();
					matriz[i][j + 4].SetLiberable();
					matriz[i + 1][j].SetLiberable();
					matriz[i + 1][j + 1].SetLiberable();
					matriz[i + 1][j + 2].SetLiberable();
					matriz[i + 1][j + 3].SetLiberable();
					matriz[i - 1][j].SetLiberable();
					matriz[i - 1][j + 1].SetLiberable();
					matriz[i - 1][j + 2].SetLiberable();
					matriz[i - 1][j + 3].SetLiberable();
				}
				else if ( j == 3 )												//Octavo caso:
				{																//Que sea columna 3
					matriz[i][j].SetLiberable();
					matriz[i][j + 1].SetLiberable();
					matriz[i][j + 2].SetLiberable();
					matriz[i][j + 3].SetLiberable();
					matriz[i][j - 1].SetLiberable();
					matriz[i + 1][j].SetLiberable();
					matriz[i + 1][j + 1].SetLiberable();
					matriz[i + 1][j + 2].SetLiberable();
					matriz[i + 1][j + 3].SetLiberable();
					matriz[i - 1][j].SetLiberable();
					matriz[i - 1][j + 1].SetLiberable();
					matriz[i - 1][j + 2].SetLiberable();
					matriz[i - 1][j + 3].SetLiberable();
				} 
				else															//Noveno Caso(caso por defecto):
				{																//Que no sea ninguno de los anteriores
					matriz[i][j].SetLiberable();
					matriz[i][j + 1].SetLiberable();
					matriz[i][j + 2].SetLiberable();
					matriz[i][j + 3].SetLiberable();
					matriz[i][j + 4].SetLiberable();
					matriz[i][j - 1].SetLiberable();
					matriz[i + 1][j].SetLiberable();
					matriz[i + 1][j + 1].SetLiberable();
					matriz[i + 1][j + 2].SetLiberable();
					matriz[i + 1][j + 3].SetLiberable();
					matriz[i - 1][j].SetLiberable();
					matriz[i - 1][j + 1].SetLiberable();
					matriz[i - 1][j + 2].SetLiberable();
					matriz[i - 1][j + 3].SetLiberable();
				}
			}
			else if (j <= 4 &&													//Revisa si es hay un match 3 vertical
				matriz[i][j].GetPokemon() != 0 &&
				!(matriz[i][j].EstaCongelado()) &&
				matriz[i][j].GetPokemon() == matriz[i][j + 1].GetPokemon() &&
				matriz[i][j].GetPokemon() == matriz[i][j + 2].GetPokemon())
			{
				matriz[i][j].SetLiberable();
				matriz[i][j + 1].SetLiberable();
				matriz[i][j + 2].SetLiberable();
			}
	//		else if ( j <= 5 &&
	//			matriz[i][j].GetEvolucion() &&								//Revisa si es hay un match 2 vertical
	//			matriz[i][j].GetPokemon() != 0 &&
	//			!(matriz[i][j].EstaCongelado()) &&
	//			matriz[i][j].GetPokemon()==matriz[i][j+1].GetPokemon())
	//		{
	//			matriz[i][j].SetLiberable();
	//			matriz[i][j+1].SetLiberable();
	//		}
		}
	}
}

void Tablero::DescongelarCajas()
{
	for (int i = 0; i < 7; ++i)
	{
		for (int j = 0; j < 7; j++)
		{
			matriz[i][j].Descongelar();
		}
	}
}

void Tablero::AddScore(Caja & caja)
{
	int puntaje = caja.GetPunaje();
	int tipo = caja.GetPokemon();
	switch (tipo)
	{
	case 0:
		if (pokebola > 0)
		{
			--pokebola;
		}
		break;
	case 1:
		if (mew > 0)
		{
			--mew;
		} 
		scoreTotal = scoreTotal + puntaje; 
		break;

	case 2:
		if (mew2 > 0)
		{
			--mew2;
		}
		scoreTotal = scoreTotal + puntaje;
		break;

	case 3:
		if (pikachu > 0)
		{
			--pikachu;
		}
		scoreTotal = scoreTotal + puntaje;
		break;

	case 4:
		if (raichu > 0)
		{
			--raichu;
		};
		scoreTotal = scoreTotal + puntaje;
		break;					  
								  
	case 5:						  
		if (kirlia > 0)
		{
			--kirlia;
		}
					  
		scoreTotal = scoreTotal + puntaje;
		break;					  
								  
	case 6:	
		if (gardevoir > 0)
		{
			--gardevoir;
		}
					  
		scoreTotal = scoreTotal + puntaje;
		break;					  
								  
	case 7:				

		if (staravia > 0)
		{
			--staravia;
		}				  
		scoreTotal = scoreTotal + puntaje;
		break;					  
								  
	case 8:			

		if (staraptor > 0)
		{
			--staraptor;
		}	  
		scoreTotal = scoreTotal + puntaje;
		break;



	} 
	numPokemon = mew + mew2 + pikachu + raichu + kirlia + gardevoir + staravia + staraptor;
}

void Tablero::ReAcomodarTablero()
{
	for (int i = 0; i < 7; ++i)
	{
		for (int j = 0; j < 7; j++)
		{
			matriz[i][j] = Caja(rng);
			matriz[i][j].AsignarPos(j + 1, i + 1);				// pos.x = columnas = j
		}														// pos.y = filas = i
	}
}

void Tablero::QuitarLiberable()
{
	for (int i = 0; i < 7; ++i)
	{
		for (int j = 0; j < 7; j++)
		{
			matriz[i][j].QuitarLibertad();
		}
	}
}

void Tablero::RevizaPokebola()
{
	for (int i = 0; i < 7; ++i)
	{
		for (int j = 0; j < 7; j++)
		{
			if (matriz[i][j].Pokebola())
			{
				if (matriz[i][j].EstaAbierta())
				{
					if (i == 0 && j == 0)
					{
						if (matriz[i + 1][j].GetEstado() || matriz[i][j + 1].GetEstado())
						{
							matriz[i][j].SetLiberables();
						}
					}
					else if (i == 6 && j == 0)
					{
						if (matriz[i - 1][j].GetEstado() || matriz[i][j + 1].GetEstado())
						{
							matriz[i][j].SetLiberables();
						}
					}
					else if (i == 0 && j == 6)
					{
						if (matriz[i + 1][j].GetEstado() || matriz[i][j - 1].GetEstado())
						{
							matriz[i][j].SetLiberables();
						}
					}
					else if (i == 6 && j == 6)
					{
						if (matriz[i - 1][j].GetEstado() || matriz[i][j - 1].GetEstado())
						{
							matriz[i][j].SetLiberables();
						}
					}
					else if (i == 0)
					{
						if (matriz[i + 1][j].GetEstado() || matriz[i][j - 1].GetEstado() || matriz[i][j + 1].GetEstado())
						{
							matriz[i][j].SetLiberables();
						}
					}
					else if (i == 6)
					{
						if (matriz[i - 1][j].GetEstado() || matriz[i][j - 1].GetEstado() || matriz[i][j + 1].GetEstado())
						{
							matriz[i][j].SetLiberables();
						}
					}
					else if (j == 0)
					{
						if (matriz[i - 1][j].GetEstado() || matriz[i + 1][j].GetEstado() || matriz[i][j + 1].GetEstado())
						{
							matriz[i][j].SetLiberables();
						}
					}
					else if (j == 6)
					{
						if (matriz[i - 1][j].GetEstado() || matriz[i + 1][j].GetEstado() || matriz[i][j - 1].GetEstado())
						{
							matriz[i][j].SetLiberables();
						}
					}
					else
					{
						if (matriz[i - 1][j].GetEstado() || matriz[i + 1][j].GetEstado() || matriz[i][j - 1].GetEstado() || matriz[i][j + 1].GetEstado())
						{
							matriz[i][j].SetLiberables();
						}
					}

				}
				else
				{
					if (i == 0 && j == 0)
					{
						if (matriz[i + 1][j].GetEstado() || matriz[i][j + 1].GetEstado())
						{
							matriz[i][j].Abrir();
						}
					}
					else if (i == 6 && j == 0)
					{
						if (matriz[i - 1][j].GetEstado() || matriz[i][j + 1].GetEstado())
						{
							matriz[i][j].Abrir();
						}
					}
					else if (i == 0 && j == 6)
					{
						if (matriz[i + 1][j].GetEstado() || matriz[i][j - 1].GetEstado())
						{
							matriz[i][j].Abrir();
						}
					}
					else if (i == 6 && j == 6)
					{
						if (matriz[i - 1][j].GetEstado() || matriz[i][j - 1].GetEstado())
						{
							matriz[i][j].Abrir();
						}
					}
					else if (i == 0)
					{
						if (matriz[i + 1][j].GetEstado() || matriz[i][j - 1].GetEstado() || matriz[i][j + 1].GetEstado())
						{
							matriz[i][j].Abrir();
						}
					}
					else if (i == 6)
					{
						if (matriz[i - 1][j].GetEstado() || matriz[i][j - 1].GetEstado() || matriz[i][j + 1].GetEstado())
						{
							matriz[i][j].Abrir();
						}
					}
					else if (j == 0)
					{
						if (matriz[i - 1][j].GetEstado() || matriz[i + 1][j].GetEstado() || matriz[i][j + 1].GetEstado())
						{
							matriz[i][j].Abrir();
						}
					}
					else if (j == 6)
					{
						if (matriz[i - 1][j].GetEstado() || matriz[i + 1][j].GetEstado() || matriz[i][j - 1].GetEstado())
						{
							matriz[i][j].Abrir();
						}
					}
					else
					{
						if (matriz[i - 1][j].GetEstado() || matriz[i + 1][j].GetEstado() || matriz[i][j - 1].GetEstado() || matriz[i][j + 1].GetEstado())
						{
							matriz[i][j].Abrir();
						}
					}
				}
			}
		}
	}
}

void Tablero::SetLevel(int lvl)
{
	if (lvl == 1)
	{
		numPokemon = 20;

		mew = 3;
		mew2 = 2;

		pikachu = 3;
		raichu = 2;

		kirlia = 3;
		gardevoir = 2;

		staravia = 3;
		staraptor = 2;

		pokebola = 1;
	}
	else if (lvl == 2)
	{
		numPokemon = 4000;

		mew = 600;
		mew2 = 4;

		pikachu = 6;
		raichu = 4;

		kirlia = 6;
		gardevoir = 4;

		staravia = 6;
		staraptor = 4;

		pokebola = 2;
	}
	else
	{
		//elsa capuntas
	}
}

bool Tablero::HayCajasLiberables() 
{
	for (int i = 0; i < 7; ++i)
	{
		for (int j = 0; j < 7; j++)
		{
			if (matriz[i][j].GetEstado())
			{
				return true;
			}
		}
	}
	return false;
}

bool Tablero::HayJugadasPosibles() 
{
	for (int i = 0; i < 7; ++i)
	{
		for (int j = 0; j < 7; j++)
		{
			if (i != 6)
			{
				if (matriz[i][j].GetPokemon() != 0 && matriz[i + 1][j].GetPokemon() != 0)		//vertical
				{
					std::swap(matriz[i][j], matriz[i + 1][j]);
					HayMatchVertical();
					HayMatchHorizontal();
					if (HayCajasLiberables())
					{
						std::swap(matriz[i][j], matriz[i + 1][j]);
						DescongelarCajas();
						QuitarLiberable();
						return true;
					}
					else
					{
						DescongelarCajas();
						QuitarLiberable();
						std::swap(matriz[i][j], matriz[i + 1][j]);
					}
				}
			}
		}
	}

	for (int i = 0; i < 7; ++i)
	{
		for (int j = 0; j < 7; j++)
		{
			if (j != 6)
			{
				if (matriz[i][j].GetPokemon() != 0 && matriz[i][j + 1].GetPokemon() != 0)
				{
					std::swap(matriz[i][j], matriz[i][j + 1]);
					HayMatchVertical();
					HayMatchHorizontal();
					if (HayCajasLiberables())
					{
						std::swap(matriz[i][j], matriz[i][j + 1]);
						DescongelarCajas();
						QuitarLiberable();
						return true;
					}
					else
					{
						DescongelarCajas();
						QuitarLiberable();
						std::swap(matriz[i][j], matriz[i][j + 1]);
					}
				}
			}
		}
	}
	return false;
}

bool Tablero::TerminaJuego() const					//Reviza si termina el juego
{
	return (((mew <= 0) && (mew2 <= 0) &&
		(pikachu <= 0) && (raichu <= 0) &&
		(kirlia <= 0) && (gardevoir <= 0) &&
		(staravia <= 0) && (staraptor <= 0) &&
		(pokebola <= 0)) ||
		(numPokemon <= 0));
}


int Tablero::MostrarScores(int type) const
{
	int arreglo[12];
	for (int i = 0; i < 12; ++i)
	{
		switch (i)
		{
		case 0:
			arreglo[0] = numEvoluciones;
			break;

		case 1:
			arreglo[1] = numPokemon;
			break;

		case 2:
			arreglo[2] = scoreTotal;
			break;

		case 3:
			arreglo[3] = mew;
			break;

		case 4:
			arreglo[4] = mew2;
			break;

		case 5:
			arreglo[5] = pikachu;
			break;

		case 6:
			arreglo[6] = raichu;
			break;

		case 7:
			arreglo[7] = kirlia;
			break;

		case 8:
			arreglo[8] = gardevoir;
			break;

		case 9:
			arreglo[9] = staravia;
			break;

		case 10:
			arreglo[10] = staraptor;
			break;

		case 11:
			arreglo[11] = pokebola;
			break;
		}
	}
	return arreglo[type];
}

Caja Tablero::BuscarCaja(int columna, int fila)
{
	for (int i = 0; i < 7; ++i)
	{
		for (int j = 0; j < 7; j++)
		{
			if (matriz[i][j].GetPosX() == columna &&						// i = filas 
				matriz[i][j].GetPosY() == fila )							// j = columnas
			{
				return matriz[i][j];
			}
		}
	}
}

int Tablero::BuscarCajaGuardar(int j, int i)
{
	return matriz[i][j].GetPokemon();
}


bool Tablero::EstaEntre(int limiteInferior, int limiteSuperior, int numero)
{
	if (limiteInferior < numero && numero < limiteSuperior)
	{
		return true;
	}
	else
	{
		return false;
	}
}





