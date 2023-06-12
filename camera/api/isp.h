#ifndef ISP_H
#define ISP_H

#include <string.h> // memset
#include <stdio.h>  // null 
#include <stdint.h>

#include "statistics.h"


// ---------------------------------- AE/AGC ------------------------------
float AE_compute_mean_skewness(global_stats_t *gstats);
uint8_t AE_is_adjusted(float sk);
uint8_t AE_compute_new_exposure(float exposure, float skewness);

// ---------------------------------- AWB ------------------------------
typedef struct {
    float alfa;
    float beta;
    float gamma;
} AWB_gains_t;

void AWB_compute_gains(global_stats_t *gstats, AWB_gains_t *gains);
void AWB_print_gains(AWB_gains_t *gains);
int8_t AWB_compute_filter_gain(int8_t coeff, float factor);


// ---------------------------------- GAMMA ------------------------------
extern const uint8_t gamma_1p8_s1[255];
void isp_gamma_stride1(const uint32_t buffsize, uint8_t *img);


// -------------------------- ROTATE/RESIZE -------------------------------------
void isp_bilinear_resize(
    const uint16_t in_width, 
    const uint16_t in_height, 
    uint8_t *img, 
    const uint16_t out_width, 
    const uint16_t out_height, 
    uint8_t *out_img);

void isp_rotate_image(const uint8_t *src, uint8_t *dest, int width, int height);

// -------------------------- COLOR CONVERSION -------------------------------------
// Macro arguments to get color components from packed result in the assembly program
#define GET_R(rgb) ((rgb >> 16) & 0xFF)
#define GET_G(rgb) ((rgb >> 8) & 0xFF)
#define GET_B(rgb) (rgb & 0xFF)

#define GET_Y(yuv) GET_R(yuv)
#define GET_U(yuv) GET_G(yuv)
#define GET_V(yuv) GET_B(yuv)

int yuv_to_rgb(
    int y, 
    int u, 
    int v);

int rgb_to_yuv(
    int r, 
    int g, 
    int b);

#endif // ISP_H
