#pragma once
#include <string>
#include <vector>
using namespace std;

namespace warstrategy {
	class LoreEvent
	{
	public:
		string titulo;
		string imagePath;
		string texto;

		LoreEvent(string& titulo,string& imagePath, string& texto) {
			this->titulo= titulo;
			this->imagePath = imagePath;
			this->texto = texto;
		}
	};
}