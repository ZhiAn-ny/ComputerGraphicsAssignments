#include "model.h"

#define STB_IMAGE_STATIC
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

using namespace gobj::mesh;

Model::Model() { }

Model::~Model() { }

gobj::mesh::Model::Model(string const& path)
{
	this->load_model(path);
}

void gobj::mesh::Model::set_name(string name)
{
	this->name_ = name;
}

vec3 gobj::mesh::Model::get_pos()
{
	vec3 pos = this->meshes_[0].get_pos();
	if (this->meshes_.size() == 1) return pos;

	vec3 min = pos;
	vec3 max = pos;
	for (int i = 1; i < this->meshes_.size(); i++)
	{
		pos = this->meshes_[i].get_pos();
		if (pos.x < min.x) min.x = pos.x;
		if (pos.y < min.y) min.y = pos.y;
		if (pos.z < min.z) min.z = pos.z;

		if (pos.x > max.x) max.x = pos.x;
		if (pos.y > max.y) max.y = pos.y;
		if (pos.z > max.z) max.z = pos.z;
	}
	return vec3((min.x + max.x) / 2, (min.y + max.y) / 2, (min.z + max.z) / 2);
}

string gobj::mesh::Model::get_name()
{
	return this->name_;
}

void gobj::mesh::Model::set_material(res::mat::Material mat, bool orig)
{

	for (int i = 0; i < this->meshes_.size(); i++)
	{
		if (orig) this->meshes_[i].reset_material();
		else this->meshes_[i].set_material(mat);
	}
}

void gobj::mesh::Model::set_shading(int type)
{
	for (int i = 0; i < this->meshes_.size(); i++)
		this->meshes_[i].set_shading(type);
}

void gobj::mesh::Model::select()
{
	for (int i = 0; i < this->meshes_.size(); i++)
		this->meshes_[i].select();
}

void gobj::mesh::Model::deselect()
{
	for (int i = 0; i < this->meshes_.size(); i++)
		this->meshes_[i].deselect();
}

bool gobj::mesh::Model::is_selected()
{
	for (int i = 0; i < this->meshes_.size(); i++)
		if (this->meshes_[i].is_selected())
			return true;

	return false;
}

//bool gobj::mesh::Model::is_colliding(vec4 pos)
//{
//	for (int i = 0; i < this->meshes_.size(); i++)
//		if (this->meshes_[i].is_colliding(pos )) return true;
//	return false;
//}

float gobj::mesh::Model::ray_intersection(vec3 origin, vec3 direction)
{
	float distance = INFINITE;
	float d;
	for (int i = 0; i < this->meshes_.size(); i++)
	{
		d = this->meshes_[i].ray_intersection(origin, direction);
		if (d > -1 && d < distance) distance = d;
	}
	return distance == INFINITE ? -1 : distance;
}

void Model::load_model(string path)
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate 
		| aiProcess_FlipUVs | aiProcess_GenNormals);

	if (!scene || scene->mFlags && AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
		return;
	}

	this->file_directory_ = path.substr(0, path.find_last_of('/'));
	this->process_node(scene->mRootNode, scene);

}

void Model::process_node(aiNode* node, const aiScene* scene)
{
	// process all the node's meshes (if any)
	for (unsigned int i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		meshes_.push_back(this->process_mesh(mesh, scene));
	}
	// then do the same for each of its children (define relation)
	for (unsigned int i = 0; i < node->mNumChildren; i++)
	{
		process_node(node->mChildren[i], scene);
	}
}

Mesh Model::process_mesh(aiMesh* mesh, const aiScene* scene)
{
	vector<Vertex> vertices;
	vector<unsigned int> indices;
	vector<Texture> textures;
	res::mat::Material mat = res::mat::tutorial;

	// Add vertices
	for (unsigned int i = 0; i < mesh->mNumVertices; i++)
	{
		Vertex v;

		v.pos.x = mesh->mVertices[i].x;
		v.pos.y = mesh->mVertices[i].y;
		v.pos.z = mesh->mVertices[i].z;

		if (mesh->HasNormals())
		{
			v.normal.x = mesh->mNormals[i].x;
			v.normal.y = mesh->mNormals[i].y;
			v.normal.z = mesh->mNormals[i].z;
		}

		if (mesh->mTextureCoords[0]) {
			v.tex.x = mesh->mTextureCoords[0][i].x;
			v.tex.y = mesh->mTextureCoords[0][i].y;
		} 
		else v.tex = vec2(0.0, 0.0);
		
		vertices.push_back(v);
	}
	// Add indices
	for (unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		for (unsigned int j = 0; j < face.mNumIndices; j++)
			indices.push_back(face.mIndices[j]);
	}
	// Add material textures
	if (mesh->mMaterialIndex >= 0)
	{
		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

		// 1. diffuse maps
		vector<Texture> diffuseMaps = this->load_material(material, aiTextureType_DIFFUSE, TexType::diffuse);
		textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
		// 2. specular maps
		vector<Texture> specularMaps = this->load_material(material, aiTextureType_SPECULAR, TexType::specular);
		textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
		// 3. normal maps
		//std::vector<Texture> normalMaps = this->load_material(material, aiTextureType_HEIGHT, "texture_normal");
		//textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());

		// 4. material parameters
		aiColor3D color;
		float value;
		if (aiReturn_SUCCESS == material->Get(AI_MATKEY_COLOR_AMBIENT, color))
			mat.ambient = vec3(color.r, color.g, color.b);
		if (aiReturn_SUCCESS == material->Get(AI_MATKEY_COLOR_DIFFUSE, color))
			mat.diffuse = glm::vec3(color.r, color.g, color.b);
		if (aiReturn_SUCCESS == material->Get(AI_MATKEY_COLOR_SPECULAR, color))
			mat.specular = glm::vec3(color.r, color.g, color.b);
		if (aiReturn_SUCCESS == material->Get(AI_MATKEY_SHININESS, value))
			mat.shininess = value;
	}

	Mesh m = Mesh(vertices, indices, textures);
	m.set_material(mat, true);
	m.set_diffuse_map(Texture::find_first(TexType::diffuse, textures)->name);

	return m;
}

vector<Texture> Model::load_material(aiMaterial* mat,
		aiTextureType type, TexType typeName)
{
	vector<Texture> textures;

	for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
	{
		aiString str;
		mat->GetTexture(type, i, &str);
		bool skip = false;
		// check if texture was loaded before. If so, skip loading new texture
		for (unsigned int j = 0; j < textures_loaded.size(); j++)
		{
			if (std::strcmp(textures_loaded[j].path.data(), str.C_Str()) == 0)
			{
				textures.push_back(textures_loaded[j]);
				skip = true; // a texture with same path already loaded
				break;
			}
		}
		if (!skip)
		{   // texture hasn't been loaded already
			Texture texture;
			texture.id = this->load_texture(str.C_Str(), this->file_directory_, false);
			texture.type = typeName;
			texture.path = str.C_Str();
			textures.push_back(texture);
			textures_loaded.push_back(texture);  // store it as texture loaded for entire model, to ensure we won't unnecessary load duplicate textures.
		}
	}

	return textures;
}

unsigned int Model::load_texture(const char* path, const string& directory, bool gamma)
{
	GLenum format;
	string filename = string(path);
	filename = directory + '/' + filename;

	unsigned int textureID;
	glGenTextures(1, &textureID);

	int width, height, nrComponents;
	unsigned char* data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
	if (data)
	{
		if (nrComponents == 1) format = GL_RED;
		else if (nrComponents == 3) format = GL_RGB;
		else if (nrComponents == 4) format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	}
	else
	{
		std::cout << "Texture failed to load at path: " << path << std::endl;
	}

	stbi_image_free(data);
	return textureID;
}

void gobj::mesh::Model::bind()
{
	for (int i = 0; i < this->meshes_.size(); i++)
	{
		this->meshes_[i].bind();
	}
}

void gobj::mesh::Model::transform(vec3 tvec, vec3 svec, vec3 rvec, float angle)
{
	for (int i = 0; i < this->meshes_.size(); i++)
	{
		this->meshes_[i].transform(tvec, svec, rvec, angle);
	}
}

void gobj::mesh::Model::move(Directions dir)
{
	for (int i = 0; i < this->meshes_.size(); i++)
		this->meshes_[i].move(dir);
}

void gobj::mesh::Model::render(Shader* sh)
{
	for (int i = 0; i < this->meshes_.size(); i++)
		this->meshes_[i].render(sh);
}
