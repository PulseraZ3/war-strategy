#pragma once

#include "LoreEvent.h"
namespace warstrategy 
{
	class LoreManager {
		private:
			vector<LoreEvent> eventos;
	public:
		void MostrarDialogo(string nombre, string texto, System::String^ path, LoreViewer^ visor)
		{
			String^ carpetaJuego = Application::StartupPath;
			String^ rutaImagen = System::IO::Path::Combine(
				carpetaJuego,
				path
			);
			std::string imagePath = msclr::interop::marshal_as<string>(rutaImagen);


			LoreEvent evento(nombre, imagePath, texto);

			visor->MostrarEvento(&evento);
		}
		void AgregarEvento(
			string titulo,
			string imagen,
			string texto
		) {
			eventos.emplace_back(titulo, imagen, texto);
		}
		LoreEvent* BuscarEvento(int indice) {
			if (indice < 0 || indice >= eventos.size())
			{
				return nullptr;
			}
			return &eventos[indice];
		}
		int cantidadEventos()
		{
			return eventos.size();
		}
		LoreEvent* CrearEvento(
			string titulo,
			string imagen,
			string texto
		) {
			return new LoreEvent(titulo, imagen, texto);
		}
	};
}