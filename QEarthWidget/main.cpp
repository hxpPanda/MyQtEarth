#include "qearthwidget.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	/************************************************/
	osg::ArgumentParser arguments(&argc, argv);					// 命令行参数读取
	osgViewer::Viewer viewer(arguments);						// 视图
	//viewer.setThreadingModel(viewer.SingleThreaded);			// 渲染使用单线程模型
	viewer.setThreadingModel(osgViewer::Viewer::SingleThreaded);
	viewer.setRunFrameScheme(viewer.ON_DEMAND);					// 需要渲染时再进行渲染

	ViewerWidget* viewerWidget = new ViewerWidget(&viewer);		// Qt视图窗口
	QGLFormat format = viewerWidget->format();					// Qt的GL呈现上下文的格式
	format.setSamples(8);										// 设置GL呈现格式的采样率
	viewerWidget->setFormat(format);							// Qt视图窗口使用格式
	/************************************************/

	QEarthWidget w;
	w.setOsgWidget(viewerWidget);
	w.show();
	return a.exec();
}

