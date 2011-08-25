/******************************************************************************
 *        CCCCCCC     GGGGGGG   VV     VV   II   EEEEEEEEE   WW       WW      *
 *      CC          GG           VV   VV    II   EE          WW       WW      *
 *      CC          GG     GG     VV VV     II   EEEEEE       WW  W  WW       *
 *      CC          GG     GG      VVV      II   EE            WW W WW        *
 *        CCCCCCC     GGGGGGG       V       II   EEEEEEEEE      W   W         *
 ******************************************************************************
 * University of Cagliari, Italy - Computer Graphics Group                    *
 * Filename: foo.cpp                                                          *
 * Description: CGView's engine                                               *
 *              Originally written by Fabio "Guga" Guggeri and Stefano Marras *
 ******************************************************************************
 * $Id::                                                       $: SVN Info    *
 * $Date::                                                     $: Last date   *
 * $Author::                                                   $: Last author *
 * $Revision::                                                 $: Revision    *
 ******************************************************************************/
#ifndef CGVIEW_ENGINE_H
#define CGVIEW_ENGINE_H

#include <QObject> // class QObject
#include "mesh_definition.h" // CGMesh

/**
 * Classe Engine
 *
 * La classe Engine è il cuore pulsante dell'applicazione. Essa infatti si occupa,
 * in maniera del tutto indipendente dalla visualizzazione, di caricare i file .off
 * e costruire le DCEL associate utilizzando i dati in essi contenuti. Consente inoltre
 * di salvare una mesh, contiene gli slot necessari per comunicare con l'esterno
 * ed ha già predisposto un metodo per il calcolo del Convex Hull.
 */
class Engine : public QObject
{
	Q_OBJECT

public:
	enum NewType
	{
		kTypePointCloud,
	};
	/**
	 * Enum per lo stato dell'algoritmo
	 * Distingue se la finestra è in attesa di input o se la dcel è stata calcolata
	 */
	enum state
	{
		kStateInput,
		kStateComputed,
	};

	/**
	 * Il costruttore della classe Engine
	 * Estende il costruttore della classe QObject, prendendo come parametro
	 * un eventuale widget che lo conterrà
	 */
	Engine(QObject *parent = 0);

	/** Carica un file dal nome specificato (noto a priori). **/
	void loadFile(QString filename);

	/** return index of active mesh **/
	int getActiveMesh(void);

public slots:
	/** Reset dell'applicazione che torna allo stato iniziale. */
	void reset(void);
	/** Consente di caricare un file scelto mediante una finestra di dialogo (non noto a priori). */
	void openFile(void);
	/** Consente di salvare un file .OFF (il convex hull). */
	void saveFile(void);
	/** Slot per il calcolo del convex hull */
	void calculateCH(void);

	void myFilter();

	void faceToVertQ(void);

	void newObject(void);

	void setActiveMesh(int a);

signals:
	/** Consente la visualizzazione della DCEL, inviandola al visualizzatore */
	void sendDcel(CGMesh* dc);
	void sendInfo(const unsigned int v, const unsigned int f, const unsigned int t, bool n);
	void loaded(bool tf);
	void updateWindow(void);
	void changeWindowTitle(QString title);

private:
	/** Crea la DCEL in base ai vertici inseriti dall'utente */
	bool createFromFile( QString filename );
	/// Lo stato dell'algoritmo
	state _s;
	///index of the active mesh (default: 0)
	int _active;
	///List of pointers to the meshes
	std::vector<CGMesh*> _meshlist;

};

#endif // CGVIEW_ENGINE_H
