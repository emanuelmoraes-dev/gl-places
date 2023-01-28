# GL Places
Render different places in OpenGL

## Building
To be able to compile the source code, follow the instructions below

### Dependencies
* [GLM](https://glm.g-truc.net/0.9.9/index.html)
  * Note: It is already in the project
* [STB](https://github.com/nothings/stb)
  * Note: It is already in the project
* [OpenGL](https://www.opengl.org)
  * Note: It is possible that your operating system already provides this library
* [GLFW](https://www.glfw.org)
  * Note: For Windows environments extract in "lib/glfw"
  * Note: If you use Windows, you can download [here](https://github.com/emanuelmoraes-dev/gl-places/releases/download/v0.0.0-windows_x86_amd64/glfw.zip)
* [GLEW](http://glew.sourceforge.net)
  * Note: For Windows environments extract in "lib/glew"
  * Note: For Windows environments the "glew32.dll" must to be in the binary folder OR in the %PATH% variable
  * Note: If you use Windows, you can download [here](https://github.com/emanuelmoraes-dev/gl-places/releases/download/v0.0.0-windows_x86_amd64/glew.zip)

### configuring options
Copy the file "opts.example.cmake" to "opts.cmake" with the options configurations

### configuring data
Copy the file "data/gl-places.example.json" to "data/gl-places.json" with the application configuration

### Configuring Environment
Copy the files "env/debug/env.example.hh" and "env/release/env.example.hh" to "env/debug/env.hh" and "env/release/env.hh" (respectively) with the environments configurations

#### env/debug/env.hh and env/release/env.hh
* PL_ENV_SHADER_DIR: Relative path (from the binary folder) that has the shading source
* PL_ENV_TEXTURE_DIR: Relative path (from the binary folder) that has the textures
* PL_ENV_DATA_DIR: Relative path (from the binary folder) that has data files
* PL_ENV_WINDOW_WIDTH: Initial window width
* PL_ENV_WINDOW_HEIGHT: Initial window heith
* PL_ENV_WINDOW_TITLE: Window title
