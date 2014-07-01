/*
 * Copyright (C) 2007-2013 German Aerospace Center (DLR/SC)
 *
 * Created: 2014-01-28 Mark Geiger <Mark.Geiger@dlr.de>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
/**
 * @file
 * @brief  Implementation of CPACS ...  handling routines.
 */

#include <iostream>
#include <sstream>
#include <exception>
#include <cassert>

#include "CCPACSTrailingEdgeDevice.h"
#include "CCPACSWingComponentSegment.h"
#include "CCPACSWingSegment.h"

#include "Handle_Geom_Plane.hxx"
#include "Geom_Plane.hxx"
#include "BRepBuilderAPI_MakePolygon.hxx"
#include "GeomAPI_ProjectPointOnSurf.hxx"
#include "Handle_Geom_TrimmedCurve.hxx"
#include "BRepBuilderAPI_MakeEdge.hxx"
#include "BRepBuilderAPI_MakeFace.hxx"
#include "BRepBuilderAPI_MakeWire.hxx"
#include "BRepBuilderAPI_MakePolygon.hxx"
#include "GeomAPI_ProjectPointOnSurf.hxx"
#include "GC_MakeSegment.hxx"
#include <BRepPrimAPI_MakePrism.hxx>
#include <BRepAlgoAPI_Common.hxx>
#include <BRepAlgoAPI_Cut.hxx>
#include "Bnd_Box.hxx"
#include "BRepBndLib.hxx"
#include "gp_Pln.hxx"

#ifdef TIGL_USE_XCAF
#include "XCAFDoc_ShapeTool.hxx"
#include "XCAFApp_Application.hxx"
#include "XCAFDoc_DocumentTool.hxx"
#include "TDataStd_Name.hxx"
#include "TDataXtd_Shape.hxx"
#endif

namespace tigl {

CCPACSTrailingEdgeDevice::CCPACSTrailingEdgeDevice(CCPACSWingComponentSegment* segment)
    : _segment(segment)
{
    uID = "not loaded";
}

// Read CPACS trailingEdgeDevice elements
void CCPACSTrailingEdgeDevice::ReadCPACS(TixiDocumentHandle tixiHandle, const std::string& trailingEdgeDeviceXPath, bool isLeadingEdge)
{
    char*       elementPath;
    std::string tempString;

    // Get sublement "outerShape"
    char* ptrName = NULL;
    tempString    = trailingEdgeDeviceXPath + "/outerShape";
    elementPath   = const_cast<char*>(tempString.c_str());
    if (tixiGetTextElement(tixiHandle, elementPath, &ptrName) == SUCCESS)
    {
        outerShape.ReadCPACS(tixiHandle, elementPath, isLeadingEdge);
    }

    tempString = trailingEdgeDeviceXPath + "/path";
    elementPath = const_cast<char*>(tempString.c_str());
    if (tixiCheckElement(tixiHandle, elementPath) == SUCCESS) {
        path.ReadCPACS(tixiHandle, elementPath);
    }

    char* atrName = NULL;
    if ( tixiGetAttributeName(tixiHandle,trailingEdgeDeviceXPath.c_str(),1,&atrName) == SUCCESS ) {
        if (tixiCheckAttribute(tixiHandle, trailingEdgeDeviceXPath.c_str(), atrName) == SUCCESS ) {
            char* uIDtmp;
            tixiGetTextAttribute(tixiHandle,trailingEdgeDeviceXPath.c_str(),atrName, &uIDtmp);
            uID = uIDtmp;
        }
    }

    _isLeadingEdge = isLeadingEdge;
}

void CCPACSTrailingEdgeDevice::setLoft(TopoDS_Shape loft)
{
    this->loft = loft;
}

TopoDS_Shape CCPACSTrailingEdgeDevice::BuildLoft()
{
    return loft;
}

CCPACSControlSurfaceOuterShape CCPACSTrailingEdgeDevice::getOuterShape()
{
    return outerShape;
}

CCPACSTrailingEdgeDevicePath CCPACSTrailingEdgeDevice::getMovementPath()
{
    return path;
}

std::string CCPACSTrailingEdgeDevice::getUID()
{
    return uID;
}

gp_Trsf CCPACSTrailingEdgeDevice::getTransformation(double flapStatusInPercent)
{

    // rotation axis defined by two hinge Points, inner and outer.
    gp_Pnt hingePoint1;
    gp_Pnt hingePoint2;

    /*
     * this block of code calculates all needed values to rotate and move the trailingEdgeDevice according
     * to the given relDeflection by using a linearInterpolation.
     */
    std::vector<double> relDeflections = this->getMovementPath().getRelDeflections();
    double inputDeflection = ( relDeflections[relDeflections.size()-1] - relDeflections[0] ) * ( flapStatusInPercent/100 ) + relDeflections[0];
    double rotation = linearInterpolation( relDeflections, this->getMovementPath().getHingeLineRotations(), inputDeflection );
    double innerTranslationX = linearInterpolation( relDeflections, this->getMovementPath().getInnerHingeTranslationsX(), inputDeflection );
    double innerTranslationY = linearInterpolation( relDeflections, this->getMovementPath().getInnerHingeTranslationsY(), inputDeflection );
    double innerTranslationZ = linearInterpolation( relDeflections, this->getMovementPath().getInnerHingeTranslationsZ(), inputDeflection );
    double outerTranslationX = linearInterpolation( relDeflections, this->getMovementPath().getOuterHingeTranslationsX(), inputDeflection );
    double outerTranslationZ = linearInterpolation( relDeflections, this->getMovementPath().getOuterHingeTranslationsZ(), inputDeflection );
    relDeflections.clear();

    const tigl::CCPACSControlSurfaceBorder& outerBorder = this->getOuterShape().getOuterBorder();
    const tigl::CCPACSControlSurfaceBorder& innerBorder = this->getOuterShape().getInnerBorder();

    gp_Pnt innerHingeOld;
    gp_Pnt outerHingeOld;

    /*
     * determine outer and inner HingePoint, this is tricky because
     * the eta coordinate is not given in the CPACS file, so it has
     * to get calculated first.
     */
    for ( int borderCounter = 0; borderCounter < 2; borderCounter++) {
        tigl::CCPACSControlSurfaceBorder border;
        double hingeXsi;
        if (borderCounter == 0) {
            border = outerBorder;
            hingeXsi = this->getMovementPath().getOuterHingePoint().getXsi();
        }
        else {
            border = innerBorder;
            hingeXsi = this->getMovementPath().getInnerHingePoint().getXsi();
        }

        double borderEtaLE = border.getEtaLE();
        double borderEtaTE = border.getEtaTE();
        double hingeEta = -1;

        // only calculate etaCoordinate if it´s not the same as the other one.
        if ( fabs(borderEtaLE - borderEtaTE) < 0.0001 ) {
            hingeEta = (borderEtaTE + borderEtaLE)/2;
        }
        else {
            double m = ( border.getXsiLE() - 1 ) /( borderEtaLE - borderEtaTE );
            double x = borderEtaLE;
            double y = 1;
            double b = - ( ( m * x) / (y));
            hingeEta = ( y - b ) / m;
        }

        /*
         *  different approach for inner and outer border. borderCounter == 0 means outerBorder,
         *  borderCounter == 1 means innerBorder. Could be packed into one block by using arrays
         *  to store values.
         */
        if (borderCounter == 0) {
            hingePoint1 = _segment->GetPoint(hingeEta,hingeXsi);
            gp_Vec hingeTranslation(outerTranslationX, 0, outerTranslationZ);
            gp_Vec hingeVec1(hingePoint1.X(), hingePoint1.Y(), hingePoint1.Z());
            hingeVec1 = hingeVec1 + hingeTranslation;
            outerHingeOld = hingePoint1;
            hingePoint1.SetX(hingeVec1.X());
            hingePoint1.SetY(hingeVec1.Y());
            hingePoint1.SetZ(hingeVec1.Z());
        }
        else {
            hingePoint2 = _segment->GetPoint(hingeEta,hingeXsi);
            gp_Vec hingeTranslation(innerTranslationX, innerTranslationY, innerTranslationZ);
            gp_Vec hingeVec2(hingePoint2.X(), hingePoint2.Y(), hingePoint2.Z());
            hingeVec2 = hingeVec2 + hingeTranslation;
            innerHingeOld = hingePoint2;
            hingePoint2.SetX(hingeVec2.X());
            hingePoint2.SetY(hingeVec2.Y());
            hingePoint2.SetZ(hingeVec2.Z());
        }
    }

    // calculating the needed transformations
    CTiglControlSurfaceTransformation transformation(innerHingeOld, outerHingeOld, hingePoint2, hingePoint1, rotation);

    return transformation.getTotalTransformation();
}

TopoDS_Shape CCPACSTrailingEdgeDevice::getCutOutShape()
{
    TopoDS_Face face = getFace();
    gp_Vec vec = getNormalOfTrailingEdgeDevice();
    vec.Multiply(determineCutOutPrismThickness()*2);
    TopoDS_Shape prism = BRepPrimAPI_MakePrism(face,vec);

    loft = prism;
    return loft;
}

TopoDS_Face CCPACSTrailingEdgeDevice::getFace()
{
    tigl::CCPACSControlSurfaceBorder outerBorder = getOuterShape().getOuterBorder();
    gp_Pnt point1 = _segment->GetPoint(outerBorder.getEtaLE(),outerBorder.getXsiLE());
    gp_Pnt point2 = _segment->GetPoint(outerBorder.getEtaTE(),outerBorder.getXsiTE());

    tigl::CCPACSControlSurfaceBorder innerBorder = getOuterShape().getInnerBorder();
    gp_Pnt point3 = _segment->GetPoint(innerBorder.getEtaLE(),innerBorder.getXsiLE());
    gp_Pnt point4 = _segment->GetPoint(innerBorder.getEtaTE(), innerBorder.getXsiTE());

    gp_Vec nvV = getNormalOfTrailingEdgeDevice();
    nvV.Multiply(determineCutOutPrismThickness());

    gp_Vec sv;
    gp_Dir nv;

    sv = gp_Vec(point1.XYZ()) - (nvV);
    nv.SetXYZ(nvV.XYZ());

    Handle(Geom_Plane) plane = new Geom_Plane(gp_Pnt(sv.XYZ()),nv);

    gp_Pnt projectedPoint1;
    gp_Pnt projectedPoint2;
    gp_Pnt projectedPoint3;
    gp_Pnt projectedPoint4;

    GeomAPI_ProjectPointOnSurf projection1(point1,plane);
    for ( int i = 1; i <= projection1.NbPoints(); i++ ) {
       projectedPoint1 = projection1.Point(1);
    }
    GeomAPI_ProjectPointOnSurf projection2(point2,plane);
    for ( int i = 1; i <= projection2.NbPoints(); i++ ) {
        projectedPoint2 = projection2.Point(1);
    }
    GeomAPI_ProjectPointOnSurf projection3(point3,plane);
    for ( int i = 1; i <= projection3.NbPoints(); i++ ) {
      projectedPoint3 = projection3.Point(1);
    }
    GeomAPI_ProjectPointOnSurf projection4(point4,plane);
    for ( int i = 1; i <= projection4.NbPoints(); i++ ) {
        projectedPoint4 = projection4.Point(1);
    }

    gp_Vec p1(projectedPoint1.XYZ());
    gp_Vec p2(projectedPoint2.XYZ());
    gp_Vec p3(projectedPoint3.XYZ());
    gp_Vec p4(projectedPoint4.XYZ());

    gp_Vec dirP1P2(p2 - p1);
    gp_Vec dirP3P4(p4 - p3);
    dirP1P2.Normalize();
    dirP3P4.Normalize();

    double fac = 1;
    if ( _isLeadingEdge ) {
        fac = -1;
    }
    p2 = p2 + dirP1P2.Multiplied(0.1*fac);
    p4 = p4 + dirP3P4.Multiplied(0.1*fac);

    projectedPoint2.SetXYZ(p2.XYZ());
    projectedPoint4.SetXYZ(p4.XYZ());

    Handle(Geom_TrimmedCurve) segment1 = GC_MakeSegment(projectedPoint1,projectedPoint2);
    Handle(Geom_TrimmedCurve) segment2 = GC_MakeSegment(projectedPoint2,projectedPoint4);
    Handle(Geom_TrimmedCurve) segment3 = GC_MakeSegment(projectedPoint3,projectedPoint4);
    Handle(Geom_TrimmedCurve) segment4 = GC_MakeSegment(projectedPoint3,projectedPoint1);

    TopoDS_Edge edge1 = BRepBuilderAPI_MakeEdge(segment1);
    TopoDS_Edge edge2 = BRepBuilderAPI_MakeEdge(segment2);
    TopoDS_Edge edge3 = BRepBuilderAPI_MakeEdge(segment3);
    TopoDS_Edge edge4 = BRepBuilderAPI_MakeEdge(segment4);

    TopoDS_Wire wire = BRepBuilderAPI_MakeWire(edge4,edge3,edge2,edge1);
    TopoDS_Face face = BRepBuilderAPI_MakeFace(wire);

    return face;
}

double CCPACSTrailingEdgeDevice::linearInterpolation(std::vector<double> list1, std::vector<double> list2, double valueRelList1)
{
    double min = 0;
    double max = 0;
    int idefRem = 0;
    for ( std::vector<double>::size_type idef = 1; idef < list1.size(); idef++ ) {
        if ( list1[idef-1] <= valueRelList1 && list1[idef] >= valueRelList1 ) {
            min = list1[idef-1];
            max = list1[idef];
            idefRem = idef;
            break;
        }
    }
    double value = ( valueRelList1 - list1[idefRem-1] ) / ( list1[idefRem] - list1[idefRem-1] );
    double min2 = list2[idefRem-1];
    double max2 = list2[idefRem];
    return value * ( max2 - min2 ) + min2;
}

double CCPACSTrailingEdgeDevice::determineCutOutPrismThickness()
{
    TopoDS_Shape wcsShape = _segment->GetLoft();
    Bnd_Box B;
    double Xmin,Xmax,Ymin,Ymax,Zmin,Zmax;
    BRepBndLib::Add(wcsShape,B);
    B.Get(Xmin,Ymin,Zmin,Xmax,Ymax,Zmax);

    double minThickness = Xmax-Xmin;

    /*
     * This may lead to bugs in some really special cases, like when
     * a WCS is thicker than wide or long -> return maxThickness instead.
     */

    if ( Ymax-Ymin < minThickness ) {
        minThickness = Ymax-Ymin;
    }
    if ( Zmax-Zmin < minThickness ) {
        minThickness = Zmax-Zmin;
    }
    return minThickness;
}

gp_Vec CCPACSTrailingEdgeDevice::getNormalOfTrailingEdgeDevice()
{
    gp_Pnt point1 = _segment->GetPoint(0,0);
    gp_Pnt point2 = _segment->GetPoint(0,1);
    gp_Pnt point3 = _segment->GetPoint(1,0);

    gp_Vec dir1to2 = -(gp_Vec(point1.XYZ()) - gp_Vec(point2.XYZ()));
    gp_Vec dir1to3 = -(gp_Vec(point1.XYZ()) - gp_Vec(point3.XYZ()));

    gp_Vec nvV = dir1to2^dir1to3;
    nvV.Normalize();
    return nvV;
}

} // end namespace tigl