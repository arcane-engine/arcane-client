#ifndef REGISTERS_HLSLI
#define REGISTERS_HLSLI

// Constant Buffer Slots
#define CB_REGISTER_CAMERA_TRANSFORM  b0
#define CB_REGISTER_OBJECT_TRANSFORM  b1
#define CB_REGISTER_LIGHT             b2

// Texture Slots
#define TEX_REGISTER_ALBEDO           t0

#define TEX_REGISTER_RENDER_TARGET    t0
#define TEX_REGISTER_DEPTH_STENCIL    t1

#define TEX_REGISTER_TERRAIN_WEIGHT   t0
#define TEX_REGISTER_TERRAIN_BASE     t1
#define TEX_REGISTER_TERRAIN_R        t2
#define TEX_REGISTER_TERRAIN_G        t3
#define TEX_REGISTER_TERRAIN_B        t4
#define TEX_REGISTER_TERRAIN_A        t5

// Sampler Slots
#define SMP_REGISTER_MAIN             s0

#endif
