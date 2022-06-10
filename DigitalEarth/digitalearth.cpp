#include "digitalearth.h"
#include <osg/TexGen>
DigitalEarth::DigitalEarth(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	InitOSG();
	InitOsgearth();
	InitUI();
	InitTimer();
}
DigitalEarth::~DigitalEarth()
{
}
void DigitalEarth::InitOSG()// 初始化设置osg
{
	viewer = new osgViewer::Viewer;
	// 设置模型
	root = new osg::Group;
	// 显示 .earth 文件中的地球模型
	earthNode = new osg::Node;
	QString earthFilePath = "D:/OSGcore/path/data/gdal_tiff.earth";
	earthNode = osgDB::readNodeFile(earthFilePath.toStdString());

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
	camera = new osg::Camera;
	camera->setGraphicsContext(new osgQt::GraphicsWindowQt(traits.get()));
	camera->setClearColor(osg::Vec4(0.2, 0.2, 0.6, 1.0));
	camera->setViewport(new osg::Viewport(0, 0, width, height));
	camera->setProjectionMatrixAsPerspective(30.0f, (double(traits->width)) / (double(traits->height)), 1.0f, 10000.0f);

	//设置渲染器
	viewer->setCamera(camera);
	viewer->setSceneData(root);
	viewer->setThreadingModel(osgViewer::Viewer::SingleThreaded);//创建为单线程
	viewer->addEventHandler(new osgGA::StateSetManipulator(viewer->getCamera()->getOrCreateStateSet()));
}
void DigitalEarth::InitOsgearth()
{
	//mapnode初始化
	mapNode = osgEarth::MapNode::findMapNode(earthNode.get());
	earthForm = new osg::MatrixTransform;
	//osgearth操作器
	em = new osgEarth::Util::EarthManipulator;
	if (mapNode.valid())
	{
		em->setNode(mapNode);
	}

	em->getSettings()->setArcViewpointTransitions(true);
	viewer->setCameraManipulator(em);

	//获取地球半径 设置视点
	double earth_R = mapNode->getMap()->getSRS()->getEllipsoid()->getRadiusEquator();
	const char* viewPointName = QString::fromLocal8Bit("北京").toStdString().c_str();
	em->setViewpoint(osgEarth::Viewpoint(viewPointName, 112.44, 33.75, 0.0, 0.0, -90.0, 5 * earth_R), 5);
	//初始化天空
	InitSky();
}
void DigitalEarth::InitSky()
{
	//获取当前时间 初始化天空
	now_time = time(0);
	t_tm = localtime(&now_time);
	osgEarth::DateTime cur_date_time(now_time);
	osgEarth::Util::Ephemeris* ephemeris = new osgEarth::Util::Ephemeris;

	//设置黑夜明暗程度
	osgEarth::Util::SkyOptions skyOptions;
	skyOptions.ambient() = 0.3;

	m_pSkyNode = osgEarth::Util::SkyNode::create(skyOptions, mapNode);
	m_pSkyNode->setName("SkyNode");
	m_pSkyNode->setEphemeris(ephemeris);
	m_pSkyNode->setDateTime(cur_date_time);
	viewer->setLightingMode(osg::View::SKY_LIGHT);
	m_pSkyNode->attach(viewer, 0);
	m_pSkyNode->setLighting(true);

	m_pSkyNode->addChild(mapNode);
	root->addChild(m_pSkyNode);

}
void DigitalEarth::InitUI()//界面初始化
{
	// ui布局
	osgQt::GraphicsWindowQt* gw = dynamic_cast<osgQt::GraphicsWindowQt*>(camera->getGraphicsContext());
	QWidget* osg_widget = (QWidget*)(gw->getGLWidget());
	this->setCentralWidget(osg_widget);
	//窗口最大化
	this->setWindowState(Qt::WindowMaximized);
	this->setWindowTitle(QString::fromLocal8Bit("数字地球"));
}
void DigitalEarth::InitTimer()//屏幕刷新初始化
{
	_timer = new QTimer;
	QObject::connect(_timer, SIGNAL(timeout()), this, SLOT(updateFrame()));
	_timer->start(10);

}
void DigitalEarth::updateFrame()
{

	viewer->frame();
}
