
# asm-prite

Asm-prite is a project built for the final project of the course 組合語言與系統程式(CE2012).
It's an web application with an GUI where user can draw, share pixel art on the website. The image is also available for download in the form of .ppm file.

Please read the following to properly setup the project.

**Also do notice that, despite the target is Win32(x86),
the project is mainly developed and tested on MacOS (M3/Apple Silicon)
with VMware Fusion running Windows on ARM.**
The emulation and compatibility layer should get the job done, but please expect bug when running on native x64 platform.

## Requirements

To run the project, please run the following commands:

```sh
git clone https://github.com/Yuyu-1115/asm-prite.git
cd asm-prite
docker-compose up -d
```
