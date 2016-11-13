#include <iostream>
#include "kohonenmap.h"
//количество входных векторов
#define NUMBER_OF_INPUTS 15

bool func(som map)
{
    return false;
}

int main(int argc, char *argv[])
{
//чтение входных данных из input.txt по одному и передача их нейросети
double input_vector[WEIGHTS];
ifstream input_file;
input_file.open("input.txt");
//считали массив
double buf;
for(int i=0;i<WEIGHTS;i++)
 input_file >> input_vector[i];
//передали массив нейросети
som map = som(input_vector);
for(int i=1;i<NUMBER_OF_INPUTS;i++)
{
 for(int i=0;i<WEIGHTS;i++)
  input_file >> input_vector[i];
//передали массив нейросети
map.add_vector(input_vector);
map.work();
if(!map.is_learn_finish())
    map.correct_weights();
map.write_map("maps.txt");
}
input_file.close();
return 0;
}
