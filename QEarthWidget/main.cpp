#include "qearthwidget.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	/************************************************/
	osg::ArgumentParser arguments(&argc, argv);					// �����в�����ȡ
	osgViewer::Viewer viewer(arguments);						// ��ͼ
	//viewer.setThreadingModel(viewer.SingleThreaded);			// ��Ⱦʹ�õ��߳�ģ��
	viewer.setThreadingModel(osgViewer::Viewer::SingleThreaded);
	viewer.setRunFrameScheme(viewer.ON_DEMAND);					// ��Ҫ��Ⱦʱ�ٽ�����Ⱦ

	ViewerWidget* viewerWidget = new ViewerWidget(&viewer);		// Qt��ͼ����
	QGLFormat format = viewerWidget->format();					// Qt��GL���������ĵĸ�ʽ
	format.setSamples(8);										// ����GL���ָ�ʽ�Ĳ�����
	viewerWidget->setFormat(format);							// Qt��ͼ����ʹ�ø�ʽ
	/************************************************/

	QEarthWidget w;
	w.setOsgWidget(viewerWidget);
	w.show();
	return a.exec();
}

