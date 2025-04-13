# Project Roadmap: Evolving Towards an Immediate Mode GUI Library

This document outlines a potential roadmap for evolving the current basic C UI framework into a more comprehensive Immediate Mode GUI (IMGUI) library, similar in philosophy to libraries like Dear ImGui.

## Current Project Status:

*   **Build:** Compiles and links successfully on Windows using CMake, Clang, Ninja, SDL2, and OpenGL (via vcpkg dependencies).
*   **PAL:** Platform Abstraction Layer implemented for:
    *   Windowing (SDL backend) - **DONE**
    *   Input (SDL backend) - **DONE**
    *   Renderer (SDL+OpenGL 3.3 backend) - **Basic implementation DONE** (shaders, buffers, basic texture handling, triangle drawing).
*   **Application:** Creates a window, polls input, clears background, draws a placeholder quad using the PAL renderer.
*   **Limitations:** Old drawing code (`Canvas`, `primitives.c`, widget draw functions) is not yet refactored to use the PAL renderer. Text rendering is missing. Input is polled but not connected to widget interaction.

## Detailed Roadmap:

### Phase 1: Core Foundation & Abstraction

1.  **Platform Abstraction Layer (PAL):**
    *   **Goal:** Decouple core logic from OS/windowing systems and rendering APIs.
    *   **Status:** **DONE** (SDL2+OpenGL backend implemented for Window, Input, Renderer base).
    *   **NEXT:** Refactor existing drawing code (`Canvas`, `primitives.c`, widget draw functions) to use `pal_renderer_*` functions.
    *   **TODO:** Implement PAL Time interface (`pal_time.h` and `pal_sdl_time.c`).
2.  **Core Immediate Mode Context:**
    *   **Goal:** Establish central data structure and API flow.
    *   **Tasks:** Design `UIContext` struct; Define `NewFrame()`, `EndFrame()`, `Render()` API; Manage UI state within `UIContext`.
3.  **Basic Drawing API:**
    *   **Goal:** Provide fundamental drawing commands for widgets (using the PAL).
    *   **Tasks:** Design `DrawList` structure; Implement `DrawRect`, `DrawText`, etc., adding commands to `DrawList`; Modify `pal_renderer_render_triangles` or add batching logic to process `DrawList` efficiently.
4.  **Input Handling Integration:**
    *   **Goal:** Feed platform input into the UI context and widgets.
    *   **Tasks:** Map PAL input state to `UIContext` state in `NewFrame()`; Implement widget event handling logic using PAL input queries.
5.  **Basic Windowing (ImGui-style):**
    *   **Goal:** Implement UI windows within the main application window.
    *   **Tasks:** Implement `BeginWindow()`/`EndWindow()`; Manage window state; Handle interaction; Implement clipping.

### Phase 2: Fundamental Widgets & Interaction

1.  **Widget State Management:**
    *   **Goal:** Persistently store widget state across frames.
    *   **Tasks:** Design widget ID mechanism (string ID, hash); Store state associated with ID in `UIContext`.
2.  **Core Widgets:**
    *   **Goal:** Implement common UI controls.
    *   **Tasks:** `Text`, `Button`, `Checkbox`, `RadioButton`, `SliderFloat`, `InputText`. Functions take ID/label, return interaction state, modify data via pointers.
3.  **Basic Layout:**
    *   **Goal:** Automatic widget positioning.
    *   **Tasks:** Vertical layout; `SameLine()`; `Separator()`; `Spacing()`.

### Phase 3: Layout, Styling, and Text

1.  **Advanced Layout:**
    *   **Goal:** More flexible positioning.
    *   **Tasks:** `SetNextItemWidth`; Horizontal groups; Cursor control (`Get/SetCursorPos`); `GetContentRegionAvail`.
2.  **Styling System:**
    *   **Goal:** Customizable appearance.
    *   **Tasks:** `Style` struct in `UIContext`; API to modify style (`GetStyle`, `Push/PopStyleColor/Var`); Refactor widgets to use style settings.
3.  **Text Rendering & Fonts:**
    *   **Goal:** Robust text rendering.
    *   **Tasks:** Integrate font library (`stb_truetype` or FreeType); Load fonts; Build font atlases; Text layout/alignment; Font selection API (`Push/PopFont`).

### Phase 4: Advanced Widgets & Features

1.  **Complex Widgets:**
    *   **Goal:** Implement sophisticated controls.
    *   **Tasks:** `TreeNode`, `ListBox`, `ComboBox`, `MenuBar`, `Popups`, `Tables`, `Plots`, `TabBar`.
2.  **Input Handling Enhancements:**
    *   **Goal:** Nuanced input control.
    *   **Tasks:** Focus management; Drag and drop; Advanced mouse interaction.
3.  **Windowing Enhancements (Optional):**
    *   **Goal:** Features like docking.
    *   **Tasks:** Docking system; Viewports.

### Phase 5: Performance, Backends, and Polish

1.  **Performance Optimization:**
    *   **Goal:** Fast and responsive UI.
    *   **Tasks:** Optimize drawing (batching), vertex generation, memory allocation; Profiling.
2.  **More Backends:**
    *   **Goal:** Support more platforms/APIs.
    *   **Tasks:** Implement PAL backends for DirectX, Vulkan, Metal, other windowing systems.
3.  **API Refinement & Documentation:**
    *   **Goal:** Stable, well-documented, easy-to-use API.
    *   **Tasks:** API review; Comprehensive documentation; Example applications.
4.  **Debugging Tools:**
    *   **Goal:** Help developers debug the UI.
    *   **Tasks:** Metrics window; Style editor; Widget inspection tools. 