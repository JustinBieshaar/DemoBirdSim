# 🐦 Bird Game Simulator – C++ Demo Project 2025 (readme WIP)
[![License: MIT](https://img.shields.io/badge/license-MIT-blue.svg)](LICENSE)
[![Made With C++](https://img.shields.io/badge/made%20with-C++20-blue.svg)](https://en.cppreference.com)
[![GitHub Repo stars](https://img.shields.io/github/stars/JustinBieshaar/DemoBirdSim?style=social)](https://github.com/JustinBieshaar/DemoBirdSim)

Hi there! 👋
Welcome to my 2025 C++ demo project – a playful, hands-on showcase of my skills in modern C++ game development.

> 🎮 A playful bird simulator built in modern C++ — with custom architecture, tools and built to showcase my passion.

## ✨ About This Project
In June 2025, I was laid off, and I decided to take this as an opportunity to first take a step back and rest, but also to finally pursue that transition. However, one key element was missing: a demo project to showcase my C++ skills. That’s where this idea was born — a focused demo, built over approximately three weeks in my spare time (well.. I got to be honest; I also had some days of procrastination..), aimed at demonstrating my proficiency in C++, what I can accomplish independently, showcase I can adapt to other languages, and (‘perhaps most importantly’) having some fun during this turbulent period in my career.

As I have a big interest in making tools, writing systems and care about software architecture. This felt like a good chance to make some time and share some of this interest and showcase it to demonstrate while exploring new roles.

So that's where this idea came from and I am happy to bring you along with me through this journey.

---

## 🖼️ Screenshots

---

## 📦 Features
This project includes:

- ✅ Premake build setup for cross-platform project generation
- ✅ Custom bird creation tool, using JSON input and code generation, built for non-technical users
- ✅ Reusable core libraries to isolate shared logic between the game and tool
- ✅ Simple 3D bird simulation, where you can select and control generated birds in a terrain environment
- ✅ Unit tests for the core systems

---

## 🧱 Architecture Highlights
- 🧩 Custom Entity-Component System (ECS) – Lightweight, flexible, and built from scratch
- 🧪 Custom Dependency Injection (DI) – Designed to make system wiring clean and testable
- 📣 Custom Signal System – For decoupled communication between systems
- 🔧 Code generation pipeline – Converts JSON bird definitions into native C++ types

---

## 🔗 Dependencies

- [GLAD](https://github.com/Dav1dde/glad) – OpenGL function loader  
- [GLFW](https://www.glfw.org/) – Window and input handling  
- [GLM](https://github.com/g-truc/glm) – Math library for graphics  
- [ImGui](https://github.com/ocornut/imgui) – Immediate-mode GUI  
- [ImGuiFileDialog](https://github.com/aiekick/ImGuiFileDialog) – File picker for ImGui  
- [nlohmann/json](https://github.com/nlohmann/json) – JSON parsing  
- [stbi_image.h](https://github.com/nothings/stb/blob/master/stb_image.h) – stbi_image.h for texture loading

---

## 🚀 Getting Started

1. **Clone the repo**
   ```bash
   git clone https://github.com/your-username/bird-game-simulator.git
   cd bird-game-simulator

2. **Generate project files**
- Windows run premake-win.bat
- todo support linux and mac

3. **Build and run**
Open the generated solution/project in your IDE and hit build.

---

# Tools


---

# Known flaws/issues

---

## 📬 Final Notes
This demo is more than just a codebase — it’s a snapshot of where I am as a developer, how I think about architecture, and how I approach challenges creatively and independently.

Thanks for checking it out! Feel free to open an issue, leave feedback, or just say hi. 👋
