#ifndef _KOHONEN_H
#define _KOHONEN_H
//count of neurons
#define SIZE 10
//count of weights(input vectors size)
#define WEIGHTS 15
#define CONST_A 254
#define CONST_B 37

class som 
{
//step of training
int step;
//colored map
double map[SIZE][SIZE];
//15 matrix 10х10
double neurons_arr[WEIGHTS][SIZE][SIZE];
//input array
double input_arr[WEIGHTS];
//coords of winner(neuron)
int winner_coords[2];
//parameter of mistake(mistake must be < mistake_param)
double mistake_param;
//is som trained
bool is_train;
public:
//create a som with random weights
som(double input_vector[]);
//read neurons weights from file
som(char *filename, double input_vector[]);
//give next input vector to som
void add_vector(double input_vector[]);
//normalyze input vector
void normalyze();
//write coords of neuron-winner in winner_coords
void work();
//correcting weights
void correct_weights();
//return true if training end
template< typename TCallback >
bool is_learn_finish(TCallback func)
{
    bool rez;
        //callback work
        rez=func(*this);
        if(rez == false)
        {
        double sum1=0.0
                sum2=0.0;
    for(int k=0;k<SIZE;k++)
      for(int j=0;j<SIZE;j++)
        for(int i=0;i<WEIGHTS;i++)
        {
           sum1+=neurons_arr[i][j][k]
           sum2+=input_arr[i];
        }
       sum1 /= WEIGHTS;
       sum2 /= WEIGHTS;
       if(sum1>sum2)
           rez = sum2-sum1<mistake_param;
       else
           rez = sum1-sum2<mistake_param;
   }
return rez;
}
//пишем массив весов нейронов в файл
void write_neurons();
//запись карты в файл
void write_map(char* filename);
} ;

#endif
