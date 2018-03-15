/*
*   Author: Ibrahim Sardar
*   02/25/2018
*/

#include <iostream>
#include "math.h"
#include "matrix.h"

#define PI_MAX_ROWS 128
#define PI_MAX_COLS 2
#define PW_MAX_ROWS 128
#define PW_MAX_COLS 3


int main() {

    // STEP 1:
    // collect 2D image coordinates
    // collect 3D world coordinates

    // image coordinates
    double Pi[PI_MAX_ROWS][PI_MAX_COLS] = {
        {456,436},{455,509},{454,584},{454,656},{453,735},{452,807},{452,884},{452,959},
        {517,443},{516,512},{514,589},{514,660},{514,735},{513,809},{512,884},{514,957},
        {576,450},{577,519},{574,592},{574,663},{574,738},{573,809},{572,883},{573,956},
        {633,456},{633,525},{633,597},{632,667},{631,739},{631,810},{630,884},{630,954},
        {689,463},{689,531},{689,601},{687,671},{687,742},{687,811},{687,883},{686,953},
        {742,469},{742,536},{741,605},{740,672},{741,743},{740,813},{741,882},{740,951},
        {793,473},{793,541},{793,608},{793,676},{793,745},{793,813},{793,880},{793,951},
        {846,480},{847,546},{846,613},{843,679},{844,746},{843,813},{844,880},{843,949},
        {1030,477},{1029,543},{1028,608},{1029,677},{1031,743},{1032,811},{1034,880},{1034,946},
        {1079,470},{1079,537},{1079,607},{1079,672},{1079,743},{1080,811},{1079,879},{1079,948},
        {1126,463},{1127,532},{1127,601},{1128,669},{1129,740},{1129,810},{1129,880},{1129,949},
        {1175,456},{1178,525},{1178,597},{1179,667},{1180,738},{1182,808},{1181,880},{1183,951},
        {1227,448},{1229,520},{1230,592},{1232,663},{1234,736},{1234,807},{1234,880},{1234,952},
        {1284,442},{1282,512},{1284,587},{1287,659},{1288,733},{1287,806},{1287,880},{1288,953},
        {1339,434},{1339,507},{1342,582},{1343,656},{1344,730},{1344,805},{1344,880},{1346,954},
        {1399,426},{1399,501},{1400,576},{1401,653},{1402,727},{1402,804},{1403,880},{1403,956}
    };

    // world coordinates
    double Pw[PW_MAX_ROWS][PW_MAX_COLS] = {
        {18,0,0},{18,0,2},{18,0,4},{18,0,6},{18,0,8},{18,0,10},{18,0,12},{18,0,14},
        {16,0,0},{16,0,2},{16,0,4},{16,0,6},{16,0,8},{16,0,10},{16,0,12},{16,0,14},
        {14,0,0},{14,0,2},{14,0,4},{14,0,6},{14,0,8},{14,0,10},{14,0,12},{14,0,14},
        {12,0,0},{12,0,2},{12,0,4},{12,0,6},{12,0,8},{12,0,10},{12,0,12},{12,0,14},
        {10,0,0},{10,0,2},{10,0,4},{10,0,6},{10,0,8},{10,0,10},{10,0,12},{10,0,14},
        {8,0,0},{8,0,2},{8,0,4},{8,0,6},{8,0,8},{8,0,10},{8,0,12},{8,0,14},
        {6,0,0},{6,0,2},{6,0,4},{6,0,6},{6,0,8},{6,0,10},{6,0,12},{6,0,14},
        {4,0,0},{4,0,2},{4,0,4},{4,0,6},{4,0,8},{4,0,10},{4,0,12},{4,0,14},
        {0,4,0},{0,4,2},{0,4,4},{0,4,6},{0,4,8},{0,4,10},{0,4,12},{0,4,14},
        {0,6,0},{0,6,2},{0,6,4},{0,6,6},{0,6,8},{0,6,10},{0,6,12},{0,6,14},
        {0,8,0},{0,8,2},{0,8,4},{0,8,6},{0,8,8},{0,8,10},{0,8,12},{0,8,14},
        {0,10,0},{0,10,2},{0,10,4},{0,10,6},{0,10,8},{0,10,10},{0,10,12},{0,10,14},
        {0,12,0},{0,12,2},{0,12,4},{0,12,6},{0,12,8},{0,12,10},{0,12,12},{0,12,14},
        {0,14,0},{0,14,2},{0,14,4},{0,14,6},{0,14,8},{0,14,10},{0,14,12},{0,14,14},
        {0,16,0},{0,16,2},{0,16,4},{0,16,6},{0,16,8},{0,16,10},{0,16,12},{0,16,14},
        {0,18,0},{0,18,2},{0,18,4},{0,18,6},{0,18,8},{0,18,10},{0,18,12},{0,18,14}
    };

    // STEP 2:
    // FORM: Ax=b
    // A : 2n x 11 matrix to solve for the projection matrix
    // x : projection matrix in a column vector form 11 x 1 (solving for this)
    // b : image coordinate list in a column vector form 2n x 1

    Matrix A(2*PI_MAX_ROWS, 11); // 12); nope!
    for (int r=0; r<2*PI_MAX_ROWS; r++) {
        // Pw index
        int i = r / 2;
        // is row even?
        bool even = (r+1) % 2;
        // col 1
        int c = 0;
        A(r,c) = (even ? Pw[i][0] : 0); // xw1,0,xw2,0, ... xwn,0
        // col 2
        c++;
        A(r,c) = (even ? Pw[i][1] : 0); // yw1,0,yw2,0, ... ywn,0
        // col 3
        c++;
        A(r,c) = (even ? Pw[i][2] : 0); // zw1,0,zw2,0, ... zwn,0
        // col 4
        c++;
        A(r,c) = (even ? 1 : 0); // 1,0,1,0, ... 1,0
        // col 5
        c++;
        A(r,c) = (even ? 0 : Pw[i][0]); // 0,xw1,0,xw2, ... 0,xwn
        // col 6
        c++;
        A(r,c) = (even ? 0 : Pw[i][1]); // 0,yw1,0,yw2, ... 0,ywn
        // col 7
        c++;
        A(r,c) = (even ? 0 : Pw[i][2]); // 0,zw1,0,zw2, ... 0,zwn
        // col 8
        c++;
        A(r,c) = (even ? 0 : 1); // 0,1,0,1, ... 0,1
        // col 9
        c++;
        A(r,c) = (even ? -Pi[i][0]*Pw[i][0] : -Pi[i][1]*Pw[i][0]); // -xi1*xw1,-yi1*xw1, ... -xin*xwn,-yin*xwn
        // col 10
        c++;
        A(r,c) = (even ? -Pi[i][0]*Pw[i][1] : -Pi[i][1]*Pw[i][1]); // -xi1*yw1,-yi1*yw1, ... -xin*ywn,-yin*ywn
        // col 11
        c++;
        A(r,c) = (even ? -Pi[i][0]*Pw[i][2] : -Pi[i][1]*Pw[i][2]); // -xi1*zw1,-yi1*zw1, ... -xin*zwn,-yin*zwn
        // col 12 nope!
        //c++;
        //A(r,c) = ((r+1) % 2 ? -Pi[i][0] : -Pi[i][1]); // -xi1*1,-yi1*1,-xi2*1,-yi2*1, ... -xin*1,-yin*1
    }
    std::cout << "A:\n" << A << std::endl;

    Matrix b(2*PI_MAX_ROWS, 1);
    for (int r=0; r<2*PI_MAX_ROWS; r++) {
        for (int c=0; c<1; c++) {
            // Pi index
            int i = r / 2;
            // col 1
            b(r,c) = ((r+1) % 2 ? Pi[i][0] : Pi[i][1]); //xi1,yi1,xi2,yi2 ... xin,yin
        }
    }
    std::cout << "b:\n" << b << std::endl;

    // multiply the pseudo inverse of A to b to solve for x
    Matrix A_sudo_inv = A.transpose() * A;
    A_sudo_inv = A_sudo_inv.inverse() * A.transpose();
    Matrix x = A_sudo_inv * b;
    std::cout << "x:\n" << x << std::endl;

    // STEP 3:
    // INTRINSIC PARAMETERS (parameters that don't change if the camera moves or rotates)
    // FORM: P = K[R t] = [KR Kt]
    // P : projection matrix formed from x from step 2
    // K : intrinsic parameter matrix (solving for this)
    // R : extrinsic rotation matrix
    // t : extrinsic translation matrix
    // FORM: BBT = K*transpose(K)
    // BBT  : (K*R) * transpose(K*R)
    // BBTN : BBT / BBT[r=3][c=3]
    // - (GIVEN: SKEW=0, DISTORTION=0)
    // FORM: u0 = BBTN[r=1][c=3]
    // FORM: v0 = BBTN[r=2][c=3]
    // FORM: alpha = sqrt(BBTN[r=1][c=1] - u0*u0)
    // FORM: beta = sqrt(BBTN[r=2][c=2] - v0*v0)

    Matrix P(3,4);
    for (int r=0; r<3; r++) {
        for (int c=0; c<4; c++) {
            if (r==2 && c==3)
                P(r,c) = 1;
            else
                P(r,c) = x((r*4)+c,0);
        }
    }
    std::cout << "P:\n" << P << std::endl;

    Matrix KR(3,3);
    for (int r=0; r<3; r++) {
        for (int c=0; c<3; c++) {
            KR(r,c) = P(r,c);
        }
    }
    std::cout << "KR:\n" << KR << std::endl;

    Matrix Kt(3,1);
    for (int r=0; r<3; r++) {
        for (int c=3; c<4; c++) {
            Kt(r,0) = P(r,c);
        }
    }
    std::cout << "Kt:\n" << Kt << std::endl;

    Matrix BBT = KR * KR.transpose();
    BBT /= BBT(2,2); //normalize
    std::cout << "BBT:\n" << BBT << std::endl;

    double u0 = BBT(0,2);
    double v0 = BBT(1,2);
    double alpha = sqrt(BBT(0,0) - u0*u0);
    double beta = sqrt(BBT(1,1) - v0*v0);
    std::cout << "Intrinsics: " << "u0: " << u0 << ", "
                                << "v0: " << v0 << ", "
                                << "alpha: " << alpha << ", "
                                << "beta: " << beta << "\n" << std::endl;

    // STEP 4:
    // CONSTRUCT K (NO SKEW)

    Matrix K(3,3);
    K(0,0) = alpha;
    K(1,1) = beta;
    K(2,2) = 1;
    K(0,2) = u0;
    K(1,2) = v0;
    std::cout << "K:\n" << K << std::endl;

    // STEP 5:
    // EXTRINSIC PARAMTERS (parameters that change if the camera moves or rotates)
    // FORM: R = inverse(K) * KR
    // FORM: t = inverse(K) * Kt

    Matrix R = K.inverse() * KR;
    Matrix t = K.inverse() * Kt;
    std::cout << "Extrinsics: " << std::endl;
    std::cout << "Camera Rotation: \n" << R << std::endl;
    std::cout << "Camera Translation: \n" << t << std::endl;

    // STEP 6:
    // REPROJECTION
    // FORM: transpose(Pi_reprojected_coord) = P * transpose(Pw_coord)
    // Pi_reprojected : new set of image points from projection matrix from step 3

    std::cout << "2D coordinates after reprojection:" << std::endl;
    double Pi_reprojected[PI_MAX_ROWS][PI_MAX_COLS];
    for (int i=0; i<PI_MAX_ROWS; i++) {
        Matrix vec3D(4,1);
        vec3D(0,0) = Pw[i][0];
        vec3D(1,0) = Pw[i][1];
        vec3D(2,0) = Pw[i][2];
        vec3D(3,0) = 1;
        Matrix vec2D = P * vec3D;
        Pi_reprojected[i][0] = vec2D(0,0);
        Pi_reprojected[i][1] = vec2D(1,0);
        std::cout << vec2D(0,0) << ", " << vec2D(1,0) << "\n";
    }

    // STEP 7:
    // GENERATE BASIC STATISTICS
    // Mean Comparison
    // Variance Comparison
    // Standard Deviation comparison
    // Notable Trends: Shift

    std::cout << "Statistics: " << std::endl;

    double sum0[2]   = {0, 0}, sum1[2]   = {0, 0};
    double sumsq0[2]   = {0, 0}, sumsq1[2]   = {0, 0};
    double mean0[2]  = {0, 0}, mean1[2]  = {0, 0};
    double var0[2]   = {0, 0}, var1[2]   = {0, 0};
    double stdev0[2] = {0, 0}, stdev1[2] = {0, 0};
    double sum_shift[2] = {0, 0};
    double mean_shift[2] = {0, 0};

    for (int i=0; i<PI_MAX_ROWS; i++) {
        sum0[0] += Pi[i][0];
        sum0[1] += Pi[i][1];
        sum1[0] += Pi_reprojected[i][0];
        sum1[1] += Pi_reprojected[i][1];
    }

    mean0[0] = sum0[0] / PI_MAX_ROWS;
    mean0[1] = sum0[1] / PI_MAX_ROWS;
    mean1[0] = sum1[0] / PI_MAX_ROWS;
    mean1[1] = sum1[1] / PI_MAX_ROWS;
    std::cout << "Means:" << std::endl;
    std::cout << "\tOriginal x,y:  " << mean0[0] << ",  " << mean0[1] << "\n";
    std::cout << "\tReprojected x,y:  " << mean1[0] << ",  " << mean1[1] << std::endl;

    for (int i=0; i<PI_MAX_ROWS; i++) {
        sumsq0[0] += (Pi[i][0] - mean0[0])*(Pi[i][0] - mean0[0]);
        sumsq0[1] += (Pi[i][1] - mean0[1])*(Pi[i][1] - mean0[1]);
        sumsq1[0] += (Pi_reprojected[i][0] - mean1[0])*(Pi_reprojected[i][0] - mean1[0]);
        sumsq1[1] += (Pi_reprojected[i][1] - mean1[1])*(Pi_reprojected[i][1] - mean1[1]);
    }

    var0[0] = sumsq0[0] / (PI_MAX_ROWS-1);
    var0[1] = sumsq0[1] / (PI_MAX_ROWS-1);
    var1[0] = sumsq1[0] / (PI_MAX_ROWS-1);
    var1[1] = sumsq1[1] / (PI_MAX_ROWS-1);
    std::cout << "Variances:" << std::endl;
    std::cout << "\tOriginal x,y:  " << var0[0] << ",  " << var0[1] << "\n";
    std::cout << "\tReprojected x,y:  " << var1[0] << ",  " << var1[1] << std::endl;

    stdev0[0] = sqrt(var0[0]);
    stdev0[1] = sqrt(var0[1]);
    stdev1[0] = sqrt(var1[0]);
    stdev1[1] = sqrt(var1[1]);
    std::cout << "Standard Deviations:" << std::endl;
    std::cout << "\tOriginal x,y:  " << stdev0[0] << ",  " << stdev0[1] << "\n";
    std::cout << "\tReprojected x,y:  " << stdev1[0] << ",  " << stdev1[1] << std::endl;

    for (int i=0; i<PI_MAX_ROWS; i++) {
        sum_shift[0] += (Pi_reprojected[i][0] - Pi[i][0]);
        sum_shift[1] += (Pi_reprojected[i][1] - Pi[i][1]);
    }

    mean_shift[0] = sum_shift[0] / PI_MAX_ROWS;
    mean_shift[1] = sum_shift[1] / PI_MAX_ROWS;
    std::cout << "Average Shift (from old to new):" << std::endl;
    std::cout << "\tShift x,y:  " << mean_shift[0] << ",  " << mean_shift[1] << std::endl;

    return 0;
}
