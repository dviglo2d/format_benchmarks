// Copyright (c) the Dviglo project
// License: MIT

#include "utils.hpp"

#include <pugixml.hpp>

#include <rapidjson/filewritestream.h>
#include <rapidjson/prettywriter.h>
#include <rapidjson/stringbuffer.h>

#include <ryml.hpp>
#include <ryml_std.hpp>
#include <c4/format.hpp>


std::string fnt_xml_to_json()
{
    namespace rj = rapidjson;

    /*const char* fnt_xml_src =
        //#include "fnt_xml.inl"
        #include "small_xml.inl"
        ;*/

    pugi::xml_document xml_doc;
    //xml_doc.load(fnt_xml_src);

    rj::Document json_doc;
    json_doc["test"] = "Тест";

    rj::StringBuffer buffer;
    rj::PrettyWriter<rj::StringBuffer> writer(buffer);
    json_doc.Accept(writer);
    
    return std::string(buffer.GetString());
}

void save_file(const rapidjson::Document& doc, const char* filename)
{
    namespace rj = rapidjson;

    static char buffer[65536];

    FILE* fp = fopen(filename, "wb");
    rj::FileWriteStream stream(fp, buffer, sizeof(buffer));
    rj::PrettyWriter<rapidjson::FileWriteStream> writer(stream);
    doc.Accept(writer);
    fclose(fp);
}

void save_file(const ryml::Tree& tree, const char* filename)
{
    namespace rj = rapidjson;

    FILE* fp = fopen(filename, "wb");
    ryml::emit_yaml(tree, tree.root_id(), fp);
    fclose(fp);
}
