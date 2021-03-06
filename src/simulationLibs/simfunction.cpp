#include "simfunction.h"
simFunction::simFunction()
{

}

simFunction::simFunction(Matrix<double> in, Matrix<double> out)
{
    this->FunctionToCall = NULL;
    this->input          = in;
    this->output         = out;
    this->lMax           = in.max();
    this->lMin           = out.min();
    this->step           = 2;
}

simFunction::simFunction(double (*FunctionToCall)(double), double lMin,
                         double lMax, double step)
{
    this->FunctionToCall = FunctionToCall;
    this->lMax           = lMax;
    this->lMin           = lMin;
    this->step           = step;
}

double simFunction::FunctionCalculation(double input)
{
    input = ((*this->FunctionToCall)(input));
    return (input);
}

void simFunction::GenerateDataFunction()
{
    int tam  = (int)((this->lMax - this->lMin)/this->step);
    int cont = 1;
    this->input.init(1,tam);

    for (double i = this->lMin; i < this->lMax; i += this->step)
    {
        this->input(1,cont,i);
        this->output(1,cont,this->FunctionCalculation(i));
        cont++;
    }
}

double simFunction::normalize(double input, double xUp,
                              double xDown, double yUp, double yDown)
{
    return ((input - xDown)/(xUp - xDown))*(yUp - yDown) + yDown;
}

void simFunction::SetDataStep(double step)
{
    this->step = step;
}

void simFunction::SetDataLimits(double lMin, double lMax)
{
    this->lMax = lMax;
    this->lMin = lMin;
}

void simFunction::SetInputData(Matrix<double> input)
{
    this->input = input;
}

void simFunction::SetOutputData(Matrix<double> output)
{
    this->output = output;
}

void simFunction::SetFunctionCall(double (*FunctionToCall)(double))
{
    this->FunctionToCall = FunctionToCall;
}

Matrix<double> simFunction::GetInputData()
{
    return this->input;
}

Matrix<double> simFunction::GetOutputData()
{
    return this->output;
}

double simFunction::GetDataStep()
{
    return this->step;
}

double simFunction::GetDataMinLimit()
{
    return this->lMin;
}

double simFunction::GetDataMaxLimit()
{
    return this->lMax;
}

typedef double(*FunctionCall)(double);
FunctionCall simFunction::GetFunctionCall()
{
    return this->FunctionToCall;
}
