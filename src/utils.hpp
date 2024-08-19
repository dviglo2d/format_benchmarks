// Copyright (c) the Dviglo project
// License: MIT

#pragma once

#include <rapidjson/document.h>
#include <ryml.hpp>

#include <string>


// Создаёт тестовый json из fnt_xml.inl
std::string fnt_xml_to_json();

void save_file(const rapidjson::Document& doc, const char* filename);
void save_file(const ryml::Tree& tree, const char* filename);
