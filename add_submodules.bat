:: Меняем кодировку консоли на UTF-8
chcp 65001

:: Путь к git.exe
set "PATH=c:\program files\git\bin"

set "this_dir=%~dp0"
:: Удаляем обратный слэш в конце
set "this_dir=%this_dir:~0,-1%"

set "sm_path=third_party/benchmark/repo"
git -C "%this_dir%" submodule add https://github.com/google/benchmark %sm_path%
git -C "%this_dir%" config -f .gitmodules submodule.%sm_path%.shallow true

set "sm_path=third_party/pugixml/repo"
git -C "%this_dir%" submodule add https://github.com/zeux/pugixml %sm_path%
git -C "%this_dir%" config -f .gitmodules submodule.%sm_path%.shallow true

set "sm_path=third_party/rapidjson/repo"
git -C "%this_dir%" submodule add https://github.com/Tencent/rapidjson %sm_path%
git -C "%this_dir%" config -f .gitmodules submodule.%sm_path%.shallow true

set "sm_path=third_party/rapidyaml/repo"
git -C "%this_dir%" submodule add https://github.com/biojppm/rapidyaml %sm_path%
git -C "%this_dir%" config -f .gitmodules submodule.%sm_path%.shallow true

set "sm_path=third_party/yaml-cpp/repo"
git -C "%this_dir%" submodule add https://github.com/jbeder/yaml-cpp %sm_path%
git -C "%this_dir%" config -f .gitmodules submodule.%sm_path%.shallow true

set "sm_path=third_party/hjson-cpp/repo"
git -C "%this_dir%" submodule add https://github.com/hjson/hjson-cpp %sm_path%
git -C "%this_dir%" config -f .gitmodules submodule.%sm_path%.shallow true

git -C "%this_dir%" submodule update --init --recursive

:: Ждём нажатие Enter перед закрытием консоли
pause
