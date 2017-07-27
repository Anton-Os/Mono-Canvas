message(STATUS "Downloading from Google Drive")

if(NOT EXISTS D:/AntonDocs/MonoCanvas/MinGW-64/AO/AO/Going3D/data/Sponge.obj)
    file(DOWNLOAD
        "https://drive.google.com/uc?export=download&id=0ByCFa5FWp8ZzS2RZdjhJZDgwMlU"
        D:/AntonDocs/MonoCanvas/MinGW-64/AO/AO/Going3D/data/Sponge.obj
        SHOW_PROGRESS
    )
endif()
