#include <iostream>
#include <string>

#include <GL/glew.h>
#include <gli/gli.hpp>
#include <glm/glm.hpp>

GLuint createTexture(const char* Filename){
    GLenum result;

	gli::texture Texture = gli::load(Filename);
	if(Texture.empty()){ 
        std::cout << "Texture provided is empty" << std::endl;
        return 1;
    }

	gli::gl GL(gli::gl::PROFILE_GL33);
	gli::gl::format const Format = GL.translate(Texture.format(), Texture.swizzles());
	GLenum Target = GL.translate(Texture.target());
    // assert(gli::is_compressed(Texture.format()) && Target == gli::TARGET_2D);

    // GLuint TextureName = 0;
    GLuint TextureName;
	glGenTextures(1, &TextureName);
    // GLuint TextureNames[100];
    // glGenTextures(100, TextureNames);
	glBindTexture(Target, TextureName);
    result = glGetError();
    if(result != GL_NO_ERROR){
        std::cout << "Error on bind is " << result << std::endl;
        glDeleteTextures(1, &TextureName);
        return 0;
    }
	glTexParameteri(Target, GL_TEXTURE_BASE_LEVEL, 0);
	glTexParameteri(Target, GL_TEXTURE_MAX_LEVEL, static_cast<GLint>(Texture.levels() - 1));
	glTexParameteriv(Target, GL_TEXTURE_SWIZZLE_RGBA, &Format.Swizzles[0]);
    glm::tvec3<GLsizei> MyExtent(Texture.extent(0)); // Because it begins at level zero
	glTexStorage2D(Target, static_cast<GLint>(Texture.levels()), Format.Internal, MyExtent.x, MyExtent.y);
    if(result != GL_NO_ERROR){
        std::cout << "Error is " << result << std::endl;
        glDeleteTextures(1, &TextureName);
        return 0;
    }
    for(std::size_t Level = 0; Level < Texture.levels(); ++Level) {
		glm::tvec3<GLsizei> Extent(Texture.extent(Level));
		glCompressedTexSubImage2D(
			Target, static_cast<GLint>(Level), 0, 0, Extent.x, Extent.y,
			Format.Internal, static_cast<GLsizei>(Texture.size(Level)), Texture.data(0, 0, Level));
        if(result != GL_NO_ERROR){
            std::cout << "Error is " << result << std::endl;
            glDeleteTextures(1, &TextureName);
            return 0;
        }
	}

	return TextureName;
}

GLuint createTexture(const char* Filename){
    GLuint textureName;
    gli::load_ktx;
	return textureName;
}

