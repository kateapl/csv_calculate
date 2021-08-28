#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <cctype>
#include <string>
using namespace std;

vector<string> parser(string value){//получаем оба аргумента и знак
    string arg1 = "";
    string arg2 = "";
    string sign = "";
    string plus = "+";
    string minus = "-";
    string division = "/";
    string mul = "*";
    vector<string> expression;
    int pos;
    if(value.find('+') != -1){
        pos = value.find('+');
        sign = "+";
    }
    if(value.find('-')!= -1){
        pos = value.find('-');
        sign = "-";
    }
    if(value.find('*')!= -1){
        pos = value.find('*');
        sign = "*";
    }
    if(value.find('/')!= -1){
        pos = value.find('/');
        sign = "/";
    }

    for (int i = 0; i < pos; i++){//получаем первый аргумент
        arg1 += value[i];
    }
    for (int i = pos+1; i < value.size(); i++){//получаем второй аргумент
        arg2 += value[i];
    }

    expression.push_back(arg1);
    expression.push_back(sign);
    expression.push_back(arg2);

    return expression;
}

vector<string> parse_coordinate(string value){//находим слово и число координаты
    string word = "";
    string number = "";
    for (int i = 0; i < value.length(); i++){
        if(isalpha(value[i])){
            word += value[i];
        }
        if (isdigit(value[i]) ) {
            number += value[i];
        }

    }
    vector<string> expression;
    expression.push_back(word);
    expression.push_back(number);
    return expression;
}

int get_coordinate(string coordinate, vector <string>& array){//находим индекс координаты
    for (int j = 0; j < array.size(); j++){
        if(coordinate==array[j]){
            return j;
        }
    }
    return -1;
}

string extract(string value, vector <string>& header, vector <string>& numbers, vector <vector <string>>& cells){
    vector<string> expression = parser(value);//получаем 2 аргумента и знак
    int res1 = 0, res2 = 0;

    if (isalpha(expression[0][0])){//если первый аргумент содержит букву
        vector<string> coord1 = parse_coordinate(expression[0]);//разбираем координату на 2 составляющих
        int coord1x = get_coordinate(coord1[0], header);
        int coord1y = get_coordinate(coord1[1], numbers);//получили первые координаты

        try {
            res1 = stoi(cells[coord1y][coord1x]);
        }
        catch(invalid_argument e) {
            cout << "Invalid Argument In Cell"<< coord1x << coord1y;
        }
    }else{
        try {
            res1 = stoi(expression[0]);//если буквы в аргументе нет, то это просто число
        }
        catch(invalid_argument e) {
            cout << "Invalid Argument In "<< expression[0];
        }
    }

    if (isalpha(expression[2][0])){//если второй аргумент содержит букву
        vector<string> coord2 = parse_coordinate(expression[2]);//разбираем координату на 2 составляющих
        int coord2x = get_coordinate(coord2[0], header);
        int coord2y = get_coordinate(coord2[1], numbers);//получили первые координаты
        try {
            res2 = stoi(cells[coord2y][coord2x]);//получаем значение по координатам
        }
        catch(invalid_argument e) {
            cout << "Invalid Argument In Cell"<< coord2x << coord2y;
        }
    }else{
        try {
            res2 = stoi(expression[2]);//если буквы в аргументе нет, то это просто число
        }
        catch(invalid_argument e) {
            cout << "Invalid Argument In "<< expression[2];
        }
    }
    string plus = "+";
    string minus = "-";
    string division = "/";
    string mul = "*";
    int result = 0;
    if(expression[1] == plus){
        result = res1 + res2;
    }
    else if(expression[1] == minus){
        result = res1 - res2;
    }
    else if(expression[1] == division){
        if (res2 == 0) result = 0;
        else result = int(res1/res2);
    }
    else if(expression[1] == mul){
        result = res1 * res2;
    }

    return to_string(result);
}

int calculate(vector <string>& header, vector <string>& numbers, vector <vector <string>>& cells){
    vector <string> expression;
    string  value = "";
    for (int i = 0; i < cells.size(); i++){
        for (int j = 0; j < cells[i].size(); j++){
            value = cells[i][j];
            if (value[0] == '='){
                value.erase(0,1); // удаляет из строки знак равенства

                cells[i][j] = extract(value, header, numbers, cells);//записываем результат выражения
            }
        }
   }
}


int main(int argc, char* argv[])
{
    if(argc != 2){
        cout << "usage: " << argv[0] << " path_to_csv_file\n";
        return 0;
    }
    ifstream work_file(argv[1]);

    if (!work_file.is_open()){
        cout << "file not found";
    }
    if (work_file.peek() == EOF){
        cout << endl;
        return 0;
    }
    string line;
    string value;
    char delimiter = ',';
    vector <string> header;
    vector <string> numbers;
    vector < vector <string> > cells;

    while (getline(work_file, line)){ //заполняем массив ячеек и массив номеров строк
        int j = 0;
        vector <string> row;
        istringstream s(line);
        string value;
        while (getline(s, value,delimiter)){
            if (j == 0){
                j++;
                if (value==""){}//если элемен пустой, то ничего
                else{//иначе добавить к массиву номеров строк
                    numbers.push_back(value);//добавляем к массиву номеров строк
                }
            }else{
                row.push_back(value);//строка без первого элемента
            }
        }
        cells.push_back(row);//добавляем в основной массив клеток
    }
    header = cells[0]; //получаем массив заголовка
    auto iter = cells.cbegin(); // указатель на первый элемент
    cells.erase(iter);   // удаляем элемент

    calculate(header, numbers, cells);//рассчитываем значения для ячеек

    cout << ",";
    for (int j = 0; j < header.size(); j++){
        if(j == 0) cout <<  header[j];
        else cout << "," <<  header[j];
    }
    cout << endl;//вывели заголовок
    for (int i = 0; i < cells.size(); i++){

        cout << numbers[i] << ",";
        for (int j = 0; j < cells[i].size(); j++){
            cout << cells[i][j];
            if(j!=cells[i].size()-1){
                cout << ",";
            }
        }
        cout << endl;
    }
work_file.close();
return 0;
}