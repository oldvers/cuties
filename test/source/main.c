#include <stdio.h>

#include "types.h"
#include "log.h"

#include "FreeRTOS.h"
#include "task.h"

/* -------------------------------------------------------------------------- */

typedef FW_BOOLEAN (* TestFunction_t)(void);

static U32 gPass                  = 0;
static U32 gFail                  = 0;
static U32 gTested                = 0;
static U32 gTotal                 = 0;

extern void  vTestStartUpFunction ( void );
extern void  vTestPrepareFunction ( void );
extern void  vTestHelpTaskFunction( void * pvParameters );
extern U32   uiTestsGetCount      ( void );

extern const TestFunction_t       gTests[];

/* -------------------------------------------------------------------------- */

static void vLogTestResult(FW_BOOLEAN result)
{
  if (FW_TRUE == result)
  {
    LOG_SetTextColorGreen();
    LOG(" ----> PASS\r\n");
    gPass++;
  }
  else
  {
    LOG_SetTextColorRed();
    LOG(" ----> FAIL\r\n");
    gFail++;
  }
  LOG_SetDefaultColors();
  gTested++;
}

/* -------------------------------------------------------------------------- */

void vTestMainTask(void * pvParameters)
{
  FW_BOOLEAN result = FW_FALSE;
  U32        test   = 0;

  LOG("-----------------------------------------------------------\r\n");
  LOG(" --- Test Main Task Started\r\n");

  gTotal = uiTestsGetCount();

  for (test = 0; test < gTotal; test++)
  {
    LOG_SetTextColorYellow();
    LOG("-----------------------------------------------------------\r\n");
    LOG_SetDefaultColors();
    result = gTests[test]();
    vLogTestResult(result);
    if (FW_FALSE == result) break;
  }

  LOG_SetTextColorYellow();
  LOG("-----------------------------------------------------------\r\n");

  LOG_SetDefaultColors();
  LOG(" - Total  = %d\r\n", gTotal);
  LOG(" - Tested = %d  ", gTested);

  if (0 < gPass)
  {
    LOG_SetTextColorGreen();
  }
  else
  {
    LOG_SetDefaultColors();
  }
  LOG("Pass = %d  ", gPass);

  if (0 < gFail)
  {
    LOG_SetTextColorRed();
  }
  else
  {
    LOG_SetDefaultColors();
  }
  LOG("Fail = %d\r\n", gFail);

  LOG_SetTextColorYellow();
  LOG("-----------------------------------------------------------\r\n");
  LOG_SetDefaultColors();

  while (FW_TRUE)
  {
    vTaskDelay(500);
  }
}

/* -------------------------------------------------------------------------- */

int main(void)
{
  LOG_Init();
  LOG_DisableControlCodes();
  LOG_SetDefaultColors();

  vTestStartUpFunction();

  LOG("-----------------------------------------------------------\r\n");
  LOG("Simulator Started!\r\n");
  LOG("CPU clock = %d Hz\r\n", CPUClock);

  LOG("Preparing Test Tasks To Run...\r\n");

  vTestPrepareFunction();

  xTaskCreate
  (
    vTestMainTask,
    "TestMainTask",
    configMINIMAL_STACK_SIZE * 2,
    NULL,
    tskIDLE_PRIORITY + 2,
    NULL
  );

  xTaskCreate
  (
    vTestHelpTaskFunction,
    "TestHelpTask",
    configMINIMAL_STACK_SIZE * 2,
    NULL,
    tskIDLE_PRIORITY + 1,
    NULL
  );

  vTaskStartScheduler();

  while (FW_TRUE) {};
}

/* -------------------------------------------------------------------------- */
