/*==================[inclusions]=============================================*/
#include "../inc/principal.h"         /* <= own header */
#include "os.h"               /* <= operating system header */
#include "ciaaPOSIX_stdio.h"  /* <= device handler header */
#include "ciaaPOSIX_string.h" /* <= string header */
#include "ciaak.h"            /* <= ciaa kernel header */

/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/
static uint8 led1=0;
static uint8 led2=0;
static uint8 led3=0;
static uint8 led4;
static int n;
static int salida;
/*==================[external data definition]===============================*/
/*==================[internal functions definition]==========================*/
/**  File descriptor for digital output ports
 *   Device path /dev/dio/out/0
 */
static int32_t leds;
/**  File descriptor for digital input ports
 *   Device path /dev/dio/in/0
 */
static int32_t buttons;

int main(void)
{
   /* Starts the operating system in the Application Mode 1 */
   /* This example has only one Application Mode */
   StartOS(AppMode1);

   /* StartOs shall never returns, but to avoid compiler warnings or errors
    * 0 is returned */
   return 0;
}

void ErrorHook(void)
{
   ciaaPOSIX_printf("ErrorHook was called\n");
   ciaaPOSIX_printf("Service: %d, P1: %d, P2: %d, P3: %d, RET: %d\n", OSErrorGetServiceId(), OSErrorGetParam1(), OSErrorGetParam2(), OSErrorGetParam3(), OSErrorGetRet());
   ShutdownOS(0);
}

/** Initial task
 *  This task is started automatically in the application mode 1.
 */
TASK(InitTask)
{
   /* init CIAA kernel and devices */
   ciaak_start();

   /* print message (only on x86) */
   ciaaPOSIX_printf("Init Task...\n");

   /* open CIAA digital outputs & inputs */
   leds = ciaaPOSIX_open(OUTPUTS, ciaaPOSIX_O_RDWR);
   buttons = ciaaPOSIX_open(INPUTS, ciaaPOSIX_O_RDONLY);

   n = 0;
   salida = 0;

   SetRelAlarm(ActivateTask1, 400, 400);
   SetRelAlarm(ActivateTask2, 600, 600);
   SetRelAlarm(ActivateTask3, 800, 800);
   SetRelAlarm(ActivatePeriodicTask5, 350, 50);
   SetRelAlarm(ActivateSwitchesTask, 350, 100);

   TerminateTask();
}

/**
 * Prende Led 1
 * Y muestra en archivo de salida (openocd) N*1
 *  */
TASK(Task1)
{
	uint8 outputs;
	/* write blinking message */
	ciaaPOSIX_printf("Task1\n");

	/* blink output */
	ciaaPOSIX_read(leds, &outputs, 1);
	outputs ^= 0x08;
	ciaaPOSIX_write(leds, &outputs, 1);

   TerminateTask();
}

/**
 * Prende Led 2
 * Y muestra en archivo de salida (openocd) N*10
 *  */
TASK(Task2)
{
	uint8 outputs;
	/* write blinking message */
	ciaaPOSIX_printf("Task2\n");

	/* blink output */
	ciaaPOSIX_read(leds, &outputs, 1);
	outputs ^= 0x10;
	ciaaPOSIX_write(leds, &outputs, 1);

   /* terminate task */
   TerminateTask();
}

/**
 * Prende Led 3
 * Y muestra en archivo de salida (openocd) N*100
 *  */
TASK(Task3)
{
	uint8 outputs;
	/* write blinking message */
	ciaaPOSIX_printf("Task3\n");

	/* blink output */
	ciaaPOSIX_read(leds, &outputs, 1);
	outputs ^= 0x20;
	ciaaPOSIX_write(leds, &outputs, 1);

   /* terminate task */
   TerminateTask();
}

TASK(Task4)
{
	n++;

	TerminateTask();
}

TASK(PeriodicTask5)
{
	uint8 outputs;

	if(led4 == 1){
		ciaaPOSIX_read(leds, &outputs, 1);
		outputs = outputs | 0x01;
		ciaaPOSIX_write(leds, &outputs, 1);
	}

	if(led4 == 0){
		ciaaPOSIX_read(leds, &outputs, 1);
		outputs = outputs & 0xFE;
		ciaaPOSIX_write(leds, &outputs, 1);
	}

	//Imprime n*1000

	TerminateTask();
}

TASK(SwitchesTask)
{
	uint8 inputs;
	ciaaPOSIX_read(buttons, &inputs, 1);

	if((inputs&0x01) == 0){
		if(led4 == 0){
			led4 = 1;
		}else{
			led4 = 0;
		}
	}

	if((inputs&0x08) == 0){
		ActivateTask(Task4);
	}

	TerminateTask();
}

/** @} doxygen end group definition */
/*==================[end of file]============================================*/

