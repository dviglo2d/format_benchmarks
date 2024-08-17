:: Меняем кодировку консоли на UTF-8
chcp 65001

:: Путь к git.exe
set "PATH=c:\program files\git\bin"

set "this_dir=%~dp0"
:: Удаляем обратный слэш в конце
set "this_dir=%this_dir:~0,-1%"

call :remove_submodule third_party/benchmark/repo
call :remove_submodule third_party/pugixml/repo
call :remove_submodule third_party/rapidjson/repo
call :remove_submodule third_party/rapidyaml/repo
call :remove_submodule third_party/yaml-cpp/repo
call :remove_submodule third_party/hjson-cpp/repo

goto :end

:: Функция удаляет подмодуль
:remove_submodule
set arg=%1
git -C "%this_dir%" submodule deinit -f %1
git -C "%this_dir%" rm -f %1
rmdir /s /q "%this_dir%/.git/modules/%1"
goto :eof

:end
:: Ждём нажатие Enter перед закрытием консоли
pause
