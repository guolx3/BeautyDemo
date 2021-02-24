/********************************************************************
 * Copyright (c) 2019-2020 Oplus. All Rights Reserved.
 * File              : op_beauty_common.h
 * Version           : 1.0
 * Description       : face beauty algo
 * Date              : 2020/10/16
 * Author            : ouyangdan@Camera
 * -------------Revision History-----------------------------------------
 * <version>      <date>           <author>             <desc>
 * 1.0          2020/10/16      ouyangdan@Camera   face beauty algo
 * Oplus Mobile Comm Proprietary and Confidential.
 *********************************************************************/
#ifndef _OP_BEAUTY_COMMON_H_
#define _OP_BEAUTY_COMMON_H_

#include <stdio.h>

#define RESERVE_NUM1                                        3
#define RESERVE_NUM2                                        18
#define RESERVE_NUM3                                        18

#define OPLUS_FB_FEATURE_NO_FEATURE                         0x00000000
#define OPLUS_FB_GPU_FEATURE_FACE_DEBLEMISH                 1 << 1
#define OPLUS_FB_CPU_FEATURE_FACE_DEBLEMISH                 1 << 2
#define OPLUS_FB_GPU_FEATURE_FACE_SOFTEN                    1 << 3
#define OPLUS_FB_CPU_FEATURE_FACE_SOFTEN                    1 << 4
#define OPLUS_FB_GPU_FEATURE_FACE_WHITEN                    1 << 5
#define OPLUS_FB_CPU_FEATURE_FACE_WHITEN                    1 << 6
#define OPLUS_FB_GPU_FEATURE_FACE_MORPH                     1 << 7
#define OPLUS_FB_GPU_FEATURE_FACE_SHADOW                    1 << 8
#define OPLUS_FB_GPU_FEATURE_FACE_HIGHLIGHT                 1 << 9
#define OPLUS_FB_GPU_FEATURE_FACE_EYEBROWN                  1 << 10
#define OPLUS_FB_GPU_FEATURE_FACE_BLUSH                     1 << 11
#define OPLUS_FB_GPU_FEATURE_LIP_BEAUTY                     1 << 12
#define OPLUS_FB_GPU_FEATURE_EYE_ENHANCE                    1 << 13
#define OPLUS_FB_GPU_FEATURE_EYE_DEPOUCH                    1 << 14
#define OPLUS_FB_GPU_FEATURE_FACE_DEFOLDS                   1 << 15
#define OPLUS_FB_GPU_FEATURE_BEARD_ENHANCE                  1 << 16
#define OPLUS_FB_GPU_FEATURE_UNIFY_COLOR                    1 << 17
#define OPLUS_FB_GPU_FEATURE_MAKE_DOWNSCALE                 1 << 18
#define OPLUS_FB_GPU_FEATURE_HIGH_DOWNSCALE                 1 << 19

#define OPLUS_FB_DSP_FEATURE_AI_DEBLEMISH                   1 << 29
#define OPLUS_FB_DSP_FEATURE_SKIN_DETECT                    1 << 30


#define SKIN_SOFTEN_TYPE_0 0    // highPass
#define SKIN_SOFTEN_TYPE_1 1    // meanFilter
#define SKIN_SOFTEN_TYPE2_0 0   // high quality
#define SKIN_SOFTEN_TYPE2_1 1   // high performance
#define SKIN_WHITEN_TYPE_0 0    // more bright
#define SKIN_WHITEN_TYPE_1 1    // less bright-multi LUT
#define SKIN_WHITEN_TYPE_2 2    // less bright-single LUT

#ifdef __cplusplus
extern "C" {
#endif

#define SLENDER2D_OK 1

typedef void * op_handle_t;
typedef int op_result_t;

typedef enum {
    IMAGE_TYPE_NV12 = 0,
    IMAGE_TYPE_NV21,
    IMAGE_TYPE_RGBA,
    IMAGE_TYPE_GRAY,
    IMAGE_TYPE_MAX
} op_image_type_t;

typedef enum {
    NORMAL,
    BACK_LIGHT,
    HIGH_COLOR_TEMPERATURE,
    LOW_COLOR_TEMPERATURE,
    MAX_SCENE_NUM = 4,
} fbScene_t;

typedef enum {
    LUT_NORMAL = 0,
    LUT_BACK_LIGHT,
    LUT_HIGH_COLOR_TEMPERATURE,
    LUT_LOW_COLOR_TEMPERATURE,
    LUT_BRIGHT_NORMAL,
    LUT_TYPE_MAX
} lutType_t;

typedef enum {
    DODGE_BURN = 0,
    FREQ_SEPARATE_NormType,
    FREQ_SEPARATE_MixType,
    SOFTEN_TYPE_MAX
} softenType_t;

typedef enum {
    REGION_TPYE_ASIAN = 0,
    REGION_TPYE_INDIAN,
    REGION_TPYE_EUROPEAN,
    REGION_TPYE_MAX
} regionType_t;

typedef struct op_point3f_t {
    int x;
    int y;
    int z;
} op_point3f_t;

typedef struct op_beauty_param_t {
    int SkinSoften;
    int SkinWhiten;
    int HigherNose;
    int NarrowNose;
    int EnlargeEyes;
    int SlimFace;
    int SmallFace;
    int CheekBone;
    int DragChin;
    int Shadow;
    int Makeup;
    int EyeBrown;
    int LipsPink;
    int TeethWhite;
    int Deblemish;
    int Depouch;
    int EyeBright;
    int SoftenSharp;
    int EyeSharp;
    int Defolds;
    int PupilBright;
    int ProtectTilak;
    int BeardSharp;
    int UnifyColor;
    int nReserve[RESERVE_NUM1];
} op_beauty_params_t;

typedef struct op_init_data_t {
    int width;
    int height;
    int stride;
    int scanline;
    int zoomFlag;
    int versionID;
    int region;
    int isMakeupFlag;                        //no makeup : 0 ; else : 1
    int isSkintuneFlag;                      //no soften&whiten : 0 ; else : 1
    char * path;
    int featureFlag;
    int skinsoftenType;                      //highPass : 0 ; meanFilter : 1; mean+surface : 2
    int skinsoftenType2;                     //high quality : 0 ; high performance : 1
    int skinwhitenType;                      //18115 more bright : 0; logan less bright : 1; back sensor : 2;
    char * shaderPath;                       // Preview shader bin path
    int format;
    int nReserve[RESERVE_NUM2];
} op_init_data_t;

typedef struct op_depth_data_t {
    float * depth;
    int dep_width;
    int dep_height;
} op_depth_data_t;

typedef struct op_image_data_t {
    void * bufferY;
    void * bufferUV;
    int yuv_type;
    int image_width;
    int image_height;
    int image_stride;
    int image_scanline;
} op_image_data_t;

typedef struct op_param_data_t {
    int region;
    int face_num;
    int * gender;
    int * race;
    char * path;
    op_point3f_t * ffd_points;
    op_beauty_params_t * param;
    int hdr_flag;
    int cct_value;
    int iso_value;
    bool video_flag;                    //video, true : only soften&whiten
    bool sticker_flag;                  //for MTK, true : close some makeup function
    bool efficent_flag;                 //for MTK P70, true : close highlight function
    int skinLutType;
    bool contourOptiFlag;               // contour optimization, true : open, flase : close;
    int nReserve[RESERVE_NUM3];
} op_param_data_t;

typedef struct op_AIMask_data_t {
    uint8_t * pBuffer;
    int channel;
    int maskWidth;
    int maskHeight;
    int maskStride;
    int maskScanline;
} op_AIMask_data_t;

#ifdef __cplusplus
}
#endif

#endif // end of _OP_BEAUTY_COMMON_H_
