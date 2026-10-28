#pragma once
#include <iostream>
#include <vector>
#include "LoreEvent.h"
#include <string>
#include <msclr/marshal_cppstd.h>
namespace warstrategy {
	using namespace std;

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Resumen de LoreViewer
	/// </summary>
	public ref class LoreViewer : public System::Windows::Forms::UserControl
	{
	private:
		cli::array<System::String^>^ paginas;
		int indiceTexto;
		System::Windows::Forms::Timer^ temporizadorTexto;
		int cantidadCaracteres;
		int velocidadTexto;
		void DividirTexto(System::String^ texto)
		{
			System::Collections::Generic::List<System::String^>^ lista =
				gcnew System::Collections::Generic::List<System::String^>();

			int ancho = lblTexto->ClientSize.Width;
			int alto = lblTexto->ClientSize.Height;

			System::Drawing::Size espacioMedicion(ancho, 100000);

			System::Windows::Forms::TextFormatFlags opciones =
				System::Windows::Forms::TextFormatFlags::WordBreak |
				System::Windows::Forms::TextFormatFlags::TextBoxControl;

			int inicio = 0;

			while (inicio < texto->Length)
			{
				int fin = inicio + 1;
				int ultimoCorte = -1;

				while (fin <= texto->Length)
				{
					System::String^ candidato =
						texto->Substring(inicio, fin - inicio);

					System::Drawing::Size medida =
						TextRenderer::MeasureText(
							candidato,
							lblTexto->Font,
							espacioMedicion,
							opciones
						);

					if (medida.Height > alto)
						break;

					if (System::Char::IsWhiteSpace(texto[fin - 1]))
						ultimoCorte = fin;

					fin++;
				}

				if (fin > texto->Length)
				{
					lista->Add(texto->Substring(inicio));
					break;
				}

				int corte;

				if (ultimoCorte > inicio)
					corte = ultimoCorte;
				else
					corte = fin - 1;

				if (corte <= inicio)
					corte = inicio + 1;

				lista->Add(texto->Substring(inicio, corte - inicio));
				inicio = corte;
			}

			paginas = lista->ToArray();
		}
	public:
		LoreViewer(void)
		{
			InitializeComponent();
			//
			//TODO: agregar código de constructor aquí
			//
		}
		void MostrarEvento(LoreEvent* evento)
		{
			if (evento == nullptr)
				return;

			lblNombre->Text =
				msclr::interop::marshal_as<System::String^>(
					evento->titulo
				);

			System::String^ textoCompleto =
				msclr::interop::marshal_as<System::String^>(
					evento->texto
				);

			DividirTexto(textoCompleto);

			indiceTexto = 0;
			System::Diagnostics::Debug::WriteLine(
				"Panel: " + this->Size.ToString()
			);

			System::Diagnostics::Debug::WriteLine(
				"Etiqueta: " + lblTexto->Size.ToString()
			);

			System::Diagnostics::Debug::WriteLine(
				"Texto: " + lblTexto->Text->Length.ToString()
			);
			if (paginas->Length > 0)
				lblTexto->Text = paginas[indiceTexto];
			else
				lblTexto->Text = "";

			System::String^ ruta =
				msclr::interop::marshal_as<System::String^>(
					evento->imagePath
				);

			if (System::IO::File::Exists(ruta))
			{
				pictureBox1->Image = Image::FromFile(ruta);
				pictureBox1->SizeMode = PictureBoxSizeMode::Zoom;
			}

			this->Visible = true;
			this->BringToFront();
		}
		void AvanzarTexto()
		{
			if (paginas == nullptr)
				return;

			if (indiceTexto + 1 < paginas->Length)
			{
				indiceTexto++;
				lblTexto->Text = paginas[indiceTexto];
			}
			else
			{
				this->Visible = false;
			}
		}
		
	protected:
		/// <summary>
		/// Limpiar los recursos que se estén usando.
		/// </summary>
		~LoreViewer()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^ lblNombre;
	protected:
	private: System::Windows::Forms::Label^ lblTexto;
	private: System::Windows::Forms::PictureBox^ pictureBox1;
	private: System::Windows::Forms::Button^ btnContinuar;



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
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(LoreViewer::typeid));
			this->lblNombre = (gcnew System::Windows::Forms::Label());
			this->lblTexto = (gcnew System::Windows::Forms::Label());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->btnContinuar = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			this->SuspendLayout();
			// 
			// lblNombre
			// 
			this->lblNombre->AutoSize = true;
			this->lblNombre->Font = (gcnew System::Drawing::Font(L"MS Gothic", 20.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblNombre->ForeColor = System::Drawing::SystemColors::Control;
			this->lblNombre->Location = System::Drawing::Point(12, 28);
			this->lblNombre->Name = L"lblNombre";
			this->lblNombre->Size = System::Drawing::Size(102, 27);
			this->lblNombre->TabIndex = 0;
			this->lblNombre->Text = L"Prueba";
			this->lblNombre->Click += gcnew System::EventHandler(this, &LoreViewer::lblNombre_Click);
			// 
			// lblTexto
			// 
			this->lblTexto->BackColor = System::Drawing::Color::Transparent;
			this->lblTexto->Font = (gcnew System::Drawing::Font(L"MS Gothic", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblTexto->ForeColor = System::Drawing::SystemColors::Control;
			this->lblTexto->Location = System::Drawing::Point(13, 72);
			this->lblTexto->Name = L"lblTexto";
			this->lblTexto->Size = System::Drawing::Size(823, 148);
			this->lblTexto->TabIndex = 1;
			this->lblTexto->Text = resources->GetString(L"lblTexto.Text");
			// 
			// pictureBox1
			// 
			this->pictureBox1->Location = System::Drawing::Point(864, 12);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(239, 252);
			this->pictureBox1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->pictureBox1->TabIndex = 2;
			this->pictureBox1->TabStop = false;
			// 
			// btnContinuar
			// 
			this->btnContinuar->BackColor = System::Drawing::Color::Transparent;
			this->btnContinuar->Cursor = System::Windows::Forms::Cursors::Hand;
			this->btnContinuar->FlatAppearance->BorderColor = System::Drawing::Color::White;
			this->btnContinuar->FlatAppearance->BorderSize = 0;
			this->btnContinuar->FlatAppearance->MouseDownBackColor = System::Drawing::Color::Transparent;
			this->btnContinuar->FlatAppearance->MouseOverBackColor = System::Drawing::Color::Transparent;
			this->btnContinuar->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btnContinuar->Font = (gcnew System::Drawing::Font(L"MS Gothic", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnContinuar->ForeColor = System::Drawing::SystemColors::ControlLight;
			this->btnContinuar->Location = System::Drawing::Point(17, 241);
			this->btnContinuar->Name = L"btnContinuar";
			this->btnContinuar->Size = System::Drawing::Size(93, 23);
			this->btnContinuar->TabIndex = 3;
			this->btnContinuar->Text = L"Continuar >";
			this->btnContinuar->UseVisualStyleBackColor = false;
			this->btnContinuar->Click += gcnew System::EventHandler(this, &LoreViewer::button1_Click);
			// 
			// LoreViewer
			// 
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::None;
			this->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(45)), static_cast<System::Int32>(static_cast<System::Byte>(45)),
				static_cast<System::Int32>(static_cast<System::Byte>(50)));
			this->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->Controls->Add(this->btnContinuar);
			this->Controls->Add(this->pictureBox1);
			this->Controls->Add(this->lblTexto);
			this->Controls->Add(this->lblNombre);
			this->Name = L"LoreViewer";
			this->Size = System::Drawing::Size(1127, 280);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void lblNombre_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
		AvanzarTexto();
	}
};
}
