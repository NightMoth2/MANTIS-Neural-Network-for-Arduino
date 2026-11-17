/*
 * Ver 2 - 2026-09-25
 * Added empty constructor and init() method 
 * Now it is possible to define object globaly but initialize locally
 * 
 * 2026-04-27
 * Class for doble pointer dynamically allocated 2D arrays
 * Based on template functions, can be arbitary data type
 */


#ifndef DYNAMIC2DARR_H
#define DYNAMIC2DARR_H

#include <Arduino.h>

//#define DEBUG_MODE
//#define REPORT_MODE

template <typename T> 
class Dynamic2DArr
{
  private:
    int rows_cnt;
    int cols_cnt;

    T** Arr;

  public:

    Dynamic2DArr();
    Dynamic2DArr(int rows_cnt, int cols_cnt);
    ~Dynamic2DArr();

    void init(int rows_cnt, int cols_cnt);
    int getRowsCnt();
    int getColsCnt();    
    void setVal(int row_idx, int col_idx, T val);
    T getVal(int row_idx, int col_idx);
    T** getArrPtr();   
     
    void dispArr();
};


template <typename T> 
Dynamic2DArr<T>::Dynamic2DArr(){

    rows_cnt = 0;
    cols_cnt = 0;

    Arr - NULL;
}

template <typename T> 
Dynamic2DArr<T>::Dynamic2DArr(int rows_cnt, int cols_cnt)
{
  #ifdef DEBUG_MODE
    Serial.println(F("Constructor Dynamic2DAr::Dynamic2DArr() start"));
  #endif
  
  this->rows_cnt = rows_cnt;
  this->cols_cnt = cols_cnt;

  this->Arr = new T*[rows_cnt];  
  for(int row = 0; row <  this->rows_cnt; row++)
  {
    this->Arr[row] = new T[this->cols_cnt];
    
    #ifdef DEBUG_MODE
      Serial.print(F("row # "));
      Serial.print(row);
      Serial.print(F(" columns added "));
      Serial.println(this->cols_cnt);
    #endif
  }

  for(int row = 0; row <  this->rows_cnt; row++)
  {
    for(int col = 0; col <  this->cols_cnt; col++)
    {
      this->Arr[row][col] = 7;

      #ifdef DEBUG_MODE
        Serial.print(F("Arr["));
        Serial.print(row);
        Serial.print(F("]["));
        Serial.print(col);
        Serial.print(F("]="));
        Serial.print(this->Arr[row][col]);
        Serial.print(F(";"));
      #endif     
    }
    #ifdef DEBUG_MODE
      Serial.println();
    #endif
  }

  #ifdef DEBUG_MODE
    Serial.println(F("Constructor Dynamic2DAr::Dynamic2DArr() end"));
  #endif
}


template <typename T> 
Dynamic2DArr<T>::~Dynamic2DArr()
{
  #ifdef DEBUG_MODE
    Serial.println(F("Destructor Dynamic2DAr::~Dynamic2DArr() start"));
  #endif
  
  for(int row = 0; row < rows_cnt; row++)
  {
    delete[] this->Arr[row]; 
  }
  delete[] this->Arr;   
  this->Arr = NULL; 
  
  #ifdef DEBUG_MODE
    Serial.println(F("Destructor Dynamic2DAr::~Dynamic2DArr() end"));
  #endif
}

template <typename T> 
void Dynamic2DArr<T>::init(int rows_cnt, int cols_cnt){

  #ifdef DEBUG_MODE
    Serial.println(F("Constructor Dynamic2DAr::init() start"));
  #endif
  
  this->rows_cnt = rows_cnt;
  this->cols_cnt = cols_cnt;

  this->Arr = new T*[rows_cnt];  
  for(int row = 0; row <  this->rows_cnt; row++)
  {
    this->Arr[row] = new T[this->cols_cnt];
  }

  for(int row = 0; row <  this->rows_cnt; row++)
  {
    for(int col = 0; col <  this->cols_cnt; col++)
    {
      this->Arr[row][col] = 0.0;  
    }
  }
}

template <typename T> 
int Dynamic2DArr<T>::getRowsCnt()
{
  return rows_cnt;
}


template <typename T> 
int Dynamic2DArr<T>::getColsCnt()
{
  return cols_cnt;
}


template <typename T> 
void Dynamic2DArr<T>::setVal(int row_idx, int col_idx, T val) 
{

  this->Arr[row_idx][col_idx] = val;
  
  #ifdef DEBUG_MODE
    Serial.print(F("Dynamic2DAr::setVal() Arr["));
    Serial.print(row_idx);
    Serial.print(F("]["));
    Serial.print(col_idx);
    Serial.print(F("]="));
    Serial.print(Arr[row_idx][col_idx]);
    Serial.println(F(" Done;"));
  #endif     
}


template <typename T> 
T Dynamic2DArr<T>::getVal(int row_idx, int col_idx)
{
  return this->Arr[row_idx][col_idx];
}


template <typename T> 
T** Dynamic2DArr<T>::getArrPtr()
{
  return this->Arr;
}


template <typename T> 
void Dynamic2DArr<T>::dispArr()
{

  //#ifdef DEBUG_MODE
    //Serial.println(F("Dynamic2DAr::dispArr() start"));

    for(int row = 0; row < this->rows_cnt; row++)
    {
      for(int col = 0; col < this->cols_cnt; col++)
      {
        Serial.print(this->Arr[row][col]);
        Serial.print(F("; "));
      }
      Serial.println();
    }

    //Serial.println(F("Dynamic2DAr::dispArr() end"));
  //#endif
}

#endif
