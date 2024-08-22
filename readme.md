Скачивание репозитория:

```
git clone --recurse-submodules https://github.com/dviglo2d/format_benchmarks repo
```

Результаты релизной сборки VS:

```
-------------------------------------------------------------------
Benchmark                         Time             CPU   Iterations
-------------------------------------------------------------------
bm_save_pugixml_small        168476 ns       139509 ns         4480
bm_save_rapidjson_small      224730 ns       161133 ns         6400
bm_save_hjson_small          343848 ns       344572 ns         2358
bm_save_rapidyaml_small      180093 ns       159040 ns         5600
bm_save_yaml_cpp_small       370114 ns       332714 ns         2489
bm_save_pugixml_medium      3857310 ns       627510 ns          747
bm_save_rapidjson_medium    3535747 ns       732422 ns          896
bm_save_hjson_medium       14247624 ns      6944444 ns           90
bm_save_rapidyaml_medium    7644702 ns      1129518 ns          498
bm_save_yaml_cpp_medium    14635736 ns     13437500 ns           50
bm_save_pugixml_big         9470200 ns      2090301 ns          299
bm_save_rapidjson_big       9377747 ns      4404362 ns          149
bm_save_hjson_big         150362260 ns    153125000 ns            5
bm_save_rapidyaml_big      16498531 ns     11501736 ns           72
bm_save_yaml_cpp_big      164229225 ns    164062500 ns            4
```

Результаты отладочной версии VS:

```
-------------------------------------------------------------------
Benchmark                         Time             CPU   Iterations
-------------------------------------------------------------------
bm_save_pugixml_small        204827 ns       179983 ns         3733
bm_save_rapidjson_small      291442 ns       249023 ns         3200
bm_save_hjson_small         1063385 ns      1060268 ns          560
bm_save_rapidyaml_small      361767 ns       288771 ns         2489
bm_save_yaml_cpp_small      1150689 ns      1024933 ns          747
bm_save_pugixml_medium      8566195 ns      1066767 ns          498
bm_save_rapidjson_medium    8481710 ns      2544981 ns          264
bm_save_hjson_medium      128250620 ns    128125000 ns            5
bm_save_rapidyaml_medium   11087648 ns      6063433 ns          134
bm_save_yaml_cpp_medium    98411571 ns    100446429 ns            7
bm_save_pugixml_big        14479380 ns      6777108 ns          166
bm_save_rapidjson_big      25713207 ns     25669643 ns           28
bm_save_hjson_big        1926832000 ns   1921875000 ns            1
bm_save_rapidyaml_big      75254611 ns     74652778 ns            9
bm_save_yaml_cpp_big     1555345700 ns   1562500000 ns            1
```
