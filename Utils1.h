

#include "MemMap.h"

#ifndef UTILS1_H_
#define UTILS1_H_

#define SET_BIT(REG,BIT)             (REG=REG|(1<<BIT))
#define CLR_BIT(REG,BIT)             (REG=REG&~(1<<BIT))
#define READ_BIT(REG,BIT)            ((REG>>BIT)&1)
#define  WRITE_BIT(REG,BIT,VALUE)    (REG=REG&(~(1<<BIT) | (VLAUE<<BIT))
#define  TOG_BIT(REG,BIT)            (REG=REG^(1<<BIT))
#define TOG_REG(REG)         (REG=REG^OXFF)



#endif /* UTILS1_H_ */