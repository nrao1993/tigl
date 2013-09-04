#include "SelectionBoxHandler.h"
#include <algorithm>
#include <iostream>

bool SelectionBoxHandler::select(osgViewer::View* view, const double currentX, const double currentY){
	    if(!view->getSceneData()) return false;

        float xMin = std::min(start_X, currentX);
        float yMin = std::min(start_Y, currentY);
        float xMax = std::max(start_X, currentX);
		float yMax = std::max(start_Y, currentY);

        osgUtil::PolytopeIntersector* intersector =
			new osgUtil::PolytopeIntersector(osgUtil::PolytopeIntersector::WINDOW, xMin, yMin, xMax, yMax);

        osgUtil::IntersectionVisitor iv(intersector);
        view->getCamera()->accept(iv);

        if(intersector->containsIntersections())
        {
            osgUtil::PolytopeIntersector::Intersection result =  *(intersector->getIntersections().begin());
            osg::NodePath path = result.nodePath;

			for(unsigned int i = 0; i < result.numIntersectionPoints; ++i)
            {
				std::cout << "Something was selected:" << path.back()->getName() << std::endl;
            }
            return true;
        }

        return false;
    }

bool SelectionBoxHandler::handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa)
   { 
        if(ea.getButton() != osgGA::GUIEventAdapter::LEFT_MOUSE_BUTTON ||
           !(ea.getModKeyMask() & osgGA::GUIEventAdapter::MODKEY_CTRL))
        {
            return false;
        }

        osgViewer::View* view = dynamic_cast<osgViewer::View*>(&aa);
        if(!view) return false;

        switch(ea.getEventType())
        {
            case osgGA::GUIEventAdapter::PUSH:
            case osgGA::GUIEventAdapter::MOVE:
            {
                // record mouse location for the button press and move event
                start_X = ea.getX();
                start_Y = ea.getY();
                return false;
            }
            case osgGA::GUIEventAdapter::RELEASE:
            {
                if(start_X != ea.getX() && start_Y != ea.getY())
                {
                    if(select( view, ea.getX(), ea.getY()))
                    {
                        return true;
                    }
                }

                return false;
            }
        }

        return false;
    }