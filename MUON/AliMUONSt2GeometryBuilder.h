// $Id$
//
// Class AliMUONSt2GeometryBuilder
// -----------------------------
// MUON Station2 geometry construction class.
//
// Author: Ivana Hrivnacova, IPN Orsay

#ifndef ALI_MUON_ST2_GEOMETRY_BUILDER_H
#define ALI_MUON_ST2_GEOMETRY_BUILDER_H

#include "AliMUONVGeometryBuilder.h"

class AliMUON;

class AliMUONSt2GeometryBuilder : public AliMUONVGeometryBuilder
{
  public:
    AliMUONSt2GeometryBuilder(AliMUON* muon);
    AliMUONSt2GeometryBuilder(const AliMUONSt2GeometryBuilder& rhs);
    AliMUONSt2GeometryBuilder();
    virtual ~AliMUONSt2GeometryBuilder();

    // operators  
    AliMUONSt2GeometryBuilder& operator = (const AliMUONSt2GeometryBuilder& rhs);
  
    // methods
    virtual void CreateGeometry();
    virtual void SetTransformations();
    virtual void SetSensitiveVolumes();
    
  private:
     AliMUON*  fMUON; // the MUON detector class 
        
  ClassDef(AliMUONSt2GeometryBuilder,1) // MUON chamber geometry base class
};

#endif //ALI_MUON_ST2_GEOMETRY_BUILDER_H
