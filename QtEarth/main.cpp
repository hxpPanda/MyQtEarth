#include "myviewerwidget.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	std::string filepath = "D:/OSGcore/path/data/gdal_tiff.earth";
	MyViewerWidget w(filepath);
	w.show();
	return a.exec();
}
