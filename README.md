# csv_calculate
Задан CSV-файл (comma-separated values) с заголовком, в котором перечислены названия столбцов. Строки нумеруются целыми положительными числами, необязательно в порядке возрастания. В ячейках CSV-файла могут хранится или целые числа или выражения вида
= ARG1 OP ARG2
где ARG1 и ARG2 – целые числа или адреса ячеек в формате Имя_колонки Номер_строки, а OP – арифметическая операция из списка: +, -, *, /. 
Программа, читает произвольную CSV-форму из файла (количество строк и столбцов может быть любым), вычисляет значения ячеек, если это необходимо, и выводит получившуюся табличку в виде CSV-представления в консоль.

Иструкция по запуску:
Скомпилировать программу можно при помощи команды g++ -o read read_csv.cpp.
Запуск программы на данных из файла с помощью команды ./read some_file.csv
Также можно запустить скрипт с небольшой презентацией с помощью команды ./present.bash
