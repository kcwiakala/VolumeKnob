#pragma once

#define IZI_CAT_II(res) res
#define IZI_CAT_I(x,y)  IZI_CAT_II(x ## y)
#define IZI_CAT(x,y)    IZI_CAT_I(x,y)

#define IZI_BV(b) (1 << b)