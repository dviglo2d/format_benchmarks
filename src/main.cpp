// Copyright (c) the Dviglo project
// License: MIT

#include "utils.hpp"

#include "dviglo/fs/file.hpp"
#include "dviglo/fs/fs_base.hpp"

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

// --------------------------------------------------------------------------

static const std::string base_path = dviglo::get_base_path();
static const std::string small_xml_src = dviglo::read_all_text(base_path + "data/small.xml");
static const std::string small_json_src = dviglo::read_all_text(base_path + "data/small.json");
static const std::string small_yml_src = dviglo::read_all_text(base_path + "data/small.yml");
static const std::string medium_xml_src = dviglo::read_all_text(base_path + "data/urho3d.xml");
static const std::string big_xml_src = dviglo::read_all_text(base_path + "data/fnt.xml");

//std::string fnt_json = fnt_xml_to_json();

// --------------------------------------------------------------------------

static void save_pugixml_small()
{
    static const std::string file_path = base_path + "pugixml_small.xml";

    pugi::xml_document doc;
    doc.load(small_xml_src.c_str());
    doc.save_file(file_path.c_str());
}

static void bm_save_pugixml_small(benchmark::State& state)
{
    for (auto _ : state)
        save_pugixml_small();
}
BENCHMARK(bm_save_pugixml_small);

// --------------------------------------------------------------------------

static void save_pugixml_medium()
{
    static const std::string file_path = base_path + "pugixml_medium.xml";

    pugi::xml_document doc;
    doc.load(medium_xml_src.c_str());
    doc.save_file(file_path.c_str());
}

static void bm_save_pugixml_medium(benchmark::State& state)
{
    for (auto _ : state)
        save_pugixml_medium();
}
BENCHMARK(bm_save_pugixml_medium);

// --------------------------------------------------------------------------


static void save_pugixml_big()
{
    static const std::string file_path = base_path + "pugixml_big.xml";

    pugi::xml_document doc;
    doc.load(big_xml_src.c_str());
    doc.save_file(file_path.c_str());
}

static void bm_save_pugixml_big(benchmark::State& state)
{
    for (auto _ : state)
        save_pugixml_big();
}
BENCHMARK(bm_save_pugixml_big);

// --------------------------------------------------------------------------

static void save_rapidjson_small()
{
    static const std::string file_path = base_path + "rapidjson_small.json";

    rapidjson::Document doc;
    doc.Parse(small_json_src.c_str());
    save_file(doc, file_path.c_str());
}

static void bm_save_rapidjson_small(benchmark::State& state)
{
    for (auto _ : state)
        save_rapidjson_small();
}
BENCHMARK(bm_save_rapidjson_small);

// --------------------------------------------------------------------------

static void save_rapidyaml_small()
{
    static const std::string file_path = base_path + "rapidyaml_small.yml";
    static const ryml::csubstr yml_src(small_yml_src.c_str());

    ryml::Tree tree = ryml::parse_in_arena(yml_src);
    save_file(tree, file_path.c_str());
}

static void bm_save_rapidyaml_small(benchmark::State& state)
{
    for (auto _ : state)
        save_rapidyaml_small();
}
BENCHMARK(bm_save_rapidyaml_small);

// --------------------------------------------------------------------------

static void save_yaml_cpp_small()
{
    static const std::string file_path = base_path + "yml-cpp_small.yml";

    YAML::Node doc = YAML::Load(small_yml_src);
    std::ofstream fout(file_path);
    fout << doc;
}

static void bm_save_yaml_cpp_small(benchmark::State& state)
{
    for (auto _ : state)
        save_yaml_cpp_small();
}
BENCHMARK(bm_save_yaml_cpp_small);

// --------------------------------------------------------------------------

BENCHMARK_MAIN();
