/* Copyright(c) 1998-1999, ALICE Experiment at CERN, All rights reserved. *
 * See cxx source for full Copyright notice                               */

// $Id$
//
// Class AliMUONSt1GeometryBuilderV2
// ---------------------------------
// MUON Station1 detailed geometry construction class.
//
// Authors: David Guez, Ivana Hrivnacova, Marion MacCormick; IPN Orsay

#ifndef ALI_MUON_ST1_GEOMETRY_BUILDER_V2_H
#define ALI_MUON_ST1_GEOMETRY_BUILDER_V2_H

//#include "AliMUONSt1Containers.h"
#include "AliMUONSt1Types.h"

/*
#ifdef ST1_WITH_STL
  #include <map>
  #ifdef __HP_aCC
    using std::map;
  #endif
#endif

#ifdef ST1_WITH_ROOT
  #include "TExMap.h"
#endif
*/
#include "AliMUONVGeometryBuilder.h"

//typedef Float_t GReal_t; // for AliGeant3
typedef Double_t GReal_t;  // for VirtualMC

class TTree;
class TVector2;
class TVector3;

class AliMpSector;
class AliMUON;

class AliMUONSt1GeometryBuilderV2 : public AliMUONVGeometryBuilder 
{
  public:
    AliMUONSt1GeometryBuilderV2(AliMUON* muon);
    AliMUONSt1GeometryBuilderV2(const AliMUONSt1GeometryBuilderV2& rMUON);
    AliMUONSt1GeometryBuilderV2();
    virtual ~AliMUONSt1GeometryBuilderV2();

    virtual void CreateMaterials();
    virtual void CreateGeometry();
    virtual void SetTransformations();
    virtual void SetSensitiveVolumes();
   
  protected:
    AliMUONSt1GeometryBuilderV2& operator = (const AliMUONSt1GeometryBuilderV2& rhs);    
 
  private:
    // Typedefs
    //
/*
#ifdef ST1_WITH_STL
    typedef map<Int_t , AliMUONSt1SpecialMotif> SpecialMap;
#endif
#ifdef ST1_WITH_ROOT
    typedef  TExMap  SpecialMap;
#endif
*/
    // Constants
    //
    static const GReal_t fgkHzPadPlane;    // Pad plane
    static const GReal_t fgkHzFoam;        // Foam of mechanicalplane
    static const GReal_t fgkHzFR4;         // FR4 of mechanical plane
    static const GReal_t fgkHzSnPb;        // Pad/Kapton connection (66 pt)
    static const GReal_t fgkHzKapton;      // Kapton
    static const GReal_t fgkHzBergPlastic; // Berg connector 
    static const GReal_t fgkHzBergCopper;  // Berg connector (80 pt)
    static const GReal_t fgkHzDaughter;    // Daughter board
    static const GReal_t fgkHzGas;         // ArCO2 Gas
        
    // Sensitive copper pads, foam layer, PCB and electronics model parameters
    static const GReal_t fgkHxHole;          // foam hole paremeter
    static const GReal_t fgkHyHole;          // foam hole paremeter
    static const GReal_t fgkHxBergPlastic;   // Berg connector parameter
    static const GReal_t fgkHyBergPlastic;   // Berg connector parameter
    static const GReal_t fgkHxBergCopper;    // Berg connector parameter
    static const GReal_t fgkHyBergCopper;    // Berg connector parameter
    static const GReal_t fgkHxKapton;        // Kapton parameter
    static const GReal_t fgkHyKapton;        // Kapton parameter
    static const GReal_t fgkHxDaughter;      // Electronics parameter
    static const GReal_t fgkHyDaughter;      // Electronics parameter
    static const GReal_t fgkOffsetX;         // Offset X
    static const GReal_t fgkOffsetY;         // Offset Y
    static const GReal_t fgkDeltaFilleEtamX; // Electronics parameter
    static const GReal_t fgkDeltaFilleEtamY; // Electronics parameter

    static const GReal_t fgkDeltaQuadLHC; // LHC Origin wrt Quadrant Origin
    static const GReal_t fgkFrameOffset;  // Frame offset

    // Quadrant Mother volume - TUBS1   
    static const GReal_t fgkMotherIR1;    // Middle Layer Rin
    static const GReal_t fgkMotherOR1;    // Middle Layer Rout
    static const GReal_t fgkMotherThick1; // Middle Layer Hz 
    static const GReal_t fgkMotherPhiL1;  // Middle Layer Sphi
    static const GReal_t fgkMotherPhiU1;  // Middle Layer Endphi

    // Quadrant Mother volume - TUBS2 (2 copies at different Z's)   
    static const GReal_t fgkMotherIR2;    // Near and Far Layer Rin
    static const GReal_t fgkMotherOR2;    // Near and Far Layer Rout
    static const GReal_t fgkMotherThick2; // Near and Far Layer Hz 
    static const GReal_t fgkMotherPhiL2;  // Near and Far Layer Sphi
    static const GReal_t fgkMotherPhiU2;  // Near and Far Layer Endphi  

    static const char* fgkHoleName;          // prefix for automatic volume naming
    static const char* fgkQuadrantMLayerName;// prefix for automatic volume naming
    static const char* fgkQuadrantNLayerName;// prefix for automatic volume naming
    static const char* fgkQuadrantFLayerName;// prefix for automatic volume naming
    static const char* fgkDaughterName;      // prefix for automatic volume naming
    static const char  fgkFoamLayerSuffix;   // suffix for automatic volume naming

    // Methods
    //
    void CreateHole();
    void CreateDaughterBoard();
    void CreateInnerLayers();
    void CreateQuadrant(Int_t chamber);
    void CreateFoamBox(const char* name,const TVector2& dimensions);
    void CreatePlaneSegment(const char* name,const TVector2& dimensions,
                     Int_t nofHoles);
    void CreateFrame(Int_t chamber);

    void PlaceInnerLayers(Int_t chamber);
    void PlaceSector(AliMpSector* sector, SpecialMap specialMap,
                     const TVector3& where, Bool_t reflectZ, Int_t chamber);
		     
    TString QuadrantMLayerName(Int_t chamber) const;
    TString QuadrantNLayerName(Int_t chamber) const;
    TString QuadrantFLayerName(Int_t chamber) const;
    TString GasVolumeName(const TString& name, Int_t chamber) const;

    void   AddChamberGid(Int_t id,Int_t volName,Int_t idx);
    //Bool_t IsInChamber(Int_t ich, Int_t volGid) const;   

    GReal_t TotalHzPlane() const ;         // Total mechanical plane half Size
    GReal_t TotalHzDaughter() const ;      // Total daughter plane half Size
    GReal_t TotalHz() const ;              // Total plane half Size
       
    // Data members
    //
    //Float_t  fRadlCopper;  //! copper computed radiation length
    //Float_t  fRadlFoam;    //! foam   computed radiation length
    //Float_t  fRadlFR4;     //! FR4    computed radiation length
    AliMUON*  fMUON; // the MUON detector class 
    
  ClassDef(AliMUONSt1GeometryBuilderV2,1)  // MUON Detector base class
};

// inline functions

inline GReal_t AliMUONSt1GeometryBuilderV2::TotalHzPlane() const 
//{ return fgkHzPadPlane + fgkHzFoam + fgkHzFR4; }
{ return fgkHzFoam + fgkHzFR4; }

inline GReal_t AliMUONSt1GeometryBuilderV2::TotalHzDaughter() const 
{ return fgkHzBergPlastic + fgkHzDaughter; }

inline GReal_t AliMUONSt1GeometryBuilderV2::TotalHz() const 
{ return TotalHzPlane() + TotalHzDaughter(); }

inline TString AliMUONSt1GeometryBuilderV2::QuadrantMLayerName(Int_t chamber) const
{ return Form("%s%d",fgkQuadrantMLayerName,chamber); }

inline TString AliMUONSt1GeometryBuilderV2::QuadrantNLayerName(Int_t chamber) const
{ return Form("%s%d",fgkQuadrantNLayerName,chamber); }

inline TString AliMUONSt1GeometryBuilderV2::QuadrantFLayerName(Int_t chamber) const
{ return Form("%s%d",fgkQuadrantFLayerName,chamber); }

#endif //ALI_MUON_ST1_GEOMETRY_BUILDER_V2_H
