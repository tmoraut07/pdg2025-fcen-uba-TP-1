//------------------------------------------------------------------------
//  Copyright (C) Gabriel Taubin
//  Time-stamp: <2025-08-04 22:14:44 gtaubin>
//------------------------------------------------------------------------
//
// SaverStl.cpp
//
// Written by: <Your Name>
//
// Software developed for the course
// Digital Geometry Processing
// Copyright (c) 2025, Gabriel Taubin
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//     * Redistributions of source code must retain the above copyright
//       notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above copyright
//       notice, this list of conditions and the following disclaimer in the
//       documentation and/or other materials provided with the distribution.
//     * Neither the name of the Brown University nor the
//       names of its contributors may be used to endorse or promote products
//       derived from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL GABRIEL TAUBIN BE LIABLE FOR ANY
// DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
// ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#include "SaverStl.hpp"

#include "wrl/Shape.hpp"
#include "wrl/Appearance.hpp"
#include "wrl/Material.hpp"
#include "wrl/IndexedFaceSet.hpp"

#include "core/Faces.hpp"

const char* SaverStl::_ext = "stl";

//////////////////////////////////////////////////////////////////////
bool SaverStl::save(const char* filename, SceneGraph& wrl) const {
  bool success = false;
  if(filename!=(char*)0) {

    // Check these conditions

    // 1) the SceneGraph should have a single child
    if(wrl.getNumberOfChildren() != 1) return false;
    
    // 2) the child should be a Shape node
    auto children = wrl.getChildren();
    IndexedFaceSet *geometry = NULL;
    for(auto child : children){
      if (child->isShape()){
    // 3) the geometry of the Shape node should be an IndexedFaceSet node
        geometry = (IndexedFaceSet*) ((Shape*)child)->getGeometry();
      }
    }
    if (!geometry->isIndexedFaceSet()) return false;

    // - construct an instance of the Faces class from the IndexedFaceSet

    vector<int>& coordIndex = geometry->getCoordIndex();
    vector<float>& coord = geometry->getCoord();
    vector<float>& normal = geometry->getNormal();
    vector<int>& normalIdx = geometry->getNormalIndex();
    int numVertex = geometry->getNumberOfCorners();

    Faces meshFaces = Faces(numVertex, coordIndex);

    Vec3f vecBuffer;
    // - remember to delete it when you are done with it (if  necessary)
    //   before returning


    // 4) the IndexedFaceSet should be a triangle mesh
    // 5) the IndexedFaceSet should have normals per face

    // if (all the conditions are satisfied) {

    FILE* fp = fopen(filename,"w");
    if(	fp!=(FILE*)0) {

      // if set, use ifs->getName()
      // otherwise use filename,
      // but first remove directory and extension
      const string& name = wrl.getName().c_str();

      fprintf(fp,"solid %s\n",filename);
      int faceNum = 0;
      while(meshFaces.getFaceVertex(faceNum, 0) != -1){
        int normalNum;
        if(normalIdx.empty()) normalNum = faceNum;
        else normalNum = normalIdx[faceNum];

        vecBuffer.x = normal[3 * normalNum];
        vecBuffer.y = normal[3 * normalNum + 1];
        vecBuffer.z = normal[3 * normalNum + 2];

        for(int corner = 0; corner < 3; corner ++){
          int vertex = meshFaces.getFaceVertex(faceNum, corner);
          vecBuffer.x = coord[3 * vertex];
          vecBuffer.y = coord[3 * vertex + 1];
          vecBuffer.z = coord[3 * vertex + 2];
        }

        faceNum++;
      }

      
      fclose(fp);
      success = true;
    }

    // } endif (all the conditions are satisfied)

  }
  return success;
}
