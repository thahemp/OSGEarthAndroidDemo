//
//  DemoScene.cpp
//  osgearthDemos
//

#include "DemoScene.h"
#include "debug.h"
#include <osgEarth/AndroidCapabilities>
#include <osgEarth/Registry>

DemoScene::DemoScene()
    :osg::Referenced()
{
    
}

DemoScene::~DemoScene()
{
    
}

void DemoScene::init(const std::string& file, osg::Vec2 viewSize, UIView* view)
{
	// Set up a handler to pass debug info to the java code
	DebugAndroid *notify = new DebugAndroid();
	notify->setTag("OSGEarthAndroidDemo");
	osg::setNotifyHandler(notify);

    osg::setNotifyLevel(osg::INFO);
    osgEarth::setNotifyLevel(osg::INFO);

	OSG_ALWAYS << "Initializing scene graph" << std::endl;

    osgEarth::Registry::instance()->setCapabilities(new osgEarth::AndroidCapabilities());
    
	_viewer = new osgViewer::Viewer();
    _viewer->setUpViewerAsEmbeddedInWindow(0, 0, viewSize.x(), viewSize.y());
    _viewer->getCamera()->setViewport(new osg::Viewport(0, 0, viewSize.x(), viewSize.y()));
    _viewer->getCamera()->setClearMask(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    _viewer->getCamera()->setClearColor(osg::Vec4(0.0f,1.0f,0.0f,1.0f));
    _viewer->getCamera()->setProjectionMatrixAsPerspective(45.0f,(float)viewSize.x()/viewSize.y(), 0.1, 1000.0);
    _viewer->getCamera()->setNearFarRatio(0.00002);
    _viewer->setThreadingModel(osgViewer::ViewerBase::SingleThreaded);
    _viewer->getDatabasePager()->setIncrementalCompileOperation(new osgUtil::IncrementalCompileOperation());
    _viewer->getDatabasePager()->setDoPreCompile( true );
    _viewer->getDatabasePager()->setTargetMaximumNumberOfPageLOD(0);
    _viewer->getDatabasePager()->setUnrefImageDataAfterApplyPolicy(true,true);

    this->initDemo(file);
}

void DemoScene::frame()
{
	_viewer->frame();
}

void DemoScene::setDataPath(std::string dataPath, std::string packagePath)
{
	_dataPath = dataPath;
	_packagePath = packagePath;
}

