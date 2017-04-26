#ifndef MESH_LOADER_H
#define  MESH_LOADER_H

#include "Importer.hpp"
#include "..\assimp\inc\scene.h"
#include "postprocess.h"

#include <vector>
#include <iostream>

#include "soil.h"

#include "drawing_mesh.h"

using namespace std;

class MeshLoader {
	public:
		
	void load_from_file(const string& file,vector<DrawingMesh>& meshes) {
	
			Assimp::Importer importer;
			//const aiScene* assimp_scene = importer.ReadFile(scene_file, aiProcess_Triangulate | aiProcess_FlipUVs);
			const aiScene* assimp_scene = importer.ReadFile(file, 0);
			if (!assimp_scene || assimp_scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !assimp_scene->mRootNode)
			{
				cout << "ERROR::ASSIMP::" << importer.GetErrorString() << endl;
				return;
			}
			directory = file.substr(0,file.find_last_of('\\'));
			processNode(assimp_scene->mRootNode, assimp_scene,meshes);
	}

private:
	string directory;
		void processNode(aiNode* node,  const aiScene* assimp_scene,vector<DrawingMesh>& meshes ) {
			for (int i = 0; i < node->mNumMeshes; i++) {
				aiMesh* mesh = assimp_scene->mMeshes[node->mMeshes[i]];
				meshes.push_back(copy_aasimp_data_2_mesh(mesh,assimp_scene));
			}
			for (int i = 0; i < node->mNumChildren; i++) {
				processNode(node->mChildren[i], assimp_scene,meshes);
			}
		}

		DrawingMesh copy_aasimp_data_2_mesh(aiMesh* a_mesh, const aiScene* a_scene) {
			DrawingMesh mesh;
			mesh.vertex.resize(a_mesh->mNumVertices);
			
			for (int i = 0; i < a_mesh->mNumVertices; i++) {
				mesh.vertex[i].position.x = a_mesh->mVertices[i].x;
				mesh.vertex[i].position.y = a_mesh->mVertices[i].y;
				mesh.vertex[i].position.z = a_mesh->mVertices[i].z;
				if (a_mesh->mNormals != NULL) {
					mesh.vertex[i].normal.x = a_mesh->mNormals[i].x;
					mesh.vertex[i].normal.y = a_mesh->mNormals[i].y;
					mesh.vertex[i].normal.z = a_mesh->mNormals[i].z;
				}

				// A vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't 
                // use models where a vertex can have multiple texture coordinates so we always take the first set (0).
				if (a_mesh->mTextureCoords[0]) {
					glm::vec2 _tCood;
					_tCood.x = a_mesh->mTextureCoords[0][i].x;
					_tCood.y = a_mesh->mTextureCoords[0][i].y;
					mesh.vertex[i].texture_coordinate = _tCood;
				}
			}
			for (int i = 0; i < a_mesh->mNumFaces; i++) {
				auto face = a_mesh->mFaces[i];
				for (int j = 0; j < face.mNumIndices; j++) {
					mesh.triangles.push_back(face.mIndices[j]);
				}

			}
			if (a_mesh->mMaterialIndex >= 0) {
				aiMaterial* material = a_scene->mMaterials[a_mesh->mMaterialIndex];
				auto diffuse_map = loadMaterialTexture(material, aiTextureType_DIFFUSE, "texture_diffuse");
				auto specular_map = loadMaterialTexture(material, aiTextureType_SPECULAR, "texture_specular");
				auto& tx = mesh.texture;
				tx.insert(tx.end(), diffuse_map.begin(), diffuse_map.end());
				tx.insert(tx.end(), specular_map.begin(), specular_map.end());
			}
			
			mesh.prepare_GL_buffer();
			return mesh;

		}


		vector<Texture> loadMaterialTexture(aiMaterial* material, aiTextureType texture_type, string texture_type_name) {
			vector<Texture> ret;
			int tex_num = material->GetTextureCount(texture_type);
			for (int i = 0; i < tex_num; i++) {
				aiString str;
				material->GetTexture(texture_type, i, &str);
				Texture texture;
				texture.id = TextureFromFile(str.C_Str(), directory);
				texture.type=texture_type_name;
				texture.path = str.C_Str();
				ret.push_back(texture);
			}
			return ret;
		}
		GLuint TextureFromFile(const char* file, string directory) {
			string file_name(file);
			file_name = directory + '\\' + file_name;

			GLuint textureID;
			glGenTextures(1, &textureID);
			int width, height;
			unsigned char* image = SOIL_load_image(file_name.c_str(), &width, &height, 0, SOIL_LOAD_RGB);
			// Assign texture to ID
			glBindTexture(GL_TEXTURE_2D, textureID);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
			glGenerateMipmap(GL_TEXTURE_2D);

			// Parameters
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glBindTexture(GL_TEXTURE_2D, 0);
			SOIL_free_image_data(image);
			return textureID;
		}
};

#endif // !MESH_LOADER_H
