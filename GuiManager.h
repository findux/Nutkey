#ifndef GUIMANAGER_H
#define GUIMANAGER_H

#include <Adafruit_SSD1306.h>
#include "Keyboard.h"

class GuiManager {
private:
  int m_page;
  int m_maxPage;
  Adafruit_SSD1306* display;
public:
  GuiManager(Adafruit_SSD1306* tdisplay);

  void nextPage();
  void previousPage();
  void draw();
  void doit();
};

#endif