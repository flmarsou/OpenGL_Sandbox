# 🎲 Blocks

## 🧱 Solids:
- **[`Stone`](https://github.com/flmarsou/OpenGL_Sandbox/blob/main/src/block/solid/StoneBlock.cpp):** Unaffected by **Fire** and **explosions**, erodes with **Water**.
- **[`Wood`](https://github.com/flmarsou/OpenGL_Sandbox/blob/main/src/block/solid/WoodBlock.cpp):** Ignites on contact with **Fire**. May spread **Fire** *(sideways and diagonally)*, turns into **Ash**.
- **[`Metal`](https://github.com/flmarsou/OpenGL_Sandbox/blob/main/src/block/solid/MetalBlock.cpp):** Electrifies on contact with a **Battery**.
- **[`Ice`](https://github.com/flmarsou/OpenGL_Sandbox/blob/main/src/block/solid/IceBlock.cpp):** Melts on contact with **Fire**. May convert **Water** into **Ice** in all directions.

## ⏳ Powders:
- **[`Sand`](https://github.com/flmarsou/OpenGL_Sandbox/blob/main/src/block/powder/SandBlock.cpp):** Falls straight down. If blocked below, randomly slides sideways. Falls down into **Water**.
- **[`Ash`](https://github.com/flmarsou/OpenGL_Sandbox/blob/main/src/block/powder/AshBlock.cpp):** Moves like **Sand**.
- **[`Mud`](https://github.com/flmarsou/OpenGL_Sandbox/blob/main/src/block/powder/MudBlock.cpp):** Moves like **Sand**. If blocked below, has a random chance to be stuck in place.

## 🌊 Liquids:
- **[`Water`](https://github.com/flmarsou/OpenGL_Sandbox/blob/main/src/block/liquid/WaterBlock.cpp):** Falls straight down. If blocked below, randomly slides and moves sideways. Boils into **Steam** on contact with **Fire**.
- **[`Acid`](https://github.com/flmarsou/OpenGL_Sandbox/blob/main/src/block/liquid/AcidBlock.cpp):** Moves like **Water**. Dissolves adjacent blocks and may self-destruct during interaction. Converts **Water** into **Toxic Sludge**.
- **[`Toxic Sludge`](https://github.com/flmarsou/OpenGL_Sandbox/blob/main/src/block/liquid/ToxicSludgeBlock.cpp):** Moves like **Water**. Converts nearby **Water** into **Toxic Sludge**. Slowly evaporates into **Flammable Gas**.
- **[`Oil`](https://github.com/flmarsou/OpenGL_Sandbox/blob/main/src/block/liquid/OilBlock.cpp):** Moves like **Water**, and floats on top of liquids. Ignites on contact with **Fire**. May spread **Fire** on top and sides.
- **[`Lava`](https://github.com/flmarsou/OpenGL_Sandbox/blob/main/src/block/liquid/LavaBlock.cpp):** Moves like **Water** but slower. Generates **Fire**. Turns **Water** into **Stone**.

## 💨 Gasses:
- **[`Steam`](https://github.com/flmarsou/OpenGL_Sandbox/blob/main/src/block/gas/SteamBlock.cpp):** Rises randomly *(mostly up, left, or right)*. Randomly condensate into **Water**.
- **[`Flammable Gas`](https://github.com/flmarsou/OpenGL_Sandbox/blob/main/src/block/gas/FlammableGasBlock.cpp):** Moves like **Steam**. Ignites and spreads **Fire** in a chain reaction.

## 💥 Reactives:
- **[`Fire`](https://github.com/flmarsou/OpenGL_Sandbox/blob/main/src/block/reactive/FireBlock.cpp):** Rises randomly *(up, left, or right)*. May ignite flammable materials or extinguish on its own.
- **[`Bomb`](https://github.com/flmarsou/OpenGL_Sandbox/blob/main/src/block/reactive/BombBlock.cpp):** Falls straight down. Explodes on impact *(**15**-block radius)*, igniting affected blocks.
- **[`Dynamite`](https://github.com/flmarsou/OpenGL_Sandbox/blob/main/src/block/reactive/DynamiteBlock.cpp):** Moves like **Sand**. Explodes on contact to fire *(**5**-block radius)*, igniting affected blocks.
- **[`TNT`](https://github.com/flmarsou/OpenGL_Sandbox/blob/main/src/block/reactive/TNTBlock.cpp):** Solid block. Explodes on contact to fire *(**5**-block radius)*, igniting affected blocks.

## ⚡ Electricity:
- **[`Battery`](https://github.com/flmarsou/OpenGL_Sandbox/blob/main/src/block/electricity/BatteryBlock.cpp):** Electrifies conductive blocks on contact (e.g. **Metal**, **LEDs**, ...).
- **[`Red LED`](https://github.com/flmarsou/OpenGL_Sandbox/blob/main/src/block/electricity/RedLedBlock.cpp), [`Green LED`](https://github.com/flmarsou/OpenGL_Sandbox/blob/main/src/block/electricity/GreenLedBlock.cpp), [`Blue LED`](https://github.com/flmarsou/OpenGL_Sandbox/blob/main/src/block/electricity/BlueLedBlock.cpp):** Lits up on contact to electricity.
- **[`C4`](https://github.com/flmarsou/OpenGL_Sandbox/blob/main/src/block/electricity/C4Block.cpp):** Explodes on contact to an electrified block (e.g. **Battery**, electrified **Metal**, ...).
