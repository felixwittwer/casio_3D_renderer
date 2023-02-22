/*****************************************************************/
/*                                                               */
/*   CASIO fx-9860G SDK Library                                  */
/*                                                               */
/*   File name : [ProjectName].c                                 */
/*                                                               */
/*   Copyright (c) 2006 CASIO COMPUTER CO., LTD.                 */
/*                                                               */
/*****************************************************************/
#include "fxlib.h"
#include <stdio.h>
#include <math.h>
#include <mathf.h>

void DrawCube(int x, int y, int heigth, int rotatez, int radius, float stretchx, float stretchy, int debug){
    int iteration = 0;
    float rad = 0;
    float radone = 0;
    float radtwo = 0;

    if(debug==1){
        while(iteration<360){
            Bdisp_SetPoint_VRAM(stretchx*(radius*sin(iteration))+x, stretchy*(radius*cos(iteration))+y, 1);
            Bdisp_SetPoint_VRAM(stretchx*(radius*sin(iteration))+x, stretchy*(radius*cos(iteration))+y+heigth, 1);
            iteration = iteration + 1;
        }
    }

    //draw vertical lines of cube
    iteration = 0;
    while(iteration<361){
        rad = ((iteration+rotatez)/180.0)*3.141592;
        Bdisp_DrawLineVRAM(stretchx*(radius*sin(rad))+x, stretchy*(radius*cos(rad))+y, stretchx*(radius*sin(rad))+x, stretchy*(radius*cos(rad))+y+heigth);
        iteration = iteration +90;
    }

    //conect vertical lines
    iteration = 0;
    while(iteration<361){
        radone = ((iteration+rotatez)/180.0)*3.141592;
        radtwo = (((iteration+90)+rotatez)/180.0)*3.141592;
        Bdisp_DrawLineVRAM(stretchx*(radius*sin(radone))+x, stretchy*(radius*cos(radone))+y+heigth, stretchx*(radius*sin(radtwo))+x, stretchy*(radius*cos(radtwo))+y+heigth);
        Bdisp_DrawLineVRAM(stretchx*(radius*sin(radone))+x, stretchy*(radius*cos(radone))+y, stretchx*(radius*sin(radtwo))+x, stretchy*(radius*cos(radtwo))+y);
        iteration = iteration +90;
    }

    // Bdisp_SetPoint_VRAM(stretchx*(radius*sin(rad))+x, stretchy*(radius*cos(rad))+y+10, 1);
}

void DrawPyramid(int x, int y, int heigth, int rotatez, int radius, float stretchx, float stretchy, int nr_sides,int debug){
    int iteration = 0;
    float rad = 0;
    float radone = 0;
    float radtwo = 0;

    if(debug==1){
        while(iteration<360){
            Bdisp_SetPoint_VRAM(stretchx*(radius*sin(iteration))+x, stretchy*(radius*cos(iteration))+y, 1);
            iteration = iteration + 1;
        }
    }

     //draw vertical lines of pyramid
    iteration = 0;
    while(iteration<361){
        rad = ((iteration+rotatez)/180.0)*3.141592;
        Bdisp_DrawLineVRAM(x, y-heigth, stretchx*(radius*sin(rad))+x, stretchy*(radius*cos(rad))+y);
        iteration = iteration + (360/nr_sides);
    }

    //conect vertical lines
    iteration = 0;
    while(iteration<361){
        radone = ((iteration+rotatez)/180.0)*3.141592;
        radtwo = (((iteration+(360/nr_sides))+rotatez)/180.0)*3.141592;
        Bdisp_DrawLineVRAM(stretchx*(radius*sin(radone))+x, stretchy*(radius*cos(radone))+y, stretchx*(radius*sin(radtwo))+x, stretchy*(radius*cos(radtwo))+y);
        iteration = iteration + (360/nr_sides);
    }

}

void DrawPrism(int x, int y, int heigth, int rotatez, int radius, float stretchx, float stretchy, int nr_sides,int debug){
    int iteration = 0;
    float rad = 0;
    float radone = 0;
    float radtwo = 0;

    if(debug==1){
        while(iteration<360){
            Bdisp_SetPoint_VRAM(stretchx*(radius*sin(iteration))+x, stretchy*(radius*cos(iteration))+y, 1);
            iteration = iteration + 1;
        }
    }

     //draw vertical lines of pyramid
    iteration = 0;
    while(iteration<361){
        rad = ((iteration+rotatez)/180.0)*3.141592;
        Bdisp_DrawLineVRAM(stretchx*(radius*sin(rad))+x, stretchy*(radius*cos(rad))+y, stretchx*(radius*sin(rad))+x, stretchy*(radius*cos(rad))+y-heigth);
        iteration = iteration + (360/nr_sides);
    }

    //conect vertical lines
    iteration = 0;
    while(iteration<361){
        radone = ((iteration+rotatez)/180.0)*3.141592;
        radtwo = (((iteration+(360/nr_sides))+rotatez)/180.0)*3.141592;
        Bdisp_DrawLineVRAM(stretchx*(radius*sin(radone))+x, stretchy*(radius*cos(radone))+y-heigth, stretchx*(radius*sin(radtwo))+x, stretchy*(radius*cos(radtwo))+y-heigth);
        Bdisp_DrawLineVRAM(stretchx*(radius*sin(radone))+x, stretchy*(radius*cos(radone))+y, stretchx*(radius*sin(radtwo))+x, stretchy*(radius*cos(radtwo))+y);
        iteration = iteration + (360/nr_sides);
    }

}


//****************************************************************************
//  AddIn_main (Sample program main function)
//
//  param   :   isAppli   : 1 = This application is launched by MAIN MENU.
//                        : 0 = This application is launched by a strip in eACT application.
//
//              OptionNum : Strip number (0~3)
//                         (This parameter is only used when isAppli parameter is 0.)
//
//  retval  :   1 = No error / 0 = Error
//
//****************************************************************************
int AddIn_main(int isAppli, unsigned short OptionNum)
{
    unsigned int key;
    int rotatez = 20;
    float stretchx = 1;
    float stretchy = 0.3;
    int sidelength = 20;

    Bdisp_AllClr_DDVRAM();

    while(1){
        GetKey(&key);
        Bdisp_AllClr_DDVRAM();
        if(key==KEY_CTRL_RIGHT){
            rotatez = rotatez + 10;
        }else if(key==KEY_CTRL_LEFT){
            rotatez = rotatez - 10;
        }
        DrawCube(25,10,sidelength,rotatez,sidelength,stretchx,stretchy,0);
        DrawPyramid(60,55,30,rotatez,sidelength,stretchx,stretchy,4,0);
        DrawPrism(100,35,25,rotatez,sidelength,stretchx,stretchy,7,0);
    }

    return 1;
}


//****************************************************************************
//**************                                              ****************
//**************                 Notice!                      ****************
//**************                                              ****************
//**************  Please do not change the following source.  ****************
//**************                                              ****************
//****************************************************************************


#pragma section _BR_Size
unsigned long BR_Size;
#pragma section


#pragma section _TOP

//****************************************************************************
//  InitializeSystem
//
//  param   :   isAppli   : 1 = Application / 0 = eActivity
//              OptionNum : Option Number (only eActivity)
//
//  retval  :   1 = No error / 0 = Error
//
//****************************************************************************
int InitializeSystem(int isAppli, unsigned short OptionNum)
{
    return INIT_ADDIN_APPLICATION(isAppli, OptionNum);
}

#pragma section

