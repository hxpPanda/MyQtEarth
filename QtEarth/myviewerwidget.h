#ifndef MYVIEWERWIDGET_H
#define MYVIEWERWIDGET_H

#include <QWidget>
#include <QtWidgets/QMainWindow>
#include "ui_myviewerwidget.h"

//#include "common.h"

#include <QMessageBox>
#define  QCODEC(str)	QString::fromLocal8Bit(str)
#define  QMSG_ERR(str)	QMessageBox::critical(0,QCODEC("错误"),str,QMessageBox::Ok)
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

#include <osgEarth/MapNode>
#include <osgEarth/Terrain>
#include <osgEarth/GeoTransform>
#include <osgEarth/ElevationQuery>
#include <osgEarth/ElevationQuery>

#include <osgEarthAnnotation/PlaceNode>
#include <osgEarthAnnotation/FeatureNode>
#include <osgEarthFeatures/Feature>
#include <osgEarthSymbology/Style>
#include <osgEarthSymbology/TextSymbol>
#include <osgEarthSymbology/IconSymbol>


#include <osg/BlendFunc>
#include <osg/BlendColor>
#include <osg/Math>
#include <osg/GraphicsContext>

#include <osgQt/GraphicsWindowQt>
#include <osgQt/QWidgetImage>
#include <osgQt/QGraphicsViewAdapter>

//我的事件消息
class MyGUIEventHandler : public osgGA::GUIEventHandler
{


public:

	MyGUIEventHandler()
	{

	};

	bool handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa)
	{
		osgViewer::View* view = dynamic_cast<osgViewer::View*>(&aa);
		//osgViewer::View* view = static_cast<osgViewer::View*>(aa.asView());
		if (view)
		{
			if (ea.getEventType() == ea.MOVE || ea.getButton() == ea.DRAG)
			{

				//cout << "getEventType == move" << endl;
			}

			if (ea.getEventType() == ea.KEYDOWN)
			{


				if (ea.getKey() == 'P')
				{
				}

			}
		}

		return false;
	};



private:

};


class MyViewerWidget : public QMainWindow
{
	Q_OBJECT

public:
	MyViewerWidget(std::string fileName, QWidget* parent = 0);
	~MyViewerWidget();

private:
	void InitUI();

	//hud
private:
	osg::Camera *createTextHUD();

private:
	Ui::MyViewerWidgetClass ui;

	osg::ref_ptr<osgViewer::Viewer> viewer;
	std::string _earthFileName;

	private slots:
	void  updateFrame();  //定时更新帧的槽函数
};

#endif // MYVIEWERWIDGET_H
