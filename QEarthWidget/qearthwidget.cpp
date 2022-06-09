#include "qearthwidget.h"

QEarthWidget::QEarthWidget(QWidget *parent) : QWidget(parent)
{
	ui.setupUi(this);
}

void QEarthWidget::setOsgWidget(QWidget *widget)
{
	QVBoxLayout *layout = new QVBoxLayout(this);
	layout->addWidget(widget);

	viewerWidget = dynamic_cast<ViewerWidget*>(widget);						// ��ͼ����
	viewer = dynamic_cast<osgViewer::Viewer *>(viewerWidget->getViewer());	// ����ͼ���ڻ�ȡ��ͼ
	viewer->setCameraManipulator(earthManipulator);							// ���õ������������
	//����Ӧ�¼�
	viewer->addEventHandler(new osgGA::StateSetManipulator(viewer->getCamera()->getOrCreateStateSet()));
	viewer->addEventHandler(new osgViewer::StatsHandler);
	viewer->addEventHandler(new osgViewer::WindowSizeHandler);
	viewer->addEventHandler(new osgViewer::ScreenCaptureHandler);
	viewer->addEventHandler(new osgViewer::RecordCameraPathHandler);
	viewer->addEventHandler(new osgViewer::HelpHandler);

	viewer->getCamera()->setNearFarRatio(0.000006);						// ���õ������Զ����
	mapNode = MapNode::findMapNode(earthNode);								// ���ҶԶ������ͼ�ڵ�
	if (!mapNode) { QMSG_ERR(QCODEC("���ص�ͼʧ��!")); return; }

	SkyOptions skyOptions;											// ��ջ���ѡ��
	skyOptions.ambient() = 1;										// ��������ˮƽ(0~1)
	SkyNode* skyNode = SkyNode::create(skyOptions, mapNode);		// ���������ṩ��ա���������������Ч������
	skyNode->setDateTime(osgEarth::DateTime(2021, 4, 15, 12 - 8));	// ���û���������/ʱ�䡣(�������Σ�ʱ��8Сʱ)
	skyNode->setEphemeris(new osgEarth::Util::Ephemeris);			// ���ڸ�������/ʱ�䶨λ̫��������������
	skyNode->setLighting(true);										// ����Ƿ�������������ͼ
	skyNode->addChild(mapNode);										// ��ӵ�ͼ�ڵ�
	skyNode->attach(viewer);										// ������սڵ㸽�ŵ���ͼ��������⣩

	root->addChild(skyNode);										// �齫�����ڵ���루�����ڵ�����˵���
	viewer->setSceneData(root);										// ��ͼ���ó�������
	viewer->realize();												// ��ͼ����
}


