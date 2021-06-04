/* 
 *  > File Name: pcolor.h
 *  > Action: define printf output style settings
 */

#ifndef PCOLOR_H
#define PCOLOR_H

/* Set printf font color */
#define PRINT_FONT_BLA  printf("\033[30m") // Black
#define PRINT_FONT_RED  printf("\033[31m") // Red
#define PRINT_FONT_GRE  printf("\033[32m") // Green
#define PRINT_FONT_YEL  printf("\033[33m") // Yellow
#define PRINT_FONT_BLU  printf("\033[34m") // Blue
#define PRINT_FONT_MAG  printf("\033[35m") // Magenta
#define PRINT_FONT_CYA  printf("\033[36m") // Cyan
#define PRINT_FONT_WHI  printf("\033[37m") // White

/* Set printf background color */
#define PRINT_BACK_BLA  printf("\033[40m"); // Black
#define PRINT_BACK_RED  printf("\033[41m"); // Red
#define PRINT_BACK_GRE  printf("\033[42m"); // Green
#define PRINT_BACK_YEL  printf("\033[43m"); // Yellow
#define PRINT_BACK_BLU  printf("\033[44m"); // Blue
#define PRINT_BACK_MAG  printf("\033[45m"); // Magenta
#define PRINT_BACK_CYA  printf("\033[46m"); // Cyan
#define PRINT_BACK_WHI  printf("\033[47m"); // White

/* Set printf attribute */
#define PRINT_ATTR_REC  printf("\033[0m");  // Reset the properties to the default settings
#define PRINT_ATTR_BOL  printf("\033[1m");  // Set bold 
#define PRINT_ATTR_LIG  printf("\033[2m");  // Set half brightness (simulate color of color monitor) 
#define PRINT_ATTR_LIN  printf("\033[4m");  // Set underline (simulate color of color display)
#define PRINT_ATTR_GLI  printf("\033[5m");  // Set flicker 
#define PRINT_ATTR_REV  printf("\033[7m");  // Set reverse image 
#define PRINT_ATTR_THI  printf("\033[22m"); // Set general density 
#define PRINT_ATTR_ULIN  printf("\033[24m");// Turn off underline 
#define PRINT_ATTR_UGLI  printf("\033[25m");// Blink off 
#define PRINT_ATTR_UREV  printf("\033[27m");// Turn off reverse image

#endif