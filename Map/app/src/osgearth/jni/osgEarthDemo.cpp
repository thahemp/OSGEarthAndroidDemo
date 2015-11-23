//
//  osgEarthDemo.cpp
//  osgearthDemos
//

#include "DemoScene.h"

#include <osgEarth/MapNode>
#include <osgEarthUtil/Sky>
#include <osgEarthUtil/EarthManipulator>
#include <osgEarthDrivers/tms/TMSOptions>
#include <osgEarthDrivers/tilecache/TileCacheOptions>
#include <osg/PositionAttitudeTransform>

#include <osgDB/ReadFile>
#include <osgDB/FileUtils>
#include <osgGA/MultiTouchTrackballManipulator>


using namespace osgEarth;
using namespace osgEarth::Util;
using namespace osgEarth::Drivers;


// Initialize satellite and OSM image layers
int createImageLayers(osgEarth::Map *map)
{
	// add a TMS imager layer:
    TMSOptions imagery;
    imagery.url() = "http://readymap.org/readymap/tiles/1.0.0/7/";
    map->addImageLayer( new ImageLayer("Imagery", imagery) );

	return 0;
}


void DemoScene::initDemo(const std::string &file)
{
	osgEarth::Map *map = new osgEarth::Map();
	createImageLayers(map);
	_mapNode = new osgEarth::MapNode(map);

    _viewer->setCameraManipulator(new osgEarth::Util::EarthManipulator());
	osgEarth::Util::EarthManipulator* manip = dynamic_cast<osgEarth::Util::EarthManipulator*>(_viewer->getCameraManipulator());
	osgEarth::Util::EarthManipulator::ActionOptions options;
	manip->getSettings()->setMouseSensitivity(0.30);
	manip->getSettings()->setThrowingEnabled(true);
	manip->getSettings()->setThrowDecayRate(0.1);
	manip->getSettings()->setLockAzimuthWhilePanning(true);
	manip->getSettings()->setArcViewpointTransitions(false);
	manip->getSettings()->bindTwist(osgEarth::Util::EarthManipulator::ACTION_NULL, options);
	manip->getSettings()->bindMultiDrag(osgEarth::Util::EarthManipulator::ACTION_NULL, options);
	manip->getSettings()->setMinMaxPitch(-90.0, -90.0);

	osgEarth::Util::SkyOptions sOptions;
	sOptions.ambient() = 1.0;
	osgEarth::Util::SkyNode* sky = osgEarth::Util::SkyNode::create(sOptions, _mapNode);
	sky->attach(_viewer, 0);
	sky->addChild(_mapNode);

    osg::Group* root = new osg::Group();
    root->addChild(sky);

    // Set up our material and lighting properties
    osg::Material* material = new osg::Material();
    material->setAmbient(osg::Material::FRONT, osg::Vec4(0.4,0.4,0.4,1.0));
    material->setDiffuse(osg::Material::FRONT, osg::Vec4(0.9,0.9,0.9,1.0));
    material->setSpecular(osg::Material::FRONT, osg::Vec4(0.4,0.4,0.4,1.0));
    root->getOrCreateStateSet()->setAttribute(material);
	root->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF | osg::StateAttribute::OVERRIDE);
	root->getOrCreateStateSet()->setAttribute(_viewer->getLight());

	_viewer->setSceneData(root);

    _viewer->realize();
}
