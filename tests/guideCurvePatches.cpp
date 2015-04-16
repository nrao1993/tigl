/* 
* Copyright (C) 2007-2014 German Aerospace Center (DLR/SC)
*
* Created: 2015-04-08 Tobias Stollenwerk <Tobias.Stollenwerk@dlr.de>
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


#include "test.h" 
#include "contrib/MakePatches.hxx" 
#include "contrib/MakeLoops.hxx" 

#include <BRepTools.hxx>
#include <BRep_Builder.hxx>
#include <Precision.hxx>
#include <GeomFill_FillingStyle.hxx>

#include <BRepAlgoAPI_Fuse.hxx>
#include <BOPCol_ListOfShape.hxx>
#include <BOPAlgo_PaveFiller.hxx>
#include <TopExp_Explorer.hxx>
#include <TopTools_ListIteratorOfListOfShape.hxx>
#include <TopoDS.hxx>
#include <TopoDS_Edge.hxx>
#include <Geom_Curve.hxx>
#include <BRepBuilderAPI_MakeVertex.hxx>
#include <TopTools_MapIteratorOfMapOfShape.hxx>
#include <TopExp.hxx>
#include <TopTools_IndexedDataMapOfShapeListOfShape.hxx>
#include <TopoDS_TEdge.hxx>

/******************************************************************************/

TEST(guideCurvePatches, segment)
{
    TopoDS_Shape guides;
    BRep_Builder b;
    ifstream in;
    in.open("TestData/guideCurvePatch_segmentGuides.brep");
    BRepTools::Read(guides, in, b);
    in.close();
    
    TopoDS_Shape profiles;
    in.open("TestData/guideCurvePatch_segmentProfiles.brep");
    BRepTools::Read(profiles, in, b);
    in.close();
    MakePatches SurfMaker(guides, profiles);
    Standard_Real tolConf = Precision::Confusion();
    Standard_Real tolPara = Precision::Confusion();
    GeomFill_FillingStyle style = GeomFill_CoonsC2Style;
    SurfMaker.Perform(tolConf, tolPara, style, Standard_True);
    TopoDS_Shape faces = SurfMaker.Patches();
    ASSERT_EQ(SurfMaker.GetStatus(), 0);
}

TEST(guideCurvePatches, simpleWing)
{
    TopoDS_Shape guides;
    BRep_Builder b;
    ifstream in;
    in.open("TestData/guideCurvePatch_simpleWingGuides.brep");
    BRepTools::Read(guides, in, b);
    in.close();
    
    TopoDS_Shape profiles;
    in.open("TestData/guideCurvePatch_simpleWingProfiles.brep");
    BRepTools::Read(profiles, in, b);
    in.close();
    MakePatches SurfMaker(guides, profiles);
    Standard_Real tolConf = Precision::Confusion();
    Standard_Real tolPara = Precision::Confusion();
    GeomFill_FillingStyle style = GeomFill_CoonsC2Style;
    SurfMaker.Perform(tolConf, tolPara, style, Standard_True);
    TopoDS_Shape faces = SurfMaker.Patches();
    ASSERT_EQ(SurfMaker.GetStatus(), 0);
}


gp_Pnt EdgeFirstPoint(TopoDS_Edge e) 
{
    double u1, u2;
    Handle_Geom_Curve c = BRep_Tool::Curve(e, u1, u2);
    
    if (e.Orientation() == TopAbs_REVERSED) {
        return c->Value(u2);
    }
    else {
        return c->Value(u1);
    }
}
gp_Pnt EdgeLastPoint(TopoDS_Edge e) 
{
    double u1, u2;
    Handle_Geom_Curve c = BRep_Tool::Curve(e, u1, u2);
    
    if (e.Orientation() == TopAbs_REVERSED) {
        return c->Value(u1);
    }
    else {
        return c->Value(u2);
    }
}


// implements the fusing part part and tests only the makeLoops part of the whole pipeline
// depending on two strings containing the filenames of the guides and profiles brep files
class guideCurvePatchesMakeLoops: public ::testing::TestWithParam<std::vector<std::string> > {
    
protected:
    virtual void SetUp()
    {
        // get name of the test case
        name = GetParam()[0];

        // ************************************************************
        // Read in guides and profiles
        // ************************************************************
        BRep_Builder b;
        ifstream in;
        in.open(GetParam()[1].c_str());
        BRepTools::Read(guides, in, b);
        in.close();

        in.open(GetParam()[2].c_str());
        BRepTools::Read(profiles, in, b);
        in.close();
    }

    void TearDown()
    {

        // ************************************************************
        // Export modified guide and profile edges
        // ************************************************************

        int gCount = 0;
        for(TopTools_MapIteratorOfMapOfShape it(GuideEdges); it.More(); it.Next()) {
            std::stringstream sguide;
            sguide << "TestData/export/guideCurvePatches_makeLoops_" << name << "_modifiedGuideEdge" << gCount << ".brep";
            BRepTools::Write(it.Key(), sguide.str().c_str());
            gCount++;
        }
        int pCount = 0;
        for(TopTools_MapIteratorOfMapOfShape it(ProfileEdges); it.More(); it.Next()) {
            std::stringstream sprofile;
            sprofile << "TestData/export/guideCurvePatches_makeLoops_" << name << "_modifiedProfileEdge" << pCount << ".brep";
            BRepTools::Write(it.Key(), sprofile.str().c_str());
            pCount++;
        }

        // ************************************************************
        // Get patch boundary loops
        // ************************************************************

        //Creating list of cells
        MakeLoops aLoopMaker(myGrid,  GuideEdges, ProfileEdges);
        aLoopMaker.Perform();
        ASSERT_EQ(aLoopMaker.GetStatus(), MAKEPATCHES_OK);
        const Handle(TopTools_HArray2OfShape)& PatchFrames = aLoopMaker.Cells();
        ASSERT_FALSE(PatchFrames.IsNull());

        for (Standard_Integer icell = 1; icell <= PatchFrames->ColLength(); icell++) {
            for (Standard_Integer jcell = 1; jcell <= PatchFrames->RowLength(); jcell++) {
                const TopoDS_Shape& aFrame =  PatchFrames->Value(icell, jcell);
                TopExp_Explorer anExp(aFrame, TopAbs_EDGE);
                int eCount = 0;
                std::vector<TopoDS_Edge> edges;
                for (; anExp.More(); anExp.Next()) {
                    const TopoDS_Edge& anE = TopoDS::Edge(anExp.Current());
                    edges.push_back(anE);

                    std::stringstream spatches;
                    spatches << "TestData/export/guideCurvePatches_makeLoops_" << name << "_patch" << icell << "-" << jcell << "_edge" << eCount << ".brep";
                    BRepTools::Write(anE, spatches.str().c_str());
                    eCount++;
                }
                ASSERT_EQ(edges.size(), 4);
                if (EdgeFirstPoint(edges[0]).Distance(EdgeFirstPoint(edges[3])) < Precision::Confusion()) {
                    ASSERT_NEAR(EdgeFirstPoint(edges[0]).Distance(EdgeFirstPoint(edges[3])), 0, Precision::Confusion());
                    ASSERT_NEAR( EdgeLastPoint(edges[0]).Distance(EdgeFirstPoint(edges[1])), 0, Precision::Confusion());
                    ASSERT_NEAR(EdgeFirstPoint(edges[2]).Distance( EdgeLastPoint(edges[3])), 0, Precision::Confusion());
                    ASSERT_NEAR( EdgeLastPoint(edges[2]).Distance( EdgeLastPoint(edges[1])), 0, Precision::Confusion());
                }
                else {
                    ASSERT_NEAR(EdgeFirstPoint(edges[0]).Distance(EdgeFirstPoint(edges[1])), 0, Precision::Confusion());
                    ASSERT_NEAR( EdgeLastPoint(edges[0]).Distance(EdgeFirstPoint(edges[3])), 0, Precision::Confusion());
                    ASSERT_NEAR(EdgeFirstPoint(edges[2]).Distance( EdgeLastPoint(edges[1])), 0, Precision::Confusion());
                    ASSERT_NEAR( EdgeLastPoint(edges[2]).Distance( EdgeLastPoint(edges[3])), 0, Precision::Confusion());
                }
            }
        }
    }
    // guides as input for makeLoops
    TopTools_MapOfShape GuideEdges;
    // profiles as input for makeLoops
    TopTools_MapOfShape ProfileEdges;
    // fused guides and profiles
    TopoDS_Shape myGrid;
    // name of the test case
    std::string name;
    // input guides
    TopoDS_Shape guides;
    // input profiles
    TopoDS_Shape profiles;
};

TEST_P(guideCurvePatchesMakeLoops, fuseAtOnce)
{
    BRepAlgoAPI_Fuse* Fuser;

    BOPCol_ListOfShape aLC;
    aLC.Append(guides);
    aLC.Append(profiles);

    Handle(NCollection_BaseAllocator) aAL = new NCollection_IncAllocator;
    BOPAlgo_PaveFiller aPF(aAL);
    //
    aPF.SetArguments(aLC);
    //
    aPF.Perform();

    Standard_Integer iErr = aPF.ErrorStatus();
    ASSERT_FALSE(iErr);
    Fuser = new BRepAlgoAPI_Fuse(guides, profiles, aPF);
    ASSERT_TRUE(Fuser->IsDone());

    myGrid = Fuser->Shape();

    TopTools_ListIteratorOfListOfShape itl;
    TopExp_Explorer Explo(guides, TopAbs_EDGE);
    for (; Explo.More(); Explo.Next()) {
        const TopoDS_Shape& anEdge = Explo.Current();
        const TopTools_ListOfShape& aList = Fuser->Modified(anEdge);
        if (aList.IsEmpty()) {
            GuideEdges.Add(anEdge);
        }
        else {
            for (itl.Initialize(aList); itl.More(); itl.Next()) {
                GuideEdges.Add(itl.Value());
            }
        }
    }
    for (Explo.Init(profiles, TopAbs_EDGE); Explo.More(); Explo.Next()) {
        const TopoDS_Shape& anEdge = Explo.Current();
        const TopTools_ListOfShape& aList = Fuser->Modified(anEdge);
        if (aList.IsEmpty()) {
            ProfileEdges.Add(anEdge);
        }
        else {
            for (itl.Initialize(aList); itl.More(); itl.Next()) {
                ProfileEdges.Add(itl.Value());
            }
        }
    }
}

TEST_P(guideCurvePatchesMakeLoops, fuseSequential)
{
    // ************************************************************
    // Fuse all guides and profiles one after another, since the
    // fusing in one step is buggy in OpenCASCADE
    // ************************************************************
    // save fusers
    std::vector<BRepAlgoAPI_Fuse*> fusers;
    TopExp_Explorer ex(guides, TopAbs_EDGE);
    // resulting grid wire
    myGrid = ex.Current();;
    for(; ex.More(); ex.Next()) {
        TopoDS_Edge E = TopoDS::Edge(ex.Current());
        BRepAlgoAPI_Fuse* fuser = new BRepAlgoAPI_Fuse(myGrid, E);
        ASSERT_TRUE(fuser->IsDone());
        myGrid = fuser->Shape();
        fusers.push_back(fuser);
    }
    for(TopExp_Explorer pex(profiles, TopAbs_EDGE); pex.More(); pex.Next()) {
        TopoDS_Edge E = TopoDS::Edge(pex.Current());
        BRepAlgoAPI_Fuse* fuser = new BRepAlgoAPI_Fuse(myGrid, E);
        ASSERT_TRUE(fuser->IsDone());
        myGrid = fuser->Shape();
        fusers.push_back(fuser);
    }

    // ************************************************************
    // Get the profile and guide edges after fusing
    // (they might be cutted)
    // ************************************************************
    TopoDS_Compound cuttedProfiles;
    BRep_Builder profileBuilder;
    profileBuilder.MakeCompound(cuttedProfiles);
    TopoDS_Compound cuttedGuides;
    BRep_Builder guideBuilder;
    guideBuilder.MakeCompound(cuttedGuides);

    TopTools_ListIteratorOfListOfShape itl;
    TopExp_Explorer Explo(guides, TopAbs_EDGE);
    for (; Explo.More(); Explo.Next()) {
        const TopoDS_Shape& anEdge = Explo.Current();
        bool ModifiedEdgeFound = false;
        for (int i = 0; i < fusers.size(); i++) {
            const TopTools_ListOfShape& aList = fusers[i]->Modified(anEdge);
            if (!aList.IsEmpty()) {
                for (itl.Initialize(aList); itl.More(); itl.Next()) {
                    guideBuilder.Add(cuttedGuides, itl.Value());
                }
                ModifiedEdgeFound = true;
                break;
            }
        }
        if (!ModifiedEdgeFound) {
            guideBuilder.Add(cuttedGuides, anEdge);
        }
    }
    for (Explo.Init(profiles, TopAbs_EDGE); Explo.More(); Explo.Next()) {
        const TopoDS_Shape& anEdge = Explo.Current();
        bool ModifiedEdgeFound = false;
        for (int i = 0; i < fusers.size(); i++) {
            const TopTools_ListOfShape& aList = fusers[i]->Modified(anEdge);
            if (!aList.IsEmpty()) {
                for (itl.Initialize(aList); itl.More(); itl.Next()) {
                    profileBuilder.Add(cuttedProfiles, itl.Value());
                }
                ModifiedEdgeFound = true;
                break;
            }
        }
        if (!ModifiedEdgeFound) {
            profileBuilder.Add(cuttedProfiles, anEdge);
        }
    }

    // ************************************************************
    // Fuse the cutted guides and cutted profiles
    // ************************************************************
    BRepAlgoAPI_Fuse fuser2(cuttedGuides, cuttedProfiles);
    ASSERT_TRUE(fuser2.IsDone());
    myGrid = fuser2.Shape();

    // ************************************************************
    // Get the guide and profile edges after fusing 
    // ************************************************************
    Explo.Init(cuttedGuides, TopAbs_EDGE);
    for (; Explo.More(); Explo.Next()) {
        const TopoDS_Shape& anEdge = Explo.Current();
        const TopTools_ListOfShape& aList = fuser2.Modified(anEdge);
        if (!aList.IsEmpty()) {
            for (itl.Initialize(aList); itl.More(); itl.Next()) {
                GuideEdges.Add(itl.Value());
            }
        }
        else {
            GuideEdges.Add(anEdge);
        }
    }
    for (Explo.Init(cuttedProfiles, TopAbs_EDGE); Explo.More(); Explo.Next()) {
        const TopoDS_Shape& anEdge = Explo.Current();
        const TopTools_ListOfShape& aList = fuser2.Modified(anEdge);
        if (!aList.IsEmpty()) {
            for (itl.Initialize(aList); itl.More(); itl.Next()) {
                ProfileEdges.Add(itl.Value());
            }
        }
        else {
            ProfileEdges.Add(anEdge);
        }
    }

}

// test case for single segment
const char * fnsg[] = {"segment", "TestData/guideCurvePatch_segmentGuides.brep", "TestData/guideCurvePatch_segmentProfiles.brep"};
const std::vector<std::string> filenamesSegment(fnsg, fnsg + 3);
// test case for simple wing from simpletest.xml file
const char * fnst[] = {"simpleTest", "TestData/guideCurvePatch_simpleWingSimpleTestGuides.brep", "TestData/guideCurvePatch_simpleWingSimpleTestProfiles.brep"};
const std::vector<std::string> filenamesSimpleTest(fnst, fnst + 3);
// test case for simple wing
const char * fnsw[] = {"simpleWing", "TestData/guideCurvePatch_simpleWingGuides.brep", "TestData/guideCurvePatch_simpleWingProfiles.brep"};
const std::vector<std::string> filenamesSimpleWing(fnsw, fnsw + 3);
// combine all test cases
const std::vector<std::string> fn[] = {filenamesSegment, filenamesSimpleTest, filenamesSimpleWing};
const std::vector<std::vector< std::string> >filenames(fn, fn + 3);

INSTANTIATE_TEST_CASE_P(makeLoops, guideCurvePatchesMakeLoops, ::testing::ValuesIn(filenames));