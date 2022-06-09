#include "MyViewerWidget.h"

MyViewerWidget::MyViewerWidget(std::string fileName, QWidget* parent)
	: QMainWindow(parent)
{
	_earthFileName = fileName;

	ui.setupUi(this);
	InitUI();
}

MyViewerWidget::~MyViewerWidget()
{
}

void MyViewerWidget::InitUI()
{
	viewer = new osgViewer::Viewer();
	viewer->setCameraManipulator(new osgEarth::Util::EarthManipulator());
	viewer->setThreadingModel(osgViewer::Viewer::SingleThreaded);//����Ϊ���߳�

	if (_earthFileName.empty())
	{
		return;
	}
	osg::ref_ptr<osg::Node> node = osgDB::readNodeFile(_earthFileName);
	osg::ref_ptr<osgEarth::MapNode> mapNode = osgEarth::MapNode::get(node.get());
	osg::Group* root = new osg::Group();
	root->addChild(mapNode);

	//��ȡ��Ļ�ֱ��� ����
	osg::GraphicsContext::WindowingSystemInterface* wsi = osg::GraphicsContext::getWindowingSystemInterface();
	if (!wsi)
		return;
	unsigned int width, height;
	wsi->getScreenResolution(osg::GraphicsContext::ScreenIdentifier(0), width, height);
	//����ͼ�λ�������
	osg::ref_ptr<osg::GraphicsContext::Traits> traits = new osg::GraphicsContext::Traits;
	traits->windowDecoration = false;//�����Ƿ���ʾ���ڵ�����
	traits->x = 0;
	traits->y = 0;
	traits->width = width;
	traits->height = height;
	traits->doubleBuffer = true;//����ͼ�δ����Ƿ�ʹ��˫����

	//���������
	osg::ref_ptr<osg::Camera> camera = new osg::Camera;
	camera->setGraphicsContext(new osgQt::GraphicsWindowQt(traits.get()));
	camera->setClearColor(osg::Vec4(0.2, 0.2, 0.5, 1.0));
	camera->setViewport(new osg::Viewport(0, 0, width, height));
	camera->setProjectionMatrixAsPerspective(30.0f, (double(traits->width)) / (double(traits->height)), 1.0f, 10000.0f);

	//������Ⱦ��
	viewer->setCamera(camera);
	viewer->setSceneData(root);


	//���ڴ�С�仯����ӦF
	viewer->addEventHandler(new osgViewer::WindowSizeHandler);
	//���·����¼ Z
	viewer->addEventHandler(new osgViewer::RecordCameraPathHandler);
	//�����ĵ���ʾH
	viewer->addEventHandler(new osgViewer::HelpHandler);
	//���� C
	viewer->addEventHandler(new osgViewer::ScreenCaptureHandler);
	//�ӽ�׷��
	viewer->addEventHandler(new osgViewer::ThreadingHandler);
	//���һЩ����״̬���ã���ӦW,S
	viewer->addEventHandler(new osgViewer::StatsHandler);

	//����ҵ���Ϣ
	MyGUIEventHandler* labEvent = new MyGUIEventHandler();
	viewer->addEventHandler(labEvent);


	//���hud
	root->addChild(createTextHUD());

	//��ʼ�����
	osgEarth::Util::SkyOptions skyOptions;
	osgEarth::Util::Ephemeris* ephemeris = new osgEarth::Util::Ephemeris;

	skyOptions.ambient() = 0.25;
	osgEarth::DateTime dateTime(2019, 5, 8, 12);
	osgEarth::Util::SkyNode* sky_node = osgEarth::Util::SkyNode::create(skyOptions, mapNode);
	sky_node->setEphemeris(ephemeris);
	viewer->setLightingMode(osg::View::SKY_LIGHT);
	sky_node->setDateTime(dateTime);
	sky_node->attach(viewer, 0);
	sky_node->setLighting(true);

	sky_node->addChild(mapNode);
	root->addChild(sky_node);

	// ui����
	osgQt::GraphicsWindowQt* gw = dynamic_cast<osgQt::GraphicsWindowQt*>(camera->getGraphicsContext());
	if (!gw)
	{
		QMessageBox::question(this, "��ʾ", "gw==null", QMessageBox::Yes | QMessageBox::No);
	}
	QWidget* osg_widget = (QWidget*)(gw->getGLWidget());
	this->setCentralWidget(osg_widget);

	//QGridLayout* grid = new QGridLayout;
	//grid->addWidget(osg_widget);

	//ui.openGLWidget->setLayout(grid);  //Ҫ�ҽӵĴ���


	//�������
	//this->setWindowState(Qt::WindowMaximized);
	//this->setWindowTitle(QString::fromLocal8Bit("���ֵ���"));

	QTimer* _timer = new QTimer;
	QObject::connect(_timer, SIGNAL(timeout()), this, SLOT(updateFrame()));
	_timer->start(10);
}

void MyViewerWidget::updateFrame()
{
	viewer->frame();
}

osg::Camera * MyViewerWidget::createTextHUD()
{
	osg::ref_ptr<osg::Camera> camera = new osg::Camera;
	camera->setViewMatrix(osg::Matrix::identity());
	camera->setRenderOrder(osg::Camera::POST_RENDER);  //�����Ⱦ

	camera->setClearMask(GL_DEPTH_BUFFER_BIT);
	camera->setAllowEventFocus(false);  //�����������¼�
	camera->setReferenceFrame(osg::Transform::ABSOLUTE_RF); //���游�ڵ���ʾ���� 
	camera->setProjectionMatrixAsOrtho2D(0, 1920, 0, 1080);

	osg::ref_ptr<osg::Geode> gnode = new osg::Geode;
	gnode->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF);//�رչ���
	osg::ref_ptr<osgText::Text> text = new osgText::Text;
	gnode->addDrawable(text);

	//text->setFont("Fonts/msyh.ttf");
	text->setCharacterSize(50);
	text->setText("hud");
	text->setPosition(osg::Vec3(0.0, 0.0, 0.0));

	osg::BoundingBox bx;
	bx.expandBy(text->getBound()); //���ֵİ�Χ��

	//�������
	osg::ref_ptr<osg::Geometry> gm = new osg::Geometry;
	gnode->addDrawable(gm);



	camera->addChild(gnode);
	return camera.release();

}

