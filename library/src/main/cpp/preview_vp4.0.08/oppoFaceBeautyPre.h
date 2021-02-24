#ifndef _OPPOFACEBEAUTYPRE_H_
#define _OPPOFACEBEAUTYPRE_H_

#include "op_beauty_common.h"

#ifdef __cplusplus
extern "C" {
#endif

#define ZOOM_FLAG_OFF 0
#define ZOOM_FLAG_ON  1

op_handle_t Slender2D_init(op_init_data_t * initData);

op_result_t Slender2D_process(op_handle_t handle, int textureIn, int * textureOut, op_param_data_t * paramData);

float Slender2D_getZoomScale();

op_result_t Slender2D_Reset(op_handle_t handle);

op_result_t Slender2D_destory(op_handle_t handle);

#ifdef __cplusplus
}
#endif

#endif
