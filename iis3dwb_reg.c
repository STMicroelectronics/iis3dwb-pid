/**
  ******************************************************************************
  * @file    iis3dwb_reg.c
  * @author  Sensors Software Solution Team
  * @brief   IIS3DWB driver file
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

#include "iis3dwb_reg.h"
#include <string.h>

/**
  * @defgroup    IIS3DWB
  * @brief       This file provides a set of functions needed to drive the
  *              iis3dwb enhanced inertial module.
  * @{
  *
  */

/**
  * @defgroup    IIS3DWB_Interfaces_Functions
  * @brief       This section provide a set of functions used to read and
  *              write a generic register of the device.
  *              MANDATORY: return 0 -> no Error.
  * @{
  *
  */

/**
  * @brief  Read generic device register
  *
  * @param  ctx   read / write interface definitions(ptr)
  * @param  reg   register to read
  * @param  data  pointer to buffer that store the data read(ptr)
  * @param  len   number of consecutive register to read
  * @retval       interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t __weak iis3dwb_read_reg(const stmdev_ctx_t *ctx, uint8_t reg,
                                uint8_t *data,
                                uint16_t len)
{
  if (ctx == NULL) return -1;

  return ctx->read_reg(ctx->handle, reg, data, len);
}

/**
  * @brief  Write generic device register
  *
  * @param  ctx   read / write interface definitions(ptr)
  * @param  reg   register to write
  * @param  data  pointer to data to write in register reg(ptr)
  * @param  len   number of consecutive register to write
  * @retval       interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t __weak iis3dwb_write_reg(const stmdev_ctx_t *ctx, uint8_t reg,
                                 uint8_t *data,
                                 uint16_t len)
{
  if (ctx == NULL) return -1;

  return ctx->write_reg(ctx->handle, reg, data, len);
}

/**
  * @}
  *
  */

/**
  * @defgroup  Private functions
  * @brief     Section collect all the utility functions needed by APIs.
  * @{
  *
  */

static void bytecpy(uint8_t *target, const uint8_t *source)
{
  if ((target != NULL) && (source != NULL))
  {
    *target = *source;
  }
}

/**
  * @}
  *
  */

/**
  * @defgroup    IIS3DWB_Sensitivity
  * @brief       These functions convert raw-data into engineering units.
  * @{
  *
  */

float_t iis3dwb_from_fs2g_to_mg(int16_t lsb)
{
  return ((float_t)lsb * 0.061f);
}

float_t iis3dwb_from_fs4g_to_mg(int16_t lsb)
{
  return ((float_t)lsb * 0.122f);
}

float_t iis3dwb_from_fs8g_to_mg(int16_t lsb)
{
  return ((float_t)lsb * 0.244f);
}

float_t iis3dwb_from_fs16g_to_mg(int16_t lsb)
{
  return ((float_t)lsb * 0.488f);
}

float_t iis3dwb_from_lsb_to_celsius(int16_t lsb)
{
  return (((float_t)lsb / 256.0f) + 25.0f);
}

float_t iis3dwb_from_lsb_to_nsec(int32_t lsb)
{
  return ((float_t)lsb * 25000.0f);
}

/**
  * @}
  *
  */

/**
  * @defgroup   LSM9DS1_Data_generation
  * @brief      This section groups all the functions concerning data
  *             generation
  * @{
  *
  */

/**
  * @brief  Accelerometer full-scale selection[set]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of fs_xl in reg CTRL1_XL
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t iis3dwb_xl_full_scale_set(const stmdev_ctx_t *ctx,
                                  iis3dwb_fs_xl_t val)
{
  iis3dwb_ctrl1_xl_t ctrl1_xl;

  int32_t ret = iis3dwb_read_reg(ctx, IIS3DWB_CTRL1_XL, (uint8_t *)&ctrl1_xl, 1);

  if (ret == 0)
  {
    ctrl1_xl.fs_xl = (uint8_t)val;
    ret = iis3dwb_write_reg(ctx, IIS3DWB_CTRL1_XL,
                            (uint8_t *)&ctrl1_xl, 1);
  }

  return ret;
}

/**
  * @brief  Accelerometer full-scale selection.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Get the values of fs_xl in reg CTRL1_XL
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t iis3dwb_xl_full_scale_get(const stmdev_ctx_t *ctx,
                                  iis3dwb_fs_xl_t *val)
{
  iis3dwb_ctrl1_xl_t ctrl1_xl;

  const int32_t ret = iis3dwb_read_reg(ctx, IIS3DWB_CTRL1_XL, (uint8_t *)&ctrl1_xl, 1);

  switch (ctrl1_xl.fs_xl)
  {
    case IIS3DWB_2g:
      *val = IIS3DWB_2g;
      break;

    case IIS3DWB_16g:
      *val = IIS3DWB_16g;
      break;

    case IIS3DWB_4g:
      *val = IIS3DWB_4g;
      break;

    case IIS3DWB_8g:
      *val = IIS3DWB_8g;
      break;

    default:
      *val = IIS3DWB_2g;
      break;
  }

  return ret;
}

/**
  * @brief  Accelerometer UI data rate selection.[set]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of xl_en in reg CTRL1_XL
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t iis3dwb_xl_data_rate_set(const stmdev_ctx_t *ctx,
                                 iis3dwb_odr_xl_t val)
{
  iis3dwb_ctrl1_xl_t ctrl1_xl;

  int32_t ret = iis3dwb_read_reg(ctx, IIS3DWB_CTRL1_XL, (uint8_t *)&ctrl1_xl, 1);

  if (ret == 0)
  {
    ctrl1_xl.xl_en = (uint8_t)val;
    ret = iis3dwb_write_reg(ctx, IIS3DWB_CTRL1_XL,
                            (uint8_t *)&ctrl1_xl, 1);
  }

  return ret;
}

/**
  * @brief  Accelerometer UI data rate selection.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Get the values of odr_xl in reg CTRL1_XL
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t iis3dwb_xl_data_rate_get(const stmdev_ctx_t *ctx,
                                 iis3dwb_odr_xl_t *val)
{
  iis3dwb_ctrl1_xl_t ctrl1_xl;

  const int32_t ret = iis3dwb_read_reg(ctx, IIS3DWB_CTRL1_XL, (uint8_t *)&ctrl1_xl, 1);

  switch (ctrl1_xl.xl_en)
  {
    case IIS3DWB_XL_ODR_OFF:
      *val = IIS3DWB_XL_ODR_OFF;
      break;

    case IIS3DWB_XL_ODR_26k7Hz:
      *val = IIS3DWB_XL_ODR_26k7Hz;
      break;

    default:
      *val = IIS3DWB_XL_ODR_OFF;
      break;
  }

  return ret;
}

/**
  * @brief  Block data update.[set]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of bdu in reg CTRL3_C
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t iis3dwb_block_data_update_set(const stmdev_ctx_t *ctx, uint8_t val)
{
  iis3dwb_ctrl3_c_t ctrl3_c;

  int32_t ret = iis3dwb_read_reg(ctx, IIS3DWB_CTRL3_C, (uint8_t *)&ctrl3_c, 1);

  if (ret == 0)
  {
    ctrl3_c.bdu = (uint8_t)val;
    ret = iis3dwb_write_reg(ctx, IIS3DWB_CTRL3_C, (uint8_t *)&ctrl3_c, 1);
  }

  return ret;
}

/**
  * @brief  Block data update.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of bdu in reg CTRL3_C
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t iis3dwb_block_data_update_get(const stmdev_ctx_t *ctx, uint8_t *val)
{
  iis3dwb_ctrl3_c_t ctrl3_c;

  const int32_t ret = iis3dwb_read_reg(ctx, IIS3DWB_CTRL3_C, (uint8_t *)&ctrl3_c, 1);
  *val = ctrl3_c.bdu;

  return ret;
}

/**
  * @brief  Weight of XL user offset bits of registers X_OFS_USR (73h),
  *         Y_OFS_USR (74h), Z_OFS_USR (75h).[set]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of usr_off_w in reg CTRL6_C
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t iis3dwb_xl_offset_weight_set(const stmdev_ctx_t *ctx,
                                     iis3dwb_usr_off_w_t val)
{
  iis3dwb_ctrl6_c_t ctrl6_c;

  int32_t ret = iis3dwb_read_reg(ctx, IIS3DWB_CTRL6_C, (uint8_t *)&ctrl6_c, 1);

  if (ret == 0)
  {
    ctrl6_c.usr_off_w = (uint8_t)val;
    ret = iis3dwb_write_reg(ctx, IIS3DWB_CTRL6_C, (uint8_t *)&ctrl6_c, 1);
  }

  return ret;
}

/**
  * @brief  Weight of XL user offset bits of registers X_OFS_USR (73h),
  *         Y_OFS_USR (74h), Z_OFS_USR (75h).[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Get the values of usr_off_w in reg CTRL6_C
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t iis3dwb_xl_offset_weight_get(const stmdev_ctx_t *ctx,
                                     iis3dwb_usr_off_w_t *val)
{
  iis3dwb_ctrl6_c_t ctrl6_c;

  const int32_t ret = iis3dwb_read_reg(ctx, IIS3DWB_CTRL6_C, (uint8_t *)&ctrl6_c, 1);

  switch (ctrl6_c.usr_off_w)
  {
    case IIS3DWB_LSb_1mg:
      *val = IIS3DWB_LSb_1mg;
      break;

    case IIS3DWB_LSb_16mg:
      *val = IIS3DWB_LSb_16mg;
      break;

    default:
      *val = IIS3DWB_LSb_1mg;
      break;
  }

  return ret;
}

/**
  * @brief  select accelerometer axis.[set]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of xl_axis_sel in reg CTRL6_C and
  *                the values of _1ax_to_3regout in reg CTRL4_C
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t iis3dwb_xl_axis_selection_set(const stmdev_ctx_t *ctx,
                                      iis3dwb_xl_axis_sel_t val)
{
  iis3dwb_ctrl4_c_t ctrl4_c;
  iis3dwb_ctrl6_c_t ctrl6_c;

  int32_t ret = iis3dwb_read_reg(ctx, IIS3DWB_CTRL4_C, (uint8_t *)&ctrl4_c, 1);

  if (ret == 0)
  {
    ctrl4_c._1ax_to_3regout = ((uint8_t)val & 0x10U) >> 4;
    ret = iis3dwb_write_reg(ctx, IIS3DWB_CTRL4_C, (uint8_t *)&ctrl4_c, 1);
  }

  if (ret == 0)
  {
    ret = iis3dwb_read_reg(ctx, IIS3DWB_CTRL6_C, (uint8_t *)&ctrl6_c, 1);
  }

  if (ret == 0)
  {
    ctrl6_c.xl_axis_sel = (uint8_t)val;
    ret = iis3dwb_write_reg(ctx, IIS3DWB_CTRL6_C, (uint8_t *)&ctrl6_c, 1);
  }

  return ret;
}

/**
  * @brief  select accelerometer axis.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Get the values of xl_axis_sel in reg CTRL6_C and
  *                the values of _1ax_to_3regout in reg CTRL4_C.(ptr)
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t iis3dwb_xl_axis_selection_get(const stmdev_ctx_t *ctx,
                                      iis3dwb_xl_axis_sel_t *val)
{
  iis3dwb_ctrl4_c_t ctrl4_c;
  iis3dwb_ctrl6_c_t ctrl6_c;

  *val = IIS3DWB_ENABLE_ALL;

  int32_t ret = iis3dwb_read_reg(ctx, IIS3DWB_CTRL4_C, (uint8_t *)&ctrl4_c, 1);
  if (ret != 0) { return ret; }

  ret = iis3dwb_read_reg(ctx, IIS3DWB_CTRL6_C, (uint8_t *)&ctrl6_c, 1);
  if (ret != 0) { return ret; }

  switch ((ctrl4_c._1ax_to_3regout << 4) + ctrl6_c.xl_axis_sel)
  {
    case IIS3DWB_ENABLE_ALL:
      *val = IIS3DWB_ENABLE_ALL;
      break;

    case IIS3DWB_ONLY_X_ON_ONE_OUT_REG:
      *val = IIS3DWB_ONLY_X_ON_ONE_OUT_REG;
      break;

    case IIS3DWB_ONLY_Y_ON_ONE_OUT_REG:
      *val = IIS3DWB_ONLY_Y_ON_ONE_OUT_REG;
      break;

    case IIS3DWB_ONLY_Z_ON_ONE_OUT_REG:
      *val = IIS3DWB_ONLY_Z_ON_ONE_OUT_REG;
      break;

    case IIS3DWB_ONLY_X_ON_ALL_OUT_REG:
      *val = IIS3DWB_ONLY_X_ON_ALL_OUT_REG;
      break;

    case IIS3DWB_ONLY_Y_ON_ALL_OUT_REG:
      *val = IIS3DWB_ONLY_Y_ON_ALL_OUT_REG;
      break;

    case IIS3DWB_ONLY_Z_ON_ALL_OUT_REG:
      *val = IIS3DWB_ONLY_Z_ON_ALL_OUT_REG;
      break;

    default:
      *val = IIS3DWB_ENABLE_ALL;
      break;
  }

  return ret;
}

/**
  * @brief  Read all the interrupt flag of the device.[get]
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Get registers ALL_INT_SRC; WAKE_UP_SRC;
  *                              TAP_SRC; D6D_SRC; STATUS_REG;
  *                              EMB_FUNC_STATUS; FSM_STATUS_A/B
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t iis3dwb_all_sources_get(const stmdev_ctx_t *ctx,
                                iis3dwb_all_sources_t *val)
{
  int32_t ret = iis3dwb_read_reg(ctx, IIS3DWB_ALL_INT_SRC,
                         (uint8_t *)&val->all_int_src, 1);

  if (ret == 0)
  {
    ret = iis3dwb_read_reg(ctx, IIS3DWB_WAKE_UP_SRC,
                           (uint8_t *)&val->wake_up_src, 1);
  }

  if (ret == 0)
  {
    ret = iis3dwb_read_reg(ctx, IIS3DWB_STATUS_REG,
                           (uint8_t *)&val->status_reg, 1);
  }

  return ret;
}

/**
  * @brief  The STATUS_REG register is read by the primary interface.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Get register STATUS_REG
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t iis3dwb_status_reg_get(const stmdev_ctx_t *ctx,
                               iis3dwb_status_reg_t *val)
{
  const int32_t ret = iis3dwb_read_reg(ctx, IIS3DWB_STATUS_REG, (uint8_t *) val, 1);

  return ret;
}

/**
  * @brief  Accelerometer new data available.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of xlda in reg STATUS_REG
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t iis3dwb_xl_flag_data_ready_get(const stmdev_ctx_t *ctx,
                                       uint8_t *val)
{
  iis3dwb_status_reg_t status_reg;

  const int32_t ret = iis3dwb_read_reg(ctx, IIS3DWB_STATUS_REG,
                         (uint8_t *)&status_reg, 1);
  *val = status_reg.xlda;

  return ret;
}

/**
  * @brief  Temperature new data available.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of tda in reg STATUS_REG
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t iis3dwb_temp_flag_data_ready_get(const stmdev_ctx_t *ctx,
                                         uint8_t *val)
{
  iis3dwb_status_reg_t status_reg;

  const int32_t ret = iis3dwb_read_reg(ctx, IIS3DWB_STATUS_REG,
                         (uint8_t *)&status_reg, 1);
  *val = status_reg.tda;

  return ret;
}

/**
  * @brief  Enables the accelerometer user offset correction block, can be enabled
  * by setting the USR_OFF_ON_OUT bit of the CTRL7_C register.[set]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of USR_OFF_ON_OUT in reg CTRL7_C
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t iis3dwb_usr_offset_block_set(const stmdev_ctx_t *ctx, uint8_t val)
{
  iis3dwb_ctrl7_c_t ctrl7_c;

  int32_t ret = iis3dwb_read_reg(ctx, IIS3DWB_CTRL7_C, (uint8_t *)&ctrl7_c, 1);

  if (ret == 0)
  {
    ctrl7_c.usr_off_on_out = val;
    ret = iis3dwb_write_reg(ctx, IIS3DWB_CTRL7_C, (uint8_t *)&ctrl7_c, 1);
  }

  return ret;
}

/**
  * @brief  Enables the accelerometer user offset correction block, can be enabled
  * by setting the USR_OFF_ON_OUT bit of the CTRL7_C register.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of USR_OFF_ON_OUT in reg CTRL7_C
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t iis3dwb_usr_offset_block_get(const stmdev_ctx_t *ctx, uint8_t *val)
{
  iis3dwb_ctrl7_c_t ctrl7_c;

  const int32_t ret = iis3dwb_read_reg(ctx, IIS3DWB_CTRL7_C, (uint8_t *)&ctrl7_c, 1);
  *val = ctrl7_c.usr_off_on_out;

  return ret;
}

/**
  * @brief  Accelerometer X-axis user offset correction expressed in two's
  *         complement, weight depends on USR_OFF_W in CTRL6_C (15h).
  *         The value must be in the range [-127 127].[set]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  buff   Buffer that contains data to write
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t iis3dwb_xl_usr_offset_x_set(const stmdev_ctx_t *ctx, uint8_t *buff)
{
  const int32_t ret = iis3dwb_write_reg(ctx, IIS3DWB_X_OFS_USR, buff, 1);

  return ret;
}

/**
  * @brief  Accelerometer X-axis user offset correction expressed in two's
  *         complement, weight depends on USR_OFF_W in CTRL6_C (15h).
  *         The value must be in the range [-127 127].[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  buff   Buffer that stores data read
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t iis3dwb_xl_usr_offset_x_get(const stmdev_ctx_t *ctx, uint8_t *buff)
{
  const int32_t ret = iis3dwb_read_reg(ctx, IIS3DWB_X_OFS_USR, buff, 1);

  return ret;
}

/**
  * @brief  Accelerometer Y-axis user offset correction expressed in two's
  *         complement, weight depends on USR_OFF_W in CTRL6_C (15h).
  *         The value must be in the range [-127 127].[set]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  buff   Buffer that contains data to write
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t iis3dwb_xl_usr_offset_y_set(const stmdev_ctx_t *ctx, uint8_t *buff)
{
  const int32_t ret = iis3dwb_write_reg(ctx, IIS3DWB_Y_OFS_USR, buff, 1);

  return ret;
}

/**
  * @brief  Accelerometer Y-axis user offset correction expressed in two's
  *         complement, weight depends on USR_OFF_W in CTRL6_C (15h).
  *         The value must be in the range [-127 127].[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  buff   Buffer that stores data read
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t iis3dwb_xl_usr_offset_y_get(const stmdev_ctx_t *ctx, uint8_t *buff)
{
  const int32_t ret = iis3dwb_read_reg(ctx, IIS3DWB_Y_OFS_USR, buff, 1);

  return ret;
}

/**
  * @brief  Accelerometer Z-axis user offset correction expressed in two's
  *         complement, weight depends on USR_OFF_W in CTRL6_C (15h).
  *         The value must be in the range [-127 127].[set]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  buff   Buffer that contains data to write
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t iis3dwb_xl_usr_offset_z_set(const stmdev_ctx_t *ctx, uint8_t *buff)
{
  const int32_t ret = iis3dwb_write_reg(ctx, IIS3DWB_Z_OFS_USR, buff, 1);

  return ret;
}

/**
  * @brief  Accelerometer X-axis user offset correction expressed in two's
  *         complement, weight depends on USR_OFF_W in CTRL6_C (15h).
  *         The value must be in the range [-127 127].[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  buff   Buffer that stores data read
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t iis3dwb_xl_usr_offset_z_get(const stmdev_ctx_t *ctx, uint8_t *buff)
{
  const int32_t ret = iis3dwb_read_reg(ctx, IIS3DWB_Z_OFS_USR, buff, 1);

  return ret;
}

/**
  * @}
  *
  */

/**
  * @defgroup   IIS3DWB_Timestamp
  * @brief      This section groups all the functions that manage the
  *             timestamp generation.
  * @{
  *
  */

/**
  * @brief  Reset timestamp counter.[set]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t iis3dwb_timestamp_rst(const stmdev_ctx_t *ctx)
{
  uint8_t rst_val = 0xAA;
  return iis3dwb_write_reg(ctx, IIS3DWB_TIMESTAMP2, &rst_val, 1);
}

/**
  * @brief  Enables timestamp counter.[set]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of timestamp_en in reg CTRL10_C
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t iis3dwb_timestamp_set(const stmdev_ctx_t *ctx, uint8_t val)
{
  iis3dwb_ctrl10_c_t ctrl10_c;

  int32_t ret = iis3dwb_read_reg(ctx, IIS3DWB_CTRL10_C, (uint8_t *)&ctrl10_c, 1);

  if (ret == 0)
  {
    ctrl10_c.timestamp_en = (uint8_t)val;
    ret = iis3dwb_write_reg(ctx, IIS3DWB_CTRL10_C,
                            (uint8_t *)&ctrl10_c, 1);
  }

  return ret;
}

/**
  * @brief  Enables timestamp counter.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of timestamp_en in reg CTRL10_C
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t iis3dwb_timestamp_get(const stmdev_ctx_t *ctx, uint8_t *val)
{
  iis3dwb_ctrl10_c_t ctrl10_c;

  const int32_t ret = iis3dwb_read_reg(ctx, IIS3DWB_CTRL10_C, (uint8_t *)&ctrl10_c, 1);
  *val = ctrl10_c.timestamp_en;

  return ret;
}

/**
  * @brief  Timestamp first data output register (r).
  *         The value is expressed as a 32-bit word and the bit resolution
  *         is 25 μs.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Buffer that stores data read
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t iis3dwb_timestamp_raw_get(const stmdev_ctx_t *ctx, uint32_t *val)
{
  uint8_t buff[4];

  const int32_t ret = iis3dwb_read_reg(ctx, IIS3DWB_TIMESTAMP0, buff, 4);
  *val = buff[3];
  *val = (*val * 256U) +  buff[2];
  *val = (*val * 256U) +  buff[1];
  *val = (*val * 256U) +  buff[0];

  return ret;
}

/**
  * @}
  *
  */

/**
  * @defgroup   IIS3DWB_Data output
  * @brief      This section groups all the data output functions.
  * @{
  *
  */

/**
  * @brief  Circular burst-mode (rounding) read of the output registers.[set]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of rounding in reg CTRL5_C
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t iis3dwb_rounding_mode_set(const stmdev_ctx_t *ctx,
                                  iis3dwb_rounding_t val)
{
  iis3dwb_ctrl5_c_t ctrl5_c;

  int32_t ret = iis3dwb_read_reg(ctx, IIS3DWB_CTRL5_C, (uint8_t *)&ctrl5_c, 1);

  if (ret == 0)
  {
    ctrl5_c.rounding = (uint8_t)val;
    ret = iis3dwb_write_reg(ctx, IIS3DWB_CTRL5_C, (uint8_t *)&ctrl5_c, 1);
  }

  return ret;
}

/**
  * @brief  Gyroscope UI chain full-scale selection.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Get the values of rounding in reg CTRL5_C
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t iis3dwb_rounding_mode_get(const stmdev_ctx_t *ctx,
                                  iis3dwb_rounding_t *val)
{
  iis3dwb_ctrl5_c_t ctrl5_c;

  const int32_t ret = iis3dwb_read_reg(ctx, IIS3DWB_CTRL5_C, (uint8_t *)&ctrl5_c, 1);

  switch (ctrl5_c.rounding)
  {
    case IIS3DWB_NO_ROUND:
      *val = IIS3DWB_NO_ROUND;
      break;

    case IIS3DWB_ROUND:
      *val = IIS3DWB_ROUND;
      break;

    default:
      *val = IIS3DWB_NO_ROUND;
      break;
  }

  return ret;
}

/**
  * @brief  Temperature data output register (r).
  *         L and H registers together express a 16-bit word in two's
  *         complement.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Buffer that stores data read
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t iis3dwb_temperature_raw_get(const stmdev_ctx_t *ctx, int16_t *val)
{
  uint8_t buff[2];

  const int32_t ret = iis3dwb_read_reg(ctx, IIS3DWB_OUT_TEMP_L, buff, 2);
  *val = (int16_t)buff[1];
  *val = (*val * 256) + (int16_t)buff[0];

  return ret;
}

/**
  * @brief  Linear acceleration output register. The value is expressed as a
  *         16-bit word in two's complement.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Buffer that stores data read
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t iis3dwb_acceleration_raw_get(const stmdev_ctx_t *ctx, int16_t *val)
{
  uint8_t buff[6];

  const int32_t ret = iis3dwb_read_reg(ctx, IIS3DWB_OUTX_L_A, buff, 6);
  val[0] = (int16_t)buff[1];
  val[0] = (val[0] * 256) + (int16_t)buff[0];
  val[1] = (int16_t)buff[3];
  val[1] = (val[1] * 256) + (int16_t)buff[2];
  val[2] = (int16_t)buff[5];
  val[2] = (val[2] * 256) + (int16_t)buff[4];

  return ret;
}

/**
  * @brief  FIFO data output.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Buffer that stores data read
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t iis3dwb_fifo_out_raw_get(const stmdev_ctx_t *ctx, iis3dwb_fifo_out_raw_t *val)
{
  const int32_t ret = iis3dwb_fifo_out_multi_raw_get(ctx, val, 1);

  return ret;
}

/**
  * @brief  FIFO data multi output.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  fdata  Buffer that stores data read
  * @param  num    Number of FIFO entries to be read
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t iis3dwb_fifo_out_multi_raw_get(const stmdev_ctx_t *ctx,
                                       iis3dwb_fifo_out_raw_t *fdata,
                                       uint16_t num)
{
  /* read out all FIFO entries in a single read */
  const int32_t ret = iis3dwb_read_reg(ctx, IIS3DWB_FIFO_DATA_OUT_TAG,
                         (uint8_t *)fdata,
                         sizeof(iis3dwb_fifo_out_raw_t) * num);

  return ret;
}

/**
  * @brief  Identifies the sensor in FIFO_DATA_OUT.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of tag_sensor in reg FIFO_DATA_OUT_TAG
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t iis3dwb_fifo_sensor_tag_get(const stmdev_ctx_t *ctx,
                                    iis3dwb_fifo_tag_t *val)
{
  iis3dwb_fifo_data_out_tag_t fifo_data_out_tag;

  const int32_t ret = iis3dwb_read_reg(ctx, IIS3DWB_FIFO_DATA_OUT_TAG,
                         (uint8_t *)&fifo_data_out_tag, 1);

  switch (fifo_data_out_tag.tag_sensor)
  {
    case IIS3DWB_XL_TAG:
      *val = IIS3DWB_XL_TAG;
      break;

    case IIS3DWB_TEMPERATURE_TAG:
      *val = IIS3DWB_TEMPERATURE_TAG;
      break;

    case IIS3DWB_TIMESTAMP_TAG:
      *val = IIS3DWB_TIMESTAMP_TAG;
      break;

    default:
      *val = IIS3DWB_XL_TAG;
      break;
  }

  return ret;
}

/**
  * @}
  *
  */

/**
  * @defgroup   IIS3DWB_common
  * @brief      This section groups common useful functions.
  * @{
  *
  */

/**
  * @brief  Difference in percentage of the effective ODR (and timestamp rate)
  *         with respect to the typical.[set]
  *         Step:  0.15%. 8-bit format, 2's complement.
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of freq_fine in reg INTERNAL_FREQ_FINE
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t iis3dwb_odr_cal_reg_set(const stmdev_ctx_t *ctx, uint8_t val)
{
  iis3dwb_internal_freq_fine_t internal_freq_fine;

  int32_t ret = iis3dwb_read_reg(ctx, IIS3DWB_INTERNAL_FREQ_FINE,
                         (uint8_t *)&internal_freq_fine, 1);

  if (ret == 0)
  {
    internal_freq_fine.freq_fine = (uint8_t)val;
    ret = iis3dwb_write_reg(ctx, IIS3DWB_INTERNAL_FREQ_FINE,
                            (uint8_t *)&internal_freq_fine, 1);
  }

  return ret;
}

/**
  * @brief  Difference in percentage of the effective ODR (and timestamp rate)
  *         with respect to the typical.[get]
  *         Step:  0.15%. 8-bit format, 2's complement.
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of freq_fine in reg INTERNAL_FREQ_FINE
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t iis3dwb_odr_cal_reg_get(const stmdev_ctx_t *ctx, uint8_t *val)
{
  iis3dwb_internal_freq_fine_t internal_freq_fine;

  const int32_t ret = iis3dwb_read_reg(ctx, IIS3DWB_INTERNAL_FREQ_FINE,
                         (uint8_t *)&internal_freq_fine, 1);
  *val = internal_freq_fine.freq_fine;

  return ret;
}

/**
  * @brief  Data-ready pulsed / letched mode.[set]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of dataready_pulsed in
  *                reg COUNTER_BDR_REG1
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t iis3dwb_data_ready_mode_set(const stmdev_ctx_t *ctx,
                                    iis3dwb_dataready_pulsed_t val)
{
  iis3dwb_counter_bdr_reg1_t counter_bdr_reg1;

  int32_t ret = iis3dwb_read_reg(ctx, IIS3DWB_COUNTER_BDR_REG1,
                         (uint8_t *)&counter_bdr_reg1, 1);

  if (ret == 0)
  {
    counter_bdr_reg1.dataready_pulsed = (uint8_t)val;
    ret = iis3dwb_write_reg(ctx, IIS3DWB_COUNTER_BDR_REG1,
                            (uint8_t *)&counter_bdr_reg1, 1);
  }

  return ret;
}

/**
  * @brief  Data-ready pulsed / letched mode.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Get the values of dataready_pulsed in
  *                reg COUNTER_BDR_REG1
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t iis3dwb_data_ready_mode_get(const stmdev_ctx_t *ctx,
                                    iis3dwb_dataready_pulsed_t *val)
{
  iis3dwb_counter_bdr_reg1_t counter_bdr_reg1;

  const int32_t ret = iis3dwb_read_reg(ctx, IIS3DWB_COUNTER_BDR_REG1,
                         (uint8_t *)&counter_bdr_reg1, 1);

  switch (counter_bdr_reg1.dataready_pulsed)
  {
    case IIS3DWB_DRDY_LATCHED:
      *val = IIS3DWB_DRDY_LATCHED;
      break;

    case IIS3DWB_DRDY_PULSED:
      *val = IIS3DWB_DRDY_PULSED;
      break;

    default:
      *val = IIS3DWB_DRDY_LATCHED;
      break;
  }

  return ret;
}

/**
  * @brief  Device Who am I.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  buff   Buffer that stores data read
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t iis3dwb_device_id_get(const stmdev_ctx_t *ctx, uint8_t *buff)
{
  const int32_t ret = iis3dwb_read_reg(ctx, IIS3DWB_WHO_AM_I, buff, 1);

  return ret;
}

/**
  * @brief  Software reset.[set]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Value of sw_reset in reg CTRL3_C
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t iis3dwb_reset_set(const stmdev_ctx_t *ctx, uint8_t val)
{
  iis3dwb_ctrl3_c_t ctrl3_c;

  int32_t ret = iis3dwb_read_reg(ctx, IIS3DWB_CTRL3_C, (uint8_t *)&ctrl3_c, 1);

  if (ret == 0)
  {
    ctrl3_c.sw_reset = (uint8_t)val;
    ret = iis3dwb_write_reg(ctx, IIS3DWB_CTRL3_C, (uint8_t *)&ctrl3_c, 1);
  }

  return ret;
}

/**
  * @brief  Software reset.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Value of sw_reset in reg CTRL3_C
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t iis3dwb_reset_get(const stmdev_ctx_t *ctx, uint8_t *val)
{
  iis3dwb_ctrl3_c_t ctrl3_c;

  const int32_t ret = iis3dwb_read_reg(ctx, IIS3DWB_CTRL3_C, (uint8_t *)&ctrl3_c, 1);
  *val = ctrl3_c.sw_reset;

  return ret;
}

/**
  * @brief  Register address automatically incremented during a multiple byte
  *         access with a serial interface.[set]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of if_inc in reg CTRL3_C
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t iis3dwb_auto_increment_set(const stmdev_ctx_t *ctx, uint8_t val)
{
  iis3dwb_ctrl3_c_t ctrl3_c;

  int32_t ret = iis3dwb_read_reg(ctx, IIS3DWB_CTRL3_C, (uint8_t *)&ctrl3_c, 1);

  if (ret == 0)
  {
    ctrl3_c.if_inc = (uint8_t)val;
    ret = iis3dwb_write_reg(ctx, IIS3DWB_CTRL3_C, (uint8_t *)&ctrl3_c, 1);
  }

  return ret;
}

/**
  * @brief  Register address automatically incremented during a multiple byte
  *         access with a serial interface.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of if_inc in reg CTRL3_C
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t iis3dwb_auto_increment_get(const stmdev_ctx_t *ctx, uint8_t *val)
{
  iis3dwb_ctrl3_c_t ctrl3_c;

  const int32_t ret = iis3dwb_read_reg(ctx, IIS3DWB_CTRL3_C, (uint8_t *)&ctrl3_c, 1);
  *val = ctrl3_c.if_inc;

  return ret;
}

/**
  * @brief  Reboot memory content.[set]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Value of boot in reg CTRL3_C
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t iis3dwb_boot_set(const stmdev_ctx_t *ctx, uint8_t val)
{
  iis3dwb_ctrl3_c_t ctrl3_c;

  int32_t ret = iis3dwb_read_reg(ctx, IIS3DWB_CTRL3_C, (uint8_t *)&ctrl3_c, 1);

  if (ret == 0)
  {
    ctrl3_c.boot = (uint8_t)val;
    ret = iis3dwb_write_reg(ctx, IIS3DWB_CTRL3_C, (uint8_t *)&ctrl3_c, 1);
  }

  return ret;
}

/**
  * @brief  Reboot memory content.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Value of boot in reg CTRL3_C
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t iis3dwb_boot_get(const stmdev_ctx_t *ctx, uint8_t *val)
{
  iis3dwb_ctrl3_c_t ctrl3_c;

  const int32_t ret = iis3dwb_read_reg(ctx, IIS3DWB_CTRL3_C, (uint8_t *)&ctrl3_c, 1);
  *val = ctrl3_c.boot;

  return ret;
}



/**
  * @brief  Linear acceleration sensor self-test enable.[set]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of st_xl in reg CTRL5_C
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t iis3dwb_xl_self_test_set(const stmdev_ctx_t *ctx,
                                 iis3dwb_st_xl_t val)
{
  iis3dwb_ctrl5_c_t ctrl5_c;

  int32_t ret = iis3dwb_read_reg(ctx, IIS3DWB_CTRL5_C, (uint8_t *)&ctrl5_c, 1);

  if (ret == 0)
  {
    ctrl5_c.st_xl = (uint8_t)val;
    ret = iis3dwb_write_reg(ctx, IIS3DWB_CTRL5_C, (uint8_t *)&ctrl5_c, 1);
  }

  return ret;
}

/**
  * @brief  Linear acceleration sensor self-test enable.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Get the values of st_xl in reg CTRL5_C
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t iis3dwb_xl_self_test_get(const stmdev_ctx_t *ctx,
                                 iis3dwb_st_xl_t *val)
{
  iis3dwb_ctrl5_c_t ctrl5_c;

  const int32_t ret = iis3dwb_read_reg(ctx, IIS3DWB_CTRL5_C, (uint8_t *)&ctrl5_c, 1);

  switch (ctrl5_c.st_xl)
  {
    case IIS3DWB_XL_ST_DISABLE:
      *val = IIS3DWB_XL_ST_DISABLE;
      break;

    case IIS3DWB_XL_ST_POSITIVE:
      *val = IIS3DWB_XL_ST_POSITIVE;
      break;

    case IIS3DWB_XL_ST_NEGATIVE:
      *val = IIS3DWB_XL_ST_NEGATIVE;
      break;

    default:
      *val = IIS3DWB_XL_ST_DISABLE;
      break;
  }

  return ret;
}



/**
  * @}
  *
  */

/**
  * @defgroup   IIS3DWB_filters
  * @brief      This section group all the functions concerning the
  *             filters configuration
  * @{
  *
  */

/**
  * @brief  Mask DRDY on pin (both XL & Gyro) until filter settling ends
  *         (XL and Gyro independently masked).[set]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of drdy_mask in reg CTRL4_C
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t iis3dwb_filter_settling_mask_set(const stmdev_ctx_t *ctx,
                                         uint8_t val)
{
  iis3dwb_ctrl4_c_t ctrl4_c;

  int32_t ret = iis3dwb_read_reg(ctx, IIS3DWB_CTRL4_C, (uint8_t *)&ctrl4_c, 1);

  if (ret == 0)
  {
    ctrl4_c.drdy_mask = (uint8_t)val;
    ret = iis3dwb_write_reg(ctx, IIS3DWB_CTRL4_C, (uint8_t *)&ctrl4_c, 1);
  }

  return ret;
}

/**
  * @brief  Mask DRDY on pin (both XL & Gyro) until filter settling ends
  *         (XL and Gyro independently masked).[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of drdy_mask in reg CTRL4_C
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t iis3dwb_filter_settling_mask_get(const stmdev_ctx_t *ctx,
                                         uint8_t *val)
{
  iis3dwb_ctrl4_c_t ctrl4_c;
  const int32_t ret = iis3dwb_read_reg(ctx, IIS3DWB_CTRL4_C, (uint8_t *)&ctrl4_c, 1);
  *val = ctrl4_c.drdy_mask;

  return ret;
}

/**
  * @brief  Accelerometer filter selection on output.[set]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change filter selection on output.
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t iis3dwb_xl_filt_path_on_out_set(const stmdev_ctx_t *ctx,
                                        iis3dwb_filt_xl_en_t val)
{
  iis3dwb_ctrl1_xl_t ctrl1_xl;
  iis3dwb_ctrl8_xl_t ctrl8_xl;

  int32_t ret = iis3dwb_read_reg(ctx, IIS3DWB_CTRL1_XL, (uint8_t *)&ctrl1_xl, 1);

  if (ret == 0)
  {
    ctrl1_xl.lpf2_xl_en = ((uint8_t)val & 0x80U) >> 7;
    ret = iis3dwb_write_reg(ctx, IIS3DWB_CTRL1_XL, (uint8_t *)&ctrl1_xl, 1);
  }

  if (ret == 0)
  {
    ret = iis3dwb_read_reg(ctx, IIS3DWB_CTRL8_XL, (uint8_t *)&ctrl8_xl, 1);
  }

  if (ret == 0)
  {
    ctrl8_xl.fds = ((uint8_t)val & 0x10U) >> 4;
    ctrl8_xl.hp_ref_mode_xl = ((uint8_t)val & 0x20U) >> 5;
    ctrl8_xl.hpcf_xl = (uint8_t)val & 0x07U;
    ret = iis3dwb_write_reg(ctx, IIS3DWB_CTRL8_XL, (uint8_t *)&ctrl8_xl, 1);
  }

  return ret;
}

/**
  * @brief Accelerometer filter selection on output.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Get filter selection on output.
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t iis3dwb_xl_filt_path_on_out_get(const stmdev_ctx_t *ctx,
                                        iis3dwb_filt_xl_en_t *val)
{
  iis3dwb_ctrl1_xl_t ctrl1_xl;
  iis3dwb_ctrl8_xl_t ctrl8_xl;

  *val = IIS3DWB_HP_REF_MODE;

  int32_t ret = iis3dwb_read_reg(ctx, IIS3DWB_CTRL1_XL, (uint8_t *)&ctrl1_xl, 1);
  if (ret != 0) { return ret; }

  ret = iis3dwb_read_reg(ctx, IIS3DWB_CTRL8_XL, (uint8_t *)&ctrl8_xl, 1);
  if (ret != 0) { return ret; }

  switch ((ctrl1_xl.lpf2_xl_en << 7) + (ctrl8_xl.hp_ref_mode_xl << 5) +
          (ctrl8_xl.fds << 4) + ctrl8_xl.hpcf_xl)
  {
    case IIS3DWB_HP_REF_MODE:
      *val = IIS3DWB_HP_REF_MODE;
      break;

    case IIS3DWB_HP_ODR_DIV_10:
      *val = IIS3DWB_HP_ODR_DIV_10;
      break;

    case IIS3DWB_HP_ODR_DIV_20:
      *val = IIS3DWB_HP_ODR_DIV_20;
      break;

    case IIS3DWB_HP_ODR_DIV_45:
      *val = IIS3DWB_HP_ODR_DIV_45;
      break;

    case IIS3DWB_HP_ODR_DIV_100:
      *val = IIS3DWB_HP_ODR_DIV_100;
      break;

    case IIS3DWB_HP_ODR_DIV_200:
      *val = IIS3DWB_HP_ODR_DIV_200;
      break;

    case IIS3DWB_HP_ODR_DIV_400:
      *val = IIS3DWB_HP_ODR_DIV_400;
      break;

    case IIS3DWB_HP_ODR_DIV_800:
      *val = IIS3DWB_HP_ODR_DIV_800;
      break;

    case IIS3DWB_LP_ODR_DIV_4:
      *val = IIS3DWB_LP_ODR_DIV_4;
      break;

    case IIS3DWB_LP_6k3Hz:
      *val = IIS3DWB_LP_6k3Hz;
      break;

    case IIS3DWB_LP_ODR_DIV_10:
      *val = IIS3DWB_LP_ODR_DIV_10;
      break;

    case IIS3DWB_LP_ODR_DIV_20:
      *val = IIS3DWB_LP_ODR_DIV_20;
      break;

    case IIS3DWB_LP_ODR_DIV_45:
      *val = IIS3DWB_LP_ODR_DIV_45;
      break;

    case IIS3DWB_LP_ODR_DIV_100:
      *val = IIS3DWB_LP_ODR_DIV_100;
      break;

    case IIS3DWB_LP_ODR_DIV_200:
      *val = IIS3DWB_LP_ODR_DIV_200;
      break;

    case IIS3DWB_LP_ODR_DIV_400:
      *val = IIS3DWB_LP_ODR_DIV_400;
      break;

    case IIS3DWB_LP_ODR_DIV_800:
      *val = IIS3DWB_LP_ODR_DIV_800;
      break;

    default:
      *val = IIS3DWB_HP_REF_MODE;
      break;
  }

  return ret;
}

/**
  * @brief  Enables accelerometer LPF2 and HPF fast-settling mode.
  *         The filter sets the second samples after writing this bit.
  *         Active only during device exit from powerdown mode.[set]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of fastsettl_mode_xl in reg CTRL8_XL
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t iis3dwb_xl_fast_settling_set(const stmdev_ctx_t *ctx, uint8_t val)
{
  iis3dwb_ctrl8_xl_t ctrl8_xl;

  int32_t ret = iis3dwb_read_reg(ctx, IIS3DWB_CTRL8_XL, (uint8_t *)&ctrl8_xl, 1);

  if (ret == 0)
  {
    ctrl8_xl.fastsettl_mode_xl = (uint8_t)val;
    ret = iis3dwb_write_reg(ctx, IIS3DWB_CTRL8_XL,
                            (uint8_t *)&ctrl8_xl, 1);
  }

  return ret;
}

/**
  * @brief  Enables accelerometer LPF2 and HPF fast-settling mode.
  *         The filter sets the second samples after writing
  *         this bit. Active only during device exit from powerdown mode.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of fastsettl_mode_xl in reg CTRL8_XL
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t iis3dwb_xl_fast_settling_get(const stmdev_ctx_t *ctx, uint8_t *val)
{
  iis3dwb_ctrl8_xl_t ctrl8_xl;

  const int32_t ret = iis3dwb_read_reg(ctx, IIS3DWB_CTRL8_XL, (uint8_t *)&ctrl8_xl, 1);
  *val = ctrl8_xl.fastsettl_mode_xl;

  return ret;
}

/**
  * @brief  HPF or SLOPE filter selection on wake-up and Activity/Inactivity
  *         functions.[set]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of slope_fds in reg TAP_CFG0
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t iis3dwb_xl_hp_path_internal_set(const stmdev_ctx_t *ctx,
                                        iis3dwb_slope_fds_t val)
{
  iis3dwb_slope_en_t int_cfg0;

  int32_t ret = iis3dwb_read_reg(ctx, IIS3DWB_SLOPE_EN, (uint8_t *)&int_cfg0, 1);

  if (ret == 0)
  {
    int_cfg0.slope_fds = (uint8_t)val;
    ret = iis3dwb_write_reg(ctx, IIS3DWB_SLOPE_EN,
                            (uint8_t *)&int_cfg0, 1);
  }

  return ret;
}

/**
  * @brief  HPF or SLOPE filter selection on wake-up and Activity/Inactivity
  *         functions.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Get the values of slope_fds in reg TAP_CFG0
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t iis3dwb_xl_hp_path_internal_get(const stmdev_ctx_t *ctx,
                                        iis3dwb_slope_fds_t *val)
{
  iis3dwb_slope_en_t int_cfg0;

  const int32_t ret = iis3dwb_read_reg(ctx, IIS3DWB_SLOPE_EN, (uint8_t *)&int_cfg0, 1);

  switch (int_cfg0.slope_fds)
  {
    case IIS3DWB_USE_SLOPE:
      *val = IIS3DWB_USE_SLOPE;
      break;

    case IIS3DWB_USE_HPF:
      *val = IIS3DWB_USE_HPF;
      break;

    default:
      *val = IIS3DWB_USE_SLOPE;
      break;
  }

  return ret;
}

/**
  * @}
  *
  */

/**
  * @defgroup   IIS3DWB_ main_serial_interface
  * @brief      This section groups all the functions concerning main
  *             serial interface management (not auxiliary)
  * @{
  *
  */

/**
  * @brief  Connect/Disconnect SDO/SA0 internal pull-up.[set]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of sdo_pu_en in reg PIN_CTRL
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t iis3dwb_sdo_sa0_mode_set(const stmdev_ctx_t *ctx,
                                 iis3dwb_sdo_pu_en_t val)
{
  iis3dwb_pin_ctrl_t pin_ctrl;

  int32_t ret = iis3dwb_read_reg(ctx, IIS3DWB_PIN_CTRL, (uint8_t *)&pin_ctrl, 1);

  if (ret == 0)
  {
    pin_ctrl.sdo_pu_en = (uint8_t)val;
    ret = iis3dwb_write_reg(ctx, IIS3DWB_PIN_CTRL, (uint8_t *)&pin_ctrl, 1);
  }

  return ret;
}

/**
  * @brief  Connect/Disconnect SDO/SA0 internal pull-up.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Get the values of sdo_pu_en in reg PIN_CTRL
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t iis3dwb_sdo_sa0_mode_get(const stmdev_ctx_t *ctx,
                                 iis3dwb_sdo_pu_en_t *val)
{
  iis3dwb_pin_ctrl_t pin_ctrl;

  const int32_t ret = iis3dwb_read_reg(ctx, IIS3DWB_PIN_CTRL, (uint8_t *)&pin_ctrl, 1);

  switch (pin_ctrl.sdo_pu_en)
  {
    case IIS3DWB_PULL_UP_DISC:
      *val = IIS3DWB_PULL_UP_DISC;
      break;

    case IIS3DWB_PULL_UP_CONNECT:
      *val = IIS3DWB_PULL_UP_CONNECT;
      break;

    default:
      *val = IIS3DWB_PULL_UP_DISC;
      break;
  }

  return ret;
}

/**
  * @brief  SPI Serial Interface Mode selection.[set]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of sim in reg CTRL3_C
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t iis3dwb_spi_mode_set(const stmdev_ctx_t *ctx, iis3dwb_sim_t val)
{
  iis3dwb_ctrl3_c_t ctrl3_c;

  int32_t ret = iis3dwb_read_reg(ctx, IIS3DWB_CTRL3_C, (uint8_t *)&ctrl3_c, 1);

  if (ret == 0)
  {
    ctrl3_c.sim = (uint8_t)val;
    ret = iis3dwb_write_reg(ctx, IIS3DWB_CTRL3_C, (uint8_t *)&ctrl3_c, 1);
  }

  return ret;
}

/**
  * @brief  SPI Serial Interface Mode selection.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Get the values of sim in reg CTRL3_C
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t iis3dwb_spi_mode_get(const stmdev_ctx_t *ctx, iis3dwb_sim_t *val)
{
  iis3dwb_ctrl3_c_t ctrl3_c;

  const int32_t ret = iis3dwb_read_reg(ctx, IIS3DWB_CTRL3_C, (uint8_t *)&ctrl3_c, 1);

  switch (ctrl3_c.sim)
  {
    case IIS3DWB_SPI_4_WIRE:
      *val = IIS3DWB_SPI_4_WIRE;
      break;

    case IIS3DWB_SPI_3_WIRE:
      *val = IIS3DWB_SPI_3_WIRE;
      break;

    default:
      *val = IIS3DWB_SPI_4_WIRE;
      break;
  }

  return ret;
}

/**
  * @brief  Disable / Enable I2C interface.[set]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of i2c_disable in reg CTRL4_C
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t iis3dwb_i2c_interface_set(const stmdev_ctx_t *ctx,
                                  iis3dwb_i2c_disable_t val)
{
  iis3dwb_ctrl4_c_t ctrl4_c;

  int32_t ret = iis3dwb_read_reg(ctx, IIS3DWB_CTRL4_C, (uint8_t *)&ctrl4_c, 1);

  if (ret == 0)
  {
    ctrl4_c.i2c_disable = (uint8_t)val;
    ret = iis3dwb_write_reg(ctx, IIS3DWB_CTRL4_C, (uint8_t *)&ctrl4_c, 1);
  }

  return ret;
}

/**
  * @brief  Disable / Enable I2C interface.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Get the values of i2c reg CTRL4_C
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t iis3dwb_i2c_interface_get(const stmdev_ctx_t *ctx,
                                  iis3dwb_i2c_disable_t *val)
{
  iis3dwb_ctrl4_c_t ctrl4_c;

  const int32_t ret = iis3dwb_read_reg(ctx, IIS3DWB_CTRL4_C, (uint8_t *)&ctrl4_c, 1);

  switch (ctrl4_c.i2c_disable)
  {
    case IIS3DWB_I2C_ENABLE:
      *val = IIS3DWB_I2C_ENABLE;
      break;

    case IIS3DWB_I2C_DISABLE:
      *val = IIS3DWB_I2C_DISABLE;
      break;

    default:
      *val = IIS3DWB_I2C_ENABLE;
      break;
  }

  return ret;
}

/**
  * @}
  *
  */

/**
  * @defgroup   IIS3DWB_interrupt_pins
  * @brief      This section groups all the functions that manage
  *             interrupt pins
  * @{
  *
  */

/**
  * @brief   Select the signal that need to route on int1 pad[set]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    the signals to route on int1 pin.
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t iis3dwb_pin_int1_route_set(const stmdev_ctx_t *ctx,
                                   iis3dwb_pin_int1_route_t *val)
{
  iis3dwb_int1_ctrl_t          int1_ctrl;
  iis3dwb_slope_en_t           slope_en;
  iis3dwb_md1_cfg_t            md1_cfg;

  int32_t ret = iis3dwb_read_reg(ctx, IIS3DWB_INT1_CTRL, (uint8_t *)&int1_ctrl, 1);
  if (ret != 0) { return ret; }

  ret = iis3dwb_read_reg(ctx, IIS3DWB_MD1_CFG, (uint8_t *)&md1_cfg, 1);
  if (ret != 0) { return ret; }

  ret = iis3dwb_read_reg(ctx, IIS3DWB_SLOPE_EN, (uint8_t *)&slope_en, 1);
  if (ret != 0) { return ret; }

  int1_ctrl.int1_drdy_xl       = val->drdy_xl;
  int1_ctrl.int1_boot          = val->boot;
  int1_ctrl.int1_fifo_th       = val->fifo_th;
  int1_ctrl.int1_fifo_ovr      = val->fifo_ovr;
  int1_ctrl.int1_fifo_full     = val->fifo_full;
  int1_ctrl.int1_cnt_bdr       = val->fifo_bdr;
  md1_cfg.int1_wu              = val->wake_up;
  md1_cfg.int1_sleep_change    = val->sleep_change | val->sleep_status;
  slope_en.sleep_status_on_int = val->sleep_status;

  ret = iis3dwb_write_reg(ctx, IIS3DWB_INT1_CTRL, (uint8_t *)&int1_ctrl, 1);
  if (ret != 0) { return ret; }

  ret = iis3dwb_write_reg(ctx, IIS3DWB_MD1_CFG, (uint8_t *)&md1_cfg, 1);
  if (ret != 0) { return ret; }

  ret = iis3dwb_write_reg(ctx, IIS3DWB_SLOPE_EN, (uint8_t *)&slope_en, 1);

  return ret;
}

/**
  * @brief  Select the signal that need to route on int1 pad.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    the signals that are routed on int1 pin.(ptr)
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t iis3dwb_pin_int1_route_get(const stmdev_ctx_t *ctx,
                                   iis3dwb_pin_int1_route_t *val)
{
  iis3dwb_int1_ctrl_t          int1_ctrl;
  iis3dwb_slope_en_t           slope_en;
  iis3dwb_md1_cfg_t            md1_cfg;

  memset(val, 0, sizeof(iis3dwb_pin_int1_route_t));

  int32_t ret = iis3dwb_read_reg(ctx, IIS3DWB_INT1_CTRL, (uint8_t *)&int1_ctrl, 1);
  if (ret != 0) { return ret; }

  ret = iis3dwb_read_reg(ctx, IIS3DWB_MD1_CFG, (uint8_t *)&md1_cfg, 1);
  if (ret != 0) { return ret; }

  ret = iis3dwb_read_reg(ctx, IIS3DWB_SLOPE_EN, (uint8_t *)&slope_en, 1);
  if (ret != 0) { return ret; }

  val->drdy_xl   = int1_ctrl.int1_drdy_xl;
  val->boot      = int1_ctrl.int1_boot;
  val->fifo_th   = int1_ctrl.int1_fifo_th;
  val->fifo_ovr  = int1_ctrl.int1_fifo_ovr;
  val->fifo_full = int1_ctrl.int1_fifo_full;
  val->fifo_bdr  = int1_ctrl.int1_cnt_bdr;
  val->wake_up      = md1_cfg.int1_wu;

  if (slope_en.sleep_status_on_int == PROPERTY_ENABLE)
  {
    val->sleep_status = PROPERTY_ENABLE;
    val->sleep_change = PROPERTY_DISABLE;
  }

  else
  {
    val->sleep_change = md1_cfg.int1_sleep_change;
  }

  return ret;
}

/**
  * @brief  Select the signal that need to route on int2 pad[set]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    the signals to route on int2 pin.
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t iis3dwb_pin_int2_route_set(const stmdev_ctx_t *ctx,
                                   iis3dwb_pin_int2_route_t *val)
{
  iis3dwb_int2_ctrl_t          int2_ctrl;
  iis3dwb_slope_en_t           slope_en;
  iis3dwb_md2_cfg_t            md2_cfg;

  int32_t ret = iis3dwb_read_reg(ctx, IIS3DWB_INT2_CTRL, (uint8_t *)&int2_ctrl, 1);
  if (ret != 0) { return ret; }

  ret = iis3dwb_read_reg(ctx, IIS3DWB_MD2_CFG, (uint8_t *)&md2_cfg, 1);
  if (ret != 0) { return ret; }

  ret = iis3dwb_read_reg(ctx, IIS3DWB_SLOPE_EN, (uint8_t *)&slope_en, 1);
  if (ret != 0) { return ret; }

  int2_ctrl.int2_drdy_xl       = val->drdy_xl;
  int2_ctrl.int2_drdy_temp     = val->drdy_temp;
  int2_ctrl.int2_fifo_th       = val->fifo_th;
  int2_ctrl.int2_fifo_ovr      = val->fifo_ovr;
  int2_ctrl.int2_fifo_full     = val->fifo_full;
  int2_ctrl.int2_cnt_bdr       = val->fifo_bdr;
  md2_cfg.int2_timestamp       = val->timestamp;
  md2_cfg.int2_wu              = val->wake_up;
  md2_cfg.int2_sleep_change    = val->sleep_change | val->sleep_status;
  slope_en.sleep_status_on_int = val->sleep_status;

  ret = iis3dwb_write_reg(ctx, IIS3DWB_INT2_CTRL, (uint8_t *)&int2_ctrl, 1);
  if (ret != 0) { return ret; }

  ret = iis3dwb_write_reg(ctx, IIS3DWB_MD2_CFG, (uint8_t *)&md2_cfg, 1);
  if (ret != 0) { return ret; }

  ret = iis3dwb_write_reg(ctx, IIS3DWB_SLOPE_EN, (uint8_t *)&slope_en, 1);

  return ret;
}

/**
  * @brief  Select the signal that need to route on int2 pad.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    the signals that are routed on int2 pin.(ptr)
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t iis3dwb_pin_int2_route_get(const stmdev_ctx_t *ctx,
                                   iis3dwb_pin_int2_route_t *val)
{
  iis3dwb_int2_ctrl_t          int2_ctrl;
  iis3dwb_slope_en_t           slope_en;
  iis3dwb_md2_cfg_t            md2_cfg;

  memset(val, 0, sizeof(iis3dwb_pin_int2_route_t));

  int32_t ret = iis3dwb_read_reg(ctx, IIS3DWB_INT2_CTRL, (uint8_t *)&int2_ctrl, 1);
  if (ret != 0) { return ret; }

  ret = iis3dwb_read_reg(ctx, IIS3DWB_MD2_CFG, (uint8_t *)&md2_cfg, 1);
  if (ret != 0) { return ret; }

  ret = iis3dwb_read_reg(ctx, IIS3DWB_SLOPE_EN, (uint8_t *)&slope_en, 1);
  if (ret != 0) { return ret; }

  val->drdy_xl   = int2_ctrl.int2_drdy_xl;
  val->drdy_temp = int2_ctrl.int2_drdy_temp;
  val->fifo_th   = int2_ctrl.int2_fifo_th;
  val->fifo_ovr  = int2_ctrl.int2_fifo_ovr;
  val->fifo_full = int2_ctrl.int2_fifo_full;
  val->fifo_bdr  = int2_ctrl.int2_cnt_bdr;
  val->timestamp  = md2_cfg.int2_timestamp;
  val->wake_up   = md2_cfg.int2_wu;

  if (slope_en.sleep_status_on_int == PROPERTY_ENABLE)
  {
    val->sleep_status = PROPERTY_ENABLE;
    val->sleep_change = PROPERTY_DISABLE;
  }

  else
  {
    val->sleep_change = md2_cfg.int2_sleep_change;
  }

  return ret;
}

/**
  * @brief  Push-pull/open drain selection on interrupt pads.[set]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of pp_od in reg CTRL3_C
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t iis3dwb_pin_mode_set(const stmdev_ctx_t *ctx, iis3dwb_pp_od_t val)
{
  iis3dwb_ctrl3_c_t ctrl3_c;

  int32_t ret = iis3dwb_read_reg(ctx, IIS3DWB_CTRL3_C, (uint8_t *)&ctrl3_c, 1);

  if (ret == 0)
  {
    ctrl3_c.pp_od = (uint8_t)val;
    ret = iis3dwb_write_reg(ctx, IIS3DWB_CTRL3_C, (uint8_t *)&ctrl3_c, 1);
  }

  return ret;
}

/**
  * @brief  Push-pull/open drain selection on interrupt pads.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Get the values of pp_od in reg CTRL3_C
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t iis3dwb_pin_mode_get(const stmdev_ctx_t *ctx, iis3dwb_pp_od_t *val)
{
  iis3dwb_ctrl3_c_t ctrl3_c;

  int32_t ret = iis3dwb_read_reg(ctx, IIS3DWB_CTRL3_C, (uint8_t *)&ctrl3_c, 1);

  switch (ctrl3_c.pp_od)
  {
    case IIS3DWB_PUSH_PULL:
      *val = IIS3DWB_PUSH_PULL;
      break;

    case IIS3DWB_OPEN_DRAIN:
      *val = IIS3DWB_OPEN_DRAIN;
      break;

    default:
      *val = IIS3DWB_PUSH_PULL;
      break;
  }

  return ret;
}

/**
  * @brief  Interrupt active-high/low.[set]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of h_lactive in reg CTRL3_C
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t iis3dwb_pin_polarity_set(const stmdev_ctx_t *ctx,
                                 iis3dwb_h_lactive_t val)
{
  iis3dwb_ctrl3_c_t ctrl3_c;

  int32_t ret = iis3dwb_read_reg(ctx, IIS3DWB_CTRL3_C, (uint8_t *)&ctrl3_c, 1);

  if (ret == 0)
  {
    ctrl3_c.h_lactive = (uint8_t)val;
    ret = iis3dwb_write_reg(ctx, IIS3DWB_CTRL3_C, (uint8_t *)&ctrl3_c, 1);
  }

  return ret;
}

/**
  * @brief  Interrupt active-high/low.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Get the values of h_lactive in reg CTRL3_C
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t iis3dwb_pin_polarity_get(const stmdev_ctx_t *ctx,
                                 iis3dwb_h_lactive_t *val)
{
  iis3dwb_ctrl3_c_t ctrl3_c;

  int32_t ret = iis3dwb_read_reg(ctx, IIS3DWB_CTRL3_C, (uint8_t *)&ctrl3_c, 1);

  switch (ctrl3_c.h_lactive)
  {
    case IIS3DWB_ACTIVE_HIGH:
      *val = IIS3DWB_ACTIVE_HIGH;
      break;

    case IIS3DWB_ACTIVE_LOW:
      *val = IIS3DWB_ACTIVE_LOW;
      break;

    default:
      *val = IIS3DWB_ACTIVE_HIGH;
      break;
  }

  return ret;
}

/**
  * @brief  All interrupt signals become available on INT1 pin.[set]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of int2_on_int1 in reg CTRL4_C
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t iis3dwb_all_on_int1_set(const stmdev_ctx_t *ctx, uint8_t val)
{
  iis3dwb_ctrl4_c_t ctrl4_c;

  int32_t ret = iis3dwb_read_reg(ctx, IIS3DWB_CTRL4_C, (uint8_t *)&ctrl4_c, 1);

  if (ret == 0)
  {
    ctrl4_c.int2_on_int1 = (uint8_t)val;
    ret = iis3dwb_write_reg(ctx, IIS3DWB_CTRL4_C, (uint8_t *)&ctrl4_c, 1);
  }

  return ret;
}

/**
  * @brief  All interrupt signals become available on INT1 pin.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of int2_on_int1 in reg CTRL4_C
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t iis3dwb_all_on_int1_get(const stmdev_ctx_t *ctx, uint8_t *val)
{
  iis3dwb_ctrl4_c_t ctrl4_c;

  int32_t ret = iis3dwb_read_reg(ctx, IIS3DWB_CTRL4_C, (uint8_t *)&ctrl4_c, 1);
  *val = ctrl4_c.int2_on_int1;

  return ret;
}

/**
  * @brief  All interrupt signals notification mode.[set]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of lir in reg SLOPE_EN
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t iis3dwb_int_notification_set(const stmdev_ctx_t *ctx,
                                     iis3dwb_lir_t val)
{
  iis3dwb_slope_en_t slope_en;

  int32_t ret = iis3dwb_read_reg(ctx, IIS3DWB_SLOPE_EN, (uint8_t *)&slope_en, 1);

  if (ret == 0)
  {
    slope_en.lir = (uint8_t)val;
    ret = iis3dwb_write_reg(ctx, IIS3DWB_SLOPE_EN, (uint8_t *)&slope_en, 1);
  }

  return ret;
}

/**
  * @brief  All interrupt signals notification mode.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Get the values of lir in reg SLOPE_EN
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t iis3dwb_int_notification_get(const stmdev_ctx_t *ctx,
                                     iis3dwb_lir_t *val)
{
  iis3dwb_slope_en_t slope_en;

  int32_t ret = iis3dwb_read_reg(ctx, IIS3DWB_SLOPE_EN, (uint8_t *)&slope_en, 1);

  switch (slope_en.lir)
  {
    case IIS3DWB_INT_PULSED:
      *val = IIS3DWB_INT_PULSED;
      break;

    case IIS3DWB_INT_LATCHED:
      *val = IIS3DWB_INT_LATCHED;
      break;

    default:
      *val = IIS3DWB_INT_PULSED;
      break;
  }

  return ret;
}

/**
  * @}
  *
  */

/**
  * @defgroup   IIS3DWB_Wake_Up_event
  * @brief      This section groups all the functions that manage the
  *             Wake Up event generation.
  * @{
  *
  */

/**
  * @brief  Weight of 1 LSB of wakeup threshold.[set]
  *         0: 1 LSB =FS_XL  /  64
  *         1: 1 LSB = FS_XL / 256
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of wake_ths_w in reg WAKE_UP_DUR
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t iis3dwb_wkup_ths_weight_set(const stmdev_ctx_t *ctx,
                                    iis3dwb_wake_ths_w_t val)
{
  iis3dwb_wake_up_dur_t wake_up_dur;

  int32_t ret = iis3dwb_read_reg(ctx, IIS3DWB_WAKE_UP_DUR,
                         (uint8_t *)&wake_up_dur, 1);

  if (ret == 0)
  {
    wake_up_dur.wake_ths_w = (uint8_t)val;
    ret = iis3dwb_write_reg(ctx, IIS3DWB_WAKE_UP_DUR,
                            (uint8_t *)&wake_up_dur, 1);
  }

  return ret;
}

/**
  * @brief  Weight of 1 LSB of wakeup threshold.[get]
  *         0: 1 LSB =FS_XL  /  64
  *         1: 1 LSB = FS_XL / 256
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Get the values of wake_ths_w in reg WAKE_UP_DUR
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t iis3dwb_wkup_ths_weight_get(const stmdev_ctx_t *ctx,
                                    iis3dwb_wake_ths_w_t *val)
{
  iis3dwb_wake_up_dur_t wake_up_dur;

  int32_t ret = iis3dwb_read_reg(ctx, IIS3DWB_WAKE_UP_DUR,
                         (uint8_t *)&wake_up_dur, 1);

  switch (wake_up_dur.wake_ths_w)
  {
    case IIS3DWB_LSb_FS_DIV_64:
      *val = IIS3DWB_LSb_FS_DIV_64;
      break;

    case IIS3DWB_LSb_FS_DIV_256:
      *val = IIS3DWB_LSb_FS_DIV_256;
      break;

    default:
      *val = IIS3DWB_LSb_FS_DIV_64;
      break;
  }

  return ret;
}

/**
  * @brief  Threshold for wakeup: 1 LSB weight depends on WAKE_THS_W in
  *         WAKE_UP_DUR. This function is mandatory for activate the
  *         wake up (and activity/inactivity) logic.[set]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of wk_ths in reg WAKE_UP_THS
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t iis3dwb_wkup_threshold_set(const stmdev_ctx_t *ctx, uint8_t val)
{
  iis3dwb_interrupts_en_t interrupts_en;
  iis3dwb_wake_up_ths_t wake_up_ths;

  int32_t ret = iis3dwb_read_reg(ctx, IIS3DWB_WAKE_UP_THS,
                         (uint8_t *)&wake_up_ths, 1);

  if (ret == 0)
  {
    wake_up_ths.wk_ths = (uint8_t)val;
    ret = iis3dwb_write_reg(ctx, IIS3DWB_WAKE_UP_THS,
                            (uint8_t *)&wake_up_ths, 1);
  }

  if (ret == 0)
  {
    ret = iis3dwb_read_reg(ctx, IIS3DWB_INTERRUPTS_EN,
                           (uint8_t *)&interrupts_en, 1);
  }

  if (ret == 0)
  {
    interrupts_en.interrupts_enable = PROPERTY_ENABLE;
    ret = iis3dwb_write_reg(ctx, IIS3DWB_INTERRUPTS_EN,
                            (uint8_t *)&interrupts_en, 1);
  }

  return ret;
}

/**
  * @brief  Threshold for wakeup: 1 LSB weight depends on WAKE_THS_W in
  *         WAKE_UP_DUR.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of wk_ths in reg WAKE_UP_THS
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t iis3dwb_wkup_threshold_get(const stmdev_ctx_t *ctx, uint8_t *val)
{
  iis3dwb_wake_up_ths_t wake_up_ths;

  int32_t ret = iis3dwb_read_reg(ctx, IIS3DWB_WAKE_UP_THS,
                         (uint8_t *)&wake_up_ths, 1);
  *val = wake_up_ths.wk_ths;

  return ret;
}

/**
  * @brief  Wake up duration event( 1LSb = 1 / ODR ).[set]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of usr_off_on_wu in reg WAKE_UP_THS
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t iis3dwb_xl_usr_offset_on_wkup_set(const stmdev_ctx_t *ctx,
                                          uint8_t val)
{
  iis3dwb_wake_up_ths_t wake_up_ths;

  int32_t ret = iis3dwb_read_reg(ctx, IIS3DWB_WAKE_UP_THS,
                         (uint8_t *)&wake_up_ths, 1);

  if (ret == 0)
  {
    wake_up_ths.usr_off_on_wu = (uint8_t)val;
    ret = iis3dwb_write_reg(ctx, IIS3DWB_WAKE_UP_THS,
                            (uint8_t *)&wake_up_ths, 1);
  }

  return ret;
}

/**
  * @brief  Wake up duration event( 1LSb = 1 / ODR ).[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of usr_off_on_wu in reg WAKE_UP_THS
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t iis3dwb_xl_usr_offset_on_wkup_get(const stmdev_ctx_t *ctx,
                                          uint8_t *val)
{
  iis3dwb_wake_up_ths_t wake_up_ths;

  int32_t ret = iis3dwb_read_reg(ctx, IIS3DWB_WAKE_UP_THS,
                         (uint8_t *)&wake_up_ths, 1);
  *val = wake_up_ths.usr_off_on_wu;

  return ret;
}

/**
  * @brief  Wake up duration event(1LSb = 1 / ODR).[set]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of wake_dur in reg WAKE_UP_DUR
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t iis3dwb_wkup_dur_set(const stmdev_ctx_t *ctx, uint8_t val)
{
  iis3dwb_wake_up_dur_t wake_up_dur;

  int32_t ret = iis3dwb_read_reg(ctx, IIS3DWB_WAKE_UP_DUR,
                         (uint8_t *)&wake_up_dur, 1);

  if (ret == 0)
  {
    wake_up_dur.wake_dur = (uint8_t)val;
    ret = iis3dwb_write_reg(ctx, IIS3DWB_WAKE_UP_DUR,
                            (uint8_t *)&wake_up_dur, 1);
  }

  return ret;
}

/**
  * @brief  Wake up duration event(1LSb = 1 / ODR).[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of wake_dur in reg WAKE_UP_DUR
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t iis3dwb_wkup_dur_get(const stmdev_ctx_t *ctx, uint8_t *val)
{
  iis3dwb_wake_up_dur_t wake_up_dur;

  int32_t ret = iis3dwb_read_reg(ctx, IIS3DWB_WAKE_UP_DUR,
                         (uint8_t *)&wake_up_dur, 1);
  *val = wake_up_dur.wake_dur;

  return ret;
}

/**
  * @}
  *
  */

/**
  * @defgroup   IIS3DWB_ Activity/Inactivity_detection
  * @brief      This section groups all the functions concerning
  *             activity/inactivity detection.
  * @{
  *
  */

/**
  * @brief  Duration to go in sleep mode (1 LSb = 512 / ODR).[set]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of sleep_dur in reg WAKE_UP_DUR
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t iis3dwb_act_sleep_dur_set(const stmdev_ctx_t *ctx, uint8_t val)
{
  iis3dwb_wake_up_dur_t wake_up_dur;

  int32_t ret = iis3dwb_read_reg(ctx, IIS3DWB_WAKE_UP_DUR,
                         (uint8_t *)&wake_up_dur, 1);

  if (ret == 0)
  {
    wake_up_dur.sleep_dur = (uint8_t)val;
    ret = iis3dwb_write_reg(ctx, IIS3DWB_WAKE_UP_DUR,
                            (uint8_t *)&wake_up_dur, 1);
  }

  return ret;
}

/**
  * @brief  Duration to go in sleep mode.(1 LSb = 512 / ODR).[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of sleep_dur in reg WAKE_UP_DUR
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t iis3dwb_act_sleep_dur_get(const stmdev_ctx_t *ctx, uint8_t *val)
{
  iis3dwb_wake_up_dur_t wake_up_dur;

  int32_t ret = iis3dwb_read_reg(ctx, IIS3DWB_WAKE_UP_DUR,
                         (uint8_t *)&wake_up_dur, 1);
  *val = wake_up_dur.sleep_dur;

  return ret;
}

/**
  * @}
  *
  */

/**
  * @defgroup   IIS3DWB_fifo
  * @brief      This section group all the functions concerning
  *             the fifo usage
  * @{
  *
  */

/**
  * @brief  FIFO watermark level selection.[set]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of wtm in reg FIFO_CTRL1
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t iis3dwb_fifo_watermark_set(const stmdev_ctx_t *ctx, uint16_t val)
{
  iis3dwb_fifo_ctrl1_t fifo_ctrl1;
  iis3dwb_fifo_ctrl2_t fifo_ctrl2;

  int32_t ret = iis3dwb_read_reg(ctx, IIS3DWB_FIFO_CTRL2,
                         (uint8_t *)&fifo_ctrl2, 1);

  if (ret == 0)
  {
    fifo_ctrl1.wtm = (uint8_t)(0x00FFU & val);
    ret = iis3dwb_write_reg(ctx, IIS3DWB_FIFO_CTRL1,
                            (uint8_t *)&fifo_ctrl1, 1);
  }

  if (ret == 0)
  {
    fifo_ctrl2.wtm = (uint8_t)((0x0100U & val) >> 8);
    ret = iis3dwb_write_reg(ctx, IIS3DWB_FIFO_CTRL2,
                            (uint8_t *)&fifo_ctrl2, 1);
  }

  return ret;
}

/**
  * @brief  FIFO watermark level selection.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of wtm in reg FIFO_CTRL1
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t iis3dwb_fifo_watermark_get(const stmdev_ctx_t *ctx, uint16_t *val)
{
  iis3dwb_fifo_ctrl1_t fifo_ctrl1;
  iis3dwb_fifo_ctrl2_t fifo_ctrl2;

  *val = 0;

  int32_t ret = iis3dwb_read_reg(ctx, IIS3DWB_FIFO_CTRL2,
                         (uint8_t *)&fifo_ctrl2, 1);
  if (ret != 0) { return ret; }

  ret = iis3dwb_read_reg(ctx, IIS3DWB_FIFO_CTRL1,
                           (uint8_t *)&fifo_ctrl1, 1);

  *val = fifo_ctrl2.wtm;
  *val = *val << 8;
  *val += fifo_ctrl1.wtm;

  return ret;
}

/**
  * @brief  Sensing chain FIFO stop values memorization at threshold
  *         level.[set]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of stop_on_wtm in reg FIFO_CTRL2
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t iis3dwb_fifo_stop_on_wtm_set(const stmdev_ctx_t *ctx, uint8_t val)
{
  iis3dwb_fifo_ctrl2_t fifo_ctrl2;

  int32_t ret = iis3dwb_read_reg(ctx, IIS3DWB_FIFO_CTRL2,
                         (uint8_t *)&fifo_ctrl2, 1);

  if (ret == 0)
  {
    fifo_ctrl2.stop_on_wtm = (uint8_t)val;
    ret = iis3dwb_write_reg(ctx, IIS3DWB_FIFO_CTRL2,
                            (uint8_t *)&fifo_ctrl2, 1);
  }

  return ret;
}

/**
  * @brief  Sensing chain FIFO stop values memorization at threshold
  *         level.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of stop_on_wtm in reg FIFO_CTRL2
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t iis3dwb_fifo_stop_on_wtm_get(const stmdev_ctx_t *ctx, uint8_t *val)
{
  iis3dwb_fifo_ctrl2_t fifo_ctrl2;

  int32_t ret = iis3dwb_read_reg(ctx, IIS3DWB_FIFO_CTRL2,
                         (uint8_t *)&fifo_ctrl2, 1);
  *val = fifo_ctrl2.stop_on_wtm;

  return ret;
}

/**
  * @brief  Selects Batching Data Rate (writing frequency in FIFO)
  *         for accelerometer data.[set]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of bdr_xl in reg FIFO_CTRL3
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t iis3dwb_fifo_xl_batch_set(const stmdev_ctx_t *ctx,
                                  iis3dwb_bdr_xl_t val)
{
  iis3dwb_fifo_ctrl3_t fifo_ctrl3;

  int32_t ret = iis3dwb_read_reg(ctx, IIS3DWB_FIFO_CTRL3,
                         (uint8_t *)&fifo_ctrl3, 1);

  if (ret == 0)
  {
    fifo_ctrl3.bdr_xl = (uint8_t)val;
    ret = iis3dwb_write_reg(ctx, IIS3DWB_FIFO_CTRL3,
                            (uint8_t *)&fifo_ctrl3, 1);
  }

  return ret;
}

/**
  * @brief  Selects Batching Data Rate (writing frequency in FIFO)
  *         for accelerometer data.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Get the values of bdr_xl in reg FIFO_CTRL3
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t iis3dwb_fifo_xl_batch_get(const stmdev_ctx_t *ctx,
                                  iis3dwb_bdr_xl_t *val)
{
  iis3dwb_fifo_ctrl3_t fifo_ctrl3;

  int32_t ret = iis3dwb_read_reg(ctx, IIS3DWB_FIFO_CTRL3,
                         (uint8_t *)&fifo_ctrl3, 1);

  switch (fifo_ctrl3.bdr_xl)
  {
    case IIS3DWB_XL_NOT_BATCHED:
      *val = IIS3DWB_XL_NOT_BATCHED;
      break;

    case IIS3DWB_XL_BATCHED_AT_26k7Hz:
      *val = IIS3DWB_XL_BATCHED_AT_26k7Hz;
      break;

    default:
      *val = IIS3DWB_XL_NOT_BATCHED;
      break;
  }

  return ret;
}

/**
  * @brief  FIFO mode selection.[set]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of fifo_mode in reg FIFO_CTRL4
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t iis3dwb_fifo_mode_set(const stmdev_ctx_t *ctx,
                              iis3dwb_fifo_mode_t val)
{
  iis3dwb_fifo_ctrl4_t fifo_ctrl4;

  int32_t ret = iis3dwb_read_reg(ctx, IIS3DWB_FIFO_CTRL4,
                         (uint8_t *)&fifo_ctrl4, 1);

  if (ret == 0)
  {
    fifo_ctrl4.fifo_mode = (uint8_t)val;
    ret = iis3dwb_write_reg(ctx, IIS3DWB_FIFO_CTRL4,
                            (uint8_t *)&fifo_ctrl4, 1);
  }

  return ret;
}

/**
  * @brief  FIFO mode selection.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Get the values of fifo_mode in reg FIFO_CTRL4
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t iis3dwb_fifo_mode_get(const stmdev_ctx_t *ctx,
                              iis3dwb_fifo_mode_t *val)
{
  iis3dwb_fifo_ctrl4_t fifo_ctrl4;

  int32_t ret = iis3dwb_read_reg(ctx, IIS3DWB_FIFO_CTRL4,
                         (uint8_t *)&fifo_ctrl4, 1);

  switch (fifo_ctrl4.fifo_mode)
  {
    case IIS3DWB_BYPASS_MODE:
      *val = IIS3DWB_BYPASS_MODE;
      break;

    case IIS3DWB_FIFO_MODE:
      *val = IIS3DWB_FIFO_MODE;
      break;

    case IIS3DWB_STREAM_TO_FIFO_MODE:
      *val = IIS3DWB_STREAM_TO_FIFO_MODE;
      break;

    case IIS3DWB_BYPASS_TO_STREAM_MODE:
      *val = IIS3DWB_BYPASS_TO_STREAM_MODE;
      break;

    case IIS3DWB_STREAM_MODE:
      *val = IIS3DWB_STREAM_MODE;
      break;

    case IIS3DWB_BYPASS_TO_FIFO_MODE:
      *val = IIS3DWB_BYPASS_TO_FIFO_MODE;
      break;

    default:
      *val = IIS3DWB_BYPASS_MODE;
      break;
  }

  return ret;
}

/**
  * @brief  Selects Batching Data Rate (writing frequency in FIFO)
  *         for temperature data.[set]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of odr_t_batch in reg FIFO_CTRL4
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t iis3dwb_fifo_temp_batch_set(const stmdev_ctx_t *ctx,
                                    iis3dwb_odr_t_batch_t val)
{
  iis3dwb_fifo_ctrl4_t fifo_ctrl4;

  int32_t ret = iis3dwb_read_reg(ctx, IIS3DWB_FIFO_CTRL4,
                         (uint8_t *)&fifo_ctrl4, 1);

  if (ret == 0)
  {
    fifo_ctrl4.odr_t_batch = (uint8_t)val;
    ret = iis3dwb_write_reg(ctx, IIS3DWB_FIFO_CTRL4,
                            (uint8_t *)&fifo_ctrl4, 1);
  }

  return ret;
}

/**
  * @brief  Selects Batching Data Rate (writing frequency in FIFO)
  *         for temperature data.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Get the values of odr_t_batch in reg FIFO_CTRL4
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t iis3dwb_fifo_temp_batch_get(const stmdev_ctx_t *ctx,
                                    iis3dwb_odr_t_batch_t *val)
{
  iis3dwb_fifo_ctrl4_t fifo_ctrl4;

  int32_t ret = iis3dwb_read_reg(ctx, IIS3DWB_FIFO_CTRL4,
                         (uint8_t *)&fifo_ctrl4, 1);

  switch (fifo_ctrl4.odr_t_batch)
  {
    case IIS3DWB_TEMP_NOT_BATCHED:
      *val = IIS3DWB_TEMP_NOT_BATCHED;
      break;

    case IIS3DWB_TEMP_BATCHED_AT_104Hz:
      *val = IIS3DWB_TEMP_BATCHED_AT_104Hz;
      break;

    default:
      *val = IIS3DWB_TEMP_NOT_BATCHED;
      break;
  }

  return ret;
}

/**
  * @brief  Selects decimation for timestamp batching in FIFO.
  *         Writing rate will be the maximum rate between XL and
  *         GYRO BDR divided by decimation decoder.[set]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of odr_ts_batch in reg FIFO_CTRL4
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t iis3dwb_fifo_timestamp_batch_set(const stmdev_ctx_t *ctx,
                                         iis3dwb_fifo_timestamp_batch_t val)
{
  iis3dwb_fifo_ctrl4_t fifo_ctrl4;

  int32_t ret = iis3dwb_read_reg(ctx, IIS3DWB_FIFO_CTRL4,
                         (uint8_t *)&fifo_ctrl4, 1);

  if (ret == 0)
  {
    fifo_ctrl4.odr_ts_batch = (uint8_t)val;
    ret = iis3dwb_write_reg(ctx, IIS3DWB_FIFO_CTRL4,
                            (uint8_t *)&fifo_ctrl4, 1);
  }

  return ret;
}

/**
  * @brief  Selects decimation for timestamp batching in FIFO.
  *         Writing rate will be the maximum rate between XL and
  *         GYRO BDR divided by decimation decoder.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Get the values of odr_ts_batch in reg
  *                                 FIFO_CTRL4
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t iis3dwb_fifo_timestamp_batch_get(const stmdev_ctx_t *ctx,
                                         iis3dwb_fifo_timestamp_batch_t *val)
{
  iis3dwb_fifo_ctrl4_t fifo_ctrl4;

  int32_t ret = iis3dwb_read_reg(ctx, IIS3DWB_FIFO_CTRL4,
                         (uint8_t *)&fifo_ctrl4, 1);

  switch (fifo_ctrl4.odr_ts_batch)
  {
    case IIS3DWB_NO_DECIMATION:
      *val = IIS3DWB_NO_DECIMATION;
      break;

    case IIS3DWB_DEC_1:
      *val = IIS3DWB_DEC_1;
      break;

    case IIS3DWB_DEC_8:
      *val = IIS3DWB_DEC_8;
      break;

    case IIS3DWB_DEC_32:
      *val = IIS3DWB_DEC_32;
      break;

    default:
      *val = IIS3DWB_NO_DECIMATION;
      break;
  }

  return ret;
}

/**
  * @brief  Resets the internal counter of batching events for a single sensor.
  *         This bit is automatically reset to zero if it was set to ‘1’.[set]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of rst_counter_bdr in reg COUNTER_BDR_REG1
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t iis3dwb_rst_batch_counter_set(const stmdev_ctx_t *ctx, uint8_t val)
{
  iis3dwb_counter_bdr_reg1_t counter_bdr_reg1;

  int32_t ret = iis3dwb_read_reg(ctx, IIS3DWB_COUNTER_BDR_REG1,
                         (uint8_t *)&counter_bdr_reg1, 1);

  if (ret == 0)
  {
    counter_bdr_reg1.rst_counter_bdr = (uint8_t)val;
    ret = iis3dwb_write_reg(ctx, IIS3DWB_COUNTER_BDR_REG1,
                            (uint8_t *)&counter_bdr_reg1, 1);
  }

  return ret;
}

/**
  * @brief  Resets the internal counter of batching events for a single sensor.
  *         This bit is automatically reset to zero if it was set to ‘1’.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of rst_counter_bdr in reg COUNTER_BDR_REG1
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t iis3dwb_rst_batch_counter_get(const stmdev_ctx_t *ctx, uint8_t *val)
{
  iis3dwb_counter_bdr_reg1_t counter_bdr_reg1;

  int32_t ret = iis3dwb_read_reg(ctx, IIS3DWB_COUNTER_BDR_REG1,
                         (uint8_t *)&counter_bdr_reg1, 1);
  *val = counter_bdr_reg1.rst_counter_bdr;

  return ret;
}

/**
  * @brief  Batch data rate counter.[set]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of cnt_bdr_th in reg COUNTER_BDR_REG2
  *                and COUNTER_BDR_REG1.
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t iis3dwb_batch_counter_threshold_set(const stmdev_ctx_t *ctx,
                                            uint16_t val)
{
  iis3dwb_counter_bdr_reg2_t counter_bdr_reg1;
  iis3dwb_counter_bdr_reg2_t counter_bdr_reg2;

  int32_t ret = iis3dwb_read_reg(ctx, IIS3DWB_COUNTER_BDR_REG1,
                         (uint8_t *)&counter_bdr_reg1, 1);

  if (ret == 0)
  {
    counter_bdr_reg1.cnt_bdr_th = (uint8_t)((0x0700U & val) >> 8);
    ret = iis3dwb_write_reg(ctx, IIS3DWB_COUNTER_BDR_REG1,
                            (uint8_t *)&counter_bdr_reg1, 1);
  }

  if (ret == 0)
  {
    counter_bdr_reg2.cnt_bdr_th = (uint8_t)(0x00FFU & val);
    ret = iis3dwb_write_reg(ctx, IIS3DWB_COUNTER_BDR_REG2,
                            (uint8_t *)&counter_bdr_reg2, 1);
  }

  return ret;
}

/**
  * @brief  Batch data rate counter.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of cnt_bdr_th in reg COUNTER_BDR_REG2
  *                and COUNTER_BDR_REG1.
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t iis3dwb_batch_counter_threshold_get(const stmdev_ctx_t *ctx,
                                            uint16_t *val)
{
  iis3dwb_counter_bdr_reg1_t counter_bdr_reg1;
  iis3dwb_counter_bdr_reg2_t counter_bdr_reg2;

  *val = 0;

  int32_t ret = iis3dwb_read_reg(ctx, IIS3DWB_COUNTER_BDR_REG1,
                         (uint8_t *)&counter_bdr_reg1, 1);
  if (ret != 0) { return ret; }

  ret = iis3dwb_read_reg(ctx, IIS3DWB_COUNTER_BDR_REG2,
                           (uint8_t *)&counter_bdr_reg2, 1);
  if (ret != 0) { return ret; }

  *val = counter_bdr_reg1.cnt_bdr_th;
  *val = *val << 8;
  *val += counter_bdr_reg2.cnt_bdr_th;

  return ret;
}

/**
  * @brief  Number of unread sensor data (TAG + 6 bytes) stored in FIFO.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Change the values of diff_fifo in reg FIFO_STATUS1
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t iis3dwb_fifo_data_level_get(const stmdev_ctx_t *ctx, uint16_t *val)
{
  iis3dwb_fifo_status1_t fifo_status1;
  iis3dwb_fifo_status2_t fifo_status2;

  int32_t ret = iis3dwb_read_reg(ctx, IIS3DWB_FIFO_STATUS1,
                         (uint8_t *)&fifo_status1, 1);

  if (ret == 0)
  {
    ret = iis3dwb_read_reg(ctx, IIS3DWB_FIFO_STATUS2,
                           (uint8_t *)&fifo_status2, 1);
    *val = fifo_status2.diff_fifo;
    *val = *val << 8;
    *val += fifo_status1.diff_fifo;
  }

  return ret;
}

/**
  * @brief  Smart FIFO status.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    Registers FIFO_STATUS1 and FIFO_STATUS2
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t iis3dwb_fifo_status_get(const stmdev_ctx_t *ctx,
                                iis3dwb_fifo_status_t *val)
{
  uint8_t buff[2];
  iis3dwb_fifo_status2_t status;

  int32_t ret = iis3dwb_read_reg(ctx, IIS3DWB_FIFO_STATUS1, (uint8_t *)&buff[0], 2);
  bytecpy((uint8_t *)&status, &buff[1]);

  val->fifo_bdr = status.counter_bdr_ia;
  val->fifo_ovr = status.fifo_ovr_ia | status.fifo_ovr_latched;
  val->fifo_full = status.fifo_full_ia;
  val->fifo_th = status.fifo_wtm_ia;

  val->fifo_level = (uint16_t)buff[1] & 0x03U;
  val->fifo_level = (val->fifo_level * 256U) + buff[0];

  return ret;
}

/**
  * @}
  *
  */
