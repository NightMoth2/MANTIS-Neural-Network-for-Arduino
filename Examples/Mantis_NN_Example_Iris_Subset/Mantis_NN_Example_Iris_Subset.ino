// Example of using Mantis neural net
// with Iris data subset.
// Data is stored in Arduino's RAM in this example,
// and size of a dataset is limited by Arduino's RAM.
// For more complex datasets, data can be received from 
// PC row by row via serial  

// ------------------------------------------------------------------------------------------------------------
#include "Mantis_NN.h"
#include "Dynamic2DArr.h"


// Metadata for Iris train subset
byte train_rows_cnt = 30; // num of rows in train dataset
byte in_cols_cnt = 4;     // num of columns with input data
byte tgt_cols_cnt = 1;    // num of columns with target data
double x0_min = 4.8;      // input column 0("sepal length") min value
double x0_max = 7.7;      // input column 0("sepal length") max value
double x1_min = 2.0;      // input column 1("sepal width") min value
double x1_max = 4.4;      // input column 1("sepal width") max value
double x2_min = 1.2;      // input column 2("petal length") min value
double x2_max = 6.6;      // input column 2("petal length") max value
double x3_min = 0.2;      // input column 3("petal width") min value
double x3_max = 2.5;      // input column 3("petal width") max value
double y0_min = 0.0;      // target column 0("Class") min value (0 = Iris-setosa; 1 = Iris-versicolor; 2 = Iris-virginica)
double y0_max = 2.0;      // target column 0("Class") max value (0 = Iris-setosa; 1 = Iris-versicolor; 2 = Iris-virginica)
// Metadata for Iris test subset
byte test_rows_cnt = 6;   // num of rows in test dataset

// Data tables
Dynamic2DArr<double> dyn_X;   // Array for Iris train inputs data
Dynamic2DArr<double> dyn_Y;   // Array for Iris train targets data
Dynamic2DArr<double> dyn_T;   // Array for Iris test inputs data
Dynamic2DArr<double> dyn_C;   // Array for Iris test targets data (correct class)


NN testNN;            // NN Object
int epochs_cnt = 50;  // Number of epochs to train
double x_scaled_min = -2.5;
double x_scaled_max = 2.5;
double y_scaled_min = 0.0;
double y_scaled_max = 1.0;

// ------------------------------------------------------------------------------------------------------------
void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);

  // Display Available RAM
  Serial.println(F("RAM before NN and datasets initialized: "));
  display_freeram();

  // setup and initialize NN
  testNN.setNumOfLayers(3);       // Set number of layers
  testNN.setNumOfNodes(0, 4);     // Input layer 
  testNN.setNumOfNodes(1, 12);     // 1st hidden layer 
  //testNN.setNumOfNodes(2, 4);     // 2nd hidden layer 
  testNN.setNumOfNodes(2, 1);     // Output layer 

  testNN.initEmptyNN();        // empty nn allocated
  testNN.randomizeWeights(0);  // init NN weights with random values

  // Display NN and remaining RAM
  Serial.println();
  Serial.println(F("NN created: "));
  testNN.disp_NN();

  Serial.println(F("RAM after NN initialized: "));
  display_freeram();


  // Iris train subset data
  dyn_X.init(train_rows_cnt, in_cols_cnt);
  dyn_Y.init(train_rows_cnt, tgt_cols_cnt);
  
  // "sepal length"         | "sepal width"           | "petal length"          | "petal width"           | "Class"
  dyn_X.setVal(0, 0, 5.4);  dyn_X.setVal(0, 1, 3.7);  dyn_X.setVal(0, 2, 1.5);  dyn_X.setVal(0, 3, 0.2);  dyn_Y.setVal(0, 0, 0.0);    // #12
  dyn_X.setVal(1, 0, 6.6);  dyn_X.setVal(1, 1, 3.0);  dyn_X.setVal(1, 2, 4.4);  dyn_X.setVal(1, 3, 1.4);  dyn_Y.setVal(1, 0, 1.0);    // #76
  dyn_X.setVal(2, 0, 5.0);  dyn_X.setVal(2, 1, 3.2);  dyn_X.setVal(2, 2, 1.2);  dyn_X.setVal(2, 3, 0.2);  dyn_Y.setVal(2, 0, 0.0);    // #26
  dyn_X.setVal(3, 0, 7.0);  dyn_X.setVal(3, 1, 3.2);  dyn_X.setVal(3, 2, 4.7);  dyn_X.setVal(3, 3, 1.4);  dyn_Y.setVal(3, 0, 1.0);    // #51
  dyn_X.setVal(4, 0, 6.7);  dyn_X.setVal(4, 1, 3.0);  dyn_X.setVal(4, 2, 5.2);  dyn_X.setVal(4, 3, 2.3);  dyn_Y.setVal(4, 0, 2.0);    // #146
  dyn_X.setVal(5, 0, 5.0);  dyn_X.setVal(5, 1, 3.5);  dyn_X.setVal(5, 2, 1.3);  dyn_X.setVal(5, 3, 0.3);  dyn_Y.setVal(5, 0, 0.0);    // #41
  dyn_X.setVal(6, 0, 5.9);  dyn_X.setVal(6, 1, 3.2);  dyn_X.setVal(6, 2, 4.8);  dyn_X.setVal(6, 3, 1.8);  dyn_Y.setVal(6, 0, 1.0);    // #71
  dyn_X.setVal(7, 0, 4.8);  dyn_X.setVal(7, 1, 3.0);  dyn_X.setVal(7, 2, 1.4);  dyn_X.setVal(7, 3, 0.3);  dyn_Y.setVal(7, 0, 0.0);    // $46
  dyn_X.setVal(8, 0, 6.3);  dyn_X.setVal(8, 1, 3.3);  dyn_X.setVal(8, 2, 6);    dyn_X.setVal(8, 3, 2.5);  dyn_Y.setVal(8, 0, 2.0);    // #101
  dyn_X.setVal(9, 0, 5.0);  dyn_X.setVal(9, 1, 2.0);  dyn_X.setVal(9, 2, 3.5);  dyn_X.setVal(9, 3, 1.0);  dyn_Y.setVal(9, 0, 1.0);    // #61
  dyn_X.setVal(10, 0, 6.4); dyn_X.setVal(10, 1, 3.2); dyn_X.setVal(10, 2, 5.3); dyn_X.setVal(10, 3, 2.3); dyn_Y.setVal(10, 0, 2.0);   // #116
  dyn_X.setVal(11, 0, 6.9); dyn_X.setVal(11, 1, 3.2); dyn_X.setVal(11, 2, 5.7); dyn_X.setVal(11, 3, 2.3); dyn_Y.setVal(11, 0, 2.0);   // #121
  dyn_X.setVal(12, 0, 5.5); dyn_X.setVal(12, 1, 2.4); dyn_X.setVal(12, 2, 3.8); dyn_X.setVal(12, 3, 1.1); dyn_Y.setVal(12, 0, 1.0);   // #81
  dyn_X.setVal(13, 0, 5.7); dyn_X.setVal(13, 1, 3.0); dyn_X.setVal(13, 2, 4.2); dyn_X.setVal(13, 3, 1.2); dyn_Y.setVal(13, 0, 1.0);   // #96
  dyn_X.setVal(14, 0, 6.7); dyn_X.setVal(14, 1, 3.1); dyn_X.setVal(14, 2, 5.6); dyn_X.setVal(14, 3, 2.4); dyn_Y.setVal(14, 0, 2.0);   // #141
  dyn_X.setVal(15, 0, 5.7); dyn_X.setVal(15, 1, 4.4); dyn_X.setVal(15, 2, 1.5); dyn_X.setVal(15, 3, 0.4); dyn_Y.setVal(15, 0, 0.0);   // #16
  dyn_X.setVal(16, 0, 6.7); dyn_X.setVal(16, 1, 3.1); dyn_X.setVal(16, 2, 4.4); dyn_X.setVal(16, 3, 1.4); dyn_Y.setVal(16, 0, 1.0);   // #66
  dyn_X.setVal(17, 0, 4.8); dyn_X.setVal(17, 1, 3.1); dyn_X.setVal(17, 2, 1.6); dyn_X.setVal(17, 3, 0.2); dyn_Y.setVal(17, 0, 0.0);   // #31
  dyn_X.setVal(18, 0, 5.4); dyn_X.setVal(18, 1, 3.4); dyn_X.setVal(18, 2, 1.7); dyn_X.setVal(18, 3, 0.2); dyn_Y.setVal(18, 0, 0.0);   // #21
  dyn_X.setVal(19, 0, 5.5); dyn_X.setVal(19, 1, 2.6); dyn_X.setVal(19, 2, 4.4); dyn_X.setVal(19, 3, 1.2); dyn_Y.setVal(19, 0, 1.0);   // #91
  dyn_X.setVal(20, 0, 5.0); dyn_X.setVal(20, 1, 3.0); dyn_X.setVal(20, 2, 1.6); dyn_X.setVal(20, 3, 0.2); dyn_Y.setVal(20, 0, 0.0);   // #26
  dyn_X.setVal(21, 0, 5.7); dyn_X.setVal(21, 1, 2.8); dyn_X.setVal(21, 2, 4.5); dyn_X.setVal(21, 3, 1.3); dyn_Y.setVal(21, 0, 1.0);   // #56
  dyn_X.setVal(22, 0, 7.4); dyn_X.setVal(22, 1, 2.8); dyn_X.setVal(22, 2, 6.1); dyn_X.setVal(22, 3, 1.9); dyn_Y.setVal(22, 0, 2.0);   // #131
  dyn_X.setVal(23, 0, 6.0); dyn_X.setVal(23, 1, 3.4); dyn_X.setVal(23, 2, 4.5); dyn_X.setVal(23, 3, 1.6); dyn_Y.setVal(23, 0, 1.0);   // #86
  dyn_X.setVal(24, 0, 6.5); dyn_X.setVal(24, 1, 3.2); dyn_X.setVal(24, 2, 5.1); dyn_X.setVal(24, 3, 2.0); dyn_Y.setVal(24, 0, 3.0);   // #111
  dyn_X.setVal(25, 0, 7.2); dyn_X.setVal(25, 1, 3.2); dyn_X.setVal(25, 2, 6);   dyn_X.setVal(25, 3, 1.8); dyn_Y.setVal(25, 0, 2.0);   // #126
  dyn_X.setVal(26, 0, 7.6); dyn_X.setVal(26, 1, 3.0); dyn_X.setVal(26, 2, 6.6); dyn_X.setVal(26, 3, 2.1); dyn_Y.setVal(26, 0, 2.0);   // #106
  dyn_X.setVal(27, 0, 5.4); dyn_X.setVal(27, 1, 3.9); dyn_X.setVal(27, 2, 1.7); dyn_X.setVal(27, 3, 0.4); dyn_Y.setVal(27, 0, 0.0);   // #6
  dyn_X.setVal(28, 0, 5.1); dyn_X.setVal(28, 1, 3.5); dyn_X.setVal(28, 2, 1.4); dyn_X.setVal(28, 3, 0.2); dyn_Y.setVal(28, 0, 0.0);   // #1
  dyn_X.setVal(29, 0, 7.7); dyn_X.setVal(29, 1, 3.0); dyn_X.setVal(29, 2, 6.1); dyn_X.setVal(29, 3, 2.3); dyn_Y.setVal(29, 0, 1.0);   // #136

  // Iris test subset data
  dyn_T.init(test_rows_cnt, in_cols_cnt);
  dyn_C.init(test_rows_cnt, tgt_cols_cnt);
  
  // "sepal length"         | "sepal width"           | "petal length"          | "petal width"           | "Class"
  dyn_T.setVal(0, 0, 4.9);  dyn_T.setVal(0, 1, 3.0);  dyn_T.setVal(0, 2, 1.4);  dyn_T.setVal(0, 3, 0.2);  dyn_C.setVal(0, 0, 0.0);  // #2
  dyn_T.setVal(1, 0, 4.6);  dyn_T.setVal(1, 1, 3.4);  dyn_T.setVal(1, 2, 1.4);  dyn_T.setVal(1, 3, 0.3);  dyn_C.setVal(1, 0, 0.0);  // #7
  dyn_T.setVal(2, 0, 6.4);  dyn_T.setVal(2, 1, 3.2);  dyn_T.setVal(2, 2, 4.5);  dyn_T.setVal(2, 3, 1.5);  dyn_C.setVal(2, 0, 1.0);  // #52
  dyn_T.setVal(3, 0, 6.3);  dyn_T.setVal(3, 1, 3.3);  dyn_T.setVal(3, 2, 4.7);  dyn_T.setVal(3, 3, 1.6);  dyn_C.setVal(3, 0, 1.0);  // #57
  dyn_T.setVal(4, 0, 5.8);  dyn_T.setVal(4, 1, 2.7);  dyn_T.setVal(4, 2, 5.1);  dyn_T.setVal(4, 3, 1.9);  dyn_C.setVal(4, 0, 2.0);  // #102
  dyn_T.setVal(5, 0, 4.9);  dyn_T.setVal(5, 1, 2.5);  dyn_T.setVal(5, 2, 4.5);  dyn_T.setVal(5, 3, 1.7);  dyn_C.setVal(5, 0, 2.0);  // #107
  
  Serial.println();
  Serial.println(F("Raw train inputs: "));
  dyn_X.dispArr();

  Serial.println();
  Serial.println(F("Raw train targets: "));
  dyn_Y.dispArr();

  Serial.println();
  Serial.println(F("Raw test inputs: "));
  dyn_T.dispArr();

  Serial.println();
  Serial.println(F("Raw test targets: "));
  dyn_C.dispArr();

  // Scale/Normalize inputs and targets and test
  nn_encode_X(dyn_X.getArrPtr(), train_rows_cnt, in_cols_cnt);
  nn_encode_Y(dyn_Y.getArrPtr(), train_rows_cnt, tgt_cols_cnt);
  nn_encode_X(dyn_T.getArrPtr(), test_rows_cnt, in_cols_cnt);
  nn_encode_Y(dyn_C.getArrPtr(), test_rows_cnt, tgt_cols_cnt);

  Serial.println();
  Serial.println(F("Scaled train inputs: "));
  dyn_X.dispArr();

  Serial.println();
  Serial.println(F("Scaled train targets: "));
  dyn_Y.dispArr();

  Serial.println();
  Serial.println(F("Scaled test inputs: "));
  dyn_T.dispArr();

  Serial.println();
  Serial.println(F("Scaled test targets: "));
  dyn_C.dispArr();

  Serial.println();
  Serial.println(F("RAM after datasets created: "));
  display_freeram();

  nn_train_and_calc_learning_curves();


}


// ------------------------------------------------------------------------------------------------------------
void loop() {
  // put your main code here, to run repeatedly:

}



// ------------------------------------------------------------------------------------------------------------
void nn_encode_X(double** X, byte rows_cnt, byte cols_cnt){

  // Feature engineering for inputs (Scaling, normalization,... etc.)

  double tmp_val = 0;

  // Min/Max normalization

  // For each row
  for(int i = 0; i < rows_cnt; i++){

    // For each column
    for(int j = 0; j < cols_cnt; j++){
      
      tmp_val = X[i][j];
      
      // Normalize according to min/max metadata
      switch(j){
        case 0:{  // Column x0
          X[i][j] = testNN.fun_map(tmp_val, x0_min, x0_max, x_scaled_min, x_scaled_max); 
          break;
        }
        case 1:{  // Column x1
          X[i][j] = testNN.fun_map(tmp_val, x1_min, x1_max, x_scaled_min, x_scaled_max); 
          break;
        }
        case 2:{  // Column x2
          X[i][j] = testNN.fun_map(tmp_val, x2_min, x2_max, x_scaled_min, x_scaled_max); 
          break;
        }
        case 3:{  // Column x3
          X[i][j] = testNN.fun_map(tmp_val, x3_min, x3_max, x_scaled_min, x_scaled_max); 
          break;
        }
        default:{
          // do nothing
        }
      } // end switch columns
      
    } // end loop columns
  } // end loop rows  
}

// ------------------------------------------------------------------------------------------------------------
void nn_encode_Y(double** Y, byte rows_cnt, byte cols_cnt){

  // Scaling, normalization,... etc. for targets

  // Min/Max normalization

  double tmp_val = 0;

  // For each row
  for(int i = 0; i < rows_cnt; i++){

    // For each column
    for(int j = 0; j < cols_cnt; j++){
      tmp_val = Y[i][j];

      // Normalize according to min/max metadata
      switch(j){
        case 0:{  // Column y0
          Y[i][j] = testNN.fun_map(tmp_val, y0_min, y0_max, y_scaled_min, y_scaled_max); 
          break;
        }
        default:{
          // do nothing
        }
      } // end switch columns
      
    } // end loop columns
  } // end loop rows  
}

// ------------------------------------------------------------------------------------------------------------
void nn_train_and_calc_learning_curves(){

  // Train NN and test it, produce and print data to plot learning curves

  double epoch_accum_train_loss = 0;  // accumulated loss per epoch for train
  double epoch_accum_test_loss = 0;   // accumulated loss per epoch for test
  double epoch_avg_train_rmse = 0;    // train rmse per epoch
  double epoch_avg_test_rmse = 0;     // test rmse per epoch

  // Print column header
  Serial.println(F("EPOCH | TRAIN RMSE | TEST RMSE")); 

  // For each epoch
  for(int i = 0; i < epochs_cnt; i++){

    // reset accumulated values
    epoch_accum_train_loss = 0;
    epoch_accum_test_loss = 0;

    // TRAIN
    // For each train row
    for(int r = 0; r < train_rows_cnt; r++){

      // Train single row and accumulate loss
      epoch_accum_train_loss += testNN.single_train(dyn_X.getArrPtr()[r], dyn_Y.getArrPtr()[r]);      
    } 

    // Calculate train rmse
    epoch_avg_train_rmse = sqrt(epoch_accum_train_loss/train_rows_cnt);


    // TEST
    // For each test row
    for(int r = 0; r < test_rows_cnt; r++){

      // Test single row
      testNN.propagate_network(dyn_T.getArrPtr()[r]);  

      // Accumulate loss
      for(int c = 0; c < tgt_cols_cnt; c++){

        epoch_accum_test_loss += testNN.fun_Loss(testNN.getOut(c), dyn_C.getArrPtr()[r][c]);
      }      
    } 

    // Calculate test rmse
    epoch_avg_test_rmse = sqrt(epoch_accum_test_loss/(test_rows_cnt*tgt_cols_cnt));

    // Print result
    Serial.print(i);                    // Epoch#
    Serial.print(F(";"));
    Serial.print(epoch_avg_train_rmse); // Train RMSE
    Serial.print(F(";"));
    Serial.print(epoch_avg_test_rmse);  // Test RMSE
    Serial.println(); 
       
  }  // end loop epochs
   
}

// ------------------------------------------------------------------------------------------------------------
// See https://docs.arduino.cc/learn/programming/memory-guide/
void display_freeram() {
    Serial.print(F(" - SRAM left: "));
    Serial.println(freeRam());
}

int freeRam() {
  extern int __heap_start,*__brkval;
  int v;
  return (int)&v - (__brkval == 0  ? (int)&__heap_start : (int) __brkval);  
}
