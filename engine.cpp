#include <QtGui>
#include <QFileDialog>
#include <QFile>
#include <QByteArray>
#include <stdio.h>
#include <stdlib.h>
#include <QColor>
#include "engine.h"
#include <cmath>
#include <string.h>

#include <wrap/io_trimesh/import.h>
#include <wrap/io_trimesh/import_OFF.h>
#include <wrap/io_trimesh/import_PLY.h>
#include <wrap/io_trimesh/export.h>
#include <vcg/complex/trimesh/allocate.h>
#include <vcg/complex/trimesh/update/normal.h>
#include <vcg/complex/trimesh/update/color.h>
#include <vcg/complex/trimesh/update/bounding.h>

#include "convex_hull/my_convhull.h"

#include "mesh_definition.h"

/**
* Il costruttore della classe Engine
* Estende il costruttore della classe QWidget, prendendo come parametro
* un eventuale widget che lo conterrà
**/
Engine::Engine(QObject *parent) : QObject(parent)
{
	// Inizializza le variabili
        s = INPUT_M;
	srand(time(NULL));
}

/**
* Carica un file e crea la mesh
* Funzione come open_file con la differenza che il nome del file
* è già noto a priori.
*/
void Engine::load_file( QString filename )	{

	if (!create_from_file( filename ))
		return;

        s = COMPUTED_M;
}

/*********************************************************************
* IMPLEMENTAZIONE DEGLI SLOT - RISPOSTA AI COMANDI FORNITI DALLA GUI *
*********************************************************************/

/**
* Apre un file e carica una DCEL
**/
void Engine::open_file ( void )
{
        QString filename = QFileDialog::getOpenFileName( NULL, "Apri mesh", "examples", "3D Meshes (*.off *.ply);;OFF (*.off);;PLY (*.ply)");

	if( !filename.isNull() )
	{
		if(!create_from_file( filename ))
		{
			return;
		}
                s = COMPUTED_M;
	}

}

/**
* Salva un file .OFF.
* Il file .OFF è ottenuto partendo dai dati contenuti nell'ultima DCEL che è stata inserita nel QVector d.
* Idealmente, questa DCEL dovrebbe corrisponde al Convex Hull (si veda a tal proposito il commento relativo
* al metodo per il calcolo del CH).
*/
void Engine::save_file( void )
{
	
        QFileDialog saveDialog( NULL, "Salva mesh", "examples", "3D Meshes (*.off *.ply);;OFF (*.off);;PLY (*.ply)");
	saveDialog.setDefaultSuffix( "off" );
	saveDialog.setAcceptMode( QFileDialog::AcceptSave );
	saveDialog.setConfirmOverwrite( true );
	saveDialog.setFileMode(QFileDialog::AnyFile);
	
	if( saveDialog.exec() )
	{
		QString filename = saveDialog.selectedFiles().takeFirst();
	
                int err;
                if(vcg::tri::io::Exporter<CGMesh>::FileExtension(filename.toStdString().c_str(),"off"))
                    err = vcg::tri::io::ExporterOFF<CGMesh>::Save(d, filename.toStdString().c_str());
                else if(vcg::tri::io::Importer<CGMesh>::FileExtension(filename.toStdString().c_str(),"ply"))
                    err = vcg::tri::io::ExporterPLY<CGMesh>::Save(d, filename.toStdString().c_str());
                if(err)
		{
                    printf("Error in saving %s: '%s'\n",filename.toStdString().c_str(), vcg::tri::io::Exporter<CGMesh>::ErrorMsg(err));

                    return;

                }
		

	}
}

/**
* Risponde al comando di reinizializzazione dell'algoritmo
* Reinizializza tutte le variabili e le strutture di supporto
**/
void Engine::reset(void)
{
        s = INPUT_M;

        d.Clear();
        Loaded(false);
}

/**
* Partendo dal file .off specificato come parametro, viene creata
* la DCEL associata che ha un vertice per ogni vertice dichiarato nel file,
* le facce aventi i vertici dichiarati e crea i corretti half-edges.
* Inoltre (bonus) effettua il calcolo delle normali dei vertici e delle facce.
*/
bool Engine::create_from_file( QString filename )
{

        //CGMesh tmp_d;
	// Decommentare le due righe seguenti se si vuole dare la possibilità di caricare più mesh	
        int err;
        if(vcg::tri::io::Importer<CGMesh>::FileExtension(filename.toStdString().c_str(),"off"))
        {
                err = vcg::tri::io::ImporterOFF<CGMesh>::Open(d, filename.toStdString().c_str());
        }
        else if(vcg::tri::io::Importer<CGMesh>::FileExtension(filename.toStdString().c_str(),"ply"))
        {
                err = vcg::tri::io::ImporterPLY<CGMesh>::Open(d, filename.toStdString().c_str());
        }

        if(err) { // all the importers return 0 in case of success
          printf("Error in reading %s: '%s'\n",filename.toStdString().c_str(), vcg::tri::io::Importer<CGMesh>::ErrorMsg(err));
          return false;
        }

        vcg::tri::UpdateBounding<CGMesh>::Box(d);
        for(int i = 0; i < d.vn; i++)
        {
            d.vert[i].P() = d.vert[i].P() - d.bbox.Center();
            d.vert[i].Q() = -1;
        }
        for(int i = 0; i < d.fn; i++)
        {
            d.face[i].Q() = -1;
        }

        vcg::tri::UpdateBounding<CGMesh>::Box(d);

        vcg::tri::UpdateTopology<CGMesh>::FaceFace(d);
        vcg::tri::UpdateNormals<CGMesh>::PerFace(d);
        //vcg::tri::UpdateNormals<CGMesh>::PerVertex(d);
        for(int i = 0; i < d.vn; i++)
        {
            d.vert[i].N() = CGPoint(0, 0, 0);
        }
        for(int i = 0; i < d.fn; i++)
        {
            for(int j = 0; j < 3; j++)
            {
                if((d.face[i].V(j)->N()[0] == 0) && (d.face[i].V(j)->N()[1] == 0) && (d.face[i].V(j)->N()[2] == 0))
                {
                    d.face[i].V(j)->N() = d.face[i].N();
                }
                else
                {
                    d.face[i].V(j)->N()[0] = (d.face[i].V(j)->N()[0] + d.face[i].N()[0]) / 2.0;
                    d.face[i].V(j)->N()[1] = (d.face[i].V(j)->N()[1] + d.face[i].N()[1]) / 2.0;
                    d.face[i].V(j)->N()[2] = (d.face[i].V(j)->N()[2] + d.face[i].N()[2]) / 2.0;
                }
            }
        }

        vcg::tri::UpdateNormals<CGMesh>::NormalizeVertex(d);
        vcg::tri::UpdateNormals<CGMesh>::NormalizeFace(d);



        emit sendDcel(&d);
        emit Loaded(true);
        emit sendInfo(d.vn, d.fn, 0);

	return true;
}

/**
 * Il metodo dovrà calcolare il Convex Hull dei punti precedentemente caricati.
 * Il convex hull dovrà essere calcolato sotto forma di DCEL, verrà visualizzato in trasparenza
 * sopra i punti precendemente inseriti e potrà essere salvato in un file off utilizzando
 * la funzione di salvataggio.
 */
void Engine::calculate_ch( void )
{
    QTime t;
    t.start();

    My_ConvHull* conv_hull = new My_ConvHull();
    conv_hull->setMesh(&d);

    conv_hull->apply();

    emit UpdateWindow();
    emit sendInfo(d.vn, d.fn, t.elapsed());
}

void Engine::facetovert_q()
{
    for(int i = 0; i < d.vn; i++)
    {
        d.vert[i].Q() = -1;
    }

    for(int i = 0; i < d.fn; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            if(d.face[i].V(j)->Q() == -1)
            {
                d.face[i].V(j)->Q() = d.face[i].Q();
            }
            else
            {
                d.face[i].V(j)->Q() = (d.face[i].V(j)->Q() + d.face[i].Q()) / 2;
            }
        }
    }
}

void Engine::newObject()
{
    NewType t = POINT_CLOUD;
    int X = 2;
    int Y = 1;

    d.Clear();

    //vcg::tri::Allocator<CGMesh>::AddVertices(d, X*Y);
    //vcg::tri::Allocator<CGMesh>::AddVertices(d, 3);
    //vcg::tri::Allocator<CGMesh>::AddFaces(d, 2*X*Y);
    //vcg::tri::Allocator<CGMesh>::AddFaces(d, 1);


    switch(t)
    {
    case POINT_CLOUD:
        {
            time(NULL);

            vcg::tri::Allocator<CGMesh>::AddVertices(d, 100);
            CGMesh::VertexPointer ivp[100];
            CGMesh::VertexIterator vi = d.vert.begin();
            for(int i = 0; i < 100; i++)
            {
                ivp[i] = &*vi;
                (*vi).P() = CGPoint(rand(), rand(), rand());
                ++vi;
            }



            /*CGMesh::VertexPointer ivp[3];
            CGMesh::VertexIterator vi = d.vert.begin();
            for(int i = 0; i < X; i++)
            {
                for(int j = 0; j < Y; j++)
                {
                    //Vertex
                    ivp[i + (j * Y)] = &*vi;
                    (*vi).P() = CGPoint(0 + i, 0 + j, 0);
                    ++vi;
                }
            }*/

            /*CGMesh::FaceIterator fi = d.face.begin();
            for(int i = 0; i < (X - 1); i++)
            {
                for(int j = 0; j < Y; j++)
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
            }*/
            /*CGMesh::FaceIterator fi = d.face.begin();
            (*fi).V(0) = ivp[0];
            (*fi).V(1) = ivp[1];
            (*fi).V(2) = ivp[2];*/
        }
        break;

    default: break;
    }

    vcg::tri::UpdateBounding<CGMesh>::Box(d);
    for(int i = 0; i < d.vn; i++)
    {
        d.vert[i].P() = d.vert[i].P() - d.bbox.Center();
        d.vert[i].Q() = -1;
    }
    vcg::tri::UpdateBounding<CGMesh>::Box(d);

    vcg::tri::UpdateTopology<CGMesh>::FaceFace(d);
    vcg::tri::UpdateNormals<CGMesh>::PerFace(d);
    //vcg::tri::UpdateNormals<CGMesh>::PerVertex(d);
    vcg::tri::UpdateNormals<CGMesh>::NormalizeVertex(d);
    vcg::tri::UpdateNormals<CGMesh>::NormalizeFace(d);

    for(int i = 0; i < d.fn; i++)
    {
        d.face[i].Q() = -1;
    }

    emit sendDcel(&d);
    emit Loaded(true);
    emit sendInfo(d.vn, d.fn, 0);
}

void Engine::my_filter()
{

}
