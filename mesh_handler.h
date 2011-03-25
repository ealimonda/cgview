#ifndef MESH_HANDLER_H
#define MESH_HANDLER_H


/*
 *  Questa classe si occupa di gestire il vettore contenente tutte le mesh aperte
 */

// definisco i parametri opzionali per l'aggiunta delle mesh

#define _NO_ACTIVE 0x00000001
#define _NO_SELECT 0x00000010

#include "opengl/mesh/glmesh.h"

class MeshHandler
{

public:
        // Costruttore
        MeshHandler();

        // Distruttore
        ~MeshHandler();

        // Svuota il vettore:
        void clear();

        // Aggiunge una mesh al vettore (in coda o nella i-esima posizione),
        // eventualmente con impostazioni (selezionata o no).
        // se si usano le versioni senza impostazioni le nuove mesh vengono
        // auttomaticamente prese come attive e selezionate.

        void add(GLMesh);
        void add(GLMesh,int);

        //versioni con impostazioni, il parametro char contiene i bit di impostazione.
        void add(GLMesh, char);
        void add(GLMesh, int, char);

        // Rimuove la msh selezionata dall'elenco, o l'i-esima
        void remove();
        void remove(int);

        // Restituisce il numero di mesh aperte
        int count();

        // Restituisce l'indice della mesh attiva
        int active();

        // Restituisce il vettore delle mesh selezionate
        QVector<int> selected();

        // Permette di attivare una specifica mesh
        // (solo una mesh per volta può essere attivata)
        // rende falso se l'indice non è disponibile
        bool activate(int);

        // Permette di selezionare una mesh
        bool select(int);

        // Permette di deselezionare una mesh
        bool deselect(int);

        // restituisce una mesh

        GLMesh get_mesh(int);



        // disegna una mesh

        void inline draw_mesh( int i)
        {
            mesh_list[i].drawMesh();
        }

private:
        //vettore delle mesh aperte:
        std::vector<GLMesh> mesh_list;

        // vettore delle VERE mesh
        std::vector<CGMesh> cgmeshes;

        //indice della mesh attiva:
        // ( -1 se nessuna mesh è attiva)
        int active_index;

        //vettore degli indici delle mesh selezionate
        QVector<int> select_index;

        // metodi per la gestione dei parametri dei metodi add:

        // rende true se _NO_SELECT è tra i parametri
        bool is_par_noselect(char);

        // rende true se _NO_ACTIVE è tra i parametri
        bool is_par_noactive(char);


protected:



};

#endif // MESH_HANDLER_H
