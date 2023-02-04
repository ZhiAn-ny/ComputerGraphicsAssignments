#include "cubemap.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

gview::sky::Cubemap::Cubemap() { }

gview::sky::Cubemap::~Cubemap() { }

unsigned int gview::sky::Cubemap::load_skybox(vector<string> faces)
{
	unsigned int textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
	int width, height, nrChannels;

	for (unsigned int i = 0; i < faces.size(); i++)
	{
		unsigned char* data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);

		if (data)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
				0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		}
		else
		{
			std::cout << "Cubemap tex failed to load at path: " << faces[i] << std::endl;
		}
		stbi_image_free(data);
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	return textureID;
}

void gview::sky::Cubemap::init()
{
	gobj::mesh::MeshFactory mf;
	gobj::mesh::Mesh mesh = mf.create_cube();
	this->cube_ = &mesh;
	this->cube_->bind();
}

void gview::sky::Cubemap::set_theme(res::sky::SkyBoxThemes theme)
{
	try {
		this->skybox_ = this->themes_.at(theme);
	}
	catch (const std::out_of_range& e) {
		std::cerr << e.what() << std::endl;
	}
}

void gview::sky::Cubemap::render(Shader* sh, Camera* cam)
{
	//sh->use();
	glDepthMask(GL_FALSE);

	//glUniform1i(glGetUniformLocation(sh->get_ID(), "skybox"), 0);

	glBindVertexArray(this->cube_->get_vao());
	util::check_error("CUBEMAP::ERROR::BIND_VAO");
	glBindTexture(GL_TEXTURE_CUBE_MAP, this->skybox_);
	util::check_error("CUBEMAP::ERROR::BIND_TEXTURE");
	glDrawElements(GL_TRIANGLES, this->cube_->get_indices_size() * sizeof(GLuint), GL_UNSIGNED_INT, 0);
	util::check_error("CUBEMAP::ERROR::DRAW_ELEMENTS");

	glBindVertexArray(0);

	glDepthMask(GL_TRUE);
}
