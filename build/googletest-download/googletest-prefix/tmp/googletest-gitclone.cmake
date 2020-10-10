
if(NOT "E:/U/Semestre 6°/Estructura de Datos Avanzada/Practico/Repositorios/smart_pointer/build/googletest-download/googletest-prefix/src/googletest-stamp/googletest-gitinfo.txt" IS_NEWER_THAN "E:/U/Semestre 6°/Estructura de Datos Avanzada/Practico/Repositorios/smart_pointer/build/googletest-download/googletest-prefix/src/googletest-stamp/googletest-gitclone-lastrun.txt")
  message(STATUS "Avoiding repeated git clone, stamp file is up to date: 'E:/U/Semestre 6°/Estructura de Datos Avanzada/Practico/Repositorios/smart_pointer/build/googletest-download/googletest-prefix/src/googletest-stamp/googletest-gitclone-lastrun.txt'")
  return()
endif()

execute_process(
  COMMAND ${CMAKE_COMMAND} -E rm -rf "E:/U/Semestre 6°/Estructura de Datos Avanzada/Practico/Repositorios/smart_pointer/source/googletest/googletest-src"
  RESULT_VARIABLE error_code
  )
if(error_code)
  message(FATAL_ERROR "Failed to remove directory: 'E:/U/Semestre 6°/Estructura de Datos Avanzada/Practico/Repositorios/smart_pointer/source/googletest/googletest-src'")
endif()

# try the clone 3 times in case there is an odd git clone issue
set(error_code 1)
set(number_of_tries 0)
while(error_code AND number_of_tries LESS 3)
  execute_process(
    COMMAND "E:/Git/mingw64/bin/git.exe"  clone --no-checkout "https://github.com/google/googletest.git" "googletest-src"
    WORKING_DIRECTORY "E:/U/Semestre 6°/Estructura de Datos Avanzada/Practico/Repositorios/smart_pointer/source/googletest"
    RESULT_VARIABLE error_code
    )
  math(EXPR number_of_tries "${number_of_tries} + 1")
endwhile()
if(number_of_tries GREATER 1)
  message(STATUS "Had to git clone more than once:
          ${number_of_tries} times.")
endif()
if(error_code)
  message(FATAL_ERROR "Failed to clone repository: 'https://github.com/google/googletest.git'")
endif()

execute_process(
  COMMAND "E:/Git/mingw64/bin/git.exe"  checkout master --
  WORKING_DIRECTORY "E:/U/Semestre 6°/Estructura de Datos Avanzada/Practico/Repositorios/smart_pointer/source/googletest/googletest-src"
  RESULT_VARIABLE error_code
  )
if(error_code)
  message(FATAL_ERROR "Failed to checkout tag: 'master'")
endif()

set(init_submodules TRUE)
if(init_submodules)
  execute_process(
    COMMAND "E:/Git/mingw64/bin/git.exe"  submodule update --recursive --init 
    WORKING_DIRECTORY "E:/U/Semestre 6°/Estructura de Datos Avanzada/Practico/Repositorios/smart_pointer/source/googletest/googletest-src"
    RESULT_VARIABLE error_code
    )
endif()
if(error_code)
  message(FATAL_ERROR "Failed to update submodules in: 'E:/U/Semestre 6°/Estructura de Datos Avanzada/Practico/Repositorios/smart_pointer/source/googletest/googletest-src'")
endif()

# Complete success, update the script-last-run stamp file:
#
execute_process(
  COMMAND ${CMAKE_COMMAND} -E copy
    "E:/U/Semestre 6°/Estructura de Datos Avanzada/Practico/Repositorios/smart_pointer/build/googletest-download/googletest-prefix/src/googletest-stamp/googletest-gitinfo.txt"
    "E:/U/Semestre 6°/Estructura de Datos Avanzada/Practico/Repositorios/smart_pointer/build/googletest-download/googletest-prefix/src/googletest-stamp/googletest-gitclone-lastrun.txt"
  RESULT_VARIABLE error_code
  )
if(error_code)
  message(FATAL_ERROR "Failed to copy script-last-run stamp file: 'E:/U/Semestre 6°/Estructura de Datos Avanzada/Practico/Repositorios/smart_pointer/build/googletest-download/googletest-prefix/src/googletest-stamp/googletest-gitclone-lastrun.txt'")
endif()

