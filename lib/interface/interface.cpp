#include <lvgl.h>

#include <GxTFT.h> // Hardware-specific library
#include <GxIO/STM32MICRO/GxIO_STM32F4_FSMC/GxIO_STM32F4_FSMC.h>
#include <GxCTRL/GxCTRL_R61529/GxCTRL_R61529.h> 

#define TFT_Class GxTFT

GxIO_Class io;
GxCTRL_Class controller(io); 
TFT_Class tft(io, controller, 320, 480);


void interface_init()
{
    //******************************LVGL STUFF******************************
  tft.init();

  lv_init(); //might need to put before eSPI init.

  lv_disp_buf_init(&disp_buf, buf, NULL, LV_HOR_RES_MAX * 10);

  /*Initialize the display*/
  
  lv_disp_drv_init(&disp_drv);
  disp_drv.hor_res = 320;
  disp_drv.ver_res = 480;
  disp_drv.flush_cb = my_disp_flush;
  disp_drv.buffer = &disp_buf;
  lv_disp_drv_register(&disp_drv);

  /*Initialize the input device driver*/
  
  lv_indev_drv_init(&indev_drv);             /*Descriptor of a input device driver*/
  indev_drv.type = LV_INDEV_TYPE_POINTER;    /*Touch pad is a pointer-like device*/
  indev_drv.read_cb = my_input_read;      /*Set your driver function*/
  lv_indev_drv_register(&indev_drv);         /*Finally register the driver*/
}