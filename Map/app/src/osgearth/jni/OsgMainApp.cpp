#include "OsgMainApp.hpp"

#include <osgEarthUtil/EarthManipulator>
#include <osgEarth/MapNode>


// Create scene graph and start TCP/UDP sockets for communicating with the server
// DemoScene.cpp contains viewer setup
// osgEarthDemo.cpp contains Map and EarthManipulator setup
void OsgMainApp::initOsgWindow(int x,int y,int width,int height)
{
    _scene = new DemoScene();
    _scene->setDataPath(_dataPath, _packagePath);
    _scene->init("", osg::Vec2(width, height), 0);
    _bufferWidth = width;
    _bufferHeight = height;
}

// Called from Java app on frame render
void OsgMainApp::draw()
{
    _scene->frame();
    
    //clear events for next frame
    _frameTouchBeganEvents = NULL;
    _frameTouchMovedEvents = NULL;
    _frameTouchEndedEvents = NULL;
}

// Events originate in the Java code
// Attach handlers to each type of event
static bool flipy = true;
void OsgMainApp::touchBeganEvent(int touchid,float x,float y)
{
    if (!_frameTouchBeganEvents.valid()) {
        if(_scene->getViewer()){
            _frameTouchBeganEvents = _scene->getViewer()->getEventQueue()->touchBegan(touchid, osgGA::GUIEventAdapter::TOUCH_BEGAN, x, flipy ? _bufferHeight-y : y);
        }
    } else {
        _frameTouchBeganEvents->addTouchPoint(touchid, osgGA::GUIEventAdapter::TOUCH_BEGAN, x, flipy ? _bufferHeight-y : y);
    }
}

void OsgMainApp::touchMovedEvent(int touchid,float x,float y)
{
    if (!_frameTouchMovedEvents.valid())
    {
        if(_scene->getViewer()){
            _frameTouchMovedEvents = _scene->getViewer()->getEventQueue()->touchMoved(touchid, osgGA::GUIEventAdapter::TOUCH_MOVED, x, flipy ? _bufferHeight-y : y);
        }
    } else {
        _frameTouchMovedEvents->addTouchPoint(touchid, osgGA::GUIEventAdapter::TOUCH_MOVED, x, flipy ? _bufferHeight-y : y);
    }
}

void OsgMainApp::touchZoomEvent(double delta)
{
	osgEarth::Util::EarthManipulator* manip = dynamic_cast<osgEarth::Util::EarthManipulator*>(_scene->getViewer()->getCameraManipulator());
	manip->zoom(0.0, delta);
}

void OsgMainApp::touchEndedEvent(int touchid,float x,float y,int tapcount)
{
    if (!_frameTouchEndedEvents.valid())
    {
        if(_scene->getViewer()){
            _frameTouchEndedEvents = _scene->getViewer()->getEventQueue()->touchEnded(touchid, osgGA::GUIEventAdapter::TOUCH_ENDED, x, flipy ? _bufferHeight-y : y,tapcount);
        }
    } else {
        _frameTouchEndedEvents->addTouchPoint(touchid, osgGA::GUIEventAdapter::TOUCH_ENDED, x, flipy ? _bufferHeight-y : y,tapcount);
    }
}

void OsgMainApp::clearEventQueue()
{
    //clear our groups
    _frameTouchBeganEvents = NULL;
    _frameTouchMovedEvents = NULL;
    _frameTouchEndedEvents = NULL;
    
    //clear the viewers queue
    _scene->getViewer()->getEventQueue()->clear();
}

void OsgMainApp::setDataPath(std::string dataPath, std::string packagePath)
{
	_dataPath = dataPath;
	_packagePath = packagePath;
}
