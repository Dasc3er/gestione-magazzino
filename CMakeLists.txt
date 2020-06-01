cmake_minimum_required(VERSION 3.13)

# Impostazioni di compilazione
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O2")

# Impostazione nome del progetto
project (gestione-magazzino)

# Creazione della libreria CSV (cartella csv/)
set(CSV_SOURCES
	csv/csv_file.c
	csv/csv_row.c
	csv/csv_records.c
	csv/utils.c
	csv/csv.h # Aggiunta dell'header csv.h per semplificare l'importazione esterna
)

add_library(csv STATIC ${CSV_SOURCES})
include_directories(${CMAKE_SOURCE_DIR}/csv)

# Creazione eseguibile
set(SOURCES
	src/main.c
	src/magazzino.c
	src/storico.c
	src/utils.c
)

add_executable(gestione-magazzino ${SOURCES})

# Aggiunta della libreria CSV
target_link_libraries(gestione-magazzino csv)

# Creazione documentazione tramite Doxygen
find_package(Doxygen)
if(DOXYGEN_FOUND)
    set(doxyfile_in ${CMAKE_CURRENT_SOURCE_DIR}/doxygen.config)
    set(doxygen_folder ${CMAKE_CURRENT_SOURCE_DIR}/doxygen/)
    message("Creazione task per la documentazione Doxygen.")

	file(MAKE_DIRECTORY ${doxygen_folder})

    add_custom_target(docs
		COMMAND ${DOXYGEN_EXECUTABLE} ${doxyfile_in}
		COMMENT "Generazione della documentazione tramite Doxygen"
		VERBATIM)
else (NOT DOXYGEN_FOUND)
	message(FATAL_ERROR "Doxygen is needed to build the documentation.")
endif()