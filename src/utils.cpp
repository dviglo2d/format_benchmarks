// Copyright (c) the Dviglo project
// License: MIT

#include "utils.hpp"

#include "dviglo/fs/file_base.hpp"

#include <pugixml.hpp>

#include <rapidjson/filewritestream.h>
#include <rapidjson/prettywriter.h>
#include <rapidjson/stringbuffer.h>

#include <ryml.hpp>
#include <ryml_std.hpp>
#include <c4/format.hpp>

#include <iostream>

namespace rj = rapidjson;


// Нода <element> из urho3d.xml
static void convert_element_node(const pugi::xml_node src_node, rj::Value& out_member,
                                 rj::MemoryPoolAllocator<>& allocator)
{
    for (const pugi::xml_attribute src_attribute : src_node.attributes())
    {
        out_member.AddMember(rj::StringRef(src_attribute.name()),
                             rj::StringRef(src_attribute.value()),
                             allocator);
    }

    rj::Value out_attributes;
    out_attributes.SetObject();

    for (const pugi::xml_node child_node : src_node.children("attribute"))
    {
        out_attributes.AddMember(rj::StringRef(child_node.attribute("name").value()),
                                 rj::StringRef(child_node.attribute("value").value()),
                                 allocator);
    }

    if (out_attributes.MemberCount())
        out_member.AddMember("attributes", out_attributes, allocator);

    rj::Value out_elements;
    out_elements.SetArray();

    for (const pugi::xml_node child_node : src_node.children("element"))
    {
         rj::Value element;
         element.SetObject();
         convert_element_node(child_node, element, allocator);
         out_elements.PushBack(element, allocator);
    }

    if (out_elements.Size())
        out_member.AddMember("elements", out_elements, allocator);
}

// Нода <font> из fnt.xml
static void convert_font_node(const pugi::xml_node src_node, rj::Document& out_doc)
{
    pugi::xml_node src_info = src_node.child("info");
    rj::Value out_info;
    out_info.SetObject();

    for (const pugi::xml_attribute src_attribute : src_info.attributes())
    {
        out_info.AddMember(rj::StringRef(src_attribute.name()),
                           rj::StringRef(src_attribute.value()),
                           out_doc.GetAllocator());
    }

    out_doc.AddMember("info", out_info, out_doc.GetAllocator());

    // ----------------------------------------------------------------------------

    pugi::xml_node src_chars = src_node.child("chars");
    rj::Value out_chars;
    out_chars.SetArray();

    for (const pugi::xml_node src_char : src_chars)
    {
        rj::Value out_char;
        out_char.SetObject();

        for (const pugi::xml_attribute src_attribute : src_char.attributes())
        {
            out_char.AddMember(rj::StringRef(src_attribute.name()),
                               rj::StringRef(src_attribute.value()),
                               out_doc.GetAllocator());
        }

        out_chars.PushBack(out_char, out_doc.GetAllocator());
    }

    out_doc.AddMember("chars", out_chars, out_doc.GetAllocator());

    // ----------------------------------------------------------------------------

    pugi::xml_node src_kernings = src_node.child("kernings");
    rj::Value out_kernings;
    out_kernings.SetArray();

    for (const pugi::xml_node src_kerning : src_kernings)
    {
        rj::Value out_kerning;
        out_kerning.SetObject();

        for (const pugi::xml_attribute src_attribute : src_kerning.attributes())
        {
            out_kerning.AddMember(rj::StringRef(src_attribute.name()),
                                  rj::StringRef(src_attribute.value()),
                                  out_doc.GetAllocator());
        }

        out_kernings.PushBack(out_kerning, out_doc.GetAllocator());
    }

    out_doc.AddMember("kernings", out_kernings, out_doc.GetAllocator());

    // ----------------------------------------------------------------------------

    pugi::xml_node src_common = src_node.child("common");
    rj::Value out_common;
    out_common.SetObject();

    for (const pugi::xml_attribute src_attribute : src_common.attributes())
    {
        out_common.AddMember(rj::StringRef(src_attribute.name()),
                             rj::StringRef(src_attribute.value()),
                             out_doc.GetAllocator());
    }

    out_doc.AddMember("common", out_common, out_doc.GetAllocator());

    // ----------------------------------------------------------------------------

    pugi::xml_node src_pages = src_node.child("pages");
    rj::Value out_pages;
    out_pages.SetArray();

    for (const pugi::xml_node src_page : src_pages)
    {
        rj::Value out_page;
        out_page.SetObject();

        for (const pugi::xml_attribute src_attribute : src_page.attributes())
        {
            out_page.AddMember(rj::StringRef(src_attribute.name()),
                               rj::StringRef(src_attribute.value()),
                               out_doc.GetAllocator());
        }

        out_pages.PushBack(out_page, out_doc.GetAllocator());
    }

    out_doc.AddMember("pages", out_pages, out_doc.GetAllocator());
}

std::string urho3d_xml_to_json(const std::string& xml_src)
{
    pugi::xml_document src_doc;
    src_doc.load(xml_src.c_str());
    const std::string node_name = src_doc.document_element().name();
    assert(node_name == "element");

    rj::Document out_doc;
    out_doc.SetObject();
    convert_element_node(src_doc.document_element(), out_doc, out_doc.GetAllocator());

    rj::StringBuffer buffer;
    rj::PrettyWriter<rj::StringBuffer> writer(buffer);
    out_doc.Accept(writer);

    return std::string(buffer.GetString());
}

std::string fnt_xml_to_json(const std::string& xml_src)
{
    pugi::xml_document src_doc;
    src_doc.load(xml_src.c_str());
    const std::string node_name = src_doc.document_element().name();
    assert(node_name == "font");

    rj::Document out_doc;
    out_doc.SetObject();
    convert_font_node(src_doc.document_element(), out_doc);

    rj::StringBuffer buffer;
    rj::PrettyWriter<rj::StringBuffer> writer(buffer);
    out_doc.Accept(writer);

    return std::string(buffer.GetString());
}

void save_file(const rj::Document& doc, const char* filename)
{
    static char buffer[65536];

    FILE* fp = dviglo::file_open(filename, "wb");
    rj::FileWriteStream stream(fp, buffer, sizeof(buffer));
    rj::PrettyWriter<rj::FileWriteStream> writer(stream);
    doc.Accept(writer);
    dviglo::file_close(fp);
}

void save_file(const ryml::Tree& tree, const char* filename)
{
    FILE* fp = dviglo::file_open(filename, "wb");
    ryml::emit_yaml(tree, tree.root_id(), fp);
    dviglo::file_close(fp);
}
