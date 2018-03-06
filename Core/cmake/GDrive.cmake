message(STATUS "Downloading from Google Drive")

set(GDRIVE_URLS)
set(GDRIVE_NAMES)

list(APPEND GDRIVE_URLS
    "https://drive.google.com/uc?export=download&id=1leGvUR_iBxPmkbnai7IqRoOl5OQoOeeY"
)

list(APPEND GDRIVE_NAMES
    "Smiley.png"
)

foreach(currentFile ${GDRIVE_NAMES})
    list(FIND GDRIVE_NAMES ${currentFile} currentIndex)
    list(GET GDRIVE_URLS ${currentIndex} currentUrl)
    if(NOT EXISTS @RES_DIR@/${currentFile})
        message(STATUS "Downloading ${currentFile}")
        file(DOWNLOAD
            "${currentUrl}"
            @RES_DIR@/${currentFile}
            SHOW_PROGRESS
        )
    else()
        message(STATUS "${currentFile} exists in \\res directory")
    endif()
endforeach()
