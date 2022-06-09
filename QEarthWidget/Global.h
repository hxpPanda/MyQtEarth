#pragma once
#include <QVBoxLayout>
#include <QtWidgets/QWidget>
#include <QtWidgets/QApplication>
#include <QMessageBox>
#define  QCODEC(str)	QString::fromLocal8Bit(str)
#define  QMSG_ERR(str)	QMessageBox::critical(0,QCODEC("´íÎó"),str,QMessageBox::Ok)

#include <osgUtil/LineSegmentIntersector>
#include <osgUtil/IntersectVisitor>

#include <osgGA/StateSetManipulator>
#include <osgGA/GUIEventHandler>
#include <osgGA/NodeTrackerManipulator>
#include <osgGA/FirstPersonManipulator>
#include <osgGA/KeySwitchMatrixManipulator>

#include <osgViewer/View>
#include <osgViewer/Viewer>
#include <osgViewer/ViewerEventHandlers>

#include <osgEarthUtil/EarthManipulator>
#include <osgEarthUtil/AutoClipPlaneHandler>
#include <osgEarthUtil/Sky>
#include <osgEarthQt/ViewerWidget>
#include <osgEarthUtil/EarthManipulator>
#include <osgEarth/MapNode>
#include <osgEarthSymbology/Style>
#include <osgEarthAnnotation/PlaceNode>
#include <osgEarth/GeoTransform>
#include <osgEarth/ElevationQuery>
#include <osgEarth/ElevationQuery>
#include <osgEarthAnnotation/FeatureNode>
#include <osgEarthFeatures/Feature>
#include <osgEarthSymbology/TextSymbol>
#include <osgEarthSymbology/IconSymbol>
#include <osgEarth/Terrain>

#include <osg/BlendFunc>
#include <osg/BlendColor>
#include <osg/Math>
#include <osg/GraphicsContext>

#include <osgQt/GraphicsWindowQt>
#include <osgQt/QWidgetImage>
#include <osgQt/QGraphicsViewAdapter>


using namespace osgEarth::QtGui;
using namespace osgEarth::Util;
using namespace osgEarth;
