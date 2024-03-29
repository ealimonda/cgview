/****************************************************************************
* VCGLib                                                            o o     *
* Visual and Computer Graphics Library                            o     o   *
*                                                                _   O  _   *
* Copyright(C) 2004                                                \/)\/    *
* Visual Computing Lab                                            /\/|      *
* ISTI - Italian National Research Council                           |      *
*                                                                    \      *
* All rights reserved.                                                      *
*                                                                           *
* This program is free software; you can redistribute it and/or modify      *   
* it under the terms of the GNU General Public License as published by      *
* the Free Software Foundation; either version 2 of the License, or         *
* (at your option) any later version.                                       *
*                                                                           *
* This program is distributed in the hope that it will be useful,           *
* but WITHOUT ANY WARRANTY; without even the implied warranty of            *
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             *
* GNU General Public License (http://www.gnu.org/licenses/gpl.txt)          *
* for more details.                                                         *
*                                                                           *
****************************************************************************/

#ifndef __VCGLIB_TRIALLOCATOR
#define __VCGLIB_TRIALLOCATOR

#include <typeinfo>
#include <vector>
#include <map>
#include <string>
#include <set>
#include <assert.h>
#include <vcg/container/simple_temporary_data.h>

namespace vcg {

	class PointerToAttribute
	{
	public:
		SimpleTempDataBase * _handle;		// pointer to the SimpleTempData that stores the attribute
		std::string _name;					// name of the attribute
		int _sizeof;						// size of the attribute type (used only with VMI loading)
		int _padding;						// padding 	(used only with VMI loading)

		int n_attr;							// unique ID of the attribute

		void Resize(const int & sz){((SimpleTempDataBase *)_handle)->Resize(sz);}
		void Reorder(std::vector<size_t> & newVertIndex){((SimpleTempDataBase *)_handle)->Reorder(newVertIndex);}
		bool operator<(const  PointerToAttribute    b) const {	return(_name.empty()&&b._name.empty())?(_handle < b._handle):( _name < b._name);}
	};

	namespace tri {
		/** \addtogroup trimesh */
		
		template<class MeshType>
		size_t Index(MeshType &m, typename MeshType::VertexType &v) {return &v-&*m.vert.begin();}
		template<class MeshType>
		size_t Index(MeshType &m, typename MeshType::FaceType &f) {return &f-&*m.face.begin();}
		template<class MeshType>
		size_t Index(MeshType &m, typename MeshType::EdgeType &e) {return &e-&*m.edge.begin();}
		template<class MeshType>
		size_t Index(MeshType &m, typename MeshType::HEdgeType &h) {return &h-&*m.hedge.begin();}

		template<class MeshType>
		size_t Index(MeshType &m, const typename MeshType::VertexType *vp) {return vp-&*m.vert.begin();}
		template<class MeshType>
		size_t Index(MeshType &m, const typename MeshType::FaceType * fp) {return fp-&*m.face.begin();}
		template<class MeshType>
    size_t Index(MeshType &m, const typename MeshType::EdgeType*  e) {return e-&*m.edge.begin();}
		template<class MeshType>
    size_t Index(MeshType &m, const typename MeshType::HEdgeType*  h) {return h-&*m.hedge.begin();}
		
		template <class MeshType, class ATTR_CONT>
		void ReorderAttribute(ATTR_CONT &c,std::vector<size_t> & newVertIndex, MeshType & /* m */){
			typename std::set<typename MeshType::PointerToAttribute>::iterator ai;	
				for(ai = c.begin(); ai != c.end(); ++ai)
					((typename MeshType::PointerToAttribute)(*ai)).Reorder(newVertIndex);
		}

		template <class MeshType, class ATTR_CONT>
    void ResizeAttribute(ATTR_CONT &c,const int &   sz  , MeshType &/*m*/){
			typename std::set<typename MeshType::PointerToAttribute>::iterator ai;	
				for(ai =c.begin(); ai != c.end(); ++ai)
					((typename MeshType::PointerToAttribute)(*ai)).Resize(sz);
		}

		/*@{*/
		/// Class to safely add vertexes and faces to a mesh updating all the involved pointers.
		/// It provides static memeber to add either vertex or faces to a trimesh.
		template <class AllocateMeshType>
		class Allocator
		{

		public:
			typedef AllocateMeshType MeshType;
			typedef typename MeshType::VertexType     VertexType;
			typedef typename MeshType::VertexPointer  VertexPointer;
			typedef typename MeshType::VertexIterator VertexIterator;
			typedef typename MeshType::VertContainer VertContainer;

			typedef typename MeshType::EdgeType     EdgeType;
			typedef typename MeshType::EdgePointer  EdgePointer;
			typedef typename MeshType::EdgeIterator EdgeIterator;
			typedef typename MeshType::EdgeContainer EdgeContainer;

			typedef typename MeshType::FaceType       FaceType;
			typedef typename MeshType::FacePointer    FacePointer;
			typedef typename MeshType::FaceIterator   FaceIterator;
			typedef typename MeshType::FaceContainer FaceContainer;

			typedef typename MeshType::HEdgeType     HEdgeType;
			typedef typename MeshType::HEdgePointer  HEdgePointer;
			typedef typename MeshType::HEdgeIterator HEdgeIterator;
			typedef typename MeshType::HEdgeContainer HEdgeContainer;


			typedef typename MeshType::PointerToAttribute PointerToAttribute;
			typedef typename std::set<PointerToAttribute>::iterator AttrIterator;
			typedef typename std::set<PointerToAttribute>::const_iterator AttrConstIterator;
			typedef typename std::set<PointerToAttribute >::iterator PAIte;

			/** This class is used when allocating new vertexes and faces to update 
			the pointers that can be changed when resizing the involved vectors of vertex or faces.
			It can also be used to prevent any update of the various mesh fields
			(e.g. in case you are building all the connections by hand as in a importer);
			*/ 
			template<class SimplexPointerType>
			class PointerUpdater
			{
			public:
				PointerUpdater(void) : newBase(0), oldBase(0), newEnd(0), oldEnd(0), preventUpdateFlag(false) { ; }
        void Clear(){newBase=oldBase=newEnd=oldEnd=0;}
				void Update(SimplexPointerType &vp)
				{
					//if(vp>=newBase && vp<newEnd) return;
					if(vp<oldBase || vp>oldEnd) return;
					assert(vp>=oldBase);
					assert(vp<oldEnd);
					vp=newBase+(vp-oldBase);
					if(!remap.empty())
            vp  = newBase + remap[vp-newBase];
				}
				bool NeedUpdate() {if((oldBase && newBase!=oldBase && !preventUpdateFlag) || !remap.empty()) return true; else return false;}

				SimplexPointerType newBase;
				SimplexPointerType oldBase;
				SimplexPointerType newEnd;
				SimplexPointerType oldEnd;
				std::vector<size_t> remap;

				bool preventUpdateFlag; /// when true no update is considered necessary.
			};


			/** Function to add n vertices to the mesh. The second parameter hold a vector of 
			pointers to pointer to elements of the mesh that should be updated after a 
			possible vector realloc. 
			@param n Il numero di vertici che si vuole aggiungere alla mesh.
			@param local_var Vettore di variabili locali che rappresentano puntatori a vertici. 
			restituisce l'iteratore al primo elemento aggiunto.
			*/
			static VertexIterator AddVertices(MeshType &m,int n, PointerUpdater<VertexPointer> &pu)
			{
				VertexIterator last;
				if(n == 0) return m.vert.end();
				pu.Clear();
				if(m.vert.empty()) pu.oldBase=0;  // if the vector is empty we cannot find the last valid element
        else {
          pu.oldBase=&*m.vert.begin(); 
  				pu.oldEnd=&m.vert.back()+1; 
        }

				m.vert.resize(m.vert.size()+n);
				m.vn+=n;

				typename std::set<PointerToAttribute>::iterator ai;
				for(ai = m.vert_attr.begin(); ai != m.vert_attr.end(); ++ai)
					((PointerToAttribute)(*ai)).Resize(m.vert.size());

				pu.newBase = &*m.vert.begin();
				pu.newEnd =  &m.vert.back()+1; 
                                if(pu.NeedUpdate())
					{
					FaceIterator fi;
					for (fi=m.face.begin(); fi!=m.face.end(); ++fi)
						if(!(*fi).IsD())
							for(int i=0; i < (*fi).VN(); ++i)
								if ((*fi).cV(i)!=0) pu.Update((*fi).V(i));
					EdgeIterator ei;
					for (ei=m.edge.begin(); ei!=m.edge.end(); ++ei)
						if(!(*ei).IsD())
						{
              if(HasEVAdjacency (m)) { pu.Update((*ei).V(0));pu.Update((*ei).V(1));}
//							if(HasEVAdjacency(m))   pu.Update((*ei).EVp());
						}
                                        HEdgeIterator hi;
                                        for (hi=m.hedge.begin(); hi!=m.hedge.end(); ++hi)
                                                if(!(*hi).IsD())
                                                {
                                                        if(HasHVAdjacency (m))
                                                        {
                                                            pu.Update((*hi).HVp());
                                                        }
                                                }

						// e poiche' lo spazio e' cambiato si ricalcola anche last da zero  
				}
				unsigned int siz=(unsigned int)m.vert.size()-n;	
			
				last = m.vert.begin(); 
				advance(last,siz);
			
				return last;// deve restituire l'iteratore alla prima faccia aggiunta;
			}

			/** Function to add n vertices to the mesh.
			First wrapper, with no parameters
			*/
			static VertexIterator AddVertices(MeshType &m, int n)
			{
				PointerUpdater<VertexPointer> pu;
				return AddVertices(m, n,pu);
			}

			/** Function to add n vertices to the mesh.
			Second Wrapper, with a vector of vertex pointers to be updated.
			*/
			static VertexIterator AddVertices(MeshType &m, int n, std::vector<VertexPointer *> &local_vec)
			{
				PointerUpdater<VertexPointer> pu;
				VertexIterator v_ret =  AddVertices(m, n,pu);

				typename std::vector<VertexPointer *>::iterator vi;
            for(vi=local_vec.begin();vi!=local_vec.end();++vi)
               pu.Update(**vi);
				return v_ret;
			}

      /* ++++++++++ edges +++++++++++++ */
			/** Function to add n edges to the mesh. The second parameter hold a vector of 
			pointers to pointer to elements of the mesh that should be updated after a 
			possible vector realloc. 
			@param n number of edges to be added
			@param local_var vector of pointers to pointers to edges to be updated.
			return an iterator to the first element added
			*/
			static EdgeIterator AddEdges(MeshType &m,int n, PointerUpdater<EdgePointer> &pu)
			{
				EdgeIterator last;
				if(n == 0) return m.edge.end();
				pu.Clear();
				if(m.edge.empty()) pu.oldBase=0;  // if the vector is empty we cannot find the last valid element
				else {
					pu.oldBase=&*m.edge.begin(); 
					pu.oldEnd=&m.edge.back()+1; 
				}

				m.edge.resize(m.edge.size()+n);
				m.en+=n;

				typename std::set<typename MeshType::PointerToAttribute>::iterator ai;
				for(ai = m.edge_attr.begin(); ai != m.edge_attr.end(); ++ai)
					((typename MeshType::PointerToAttribute)(*ai)).Resize(m.edge.size());

				pu.newBase = &*m.edge.begin();
				pu.newEnd =  &m.edge.back()+1; 
                                 if(pu.NeedUpdate())
					{
					FaceIterator fi;
					for (fi=m.face.begin(); fi!=m.face.end(); ++fi){
                                                //if(HasFHEAdjacency(m))
                                                //        pu.Update((*fi).FHEp());
						if(!(*fi).IsD())
							for(int i=0; i < (*fi).VN(); ++i)
								if ((*fi).cFEp(i)!=0) pu.Update((*fi).FEp(i));
					}

					VertexIterator vi;
                                        if(HasVEAdjacency(m))
                                            for (vi=m.vert.begin(); vi!=m.vert.end(); ++vi)
						if(!(*vi).IsD())
                                                        if ((*vi).cVEp()!=0) pu.Update((*vi).VEp());

                                        HEdgeIterator hi;
                                        if(HasHEAdjacency(m))
                                            for (hi=m.hedge.begin(); hi!=m.hedge.end(); ++hi)
                                                if(!(*hi).IsD())
                                                        if ((*hi).cHEp()!=0) pu.Update((*hi).HEp());



				}
				unsigned int siz=(unsigned int)m.edge.size()-n;	
			
				last = m.edge.begin(); 
				advance(last,siz);
			
				return last;// deve restituire l'iteratore alla prima faccia aggiunta;
			}

			/** Function to add n vertices to the mesh.
			First wrapper, with no parameters
			*/
			static EdgeIterator AddEdges(MeshType &m, int n)
			{
				PointerUpdater<EdgePointer> pu;
				return AddEdges(m, n,pu);
			}

      /** Function to add n vertices to the mesh.
			Second Wrapper, with a vector of vertex pointers to be updated.
			*/
			static EdgeIterator AddEdges(MeshType &m, int n, std::vector<EdgePointer*> &local_vec)
			{
				PointerUpdater<EdgePointer> pu;
				EdgeIterator v_ret =  AddEdges(m, n,pu);

				typename std::vector<EdgePointer *>::iterator ei;
            for(ei=local_vec.begin();ei!=local_vec.end();++ei)
               pu.Update(**ei);
				return v_ret;
			}


      /* ++++++++++ hedges +++++++++++++ */
			/** Function to add n edges to the mesh. The second parameter hold a vector of
			pointers to pointer to elements of the mesh that should be updated after a
			possible vector realloc.
			@param n number of edges to be added
			@param local_var vector of pointers to pointers to edges to be updated.
			return an iterator to the first element added
			*/
			static HEdgeIterator AddHEdges(MeshType &m,int n, PointerUpdater<HEdgePointer> &pu)
			{
				HEdgeIterator last;
				if(n == 0) return m.hedge.end();
				pu.Clear();
				if(m.hedge.empty()) pu.oldBase=0;  // if the vector is empty we cannot find the last valid element
				else {
					pu.oldBase=&*m.hedge.begin();
					pu.oldEnd=&m.hedge.back()+1;
				}

				m.hedge.resize(m.hedge.size()+n);
				m.hn+=n;

				pu.newBase = &*m.hedge.begin();
				pu.newEnd =  &m.hedge.back()+1;

                                if(pu.NeedUpdate())
                                {
                                    int ii = 0;
                                    FaceIterator fi;
                                    for (fi=m.face.begin(); fi!=m.face.end(); ++fi)
                                    {
                                        if(HasFHAdjacency(m))
                                            if(!(*fi).IsD() && (*fi).FHp())
																								pu.Update((*fi).FHp());
                                    }

                                    {
                                    VertexIterator vi;
                                    for (vi=m.vert.begin(); vi!=m.vert.end(); ++vi)
                                        if(HasVHAdjacency(m))
                                            if(!(*vi).IsD())
                                                if ((*vi).cVHp()!=0)
                                                    pu.Update((*vi).VHp());
                                    }

                                    {
                                    EdgeIterator ei;
                                    for (ei=m.edge.begin(); ei!=m.edge.end(); ++ei)
                                        if(HasEHAdjacency(m))
                                            if(!(*ei).IsD())
                                                if ((*ei).cEHp()!=0)
                                                    pu.Update((*ei).EHp());
                                    }

                                    {
                                    HEdgeIterator hi = m.hedge.begin();
                                    while(ii < m.hn - n)// cycle on all the faces except the new ones
                                    {
                                        if(!(*hi).IsD())
                                        {
                                            if(HasHNextAdjacency(m)) pu.Update((*hi).HNp());
                                            if(HasHPrevAdjacency(m)) pu.Update((*hi).HPp());
                                            if(HasHOppAdjacency(m)) pu.Update((*hi).HOp());
                                            ++ii;
                                        }

                                    ++hi;
                                    }
                                    }
				}
                                unsigned int siz = (unsigned int)m.hedge.size()-n;

				last = m.hedge.begin();
				advance(last,siz);

				return last;// deve restituire l'iteratore alla prima faccia aggiunta;
			}

			/** Function to add n vertices to the mesh.
			First wrapper, with no parameters
			*/
			static HEdgeIterator AddHEdges(MeshType &m, int n)
			{
				PointerUpdater<HEdgePointer> pu;
				return AddHEdges(m, n,pu);
			}

			/** Function to add n vertices to the mesh.
			Second Wrapper, with a vector of vertex pointers to be updated.
			*/
			static HEdgeIterator AddHEdges(MeshType &m, int n, std::vector<HEdgePointer*> &local_vec)
			{
				PointerUpdater<HEdgePointer> pu;
				HEdgeIterator v_ret =  AddHEdges(m, n,pu);

				typename std::vector<HEdgePointer *>::iterator ei;
						for(ei=local_vec.begin();ei!=local_vec.end();++ei)
							 pu.Update(**ei);
				return v_ret;
			}


			/** Function to add n faces to the mesh.
			First wrapper, with no parameters
			*/
			static FaceIterator AddFaces(MeshType &m, int n)
			{
				PointerUpdater<FacePointer> pu;
				return AddFaces(m,n,pu);
			}

      /** Function to add n faces to the mesh.
			Second Wrapper, with a vector of face pointer to be updated.
			*/
			static FaceIterator AddFaces(MeshType &m, int n,std::vector<FacePointer *> &local_vec)
			{
				PointerUpdater<FacePointer> pu;
				FaceIterator f_ret= AddFaces(m,n,pu);

				typename std::vector<FacePointer *>::iterator fi;
            for(fi=local_vec.begin();fi!=local_vec.end();++fi)
               pu.Update(**fi);
				return f_ret;
			}

			/** Function to add n faces to the mesh. 
      This is the only full featured function that is able to manage correctly all the internal pointers of the mesh (ff and vf relations).
			NOTE: THIS FUNCTION ALSO UPDATE FN
			*/
			static FaceIterator AddFaces(MeshType &m, int n, PointerUpdater<FacePointer> &pu)
			{
				FaceIterator  last, fi;
				if(n == 0) return m.face.end();
				pu.Clear();
				if(m.face.empty()) {
					pu.oldBase=0;  // if the vector is empty we cannot find the last valid element
				}	else  {
					pu.oldBase=&*m.face.begin(); 
					pu.oldEnd=&m.face.back()+1; 
					last=m.face.end();
				} 

				m.face.resize(m.face.size()+n);
				m.fn+=n;


				typename std::set<PointerToAttribute>::iterator ai;
				for(ai = m.face_attr.begin(); ai != m.face_attr.end(); ++ai)
					((PointerToAttribute)(*ai)).Resize(m.face.size());

				pu.newBase = &*m.face.begin();
				pu.newEnd  = &m.face.back()+1;
				
				if(pu.NeedUpdate())
				{
					int ii = 0;
					FaceIterator fi = m.face.begin();
					while(ii<m.fn-n) // cycle on all the faces except the new ones
					{
						if(!(*fi).IsD())
						{
							if(HasFFAdjacency(m))
								for(int i  = 0; i < (*fi).VN(); ++i)
									if ((*fi).cFFp(i)!=0) pu.Update((*fi).FFp(i));
						
							if(HasPerVertexVFAdjacency(m) && HasPerFaceVFAdjacency(m))
								for(int i = 0; i < (*fi).VN(); ++i)
									if ((*fi).cVFp(i)!=0) pu.Update((*fi).VFp(i));
						  ++ii;
						}
						++fi;
						}
						VertexIterator vi;
						for (vi=m.vert.begin(); vi!=m.vert.end(); ++vi)
							if(!(*vi).IsD())
							{
								if(HasPerVertexVFAdjacency(m) && HasPerFaceVFAdjacency(m))
									if ((*vi).cVFp()!=0)
										pu.Update((FaceType * &)(*vi).VFp());
								// Note the above cast is probably not useful if you have correctly defined 
								// your vertex type with the correct name of the facetype as a template argument; 
								//  pu.Update((FaceType*)(*vi).VFp()); compiles on old gcc and borland
								//  pu.Update((*vi).VFp());            compiles on .net and newer gcc
							}
						EdgeIterator ei;
						for (ei=m.edge.begin(); ei!=m.edge.end(); ++ei)
							if(!(*ei).IsD())
							{
								if(HasEFAdjacency(m))
									if ((*ei).cEFp()!=0)
										pu.Update((FaceType * &)(*ei).EFp());
								// Note the above cast is probably not useful if you have correctly defined 
								// your vertex type with the correct name of the facetype as a template argument; 
								//  pu.Update((FaceType*)(*vi).VFp()); compiles on old gcc and borland
								//  pu.Update((*vi).VFp());            compiles on .net and newer gcc
							}
	
						HEdgeIterator hi;
						for (hi=m.hedge.begin(); hi!=m.hedge.end(); ++hi)
							if(!(*hi).IsD())
							{
								if(HasHFAdjacency(m))
									if ((*hi).cHFp()!=0)
										pu.Update((FaceType * &)(*hi).HFp());
								// Note the above cast is probably not useful if you have correctly defined 
								// your vertex type with the correct name of the facetype as a template argument; 
								//  pu.Update((FaceType*)(*vi).VFp()); compiles on old gcc and borland
								//  pu.Update((*vi).VFp());            compiles on .net and newer gcc
							}

				}
				unsigned int siz=(unsigned int)m.face.size()-n;	
				last = m.face.begin(); 
				advance(last,siz);
				return last;
			}

		/** Function to delete a face from the mesh. 
			NOTE: THIS FUNCTION ALSO UPDATE FN
		*/
		static void DeleteFace(MeshType &m, FaceType &f)
		{
			assert(!f.IsD());
			f.SetD();
			--m.fn;
		}

		/** Function to delete a vertex from the mesh. 
			NOTE: THIS FUNCTION ALSO UPDATE vn
		*/
		static void DeleteVertex(MeshType &m, VertexType &v)
		{
			assert(!v.IsD());
			v.SetD();
			--m.vn;
		}

		/** Function to delete an edge from the mesh.
			NOTE: THIS FUNCTION ALSO UPDATE en
		*/
                static void DeleteEdge(MeshType &m, EdgeType &e)
		{
			assert(!e.IsD());
			e.SetD();
                        --m.en;
		}

		/** Function to delete a hedge from the mesh.
			NOTE: THIS FUNCTION ALSO UPDATE en
		*/
                static void DeleteHEdge(MeshType &m, HEdgeType &h)
		{
                        assert(!h.IsD());
                        h.SetD();
			--m.hn;
		}
		
		/*
			Function to rearrange the vertex vector according to a given index permutation
			the permutation is vector such that after calling this function
			
							m.vert[ newVertIndex[i] ] = m.vert[i];
			
			e.g. newVertIndex[i] is the new index of the vertex i
			
		*/
		static void PermutateVertexVector(MeshType &m, PointerUpdater<VertexPointer> &pu) 
		{
			for(unsigned int i=0;i<m.vert.size();++i)
			{
				if(pu.remap[i]<size_t(m.vn))
                {
                    assert(!m.vert[i].IsD());
										m.vert[ pu.remap [i] ].ImportData(m.vert[i]);
										if(HasPerVertexVFAdjacency(m) &&HasPerFaceVFAdjacency(m) )
                      if (m.vert[i].cVFp()!=0)
                        {
                            m.vert[ pu.remap[i] ].VFp() = m.vert[i].cVFp();
                            m.vert[ pu.remap[i] ].VFi() = m.vert[i].cVFi();
                        }
                }
			}
						
			// reorder the optional atttributes in m.vert_attr to reflect the changes 
			ReorderAttribute(m.vert_attr,pu.remap,m);

			// setup the pointer updater
			pu.oldBase  = &m.vert[0];
			pu.oldEnd = &m.vert.back()+1;
			
			// resize
			m.vert.resize(m.vn);
			
			// setup the pointer updater
			pu.newBase  = (m.vert.empty())?0:&m.vert[0];
			pu.newEnd = (m.vert.empty())?0:&m.vert.back()+1;


			// resize the optional atttributes in m.vert_attr to reflect the changes 
			ResizeAttribute(m.vert_attr,m.vn,m);

       // Loop on the face to update the pointers FV relation (vertex refs)
      for(FaceIterator fi=m.face.begin();fi!=m.face.end();++fi)
				if(!(*fi).IsD())
					for(unsigned int i=0;i<3;++i)
					{
						size_t oldIndex = (*fi).V(i) - pu.oldBase;
						assert(pu.oldBase <= (*fi).V(i) && oldIndex < pu.remap.size());
						(*fi).V(i) = pu.newBase+pu.remap[oldIndex];
					}
      // Loop on the edges to update the pointers EV relation
      if(HasEVAdjacency(m))
        for(EdgeIterator ei=m.edge.begin();ei!=m.edge.end();++ei)
          if(!(*ei).IsD())
            for(unsigned int i=0;i<2;++i)
            {
              pu.Update((*ei).V(i));
            }
		}


		/* 
		Function to compact all the vertices that have been deleted and put them to the end of the vector. 
		after this pass the isD test in the scanning of vertex vector, is no more strongly necessary.
		It should not be called when TemporaryData is active;
		*/
		
		static void CompactVertexVector( MeshType &m,   PointerUpdater<VertexPointer> &pu   ) 
		{
			// If already compacted fast return please!
			if(m.vn==(int)m.vert.size()) return; 
			
			// newVertIndex [ <old_vert_position> ] gives you the new position of the vertex in the vector;
			pu.remap.resize( m.vert.size(),std::numeric_limits<size_t>::max() );
			
			size_t pos=0;
			size_t i=0;
			
			for(i=0;i<m.vert.size();++i)
			{
				if(!m.vert[i].IsD())
				{
					pu.remap[i]=pos;
					++pos;
				}
			}
			assert((int)pos==m.vn);
			 
			PermutateVertexVector(m, pu);
			 
		}

		/* 
		Function to compact all the verices that have been deleted and put them to the end of the vector. 
		Wrapper if not PointerUpdater is not wanted
		*/
		static void CompactVertexVector( MeshType &m  ) {
			PointerUpdater<VertexPointer>  pu;
			CompactVertexVector(m,pu);
		}

    /*
    Function to compact all the vertices that have been deleted and put them to the end of the vector.
    after this pass the isD test in the scanning of vertex vector, is no more strongly necessary.
    It should not be called when TemporaryData is active;
    */

    static void CompactEdgeVector( MeshType &m,   PointerUpdater<EdgePointer> &pu   )
    {
      // If already compacted fast return please!
      if(m.en==(int)m.edge.size()) return;

      // remap [ <old_edge_position> ] gives you the new position of the edge in the vector;
      pu.remap.resize( m.edge.size(),std::numeric_limits<size_t>::max() );

      size_t pos=0;
      size_t i=0;

      for(i=0;i<m.edge.size();++i)
      {
        if(!m.edge[i].IsD())
        {
          pu.remap[i]=pos;
          ++pos;
        }
      }
      assert((int)pos==m.en);

      // the actual copying of the data.
      for(unsigned int i=0;i<m.edge.size();++i)
      {
        if(pu.remap[i]<size_t(m.vn))  // uninitialized entries in the remap vector has max_int value;
                {
                    assert(!m.edge[i].IsD());
                    m.edge[ pu.remap [i] ].ImportData(m.edge[i]);
                    // copy the vertex reference (they are not data!)
                     m.edge[ pu.remap[i] ].V(0) = m.edge[i].cV(0);
                     m.edge[ pu.remap[i] ].V(1) = m.edge[i].cV(1);
                    // Now just copy the adjacency pointers (without changing them, to be done later)
                    if(HasPerVertexVEAdjacency(m) && HasPerEdgeVEAdjacency(m) )
                      if (m.edge[i].cVEp(0)!=0)
                        {
                          m.edge[ pu.remap[i] ].VEp(0) = m.edge[i].cVEp(0);
                          m.edge[ pu.remap[i] ].VEi(0) = m.edge[i].cVEi(0);
                          m.edge[ pu.remap[i] ].VEp(1) = m.edge[i].cVEp(1);
                          m.edge[ pu.remap[i] ].VEi(1) = m.edge[i].cVEi(1);
                        }
                    if(HasEEAdjacency(m))
                      if (m.edge[i].cEEp(0)!=0)
                        {
                          m.edge[ pu.remap[i] ].EEp(0) = m.edge[i].cEEp(0);
                          m.edge[ pu.remap[i] ].EEi(0) = m.edge[i].cEEi(0);
                          m.edge[ pu.remap[i] ].EEp(1) = m.edge[i].cEEp(1);
                          m.edge[ pu.remap[i] ].EEi(1) = m.edge[i].cEEi(1);
                        }
                }
      }

      // reorder the optional attributes in m.vert_attr to reflect the changes
      ReorderAttribute(m.edge_attr, pu.remap,m);

      // setup the pointer updater
      pu.oldBase  = &m.edge[0];
      pu.oldEnd = &m.edge.back()+1;

      // THE resize
      m.edge.resize(m.en);

      // setup the pointer updater
      pu.newBase  = (m.edge.empty())?0:&m.edge[0];
      pu.newEnd = (m.edge.empty())?0:&m.edge.back()+1;

      // resize the optional atttributes in m.vert_attr to reflect the changes
      ResizeAttribute(m.edge_attr,m.en,m);

      // Loop on the vertices to update the pointers of VE relation
      if(HasPerVertexVEAdjacency(m) &&HasPerEdgeVEAdjacency(m))
          for (VertexIterator vi=m.vert.begin(); vi!=m.vert.end(); ++vi)
              if(!(*vi).IsD())  pu.Update((*vi).VEp());

      // Loop on the edges to update the pointers EE VE relation
       for(EdgeIterator ei=m.edge.begin();ei!=m.edge.end();++ei)
          for(unsigned int i=0;i<2;++i)
          {
             if(HasPerVertexVEAdjacency(m) &&HasPerEdgeVEAdjacency(m))
               pu.Update((*ei).VEp(i));
             if(HasEEAdjacency(m))
               pu.Update((*ei).EEp(i));
          }
    }

    /*
    Function to compact all the verices that have been deleted and put them to the end of the vector.
    Wrapper if not PointerUpdater is not wanted
    */
    static void CompactEdgeVector( MeshType &m  ) {
      PointerUpdater<EdgePointer>  pu;
      CompactEdgeVector(m,pu);
    }

		/* 
		Function to compact all the vertices that have been deleted and put them to the end of the vector. 
		after this pass the isD test in the scanning of vertex vector, is no more strongly necessary.
		It should not be called when TemporaryData is active;
		*/
		
		static void CompactFaceVector( MeshType &m, PointerUpdater<FacePointer> &pu ) 
		{
		  // If already compacted fast return please!
			if(m.fn==(int)m.face.size()) return; 
			 
			// newFaceIndex [ <old_face_position> ] gives you the new position of the face in the vector;
			pu.remap.resize( m.face.size(),std::numeric_limits<size_t>::max() );
			
			size_t pos=0;
			size_t i=0;
			
			for(i=0;i<m.face.size();++i)
			{
				if(!m.face[i].IsD())
				{
					if(pos!=i)
                    {
												m.face[pos].ImportData(m.face[i]);
                        m.face[pos].V(0) = m.face[i].V(0);
                        m.face[pos].V(1) = m.face[i].V(1);
                        m.face[pos].V(2) = m.face[i].V(2);
												if(HasPerVertexVFAdjacency(m) && HasPerFaceVFAdjacency(m))
                            for(int j=0;j<3;++j)
                                 if (m.face[i].cVFp(j)!=0) {
                                        m.face[pos].VFp(j) = m.face[i].cVFp(j);
                                        m.face[pos].VFi(j) = m.face[i].cVFi(j);
                                    }
                        if(HasFFAdjacency(m))
                            for(int j=0;j<3;++j)
                                 if (m.face[i].cFFp(j)!=0) {
                                        m.face[pos].FFp(j) = m.face[i].cFFp(j);
                                        m.face[pos].FFi(j) = m.face[i].cFFi(j);
                                    }
                    }
					pu.remap[i]=pos;
					++pos;
				}
			}
			assert((int)pos==m.fn);
								
			// reorder the optional atttributes in m.face_attr to reflect the changes 
			ReorderAttribute(m.face_attr,pu.remap,m);

			// Loop on the vertices to correct VF relation
			VertexIterator vi;
			FacePointer fbase=&m.face[0];
			for (vi=m.vert.begin(); vi!=m.vert.end(); ++vi)
					if(!(*vi).IsD())
					{
						if(HasPerVertexVFAdjacency(m) &&HasPerFaceVFAdjacency(m)  )
									if ((*vi).cVFp()!=0)
									{
										size_t oldIndex = (*vi).cVFp() - fbase;
										assert(fbase <= (*vi).cVFp() && oldIndex < pu.remap.size());
										(*vi).VFp() = fbase+pu.remap[oldIndex];
									}
					}
			

			// Loop on the faces to correct VF and FF relations
			pu.oldBase  = &m.face[0];
			pu.oldEnd = &m.face.back()+1;
			m.face.resize(m.fn);
			pu.newBase  = (m.face.empty())?0:&m.face[0];
			pu.newEnd = (m.face.empty())?0:&m.face.back()+1;


			// resize the optional atttributes in m.face_attr to reflect the changes 
			ResizeAttribute(m.face_attr,m.fn,m);

			FaceIterator fi;
			for(fi=m.face.begin();fi!=m.face.end();++fi)
				if(!(*fi).IsD())
				{
					if(HasPerVertexVFAdjacency(m) &&HasPerFaceVFAdjacency(m) )
								for(i=0;i<3;++i)
								if ((*fi).cVFp(i)!=0)
									{
										size_t oldIndex = (*fi).VFp(i) - fbase;
										assert(fbase <= (*fi).VFp(i) && oldIndex < pu.remap.size());
										(*fi).VFp(i) = fbase+pu.remap[oldIndex];
									}
					if(HasFFAdjacency(m))
										for(i=0;i<3;++i)
											if ((*fi).cFFp(i)!=0)
											{
												size_t oldIndex = (*fi).FFp(i) - fbase;
												assert(fbase <= (*fi).FFp(i) && oldIndex < pu.remap.size());
												(*fi).FFp(i) = fbase+pu.remap[oldIndex];
											}
				}

			 

		}

		/* 
		Function to compact all the face that have been deleted and put them to the end of the vector. 
		Wrapper if not PointerUpdater is wanted
		*/
		static void CompactFaceVector( MeshType &m  ) {
			PointerUpdater<FacePointer>  pu;
			CompactFaceVector(m,pu);
		}



public:

	/// Per Vertex Attributes
	template <class ATTR_TYPE>
	static 
	bool IsValidHandle( MeshType & m,  const typename MeshType::template PerVertexAttributeHandle<ATTR_TYPE> & a){
		if(a._handle == NULL) return false;
		for(AttrIterator i = m.vert_attr.begin(); i!=m.vert_attr.end();++i)
			if ( (*i).n_attr == a.n_attr ) return true;
		return false;
	}

	template <class ATTR_TYPE> 
	static
	typename MeshType::template PerVertexAttributeHandle<ATTR_TYPE>
	 AddPerVertexAttribute( MeshType & m, std::string name){
		PAIte i;
		PointerToAttribute h;
		h._name = name;
		if(!name.empty()){
			i = m.vert_attr.find(h);
			assert(i ==m.vert_attr.end() );// an attribute with this name exists
		}

		h._sizeof = sizeof(ATTR_TYPE);
		h._padding = 0;
		h._handle =   new SimpleTempData<VertContainer,ATTR_TYPE>(m.vert);
		m.attrn++;
		h.n_attr = m.attrn;
		std::pair < AttrIterator , bool> res =  m.vert_attr.insert(h);
		return typename MeshType::template PerVertexAttributeHandle<ATTR_TYPE>(res.first->_handle,res.first->n_attr );
	 }

	template <class ATTR_TYPE> 
	static
	typename MeshType::template PerVertexAttributeHandle<ATTR_TYPE>
	 AddPerVertexAttribute( MeshType & m){
		 return AddPerVertexAttribute<ATTR_TYPE>(m,std::string(""));
	 }

	template <class ATTR_TYPE> 
	static
		typename MeshType::template PerVertexAttributeHandle<ATTR_TYPE>
	 GetPerVertexAttribute( MeshType & m, const std::string & name){
		assert(!name.empty());
		PointerToAttribute h1; h1._name = name;
		typename std::set<PointerToAttribute > :: iterator i;

		i =m.vert_attr.find(h1);
		if(i!=m.vert_attr.end())
                                if((*i)._sizeof == sizeof(ATTR_TYPE) ){
						if(	(*i)._padding != 0 ){
								PointerToAttribute attr = (*i);						// copy the PointerToAttribute
								m.vert_attr.erase(i);						// remove it from the set
								FixPaddedPerVertexAttribute<ATTR_TYPE>(m,attr);
								std::pair<AttrIterator,bool> new_i = m.vert_attr.insert(attr);	// insert the modified PointerToAttribute
								assert(new_i.second);
								i = new_i.first;
								}

					return typename MeshType::template PerVertexAttributeHandle<ATTR_TYPE>((*i)._handle,(*i).n_attr);
		}

		return typename MeshType:: template PerVertexAttributeHandle<ATTR_TYPE>(NULL,0);
		
	}

	template <class ATTR_TYPE>
	static void GetAllPerVertexAttribute(const MeshType & m, std::vector<std::string> &all){
		typename std::set<PointerToAttribute > ::const_iterator i;
		for(i = m.vert_attr.begin(); i != m.vert_attr.end(); ++i )
        if((*i)._name == typeid(ATTR_TYPE).name())
						all.push_back((*i)._name);
	}

	template <class ATTR_TYPE> 
	static
		void
	DeletePerVertexAttribute( MeshType & m,typename MeshType::template PerVertexAttributeHandle<ATTR_TYPE> & h){
		typename std::set<PointerToAttribute > ::iterator i;
		for( i = m.vert_attr.begin(); i !=  m.vert_attr.end(); ++i)
			if( (*i)._handle == h._handle ){
				delete ((SimpleTempData<VertContainer,ATTR_TYPE>*)(*i)._handle);
				m.vert_attr.erase(i); 
				return;}
			assert(0);
	}

	static
		void	DeletePerVertexAttribute( MeshType & m,  std::string name){
		AttrIterator i;
		PointerToAttribute h1; h1._name = name;
		i = m.vert_attr.find(h1);
		assert(i!=m.vert_attr.end());
		delete ((SimpleTempDataBase*)(*i)._handle);
		m.vert_attr.erase(i);
	}



	/// Per Edge Attributes
	template <class ATTR_TYPE>
	static 
	bool IsValidHandle( MeshType & m,  const typename MeshType::template PerEdgeAttributeHandle<ATTR_TYPE> & a){
		if(a._handle == NULL) return false;
		for(AttrIterator i = m.edge_attr.begin(); i!=m.edge_attr.end();++i)
			if ( (*i).n_attr == a.n_attr ) return true;
		return false;
	}

	template <class ATTR_TYPE> 
	static
	typename MeshType::template PerEdgeAttributeHandle<ATTR_TYPE>
	 AddPerEdgeAttribute( MeshType & m, std::string name){
		PAIte i;
		PointerToAttribute h;
		h._name = name;
		if(!name.empty()){
			i = m.edge_attr.find(h);
			assert(i ==m.edge_attr.end() );// an attribute with this name exists
		}
		h._sizeof = sizeof(ATTR_TYPE);
                h._padding = 0;
                h._typename = typeid(ATTR_TYPE).name();
		h._handle = (void*) new SimpleTempData<EdgeContainer,ATTR_TYPE>(m.edge);
 		m.attrn++;
		h.n_attr = m.attrn;
		std::pair < AttrIterator , bool> res =  m.edge_attr.insert(h);
		return typename MeshType::template PerEdgeAttributeHandle<ATTR_TYPE>(res.first->_handle,res.first->n_attr);
	 }

	template <class ATTR_TYPE> 
	static
	typename MeshType::template PerVertexAttributeHandle<ATTR_TYPE>
	 AddPerEdgeAttribute( MeshType & m){
		 return AddPerEdgeAttribute<ATTR_TYPE>(m,std::string(""));
	 }
	
	template <class ATTR_TYPE> 
	static
		typename MeshType::template PerEdgeAttributeHandle<ATTR_TYPE>
	 GetPerEdgeAttribute( const MeshType & m, const std::string & name){
		assert(!name.empty());
		PointerToAttribute h1; h1._name = name;
		typename std::set<PointerToAttribute > ::const_iterator i;

		i =m.edge_attr.find(h1);

		if(i!=m.edge_attr.end())
				if((*i)._typename == typeid(ATTR_TYPE).name() )
						return typename MeshType:: template PerVertexAttributeHandle<ATTR_TYPE>(NULL,0);

		return typename MeshType:: template PerFaceAttributeHandle<ATTR_TYPE>(NULL,0);
	}

	template <class ATTR_TYPE>
	static void GetAllPerEdgeAttribute(const MeshType & m, std::vector<std::string> &all){
		typename std::set<PointerToAttribute > :: iterator i;
		for(i = m.edge_attr.begin(); i != m.edge_attr.end(); ++i )
				if((*i)._typename == typeid(ATTR_TYPE).name())
						all.push_back((*i)._name);
	}

	template <class ATTR_TYPE> 
	static
		void
	DeletePerEdgeAttribute( MeshType & m,typename MeshType::template PerEdgeAttributeHandle<ATTR_TYPE> & h){
		typename std::set<PointerToAttribute > ::iterator i;
		for( i = m.edge_attr.begin(); i !=  m.edge_attr.end(); ++i)
			if( (*i)._handle == h._handle ){
				delete ((SimpleTempData<FaceContainer,ATTR_TYPE>*)(*i)._handle);
				m.edge_attr.erase(i); 
				return;}
			assert(0);
	}

	static
		void	DeletePerEdgeAttribute( MeshType & m,  std::string name){
		AttrIterator i;
		PointerToAttribute h1; h1._name = name;
		i = m.edge_attr.find(h1);
		assert(i!=m.edge_attr.end());
                delete ((SimpleTempDataBase*)(*i)._handle);
		m.edge_attr.erase(i);
	}

	/// Per Face Attributes
	template <class ATTR_TYPE>
	static 
	bool IsValidHandle( MeshType & m,  const typename MeshType::template PerFaceAttributeHandle<ATTR_TYPE> & a){
		if(a._handle == NULL) return false;
		for(AttrIterator i = m.face_attr.begin(); i!=m.face_attr.end();++i)
			if ( (*i).n_attr == a.n_attr ) return true;
		return false;
	}

	template <class ATTR_TYPE> 
	static
	typename MeshType::template PerFaceAttributeHandle<ATTR_TYPE>
	 AddPerFaceAttribute( MeshType & m, std::string name){
		PAIte i;
		PointerToAttribute h;
		h._name = name;
		if(!name.empty()){
			i = m.face_attr.find(h);
			assert(i ==m.face_attr.end() );// an attribute with this name exists
		}

		h._sizeof = sizeof(ATTR_TYPE);
                h._padding = 0;
                h._handle =   new SimpleTempData<FaceContainer,ATTR_TYPE>(m.face);
		m.attrn++;
		h.n_attr = m.attrn;
		std::pair < AttrIterator , bool> res =  m.face_attr.insert(h);
		return typename MeshType::template PerFaceAttributeHandle<ATTR_TYPE>(res.first->_handle,res.first->n_attr);
	 }

	template <class ATTR_TYPE> 
	static
	typename MeshType::template PerFaceAttributeHandle<ATTR_TYPE>
	 AddPerFaceAttribute( MeshType & m){
		 return AddPerFaceAttribute<ATTR_TYPE>(m,std::string(""));
	 }
		
	template <class ATTR_TYPE> 
	static
		typename MeshType::template PerFaceAttributeHandle<ATTR_TYPE>
	 GetPerFaceAttribute( MeshType & m, const std::string & name){
		assert(!name.empty());
		PointerToAttribute h1; h1._name = name;
		typename std::set<PointerToAttribute > ::iterator i;

		i =m.face_attr.find(h1);
		if(i!=m.face_attr.end())
                                if((*i)._sizeof == sizeof(ATTR_TYPE) ){
						if(	(*i)._padding != 0 ){
						PointerToAttribute attr = (*i);											// copy the PointerToAttribute
						m.face_attr.erase(i);											// remove it from the set
						FixPaddedPerFaceAttribute<ATTR_TYPE>(m,attr);
						std::pair<AttrIterator,bool> new_i = m.face_attr.insert(attr);	// insert the modified PointerToAttribute
						assert(new_i.second);
						i = new_i.first;
						}
						return typename MeshType::template PerFaceAttributeHandle<ATTR_TYPE>((*i)._handle,(*i).n_attr);
				}
		return typename MeshType:: template PerFaceAttributeHandle<ATTR_TYPE>(NULL,0);
	}

	template <class ATTR_TYPE>
	static void GetAllPerFaceAttribute(const MeshType & m, std::vector<std::string> &all){
		typename std::set<PointerToAttribute > :: const_iterator i;
		for(i = m.face_attr.begin(); i != m.face_attr.end(); ++i )
        if((*i)._name == typeid(ATTR_TYPE).name())
						all.push_back((*i)._name);
	}

	template <class ATTR_TYPE> 
	static
		void
	DeletePerFaceAttribute( MeshType & m,typename MeshType::template PerFaceAttributeHandle<ATTR_TYPE> & h){
		typename std::set<PointerToAttribute > ::iterator i;
		for( i = m.face_attr.begin(); i !=  m.face_attr.end(); ++i)
			if( (*i)._handle == h._handle ){
				delete ((SimpleTempData<FaceContainer,ATTR_TYPE>*)(*i)._handle);
				m.face_attr.erase(i); 
				return;}
			assert(0);
	}

	static
		void	DeletePerFaceAttribute( MeshType & m,  std::string name){
		AttrIterator i;
		PointerToAttribute h1; h1._name = name;
		i = m.face_attr.find(h1);
		assert(i!=m.face_attr.end());
                delete ((SimpleTempDataBase*)(*i)._handle);
		m.face_attr.erase(i);
	}

	/// Per Mesh Attributes
	template <class ATTR_TYPE>
	static 
	bool IsValidHandle( MeshType & m,  const typename MeshType::template PerMeshAttributeHandle<ATTR_TYPE> & a){
		if(a._handle == NULL) return false;
		for(AttrIterator i = m.mesh_attr.begin(); i!=m.mesh_attr.end();++i)
			if ( (*i).n_attr == a.n_attr ) return true;
		return false;
	}

	template <class ATTR_TYPE> 
	static
	typename MeshType::template PerMeshAttributeHandle<ATTR_TYPE>
	 AddPerMeshAttribute( MeshType & m, std::string name){
		PAIte i;
		PointerToAttribute h;
		h._name = name;
		if(!name.empty()){
			i = m.mesh_attr.find(h);
			assert(i ==m.mesh_attr.end() );// an attribute with this name exists
		}
		h._sizeof = sizeof(ATTR_TYPE);
                h._padding = 0;
		h._handle =  new Attribute<ATTR_TYPE>();
		m.attrn++;
		h.n_attr = m.attrn;
		std::pair < AttrIterator , bool> res =  m.mesh_attr.insert(h);
		return typename MeshType::template PerMeshAttributeHandle<ATTR_TYPE>(res.first->_handle,res.first->n_attr);
	 }
		
	template <class ATTR_TYPE> 
	static
		typename MeshType::template PerMeshAttributeHandle<ATTR_TYPE>
	 GetPerMeshAttribute( MeshType & m, const std::string & name){
		assert(!name.empty());
		PointerToAttribute h1; h1._name = name;
		typename std::set<PointerToAttribute > ::iterator i;

		i =m.mesh_attr.find(h1);
		if(i!=m.mesh_attr.end())
                                if((*i)._sizeof == sizeof(ATTR_TYPE)  ){
						if(	(*i)._padding != 0 ){
						PointerToAttribute attr = (*i);											// copy the PointerToAttribute
						m.mesh_attr.erase(i);											// remove it from the set
						FixPaddedPerMeshAttribute<ATTR_TYPE>(m,attr);
						std::pair<AttrIterator,bool> new_i = m.mesh_attr.insert(attr);	// insert the modified PointerToAttribute
						assert(new_i.second);
						i = new_i.first;
						}

						return typename MeshType::template PerMeshAttributeHandle<ATTR_TYPE>((*i)._handle,(*i).n_attr);
		}

		return typename MeshType:: template PerMeshAttributeHandle<ATTR_TYPE>(NULL,0);
	}

	template <class ATTR_TYPE>
	static void GetAllPerMeshAttribute(const MeshType & m, std::vector<std::string> &all){
		typename std::set<PointerToAttribute > :: iterator i;
		for(i = m.mesh_attr.begin(); i != m.mesh_attr.end(); ++i )
                                if((*i)._sizeof == sizeof(ATTR_TYPE))
						all.push_back((*i)._name);
	}

	template <class ATTR_TYPE> 
	static
		void
	DeletePerMeshAttribute( MeshType & m,typename MeshType::template PerMeshAttributeHandle<ATTR_TYPE> & h){
		typename std::set<PointerToAttribute > ::iterator i;
		for( i = m.mesh_attr.begin(); i !=  m.mesh_attr.end(); ++i)
			if( (*i)._handle == h._handle ){
				delete (( Attribute<ATTR_TYPE> *)(*i)._handle);
				m.mesh_attr.erase(i); 
				return;}
			assert(0);
	}

	static
		void	DeletePerMeshAttribute( MeshType & m,  std::string name){
		AttrIterator i;
		PointerToAttribute h1; h1._name = name;
		i = m.mesh_attr.find(h1);
		assert(i!=m.mesh_attr.end());
                delete ((SimpleTempDataBase  *)(*i)._handle);
		m.mesh_attr.erase(i);
	}

	template <class ATTR_TYPE>
	static 
		void FixPaddedPerVertexAttribute ( MeshType & m,PointerToAttribute & pa){

			// create the container of the right type
			SimpleTempData<VertContainer,ATTR_TYPE>* _handle =  new SimpleTempData<VertContainer,ATTR_TYPE>(m.vert);

			// copy the padded container in the new one
			_handle->Resize(m.vert.size());
			for(unsigned int i  = 0; i < m.vert.size(); ++i){
				ATTR_TYPE * dest = &(*_handle)[i];
				char * ptr = (char*)( ((SimpleTempDataBase *)pa._handle)->DataBegin());
				memcpy((void*)dest ,  
				(void*) &(ptr[i *  pa._sizeof ]) ,sizeof(ATTR_TYPE));
			}

			// remove the padded container 
			delete ((SimpleTempDataBase*) pa._handle);

			// update the pointer to data
			pa._sizeof = sizeof(ATTR_TYPE);

			// update the pointer to data
			pa._handle = _handle;

			// zero the padding 
			pa._padding = 0;
	}
	
	template <class ATTR_TYPE>
	static 
		void FixPaddedPerFaceAttribute ( MeshType & m,PointerToAttribute & pa){

			// create the container of the right type
			SimpleTempData<FaceContainer,ATTR_TYPE>* _handle =  new SimpleTempData<FaceContainer,ATTR_TYPE>(m.face);

			// copy the padded container in the new one
			_handle->Resize(m.face.size());
			for(unsigned int i  = 0; i < m.face.size(); ++i){
				ATTR_TYPE * dest = &(*_handle)[i];
                                char * ptr = (char*)( ((SimpleTempDataBase *)pa._handle)->DataBegin());
				memcpy((void*)dest ,  
				(void*) &(ptr[i * pa._sizeof ]) ,sizeof(ATTR_TYPE));
			}

			// remove the padded container 
                        delete ((SimpleTempDataBase*) pa._handle);

			// update the pointer to data
			pa._sizeof = sizeof(ATTR_TYPE);

			// update the pointer to data
			pa._handle = _handle;

			// zero the padding 
			pa._padding = 0;
	}

	
	template <class ATTR_TYPE>
	static 
    void FixPaddedPerMeshAttribute ( MeshType & /* m */,PointerToAttribute & pa){

			// create the container of the right type
			Attribute<ATTR_TYPE> * _handle =  new Attribute<ATTR_TYPE>();

			// copy the padded container in the new one
      char * ptr = (char*)( ((Attribute<ATTR_TYPE> *)pa._handle)->DataBegin());
			memcpy((void*)_handle->attribute ,(void*) &(ptr[0]) ,sizeof(ATTR_TYPE));

			// remove the padded container 
			delete ( (Attribute<ATTR_TYPE> *) pa._handle);

			// update the pointer to data
			pa._sizeof = sizeof(ATTR_TYPE);

			// update the pointer to data
			pa._handle = _handle;

			// zero the padding 
			pa._padding = 0;
	}



}; // end class
		

		/*@}*/
	} // End Namespace TriMesh
} // End Namespace vcg

#endif
