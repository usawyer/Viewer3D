#include "model.h"

void Model::ParsingFile(const std::string &file_path) {
  std::ifstream file(file_path);
  std::string line;
  count_facets_ = 0;
  count_vertexes_ = 0;
  if (!vertexes_.empty()) vertexes_.clear();
  if (!facets_.empty()) facets_.clear();
  if (file.is_open()) {
    while (std::getline(file, line)) {
      Vertexes(line);
      Facets(line);
    }
  }
  DrawVector();
  file.close();
}

void Model::Facets(std::string &line) {
  facets_local_.clear();
  if (line[0] == 'f' && line[1] == ' ') {
    int len = 0;
    line.erase(0, 2);
    for (auto i = 0; i < line.length(); i++) {
      std::string::size_type size = 0;
      if (isdigit(line[i])) {
        facets_local_.push_back(std::stoi(line, &size) - 1);
        count_facets_++;
        line.erase(0, size);
        i = -1;
        len++;
      } else if (line[0] == '/') {
        line.erase(0, line.find_first_of(' '));
        i = -1;
      }
    }
    DoubleCoordinates(len);
  }
}

void Model::Vertexes(std::string &line) {
  if (line[0] == 'v' && line[1] == ' ') {
    count_vertexes_++;
    line.erase(0, 2);
    for (auto i = 0; i < line.length(); i++) {
      std::string::size_type size = 0;
      if (isdigit(line[i])) {
        vertexes_.push_back(std::stod(line, &size));
        line.erase(0, size);
      }
    }
  }
}

void Model::DoubleCoordinates(int len) {
  int first_was = 0, first_elem = 0;
  for (auto i = facets_local_.begin(); i <= facets_local_.end(); i++) {
    if (!first_was) {
      first_elem = *(i);
      facets_.push_back(*(i));
      first_was++;
    } else if (first_was < len) {
      facets_.push_back(*(i));
      facets_.push_back(*(i));
      first_was++;
    } else {
      facets_.push_back(first_elem);
      first_was = 0;
    }
  }
}

void Model::DrawVector() {
  draw_vector_.clear();
  for (auto &i : facets_) {
    draw_vector_.push_back(vertexes_.at(i * 3));
    draw_vector_.push_back(vertexes_.at(i * 3 + 1));
    draw_vector_.push_back(vertexes_.at(i * 3 + 2));
  }
}
