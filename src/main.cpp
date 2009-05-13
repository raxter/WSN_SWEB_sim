#include "gui/wsnsim.h"

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);

  WSN::GUI::WSNsim wsnsim;
  wsnsim.show();

  return app.exec();
}



