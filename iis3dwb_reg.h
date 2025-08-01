/**
  ******************************************************************************
  * @file    iis3dwb_reg.h
  * @author  Sensors Software Solution Team
  * @brief   This file contains all the functions prototypes for the
  *          iis3dwb_reg.c driver.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef IIS3DWB_REGS_H
#define IIS3DWB_REGS_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <stddef.h>
#include <math.h>

/** @addtogroup IIS3DWB
  * @{
  *
  */

/** @defgroup  Endianness definitions
  * @{
  *
  */

#ifndef DRV_BYTE_ORDER
#ifndef __BYTE_ORDER__

#define DRV_LITTLE_ENDIAN 1234
#define DRV_BIG_ENDIAN    4321

/** if _BYTE_ORDER is not defined, choose the endianness of your architecture
  * by uncommenting the define which fits your platform endianness
  */
//#define DRV_BYTE_ORDER    DRV_BIG_ENDIAN
#define DRV_BYTE_ORDER    DRV_LITTLE_ENDIAN

#else /* defined __BYTE_ORDER__ */

#define DRV_LITTLE_ENDIAN  __ORDER_LITTLE_ENDIAN__
#define DRV_BIG_ENDIAN     __ORDER_BIG_ENDIAN__
#define DRV_BYTE_ORDER     __BYTE_ORDER__

#endif /* __BYTE_ORDER__*/
#endif /* DRV_BYTE_ORDER */

/**
  * @}
  *
  */

/** @defgroup STMicroelectronics sensors common types
  * @{
  *
  */

#ifndef MEMS_SHARED_TYPES
#define MEMS_SHARED_TYPES

typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t bit0       : 1;
  uint8_t bit1       : 1;
  uint8_t bit2       : 1;
  uint8_t bit3       : 1;
  uint8_t bit4       : 1;
  uint8_t bit5       : 1;
  uint8_t bit6       : 1;
  uint8_t bit7       : 1;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t bit7       : 1;
  uint8_t bit6       : 1;
  uint8_t bit5       : 1;
  uint8_t bit4       : 1;
  uint8_t bit3       : 1;
  uint8_t bit2       : 1;
  uint8_t bit1       : 1;
  uint8_t bit0       : 1;
#endif /* DRV_BYTE_ORDER */
} bitwise_t;

#define PROPERTY_DISABLE                (0U)
#define PROPERTY_ENABLE                 (1U)

/** @addtogroup  Interfaces_Functions
  * @brief       This section provide a set of functions used to read and
  *              write a generic register of the device.
  *              MANDATORY: return 0 -> no Error.
  * @{
  *
  */

typedef int32_t (*stmdev_write_ptr)(void *, uint8_t, const uint8_t *, uint16_t);
typedef int32_t (*stmdev_read_ptr)(void *, uint8_t, uint8_t *, uint16_t);
typedef void (*stmdev_mdelay_ptr)(uint32_t millisec);

typedef struct
{
  /** Component mandatory fields **/
  stmdev_write_ptr  write_reg;
  stmdev_read_ptr   read_reg;
  /** Component optional fields **/
  stmdev_mdelay_ptr   mdelay;
  /** Customizable optional pointer **/
  void *handle;

  /** private data **/
  void *priv_data;
} stmdev_ctx_t;

/**
  * @}
  *
  */

#endif /* MEMS_SHARED_TYPES */

#ifndef MEMS_UCF_SHARED_TYPES
#define MEMS_UCF_SHARED_TYPES

/** @defgroup    Generic address-data structure definition
  * @brief       This structure is useful to load a predefined configuration
  *              of a sensor.
  *              You can create a sensor configuration by your own or using
  *              Unico / Unicleo tools available on STMicroelectronics
  *              web site.
  *
  * @{
  *
  */

typedef struct
{
  uint8_t address;
  uint8_t data;
} ucf_line_t;

/**
  * @}
  *
  */

#endif /* MEMS_UCF_SHARED_TYPES */

/**
  * @}
  *
  */

/** @defgroup IIS3DWB Infos
  * @{
  *
  */

/** I2C Device Address 8 bit format  if SA0=0 -> D5 if SA0=1 -> D7 **/
#define IIS3DWB_I2C_ADD_L                    0xD5U
#define IIS3DWB_I2C_ADD_H                    0xD7U

/** Device Identification (Who am I) **/
#define IIS3DWB_ID                           0x7BU

/**
  * @}
  *
  */

#define IIS3DWB_PIN_CTRL                     0x02U
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t not_used_01              : 6;
  uint8_t sdo_pu_en                : 1;
  uint8_t not_used_02              : 1;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t not_used_02              : 1;
  uint8_t sdo_pu_en                : 1;
  uint8_t not_used_01              : 6;
#endif /* DRV_BYTE_ORDER */
} iis3dwb_pin_ctrl_t;

#define IIS3DWB_FIFO_CTRL1                   0x07U
typedef struct
{
  uint8_t wtm                      : 8;
} iis3dwb_fifo_ctrl1_t;

#define IIS3DWB_FIFO_CTRL2                   0x08U
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t wtm                      : 1;
  uint8_t not_used_01              : 6;
  uint8_t stop_on_wtm              : 1;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t stop_on_wtm              : 1;
  uint8_t not_used_01              : 6;
  uint8_t wtm                      : 1;
#endif /* DRV_BYTE_ORDER */
} iis3dwb_fifo_ctrl2_t;

#define IIS3DWB_FIFO_CTRL3                   0x09U
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t bdr_xl                   : 4;
  uint8_t not_used_01              : 4;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t not_used_01              : 4;
  uint8_t bdr_xl                   : 4;
#endif /* DRV_BYTE_ORDER */
} iis3dwb_fifo_ctrl3_t;

#define IIS3DWB_FIFO_CTRL4                   0x0AU
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t fifo_mode                : 3;
  uint8_t not_used_01              : 1;
  uint8_t odr_t_batch              : 2;
  uint8_t odr_ts_batch             : 2;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t odr_ts_batch             : 2;
  uint8_t odr_t_batch              : 2;
  uint8_t not_used_01              : 1;
  uint8_t fifo_mode                : 3;
#endif /* DRV_BYTE_ORDER */
} iis3dwb_fifo_ctrl4_t;

#define IIS3DWB_COUNTER_BDR_REG1             0x0BU
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t cnt_bdr_th               : 3;
  uint8_t not_used_01              : 3;
  uint8_t rst_counter_bdr          : 1;
  uint8_t dataready_pulsed         : 1;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t dataready_pulsed         : 1;
  uint8_t rst_counter_bdr          : 1;
  uint8_t not_used_01              : 3;
  uint8_t cnt_bdr_th               : 3;
#endif /* DRV_BYTE_ORDER */
} iis3dwb_counter_bdr_reg1_t;

#define IIS3DWB_COUNTER_BDR_REG2             0x0CU
typedef struct
{
  uint8_t cnt_bdr_th               : 8;
} iis3dwb_counter_bdr_reg2_t;

#define IIS3DWB_INT1_CTRL                    0x0DU
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t int1_drdy_xl             : 1;
  uint8_t not_used_01              : 1;
  uint8_t int1_boot                : 1;
  uint8_t int1_fifo_th             : 1;
  uint8_t int1_fifo_ovr            : 1;
  uint8_t int1_fifo_full           : 1;
  uint8_t int1_cnt_bdr             : 1;
  uint8_t not_used_02              : 1;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t not_used_02              : 1;
  uint8_t int1_cnt_bdr             : 1;
  uint8_t int1_fifo_full           : 1;
  uint8_t int1_fifo_ovr            : 1;
  uint8_t int1_fifo_th             : 1;
  uint8_t int1_boot                : 1;
  uint8_t not_used_01              : 1;
  uint8_t int1_drdy_xl             : 1;
#endif /* DRV_BYTE_ORDER */
} iis3dwb_int1_ctrl_t;

#define IIS3DWB_INT2_CTRL                    0x0EU
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t int2_drdy_xl             : 1;
  uint8_t not_used_01              : 1;
  uint8_t int2_drdy_temp           : 1;
  uint8_t int2_fifo_th             : 1;
  uint8_t int2_fifo_ovr            : 1;
  uint8_t int2_fifo_full           : 1;
  uint8_t int2_cnt_bdr             : 1;
  uint8_t not_used_02              : 1;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t not_used_02              : 1;
  uint8_t int2_cnt_bdr             : 1;
  uint8_t int2_fifo_full           : 1;
  uint8_t int2_fifo_ovr            : 1;
  uint8_t int2_fifo_th             : 1;
  uint8_t int2_drdy_temp           : 1;
  uint8_t not_used_01              : 1;
  uint8_t int2_drdy_xl             : 1;
#endif /* DRV_BYTE_ORDER */
} iis3dwb_int2_ctrl_t;

#define IIS3DWB_WHO_AM_I                     0x0FU
#define IIS3DWB_CTRL1_XL                     0x10U
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t not_used_01              : 1;
  uint8_t lpf2_xl_en               : 1;
  uint8_t fs_xl                    : 2;
  uint8_t not_used_02              : 1;
  uint8_t xl_en                    : 3;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t xl_en                    : 3;
  uint8_t not_used_02              : 1;
  uint8_t fs_xl                    : 2;
  uint8_t lpf2_xl_en               : 1;
  uint8_t not_used_01              : 1;
#endif /* DRV_BYTE_ORDER */
} iis3dwb_ctrl1_xl_t;

#define IIS3DWB_CTRL3_C                      0x12U
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t sw_reset                 : 1;
  uint8_t not_used_01              : 1;
  uint8_t if_inc                   : 1;
  uint8_t sim                      : 1;
  uint8_t pp_od                    : 1;
  uint8_t h_lactive                : 1;
  uint8_t bdu                      : 1;
  uint8_t boot                     : 1;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t boot                     : 1;
  uint8_t bdu                      : 1;
  uint8_t h_lactive                : 1;
  uint8_t pp_od                    : 1;
  uint8_t sim                      : 1;
  uint8_t if_inc                   : 1;
  uint8_t not_used_01              : 1;
  uint8_t sw_reset                 : 1;
#endif /* DRV_BYTE_ORDER */
} iis3dwb_ctrl3_c_t;

#define IIS3DWB_CTRL4_C                      0x13U
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t _1ax_to_3regout          : 1;
  uint8_t lpf1_sel_g               : 1;
  uint8_t i2c_disable              : 1;
  uint8_t drdy_mask                : 1;
  uint8_t not_used_02              : 1;
  uint8_t int2_on_int1             : 1;
  uint8_t not_used_03              : 2;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t not_used_03              : 2;
  uint8_t int2_on_int1             : 1;
  uint8_t not_used_02              : 1;
  uint8_t drdy_mask                : 1;
  uint8_t i2c_disable              : 1;
  uint8_t lpf1_sel_g               : 1;
  uint8_t _1ax_to_3regout          : 1;
#endif /* DRV_BYTE_ORDER */
} iis3dwb_ctrl4_c_t;

#define IIS3DWB_CTRL5_C                      0x14U
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t st_xl                    : 2;
  uint8_t not_used_01              : 3;
  uint8_t rounding                 : 2;
  uint8_t not_used_02              : 1;
  uint8_t i2c_disable              : 1;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t i2c_disable              : 1;
  uint8_t not_used_02              : 1;
  uint8_t rounding                 : 2;
  uint8_t not_used_01              : 3;
  uint8_t st_xl                    : 2;
#endif /* DRV_BYTE_ORDER */
} iis3dwb_ctrl5_c_t;

#define IIS3DWB_CTRL6_C                      0x15U
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t xl_axis_sel              : 2;
  uint8_t not_used_01              : 1;
  uint8_t usr_off_w                : 1;
  uint8_t not_used_02              : 4;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t not_used_02              : 4;
  uint8_t usr_off_w                : 1;
  uint8_t not_used_01              : 1;
  uint8_t xl_axis_sel              : 2;
#endif /* DRV_BYTE_ORDER */
} iis3dwb_ctrl6_c_t;
#define IIS3DWB_CTRL7_C                      0x16U
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t not_used_01               : 1;
  uint8_t usr_off_on_out            : 1;
  uint8_t not_used_02               : 6;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t not_used_02               : 6;
  uint8_t usr_off_on_out            : 1;
  uint8_t not_used_01               : 1;
#endif /* DRV_BYTE_ORDER */
} iis3dwb_ctrl7_c_t;

#define IIS3DWB_CTRL8_XL                     0x17U
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t not_used_01              : 2;
  uint8_t fds                      : 1;
  uint8_t fastsettl_mode_xl        : 1;
  uint8_t hp_ref_mode_xl           : 1;
  uint8_t hpcf_xl                  : 3;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t hpcf_xl                  : 3;
  uint8_t hp_ref_mode_xl           : 1;
  uint8_t fastsettl_mode_xl        : 1;
  uint8_t fds                      : 1;
  uint8_t not_used_01              : 2;
#endif /* DRV_BYTE_ORDER */
} iis3dwb_ctrl8_xl_t;

#define IIS3DWB_CTRL10_C                     0x19U
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t not_used_01              : 5;
  uint8_t timestamp_en             : 1;
  uint8_t not_used_02              : 2;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t not_used_02              : 2;
  uint8_t timestamp_en             : 1;
  uint8_t not_used_01              : 5;
#endif /* DRV_BYTE_ORDER */
} iis3dwb_ctrl10_c_t;

#define IIS3DWB_ALL_INT_SRC                  0x1AU
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t not_used_01              : 1;
  uint8_t wu_ia                    : 1;
  uint8_t not_used_02              : 3;
  uint8_t sleep_change             : 1;
  uint8_t not_used_03              : 1;
  uint8_t timestamp_endcount       : 1;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t timestamp_endcount       : 1;
  uint8_t not_used_03              : 1;
  uint8_t sleep_change             : 1;
  uint8_t not_used_02              : 3;
  uint8_t wu_ia                    : 1;
  uint8_t not_used_01              : 1;
#endif /* DRV_BYTE_ORDER */
} iis3dwb_all_int_src_t;

#define IIS3DWB_WAKE_UP_SRC                  0x1BU
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t z_wu                     : 1;
  uint8_t y_wu                     : 1;
  uint8_t x_wu                     : 1;
  uint8_t wu_ia                    : 1;
  uint8_t sleep_state_ia           : 1;
  uint8_t not_used_01              : 1;
  uint8_t sleep_change_ia          : 1;
  uint8_t not_used_02              : 1;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t not_used_02              : 1;
  uint8_t sleep_change_ia          : 1;
  uint8_t not_used_01              : 1;
  uint8_t sleep_state_ia           : 1;
  uint8_t wu_ia                    : 1;
  uint8_t x_wu                     : 1;
  uint8_t y_wu                     : 1;
  uint8_t z_wu                     : 1;
#endif /* DRV_BYTE_ORDER */
} iis3dwb_wake_up_src_t;

#define IIS3DWB_STATUS_REG                   0x1EU
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t xlda                     : 1;
  uint8_t not_used_01              : 1;
  uint8_t tda                      : 1;
  uint8_t not_used_02              : 5;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t not_used_02              : 5;
  uint8_t tda                      : 1;
  uint8_t not_used_01              : 1;
  uint8_t xlda                     : 1;
#endif /* DRV_BYTE_ORDER */
} iis3dwb_status_reg_t;

#define IIS3DWB_OUT_TEMP_L                   0x20U
#define IIS3DWB_OUT_TEMP_H                   0x21U
#define IIS3DWB_OUTX_L_A                     0x28U
#define IIS3DWB_OUTX_H_A                     0x29U
#define IIS3DWB_OUTY_L_A                     0x2AU
#define IIS3DWB_OUTY_H_A                     0x2BU
#define IIS3DWB_OUTZ_L_A                     0x2CU
#define IIS3DWB_OUTZ_H_A                     0x2DU
#define IIS3DWB_FIFO_STATUS1                 0x3AU
typedef struct
{
  uint8_t diff_fifo                : 8;
} iis3dwb_fifo_status1_t;

#define IIS3DWB_FIFO_STATUS2                 0x3BU
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t diff_fifo                : 2;
  uint8_t not_used_01              : 1;
  uint8_t fifo_ovr_latched         : 1;
  uint8_t counter_bdr_ia           : 1;
  uint8_t fifo_full_ia             : 1;
  uint8_t fifo_ovr_ia              : 1;
  uint8_t fifo_wtm_ia              : 1;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t fifo_wtm_ia              : 1;
  uint8_t fifo_ovr_ia              : 1;
  uint8_t fifo_full_ia             : 1;
  uint8_t counter_bdr_ia           : 1;
  uint8_t fifo_ovr_latched         : 1;
  uint8_t not_used_01              : 1;
  uint8_t diff_fifo                : 2;
#endif /* DRV_BYTE_ORDER */
} iis3dwb_fifo_status2_t;

#define IIS3DWB_TIMESTAMP0                   0x40U
#define IIS3DWB_TIMESTAMP1                   0x41U
#define IIS3DWB_TIMESTAMP2                   0x42U
#define IIS3DWB_TIMESTAMP3                   0x43U
#define IIS3DWB_SLOPE_EN                     0x56U
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t lir                      : 1;
  uint8_t not_used_01              : 3;
  uint8_t slope_fds                : 1;
  uint8_t sleep_status_on_int      : 1;
  uint8_t not_used_02              : 2;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t not_used_02              : 2;
  uint8_t sleep_status_on_int      : 1;
  uint8_t slope_fds                : 1;
  uint8_t not_used_01              : 3;
  uint8_t lir                      : 1;
#endif /* DRV_BYTE_ORDER */
} iis3dwb_slope_en_t;

#define IIS3DWB_INTERRUPTS_EN                0x58U
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t not_used_01              : 7;
  uint8_t interrupts_enable        : 1;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t interrupts_enable        : 1;
  uint8_t not_used_01              : 7;
#endif /* DRV_BYTE_ORDER */
} iis3dwb_interrupts_en_t;

#define IIS3DWB_WAKE_UP_THS                  0x5BU
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t wk_ths                   : 6;
  uint8_t usr_off_on_wu            : 1;
  uint8_t not_used_01              : 1;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t not_used_01              : 1;
  uint8_t usr_off_on_wu            : 1;
  uint8_t wk_ths                   : 6;
#endif /* DRV_BYTE_ORDER */
} iis3dwb_wake_up_ths_t;

#define IIS3DWB_WAKE_UP_DUR                  0x5CU
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t sleep_dur                : 4;
  uint8_t wake_ths_w               : 1;
  uint8_t wake_dur                 : 2;
  uint8_t not_used_01              : 1;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t not_used_01              : 1;
  uint8_t wake_dur                 : 2;
  uint8_t wake_ths_w               : 1;
  uint8_t sleep_dur                : 4;
#endif /* DRV_BYTE_ORDER */
} iis3dwb_wake_up_dur_t;

#define IIS3DWB_MD1_CFG                      0x5EU
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t not_used_01              : 5;
  uint8_t int1_wu                  : 1;
  uint8_t not_used_02              : 1;
  uint8_t int1_sleep_change        : 1;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t int1_sleep_change        : 1;
  uint8_t not_used_02              : 1;
  uint8_t int1_wu                  : 1;
  uint8_t not_used_01              : 5;
#endif /* DRV_BYTE_ORDER */
} iis3dwb_md1_cfg_t;

#define IIS3DWB_MD2_CFG                      0x5FU
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t int2_timestamp           : 1;
  uint8_t not_used_01              : 4;
  uint8_t int2_wu                  : 1;
  uint8_t not_used_02              : 1;
  uint8_t int2_sleep_change        : 1;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t int2_sleep_change        : 1;
  uint8_t not_used_02              : 1;
  uint8_t int2_wu                  : 1;
  uint8_t not_used_01              : 4;
  uint8_t int2_timestamp           : 1;
#endif /* DRV_BYTE_ORDER */
} iis3dwb_md2_cfg_t;

#define IIS3DWB_INTERNAL_FREQ_FINE           0x63U
typedef struct
{
  uint8_t freq_fine                : 8;
} iis3dwb_internal_freq_fine_t;

#define IIS3DWB_X_OFS_USR                    0x73U
#define IIS3DWB_Y_OFS_USR                    0x74U
#define IIS3DWB_Z_OFS_USR                    0x75U
#define IIS3DWB_FIFO_DATA_OUT_TAG            0x78U
typedef struct
{
#if DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
  uint8_t tag_parity               : 1;
  uint8_t tag_cnt                  : 2;
  uint8_t tag_sensor               : 5;
#elif DRV_BYTE_ORDER == DRV_BIG_ENDIAN
  uint8_t tag_sensor               : 5;
  uint8_t tag_cnt                  : 2;
  uint8_t tag_parity               : 1;
#endif /* DRV_BYTE_ORDER */
} iis3dwb_fifo_data_out_tag_t;

#define IIS3DWB_FIFO_DATA_OUT_X_L            0x79U
#define IIS3DWB_FIFO_DATA_OUT_X_H            0x7AU
#define IIS3DWB_FIFO_DATA_OUT_Y_L            0x7BU
#define IIS3DWB_FIFO_DATA_OUT_Y_H            0x7CU
#define IIS3DWB_FIFO_DATA_OUT_Z_L            0x7DU
#define IIS3DWB_FIFO_DATA_OUT_Z_H            0x7EU

/**
  * @defgroup IIS3DWB_Register_Union
  * @brief    This union group all the registers having a bit-field
  *           description.
  *           This union is useful but it's not needed by the driver.
  *
  *           REMOVING this union you are compliant with:
  *           MISRA-C 2012 [Rule 19.2] -> " Union are not allowed "
  *
  * @{
  *
  */
typedef union
{
  iis3dwb_pin_ctrl_t                      pin_ctrl;
  iis3dwb_fifo_ctrl1_t                    fifo_ctrl1;
  iis3dwb_fifo_ctrl2_t                    fifo_ctrl2;
  iis3dwb_fifo_ctrl3_t                    fifo_ctrl3;
  iis3dwb_fifo_ctrl4_t                    fifo_ctrl4;
  iis3dwb_counter_bdr_reg1_t              counter_bdr_reg1;
  iis3dwb_counter_bdr_reg2_t              counter_bdr_reg2;
  iis3dwb_int1_ctrl_t                     int1_ctrl;
  iis3dwb_int2_ctrl_t                     int2_ctrl;
  iis3dwb_ctrl1_xl_t                      ctrl1_xl;
  iis3dwb_ctrl3_c_t                       ctrl3_c;
  iis3dwb_ctrl4_c_t                       ctrl4_c;
  iis3dwb_ctrl5_c_t                       ctrl5_c;
  iis3dwb_ctrl6_c_t                       ctrl6_c;
  iis3dwb_ctrl7_c_t                       ctrl7_c;
  iis3dwb_ctrl8_xl_t                      ctrl8_xl;
  iis3dwb_ctrl10_c_t                      ctrl10_c;
  iis3dwb_all_int_src_t                   all_int_src;
  iis3dwb_wake_up_src_t                   wake_up_src;
  iis3dwb_status_reg_t                    status_reg;
  iis3dwb_fifo_status1_t                  fifo_status1;
  iis3dwb_fifo_status2_t                  fifo_status2;
  iis3dwb_slope_en_t                      slope_en;
  iis3dwb_interrupts_en_t                 interrupts_en;
  iis3dwb_wake_up_ths_t                   wake_up_ths;
  iis3dwb_wake_up_dur_t                   wake_up_dur;
  iis3dwb_md1_cfg_t                       md1_cfg;
  iis3dwb_md2_cfg_t                       md2_cfg;
  iis3dwb_internal_freq_fine_t            internal_freq_fine;
  iis3dwb_fifo_data_out_tag_t             fifo_data_out_tag;
  bitwise_t                               bitwise;
  uint8_t                                 byte;
} iis3dwb_reg_t;

/**
  * @}
  *
  */

#ifndef __weak
#define __weak __attribute__((weak))
#endif /* __weak */

/*
 * These are the basic platform dependent I/O routines to read
 * and write device registers connected on a standard bus.
 * The driver keeps offering a default implementation based on function
 * pointers to read/write routines for backward compatibility.
 * The __weak directive allows the final application to overwrite
 * them with a custom implementation.
 */

int32_t iis3dwb_read_reg(const stmdev_ctx_t *ctx, uint8_t reg,
                         uint8_t *data,
                         uint16_t len);
int32_t iis3dwb_write_reg(const stmdev_ctx_t *ctx, uint8_t reg,
                          uint8_t *data,
                          uint16_t len);

float_t iis3dwb_from_fs2g_to_mg(int16_t lsb);
float_t iis3dwb_from_fs4g_to_mg(int16_t lsb);
float_t iis3dwb_from_fs8g_to_mg(int16_t lsb);
float_t iis3dwb_from_fs16g_to_mg(int16_t lsb);

extern float_t iis3dwb_from_lsb_to_celsius(int16_t lsb);

extern float_t iis3dwb_from_lsb_to_nsec(int32_t lsb);

typedef enum
{
  IIS3DWB_2g   = 0,
  IIS3DWB_16g  = 1, /* if XL_FS_MODE = '1' -> IIS3DWB_2g */
  IIS3DWB_4g   = 2,
  IIS3DWB_8g   = 3,
} iis3dwb_fs_xl_t;
int32_t iis3dwb_xl_full_scale_set(const stmdev_ctx_t *ctx,
                                  iis3dwb_fs_xl_t val);
int32_t iis3dwb_xl_full_scale_get(const stmdev_ctx_t *ctx,
                                  iis3dwb_fs_xl_t *val);

typedef enum
{
  IIS3DWB_XL_ODR_OFF    = 0,
  IIS3DWB_XL_ODR_26k7Hz = 5,
} iis3dwb_odr_xl_t;
int32_t iis3dwb_xl_data_rate_set(const stmdev_ctx_t *ctx,
                                 iis3dwb_odr_xl_t val);
int32_t iis3dwb_xl_data_rate_get(const stmdev_ctx_t *ctx,
                                 iis3dwb_odr_xl_t *val);

int32_t iis3dwb_block_data_update_set(const stmdev_ctx_t *ctx, uint8_t val);
int32_t iis3dwb_block_data_update_get(const stmdev_ctx_t *ctx,
                                      uint8_t *val);

typedef enum
{
  IIS3DWB_LSb_1mg  = 0,
  IIS3DWB_LSb_16mg = 1,
} iis3dwb_usr_off_w_t;
int32_t iis3dwb_xl_offset_weight_set(const stmdev_ctx_t *ctx,
                                     iis3dwb_usr_off_w_t val);
int32_t iis3dwb_xl_offset_weight_get(const stmdev_ctx_t *ctx,
                                     iis3dwb_usr_off_w_t *val);

typedef enum
{
  IIS3DWB_ENABLE_ALL  = 0,
  IIS3DWB_ONLY_X_ON_ONE_OUT_REG      = 0x01,
  IIS3DWB_ONLY_Y_ON_ONE_OUT_REG      = 0x02,
  IIS3DWB_ONLY_Z_ON_ONE_OUT_REG      = 0x03,
  IIS3DWB_ONLY_X_ON_ALL_OUT_REG      = 0x11,
  IIS3DWB_ONLY_Y_ON_ALL_OUT_REG      = 0x12,
  IIS3DWB_ONLY_Z_ON_ALL_OUT_REG      = 0x13,
} iis3dwb_xl_axis_sel_t;
int32_t iis3dwb_xl_axis_selection_set(const stmdev_ctx_t *ctx,
                                      iis3dwb_xl_axis_sel_t val);
int32_t iis3dwb_xl_axis_selection_get(const stmdev_ctx_t *ctx,
                                      iis3dwb_xl_axis_sel_t *val);

typedef struct
{
  iis3dwb_all_int_src_t       all_int_src;
  iis3dwb_wake_up_src_t       wake_up_src;
  iis3dwb_status_reg_t        status_reg;
} iis3dwb_all_sources_t;
int32_t iis3dwb_all_sources_get(const stmdev_ctx_t *ctx,
                                iis3dwb_all_sources_t *val);

int32_t iis3dwb_status_reg_get(const stmdev_ctx_t *ctx,
                               iis3dwb_status_reg_t *val);

int32_t iis3dwb_xl_flag_data_ready_get(const stmdev_ctx_t *ctx,
                                       uint8_t *val);

int32_t iis3dwb_temp_flag_data_ready_get(const stmdev_ctx_t *ctx,
                                         uint8_t *val);

int32_t iis3dwb_usr_offset_block_set(const stmdev_ctx_t *ctx, uint8_t val);
int32_t iis3dwb_usr_offset_block_get(const stmdev_ctx_t *ctx, uint8_t *val);

int32_t iis3dwb_xl_usr_offset_x_set(const stmdev_ctx_t *ctx, uint8_t *buff);
int32_t iis3dwb_xl_usr_offset_x_get(const stmdev_ctx_t *ctx, uint8_t *buff);

int32_t iis3dwb_xl_usr_offset_y_set(const stmdev_ctx_t *ctx, uint8_t *buff);
int32_t iis3dwb_xl_usr_offset_y_get(const stmdev_ctx_t *ctx, uint8_t *buff);

int32_t iis3dwb_xl_usr_offset_z_set(const stmdev_ctx_t *ctx, uint8_t *buff);
int32_t iis3dwb_xl_usr_offset_z_get(const stmdev_ctx_t *ctx, uint8_t *buff);

int32_t iis3dwb_xl_usr_offset_set(const stmdev_ctx_t *ctx, uint8_t val);
int32_t iis3dwb_xl_usr_offset_get(const stmdev_ctx_t *ctx, uint8_t *val);

int32_t iis3dwb_timestamp_rst(const stmdev_ctx_t *ctx);

int32_t iis3dwb_timestamp_set(const stmdev_ctx_t *ctx, uint8_t val);
int32_t iis3dwb_timestamp_get(const stmdev_ctx_t *ctx, uint8_t *val);

int32_t iis3dwb_timestamp_raw_get(const stmdev_ctx_t *ctx, uint32_t *val);

typedef enum
{
  IIS3DWB_NO_ROUND      = 0,
  IIS3DWB_ROUND         = 1,
} iis3dwb_rounding_t;
int32_t iis3dwb_rounding_mode_set(const stmdev_ctx_t *ctx,
                                  iis3dwb_rounding_t val);
int32_t iis3dwb_rounding_mode_get(const stmdev_ctx_t *ctx,
                                  iis3dwb_rounding_t *val);

int32_t iis3dwb_temperature_raw_get(const stmdev_ctx_t *ctx, int16_t *val);

int32_t iis3dwb_acceleration_raw_get(const stmdev_ctx_t *ctx, int16_t *val);

int32_t iis3dwb_odr_cal_reg_set(const stmdev_ctx_t *ctx, uint8_t val);
int32_t iis3dwb_odr_cal_reg_get(const stmdev_ctx_t *ctx, uint8_t *val);

typedef enum
{
  IIS3DWB_DRDY_LATCHED = 0,
  IIS3DWB_DRDY_PULSED  = 1,
} iis3dwb_dataready_pulsed_t;
int32_t iis3dwb_data_ready_mode_set(const stmdev_ctx_t *ctx,
                                    iis3dwb_dataready_pulsed_t val);
int32_t iis3dwb_data_ready_mode_get(const stmdev_ctx_t *ctx,
                                    iis3dwb_dataready_pulsed_t *val);

int32_t iis3dwb_device_id_get(const stmdev_ctx_t *ctx, uint8_t *buff);

int32_t iis3dwb_reset_set(const stmdev_ctx_t *ctx, uint8_t val);
int32_t iis3dwb_reset_get(const stmdev_ctx_t *ctx, uint8_t *val);

int32_t iis3dwb_auto_increment_set(const stmdev_ctx_t *ctx, uint8_t val);
int32_t iis3dwb_auto_increment_get(const stmdev_ctx_t *ctx, uint8_t *val);

int32_t iis3dwb_boot_set(const stmdev_ctx_t *ctx, uint8_t val);
int32_t iis3dwb_boot_get(const stmdev_ctx_t *ctx, uint8_t *val);

typedef enum
{
  IIS3DWB_XL_ST_DISABLE  = 0,
  IIS3DWB_XL_ST_POSITIVE = 1,
  IIS3DWB_XL_ST_NEGATIVE = 2,
} iis3dwb_st_xl_t;
int32_t iis3dwb_xl_self_test_set(const stmdev_ctx_t *ctx,
                                 iis3dwb_st_xl_t val);
int32_t iis3dwb_xl_self_test_get(const stmdev_ctx_t *ctx,
                                 iis3dwb_st_xl_t *val);

int32_t iis3dwb_filter_settling_mask_set(const stmdev_ctx_t *ctx,
                                         uint8_t val);
int32_t iis3dwb_filter_settling_mask_get(const stmdev_ctx_t *ctx,
                                         uint8_t *val);

typedef enum
{
  IIS3DWB_SLOPE_ODR_DIV_4           = 0x10,
  IIS3DWB_HP_REF_MODE               = 0x37,
  IIS3DWB_HP_ODR_DIV_10             = 0x11,
  IIS3DWB_HP_ODR_DIV_20             = 0x12,
  IIS3DWB_HP_ODR_DIV_45             = 0x13,
  IIS3DWB_HP_ODR_DIV_100            = 0x14,
  IIS3DWB_HP_ODR_DIV_200            = 0x15,
  IIS3DWB_HP_ODR_DIV_400            = 0x16,
  IIS3DWB_HP_ODR_DIV_800            = 0x17,
  IIS3DWB_LP_6k3Hz                  = 0x00,
  IIS3DWB_LP_ODR_DIV_4              = 0x80,
  IIS3DWB_LP_ODR_DIV_10             = 0x81,
  IIS3DWB_LP_ODR_DIV_20             = 0x82,
  IIS3DWB_LP_ODR_DIV_45             = 0x83,
  IIS3DWB_LP_ODR_DIV_100            = 0x84,
  IIS3DWB_LP_ODR_DIV_200            = 0x85,
  IIS3DWB_LP_ODR_DIV_400            = 0x86,
  IIS3DWB_LP_ODR_DIV_800            = 0x87,
} iis3dwb_filt_xl_en_t;
int32_t iis3dwb_xl_filt_path_on_out_set(const stmdev_ctx_t *ctx,
                                        iis3dwb_filt_xl_en_t val);
int32_t iis3dwb_xl_filt_path_on_out_get(const stmdev_ctx_t *ctx,
                                        iis3dwb_filt_xl_en_t *val);

int32_t iis3dwb_xl_fast_settling_set(const stmdev_ctx_t *ctx, uint8_t val);
int32_t iis3dwb_xl_fast_settling_get(const stmdev_ctx_t *ctx, uint8_t *val);

typedef enum
{
  IIS3DWB_USE_SLOPE = 0,
  IIS3DWB_USE_HPF   = 1,
} iis3dwb_slope_fds_t;
int32_t iis3dwb_xl_hp_path_internal_set(const stmdev_ctx_t *ctx,
                                        iis3dwb_slope_fds_t val);
int32_t iis3dwb_xl_hp_path_internal_get(const stmdev_ctx_t *ctx,
                                        iis3dwb_slope_fds_t *val);

typedef enum
{
  IIS3DWB_PULL_UP_DISC       = 0,
  IIS3DWB_PULL_UP_CONNECT    = 1,
} iis3dwb_sdo_pu_en_t;
int32_t iis3dwb_sdo_sa0_mode_set(const stmdev_ctx_t *ctx,
                                 iis3dwb_sdo_pu_en_t val);
int32_t iis3dwb_sdo_sa0_mode_get(const stmdev_ctx_t *ctx,
                                 iis3dwb_sdo_pu_en_t *val);

typedef enum
{
  IIS3DWB_SPI_4_WIRE = 0,
  IIS3DWB_SPI_3_WIRE = 1,
} iis3dwb_sim_t;
int32_t iis3dwb_spi_mode_set(const stmdev_ctx_t *ctx, iis3dwb_sim_t val);
int32_t iis3dwb_spi_mode_get(const stmdev_ctx_t *ctx, iis3dwb_sim_t *val);

typedef enum
{
  IIS3DWB_I2C_ENABLE  = 0,
  IIS3DWB_I2C_DISABLE = 1,
} iis3dwb_i2c_disable_t;
int32_t iis3dwb_i2c_interface_set(const stmdev_ctx_t *ctx,
                                  iis3dwb_i2c_disable_t val);
int32_t iis3dwb_i2c_interface_get(const stmdev_ctx_t *ctx,
                                  iis3dwb_i2c_disable_t *val);

typedef struct
{
  uint8_t drdy_xl       : 1; /* Accelerometer data ready */
  uint8_t boot          : 1; /* Restoring calibration parameters */
  uint8_t fifo_th       : 1; /* FIFO threshold reached */
  uint8_t fifo_ovr      : 1; /* FIFO overrun */
  uint8_t fifo_full     : 1; /* FIFO full */
  uint8_t fifo_bdr      : 1; /* FIFO Batch counter threshold reached */
  uint8_t wake_up       : 1; /* wake up event */
uint8_t sleep_change  :
  1; /* Act/Inact (or Vice-versa) status changed */
  uint8_t sleep_status  : 1; /* Act/Inact status */
} iis3dwb_pin_int1_route_t;
int32_t iis3dwb_pin_int1_route_set(const stmdev_ctx_t *ctx,
                                   iis3dwb_pin_int1_route_t *val);
int32_t iis3dwb_pin_int1_route_get(const stmdev_ctx_t *ctx,
                                   iis3dwb_pin_int1_route_t *val);

typedef struct
{
  uint8_t drdy_xl       : 1; /* Accelerometer data ready */
  uint8_t drdy_temp     : 1; /* Temperature data ready */
  uint8_t fifo_th       : 1; /* FIFO threshold reached */
  uint8_t fifo_ovr      : 1; /* FIFO overrun */
  uint8_t fifo_full     : 1; /* FIFO full */
  uint8_t fifo_bdr      : 1; /* FIFO Batch counter threshold reached */
  uint8_t timestamp     : 1; /* timestamp overflow */
  uint8_t wake_up       : 1; /* wake up event */
  uint8_t sleep_change  : 1; /* Act/Inact (or Vice-versa) status changed */
  uint8_t sleep_status  : 1; /* Act/Inact status */
} iis3dwb_pin_int2_route_t;
int32_t iis3dwb_pin_int2_route_set(const stmdev_ctx_t *ctx,
                                   iis3dwb_pin_int2_route_t *val);
int32_t iis3dwb_pin_int2_route_get(const stmdev_ctx_t *ctx,
                                   iis3dwb_pin_int2_route_t *val);

typedef enum
{
  IIS3DWB_PUSH_PULL   = 0,
  IIS3DWB_OPEN_DRAIN  = 1,
} iis3dwb_pp_od_t;
int32_t iis3dwb_pin_mode_set(const stmdev_ctx_t *ctx, iis3dwb_pp_od_t val);
int32_t iis3dwb_pin_mode_get(const stmdev_ctx_t *ctx, iis3dwb_pp_od_t *val);

typedef enum
{
  IIS3DWB_ACTIVE_HIGH = 0,
  IIS3DWB_ACTIVE_LOW  = 1,
} iis3dwb_h_lactive_t;
int32_t iis3dwb_pin_polarity_set(const stmdev_ctx_t *ctx,
                                 iis3dwb_h_lactive_t val);
int32_t iis3dwb_pin_polarity_get(const stmdev_ctx_t *ctx,
                                 iis3dwb_h_lactive_t *val);

int32_t iis3dwb_all_on_int1_set(const stmdev_ctx_t *ctx, uint8_t val);
int32_t iis3dwb_all_on_int1_get(const stmdev_ctx_t *ctx, uint8_t *val);

typedef enum
{
  IIS3DWB_INT_PULSED            = 0,
  IIS3DWB_INT_LATCHED           = 1,
} iis3dwb_lir_t;
int32_t iis3dwb_int_notification_set(const stmdev_ctx_t *ctx,
                                     iis3dwb_lir_t val);
int32_t iis3dwb_int_notification_get(const stmdev_ctx_t *ctx,
                                     iis3dwb_lir_t *val);

typedef enum
{
  IIS3DWB_LSb_FS_DIV_64       = 0,
  IIS3DWB_LSb_FS_DIV_256      = 1,
} iis3dwb_wake_ths_w_t;
int32_t iis3dwb_wkup_ths_weight_set(const stmdev_ctx_t *ctx,
                                    iis3dwb_wake_ths_w_t val);
int32_t iis3dwb_wkup_ths_weight_get(const stmdev_ctx_t *ctx,
                                    iis3dwb_wake_ths_w_t *val);

int32_t iis3dwb_wkup_threshold_set(const stmdev_ctx_t *ctx, uint8_t val);
int32_t iis3dwb_wkup_threshold_get(const stmdev_ctx_t *ctx, uint8_t *val);

int32_t iis3dwb_xl_usr_offset_on_wkup_set(const stmdev_ctx_t *ctx,
                                          uint8_t val);
int32_t iis3dwb_xl_usr_offset_on_wkup_get(const stmdev_ctx_t *ctx,
                                          uint8_t *val);

int32_t iis3dwb_wkup_dur_set(const stmdev_ctx_t *ctx, uint8_t val);
int32_t iis3dwb_wkup_dur_get(const stmdev_ctx_t *ctx, uint8_t *val);

int32_t iis3dwb_act_sleep_dur_set(const stmdev_ctx_t *ctx, uint8_t val);
int32_t iis3dwb_act_sleep_dur_get(const stmdev_ctx_t *ctx, uint8_t *val);

int32_t iis3dwb_fifo_watermark_set(const stmdev_ctx_t *ctx, uint16_t val);
int32_t iis3dwb_fifo_watermark_get(const stmdev_ctx_t *ctx, uint16_t *val);

int32_t iis3dwb_fifo_stop_on_wtm_set(const stmdev_ctx_t *ctx, uint8_t val);
int32_t iis3dwb_fifo_stop_on_wtm_get(const stmdev_ctx_t *ctx, uint8_t *val);

typedef enum
{
  IIS3DWB_XL_NOT_BATCHED          =  0,
  IIS3DWB_XL_BATCHED_AT_26k7Hz    = 10,
} iis3dwb_bdr_xl_t;
int32_t iis3dwb_fifo_xl_batch_set(const stmdev_ctx_t *ctx,
                                  iis3dwb_bdr_xl_t val);
int32_t iis3dwb_fifo_xl_batch_get(const stmdev_ctx_t *ctx,
                                  iis3dwb_bdr_xl_t *val);

typedef enum
{
  IIS3DWB_BYPASS_MODE             = 0,
  IIS3DWB_FIFO_MODE               = 1,
  IIS3DWB_STREAM_TO_FIFO_MODE     = 3,
  IIS3DWB_BYPASS_TO_STREAM_MODE   = 4,
  IIS3DWB_STREAM_MODE             = 6,
  IIS3DWB_BYPASS_TO_FIFO_MODE     = 7,
} iis3dwb_fifo_mode_t;
int32_t iis3dwb_fifo_mode_set(const stmdev_ctx_t *ctx,
                              iis3dwb_fifo_mode_t val);
int32_t iis3dwb_fifo_mode_get(const stmdev_ctx_t *ctx,
                              iis3dwb_fifo_mode_t *val);

typedef enum
{
  IIS3DWB_TEMP_NOT_BATCHED        = 0,
  IIS3DWB_TEMP_BATCHED_AT_104Hz   = 3,
} iis3dwb_odr_t_batch_t;
int32_t iis3dwb_fifo_temp_batch_set(const stmdev_ctx_t *ctx,
                                    iis3dwb_odr_t_batch_t val);
int32_t iis3dwb_fifo_temp_batch_get(const stmdev_ctx_t *ctx,
                                    iis3dwb_odr_t_batch_t *val);

typedef enum
{
  IIS3DWB_NO_DECIMATION = 0,
  IIS3DWB_DEC_1         = 1,
  IIS3DWB_DEC_8         = 2,
  IIS3DWB_DEC_32        = 3,
} iis3dwb_fifo_timestamp_batch_t;
int32_t iis3dwb_fifo_timestamp_batch_set(const stmdev_ctx_t *ctx,
                                              iis3dwb_fifo_timestamp_batch_t val);
int32_t iis3dwb_fifo_timestamp_batch_get(const stmdev_ctx_t *ctx,
                                              iis3dwb_fifo_timestamp_batch_t *val);

int32_t iis3dwb_rst_batch_counter_set(const stmdev_ctx_t *ctx, uint8_t val);
int32_t iis3dwb_rst_batch_counter_get(const stmdev_ctx_t *ctx,
                                      uint8_t *val);

int32_t iis3dwb_batch_counter_threshold_set(const stmdev_ctx_t *ctx,
                                            uint16_t val);
int32_t iis3dwb_batch_counter_threshold_get(const stmdev_ctx_t *ctx,
                                            uint16_t *val);

int32_t iis3dwb_fifo_data_level_get(const stmdev_ctx_t *ctx, uint16_t *val);

typedef struct
{
  uint16_t fifo_level : 10;
  uint8_t fifo_bdr : 1;
  uint8_t fifo_full : 1;
  uint8_t fifo_ovr : 1;
  uint8_t fifo_th : 1;
} iis3dwb_fifo_status_t;
int32_t iis3dwb_fifo_status_get(const stmdev_ctx_t *ctx,
                                iis3dwb_fifo_status_t *val);

typedef struct
{
  uint8_t tag;
  uint8_t data[6];
} iis3dwb_fifo_out_raw_t;
int32_t iis3dwb_fifo_out_raw_get(const stmdev_ctx_t *ctx, iis3dwb_fifo_out_raw_t *val);
int32_t iis3dwb_fifo_out_multi_raw_get(const stmdev_ctx_t *ctx,
                                       iis3dwb_fifo_out_raw_t *fdata,
                                       uint16_t num);

typedef enum
{
  IIS3DWB_XL_TAG = 2,
  IIS3DWB_TEMPERATURE_TAG,
  IIS3DWB_TIMESTAMP_TAG,
} iis3dwb_fifo_tag_t;
int32_t iis3dwb_fifo_sensor_tag_get(const stmdev_ctx_t *ctx,
                                    iis3dwb_fifo_tag_t *val);

/**
  *@}
  *
  */

#ifdef __cplusplus
}
#endif

#endif /* IIS3DWB_REGS_H */
