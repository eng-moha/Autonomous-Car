/*
 * GI_program.c
 *
 * Created: 9/9/2023 11:29:21 PM
 *  Author:  Autonomous Car Team
 */ 


/* UTILES_LIB */
#include "STD_TYPES.h"
#include "BIT_MATH.h"

/* MCAL */
#include "GI_interface.h"
#include "GI_private.h"


void GI_enable(void)
{
	SET_BIT(SREG,I);
}


void GI_disable(void)
{
	CLR_BIT(SREG,I);
}