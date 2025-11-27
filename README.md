
# asm-prite

Asm-prite is a project built for the final project of the course 組合語言與系統程式(CE2012).
It's an web application with an GUI where user can draw, share pixel art on the website. The image is also available for download in the form of .ppm file.

Please read the following to properly setup the project.

**Also do notice that, despite the target is Win32(x86),
the project is mainly developed and tested on MacOS (M3/Apple Silicon)
with VMware Fusion running Windows on ARM.**
The emulation layer should get the job done, but please expect bug when running on native x64 platform.

[ToC]

## Requirements

The MASM32 environment is already built-in within the repo, so you don't need to install the MASM32 SDK separately.
The project currently only depends on the socket API of Windows (which comes from Win32 library.)
In order to properly build and run, the following tools are required:

### Build Tool

- make: the main build tool for the project.

### Database

The data is stored in Redis, with which the server is will interact using **RESP(Redis Serialization Protocol)**.

## Build & Run

To build the project, a simple `make` should do the job, you can configure the output file via `Makefile`.
