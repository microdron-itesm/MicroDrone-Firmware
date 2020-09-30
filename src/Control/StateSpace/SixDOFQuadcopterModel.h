//
// Created by abiel on 9/29/20.
//

#ifndef MICRODRONEFIRMWARE_QUADCOPTERMODEL_H
#define MICRODRONEFIRMWARE_QUADCOPTERMODEL_H

typedef struct SixDOFQuadcopterModel_s {
    float *A;
    float *B;
    float *C;
    float *D;
} SixDOFQuadcopterModel;

//Allocates memory needed to store the model
void SixDOFQuadcopterModel_initialize(SixDOFQuadcopterModel *model);

void SixDOFQuadcopterModel_calculate(SixDOFQuadcopterModel *model, float g, float m, float lx, float ly, float lz);

#endif //MICRODRONEFIRMWARE_QUADCOPTERMODEL_H
