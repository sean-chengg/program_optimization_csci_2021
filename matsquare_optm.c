// optimized versions of matrix diagonal summing
#include "matvec.h"

int matsquare_VER1(matrix_t *mat, matrix_t *matsq) {
  matrix_t mats = *mat; //derefrences mat so we can directly access it with macros
  matrix_t matsqs = *matsq; ////derefrences matsq so we can directly access it with macros

  for (int i = 0; i < mat->rows; i++) { //loops through matrix
    for (int j = 0; j < mat->cols; j++) { 
      MSET(matsqs, i, j, 0); //sets everything to 0 in n^2 time
    }
  }

  for (int i = 0; i < mat->rows; i++) { //loops through matrix
        for (int j = 0; j < mat->cols; j++) { //loops through matrix
            int lead = MGET(mats, i, j); //sets "lead" variable, which stays ahead as second one iterates more.
            int cur = 0; //resets the current value we are dealing with
            for (int k = 0; k < mat->cols; k++) {
                int follow = MGET(mats, j, k); //sets the following variable, iterating through rows with macros
                cur = MGET(matsqs, i, k) + lead * follow; //grabs the current number of (i,k) with macros, then adds the lead * follow on
                MSET(matsqs, i, k, cur); //sets the matrix
            }
        }
  }     
    return 0; //return 0
 
 
}

int matsquare_VER2(matrix_t *mat, matrix_t *matsq) {
  for(int i=0; i<mat->rows; i++){
    for(int j=0; j<mat->cols; j++){
      mset(matsq,i,j,0);                          // initialize to 0s
      for(int k=0; k<mat->rows; k++){
        int mik = mget(mat, i, k);
        int mkj = mget(mat, k, j);
        int cur = mget(matsq, i, j);
        int new = cur + mik*mkj;
        mset(matsq, i, j, new);
      }
    }
  }
  return 0; 
        } 

int matsquare_OPTM(matrix_t *mat, matrix_t *matsq){
  if(mat->rows != mat->cols   ||      // must be a square matrix to square it
     mat->rows != matsq->rows ||
     mat->cols != matsq->cols)
  {
    printf("matsquare_OPTM: dimension mismatch\n");
    return 1;
  }

  // Call to some version of optimized code
  return matsquare_VER1(mat, matsq);
}
/////////////////////////////////////////////////////////////////////////////////
// ADDITIONAL INFORMATION
//
// (A) VERSION: If you implemented several versions, indicate which
// version you timed
// 
// ####################### YOUR ANSWER HERE #########################
// The version that I timed is version 1
// 
// ##################################################################
// 
//
// (B) TIMING ON loginNN.cselabs.umn.edu:
// Paste a copy of the results of running matsquare_benchmark on the
// above machines in the space below which shows how your performance
// optimizations improved on the baseline codes.
// 
// ####################### YOUR ANSWER HERE #########################

// 
// ##################################################################
// 
// (C) OPTIMIZATIONS:
// Describe in some detail the optimizations you used to speed the code
// up.  THE CODE SHOULD CONTAIN SOME COMMENTS already to describe these
// but in the section below, describe in English the techniques you used
// to make the code run faster.  Format your descriptions into discrete
// chunks such as.
// 
// Optimization 1: Blah bla blah... This should make run faster because
// yakkety yakeety yak.
// 
// Optimization 2: Blah bla blah... This should make run faster because
// yakkety yakeety yak.
// ...
// Optimization N: Blah bla blah... This should make run faster because
// yakkety yakeety yak.
// 
// Full credit solutions will describe 2-3 optimizations and describe
// WHY these improved performance in at least a couple sentences.
// 
// ####################### YOUR ANSWER HERE #########################
// Optimization 1: The first optimization that I made was that I changed the formula from the baseline formula, which iterates
// inefficiently because it iterates through colums a lot. I used the approach that was given to us by the write-up, which favors
//row-wise retrival. This goes down the row before having to go through a column, and C favors row wirse retrieval, so this works in our favor.
//By setting a lead variable, and then filling in an entire row before moving, on, time is saved. Even though you have to go through and set everything
//to 0 first, this only increases the time by n^2, which is insignificant to the n^3 later on in the program.
//Optimization 2: The second optimization that I made was that I derefenced matrix_t *mat and matrix_t *matsq so that I could use macros to directly access them.
//As the baseline uses a pointer, a pointer takes a lot longer since you have to go through the pointer before reteriving the data, so a direct access is more efficient.
//Later on, we can use macros like MSET instead of mset, which needs direct access, but is more efficient as well.

// ##################################################################
