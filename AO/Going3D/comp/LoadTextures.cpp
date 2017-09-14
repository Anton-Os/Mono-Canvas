#include "Common.h"

#include <gli/gli.hpp>

GLuint createTexture(const char* Filename){
    // GLenum result;

    gli::texture texture = gli::load(Filename);
    if(texture.empty()){
        std::cout << "Texture " << Filename << " is empty" << std::endl;
        return 1;
    }

    gli::gl GL(gli::gl::PROFILE_GL33);
    gli::gl::format const textureFormat = GL.translate(texture.format(), texture.swizzles());
    GLenum target = GL.translate(texture.target());
    assert(gli::is_compressed(texture.format()));
    assert(target == GL_TEXTURE_2D);

    GLuint textureName;
    glGenTextures(1, &textureName);
    glBindTexture(target, textureName);
    
    glTexParameteri(target, GL_TEXTURE_BASE_LEVEL, 0);
    glTexParameteri(target, GL_TEXTURE_MAX_LEVEL, static_cast<GLint>(texture.levels() - 1));
    glTexParameteriv(target, GL_TEXTURE_SWIZZLE_RGBA, &textureFormat.Swizzles[0]);
    glTexParameteri(target, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(target, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glm::tvec3<GLsizei> Extent(texture.extent()); // Because it begins at level zero
    glTexStorage2D(target, static_cast<GLint>(texture.levels()), textureFormat.Internal, Extent.x, Extent.y);

    for(std::size_t Level = 0; Level < texture.levels(); ++Level) {
        Extent = texture.extent(Level);
        glCompressedTexSubImage2D(
            target,
            static_cast<GLint>(Level),
            0,
            0, 
            Extent.x, 
            Extent.y,
            textureFormat.Internal, 
            static_cast<GLsizei>(texture.size(Level)), 
            texture.data(0, 0, Level)
        );
    }

    return textureName;
}
