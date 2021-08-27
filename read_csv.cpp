#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <cctype>
#include <string>
using namespace std;

vector<string> extract(string value){
    value.erase(0,1); // удаляет из строки знак равенства
    string word = "";
    string number = "";
    string plus = "+";
    string minus = "-";
    string division = "/";
    string mul = "*";
    vector<string> expression;
    for (int i = 0; i < value.length(); i++){
        if(isalpha(value[i])){
            word += value[i];
        }
        if (isdigit(value[i]) ) {
            number += value[i];
        }
        if(value[i] == '+' || value[i] == '-' || value[i] == '/' || value[i] == '*'){
            char s[] = {value[i], '\0'};
            string sign(s);
            expression.push_back(word);
            expression.push_back(number);
            expression.push_back(sign);
            word = "";
            number = "";
        }
    }
    expression.push_back(word);
    expression.push_back(number);
    return expression;
}

string find(vector <string>& expression, vector <string>& header, vector <string>& numbers, vector <vector <string>>& cells){
    int coord1x;
    int coord1y;
    int coord2x;
    int coord2y;
    for (int j = 0; j < numbers.size(); j++){
        if(expression[0]==numbers[j]){
            coord1x = j;
        }
    }
    for (int j = 0; j < header.size(); j++){
        if(expression[1]==header[j]){
            coord1y = j;
        }
    }
    for (int j = 0; j < numbers.size(); j++){
        if(expression[3]==numbers[j]){
            coord2x = j;
        }
    }
    for (int j = 0; j < header.size(); j++){
        if(expression[4]==header[j]){
            coord2y = j;
        }
    }
    int res1, res2;
    try {
        res1 = stoi(cells[coord1x][coord1y]);
    }
    catch(std::invalid_argument e) {
        cout << "Invalid Argument In Cell"<< coord1x << coord1y;
    }
    try {
        res2 = stoi(cells[coord2x][coord2y]);
    }
    catch(std::invalid_argument e) {
        cout << "Invalid Argument In Cell"<< coord2x << coord2y;
    }
    int result;
    string plus = "+";
    string minus = "-";
    string division = "/";
    string mul = "*";
    if(expression[2] == plus){
        result = res1 + res2;
    }
    else if(expression[2] == minus){
        result = res1 - res2;
    }
    else if(expression[2] == division){
        result = int(res1/res2);
    }
    else if(expression[2] == mul){
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
                expression = extract(value);//получаем выражением

//                cells[i][j] = find(expression, header, numbers, cells);//записываем результат выражения в ячейку
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
    string line;
    string value;
    char delimiter = ',';
    vector <string> header;
    vector <string> numbers;
    vector < vector <string> > cells;

    while (getline(work_file, line)){ //заполняем массив ячеек и массив номеров строк
    //    cout << line;}
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

//    cout << ",";
//    for (int j = 0; j < header.size(); j++){
//        cout <<  header[j] << ",";
//    }
//    cout << endl;//вывели заголовок
//
//    for (int i = 0; i < cells.size(); i++){
//        cout << numbers[i] << ",";
//        for (int j = 0; j < cells[i].size(); j++){
//            cout << cells[i][j];
//            if(j!=cells[i].size()-1){
//                cout << ",";
//            }
//        }
//        cout << endl;
//    }
work_file.close();
return 0;
}