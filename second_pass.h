/* Authors: Daniel Popov & Maor Maayan                        */
/* File   : second_pass.h                                     */
/*                                                            */
/* Description: Handles label operands and label attributes   */
/*------------------------------------------------------------*/
#ifndef SECOND_PASS_H
#define SECOND_PASS_H

/* Includes :               */
#include "line_structure.h"
#include "label_structure.h"
#include "extra_structure.h"
#include "code_img.h"
#include "operands.h"
#include "globals.h"


bool second_pass(code_img **head_code, line **head_line, label **head_label, extra **head_extra);

#endif