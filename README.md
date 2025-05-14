# 🎲 Blocks

## 🧱 Solids:
- **[`Stone`](https://github.com/flmarsou/OpenGL_Sandbox/blob/main/src/block/solid/StoneBlock.cpp):** Unaffected by **Fire** and **explosions**, erodes with **Water**.
- **[`Wood`](https://github.com/flmarsou/OpenGL_Sandbox/blob/main/src/block/solid/WoodBlock.cpp):** Ignites on contact with **Fire**. May spread **Fire** *(sideways and diagonally)*, turns into **Ash**, or extinguish.

## ⏳ Powders:
- **[`Sand`](https://github.com/flmarsou/OpenGL_Sandbox/blob/main/src/block/powder/SandBlock.cpp):** Falls straight down. If blocked below, randomly slides sideways. Falls down into **Water**.
- **[`Ash`](https://github.com/flmarsou/OpenGL_Sandbox/blob/main/src/block/powder/AshBlock.cpp):** Moves like **Sand**.
- **[`Mud`](https://github.com/flmarsou/OpenGL_Sandbox/blob/main/src/block/powder/MudBlock.cpp):** Moves like **Sand**. If blocked below, has a random chance to be stuck in place.

## 🌊 Liquids:
- **[`Water`](https://github.com/flmarsou/OpenGL_Sandbox/blob/main/src/block/liquid/WaterBlock.cpp):** Falls straight down. If blocked below, randomly slides and moves sideways. Boils into **Steam** on contact with **Fire**.
- **[`Acid`](https://github.com/flmarsou/OpenGL_Sandbox/blob/main/src/block/liquid/AcidBlock.cpp):** Moves like **Water**. Dissolves adjacent blocks and may self-destruct during interaction. Converts **Water** into **Toxic Sludge**.
- **[`Toxic Sludge`](https://github.com/flmarsou/OpenGL_Sandbox/blob/main/src/block/liquid/ToxicSludgeBlock.cpp):** Moves like **Water**. Converts nearby **Water** into **Toxic Sludge**. Slowly evaporates into **Flammable Gas**.

## 💨 Gasses:
- **[`Steam`](https://github.com/flmarsou/OpenGL_Sandbox/blob/main/src/block/gas/SteamBlock.cpp):** Rises randomly *(mostly up, left, or right)*. Randomly condensate into **Water**.
- **[`Flammable Gas`](https://github.com/flmarsou/OpenGL_Sandbox/blob/main/src/block/gas/FlammableGasBlock.cpp):** Moves like **Steam**. Ignites and spreads **Fire** in a chain reaction.

## 💥 Reactives:
- **[`Fire`](https://github.com/flmarsou/OpenGL_Sandbox/blob/main/src/block/reactive/FireBlock.cpp):** Rises randomly *(up, left, or right)*. May ignite flammable materials or extinguish on its own.
- **[`Bomb`](https://github.com/flmarsou/OpenGL_Sandbox/blob/main/src/block/reactive/BombBlock.cpp):** Falls straight down. Explodes on impact *(**15**-block radius)*, igniting affected blocks.
