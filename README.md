# Arcane Precision

A top-down dungeon game written in **C** with DigiPen's CProcessing framework by team *SyntaxError* for the GAM100 module (Fall 2024) at DigiPen Institute of Technology Singapore (SIT-DigiPen).

Fight your way through dungeon rooms full of enemies and obstacles, pick up item drops, and get your score onto the leaderboard.

<!-- Screenshots / gameplay GIF go here -->

## Features

- Room-based dungeon layouts with obstacles and interactions
- Enemy spawning and movement AI
- Item drops with collision handling
- Persistent leaderboard
- Full menu flow: splash screen, start menu, main menu, settings, pause, game over and credits

## My role

I built the game's **screens and menu flow**:

- Splash screen shown on launch ([`splashscreen.c`](SEP1/SEP1/splashscreen.c))
- Start menu ([`startmenu.c`](SEP1/SEP1/startmenu.c))
- Pause menu ([`pause.c`](SEP1/SEP1/pause.c))
- Game over screen ([`gameover.c`](SEP1/SEP1/gameover.c))
- Credits screen ([`credits.c`](SEP1/SEP1/credits.c))

## Tech stack

C · CProcessing · FMOD · Visual Studio

## Building (Windows)

1. Open `SEP1/SEP1.sln` in Visual Studio 2022.
2. Build and run with **F5**. CProcessing and FMOD are included in `SEP1/Extern/`.

## Controls

| Key | Action |
| --- | --- |
| W A S D | Move |
| Mouse | Aim / click menu buttons |
| Space | Action |
| Esc | Pause |
| − / = | Volume |

## Team

Toh Jing Han, Tan Che Fong, Khor Ee Ling, Beverly Choy, **Tan Wei Leong**

---

Made as a student project at DigiPen Institute of Technology Singapore. All content © 2024 DigiPen Institute of Technology Singapore.
