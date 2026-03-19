# Implementación del Algoritmo de Codificación RLE

## Descripción General

Este proyecto es una aplicación gráfica que implementa el algoritmo de codificación por longitud de ejecución (RLE - Run-Length Encoding). La aplicación permite al usuario ingresar texto, compactar el contenido utilizando RLE, descompactar el resultado, y visualizar estadísticas de compresión.

El objetivo del proyecto es tanto educativo como práctico. Demuestra cómo funciona la compresión sin pérdida internamente, proporcionando una interfaz interactiva para experimentar con diferentes tipos de texto. La interfaz gráfica facilita la comprensión de cómo los patrones de repetición de caracteres influyen en la ratio de compresión resultante.

La aplicación está construida en C++ y wxWidgets, utilizando CMake como sistema de compilación. Separa la lógica de codificación RLE de la interfaz gráfica, siguiendo una arquitectura modular.

## Herramientas y Versiones

Este proyecto está escrito en C++20 y requiere un compilador C++ moderno con soporte completo de C++20. El compilador recomendado es Microsoft Visual C++ (MSVC) proporcionado con Visual Studio 2022.

La aplicación depende de wxWidgets 3.x. Fue construida y probada usando la configuración MSVC dinámica de 64 bits (vc_x64_dll) compilada en modo Release. wxWidgets debe compilarse manualmente desde la fuente antes de compilar este proyecto.

El sistema de compilación utilizado es CMake versión 3.20 o superior. CMake debe estar instalado y accesible desde la línea de comandos. Puede verificar esto ejecutando:

```bash
cmake --version
```

La configuración de desarrollo recomendada en Windows incluye Visual Studio 2022 con la carga de trabajo "Desarrollo de escritorio con C++" instalada. Durante la instalación, asegúrese de que se seleccionen las herramientas de compilación MSVC v143 y el SDK de Windows 10 o Windows 11. El proyecto utiliza la cadena de herramientas de 64 bits y debe compilarse desde el "x64 Native Tools Command Prompt for VS" al compilar wxWidgets manualmente.

La aplicación fue desarrollada y probada en Windows 11 utilizando la cadena de herramientas MSVC x64. Aunque puede funcionar en Windows 10, no ha sido probada con MinGW u otros compiladores.

Antes de continuar con la configuración del entorno de desarrollo, asegúrese de que el siguiente software esté instalado y configurado correctamente en su sistema:

- Visual Studio 2022 con carga de trabajo C++
- CMake 3.20 o superior
- Código fuente de wxWidgets 3.x
- SDK de Windows 10 o 11
- Herramientas de compilación MSVC x64

Estos componentes son necesarios para compilar y ejecutar exitosamente la aplicación como se describe en la siguiente sección.

## Configuración del Entorno de Desarrollo (Windows + MSVC)

Este proyecto fue desarrollado y probado en Windows utilizando Microsoft Visual Studio 2022 (MSVC x64), CMake y wxWidgets compilado manualmente desde la fuente.

Primero, descargue el código fuente de wxWidgets como un archivo ZIP de Windows desde:

<https://wxwidgets.org/downloads/>

Extraiga el archivo en:

```bash
C:\cpp-lib-wxwidgets
```

Luego cree una variable de entorno que apunte a este directorio. Abra PowerShell o Símbolo del sistema y ejecute:

```bash
setx WXWIN "C:\cpp-lib-wxwidgets"
```

Cierre y reabre la terminal después de configurar la variable.

Para compilar wxWidgets, abra el Símbolo del sistema del desarrollador de Visual Studio:

```bash
x64 Native Tools Command Prompt for VS
```

Luego navegue al directorio de compilación MSVC de wxWidgets:

```bash
cd C:\cpp-lib-wxwidgets\build\msw
```

Compile wxWidgets en modo Release de 64 bits con bibliotecas compartidas:

```bash
nmake -f makefile.vc BUILD=release SHARED=1
```

Después de la compilación, las bibliotecas generadas aparecerán en:

```bash
C:\cpp-lib-wxwidgets\lib\vc_x64_dll
```

Como se trata de una compilación compartida (DLL), los archivos DLL en tiempo de ejecución deben ser accesibles. Puede agregarlos a su PATH del sistema:

```bash
setx PATH "%PATH%;C:\cpp-lib-wxwidgets\lib\vc_x64_dll"
```

O copiar los archivos DLL en el directorio ejecutable de su proyecto después de compilar:

```bash
copy C:\cpp-lib-wxwidgets\lib\vc_x64_dll\*.dll build\Release\
```

A continuación, configure el CMakeLists.txt en la raíz de su proyecto de la siguiente manera:

```cmake
cmake_minimum_required(VERSION 3.10)
project(RLEApp)

if(MSVC)
    add_compile_options(/utf-8)
endif()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(wxWidgets REQUIRED COMPONENTS core base)
include(${wxWidgets_USE_FILE})

include_directories(src/core src/ui)

add_executable(RLEApp WIN32
    src/main.cpp
    src/core/RLE.cpp
    src/ui/MainFrame.cpp
)

target_link_libraries(RLEApp ${wxWidgets_LIBRARIES})
target_compile_definitions(RLEApp PRIVATE UNICODE _UNICODE)
target_compile_options(RLEApp PRIVATE ${wxWidgets_CXX_FLAGS})
```

Para soporte de IntelliSense en Visual Studio Code, configure .vscode/c_cpp_properties.json de la siguiente manera:

```json
{
    "configurations": [
        {
            "name": "Win32",
            "compilerPath": "cl.exe",
            "intelliSenseMode": "windows-msvc-x64",
            "includePath": [
                "${workspaceFolder}/**",
                "C:/cpp-lib-wxwidgets/include",
                "C:/cpp-lib-wxwidgets/lib/vc_x64_dll/mswu"
            ],
            "defines": [
                "NDEBUG",
                "UNICODE",
                "_UNICODE"
            ],
            "cppStandard": "c++20"
        }
    ],
    "version": 4
}
```

Finalmente, desde la raíz de su proyecto, configure y compile usando CMake:

```bash
cmake -S . -B build
cmake --build build --config Release
```

El ejecutable será generado en:

```bash
build\Release\RLEApp.exe
```

Ejecute la aplicación usando:

```bash
build\Release\RLEApp.exe
```

Si la aplicación no se inicia debido a DLLs faltantes, verifique que las bibliotecas dinámicas de wxWidgets estén incluidas en el PATH del sistema o copiadas en el directorio Release.

Si necesita recompilar, use lo siguiente para una compilación limpia:

```bash
rm -r -fo build
cmake -S . -B build
cmake --build build --config Release
```

## Compilación y Ejecución

Después de completar la configuración del entorno de desarrollo y compilar exitosamente wxWidgets en modo Release (vc_x64_dll), el proyecto puede compilarse usando CMake y MSVC.

Abra una terminal en el directorio raíz del proyecto. Se recomienda usar PowerShell o Símbolo del sistema normal para configurar y compilar la aplicación, ya que wxWidgets ya ha sido compilado usando el x64 Native Tools Command Prompt.

Genere los archivos de compilación usando CMake con una compilación fuera de la fuente:

```bash
cmake -S . -B build
```

Este comando configura el proyecto y genera los archivos necesarios de Visual Studio dentro del directorio build.

A continuación, compile el proyecto en modo Release:

```bash
cmake --build build --config Release
```

Si la compilación se completa exitosamente, el ejecutable será generado en:

```bash
build\Release\RLEApp.exe
```

Ejecute la aplicación usando:

```bash
build\Release\RLEApp.exe
```

Si el vinculador reporta que no puede abrir el archivo ejecutable, asegúrese de que la aplicación no esté ya en ejecución y que ninguna instancia anterior esté bloqueando el archivo.

Si la aplicación no se inicia debido a archivos DLL faltantes, verifique que las bibliotecas dinámicas de wxWidgets desde:

```bash
C:\cpp-lib-wxwidgets\lib\vc_x64_dll
```

estén incluidas en la variable de entorno PATH del sistema o copiadas directamente en el directorio build\Release.

Este proyecto utiliza una compilación de wxWidgets compartida (SHARED=1), por lo que los archivos DLL son necesarios en tiempo de ejecución.

## Estructura del Proyecto

El proyecto sigue una arquitectura modular que separa la lógica de codificación RLE de la interfaz gráfica. La disposición del directorio está organizada de la siguiente manera:

```bash
RLEApp/
│
├── CMakeLists.txt
├── build/
│
├── src/
│   ├── main.cpp
│   │
│   ├── core/
│   │   ├── RLE.h
│   │   ├── RLE.cpp
│   │
│   ├── ui/
│   │   ├── MainFrame.h
│   │   ├── MainFrame.cpp
│
└── .vscode/
    └── c_cpp_properties.json
```

El directorio raíz contiene el archivo CMakeLists.txt, que define la configuración de compilación, la configuración del compilador, el descubrimiento de fuentes, e integración con wxWidgets.

El directorio src contiene el código fuente de la aplicación y está dividido en componentes lógicos. La carpeta core implementa el algoritmo RLE, incluyendo las estructuras de datos, análisis de frecuencias de caracteres, y lógica de codificación/decodificación. Esta parte del proyecto es independiente de la interfaz gráfica y puede reutilizarse en otros contextos.

La carpeta ui contiene todos los componentes de la interfaz de usuario construidos usando wxWidgets. MainFrame gestiona la ventana principal y el diseño de la aplicación, mostrando los campos de entrada, salida y estadísticas de compresión.

El archivo main.cpp sirve como punto de entrada de la aplicación e inicializa el objeto de aplicación wxWidgets.

El directorio build es generado automáticamente por CMake durante la compilación. Contiene archivos intermedios de compilación y el ejecutable final. Este directorio no forma parte del código fuente y no debe ser comprometido al control de versiones.

La carpeta .vscode contiene archivos de configuración para Visual Studio Code, incluyendo configuración de IntelliSense para wxWidgets y MSVC.

Esta separación asegura que el algoritmo de compresión permanezca independiente de la interfaz gráfica, haciendo que el proyecto sea más fácil de mantener, probar, depurar y extender en el futuro.

## Características

- **Codificación RLE**: Comprime texto usando el algoritmo de codificación por longitud de ejecución
- **Decodificación**: Descompacta automáticamente el texto codificado
- **Análisis de Compresión**: Muestra estadísticas detalladas sobre el ahorro de espacio
- **Soporte UTF-8**: Manipula correctamente caracteres multibyte incluyendo acentos y caracteres especiales
- **Interfaz Gráfica**: Interfaz amigable construida con wxWidgets

## Uso

1. Ejecute el programa: `build\Release\RLEApp.exe`
2. Ingrese el texto a comprimir en el campo "Entrada"
3. Haga clic en "Codificar/Decodificar"
4. Vea el resultado codificado, decodificado y las estadísticas de compresión

## Licencia

Este proyecto fue desarrollado como práctica educativa.
