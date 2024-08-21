// Copyright (c) the Dviglo project
// License: MIT

#pragma once

#include <rapidjson/document.h>
#include <ryml.hpp>

#include <string>

std::string urho3d_xml_to_json(const std::string& xml_src);
std::string fnt_xml_to_json(const std::string& xml_src);
std::string urho3d_xml_to_yml(const std::string& xml_src);

void save_file(const rapidjson::Document& doc, const char* filename);
void save_file(const ryml::Tree& tree, const char* filename);
