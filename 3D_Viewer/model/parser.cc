#include "parser.h"

#include <cstdint>
#include <deque>
#include <fstream>
#include <stdexcept>
#include <string>
#include <vector>

namespace s21 {
/// @brief Counts amount of vertices and facets in the file
/// @param file_name obj file with vertices and facets
/// @param data ObjInfo structure with information for 3D rendering
void Parser::CountVerticesAndFacets(std::string file_name, ObjInfo *data) {
  std::ifstream input(file_name);
  std::string str = "";
  while (std::getline(input, str)) {
    if (str[0] == 'f') {
      ++data->count_of_facets;
      data->count_of_indices += CountVerticesInFacet(str) * 2;
    }
    if (str[0] == 'v' && str[1] == ' ') data->count_of_vertices += 3;
  }
  input.close();
}

/// @brief Counts the amount of vertices in a given facet
/// @param str 'f' line from obj file
/// @return the amount of vertices in a given facet
uint32_t Parser::CountVerticesInFacet(std::string str) {
  uint32_t result = 0;
  for (size_t i = 0; i <= str.size(); ++i) {
    if (str[i] >= '0' && str[i] <= '9') {
      if ((str[i - 1] == ' ') || ((str[i - 1] == '-') && (str[i - 2] == ' '))) {
        ++result;
      }
    }
  }
  return result;
}

/// @brief Writes float values of vertices to ObjInfo structure
/// @param str 'v' line from obj file
/// @param data ObjInfo structure with information for 3D rendering
void Parser::WriteVertices(std::string str, ObjInfo *data) {
  uint32_t count = 0;
  std::string number = "";
  for (size_t i = 0; i < str.size(); ++i) {
    while (count < 3) {
      if (str[i] == ' ') ++i;
      if (i == str.size()) break;
      if (isdigit(str[i]) || (str[i] == '-') || (str[i] == '.')) {
        while (i < str.size() && str[i] != ' ') {
          number.push_back(str[i]);
          ++i;
        }
        data->vertices.push_back(std::stof(number));
        number.clear();
        ++i;
      }
      ++count;
    }
  }
}

/// @brief Writes the sequence of vertices' numbers which form a facet
/// @param str 'f' line from obj file
/// @param sequence initial sequence of vertices in a facet
void Parser::GetFacetVertices(std::string str, std::deque<int> *sequence) {
  std::string number = "";
  uint32_t slash = 0;
  for (size_t i = 0; i < str.size(); ++i) {
    if (str[i] == ' ') ++i;
    if (isdigit(str[i])) {
      while (i < str.size() && str[i] != ' ') {
        if (str[i] == '/') {
          ++i;
          ++slash;
        }
        if (slash == 0) number.push_back(str[i]);
        ++i;
      }
      sequence->push_back(stoi(number));
    }
    number.clear();
    slash = 0;
  }
}

/// @brief Writes vertices of a facet in the form needed for 3D-rendering
/// @param sequence initial sequence
/// @param data ObjInfo structure with information for 3D rendering
void Parser::WriteFacetVertices(std::deque<int> sequence, ObjInfo *data) {
  uint32_t total = sequence.size() * 2, count = 0, first_num = 0, last_num = 0;
  while (count < total - 1) {
    if (count == 0) {
      data->indices.push_back(sequence[0] - 1);
      first_num = sequence[0];
      sequence.pop_front();
    } else if (count % 2 != 0) {
      data->indices.push_back(sequence[0] - 1);
      last_num = sequence[0];
      sequence.pop_front();
    } else {
      data->indices.push_back(last_num - 1);
    }
    ++count;
  }
  data->indices.push_back(first_num - 1);
}

/// @brief Initialization of the Parser instance
Parser *Parser::instance_ = NULL;

/// @brief Private constructor creates single object of Parser
Parser::Parser() {
  data = {.count_of_vertices = 0,
          .count_of_facets = 0,
          .count_of_indices = 0,
          .vertices = std::vector<float>(),
          .indices = std::vector<uint32_t>()};
}

/// @brief Destructor
Parser::~Parser() {}

/// @brief Frees the single object of Parser
void Parser::FreeInstance() {
  if (instance_) {
    delete this;
    instance_ = NULL;
  }
}

/// @brief Extracts all the data neccessary for 3D-rendering from obj file and
/// writes it to ObjInfo structure
/// @param file_name path to obj file with vertices and facets
Parser *Parser::GetInstance(std::string file_name) {
  std::ifstream input(file_name);
  if (input) {
    if (!instance_) instance_ = new Parser();
    CountVerticesAndFacets(file_name, &instance_->data);
    std::string str = "";
    while (std::getline(input, str)) {
      if (str[0] == 'f') {
        std::deque<int> seq;
        str = str.substr(2, str.length());
        GetFacetVertices(str, &seq);
        WriteFacetVertices(seq, &instance_->data);
      }
      if (str[0] == 'v' && str[1] == ' ') {
        str = str.substr(2, str.length());
        WriteVertices(str, &instance_->data);
      }
    }
    input.close();
  } else {
    throw std::invalid_argument("No such file.\n");
  }
  return instance_;
}
}  // namespace s21
