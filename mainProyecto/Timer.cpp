#include "stdafx.h"
#include "Timer.h"
using namespace std::chrono;

Timer::Timer()
{
	ultimo = steady_clock::now();
}

float Timer::Mark()
{
	const auto anterior = ultimo;
	ultimo = steady_clock::now();
	const duration<float> tiempoTardado = ultimo - anterior;
	return tiempoTardado.count();
}
