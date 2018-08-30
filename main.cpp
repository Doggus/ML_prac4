#include <iostream>
#include <vector>

using namespace std;

struct IOdata
{
    float input1;
    float input2;
    float output;

    IOdata(float i1, float i2, float o)
    {
        input1 = i1;
        input2 = i2;
        output = o;
    }
};

float getRandomFloat(float a, float b) 
{
    float random = ((float) rand()) / (float) RAND_MAX;
    float diff = b - a;
    float r = random * diff;
    return a + r;
}

bool learningAlgorithm(IOdata data, pair<float, float> weights, int correctValueCount, const string type)
{

   float weightedSum = 0;
   for (int i = 0; i < 4; ++i)
   {
       weightedSum += (data.input1 * weights.first) + (data.input2 * weights.second);
   }

   //Apply thr weighted sum to the correct Activation Function.
   //Threshold being im using is unit step threshold:
   //0 if x < 0 and 1 if x >= 0  
   float thresholdValue;

   if (weightedSum < 0)
   {
       thresholdValue = 0;
   }
   else
   {
    thresholdValue = 1;
   }

    // if errorValue = 0 theshold value is equal to true output
    float errorValue = data.output - thresholdValue;
    bool isEqual;

    if (errorValue == 0)
    {
        isEqual = true;
    }
    else
    {
        isEqual = false;
    }

    cout << data.input1 << type << data.input2 << " = " << thresholdValue << " true output is: " << data.output << endl;

    //arbitrary value between 0 and 1
    float rate = 0.5;

    if (!isEqual)
    {
        cout << "Therefore: change weights, errorValue = " << errorValue << endl;

        weights.first += rate * errorValue * data.input1;
        weights.second += rate * errorValue * data.input2;

        correctValueCount = 0;

        return false;
    }

    ++correctValueCount;
    //return true if 4 in a row are correct
    return correctValueCount == 4;

}

int main()
{
    cout << "Hello, World!" << endl;

   vector<IOdata> XORdata;
   XORdata.push_back(IOdata(1,1,0));
   XORdata.push_back(IOdata(1,0,1));
   XORdata.push_back(IOdata(0,1,1));
   XORdata.push_back(IOdata(0,0,0));

   vector<IOdata> ANDdata;
   ANDdata.push_back(IOdata(1,1,1));
   ANDdata.push_back(IOdata(1,0,0));
   ANDdata.push_back(IOdata(0,1,0));
   ANDdata.push_back(IOdata(0,0,0));

   vector<IOdata> ORdata;
   ORdata.push_back(IOdata(1,1,1));
   ORdata.push_back(IOdata(1,0,1));
   ORdata.push_back(IOdata(0,1,1));
   ORdata.push_back(IOdata(0,0,0));

   //intialised to random float betwen -1 and 1
   pair<float,float> weights;
   for (int i = 0; i < 4; ++i)
   {
       weights.first = getRandomFloat(-1,1);
       weights.second = getRandomFloat(-1,1);
   }

   //Loops until 4 outputs are equal to true outputs in a row ([i % 4] = 0,1,2,3,0,1,2,3,.....)
   int correctValueCount = 0;
   for (int i = 0; i < 300; ++i)
   {
       if (learningAlgorithm(ORdata[i % 4], weights, correctValueCount, " OR "))
       {
        cout << "BREAK" << endl;
        break;
       } 
   }
   
   
    



    return 0;
}