//
// Created by abiel on 9/29/20.
//

#include "SixDOFQuadcopterModel.h"
#include <stdlib.h>

static const size_t A_ROWS = 12; //States x States
static const size_t A_COLS = 12;

static const size_t B_ROWS = 12; //States x Inputs
static const size_t B_COLS = 4;

static const size_t C_ROWS = 6; //Outputs x States
static const size_t C_COLS = 12;

static const size_t D_ROWS = 6; //Outputs x Inputs
static const size_t D_COLS = 4;

static void fillZeros(float * m, size_t rows, size_t cols){
    for(size_t i = 0; i < rows * cols; i++){
        m[i] = 0;
    }
}

static void setValue(float * m, size_t width, size_t row, size_t col, float val){
    m[width * col + row] = val;
}

void SixDOFQuadcopterModel_initialize(SixDOFQuadcopterModel *model){
    model->A = malloc(A_ROWS * A_COLS * sizeof(float));
    model->B = malloc(B_ROWS * B_COLS * sizeof(float));
    model->C = malloc(C_ROWS * C_COLS * sizeof(float));
    model->D = malloc(D_ROWS * D_COLS * sizeof(float));
}

//https://arxiv.org/pdf/1908.07401.pdf
void SixDOFQuadcopterModel_calculate(SixDOFQuadcopterModel *model, float g, float m, float lx, float ly, float lz){
    float* A = model->A;
    float* B = model->B;
    float* C = model->C;
    float* D = model->D;

    fillZeros(A, A_ROWS, A_COLS);
    fillZeros(B, B_ROWS, B_COLS);
    fillZeros(C, C_ROWS, C_COLS);
    fillZeros(D, D_ROWS, D_COLS);

    /**
     * A matrix definition
     */
    setValue(A, A_COLS, 0, 3, 1);
    setValue(A, A_COLS, 1, 4, 1);
    setValue(A, A_COLS, 2, 5, 1);
    setValue(A, A_COLS, 3, 7, -g);
    setValue(A, A_COLS, 4, 6, g);
    setValue(A, A_COLS, 6, 9, 1);
    setValue(A, A_COLS, 7, 10, 1);
    setValue(A, A_COLS, 8, 11, 1);

    /**
     * B matrix definition
     */
    setValue(B, B_COLS, 4, 0, 1.0f / m);
    setValue(B, B_COLS, 9, 1, 1.0f / lx);
    setValue(B, B_COLS, 10, 2, 1.0f / ly);
    setValue(B, B_COLS, 11, 3, 1.0f / lz);

    /**
     * C matrix definition
     */
     setValue(C, C_COLS, 0, 0, 1);
    setValue(C, C_COLS, 1, 1, 1);
    setValue(C, C_COLS, 2, 2, 1);
    setValue(C, C_COLS, 3, 6, 1);
    setValue(C, C_COLS, 4, 7, 1);
    setValue(C, C_COLS, 5, 8, 1);

    /**
     * D matrix definition
     */
     //Everything == 0
}