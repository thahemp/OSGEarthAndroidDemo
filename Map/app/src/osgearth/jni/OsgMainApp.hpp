#ifndef OSGMAINAPP_HPP_
#define OSGMAINAPP_HPP_

#include <android/log.h>
#include <iostream>
#include <cstdlib>
#include <math.h>
#include <string>
#include <osgViewer/Viewer>
#include "osgPlugins.h"
#include "DemoScene.h"


class OsgMainApp{
	private:
		osg::ref_ptr<DemoScene> _scene;
		int _bufferWidth;
		int _bufferHeight;
		std::string _dataPath;
		std::string _packagePath;
		bool _initialized;

		//events for each touch phase, these are cleared each frame
		osg::ref_ptr<osgGA::GUIEventAdapter> _frameTouchBeganEvents;
		osg::ref_ptr<osgGA::GUIEventAdapter> _frameTouchMovedEvents;
		osg::ref_ptr<osgGA::GUIEventAdapter> _frameTouchEndedEvents;
		
	public:
		void initOsgWindow(int x,int y,int width,int height);
		void draw();
		void touchBeganEvent(int touchid,float x,float y);
		void touchMovedEvent(int touchid,float x,float y);
		void touchZoomEvent(double delta);
		void touchEndedEvent(int touchid,float x,float y,int tapcount=0);
		void clearEventQueue();
		void setDataPath(std::string dataPath, std::string packagePath);
};


#endif /* OSGMAINAPP_HPP_ */
