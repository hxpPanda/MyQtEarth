#include "qearthwidget.h"

QEarthWidget::QEarthWidget(QWidget *parent) : QWidget(parent)
{
	ui.setupUi(this);
}

void QEarthWidget::setOsgWidget(QWidget *widget)
{
	QVBoxLayout *layout = new QVBoxLayout(this);
	layout->addWidget(widget);

	viewerWidget = dynamic_cast<ViewerWidget*>(widget);						// 视图窗口
	viewer = dynamic_cast<osgViewer::Viewer *>(viewerWidget->getViewer());	// 从视图窗口获取视图
	viewer->setCameraManipulator(earthManipulator);							// 设置地球相机操作者
	//各响应事件
	viewer->addEventHandler(new osgGA::StateSetManipulator(viewer->getCamera()->getOrCreateStateSet()));
	viewer->addEventHandler(new osgViewer::StatsHandler);
	viewer->addEventHandler(new osgViewer::WindowSizeHandler);
	viewer->addEventHandler(new osgViewer::ScreenCaptureHandler);
	viewer->addEventHandler(new osgViewer::RecordCameraPathHandler);
	viewer->addEventHandler(new osgViewer::HelpHandler);

	viewer->getCamera()->setNearFarRatio(0.000006);						// 设置地球相机远近比
	mapNode = MapNode::findMapNode(earthNode);								// 查找对顶层的贴图节点
	if (!mapNode) { QMSG_ERR(QCODEC("加载地图失败!")); return; }

	SkyOptions skyOptions;											// 天空环境选项
	skyOptions.ambient() = 1;										// 环境光照水平(0~1)
	SkyNode* skyNode = SkyNode::create(skyOptions, mapNode);		// 创建用于提供天空、照明和其他环境效果的类
	skyNode->setDateTime(osgEarth::DateTime(2021, 4, 15, 12 - 8));	// 配置环境的日期/时间。(格林尼治，时差8小时)
	skyNode->setEphemeris(new osgEarth::Util::Ephemeris);			// 用于根据日期/时间定位太阳和月亮的星历
	skyNode->setLighting(true);										// 天空是否照亮了它的子图
	skyNode->addChild(mapNode);										// 添加地图节点
	skyNode->attach(viewer);										// 将此天空节点附着到视图（放置天光）

	root->addChild(skyNode);										// 组将环境节点加入（环境节点包含了地球）
	viewer->setSceneData(root);										// 视图设置场景数据
	viewer->realize();												// 视图产生
}


