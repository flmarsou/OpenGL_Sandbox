# 🎲 Blocks
- **[`Sand`](https://github.com/flmarsou/OpenGL_Sandbox/blob/main/src/block/SandBlock.cpp):** Falls straight down; may slide sideways *(50% chance)* if blocked below.
- **[`Water`](https://github.com/flmarsou/OpenGL_Sandbox/blob/main/src/block/WaterBlock.cpp):** Rapidly changes color; falls down and may flow sideways *(50% chance)* if blocked below.
- **[`Stone`](https://github.com/flmarsou/OpenGL_Sandbox/blob/main/src/block/StoneBlock.cpp):** Static; doesn’t move.
- **[`Fire`](https://github.com/flmarsou/OpenGL_Sandbox/blob/main/src/block/FireBlock.cpp):** Randomly flies up, left, or right; has a 10% chance to extinguish.
- **[`Bomb`](https://github.com/flmarsou/OpenGL_Sandbox/blob/main/src/block/BombBlock.cpp):** Falls straight down; explodes on impact (15-block diameter), igniting destroyed blocks; Stone is unaffected.
- **[`Acid`](https://github.com/flmarsou/OpenGL_Sandbox/blob/main/src/block/AcidBlock.cpp):** Slowly shifts color; dissolves adjacent blocks (75% chance to act, 50% chance to self-destruct); flows like Water.
