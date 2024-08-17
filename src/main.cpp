// Copyright (c) the Dviglo project
// License: MIT

#include <benchmark/benchmark.h>
#include <pugixml.hpp>
#include <rapidjson/document.h>
#include <rapidjson/filewritestream.h>
#include <rapidjson/prettywriter.h>
#include <rapidjson/stringbuffer.h>


static void save_xml()
{
    const char* xml_src =
        "<window title='Окно'>"
        "    <controls>"
        "        <button text='Кнопка' />"
        "    </controls>"
        "</window>";

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
    namespace rj = rapidjson;

    const char* json_src =
        "{"
        "    \"window\":"
        "    {"
        "        \"title\":\"Окно\","
        "        \"controls\":"
        "        ["
        "            {"
        "                \"type\":\"button\","
        "                \"text\":\"Кнопка\""
        "            }"
        "        ]"
        "    }"
        "}";

    rj::Document doc;
    doc.Parse(json_src);

    FILE* fp = fopen("out.json", "wb");
    static char write_buffer[65536];
    rj::FileWriteStream os(fp, write_buffer, sizeof(write_buffer));
    rj::PrettyWriter<rapidjson::FileWriteStream> writer(os);
    doc.Accept(writer);
    fclose(fp);
}

static void bm_save_json(benchmark::State& state)
{
    for (auto _ : state)
        save_json();
}
BENCHMARK(bm_save_json);


BENCHMARK_MAIN();
