#include <cstdlib>
#include <limits>
#include <cmath>
#include <ctime>
#include <fstream>
#include "kohonenmap.h"
using namespace std;

som(double input_vector[])
{
  step = 0;
  for(int k=0;k<WEIGHTS;k++)
     for(int i=0;i<SIZE;i++)
         for(int j=0;j<SIZE;j++)
         {
             srand(clock());
             neurons_arr[k][i][j]=double( (rand()) / (double( (RAND_MAX/0.01))));
         }
 for(int i=0;i<WEIGHTS;i++)
     input_arr[i]=input_vector[i];
 winner_coords[0]=0;
 winner_coords[1]=0;
 for(int i=0;i<SIZE;i++)
    for(int j=0;j<SIZE;j++)
        map[i][j]=0;
}

som(char *filename, double input_vector[])
{
    step = 0;
     for(int i=0;i<SIZE;i++)
         for(int j=0;j<SIZE;j++)
             map[i][j]=0;
     winner_coords[0]=0;
     winner_coords[1]=0;
     for(int i=0;i<WEIGHTS;i++)
         input_arr[i]=input_vector[i];
     //чтение матриц нейронов из файла
     
}

void add_vector(double input_vector[])
{
     for(int i=0;i<WEIGHTS;i++)
       input_arr[i]=input_vector[i];
     winner_coords[0]=0;
     winner_coords[1]=0;
}

void normalyze()
{
double arr_module=0;
for(int i=0;i<WEIGHTS;i++)
    arr_module+=input_arr[i]*input_arr[i];
arr_module=sqrt(arr_module);
for(int i=0;i<WEIGHTS;i++)
    input_arr[i]/=arr_module;
}

void work()
{
winner_coords[0]=0;
winner_coords[1]=0;
step++;
double rez=999999.9;
double buf=0;
for(int i=0;i<SIZE;i++)
    for(int j=0;j<SIZE;j++)
    {
     for(int k=0;k<WEIGHTS;k++)
     {
        buf += (input_arr[k]-neurons_arr[k][i][j])*(input_arr[k]-neurons_arr[k][i][j]);
     }
     double x = sqrt(buf);
     buf = x;
     if(buf<rez)
         {
             rez=buf;
             winner_coords[0]=i;
             winner_coords[1]=j;
         }
    }
map[winner_coords[0]][winner_coords[1]]=1;
}

void correct_weights()
{
    double d;//расстояние до нейрона победителя
    double func_teta;
    double func_a;
    double sigma = 1 / step;
    func_a = CONST_A / step + CONST_B;
    //для каждого нейрона вычисляем расстояние до победителя и соответственно корректируем вес(на карте)
    for(int i=0;i<SIZE;i++)
        for(int j=0;j<SIZE;j++)
        {
            //расстояние до победителя
            d=sqrt((i-winner_coords[0])*(i-winner_coords[0])+(j-winner_coords[1])*(j-winner_coords[1]));
            func_teta = exp(-1*d/(2*sigma));
            //корректировка весов очередного нейрона в соответствии с полученным значением скорости обучения
            for(int k=0;k<WEIGHTS;k++)
            {
                neurons_arr[k][i][j]+=func_a*func_teta*(input_arr[k]-neurons_arr[k][i][j]);
                if(neurons_arr[k][i][j] < 0)
                    neurons_arr[k][i][j] *= -1;
            }
            //окраска карты в окрестностях победителя
            if(d!=0)
              map[i][j]=1/d;
        }
}

void write_neurons()
{
    ofstream outfile;
    outfile.open("weights.txt", ios_base::app);
    for(int k=0;k<WEIGHTS;k++)
    {
        for(int i=0;i<SIZE;i++)
        {
            for(int j=0;j<SIZE;j++)
                outfile << neurons_arr[k][i][j] << " ";
            outfile << endl;
        }
        outfile << "----------" << endl; 
    }
    outfile.close();
}

void write_map(char* filename)
{
 ofstream outfile;
 outfile.open(filename, ios_base::app);
    outfile << "step № " << step << endl << "INPUT:" << endl;
    for(int i=0;i<WEIGHTS;i++)
        outfile << input_arr[i] << " ";
    outfile << endl <<"WINNER: " << winner_coords[0] <<" " << winner_coords[1] << endl << endl;
    for(int i=0;i<SIZE;i++)
    {
        for(int j=0;j<SIZE;j++)
            outfile << map[i][j] << " ";
        outfile << endl;
    }
 outfile.close();
}
