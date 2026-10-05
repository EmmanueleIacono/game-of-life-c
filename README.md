# Conway's Game of Life (in C)

This is an implementation of [Conway's Game of Life](https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life), written in C.

The project was inspired by this [Salvatore Sanfilippo's video](https://www.youtube.com/watch?v=c5atNuYdKK8) (plus this [integration](https://www.youtube.com/watch?v=msGzuneFpDU)), part of [his YouTube Playlist on learning C](https://www.youtube.com/playlist?list=PLrEMgOSrS_3cFJpM2gdw8EGFyRBZOyAKY).

---

## The Game

**Conway's Game of Life** is a famous mathematical "game" created by mathematician John Conway in 1970.

It is a **zero-player game**: its evolution is entirely determined by its initial state. Despite its incredibly simple rules, it can generate very complex, life-like patterns. For this reason, the Game of Life is a premier example of **emergence**: how complex behaviors arise from simple, deterministic rules.

## How it Works

The game takes place on a (potentially infinite) grid of **cells**. Each cell can be in one of two states: **alive** (usually filled/black) or **dead** (empty/white).

Every cell interacts with its eight immediate neighbors (*horizontal*, *vertical*, and *diagonal*). With each tick of the clock (called a *generation*), the entire board updates at once based on **four basic rules**.

## The 4 Base Rules

| Rule | Condition |
| --- | --- |
| **1. Underpopulation** | A live cell with **fewer than 2** live neighbors dies. |
| **2. Survival** | A live cell with **2 or 3** live neighbors lives on to the next generation. |
| **3. Overpopulation** | A live cell with **more than 3** live neighbors dies. |
| **4. Reproduction** | A dead cell with **exactly 3** live neighbors becomes a live cell. |
