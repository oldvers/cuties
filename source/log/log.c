#include <stdio.h>
#include "types.h"
#include "log.h"

/* -------------------------------------------------------------------------- */

/* The following function must be implemented externally to initialize the
 * proper debug interface, like UART, RTT, SWO, etc. So the printf function
 * will output the logs into the appropriate interface. */
extern void DBG_Init(void);

/* -------------------------------------------------------------------------- */

static FW_BOOLEAN gCtrlCodesEnabled = FW_TRUE;

/* -------------------------------------------------------------------------- */

void LOG_Init(void)
{
  /* Initialize the Debug Interface */
  DBG_Init();
}

/* -------------------------------------------------------------------------- */

void LOG_SetDefaultColors(void)
{
  if (FW_TRUE == gCtrlCodesEnabled)
  {
    LOG(LOG_CTRL_RESET);
  }
}

/* -------------------------------------------------------------------------- */

void LOG_ClearScreen(void)
{
  if (FW_TRUE == gCtrlCodesEnabled)
  {
    LOG(LOG_CTRL_CLEAR"\r\n");
  }
}

/* -------------------------------------------------------------------------- */

void LOG_SetTextColorRed(void)
{
  if (FW_TRUE == gCtrlCodesEnabled)
  {
    LOG(LOG_CTRL_TEXT_RED);
  }
}

/* -------------------------------------------------------------------------- */

void LOG_SetTextColorGreen(void)
{
  if (FW_TRUE == gCtrlCodesEnabled)
  {
    LOG(LOG_CTRL_TEXT_GREEN);
  }
}

/* -------------------------------------------------------------------------- */

void LOG_SetTextColorYellow(void)
{
  if (FW_TRUE == gCtrlCodesEnabled)
  {
    LOG(LOG_CTRL_TEXT_YELLOW);
  }
}

/* -------------------------------------------------------------------------- */

void LOG_SetTextColorBlue(void)
{
  if (FW_TRUE == gCtrlCodesEnabled)
  {
    LOG(LOG_CTRL_TEXT_BLUE);
  }
}

/* -------------------------------------------------------------------------- */

void LOG_DisableControlCodes(void)
{
  gCtrlCodesEnabled = FW_FALSE;
}

/* -------------------------------------------------------------------------- */
