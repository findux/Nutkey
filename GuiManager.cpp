#include "GuiManager.h"


GuiManager::GuiManager(Adafruit_SSD1306* tdisplay) {
  m_maxPage = 5;
  m_page = 1;
  display = tdisplay;
  this->draw();
}

void GuiManager::nextPage() {
  m_page++;
  if (m_page > m_maxPage)
    m_page = 0;
  this->draw();
}

void GuiManager::previousPage() {
  m_page--;
  if (m_page <= 0)
    m_page = m_maxPage;
  this->draw();
}

void GuiManager::draw() {
  display->clearDisplay();
  display->setTextColor(SSD1306_WHITE);
  display->setCursor(0, 0);
  display->print(m_page);
  display->println("- CustomKey");
  display->display();  // Show initial text
}

void GuiManager::doit() {
  Keyboard.print(m_page);
  Keyboard.println("-Deneme");
}
