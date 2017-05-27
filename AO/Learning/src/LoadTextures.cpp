#include <iostream>
#include <string>

#include <GL/glew.h>
#include <gli/gli.hpp>
#include <glm/glm.hpp>

GLuint createTexture(const char* Filename){
    // GLenum result;

    gli::texture texture = gli::load(Filename);
    if(texture.empty()){
        std::cout << "Texture provided is empty" << std::endl;
        return 1;
    }

    gli::gl GL(gli::gl::PROFILE_GL33);
    gli::gl::format const textureFormat = GL.translate(texture.format(), texture.swizzles());
    GLenum target = GL.translate(texture.target());
    //assert(gli::is_compressed(texture.format()) && Target == gli::TARGET_2D);
    assert(gli::is_compressed(texture.format()));
    // assert(target == gli::TARGET_2D);
    assert(target == GL_TEXTURE_2D);

    // GLuint textureName = 0;
    GLuint textureName;
    // result = glGetError();
    glGenTextures(1, &textureName);
    // GLuint textureNames[100];
    // glGenTextures(100, textureNames)
    // result = glGetError();
    glBindTexture(target, textureName);
    // result = glGetError();
    /* if(result != GL_NO_ERROR){
        std::cout << "Error on bind is " << result << std::endl;
        glDeleteTextures(1, &textureName);
        return 0;
    . */
    glTexParameteri(target, GL_TEXTURE_BASE_LEVEL, 0);
    glTexParameteri(target, GL_TEXTURE_MAX_LEVEL, static_cast<GLint>(texture.levels() - 1));
    glTexParameteriv(target, GL_TEXTURE_SWIZZLE_RGBA, &textureFormat.Swizzles[0]);
    glTexParameteri(target, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(target, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glm::tvec3<GLsizei> Extent(texture.extent()); // Because it begins at level zero
    glTexStorage2D(target, static_cast<GLint>(texture.levels()), textureFormat.Internal, Extent.x, Extent.y);
    /* if(result != GL_NO_ERROR){
        std::cout << "Error is " << result << std::endl;
        glDeleteTextures(1, &textureName);
        return 0;
    . */
    for(std::size_t Level = 0; Level < texture.levels(); ++Level) {
        Extent = texture.extent(Level);
        glCompressedTexSubImage2D(
            target, static_cast<GLint>(Level), 0, 0, Extent.x, Extent.y,
            textureFormat.Internal, static_cast<GLsizei>(texture.size(Level)), texture.data(0, 0, Level));
        /* if(result != GL_NO_ERROR){
            std::cout << "Error is " << result << std::endl;
            glDeleteTextures(1, &textureName);
            return 0;
        } */
    }

    return textureName;
}

GLuint createTexture2(const char* Filename){
    gli::texture Texture = gli::load_ktx(Filename);
    if(Texture.empty()){
        std::cout << "Texture provided is empty or path provided is invalid" << std::endl;
        return 1;
    }

    gli::gl GL(gli::gl::PROFILE_GL33);
    // GL33 looks like the furthest supported version
    gli::gl::format const Format = GL.translate(Texture.format(), Texture.swizzles());
    GLenum Target = GL.translate(Texture.target());

    GLuint textureName;
    glGenTextures(1, &textureName);
    glBindTexture(Target, textureName);
    // glTexStorage2D(Target, 1, );
    return textureName;
}
