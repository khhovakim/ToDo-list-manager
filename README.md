# 🧭 TodoApp — Cross-Platform Qt C++ To-Do Manager

**TodoApp** is a simple, command-driven To-Do list manager built with **C++17** and **Qt Widgets**.  
It demonstrates clean **object-oriented design**, **cross-platform portability**, and solid use of **design patterns**.

🧩 Factory Method Pattern — creates the correct command object from text input

⚙️ Command Pattern — encapsulates each user command (add, remove, complete, etc.)

🔁 Singleton Pattern — ensures only one shared TaskManager instance across the app

🎨 Minimal Qt GUI — displays tasks, log messages, and a command input box

---

## 📥 1. How to Get This Project

You can clone the repository from GitHub:

```bash
git clone https://github.com/YourUsername/ToDo-list-manager.git
cd TodoApp
```

## ⚙️ 2. How to Build This Project Using CMake

You can build the project on Linux or Windows using CMake.
Both Qt5 and Qt6 are supported.

#### 🧩 Requirements
- **Qt 5.15+ or Qt 6.x (Widgets module)**
- **CMake ≥ 3.16**
- **C++17 compiler**
- **Optional: Qt Creator for IDE builds**


---
#### 🐧 Build on Linux
```bash
cd Path/To/ToDo-list-manager
```
Configure with CMake
```bash
cmake -B build -DCMAKE_BUILD_TYPE=Release -DCMAKE_PREFIX_PATH=Path/To/(Qt6/Qt5)
cmake --build build --config Release
```
Run the application
```bash
./buld/TodoApp
```
---
### 🪟 Build on Windows
Please add these folders to your `PATH`:
```powershell
$env:PATH = "C:\Qt\Tools\Ninja;C:\Qt\Tools\CMake_64\bin;C:\Qt\Tools\mingw1310_64\bin;C:\Qt\<version>\mingw_64\bin;$env:PATH"
```
```bash
cd Path\To\ToDo-list-manager
```
Configure with CMake
```bash
cmake -B build -G "Ninja" -DCMAKE_BUILD_TYPE=Release 
cmake --build build --config Release
```
Run the application
```bash
.\buld\TodoApp.exe
```
If the app fails due to missing Qt DLLs, deploy with:
```bash
windeployqt.exe .\build\TodoApp.exe
.\build\TodoApp.exe
```
---

### 💡 3. How to Use This Project

#### 🖥️ Running the Application
After building successfully:

- On **Linux**:
  ```bash
  ./build/TodoApp
  ```
- On **Windows**
  ```bash
  .\build\TodoApp.exe
  ```

When you launch the app, you’ll see a simple and modern Qt interface with:
- 🗒️ Task List Panel — Displays all tasks with their completion status
- 📜 Log Panel — Shows messages for every action or error
- 💬 Command Input Box — Where you type text command

#### ⚙️ Command System Overview

TodoApp doesn’t rely on buttons or menus for task control.
Instead, you use typed commands (like a mini shell inside the GUI).

| Command                        | Example                                               | Description                                               |
| ------------------------------ |-------------------------------------------------------| --------------------------------------------------------- |
| **Add a task**                 | `add_task -name {Buy milk}`                           | Adds a new task named *Buy milk*                          |
| **Remove a task**              | `remove_task -name {Buy milk}`                        | Deletes the task named *Buy milk*                         |
| **Complete a task**            | `complete_task -name {Buy milk}`                      | Marks the specified task as completed                     |
| **List all tasks**             | `list_tasks`                                          | Displays all current tasks and their statuses             |
| **Execute commands from file** | `execute_file -file_path ./Full/Path/To/commands.txt` | Reads commands line-by-line from a file and executes them |

### 📄 Example Script File

You can execute multiple commands automatically from a file using execute_file.
Example content of tasks.txt:
```bash
# This is a comment
add_task -name {Buy groceries}
add_task -name {Clean kitchen}
complete_task -name {Clean kitchen}
list_tasks
remove_task -name {Buy groceries}
```

Run file into GUI:
```bash
execute_file -file_path ./Full/Path/To/tasks.txt
```
