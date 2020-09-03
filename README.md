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

Every scene is my own implementation of the chapter, so you might find the code different from what is presented in [Learn OpenGL](https://learnopengl.com/).

Use left arrow key and right arrow key to walk through the scenes.

# Dependencies
This project relies on:
- [SDL2](https://www.libsdl.org/download-2.0.php) (to manage windowing stuff)
- [glm ](https://github.com/g-truc/glm) (does all the maths)
- [glad](https://glad.dav1d.de/) (retrieves and stores all OpenGL functions)
- [stb](https://github.com/nothings/stb) (loads all images for me)

# How to Compile it?
Just open the project in Visual Studio (VS19 is prefered) and hit that build and run button :)
