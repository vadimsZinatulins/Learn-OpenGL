# Learn OpenGL - Personal Project
This is a personal project intended to Learn OpenGL from [https://learnopengl.com/](https://learnopengl.com/)

# Project Structure
Project is divided into 2 parts:
- Engine
- Application
## Engine
Here are all parts that are considered helper stuff and can be reused in `Application` part.  
## Application
This part is where `Engine` stuff is used to create several Scenes where each scene represents a chapter from [https://learnopengl.com/](https://learnopengl.com/)

# Dependencies
This project relies on:
- [SDL2](https://www.libsdl.org/download-2.0.php) (to manage windowing stuff)
- [glm ](https://github.com/g-truc/glm) (does all the maths)
- [glad](https://glad.dav1d.de/) (retries and stores all OpenGL functions)
- [stb](https://github.com/nothings/stb) (loads all images for me)
