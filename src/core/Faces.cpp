//------------------------------------------------------------------------
//  Copyright (C) Gabriel Taubin
//  Time-stamp: <2025-08-04 22:09:56 gtaubin>
//------------------------------------------------------------------------
//
// Faces.cpp
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

#include <math.h>
#include "Faces.hpp"
  
Faces::Faces(const int nV, const vector<int>& coordIndex) {
  this->_indices = coordIndex;
  int maxIndex = *max_element(_indices.begin(), _indices.end());

  if(nV < maxIndex + 1){
    this-> _numVertices = maxIndex + 1;
  
  } else {
      this->_numVertices = nV;
    }

}

int Faces::getNumberOfVertices() const {
  return _numVertices;
}  

int Faces::getNumberOfFaces() const {
  int numberOfFaces = 0;
  for (int i = 0; i < _indices.size(); i++){
    if (_indices[i] == -1){
      numberOfFaces++;
    }
  }
  return numberOfFaces;
}

int Faces::getNumberOfCorners() const {
  return this->_indices.size();
}

int Faces::getFaceSize(const int iF) const {
  int numFaces = getNumberOfFaces();
    if(iF < 0 || iF >= numFaces) 
        return -1;

    int faceCounter = 0;
    int index = 0;
    while(index < _indices.size() && faceCounter < iF){
      if(_indices[index] == -1)
        faceCounter++;
      index++;
    }

    int faceSize = 0;
    while(index < _indices.size() && _indices[index] != -1){
      faceSize++;
      index++;
    }
    return faceSize;
}

int Faces::getFaceFirstCorner(const int iF) const {
    int numFaces = getNumberOfFaces();
    if(iF < 0 || iF >= numFaces) 
        return -1;

    int faceCounter = 0;
    for(int i = 0; i < _indices.size(); ++i) {
        if(faceCounter == iF) {
            return i; 
        }
        if(_indices[i] == -1) {
            faceCounter++;
        }
    }

    return -1; 
}

int Faces::getFaceVertex(const int iF, const int j) const {
  int numFaces = getNumberOfFaces();
  if(iF < 0 || iF >= numFaces) 
        return -1;

  int firstCornerIndex = getFaceFirstCorner(iF);
  int faceSize = getFaceSize(iF);

  if(j <= faceSize && j >= 0){
    return _indices[firstCornerIndex + j - 1];
  }
  else return -1;
}

int Faces::getCornerFace(const int iC) const {
  if(iC < 0 || iC >= _indices.size())
    return -1;

  int faceCount = 0;
  for(int i = 0; i < iC; i++){
    if(_indices[i] == -1)
      faceCount++;
  }
  return faceCount;
}

int Faces::getNextCorner(const int iC) const {
  return -1;
}