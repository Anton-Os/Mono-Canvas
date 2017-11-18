message(STATUS "Downloading from Google Drive")

set(GDRIVE_URLS)
set(GDRIVE_NAMES)

list(APPEND GDRIVE_URLS
    "https://drive.google.com/uc?export=download&id=0ByCFa5FWp8ZzVlotdmJ0V0RLc2M"
    "https://drive.google.com/uc?export=download&id=0ByCFa5FWp8ZzejhBY1FhZ0lpMTg"
    "https://drive.google.com/uc?export=download&id=0ByCFa5FWp8ZzNndkbE5uYU04VWc"
    "https://drive.google.com/uc?export=download&id=0ByCFa5FWp8ZzeVM3WGNnQUlEbEU"
    "https://drive.google.com/uc?export=download&id=0ByCFa5FWp8ZzQ1diQVRBMTNSZVk"
    "https://drive.google.com/uc?export=download&id=0ByCFa5FWp8ZzXy1LTkFNQzQ5cjA"
)

list(APPEND GDRIVE_NAMES
    "python-3.6.1-embed.tar"
    "Img2KTX.tar"
    "sqlite-amalgamation-3180000.tar"
    "glew-1.13.0.tgz"
    "fltk-1.3.4-1-source.tar.gz"
    "cpp-netlib-0.12.0-final.tar.gz"
)

foreach(currentFile ${GDRIVE_NAMES})
    message(STATUS "Downloading ${currentFile}")
    list(FIND GDRIVE_NAMES ${currentFile} currentIndex)
    list(GET GDRIVE_URLS ${currentIndex} currentUrl)
    if(NOT EXISTS @CMAKE_BINARY_DIR@/${currentFile})
        file(DOWNLOAD
            "${currentUrl}"
            @CMAKE_BINARY_DIR@/${currentFile}
            SHOW_PROGRESS
        )
    endif()
endforeach()
