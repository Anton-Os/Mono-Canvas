message(STATUS "Downloading from Google Drive")

set(GDRIVE_URLS)
set(GDRIVE_NAMES)

list(APPEND GDRIVE_URLS
    "https://drive.google.com/uc?export=download&id=0ByCFa5FWp8ZzY0RqaWRDejdIS1k"
    "https://drive.google.com/uc?export=download&id=0ByCFa5FWp8Zzdmp4RVBHdlFNeDA"
    "https://drive.google.com/uc?export=download&id=0ByCFa5FWp8ZzbTdXeHV1X3J2U1k"
    "https://drive.google.com/uc?export=download&id=0ByCFa5FWp8ZzUjB5R1pINWRxQTQ"

    "https://drive.google.com/uc?export=download&id=0ByCFa5FWp8Zzc0dNSjlRbThQaFU"
    "https://drive.google.com/uc?export=download&id=0ByCFa5FWp8ZzdUVvOXk4XzlWNTg"
    "https://drive.google.com/uc?export=download&id=0ByCFa5FWp8ZzaWpjVEJEQ2ZEOEE"
    "https://drive.google.com/uc?export=download&id=0ByCFa5FWp8ZzaWNjemIwRzMzQjA"
    "https://drive.google.com/uc?export=download&id=0ByCFa5FWp8Zza2diQlVuZ0lURUU"
    "https://drive.google.com/uc?export=download&id=0ByCFa5FWp8ZzdjJmM25vNloxNlk"
    "https://drive.google.com/uc?export=download&id=0ByCFa5FWp8ZzejFPOGhNUnppa3c"
    "https://drive.google.com/uc?export=download&id=0ByCFa5FWp8ZzOWNnS3d4Z0JsWGs"
    "https://drive.google.com/uc?export=download&id=0ByCFa5FWp8ZzUy04amxDSnpTZWs"
    "https://drive.google.com/uc?export=download&id=0ByCFa5FWp8ZzcFo1MTQ4b2t2NlE"
    "https://drive.google.com/uc?export=download&id=0ByCFa5FWp8ZzZ1gzekJXZVh4UDg"
    "https://drive.google.com/uc?export=download&id=0ByCFa5FWp8ZzRk1MSGNNOUg0WGM"
    "https://drive.google.com/uc?export=download&id=0ByCFa5FWp8ZzNzUxRkR6cnk4aVU"
)

list(APPEND GDRIVE_NAMES
    "LowPolyMill.fbx"
    "KSR-29-SniperRifle.fbx"
    "Wolf-Anim.fbx"
    "Dragon-Anim.fbx"
    
    "BrushedSteel.ktx"
    "ScratchedSteel.ktx"
    "LimeStone.ktx"
    "SevenGrass.ktx"
    "TreeBark.ktx"
    "YoungLeaves.ktx"
    "LightWood.ktx"
    "MedWood.ktx"
    "WoodPlanks.ktx"
    "SeamlessSand.ktx"
    "SandTex1.ktx"
    "MipTest.ktx"
    "Centaur.fbx"
)

foreach(currentFile ${GDRIVE_NAMES})
    list(FIND GDRIVE_NAMES ${currentFile} currentIndex)
    list(GET GDRIVE_URLS ${currentIndex} currentUrl)
    if(NOT EXISTS @CMAKE_CURRENT_BINARY_DIR@/AO/data/${currentFile})
        message(STATUS "Downloading ${currentFile}")
        file(DOWNLOAD
            "${currentUrl}"
            @CMAKE_CURRENT_BINARY_DIR@/AO/data/${currentFile}
            SHOW_PROGRESS
        )
    else()
        message(STATUS "${currentFile} exists in \\data directory")
    endif()
endforeach()
