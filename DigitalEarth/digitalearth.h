#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_digitalearth.h"

#include <osgQt/GraphicsWindowQt>
#include <osgQt/QWidgetImage>
#include <osgQt/QGraphicsViewAdapter>

#include <QTimer>
#include <osgDB/ReadFile>
#include <osg/Group>
#include <osg/Node>
#include <osg/Camera>
#include <osg/PositionAttitudeTransform>
#include <osgGA/TrackballManipulator>
#include <osgGA/StateSetManipulator>
#include <osgViewer/ViewerEventHandlers>

#include <osgEarth/MapNode>
#include <osgEarth/SpatialReference>

#include <osgEarth/GeoTransForm>
#include <osgEarth/GeoCommon>
#include <osgEarth/SpatialReference>
#include <osgEarthUtil/EarthManipulator>
#include <osgEarthUtil/Ephemeris>
#include <osgEarthUtil/Sky>

#include <osgUtil/Tessellator>
//#include <osgEarth/GLUtils>
#include <osg/Geode>
#include <osg/Geometry>

#include <QList>
#include <QGroupBox>
#include <ctime>
#include <QStatusBar>
#include <QCheckBox>
#include <QPushButton>
#include <QSpinBox>
#include <QLineEdit>

class DigitalEarth : public QMainWindow
{
	Q_OBJECT

public:
	DigitalEarth(QWidget *parent = Q_NULLPTR);
	~DigitalEarth();

private:
	Ui::DigitalEarthClass ui;

private:
	QTimer* _timer;		// 计时器，每5ms触发一次事件
	osgViewer::Viewer* viewer;
	osg::ref_ptr<osg::Group> root;
	osg::ref_ptr<osg::Camera> camera;
	osg::ref_ptr<osg::Node> earthNode;
	osg::ref_ptr<osgEarth::MapNode> mapNode;
	osg::ref_ptr <osg::MatrixTransform> earthForm;
	osg::ref_ptr<osgEarth::Util::EarthManipulator> em;
	tm* t_tm;
	osgEarth::Util::SkyNode* m_pSkyNode;
	time_t now_time;
private:
	void InitOSG();// 初始化设置osg
	void InitUI();//界面初始化
	void InitTimer();//屏幕刷新初始化
	void InitOsgearth();//初始化osgearth
	void InitSky();//天空初始化
	private slots:
	// 定时更新帧的槽函数
	void updateFrame();
};

