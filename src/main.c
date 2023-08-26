#include "board_ctrl.h"

#include "board_cfg.h"

void main(void)
{
    boardCtrl_configureBoard();

    boardCtrl_ledActive(LED0);
    boardCtrl_ledActive(LED1);
}