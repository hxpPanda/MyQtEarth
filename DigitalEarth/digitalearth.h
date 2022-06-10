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
	QTimer* _timer;		// ��ʱ����ÿ5ms����һ���¼�
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
	void InitOSG();// ��ʼ������osg
	void InitUI();//�����ʼ��
	void InitTimer();//��Ļˢ�³�ʼ��
	void InitOsgearth();//��ʼ��osgearth
	void InitSky();//��ճ�ʼ��
	private slots:
	// ��ʱ����֡�Ĳۺ���
	void updateFrame();
};

