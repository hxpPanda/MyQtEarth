#ifndef QEARTHWIDGET_H
#define QEARTHWIDGET_H

#include "Global.h"
#include "ui_qearthwidget.h"

class QEarthWidget : public QWidget
{
	Q_OBJECT

public:
	QEarthWidget(QWidget *parent = Q_NULLPTR);

	void setOsgWidget(QWidget *);

private:
	Ui::QEarthWidgetClass ui;

	ViewerWidget				*viewerWidget = nullptr;
	osgViewer::Viewer			*viewer = nullptr;
	osg::ref_ptr<osg::Group>	root = new osg::Group();
	osg::ref_ptr<osg::Node>		earthNode = osgDB::readNodeFile("D:/OSGcore/path/data/gdal_tiff.earth");
	EarthManipulator			*earthManipulator = new EarthManipulator();
	osg::ref_ptr<MapNode>		mapNode;
};


#endif

