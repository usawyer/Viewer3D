#include "settings_data.h"

QColor SettingsData::GetBgdColor() { return background_color_; }
QColor SettingsData::GetLinesColor() { return lines_color_; }
QColor SettingsData::GetVertColor() { return vert_color_; }

int SettingsData::GetTypeLines() { return type_of_lines_; }
int SettingsData::GetTypeVert() { return type_of_vertices_; }
int SettingsData::GetFlagProect() { return flag_proect_; }

float SettingsData::GetSizeVertIndex() { return index_size_vert_; }
float SettingsData::GetSizeVert() { return size_of_vertices_; }
float SettingsData::GetThicknessLinesIndex() { return index_tik_lines_; }
float SettingsData::GetThicknessLines() { return thickness_of_lines_; }

void SettingsData::SetBgdColor(QColor color) { background_color_ = color; }
void SettingsData::SetLinesColor(QColor color) { lines_color_ = color; }
void SettingsData::SetVertColor(QColor color) { vert_color_ = color; }

void SettingsData::SetTypeLines(int index) { type_of_lines_ = index; }
void SettingsData::SetTypeVert(int index) { type_of_vertices_ = index; }
void SettingsData::SetFlagProect(int index) { flag_proect_ = index; }

void SettingsData::SetSizeVert(int index) {
  index_size_vert_ = index;
  if (!index) {
    size_of_vertices_ = 3.0;
  } else if (index == 1) {
    size_of_vertices_ = 5.0;
  } else if (index == 2) {
    size_of_vertices_ = 7.0;
  }
}

void SettingsData::SetThicknessLines(int index) {
  index_tik_lines_ = index;
  if (!index) {
    thickness_of_lines_ = 1.0;
  } else if (index == 1) {
    thickness_of_lines_ = 2.0;
  } else if (index == 2) {
    thickness_of_lines_ = 3.0;
  }
}

void SettingsData::DefaultAllSetting() {
  background_color_.setRgbF(1.0, 1.0, 1.0);
  lines_color_.setRgbF(0.0, 0.0, 0.0);
  vert_color_.setRgbF(0.0, 0.0, 0.0);
  type_of_lines_ = 0;
  type_of_vertices_ = 0;
  flag_proect_ = 0;
  size_of_vertices_ = 0;
  thickness_of_lines_ = 0;
  index_size_vert_ = 0;
  index_tik_lines_ = 0;
}
