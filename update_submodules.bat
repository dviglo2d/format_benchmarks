:: Меняем кодировку консоли на UTF-8
chcp 65001

:: Путь к git.exe
set "PATH=c:\program files\git\bin"

set "this_dir=%~dp0"
:: Удаляем обратный слэш в конце
set "this_dir=%this_dir:~0,-1%"

git -C "%this_dir%" submodule update --remote --recursive

:: Ждём нажатие Enter перед закрытием консоли
pause
