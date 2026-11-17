// This is most basic example of
// how to use Mantis NN to solve XOR problem


#include "Mantis_NN.h"

NN testNN;  // Neural Network Object


void setup() {

  Serial.begin(9600);

  // Show RAM before NN initialized
  Serial.println();
  Serial.println(F("RAM before NN initialized"));
  display_freeram();

  // setup and initialize NN
  testNN.setNumOfLayers(3);       // 3-layer network
  testNN.setNumOfNodes(0, 2);     // 1st (input) layer 2 nodes
  testNN.setNumOfNodes(1, 3);     // 2nd (hidden) layer 3 nodes
  testNN.setNumOfNodes(2, 1);     // 3rd (output) layer 1 nodes
    
  testNN.initEmptyNN();           // allocate empty nn
  testNN.randomizeWeights(0);     // init NN weights with random values

  // Show NN
  Serial.println();
  Serial.println(F("NN created: "));
  testNN.disp_NN();

  // Show RAM after NN initialized
  Serial.println();
  Serial.println(F("RAM after NN initialized"));
  display_freeram();
   
  // Training data (XOR) 
  // INPUTS
  // (Number of columns same as number of input nodes)
  double X[4][2] = {{0,0},
                    {0,1},
                    {1,0},
                    {1,1}};

  // TARGETS
  // (Number of columns same as number of output nodes)
  double Y[4][1] = {{0},
                    {1},
                    {1},
                    {0}};

  // Try NN
  double Test[2] = {0, 1};
  


  // Train NN
  Serial.println();
  testNN.list_train_static_data(X, Y, 4); // 4-row dataset
  
  // Display NN after training
  Serial.println();
  Serial.println(F("NN after training: "));
  testNN.disp_NN();

  for(int i = 0; i < 3; i++){

    Serial.print(F("Input: "));
    Serial.print(X[i][0]);
    Serial.print(F(", "));
    Serial.println(X[i][1]);
    
    testNN.propagate_network(X[i]);
    testNN.disp_Outputs();
    
  }

  // Try to predict output with NN
  testNN.propagate_network(Test);

  // Display output layer values
  Serial.println();
  Serial.println(F("Outputs: "));
  testNN.disp_Outputs();
}

void loop() {
  // put your main code here, to run repeatedly:

}



// ------------------------------------------------------------------------------------------------------------
// Check available SRAM
// https://docs.arduino.cc/learn/programming/memory-guide/

void display_freeram() {
    Serial.print(F("SRAM left: "));
    Serial.println(freeRam());
}

int freeRam() {
  extern int __heap_start,*__brkval;
  int v;
  return (int)&v - (__brkval == 0  ? (int)&__heap_start : (int) __brkval);  
}
