#ifndef SETTINGS_DATA_H_
#define SETTINGS_DATA_H_

#include <QColor>


class SettingsData {
 private:
  SettingsData() {}
  SettingsData(const SettingsData &s) = delete;
  SettingsData(const SettingsData &&s) = delete;
  SettingsData &operator=(const SettingsData &&s) = delete;
  SettingsData &operator=(const SettingsData &s) = delete;
  ~SettingsData() {}
  QColor background_color_;
  QColor lines_color_;
  QColor vert_color_;
  int type_of_lines_ = 0;
  int type_of_vertices_ = 0;
  int flag_proect_ = 0;
  float size_of_vertices_ = 0;
  float thickness_of_lines_ = 0;
  int index_size_vert_ = 0;
  int index_tik_lines_ = 0;

 public:
  static SettingsData *GetInstance() {
    static SettingsData getSetting_;
    return &getSetting_;
  }

  QColor GetBgdColor();
  QColor GetLinesColor();
  QColor GetVertColor();
  int GetTypeLines();
  int GetTypeVert();
  int GetFlagProect();
  float GetSizeVert();
  float GetThicknessLines();
  float GetSizeVertIndex();
  float GetThicknessLinesIndex();

  void SetBgdColor(QColor color);
  void SetLinesColor(QColor color);
  void SetVertColor(QColor color);
  void SetTypeLines(int index);
  void SetTypeVert(int index);
  void SetFlagProect(int index);
  void SetSizeVert(int index);
  void SetThicknessLines(int index);

  void DefaultAllSetting();
};


#endif  // !SETTINGS_DATA_H_
