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

#include <yaml-cpp/yaml.h>

#include <fstream>


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


static void save_pugixml()
{
    const char* xml_src =
        #include "xml_1.inl"
        ;

    pugi::xml_document doc;
    doc.load(xml_src);
    doc.save_file("pugixml.xml");
}

static void bm_save_pugixml(benchmark::State& state)
{
    for (auto _ : state)
        save_pugixml();
}
BENCHMARK(bm_save_pugixml);


static void save_rapidjson()
{
    const char* json_src =
        #include "json_1.inl"
        ;

    rapidjson::Document doc;
    doc.Parse(json_src);
    save_file(doc, "rapidjson.json");
}

static void bm_save_rapidjson(benchmark::State& state)
{
    for (auto _ : state)
        save_rapidjson();
}
BENCHMARK(bm_save_rapidjson);


static void save_rapidyaml()
{
    static const ryml::csubstr yml_src =
        #include "yml_1.inl"
        ;

    ryml::Tree tree = ryml::parse_in_arena(yml_src);
    save_file(tree, "rapidyaml.yml");
}

static void bm_save_rapidyaml(benchmark::State& state)
{
    for (auto _ : state)
        save_rapidyaml();
}
BENCHMARK(bm_save_rapidyaml);


static void save_yaml_cpp()
{
    const char* yml_src =
#include "yml_1.inl"
        ;

    YAML::Node doc = YAML::Load(yml_src);
    std::ofstream fout("yml-cpp.yml");
    fout << doc;
}

static void bm_save_yaml_cpp(benchmark::State& state)
{
    for (auto _ : state)
        save_yaml_cpp();
}
BENCHMARK(bm_save_yaml_cpp);


BENCHMARK_MAIN();
