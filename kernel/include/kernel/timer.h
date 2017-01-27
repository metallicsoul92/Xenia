#ifndef TIMER_H_
#define TIMER_H_

#include "../../arch/i386/irq.h"

//we will use an int to represent ticks
int ticks = 0;

void timer_handler(struct regs *r)
{
    /* Increment our 'tick count' */
    ticks++;

    /* Every 18 clocks (approximately 1 second), we will
    *  display a message on the screen */
    if (ticks % 18 == 0)
    {
        //do something here, update something?
    }
}
/* This will continuously loop until the given time has
*  been reached */
void timer_wait(int pticks)
{
    unsigned long eticks;

    eticks = ticks + pticks;
    while(ticks < eticks);
}

/* Sets up the system clock by installing the timer handler
*  into IRQ0 */
void timer_install()
{
    /* Installs 'timer_handler' to IRQ0 */
    irq_install_handler(0, timer_handler);
}

#endif
