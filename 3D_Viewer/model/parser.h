/**
A class for parsing obj files.
All the data neccessary for 3D-rendering is written to a special structure
(ObjInfo).
Works only with the lines starting with 'v' (vertices) and 'f'
(facets). Doesn't support vn, vt, l, etc.
*/

#ifndef CPP4_3DVIEWER_V2_0_1_3D_VIEWER_MODEL_PARSER_H_
#define CPP4_3DVIEWER_V2_0_1_3D_VIEWER_MODEL_PARSER_H_

#include <cstdint>
#include <deque>
#include <string>
#include <vector>

namespace s21 {
typedef struct ObjInfo {
  uint32_t count_of_vertices;
  uint32_t count_of_facets;
  uint32_t count_of_indices;
  std::vector<float> vertices;
  std::vector<uint32_t> indices;
} ObjInfo;

class Parser {
 public:
  static Parser *GetInstance(std::string file_name);
  void FreeInstance();
  ObjInfo data;

 private:
  Parser();
  ~Parser();
  static void CountVerticesAndFacets(std::string file_name, ObjInfo *data);
  static uint32_t CountVerticesInFacet(std::string str);
  static void WriteVertices(std::string str, ObjInfo *data);
  static void GetFacetVertices(std::string str, std::deque<int> *sequence);
  static void WriteFacetVertices(std::deque<int> sequence, ObjInfo *data);
  static Parser *instance_;
};
}  // namespace s21

#endif  // CPP4_3DVIEWER_V2_0_1_3D_VIEWER_MODEL_PARSER_H_
