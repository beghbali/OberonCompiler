#ifndef _ARCHITECTURE_H_
#define _ARCHITECTURE_H_
#define POINTER_SIZE int

typedef POINTER_SIZE addr_type;

#define NUMBER_OF_DEFAULT_REGISTERS 8
#define NUMBER_OF_OUTPUT_REGISTERS 6
#define NUMBER_OF_INPUT_REGISTERS 6

#define GLOBAL_POINTER  "%gp"
#define STACK_POINTER   "%sp"
#define FRAME_POINTER   "%fp"

#define GLOBAL_POINTER_ADDR 0
#define STACK_POINTER_ADDR  0
#define FRAME_POINTER_ADDR  0

#define MOV_IM_UPPER_LIMIT 4096
#define MOV_IM_LOWER_LIMIT -4096

#define WITHIN_MOV_IM_RANGE(x) (x < MOV_IM_UPPER_LIMIT && x >= MOV_IM_LOWER_LIMIT)

#define GLOBAL 1
#define LOCAL  2
#define OUTPUT 3
#define INPUT  4
#define STACK  5
#define FRAME  6

#endif
