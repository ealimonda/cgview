/**********************************************************************
*                                                                     *
*    CCCCCCCCCC  GGGGGGGGGG  VV        VV                             *
*    CC          GG           VV      VV   II   EEEEE    W       W    *
*    CC          GG            VV    VV        E     E   W       W    *
*    CC          GG    GGGG     VV  VV     II  EEEEEE    W   W   W    *
*    CC          GG      GG      VVVV      II  E         W   W   W    *
*    CCCCCCCCCC  GGGGGGGGGG       VV       II   EEEEEE    WWW WWW     *
*                                                                     *
**********************************************************************/

/**
 * Motore dell'applicazione
 * By Fabio "Guga" Guggeri && Stefano Marras
 *************************/

#include <QWidget>
#include <QBrush>
#include <QString>
#include "mesh_definition.h"


/**
* Enum per lo stato dell'algoritmo
* Distingue se la finestra è in attesa di input o se la dcel è stata calcolata
**/
enum state { INPUT_M, COMPUTED_M };

/**
* Classe Engine
*
* La classe Engine è il cuore pulsante dell'applicazione. Essa infatti si occupa,
* in maniera del tutto indipendente dalla visualizzazione, di caricare i file .off
* e costruire le DCEL associate utilizzando i dati in essi contenuti. Consente inoltre
* di salvare una mesh, contiene gli slot necessari per comunicare con l'esterno
* ed ha già predisposto un metodo per il calcolo del Convex Hull.
**/
class Engine : public QObject
{
	Q_OBJECT

	private:
	/**
	* Lo stato dell'algoritmo
	**/
	state s;
	/**
	* La DCEL che verrà creata in seguito agli input dell'utente
	**/
        CGMesh d;

 	public:

        enum NewType
        {
            POINT_CLOUD,
        };

	/**
	* Il costruttore della classe Engine
	* Estende il costruttore della classe QWidget, prendendo come parametro
	* un eventuale widget che lo conterrà
	**/
     	Engine(QObject *parent = 0);

	/**
	* Carica un file dal nome specificato (noto a priori).
	*/
	void load_file( QString filename );

	signals:
	/**
	* Consente la visualizzazione della DCEL, inviandola al visualizzatore
	**/
        void sendDcel(CGMesh* dc);
        void sendInfo(const unsigned int v, const unsigned int f, const unsigned int t);
        void Loaded(bool tf);

        void UpdateWindow();

	public slots:
	/**
	* Reset dell'applicazione che torna allo stato iniziale.
	*/
	void reset(void);
	/**
	* Consente di caricare un file scelto mediante una finestra di dialogo (non noto a priori).
	*/	
	void open_file(void);
	/**
	* Consente di salvare un file .OFF (il convex hull).
	*/
	void save_file(void);
	/**
	* Slot per il calcolo del convex hull
	*/	
	void calculate_ch(void);

        void my_filter();

        void facetovert_q();

        void newObject();

	private:
	/**
	* Crea la DCEL in base ai vertici inseriti dall'utente
	**/
	bool create_from_file( QString filename );


};
