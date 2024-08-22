Скачивание репозитория:

```
git clone --recurse-submodules https://github.com/dviglo2d/format_benchmarks repo
```

Результаты релизной сборки VS:

```
-------------------------------------------------------------------
Benchmark                         Time             CPU   Iterations
-------------------------------------------------------------------
bm_save_pugixml_small        177131 ns       150663 ns         4978
bm_save_rapidjson_small      175477 ns       141941 ns         4073
bm_save_rapidyaml_small      181537 ns       167411 ns         4480
bm_save_yaml_cpp_small       329001 ns       299944 ns         2240
bm_save_pugixml_medium      4691376 ns       767299 ns          896
bm_save_rapidjson_medium    6866639 ns       927734 ns          640
bm_save_rapidyaml_medium    7736834 ns      1196289 ns          640
bm_save_yaml_cpp_medium    13805927 ns     12276786 ns           56
bm_save_pugixml_big         9421807 ns      1981027 ns          560
bm_save_rapidjson_big       9404535 ns      5000000 ns          100
bm_save_rapidyaml_big      16121026 ns     11935764 ns           72
bm_save_yaml_cpp_big      163307625 ns    164062500 ns            4
```

Результаты отладочной версии VS:

```
-------------------------------------------------------------------
Benchmark                         Time             CPU   Iterations
-------------------------------------------------------------------
bm_save_pugixml_small        214472 ns       192540 ns         3733
bm_save_rapidjson_small      267970 ns       240626 ns         2987
bm_save_rapidyaml_small      348417 ns       320159 ns         2489
bm_save_yaml_cpp_small      1182319 ns      1171352 ns          747
bm_save_pugixml_medium      8255148 ns      1245117 ns          640
bm_save_rapidjson_medium    8216763 ns      2635542 ns          249
bm_save_rapidyaml_medium   11073571 ns      6696429 ns          112
bm_save_yaml_cpp_medium   101127933 ns    101562500 ns            6
bm_save_pugixml_big        14468017 ns      5625000 ns          100
bm_save_rapidjson_big      25592268 ns     25669643 ns           28
bm_save_rapidyaml_big      77540811 ns     78125000 ns            9
bm_save_yaml_cpp_big     1540433200 ns   1531250000 ns            1
```
