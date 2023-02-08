#ifndef PARSER_CC
#define PARSER_CC

#include <fstream>
#include <vector>

#include "affine_transformation.h"

class Model {
 public:
  void ParsingFile(const std::string &file_path);

  int GetNumberOfFacets() { return count_facets_; }
  int GetNumberOfVertexes() { return count_vertexes_; }

  void DeleteMMatrix() { return transforms_matrix_.DeleteMatrix(); }
  float *MatrixMToMass() { return transforms_matrix_.MatrixToMass(); }

  void MTranslate(double x, double y, double z) {
    transforms_matrix_.Translate(x, y, z);
  }
  void MScale(double x, double y, double z) {
    transforms_matrix_.Scale(x, y, z);
  }
  void MRotate(double x, double y, double z) {
    transforms_matrix_.Rotate(x, y, z);
  }

  std::vector<double> &GetArrVertexes() { return vertexes_; }
  std::vector<int> &GetArrFacets() { return facets_; }
  std::vector<double> &GetDrawVector() { return draw_vector_; }

 private:
  int count_vertexes_ = 0, count_facets_ = 0;
  std::vector<double> vertexes_, draw_vector_;
  std::vector<int> facets_, facets_local_;
  TransformMatrix transforms_matrix_;

  void Vertexes(std::string &line);
  void Facets(std::string &line);
  void DoubleCoordinates(int len);
  void DrawVector();
};

class IModelFactory {
 public:
  virtual Model *CreateModel() = 0;
};

class ModelFactory : public IModelFactory {
 public:
  Model *CreateModel() override { return new Model; }
};

#endif  // PARSER_CC
