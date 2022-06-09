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
	viewer->setThreadingModel(osgViewer::Viewer::SingleThreaded);//创建为单线程

	if (_earthFileName.empty())
	{
		return;
	}
	osg::ref_ptr<osg::Node> node = osgDB::readNodeFile(_earthFileName);
	osg::ref_ptr<osgEarth::MapNode> mapNode = osgEarth::MapNode::get(node.get());
	osg::Group* root = new osg::Group();
	root->addChild(mapNode);

	//获取屏幕分辨率 长宽
	osg::GraphicsContext::WindowingSystemInterface* wsi = osg::GraphicsContext::getWindowingSystemInterface();
	if (!wsi)
		return;
	unsigned int width, height;
	wsi->getScreenResolution(osg::GraphicsContext::ScreenIdentifier(0), width, height);
	//设置图形环境特性
	osg::ref_ptr<osg::GraphicsContext::Traits> traits = new osg::GraphicsContext::Traits;
	traits->windowDecoration = false;//声明是否显示窗口的描述
	traits->x = 0;
	traits->y = 0;
	traits->width = width;
	traits->height = height;
	traits->doubleBuffer = true;//创建图形窗口是否使用双缓存

	//设置照相机
	osg::ref_ptr<osg::Camera> camera = new osg::Camera;
	camera->setGraphicsContext(new osgQt::GraphicsWindowQt(traits.get()));
	camera->setClearColor(osg::Vec4(0.2, 0.2, 0.5, 1.0));
	camera->setViewport(new osg::Viewport(0, 0, width, height));
	camera->setProjectionMatrixAsPerspective(30.0f, (double(traits->width)) / (double(traits->height)), 1.0f, 10000.0f);

	//设置渲染器
	viewer->setCamera(camera);
	viewer->setSceneData(root);


	//窗口大小变化，响应F
	viewer->addEventHandler(new osgViewer::WindowSizeHandler);
	//添加路径记录 Z
	viewer->addEventHandler(new osgViewer::RecordCameraPathHandler);
	//帮助文档显示H
	viewer->addEventHandler(new osgViewer::HelpHandler);
	//截屏 C
	viewer->addEventHandler(new osgViewer::ScreenCaptureHandler);
	//视角追踪
	viewer->addEventHandler(new osgViewer::ThreadingHandler);
	//添加一些常用状态设置，响应W,S
	viewer->addEventHandler(new osgViewer::StatsHandler);

	//添加我的消息
	MyGUIEventHandler* labEvent = new MyGUIEventHandler();
	viewer->addEventHandler(labEvent);


	//添加hud
	root->addChild(createTextHUD());

	//初始化天空
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

	// ui布局
	osgQt::GraphicsWindowQt* gw = dynamic_cast<osgQt::GraphicsWindowQt*>(camera->getGraphicsContext());
	if (!gw)
	{
		QMessageBox::question(this, "提示", "gw==null", QMessageBox::Yes | QMessageBox::No);
	}
	QWidget* osg_widget = (QWidget*)(gw->getGLWidget());
	this->setCentralWidget(osg_widget);

	//QGridLayout* grid = new QGridLayout;
	//grid->addWidget(osg_widget);

	//ui.openGLWidget->setLayout(grid);  //要挂接的窗口


	//窗口最大化
	//this->setWindowState(Qt::WindowMaximized);
	//this->setWindowTitle(QString::fromLocal8Bit("数字地球"));

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
	camera->setRenderOrder(osg::Camera::POST_RENDER);  //最后渲染

	camera->setClearMask(GL_DEPTH_BUFFER_BIT);
	camera->setAllowEventFocus(false);  //不接受鼠标等事件
	camera->setReferenceFrame(osg::Transform::ABSOLUTE_RF); //不随父节点显示隐藏 
	camera->setProjectionMatrixAsOrtho2D(0, 1920, 0, 1080);

	osg::ref_ptr<osg::Geode> gnode = new osg::Geode;
	gnode->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF);//关闭光照
	osg::ref_ptr<osgText::Text> text = new osgText::Text;
	gnode->addDrawable(text);

	//text->setFont("Fonts/msyh.ttf");
	text->setCharacterSize(50);
	text->setText("hud");
	text->setPosition(osg::Vec3(0.0, 0.0, 0.0));

	osg::BoundingBox bx;
	bx.expandBy(text->getBound()); //文字的包围盒

	//添加纹理
	osg::ref_ptr<osg::Geometry> gm = new osg::Geometry;
	gnode->addDrawable(gm);



	camera->addChild(gnode);
	return camera.release();

}

