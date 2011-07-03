/******************************************************************************
 *        CCCCCCC     GGGGGGG   VV     VV   II   EEEEEEEEE   WW       WW      *
 *      CC          GG           VV   VV    II   EE          WW       WW      *
 *      CC          GG     GG     VV VV     II   EEEEEE       WW  W  WW       *
 *      CC          GG     GG      VVV      II   EE            WW W WW        *
 *        CCCCCCC     GGGGGGG       V       II   EEEEEEEEE      W   W         *
 ******************************************************************************
 * University of Cagliari, Italy - Computer Graphics Group                    *
 * Filename: engine.cpp                                                       *
 * Description: CGView's engine                                               *
 ******************************************************************************
 * $Id::                                                       $: SVN Info    *
 * $Date::                                                     $: Last date   *
 * $Author::                                                   $: Last author *
 * $Revision::                                                 $: Revision    *
 ******************************************************************************/
#include "engine.h"

#include <QFileDialog> // class QFileDialog
#include <QTime> // class QTime

#include <wrap/io_trimesh/import.h> // vcg::tri::io
//#include <wrap/io_trimesh/import_OFF.h>
#include <wrap/io_trimesh/import_PLY.h> // vcg::tri::io::ImporterPLY
#include <wrap/io_trimesh/export.h> // vcg::tri::io::Exporter

//#include <vcg/complex/allocate.h> // vcg::tri::Allocator
#include <vcg/complex/trimesh/allocate.h>

//#include <vcg/complex/algorithms/update/normal.h> // vcg::tri::UpdateNormals
#include <vcg/complex/trimesh/update/normal.h>

//#include <vcg/complex/trimesh/update/color.h>

//#include <vcg/complex/algorithms/update/bounding.h> // vcg::tri::UpdateBounding
#include <vcg/complex/trimesh/update/bounding.h>

#include "convex_hull/my_convhull.h"
#include "mesh_definition.h" // CG*
#include "prefcontroller.h" // PrefController

/**
 * Il costruttore della classe Engine
 */
Engine::Engine(QObject *parent) : QObject(parent)
{
	// Inizializza le variabili
	this->_s = Engine::kStateInput;
	srand(time(NULL));
}

/**
 * Carica un file e crea la mesh
 * Funzione come open_file con la differenza che il nome del file
 * è già noto a priori.
 */
void Engine::loadFile(QString filename)
{
	if( !this->createFromFile(filename) )
		return;

	this->_s = Engine::kStateComputed;
}

/**********************************************************************
 * IMPLEMENTAZIONE DEGLI SLOT - RISPOSTA AI COMANDI FORNITI DALLA GUI *
 *********************************************************************/

/** 
 * Apre un file e carica una DCEL
 */
void Engine::openFile(void)
{
	QString filename = QFileDialog::getOpenFileName(NULL, "Apri mesh",
			PrefController::sharedInstance()->defaultDirectory(),
			"3D Meshes (*.off *.ply);;"\
			"Object File Format (*.off);;"\
			"Stanford Polygon Fil Format (*.ply);;"\
			"Any file (*.*)"
	);

	if (filename.isNull())
		return;

	if (!this->createFromFile(filename))
		return;

	this->_s = Engine::kStateComputed;
}

/**
 * Salva un file .OFF.
 * Il file .OFF è ottenuto partendo dai dati contenuti nell'ultima DCEL che è stata inserita nel QVector d.
 * Idealmente, questa DCEL dovrebbe corrisponde al Convex Hull (si veda a tal proposito il commento relativo
 * al metodo per il calcolo del CH).
 */
void Engine::saveFile(void)
{
	QFileDialog saveDialog(NULL, "Salva mesh", PrefController::sharedInstance()->defaultDirectory(),
			"3D Meshes (*.off *.ply);;"\
			"Object File Format (*.off);;"\
			"Stanford Polygon Fil Format (*.ply)"
	);
	saveDialog.setDefaultSuffix("off");
	saveDialog.setAcceptMode(QFileDialog::AcceptSave);
	saveDialog.setConfirmOverwrite(true);
	saveDialog.setFileMode(QFileDialog::AnyFile);
	
	if (!saveDialog.exec())
		return;

	QString filename = saveDialog.selectedFiles().takeFirst();
	int err = -1;
	if (vcg::tri::io::Exporter<CGMesh>::FileExtension(filename.toStdString().c_str(),"off"))
		err = vcg::tri::io::ExporterOFF<CGMesh>::Save(this->_d, filename.toStdString().c_str());
	else if (vcg::tri::io::Importer<CGMesh>::FileExtension(filename.toStdString().c_str(),"ply"))
		err = vcg::tri::io::ExporterPLY<CGMesh>::Save(this->_d, filename.toStdString().c_str());
	if (err)
	{
		printf("Error in saving %s: '%s'\n", filename.toStdString().c_str(),
				vcg::tri::io::Exporter<CGMesh>::ErrorMsg(err));
		return;
	}
}

/**
 * Risponde al comando di reinizializzazione dell'algoritmo
 * Reinizializza tutte le variabili e le strutture di supporto
 */
void Engine::reset(void)
{
	this->_s = Engine::kStateInput;
	this->_d.Clear();
	this->loaded(false);
}

/**
 * Partendo dal file .off specificato come parametro, viene creata
 * la DCEL associata che ha un vertice per ogni vertice dichiarato nel file,
 * le facce aventi i vertici dichiarati e crea i corretti half-edges.
 * Inoltre (bonus) effettua il calcolo delle normali dei vertici e delle facce.
 */
bool Engine::createFromFile( QString filename ) {
	//CGMesh tmp_d;
	// Decommentare le due righe seguenti se si vuole dare la possibilità di caricare più mesh
	int err = -1;
	if (vcg::tri::io::Importer<CGMesh>::FileExtension(filename.toStdString().c_str(),"off") )
	{
		err = vcg::tri::io::ImporterOFF<CGMesh>::Open(this->_d, filename.toStdString().c_str());
	}
	else if (vcg::tri::io::Importer<CGMesh>::FileExtension(filename.toStdString().c_str(),"ply"))
	{
		err = vcg::tri::io::ImporterPLY<CGMesh>::Open(this->_d, filename.toStdString().c_str());
	}

	if (err)
	{
		// all the importers return 0 in case of success
		printf("Error in reading %s: '%s'\n", filename.toStdString().c_str(),
				vcg::tri::io::Importer<CGMesh>::ErrorMsg(err));
		return false;
	}
	vcg::tri::UpdateBounding<CGMesh>::Box(this->_d);
	for (int i = 0; i < this->_d.vn; ++i)
	{
		this->_d.vert[i].P() = this->_d.vert[i].P() - this->_d.bbox.Center();
		this->_d.vert[i].Q() = -1;
	}
	for (int i = 0; i < this->_d.fn; ++i)
	{
		this->_d.face[i].Q() = -1;
	}
	vcg::tri::UpdateBounding<CGMesh>::Box(this->_d);
	vcg::tri::UpdateTopology<CGMesh>::FaceFace(this->_d);
	vcg::tri::UpdateNormals<CGMesh>::PerFace(this->_d);
	//vcg::tri::UpdateNormals<CGMesh>::PerVertex(this->_d);
	for (int i = 0; i < this->_d.vn; ++i)
	{
		this->_d.vert[i].N() = CGPoint(0, 0, 0);
	}
	for (int i = 0; i < this->_d.fn; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			if (
					(this->_d.face[i].V(j)->N()[0] == 0)
					&& (this->_d.face[i].V(j)->N()[1] == 0)
					&& (this->_d.face[i].V(j)->N()[2] == 0)
			)
			{
				this->_d.face[i].V(j)->N() = this->_d.face[i].N();
			}
			else
			{
				this->_d.face[i].V(j)->N()[0] = (this->_d.face[i].V(j)->N()[0] + this->_d.face[i].N()[0]) / 2.0;
				this->_d.face[i].V(j)->N()[1] = (this->_d.face[i].V(j)->N()[1] + this->_d.face[i].N()[1]) / 2.0;
				this->_d.face[i].V(j)->N()[2] = (this->_d.face[i].V(j)->N()[2] + this->_d.face[i].N()[2]) / 2.0;
			}
		}
	}
	vcg::tri::UpdateNormals<CGMesh>::NormalizeVertex(this->_d);
	vcg::tri::UpdateNormals<CGMesh>::NormalizeFace(this->_d);


	emit sendDcel(&this->_d);
	emit loaded(true);
	emit sendInfo(this->_d.vn, this->_d.fn, 0);

	return true;
}

/**
 * Il metodo dovrà calcolare il Convex Hull dei punti precedentemente caricati.
 * Il convex hull dovrà essere calcolato sotto forma di DCEL, verrà visualizzato in trasparenza
 * sopra i punti precendemente inseriti e potrà essere salvato in un file off utilizzando
 * la funzione di salvataggio.
 */
void Engine::calculateCH(void)
{
    QTime t;
    t.start();

    My_ConvHull* conv_hull = new My_ConvHull();
    conv_hull->setMesh(&this->_d);

    conv_hull->apply();

    emit updateWindow();
    emit sendInfo(this->_d.vn, this->_d.fn, t.elapsed());
}

void Engine::faceToVertQ(void)
{
	for (int i = 0; i < this->_d.vn; ++i)
	{
		this->_d.vert[i].Q() = -1;
	}
	for (int i = 0; i < this->_d.fn; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			if (this->_d.face[i].V(j)->Q() == -1)
			{
				this->_d.face[i].V(j)->Q() = this->_d.face[i].Q();
			}
			else
			{
				this->_d.face[i].V(j)->Q() = (this->_d.face[i].V(j)->Q() + this->_d.face[i].Q()) / 2;
			}
		}
	}
}

void Engine::newObject(void)
{
	NewType t = kTypePointCloud;
	//int X = 2;
	//int Y = 1;

	this->_d.Clear();

	//vcg::tri::Allocator<CGMesh>::AddVertices(this->_d, X*Y);
	//vcg::tri::Allocator<CGMesh>::AddVertices(this->_d, 3);
	//vcg::tri::Allocator<CGMesh>::AddFaces(this->_d, 2*X*Y);
	//vcg::tri::Allocator<CGMesh>::AddFaces(this->_d, 1);

	switch (t)
	{
	case kTypePointCloud:
	  {
		time(NULL);

		vcg::tri::Allocator<CGMesh>::AddVertices(this->_d, 100);
		CGMesh::VertexPointer ivp[100];
		CGMesh::VertexIterator vi = this->_d.vert.begin();
		for (int i = 0; i < 100; i++)
		{
			ivp[i] = &*vi;
			(*vi).P() = CGPoint(rand(), rand(), rand());
			++vi;
		}

#if 0
		CGMesh::VertexPointer ivp[3];
		CGMesh::VertexIterator vi = this->_d.vert.begin();
		for (int i = 0; i < X; ++i)
		{
			for (int j = 0; j < Y; ++j)
			{
				//Vertex
				ivp[i + (j * Y)] = &*vi;
				(*vi).P() = CGPoint(0 + i, 0 + j, 0);
				++vi;
			}
		}
#endif // 0

#if 0
		CGMesh::FaceIterator fi = this->_d.face.begin();
		for (int i = 0; i < (X - 1); ++i)
		{
			for (int j = 0; j < Y; j++)
			{
				//Face
				(*fi).V(0) = ivp[i + (j * Y)];
				(*fi).V(1) = ivp[(i + 1) + (j * Y)];
				(*fi).V(2) = ivp[i + ((j + 1) * Y)];
				++fi;

				(*fi).V(0) = ivp[i + ((j + 1) * Y)];
				(*fi).V(1) = ivp[(i + 1) + (j * Y)];
				(*fi).V(2) = ivp[(i + 1) + ((j + 1) * Y)];
				++fi;
			}
		}
#endif // 0

#if 0
		CGMesh::FaceIterator fi = this->_d.face.begin();
		(*fi).V(0) = ivp[0];
		(*fi).V(1) = ivp[1];
		(*fi).V(2) = ivp[2];
#endif // 0
	  }
		break;
	}

	vcg::tri::UpdateBounding<CGMesh>::Box(this->_d);
	for (int i = 0; i < this->_d.vn; ++i)
	{
		this->_d.vert[i].P() = this->_d.vert[i].P() - this->_d.bbox.Center();
		this->_d.vert[i].Q() = -1;
	}
	vcg::tri::UpdateBounding<CGMesh>::Box(this->_d);

	vcg::tri::UpdateTopology<CGMesh>::FaceFace(this->_d);
	vcg::tri::UpdateNormals<CGMesh>::PerFace(this->_d);
	//vcg::tri::UpdateNormals<CGMesh>::PerVertex(this->_d);
	vcg::tri::UpdateNormals<CGMesh>::NormalizeVertex(this->_d);
	vcg::tri::UpdateNormals<CGMesh>::NormalizeFace(this->_d);

	for (int i = 0; i < this->_d.fn; ++i)
	{
		this->_d.face[i].Q() = -1;
	}

	emit sendDcel(&this->_d);
	emit loaded(true);
	emit sendInfo(this->_d.vn, this->_d.fn, 0);
}

void Engine::myFilter(void)
{

}
