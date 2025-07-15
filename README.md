# Genesis - Game Engine

<p align="center">
   <img width="800" height="400" alt="GenesisGameEngineRevamped" src="https://github.com/user-attachments/assets/2c64cc50-b39d-439e-9aa3-522d39f7f4b2" />
</p>

[![Project Board](https://img.shields.io/badge/Project-Board-blue?logo=github)](https://github.com/orgs/FaulveCorps/projects/1)

> ⚠️ **Personal Use Only**  
> The current [License](https://github.com/altxxr0/Genesis/blob/master/LICENSE) restricts commercial or public redistribution. Please review before use.

## Description

   **Genesis** is a lightweight, modular 2D game engine built with **C++**, aimed at educational use and hobby development.  
It emphasizes clean architecture and cross-platform compatibility, using:

- **SDL3** for platform abstraction  
- **bgfx** for rendering (centralized in the Engine layer)  
- **Bullet** for physics simulation (planned)  

Genesis separates responsibilities between an `Executable`, `Engine`, and `Core` layer—encouraging scalability and reuse.

Supported platforms: **Windows**, **Linux**, and **macOS**

Check out the active [Project Board](https://github.com/orgs/FaulveCorps/projects/1) to track development progress.

---

### Requirements

- **CMake** ≥ 3.20  
- **Visual Studio 2022** (or any modern C++ IDE with CMake support)  
- **Git**  
- (Optional) **Ninja** for faster builds

---

### Dependencies

- [SDL3](https://github.com/libsdl-org/SDL) – Platform/Window/Input  
- [bgfx](https://github.com/bkaradzic/bgfx) – Rendering API abstraction  
- [Bullet Physics](https://github.com/bulletphysics/bullet3) – Physics simulation *(WIP)*

---

### Building

1. Clone the repository:
   ```bash
   git clone https://github.com/altxxr0/Genesis.git
   cd Genesis
2. Run the build script:
   ``build.cmd`` / ``build.sh``
4. After a successful build, navigate to:
   ``Genesis\Build\Debug\``
6. Launch the engine executable:
   ``Game.exe``
   
### Contributing & Feedback
Genesis is still in early development and not accepting external contributors at the moment.
However, feedback and ideas are welcome via issues or project discussions.

