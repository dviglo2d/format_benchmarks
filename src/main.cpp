// Copyright (c) the Dviglo project
// License: MIT

#include <benchmark/benchmark.h>

#include <pugixml.hpp>

#include <rapidjson/document.h>
#include <rapidjson/filewritestream.h>
#include <rapidjson/prettywriter.h>
#include <rapidjson/stringbuffer.h>

#include <ryml.hpp>
#include <ryml_std.hpp>
#include <c4/format.hpp>


static void save_file(const rapidjson::Document& doc, const char* filename)
{
    namespace rj = rapidjson;

    static char buffer[65536];

    FILE* fp = fopen(filename, "wb");
    rj::FileWriteStream stream(fp, buffer, sizeof(buffer));
    rj::PrettyWriter<rapidjson::FileWriteStream> writer(stream);
    doc.Accept(writer);
    fclose(fp);
}

static void save_file(const ryml::Tree& tree, const char* filename)
{
    namespace rj = rapidjson;

    FILE* fp = fopen(filename, "wb");
    ryml::emit_yaml(tree, tree.root_id(), fp);
    fclose(fp);
}


static void save_xml()
{
    const char* xml_src =
        #include "xml_1.inl"
        ;

    pugi::xml_document doc;
    doc.load(xml_src);
    doc.save_file("out.xml");
}

static void bm_save_xml(benchmark::State& state)
{
    for (auto _ : state)
        save_xml();
}
BENCHMARK(bm_save_xml);


static void save_json()
{
    const char* json_src =
        #include "json_1.inl"
        ;

    rapidjson::Document doc;
    doc.Parse(json_src);
    save_file(doc, "out.json");
}

static void bm_save_json(benchmark::State& state)
{
    for (auto _ : state)
        save_json();
}
BENCHMARK(bm_save_json);


static void save_yml()
{
    static const ryml::csubstr yml_src =
        #include "yml_1.inl"
        ;

    ryml::Tree tree = ryml::parse_in_arena(yml_src);
    save_file(tree, "out.yml");
}

static void bm_save_yml(benchmark::State& state)
{
    for (auto _ : state)
        save_yml();
}
BENCHMARK(bm_save_yml);


BENCHMARK_MAIN();
