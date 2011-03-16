#include "mesh_handler.h"


// Il costruttore inizializza semplicemente le variabili private
MeshHandler::MeshHandler()
{
    // metto a -1 l'indice della mesh attiva ad indicare che non ce ne sono
    // ancora:
    active_index = -1;
}


// Il distruttore semplicemente manda un clear per il vettore
MeshHandler::~MeshHandler()
{
    clear();
}

/*** Metodi Pubblici ***/

// il metodo clear che svuota il vettore

void MeshHandler::clear()
{
    mesh_list.clear();
}


// I metodi add:

// questo aggiunge una nuove mesh in coda
void MeshHandler::add(GLMesh mesh)
{


    mesh_list.push_back(mesh);
    int i = mesh_list.size()-1;

    // la nuova mesh viene automaticamente attivata e selezionata.
    select(i);
    activate(i);
}


// se si specifica un indice la mesh verrà inserita in quella posizione
//void MeshHandler::add(GLMesh mesh, int i)
//{
//    /*
//        il metodo insert della classe QVector fa si che
//        se i = 0 il la nuova mesh venga messa per prima, mentre
//        se i è più grande della dimensione del vettore viene accodato.
//    */

//    // se l'indice inserito è <0, è stata messa in testa, quindi aggiorno i a dovere.
//    if (i<0) i = 0;

//    // se invece l'indice esce dal range degli indici, la mesh viene messa in coda
//    if (i>mesh_list.size()) i = mesh_list.size();

//    mesh_list.insert(i,mesh_list,mesh);

//    // la nuova mesh viene automaticamente attivata e selezionata.
//    select(i);
//    activate(i);


//}

// questo aggiunge nuove mesh in coda impostando i parametri sul byte param
// i parametri sono _NO_ACTIVE se non si vuole che la nuova mesh sia attiva quando
// viene aggiunta, e _NO_SELECT se non si vuole che sia automaticamente salezionata.

void MeshHandler::add(GLMesh mesh, char par)
{
    int i;

    mesh_list.push_back(mesh);

    // se non si è usato il parametro _NO_SELECT la mesh viene selezionata
    if(!is_par_noselect(par))
    {
        i = mesh_list.size()-1;
        select(i);
    }

    //se non si è usato il parametro _NO_ACTIVE la mesh viene attivata
    if(!is_par_noactive(par))
    {
        i = mesh_list.size()-1;
        activate(i);
    }



}

// stessa cosa del precedente ma in posizione mesh_index-esima

//void MeshHandler::add(GLMesh mesh, int i, char par)
//{

//    // se l'indice inserito è <0, è stata messa in testa, quindi aggiorno i a dovere.
//    if (i<0) i = 0;

//    // se invece l'indice esce dal range degli indici, la mesh viene messa in coda
//    if (i>mesh_list.size()) i = mesh_list.size();

//    mesh_list.insert(i,mesh_list,mesh);


//    // se non si è usato il parametro _NO_SELECT la mesh viene selezionata
//    if(!is_par_noselect(par))
//    {
//        select(i);
//    }

//    //se non si è usato il parametro _NO_ACTIVE la mesh viene attivata
//    if(!is_par_noactive(par))
//    {
//        i = mesh_list.size()-1;
//        activate(i);
//    }



//}


// il metodo count restituisce il numero di mesh nel vettore

int MeshHandler::count()
{
    return mesh_list.size();
}


// Ottengo l'indice della mesh attiva,
int MeshHandler::active()
{
    return active_index;
}

// Rendo il vettore degli indici delle mesh selezionate
QVector<int> MeshHandler::selected()
{
    return select_index;
}


// Attivo una particolare mesh, disattivando tutte le
// altre. Se l'indice inserito non è disponibile rendo falso

bool MeshHandler::activate(int mesh_index)
{
    int n = mesh_list.size();

    //controllo che la mesh non sia già attiva, nel caso non faccio nulla
    if (mesh_index == active_index) return true;

    // Disattivo la mesh attualmente attiva
    mesh_list[active_index].setActive(false);

    //controllo che il valore inserito rientri nei valori,
    // se non succede gli assegno l'indice dell'ultima mesh inserita

    if(!( mesh_index > 0 && mesh_index < n)) return false;

    //attivo la mesh desiderata:
    mesh_list[mesh_index].setActive(true);

    //aggiorno l'indice della mesh attiva
    active_index = mesh_index;

    return true;
}

// Seleziono una particolare mesh
// Se l'indice inserito non rientra tra quelli
// disponibili non seleziona nessuna e rende false

bool MeshHandler::select(int mesh_index)
{
    int n = mesh_list.size();

    //controllo che la mesh non sia già selezonata, nel caso non faccio nulla
    if (select_index.contains(mesh_index)) return true;

     //controllo che il valore inserito rientri nei valori,
    // se non succede esco con false

    if(!( mesh_index > 0 && mesh_index < n)) return false;

    //seleziono la mesh desiderata:
    mesh_list[mesh_index].setSelect(true);

    //aggiorno il vettore delle mesh selezionate
    select_index.append(mesh_index);

    return true;
}

// deseleziono una particolare mesh

bool MeshHandler::deselect(int mesh_index)
{
    int i;

    // prima di tutto controllo se la mesh richiesta è davvero selezionata
    // se non lo è esco con false
    if(!select_index.contains(mesh_index)) return false;

    // se è effettivamente selezionata, a deseleziono
    mesh_list[mesh_index].setSelect(false);

    // e tolgo il suo indice dal vettore dei selezionati

    i = select_index.indexOf(mesh_index);
    select_index.remove(i);

    return true;
}


GLMesh MeshHandler::get_mesh ( int i )
{
    return mesh_list[i];
}




/*** metodi privati ***/

// metodi per la gestione dei parametri dei metodi add:

// rende true se _NO_SELECT è tra i parametri

bool MeshHandler::is_par_noselect(char par)
{

    if ( (par & _NO_SELECT) == 0 )
        return false;
    else
        return true;

}

// rende true se _NO_ACTIVE è tra i parametri

bool MeshHandler::is_par_noactive(char par)
{

    if ( (par & _NO_ACTIVE) == 0)
        return false;
    else
        return true;
}
