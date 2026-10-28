#pragma once
#include "LoreViewer.h"
#include "LoreEvent.h"
#include "loreManager.h"
#include <string>
#include <vector>
namespace warstrategy {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Resumen de formMain
	/// </summary>
	public ref class formMain : public System::Windows::Forms::Form
	{
	public:
		formMain(void)
		{
			InitializeComponent();
			manager = new warstrategy::LoreManager();
			visorLore = gcnew LoreViewer();

			ConfigurarVisorLore();
			manager->MostrarDialogo("Hitler", "Comandante, hemos recibido un mensaje urgente.\n"
				"Las tropas enemigas han cruzado el puente del norte "
				"y avanzan hacia nuestra posición. Nuestros exploradores "
				"estiman que llegarán antes del amanecer.\n"
				"Debemos decidir si defendemos el puente o retiramos "
				"nuestras tropas para preparar una emboscada.\n"
				"Nuestros aliados todavía no han respondido. Si esperamos "
				"demasiado, podríamos perder la oportunidad de defender "
				"la ciudad.","imagenes\\images.jpeg", visorLore);

		}
	private:
		LoreViewer^ visorLore;
		warstrategy::LoreManager* manager;

		//config del lore box
		void ConfigurarVisorLore()
		{
			visorLore->Width = this->ClientSize.Width;
			visorLore->Height = 280;

			visorLore->Location = System::Drawing::Point(
				0,
				this->ClientSize.Height - visorLore->Height
			);

			visorLore->Anchor =
				AnchorStyles::Bottom |
				AnchorStyles::Left |
				AnchorStyles::Right;

			this->Controls->Add(visorLore);
			visorLore->BringToFront();
		}

	protected:
		/// <summary>
		/// Limpiar los recursos que se estén usando.
		/// </summary>
		~formMain()
		{
			if (components)
			{
				delete components;
			}
		}

	protected:

	private:
		/// <summary>
		/// Variable del diseñador necesaria.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Método necesario para admitir el Diseñador. No se puede modificar
		/// el contenido de este método con el editor de código.
		/// </summary>
		void InitializeComponent(void)
		{
			this->SuspendLayout();
			// 
			// formMain
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1154, 809);
			this->Name = L"formMain";
			this->Text = L"formMain";
			this->Load += gcnew System::EventHandler(this, &formMain::formMain_Load);
			this->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &formMain::formMain_Paint);
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void formMain_Load(System::Object^ sender, System::EventArgs^ e) {

	};
	private: System::Void formMain_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
		Graphics^ pg = e->Graphics;
		Pen^ pen = gcnew Pen(Color::Black, 1);
		int tam = 16;
		int filas = 40;
		int columnas = 40;
		for (int fila = 0; fila <= filas; fila++) {
			int y = 50 + fila * tam;
			pg->DrawLine(
				pen,
				50,
				y,
				50 + columnas * tam,
				y
			);
		}
		for (int columna = 0; columna <= columnas; columna++) {
			int x = 50 + columna * tam;
			pg->DrawLine(
				pen,
				x,
				50,
				x,
				50 + filas * tam
			);
		}
		delete pen;
	};
	};
}
